// Copyright 2009 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Oscillators. Note that the code of each oscillator is duplicated/specialized,
// for a noticeable performance boost.

#ifndef SHRUTHI_OSCILLATOR_H_
#define SHRUTHI_OSCILLATOR_H_

#include "avrlib/base.h"
#include "shruthi/shruthi.h"

#include "shruthi/patch.h"
#include "shruthi/resources.h"
#include "avrlib/random.h"
#include "avrlib/op.h"

using namespace avrlib;

static const uint16_t kWavetableSize = 16 * 129;	// each table has 16 single cycle waves
//static const uint16_t kUserWavetableSize = 8 * 129;	// #### DELETE ###

namespace shruthi {
// ### ADDED ###
// Pattern: 11 111 111               1-2,1-3,1-4,-1-5,1-6,1-7,1-8,2-3,2-4,2-5,2-6,2-7,2-8,
static const uint8_t oDivisions[] = { 10, 11, 12, 13, 14, 15,  8, 19, 20, 21, 22, 23, 16, 
								  //3-4,3-5,3-6,3-7,3-8,4-5,4-6,4-7,4-8,5-6,5-7,5-8,6-7,6-8,7-8
									28, 29, 30, 31, 24, 37, 38, 39, 32, 46, 47, 40, 55, 48, 56};

static const uint8_t twelth_rem[] = {  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
										0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
}; 
static const uint8_t twelth_div[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
										2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
										3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
										4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
										5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
										6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
										7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
										8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
										9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
										10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10
}; 

enum ShiftType { F_SHIFT, F_EVEN, P_SHIFT, F_SHIFT_SYNC_R, F_EVEN_SYNC_R, P_SHIFT_SYNC_R};//, F_SHIFT_SYNC_1, F_EVEN_SYNC_1, P_SHIFT_SYNC_1};
static const int8_t MIN_SHIFT_AMOUNT = -63;
static const int8_t MAX_SHIFT_AMOUNT = 63;

static inline uint8_t ReadSample(
    const prog_uint8_t* table,
    uint16_t phase) __attribute__((always_inline));
static inline uint8_t ReadSample(
    const prog_uint8_t* table,
    uint16_t phase) {
  return ResourcesManager::Lookup<uint8_t, uint8_t>(table, phase >> 8);
}

#ifdef USE_OPTIMIZED_OP

static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) __attribute__((always_inline));


static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) {
  uint8_t result;
  uint8_t work;
  asm(
    "movw r30, %A2"           "\n\t"  // copy base address to r30:r31
    "add r30, %B3"            "\n\t"  // increment table address by phaseH
    "adc r31, r1"             "\n\t"  // just carry
    "mov %1, %A3"             "\n\t"  // move phaseL to working register
    "ld %0, z+"               "\n\t"  // load sample[n]
    "ld r1, z+"               "\n\t"  // load sample[n+1]
    "mul %1, r1"              "\n\t"  // multiply second sample by phaseL
    "movw r30, r0"            "\n\t"  // result to accumulator
    "com %1"                  "\n\t"  // 255 - phaseL -> phaseL
    "mul %1, %0"              "\n\t"  // multiply first sample by phaseL
    "add r30, r0"             "\n\t"  // accumulate L
    "adc r31, r1"             "\n\t"  // accumulate H
    "eor r1, r1"              "\n\t"  // reset r1 after multiplication
    "mov %0, r31"             "\n\t"  // use sum H as output
    : "=r" (result), "=r" (work)
    : "r" (table), "r" (phase)
    : "r30", "r31"
  );
  return result;
}

#else

static inline uint8_t InterpolateSampleRam(
    const uint8_t* table,
    uint16_t phase) {
  return U8Mix(table[phase >> 8], table[1 + (phase >> 8)], phase & 0xff);
}
#endif  // USE_OPTIMIZED_OP

static inline uint8_t InterpolateTwoTables(
    const prog_uint8_t* table_a, const prog_uint8_t* table_b,
    uint16_t phase, uint8_t gain_a, uint8_t gain_b) {
  return U8Mix(
      InterpolateSample(table_a, phase),
      InterpolateSample(table_b, phase),
      gain_a, gain_b);
}

static const uint8_t kVowelControlRateDecimation = 4;
static const uint8_t kNumZonesFullSampleRate = 6;
static const uint8_t kNumZonesHalfSampleRate = 5;

struct VowelSynthesizerState {
  uint16_t formant_increment[3];
  uint16_t formant_phase[3];
  uint8_t formant_amplitude[3];
  uint8_t noise_modulation;
  uint8_t update;  // Update only every kVowelControlRateDecimation-th call.
};

struct FilteredNoiseState {
  uint8_t lp_noise_sample;
  uint16_t rng_state;
  uint16_t rng_reset_value;
};

struct QuadSawPadState {
  uint16_t phase[3];
};

struct CrushedSineState {
  uint8_t decimate;
  uint8_t state;
};

union OscillatorState {
  VowelSynthesizerState vw;
  FilteredNoiseState no;
  QuadSawPadState qs;
  CrushedSineState cr;
  uint16_t secondary_phase;
  uint16_t secondary_phase2;
  uint16_t secondary_phase3;
};

class Oscillator {
 public:
 // typedef void (Oscillator::*RenderFn)(uint8_t*);
   
  Oscillator() { }
  ~Oscillator() { }
  
  inline void Reset() {
    data_.no.rng_reset_value = Random::GetByte() + 1;
  }

  inline void RenderHMC(
      uint8_t shape,
      uint8_t note,
      uint24_t increment,
      uint8_t* sync_input,
      uint8_t* sync_output,
      uint8_t* buffer,
      uint8_t* buffer2,
      uint8_t* buffer3,
      uint8_t* buffer4
	  ) {
	// Set current osc values
    shape_ = shape;
    note_ = note;
    phase_increment_ = increment;
	set_increments();
    sync_input_ = sync_input;
    sync_output_ = sync_output;
	render_count_++;
	// switch on shape value
	switch(shape)
	{
		case WAVEFORM_NONE:
			RenderSilenceHMC(buffer, buffer2, buffer3, buffer4);
			return;
		case WAVEFORM_SQUARE:
		case WAVEFORM_SAW:
		case WAVEFORM_TRIANGLE:
			RenderSimpleWavetableHMC(buffer, buffer2, buffer3, buffer4);
			return;
		case WAVEFORM_WAVETABLE_1:
		case WAVEFORM_WAVETABLE_2:
		case WAVEFORM_WAVETABLE_3:
		case WAVEFORM_WAVETABLE_4:
		case WAVEFORM_WAVETABLE_5:
		case WAVEFORM_WAVETABLE_6:
		case WAVEFORM_WAVETABLE_7:
		case WAVEFORM_WAVETABLE_8:
		case WAVEFORM_WAVETABLE_9:
		case WAVEFORM_WAVETABLE_10:
		case WAVEFORM_WAVETABLE_11:
		case WAVEFORM_WAVETABLE_12:
		case WAVEFORM_WAVETABLE_13:
		case WAVEFORM_WAVETABLE_14:
		case WAVEFORM_WAVETABLE_15:
		case WAVEFORM_WAVETABLE_16:
		case WAVEFORM_WAVETABLE_17:
		case WAVEFORM_WAVETABLE_18:
			RenderInterpolatedWavetableHMC(buffer, buffer2, buffer3, buffer4);
			return;
		case WAVEFORM_8BITLAND:
			Render8BitLandHMC(buffer, buffer2, buffer3, buffer4);
			return;
		case WAVEFORM_CRUSHED_SINE:
			RenderCrushedSineHMC(buffer, buffer2, buffer3, buffer4);
			return;
		default:
			RenderSilenceHMC(buffer, buffer2, buffer3, buffer4);
	}
  }

  inline void set_parameter(uint8_t parameter) {
    parameter_ = parameter;
  }
  
  inline void set_secondary_parameter(uint8_t secondary_parameter) {
    secondary_parameter_ = secondary_parameter;
  }

  /*
  * Sets the division amounts for the Oscillator 'partials'
  */
  inline void set_divisions(uint8_t div_code)
  {
	  // NO CHECK FOR VALID RANGE!!!!
	  divisions_ = oDivisions[div_code];
  }
  
  /*
  * Sets the type of frequency shift
  */
  inline void set_shift_type(uint8_t shift_type)
  {
	  shift_type_ = static_cast<ShiftType>(shift_type);
  }
    
  /*
  * Sets the amount of frequency shift
  */
  inline void set_shift_amount(int8_t amount)
  {
	// special case
	// bigger sweep for fine amount
	shift_val_amount_ = amount;
	if(amount == -63)
	{
		shift_amount_ = 0;
		return;
	}
	// negative values
	if(amount < 0)
	{
		// convert to positive value for shift
		// shift and then convert back to negative value
		shift_amount_ = ~(((~amount + 1)  * phase_increment_.integral) >> 6) + 1;
	}
	// zero
	else if(amount == 0)
	{
		shift_amount_ = 0;
	}
	// positive values
	else
	{

		// positive shift - semitones...
		int16_t zeroVal = ResourcesManager::Lookup<uint16_t, uint16_t>(lut_res_oscillator_increments, twelth_rem[note_ + 4] << 3) >> (10 - twelth_div[note_ + 4]);
		int8_t key = twelth_rem[note_ + 4 + amount];
		int8_t octave = twelth_div[note_ + 4 + amount];
		shift_amount_ = (ResourcesManager::Lookup<uint16_t, uint16_t>(lut_res_oscillator_increments, key << 3) >> (10 - octave)) - zeroVal;
	}
  }

  /*
  * Sets the fine amount of frequency shift
  */
  inline void set_shift_fine(uint8_t fine)
  {
	// special case
	// Larger sweep from zero shift_amount_
	if(shift_val_amount_ == -63)
	{
		shift_amount_ += (fine * phase_increment_.integral) >> 5;
		return;
	}
	// special case
	// Octave shift at limit
	if(fine == 127)
	{
		shift_amount_ += phase_increment_.integral << 1;
		return;
	}
	shift_amount_ += (fine * phase_increment_.integral) >> 6;
  }

  /*
  * Adds a metallic modulation effect to the oscillator
  *   alternates the shift of the phase
  */
  inline void set_warp(uint8_t warp)
  {
	  warp_ = phase_increment_.integral * warp;
  }

  /*
   *  Sets the frequency of the warp modulation
   *  *** extra mostly useless bit ***
   */
  inline void set_warp_check(uint8_t warp_check)
  {
		if (warp_check)
		{
			warp_check_ = 16384 - ((warp_check++) << 7);
			return;
		}
		warp_check_ = 16384;
  }

  /*
   *  Sets the phase increments for all 3 divisions
   *  Also adds the shift amount for all 3 divisions
   */
  inline void set_increments()
  {
	// default for increments is 2
	phase_increment2_ = phase_increment3_ = U24ShiftLeft(phase_increment_);
	switch (divisions_ & 56) // ### Div 1
	{
		case 8:	// 1
			phase_increment2_ = phase_increment_;
			break;
		case 24:	// 3 (2 + 1)
			phase_increment2_ = U24Add(phase_increment2_, phase_increment_);
			break;
		case 32:	// 4
			phase_increment2_ = U24ShiftLeft(phase_increment2_);
			break;
		case 40:	// 5 (4 + 1)
			phase_increment2_ = U24Add(U24ShiftLeft(phase_increment2_), phase_increment_);
			break;
		case 48:	// 6 (4 + 2)
			phase_increment2_ = U24Add(U24ShiftLeft(phase_increment2_), phase_increment2_);
			break;
		case 56:	// 7 (8 - 1)
			phase_increment2_ = U24Sub(U24ShiftLeft(U24ShiftLeft(phase_increment2_)), phase_increment_);
			break;
		default:	// 2 - Already set
			break;
	}
	switch (divisions_ & 7) // ### Div 2
	{
		case 3: // 3 (2 + 1)
			phase_increment3_ = U24Add(phase_increment3_, phase_increment_);
			break;
		case 4: // 4
			phase_increment3_ = U24ShiftLeft(phase_increment3_);
			break;
		case 5:	// 5 (4 + 1)
			phase_increment3_ = U24Add(U24ShiftLeft(phase_increment3_), phase_increment_);
			break;
		case 6:	// 6 (4 + 2)
			phase_increment3_ = U24Add(U24ShiftLeft(phase_increment3_), phase_increment3_);
			break;
		case 7:	// 7 (8 _ 1)
			phase_increment3_ = U24Sub(U24ShiftLeft(U24ShiftLeft(phase_increment3_)), phase_increment_);
			break;
		case 0:	// 8
			phase_increment3_ = U24ShiftLeft(U24ShiftLeft(phase_increment3_));
			break;
		default:	// 2 - Already set 
			break;
	}
	// Add shift amounts to each phase increment
	uint24_t shift_adjust;
	shift_adjust.integral = shift_amount_;
	uint24_t double_shift = U24ShiftLeft(shift_adjust);
	switch (shift_type_)
	{
		case F_SHIFT:
		case F_SHIFT_SYNC_R: // Freq Shift adds one shift to each
			phase_increment2_ = U24Add(phase_increment2_, shift_adjust);	
			phase_increment3_ = U24Add(phase_increment3_, shift_adjust);
			//phase_increment4_ = U24Add(phase_increment4_, shift_adjust);
			break;
		case P_SHIFT: 
		case P_SHIFT_SYNC_R:	// Pitch Shift adds equal shift amount to each increment
			switch (divisions_ & 56) // ### Div 1
			{
				case 8:		// 1	ALWAYS ADD SHIFT TO 1!
					phase_increment2_ = U24Add(phase_increment2_, shift_adjust);
					break;
				case 24:	// 3 (2 + 1)
					phase_increment2_ = U24Add(phase_increment2_, U24Add(double_shift, shift_adjust));
					break;
				case 32:	// 4
					phase_increment2_ = U24Add(phase_increment2_, U24ShiftLeft(double_shift));
					break;
				case 40:	// 5 (4 + 1)
					phase_increment2_ = U24Add(phase_increment2_, U24Add(U24ShiftLeft(double_shift), shift_adjust));
					break;
				case 48:	// 6 (4 + 2)
					phase_increment2_ = U24Add(phase_increment2_, U24Add(U24ShiftLeft(double_shift), double_shift));
					break;
				case 56:	// 7 (8 - 1)
					phase_increment2_ = U24Sub(U24ShiftLeft(U24ShiftLeft(double_shift)), shift_adjust);
					break;
				default:	// 2
					phase_increment2_ = U24Add(phase_increment2_, double_shift);
					break;
			}
			switch(divisions_ & 7) // ### Div 2
			{
				case 3:	// 3 (2 + 1)
					phase_increment3_ = U24Add(phase_increment3_, U24Add(double_shift, shift_adjust));
					break;
				case 4: // 4
					phase_increment3_ = U24Add(phase_increment3_, U24ShiftLeft(double_shift));
					break;
				case 5: // 5 (4 + 1)
					phase_increment3_ = U24Add(phase_increment3_, U24Add(U24ShiftLeft(double_shift), shift_adjust));
					break;
				case 6:	// 6 (4 + 2)
					phase_increment3_ = U24Add(phase_increment3_, U24Add(U24ShiftLeft(double_shift), double_shift));
					break;
				case 7: // 7 (8 - 1)
					phase_increment3_ = U24Add(phase_increment3_, U24Sub(U24ShiftLeft(U24ShiftLeft(double_shift)), shift_adjust));
					break;
				case 0: // 8
					phase_increment3_ = U24Add(phase_increment3_, U24ShiftLeft(U24ShiftLeft(double_shift)));
					break;
				default: // 2
					phase_increment3_ = U24Add(phase_increment3_, double_shift);
					break;
			}
			break;
		case F_EVEN:
		case F_EVEN_SYNC_R: // Add 1 less shift amount than Pitch Shift
			switch (divisions_ & 192) // ### Div 1
			{
				case 8:	// 1 - Always add one!
					phase_increment2_ = U24Add(phase_increment2_, shift_adjust);
					break;
				case 24:	// 3 - 2
					phase_increment2_ = U24Add(phase_increment2_, double_shift);
					break;
				case 32:	// 4 - 3
					phase_increment2_ = U24Add(phase_increment2_, U24Add(double_shift, shift_adjust));
					break;
				case 40:	// 5 - 4
					phase_increment2_ = U24Add(phase_increment2_, U24ShiftLeft(double_shift));
					break;
				case 48:	// 6 - 5
					phase_increment2_ = U24Add(phase_increment2_, U24Add(shift_adjust, U24ShiftLeft(double_shift)));
					break;
				case 56:	// 7 - 6
					phase_increment2_ = U24Add(phase_increment2_, U24Add(double_shift, U24ShiftLeft(double_shift)));
					break;
				default:	// 2 - 1
					phase_increment2_ = U24Add(phase_increment2_, shift_adjust);
					break;
			}
			switch(divisions_ & 7) // ### Div 
			{
				case 3:	// 3 - 2
					phase_increment3_ = U24Add(phase_increment3_, double_shift);
					break;
				case 4:	// 4 - 3
					phase_increment3_ = U24Add(phase_increment3_, U24Add(double_shift, shift_adjust));
					break;
				case 5:	// 5 - 4
					phase_increment3_ = U24Add(phase_increment3_, U24ShiftLeft(double_shift));
					break;
				case 6:	// 6 - 5
					phase_increment3_ = U24Add(phase_increment3_, U24Add(U24ShiftLeft(double_shift), shift_adjust));
					break;
				case 7:	// 7 - 6
					phase_increment3_ = U24Add(phase_increment3_, U24Add(U24ShiftLeft(double_shift), double_shift));
					break;
				case 0:	// 8 - 7
					phase_increment3_ = U24Add(phase_increment3_, U24Sub(U24ShiftLeft(U24ShiftLeft(double_shift)), shift_adjust));
					break;
				default:	// 2 - 1
					phase_increment3_ = U24Add(phase_increment3_, shift_adjust);
					break;
			}
			break;
	}
  }
  
  //static const uint16_t CHOPPER_MAX = 65535;
 
private:
  // Current phase of the oscillator.
  uint24_t phase_;
  uint24_t phase2_;
  uint24_t phase3_;
  //uint24_t phase4_;

  uint16_t render_count_;
  uint16_t chopper_;
  uint16_t chopper_check_;
  uint16_t warp_;
  static uint16_t warp_check_;

  // divisions
  uint8_t divisions_;
  // shift fields
  ShiftType shift_type_;
  int16_t shift_amount_;
  int8_t shift_val_amount_;

  // Phase increment (and phase increment x 2, for low-sr oscillators).
  uint24_t phase_increment_;
  uint24_t phase_increment2_;
  uint24_t phase_increment3_;
  //uint24_t phase_increment4_;

  // Copy of the shape used by this oscillator. When changing this, you
  // should also update the Update/Render pointers.
  uint8_t shape_;

  // Current value of the oscillator parameter.
  uint8_t parameter_;
  uint8_t secondary_parameter_;
  uint8_t note_;

  // Union of state data used by each algorithm.
  OscillatorState data_;
  
  // A flag set to true when sync is enabled ; and a table to record the
  // position of phrase wraps
  uint8_t* sync_input_;
  uint8_t* sync_output_;
  
  
  // Since this is the most computationally expensive function, we still
  // duplicated it into a "master" and a "slave" version for OSC1 and OSC2,
  // with the corresponding oscillators sync code stripped away.
  //void RenderBandlimitedPwmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  
  void RenderSilenceHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void RenderSimpleWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void RenderInterpolatedWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void RenderDirtyPwmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void Render8BitLandHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void RenderCrushedSineHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  //void RenderCzSawHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  //void RenderCzPulseResoHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  //void RenderCzResoHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  //void RenderFmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);

  //void RenderSweepingWavetableRam(uint8_t* buffer);
  //void RenderVowel(uint8_t* buffer);
  //void RenderQuadSawPad(uint8_t* buffer);
  //void RenderFilteredNoise(uint8_t* buffer);

  DISALLOW_COPY_AND_ASSIGN(Oscillator);
};

}  // namespace shruthi

#endif // SHRUTHI_OSCILLATOR_H_

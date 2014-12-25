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
// remainders for semitone shift amounts
static const uint8_t twelth_rem[] = {  32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24, 
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
										32, 40, 48, 56, 64, 72, 80, 88, 0, 8, 16, 24,
}; 
// octaves for semitone shift amounts
static const uint8_t twelth_div[] = {  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
										1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
										2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
										3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4,
										4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 
										5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6,
										6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7,
										7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
										8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9,
										9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10,
										10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11
}; 
// six types of division shifts
enum ShiftType { F_SHIFT, F_EVEN, P_SHIFT, F_SHIFT_SYNC_R, F_EVEN_SYNC_R, P_SHIFT_SYNC_R, LAST_SHIFT_TYPE};
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

static inline uint8_t InterpolateTwoTables(
    const prog_uint8_t* table_a, const prog_uint8_t* table_b,
    uint16_t phase, uint8_t gain_a, uint8_t gain_b) {
  return U8Mix(
      InterpolateSample(table_a, phase),
      InterpolateSample(table_b, phase),
      gain_a, gain_b);
}

class Oscillator {
 public:
   
  Oscillator() { }
  ~Oscillator() { }
  
  /*
   * Generate Samples
   */
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
	// update divisions when osc or setting change
	if( phase_increment_.integral != increment.integral || 
		phase_increment_.fractional != increment.fractional || 
		note_ != note || 
		increment_change_ )
	{
		note_ = note;
		phase_increment_ = increment;
		// calculate shift amounts
		update_shift_amount();
		update_shift_fine();
		// redo shifts
		set_increments();
		// reset
		increment_change_ = 0;
	}
	// set current shape values
    shape_ = shape;
    sync_input_ = sync_input;
    sync_output_ = sync_output;
	// switch on shape value
	switch(shape)
	{
		case WAVEFORM_NONE:
			RenderSilenceHMC(buffer, buffer2, buffer3, buffer4);
			return;
		case WAVEFORM_SAW:
		case WAVEFORM_SQUARE:
		case WAVEFORM_TRIANGLE:
		case WAVEFORM_SINE:
			RenderSimpleWavetableHMC(buffer, buffer2, buffer3, buffer4, true);
			return;
		case WAVEFORM_SAW2:
		case WAVEFORM_TRIANGLE2:
		case WAVEFORM_SQUARE2:
		case WAVEFORM_SINE2:
			RenderSimpleWavetableHMC(buffer, buffer2, buffer3, buffer4, false);
			return;
		default:
			RenderInterpolatedWavetableHMC(buffer, buffer2, buffer3, buffer4);
			return;
	}
  }

  inline void set_parameter(uint8_t parameter) {
    parameter_ = parameter;
  }
  
  /*
  * Sets the division amounts for the Oscillator 'partials'
  */
  inline void set_divisions(uint8_t div_code)
  {
	  if(divisions_ != oDivisions[div_code])
	  {
		  // NO CHECK FOR VALID RANGE!!!!
		  divisions_ = oDivisions[div_code];
		  // update division increments
		  increment_change_ = 1;
	  }
  }
  
  /*
  * Sets the type of frequency shift
  */
  inline void set_shift_type(uint8_t shift_type)
  {
	  if(shift_type_ != shift_type)
	  {
		shift_type_ = shift_type;
		// update division increments
		increment_change_ = 1;
	  }
  }

  /*
   * Returns the currently set shift type
   */
  inline uint8_t get_shift_type()
  {
	  return shift_type_;
  }
    
  /*
  * Sets the amount of frequency shift
  */
  inline void set_shift_amount(int8_t amount)
  {
	// unchanged - do nothing
	if(shift_value_ != amount)
	{
		shift_value_ = amount;
		// update division increments
		increment_change_ = 1;
	}
  }

  /*
  * Sets the fine amount of frequency shift
  */
  inline void set_shift_fine(uint8_t fine)
  {
	// do nothing if unchanged
	if(shift_fine_value_ != fine)
	{
		shift_fine_value_ = fine;
		// update division increments
		increment_change_ = 1;
	}
  }

  /*
  * Updates the amount of frequency shift
  */
  inline void update_shift_amount()
  {
	// zero
	if(!shift_value_)
	{
		shift_amount_ = 0;
	}
	// special case
	// bigger sweep for fine amount
	else if(shift_value_ == -64)
	{
		shift_amount_ = 0;
	}
	// negative values
	else if(shift_value_ < 0)
	{
		// convert to positive value for shift
		// shift and then convert back to negative value
		shift_amount_ = ~(((~shift_value_ + 1)  * phase_increment_.integral) >> 6) + 1;
	}
	// positive values
	else
	{
		// positive shift - semitones...
		int16_t zeroVal = ResourcesManager::Lookup<uint16_t, uint16_t>(
			lut_res_oscillator_increments, twelth_rem[note_]) >> (10 - twelth_div[note_]);
		shift_amount_ = (ResourcesManager::Lookup<uint16_t, uint16_t>(
			lut_res_oscillator_increments, twelth_rem[note_ + shift_value_]) >> (10 - twelth_div[note_ + shift_value_])) - zeroVal;
	}
  }

  /*
  * Updates the fine amount of frequency shift
  */
  inline void update_shift_fine()
  {
	// ZERO
	if(!shift_fine_value_)
	{	
		shift_fine_amount_ = 0;
	}
	// special case
	// Larger sweep from zero shift_amount_
	else if(shift_value_ == -64)
	{
		shift_fine_amount_ = (shift_fine_value_ * phase_increment_.integral) >> 5;
	}
	// special case
	// Octave shift at limit
	else if(shift_fine_value_ == 127)
	{
		shift_fine_amount_ = phase_increment_.integral << 1;
	}
	else
	{
		shift_fine_amount_ = (shift_fine_value_ * phase_increment_.integral) >> 6;
	}
  }

  /*
   *  Sets the phase increments for all 3 divisions
   *  Also adds the shift amount for all 3 divisions
   */
  inline void set_increments()
  {
	// ******* Update when - phase_increment_ / divisions_ / shift_amount_ / shift_fine / shift_type_ change
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
	shift_adjust.integral = shift_amount_ + shift_fine_amount_;
	if(shift_adjust.integral)
	{
		uint24_t double_shift = U24ShiftLeft(shift_adjust);
		ShiftType shift_type = static_cast<ShiftType>(shift_type_);
		switch (shift_type)
		{
		case F_SHIFT:
		case F_SHIFT_SYNC_R: // Freq Shift adds one shift to each
			phase_increment2_ = U24Add(phase_increment2_, shift_adjust);	
			phase_increment3_ = U24Add(phase_increment3_, shift_adjust);
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
					phase_increment2_ = U24Add(phase_increment2_, U24Sub(U24ShiftLeft(U24ShiftLeft(double_shift)), shift_adjust));
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
			switch (divisions_ & 56) // ### Div 1
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
			switch(divisions_ & 7) // ### Div 2
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
  }
   
private:
  // Current phase of the oscillator.
  uint24_t phase_;
  uint24_t phase2_;
  uint24_t phase3_;
  //uint24_t phase4_;

  uint16_t warp_;
  static uint16_t warp_check_;

  // divisions code index
  uint8_t divisions_;
  // shift fields
  uint8_t shift_type_;
  int16_t shift_amount_;
  int16_t shift_fine_amount_;
  int8_t shift_value_;
  int8_t shift_fine_value_;
  uint8_t increment_change_;

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
  uint8_t note_;

  // A flag set to true when sync is enabled ; and a table to record the
  // position of phrase wraps
  uint8_t* sync_input_;
  uint8_t* sync_output_;
  
  void RenderSilenceHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);
  void RenderSimpleWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4, bool pulse_width);
  void RenderInterpolatedWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4);

  DISALLOW_COPY_AND_ASSIGN(Oscillator);
};

}  // namespace shruthi

#endif // SHRUTHI_OSCILLATOR_H_

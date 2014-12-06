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

#include "shruthi/oscillator.h"

namespace shruthi {

#define UPDATE_PHASE_DIV \
		if (*sync_input_++) { \
			phase2.integral = 0;	\
			phase2.fractional = 0;	\
			phase3.integral = 0;	\
			phase3.fractional = 0;	\
		}	\
		phase = U24AddC(phase, phase_increment_int);	\
		phase2 = U24AddC(phase2, phase_increment_int2);	\
		phase3 = U24AddC(phase3, phase_increment_int3);	\
		*sync_output_++ = phase.carry;


#define BEGIN_SAMPLE_LOOP_DIV \
	uint24c_t phase;	\
	uint24c_t phase2;	\
	uint24c_t phase3;	\
	uint24_t phase_increment_int;	\
	uint24_t phase_increment_int2;	\
	uint24_t phase_increment_int3;	\
	phase_increment_int.integral = phase_increment_.integral;	\
	phase_increment_int.fractional = phase_increment_.fractional;	\
	phase_increment_int2.integral = phase_increment2_.integral;	\
	phase_increment_int2.fractional = phase_increment2_.fractional;	\
	phase_increment_int3.integral = phase_increment3_.integral;	\
	phase_increment_int3.fractional = phase_increment3_.fractional;	\
	phase.integral = phase_.integral;	\ 
	phase.fractional = phase_.fractional;	\ 
	phase2.integral = phase2_.integral;	\ 
	phase2.fractional = phase2_.fractional;	\ 
	phase3.integral = phase3_.integral;	\ 
	phase3.fractional = phase3_.fractional;	\ 
	uint8_t size = kAudioBlockSize;	\
	uint16_t warp_check = warp_check_;

#define END_SAMPLE_LOOP_DIV \
	phase_.integral = phase.integral;	\
	phase_.fractional = phase.fractional;	\
	phase2_.integral = phase2.integral;	\
	phase2_.fractional = phase2.fractional;	\
	phase3_.integral = phase3.integral;	\
	phase3_.fractional = phase3.fractional;	\

// ------- Silence (useful when processing external signals) -----------------
void Oscillator::RenderSilenceHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4){
  uint8_t size = kAudioBlockSize;
  while (size--) {
    *buffer++ = 128;
    *buffer2++ = 128;
    *buffer3++ = 128;
    //*buffer4++ = 128;
  }
}

  uint16_t Oscillator::warp_check_ = 16384;


//// ------- Band-limited PWM --------------------------------------------------
//void Oscillator::RenderBandlimitedPwmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4){
//  uint8_t balance_index = U8Swap4(note_ - 12);
//  uint8_t gain_2 = balance_index & 0xf0;
//  uint8_t gain_1 = ~gain_2;
//
//  uint8_t wave_index = balance_index & 0xf;
//  const prog_uint8_t* wave_1 = waveform_table[
//      WAV_RES_BANDLIMITED_SAW_1 + wave_index];
//  wave_index = U8AddClip(wave_index, 1, kNumZonesHalfSampleRate);
//  const prog_uint8_t* wave_2 = waveform_table[
//      WAV_RES_BANDLIMITED_SAW_1 + wave_index];
//  
//  uint16_t shift = static_cast<uint16_t>(parameter_ + 128) << 8;
//  // For higher pitched notes, simply use 128
//  uint8_t scale = 192 - (parameter_ >> 1);
//  if (note_ > 64) {
//    scale = U8Mix(scale, 102, (note_ - 64) << 2);
//    scale = U8Mix(scale, 102, (note_ - 64) << 2);
//  }
//  
//  phase_increment_ = U24ShiftLeft(phase_increment_);
//  
//  BEGIN_SAMPLE_LOOP_DIV
//    phase = U24AddC(phase, phase_increment_int);
//    *sync_output_++ = phase.carry;
//    *sync_output_++ = 0;
//    if (sync_input_[0] || sync_input_[1]) {
//      phase.integral = 0;
//      phase.fractional = 0;
//    }
//    sync_input_ += 2;
//    
//    uint8_t a = InterpolateTwoTables(
//        wave_1, wave_2,
//        phase.integral, gain_1, gain_2);
//    a = U8U8MulShift8(a, scale);
//    uint8_t b = InterpolateTwoTables(
//        wave_1, wave_2,
//        phase.integral + shift, gain_1, gain_2);
//    b = U8U8MulShift8(b, scale);
//    a = a - b + 128;
//    *buffer++ = a;
//    *buffer++ = a;
//    size--;
//  END_SAMPLE_LOOP_DIV
//}

// ###### ADDED ######
void Oscillator::RenderSimpleWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4){
	// swap byte halves
	uint8_t balance_index = U8Swap4(note_ - 12);
	//// remove bottom half value
	//uint8_t gain_2 = balance_index & 0xf0;
	//// set gain_1 to 2s complement of gain_2
	//uint8_t gain_1 = ~gain_2;

	// determine wave index in wavetable
	uint8_t wave_index = balance_index & 0xf;
	// determine shape -- SAW / SQUARE / TRIANGLE
	uint8_t base_resource_id = shape_ == WAVEFORM_SAW ?
		WAV_RES_BANDLIMITED_SAW_0 :
		(shape_ == WAVEFORM_SQUARE ? WAV_RES_BANDLIMITED_SQUARE_0  : 
		WAV_RES_BANDLIMITED_TRIANGLE_0);

	// grab wave 1 (129 bytes?)
	const prog_uint8_t* wave_1 = waveform_table[base_resource_id + wave_index];
	//// add 1 to wave_index up to kNumZonesFullSampleRate (6)
	//wave_index = U8AddClip(wave_index, 1, kNumZonesFullSampleRate);
	//// grab wave 2 from incremented waveTable
	//const prog_uint8_t* wave_2 = waveform_table[base_resource_id + wave_index];

	BEGIN_SAMPLE_LOOP_DIV  
	if (shape_ == WAVEFORM_SQUARE)// && parameter_)
	{
		while (size--) {
			UPDATE_PHASE_DIV
			// Add dirty PWM for PWM
			if (phase.integral & warp_check)
			{
				*buffer++ = (phase.integral + warp_ >> 8) < 127 + parameter_ ? 0 : 255;
				*buffer2++ = (phase2.integral + warp_ >> 8) < 127 + parameter_ ? 0 : 255;
				*buffer3++ = (phase3.integral + warp_ >> 8) < 127 + parameter_ ? 0 : 255;
				//uint8_t sample2 = InterpolateSample(wave_1, phase2.integral);
				//uint8_t sample3 = InterpolateSample(wave_1, phase3.integral);
				//*buffer2++ = sample2; 
				//*buffer3++ = sample3;
			}
			else
			{
				*buffer++ = (phase.integral - warp_ >> 8) < 127 + parameter_ ? 0 : 255;
				*buffer2++ = (phase2.integral - warp_ >> 8) < 127 + parameter_ ? 0 : 255;
				*buffer3++ = (phase3.integral - warp_ >> 8) < 127 + parameter_ ? 0 : 255;
			}
		}
	}
	else
	{
		uint8_t sample;
		uint8_t sample2;
		uint8_t sample3;
		while (size--) {
			//if (phase.integral & warp_check)
			//{
			//	phase_increment_int.integral -= warp_;
			//	phase_increment_int2.integral -= warp_;
			//	phase_increment_int3.integral -= warp_;
			//}
			//else
			//{
			//	phase_increment_int.integral += warp_;
			//	phase_increment_int2.integral += warp_;
			//	phase_increment_int3.integral += warp_;
			//}
			UPDATE_PHASE_DIV
			//uint8_t sample = InterpolateTwoTables(
			//	wave_1, wave_2,
			//	phase.integral, gain_1, gain_2);
			//uint8_t sample2 = InterpolateTwoTables(
			//	wave_1, wave_2,
			//	phase2.integral, gain_1, gain_2);
			//uint8_t sample3 = InterpolateTwoTables(
			//	wave_1, wave_2,
			//	phase3.integral, gain_1, gain_2);
			//uint8_t sample4 = InterpolateTwoTables(
			//	wave_1, wave_2,
			//	phase4.integral, gain_1, gain_2);
			// #### TODO #### - RANDOMIZE WAVE?

			if (phase.integral & warp_check)
			{
				sample = InterpolateSample(wave_1, phase.integral + warp_);
				sample2 = InterpolateSample(wave_1, phase2.integral + warp_);
				sample3 = InterpolateSample(wave_1, phase3.integral + warp_);
			}
			else
			{
				sample = InterpolateSample(wave_1, phase.integral - warp_);
				sample2 = InterpolateSample(wave_1, phase2.integral - warp_);
				sample3 = InterpolateSample(wave_1, phase3.integral - warp_);
			}
			//uint8_t sample = InterpolateSample(wave_1, phase.integral);
			//uint8_t sample2 = InterpolateSample(wave_1, phase2.integral);
			//uint8_t sample3 = InterpolateSample(wave_1, phase3.integral);

			// To produce pulse width-modulated variants, we shift (saw) or set to
			// a constant (triangle) a portion of the waveform within an increasingly
			// large fraction of the period. Note that this is pure waveshapping - the
			// phase information is not used to determine when/where to shift.
			//
			//     /|            /|          /\             /\
			//    / |           / |         /  \           /  \
			//   /  |    =>  /|/  |        /    \  =>  ___/    \
			//  /   |       /     |/      /      \
			// /    |/                   /        \
			//
			//if (sample < parameter_) {
			//  if (shape_ == WAVEFORM_SAW) {
			//	// Add a discontinuity.
			//	sample += parameter_ >> 1;
			//  } else {
			//	// Clip.
			//	sample = parameter_;
			//  }
			//}

			//if(chopper_ && chopper_check_ > chopper_)
			//{
			//	sample = 255 - sample;
			//	sample2 = 255 - sample2;
			//	sample3 = 255 - sample3;
			//}

			if(parameter_)
			{
				sample += parameter_ >> 1;
				sample2 += parameter_ >> 1;
				sample3 += parameter_ >> 1;
			}
			*buffer++ = sample;
			*buffer2++ = sample2; 
			*buffer3++ = sample3;
		}
	}
	END_SAMPLE_LOOP_DIV
}

// ------- Interpolation between two waveforms from two wavetables -----------
void Oscillator::RenderInterpolatedWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
  uint8_t index = shape_ >= WAVEFORM_WAVETABLE_9 ? 
      shape_ - WAVEFORM_WAVETABLE_9 + 8 :
      shape_ - WAVEFORM_WAVETABLE_1;
  
  // Which wavetable should we play?.
  const prog_uint8_t* wavetable_definition = 
      wav_res_wavetables + U8U8Mul(index, 18);
  // Get a 8:8 value with the wave index in the first byte, and the
  // balance amount in the second byte.
  uint8_t num_steps = ResourcesManager::Lookup<uint8_t, uint8_t>(
      wavetable_definition,
      0);
  uint16_t pointer = U8U8Mul(parameter_ << 1, num_steps);
  uint16_t wave_index_1 = ResourcesManager::Lookup<uint8_t, uint8_t>(
      wavetable_definition,
      1 + (pointer >> 8));
  uint16_t wave_index_2 = ResourcesManager::Lookup<uint8_t, uint8_t>(
      wavetable_definition,
      2 + (pointer >> 8));
  uint8_t gain = pointer & 0xff;
  const prog_uint8_t* wave_1 = wav_res_waves + U8U8Mul(
      wave_index_1,
      129);
  const prog_uint8_t* wave_2 = wav_res_waves + U8U8Mul(
      wave_index_2,
      129);
  BEGIN_SAMPLE_LOOP_DIV
  while (size--) {
    UPDATE_PHASE_DIV
		//if (phase.integral & warp_check_)
		//{
		//	sample = InterpolateSample(wave_1, phase.integral + warp_);
		//	sample2 = InterpolateSample(wave_1, phase2.integral + warp_);
		//	sample3 = InterpolateSample(wave_1, phase3.integral + warp_);
		//}
		//else
		//{
		//	sample = InterpolateSample(wave_1, phase.integral - warp_);
		//	sample2 = InterpolateSample(wave_1, phase2.integral - warp_);
		//	sample3 = InterpolateSample(wave_1, phase3.integral - warp_);
		//}
		*buffer++ = InterpolateTwoTables(wave_1, wave_2,
										phase.integral >> 1, ~gain, gain);
		//*buffer2++ = InterpolateTwoTables(wave_1, wave_2,
					//					phase2.integral >> 1, ~gain, gain);
		//*buffer3++ = InterpolateTwoTables(wave_1, wave_2,
					//					phase3.integral >> 1, ~gain, gain);
		//*buffer++ = InterpolateSample(wave_1, phase.integral >> 1);
		*buffer2++ = InterpolateSample(wave_1, phase2.integral >> 1);
		*buffer3++ = InterpolateSample(wave_1, phase3.integral >> 1);
  }
  END_SAMPLE_LOOP_DIV
}  

//// The position is freely determined by the parameter
//void Oscillator::RenderSweepingWavetableRam(uint8_t* buffer) {
//  uint8_t balance_index = U8Swap4(parameter_);
//  uint8_t wave_index = balance_index & 0xf;
//  uint8_t gain_2 = balance_index & 0xf0;
//  uint8_t gain_1 = ~gain_2;
//  
//  uint16_t offset = wave_index << 7;
//  offset += wave_index;
//  const uint8_t* wave_1 = user_wavetable + offset;
//  const uint8_t* wave_2 = wave_1;
//  if (offset < kUserWavetableSize - 129) {
//    wave_2 += 129;
//  }
//  
//  BEGIN_SAMPLE_LOOP
//    UPDATE_PHASE
//    *buffer++ = U8Mix(
//        InterpolateSampleRam(wave_1, phase.integral >> 1),
//        InterpolateSampleRam(wave_2, phase.integral >> 1),
//        gain_1, gain_2);
//  END_SAMPLE_LOOP
//}

//// ------- Casio CZ-like synthesis -------------------------------------------
//void Oscillator::RenderCzSawHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
//  BEGIN_SAMPLE_LOOP_DIV
//    UPDATE_PHASE_DIV
//    uint8_t phi = phase.integral >> 8;
//    //uint8_t phi2 = phase2.integral >> 8;
//    //uint8_t phi3 = phase3.integral >> 8;
//    uint8_t clipped_phi = phi < 0x20 ? phi << 3 : 0xff;
//    //uint8_t clipped_phi2 = phi2 < 0x20 ? phi2 << 3 : 0xff;
//    //uint8_t clipped_phi3 = phi3 < 0x20 ? phi3 << 3 : 0xff;
//    // Interpolation causes more aliasing here.
//    *buffer++ = ReadSample(wav_res_sine,
//        U8MixU16(phi, clipped_phi, parameter_ << 1));
//    //*buffer2++ = ReadSample(wav_res_sine,
//    //    U8MixU16(phi2, clipped_phi2, parameter_ << 1));
//    //*buffer3++ = ReadSample(wav_res_sine,
//    //    U8MixU16(phi3, clipped_phi3, parameter_ << 1));
//  END_SAMPLE_LOOP_DIV
//}

//void Oscillator::RenderCzPulseResoHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
//  uint16_t increment = (phase_increment_.integral + (
//      (phase_increment_.integral * uint32_t(parameter_)) >> 3)) << 1;
//	  uint16_t increment2 = (phase_increment2_.integral + (
//		  (phase_increment2_.integral * uint32_t(parameter_)) >> 3)) << 1;
//	  uint16_t increment3 = (phase_increment3_.integral + (
//		  (phase_increment3_.integral * uint32_t(parameter_)) >> 3)) << 1;
//  uint16_t phase_2 = data_.secondary_phase;
//  uint16_t phase_2_2 = data_.secondary_phase2;
//  uint16_t phase_2_3 = data_.secondary_phase3;
//  BEGIN_SAMPLE_LOOP_DIV
//    UPDATE_PHASE_DIV
//    if (phase.carry) {
//      phase_2 = 32768;
//		phase_2_2 = 32768;
//		phase_2_3 = 32768;
//    }
//    phase_2 += increment;
//		phase_2_2 += increment2;
//		phase_2_3 += increment3;
//    uint8_t result = ReadSample(wav_res_sine, phase_2);
//		uint8_t result2 = ReadSample(wav_res_sine, phase_2_2);
//		uint8_t result3 = ReadSample(wav_res_sine, phase_2_3);
//    result >>= 1;
//    result += 128;   
//		result2 >>= 1;
//		result2 += 128;   
//		result3 >>= 1;
//		result3 += 128;   
//    if (phase.integral < 0x4000) {
//      *buffer = result;
//    } else if (phase.integral < 0x8000) {
//      *buffer = U8U8MulShift8(result, ~(phase.integral - 0x4000) >> 6);
//    } else {
//      *buffer = 0;
//    }
//		if (phase2.integral < 0x4000) {
//		  *buffer2 = result2;
//		} else if (phase2.integral < 0x8000) {
//		  *buffer2 = U8U8MulShift8(result2, ~(phase2.integral - 0x4000) >> 6);
//		} else {
//		  *buffer2 = 0;
//		}
//		if (phase3.integral < 0x4000) {
//		  *buffer3 = result3;
//		} else if (phase3.integral < 0x8000) {
//		  *buffer3 = U8U8MulShift8(result3, ~(phase3.integral - 0x4000) >> 6);
//		} else {
//		  *buffer3 = 0;
//		}
//    ++buffer;
//    ++buffer2;
//    ++buffer3;
//  END_SAMPLE_LOOP_DIV
//  data_.secondary_phase = phase_2;
//  data_.secondary_phase2 = phase_2_2;
//  data_.secondary_phase3 = phase_2_3;
//}

//void Oscillator::RenderCzResoHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
//  uint16_t increment = phase_increment_.integral + (
//      (phase_increment_.integral * uint32_t(parameter_)) >> 3);
//	  uint16_t increment2 = phase_increment2_.integral + (
//		  (phase_increment2_.integral * uint32_t(parameter_)) >> 3);
//	  uint16_t increment3 = phase_increment3_.integral + (
//		  (phase_increment3_.integral * uint32_t(parameter_)) >> 3);
//  uint16_t phase_2 = data_.secondary_phase;
//	  uint16_t phase_2_2 = data_.secondary_phase2;
//	  uint16_t phase_2_3 = data_.secondary_phase3;
//  BEGIN_SAMPLE_LOOP_DIV
//    UPDATE_PHASE_DIV
//    if (phase.carry) {
//      phase_2 = 0;
//    }
//		if (phase2.carry) {
//		  phase_2_2 = 0;
//		}
//		if (phase3.carry) {
//		  phase_2_3 = 0;
//		}
//    phase_2 += increment;
//		phase_2_2 += increment;
//		phase_2_3 += increment;
//    uint8_t carrier = InterpolateSample(wav_res_sine, phase_2);
//		uint8_t carrier2 = InterpolateSample(wav_res_sine, phase_2_2);
//		uint8_t carrier3 = InterpolateSample(wav_res_sine, phase_2_3);
//    if (shape_ == WAVEFORM_CZ_SYNC) {
//      *buffer++ = phase.integral < 0x8000 ? carrier : 128;
//      *buffer2++ = phase2.integral < 0x8000 ? carrier2 : 128;
//      *buffer3++ = phase3.integral < 0x8000 ? carrier3 : 128;
//    } else {
//      uint8_t window = 0;
//      uint8_t window2 = 0;
//      uint8_t window3 = 0;
//      if (shape_ == WAVEFORM_CZ_RESO) {
//        window = ~(phase.integral >> 8);
//        window2 = ~(phase2.integral >> 8);
//        window3 = ~(phase3.integral >> 8);
//      } else {
//        window = (phase.integral & 0x8000) ?
//              ~static_cast<uint8_t>(phase.integral >> 7) :
//              phase.integral >> 7;
//        window2 = (phase2.integral & 0x8000) ?
//              ~static_cast<uint8_t>(phase2.integral >> 7) :
//              phase2.integral >> 7;
//        window3 = (phase3.integral & 0x8000) ?
//              ~static_cast<uint8_t>(phase3.integral >> 7) :
//              phase3.integral >> 7;
//      }
//      *buffer++ = U8U8MulShift8(carrier, window);
//      *buffer2++ = U8U8MulShift8(carrier2, window2);
//      *buffer3++ = U8U8MulShift8(carrier3, window3);
//    }
//  END_SAMPLE_LOOP_DIV
//  data_.secondary_phase = phase_2;
//  data_.secondary_phase2 = phase_2_2;
//  data_.secondary_phase3 = phase_2_3;
//}

//// ------- FM ----------------------------------------------------------------
//void Oscillator::RenderFmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
//  uint8_t offset = secondary_parameter_;
//  if (offset < 12) {
//    offset = 0;
//  } else if (offset > 36) {
//    offset = 24;
//  } else {
//    offset = offset - 12;
//  }
//  uint16_t multiplier = ResourcesManager::Lookup<uint16_t, uint8_t>(
//      lut_res_fm_frequency_ratios, offset);
//  uint16_t increment = (
//      static_cast<int32_t>(phase_increment_.integral) * multiplier) >> 8;
//  parameter_ <<= 1;
//  
//  // The modulator will have a 16 bits phase increment, so we need to drop
//  // the fractional part to 0 to ensure that the modulator frequency is
//  // the correct multiple of the carrier frequency.
//  phase_.fractional = 0;
//  uint16_t phase_2 = data_.secondary_phase;
//  BEGIN_SAMPLE_LOOP_DIV
//    UPDATE_PHASE_DIV
//    phase_2 += increment;
//    uint8_t modulator = InterpolateSample(wav_res_sine,
//        phase_2);
//    uint16_t modulation = modulator * parameter_;
//    *buffer++ = InterpolateSample(wav_res_sine,
//        phase.integral + modulation);
//  END_SAMPLE_LOOP_DIV
//  data_.secondary_phase = phase_2;
//}

 //------- 8-bit land --------------------------------------------------------
void Oscillator::Render8BitLandHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
  BEGIN_SAMPLE_LOOP_DIV
  while (size--) {
    UPDATE_PHASE_DIV
    uint8_t x = parameter_;
	if (phase.integral & warp_check)
	{
		*buffer++ = (((phase.integral + warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
		*buffer2++ = (((phase2.integral + warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
		*buffer3++ = (((phase3.integral + warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
	}
	else
	{
		*buffer++ = (((phase.integral - warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
		*buffer2++ = (((phase2.integral - warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
		*buffer3++ = (((phase3.integral - warp_ >> 8) ^ (x << 1)) & (~x)) + (x >> 1);
	}
  }
  END_SAMPLE_LOOP_DIV
}

// ------- 8-bit land --------------------------------------------------------
void Oscillator::RenderCrushedSineHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
  uint8_t decimate = data_.cr.decimate;
  uint8_t held_sample = data_.cr.state;
  //// ### ADDED
  uint8_t held_sample2 = data_.cr.state;
  uint8_t held_sample3 = data_.cr.state;

  // FIX to make it work with 'warp'
  // Half the assignments
  if(!parameter_)
  {
	  parameter_ = 1;
  }
  else if(!(~parameter_ & 127))
  {
	  parameter_ = 126;
  }

  BEGIN_SAMPLE_LOOP_DIV
  while (size--) {
    UPDATE_PHASE_DIV
    ++decimate;
    if (parameter_ <= 63) {
		if (phase.integral & warp_check)
		{
			if (decimate >= parameter_ + 1) {
				decimate = 0;
				held_sample = InterpolateSample(wav_res_sine, phase.integral + warp_);
				held_sample2 = InterpolateSample(wav_res_sine, phase3.integral + warp_);
				held_sample3 = InterpolateSample(wav_res_sine, phase3.integral + warp_);
			}
		}
		else
		{
			if (decimate >= parameter_ + 1) {
				decimate = 0;
				held_sample = InterpolateSample(wav_res_sine, phase.integral - warp_);
				held_sample2 = InterpolateSample(wav_res_sine, phase3.integral - warp_);
				held_sample3 = InterpolateSample(wav_res_sine, phase3.integral - warp_);
			}
		}
    } else {
		if (phase.integral & warp_check)
		{
			if (decimate >= 128 - parameter_) {
				decimate = 0;
				held_sample = InterpolateSample(wav_res_bandlimited_triangle_0, phase.integral + warp_);
				held_sample2 = InterpolateSample(wav_res_bandlimited_triangle_0, phase3.integral + warp_);
				held_sample3 = InterpolateSample(wav_res_bandlimited_triangle_0, phase3.integral + warp_);
			}
		}
		else
		{
			if (decimate >= 128 - parameter_) {
				decimate = 0;
				held_sample = InterpolateSample(wav_res_bandlimited_triangle_0, phase.integral - warp_);
				held_sample2 = InterpolateSample(wav_res_bandlimited_triangle_0, phase3.integral - warp_);
				held_sample3 = InterpolateSample(wav_res_bandlimited_triangle_0, phase3.integral - warp_);
			}
		}
    }
    *buffer++ = held_sample;
    *buffer2++ = held_sample2;
    *buffer3++ = held_sample3;
  }
  END_SAMPLE_LOOP_DIV
  data_.cr.decimate = decimate;
  data_.cr.state = held_sample;
}

//void Oscillator::RenderVowel(uint8_t* buffer) {
//  data_.vw.update = (data_.vw.update + 1) & 3;
//  if (!data_.vw.update) {
//    uint8_t offset_1 = U8ShiftRight4(parameter_);
//    offset_1 = U8U8Mul(offset_1, 7);
//    uint8_t offset_2 = offset_1 + 7;
//    uint8_t balance = parameter_ & 15;
//    
//    // Interpolate formant frequencies.
//    for (uint8_t i = 0; i < 3; ++i) {
//      data_.vw.formant_increment[i] = U8U4MixU12(
//          ResourcesManager::Lookup<uint8_t, uint8_t>(
//              wav_res_vowel_data, offset_1 + i),
//          ResourcesManager::Lookup<uint8_t, uint8_t>(
//              wav_res_vowel_data, offset_2 + i),
//          balance);
//      data_.vw.formant_increment[i] <<= 3;
//    }
//    
//    // Interpolate formant amplitudes.
//    for (uint8_t i = 0; i < 4; ++i) {
//      uint8_t amplitude_a = ResourcesManager::Lookup<uint8_t, uint8_t>(
//          wav_res_vowel_data,
//          offset_1 + 3 + i);
//      uint8_t amplitude_b = ResourcesManager::Lookup<uint8_t, uint8_t>(
//          wav_res_vowel_data,
//          offset_2 + 3 + i);
//      data_.vw.formant_amplitude[i] = U8U4MixU8(
//          amplitude_a,
//          amplitude_b, balance);
//    }
//  }
//  BEGIN_SAMPLE_LOOP
//    int8_t result = 0;
//    for (uint8_t i = 0; i < 3; ++i) {
//      data_.vw.formant_phase[i] += data_.vw.formant_increment[i];
//      result += ResourcesManager::Lookup<uint8_t, uint8_t>(
//          i == 2 ? wav_res_formant_square : wav_res_formant_sine,
//          ((data_.vw.formant_phase[i] >> 8) & 0xf0) |
//            data_.vw.formant_amplitude[i]);
//    }
//    result = S8U8MulShift8(result, ~(phase.integral >> 8));
//    phase.integral += phase_increment_.integral;
//    int16_t phase_noise = int8_t(Random::state_msb()) *
//        int8_t(data_.vw.noise_modulation);
//    if ((phase.integral + phase_noise) < phase_increment_.integral) {
//      data_.vw.formant_phase[0] = 0;
//      data_.vw.formant_phase[1] = 0;
//      data_.vw.formant_phase[2] = 0;
//    }
//    uint8_t x = S16ClipS8(4 * result) + 128;
//    *buffer++ = x;
//    *buffer++ = x;
//    size--;
//  END_SAMPLE_LOOP
//}
//

//// ------- Dirty Pwm (kills kittens) -----------------------------------------
//void Oscillator::RenderDirtyPwmHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4) {
//  BEGIN_SAMPLE_LOOP_DIV
//  while (size--) {
//    UPDATE_PHASE_DIV
//    *buffer++ = (phase.integral >> 8) < 127 + parameter_ ? 0 : 255;
//    *buffer2++ = (phase2.integral >> 8) < 127? 0 : 255;
//    *buffer3++ = (phase3.integral >> 8) < 127? 0 : 255;
//  }
//  END_SAMPLE_LOOP_DIV
//}

//// ------- Quad saw (mit aliasing) -------------------------------------------
//void Oscillator::RenderQuadSawPad(uint8_t* buffer) {
//  uint16_t phase_spread = (
//      static_cast<uint32_t>(phase_increment_.integral) * parameter_) >> 13;
//  ++phase_spread;
//  uint16_t phase_increment = phase_increment_.integral;
//  uint16_t increments[3];
//  for (uint8_t i = 0; i < 3; ++i) {
//    phase_increment += phase_spread;
//    increments[i] = phase_increment;
//  }
//  
//  BEGIN_SAMPLE_LOOP
//    UPDATE_PHASE
//    data_.qs.phase[0] += increments[0];
//    data_.qs.phase[1] += increments[1];
//    data_.qs.phase[2] += increments[2];
//    uint8_t value = (phase.integral >> 10);
//    value += (data_.qs.phase[0] >> 10);
//    value += (data_.qs.phase[1] >> 10);
//    value += (data_.qs.phase[2] >> 10);
//    *buffer++ = value;
//  END_SAMPLE_LOOP
//}

//// ------- Low-passed, then high-passed white noise --------------------------
//void Oscillator::RenderFilteredNoise(uint8_t* buffer) {
//  uint16_t rng_state = data_.no.rng_state;
//  if (rng_state == 0) {
//    ++rng_state;
//  }
//  uint8_t filter_coefficient = parameter_ << 2;
//  if (filter_coefficient <= 4) {
//    filter_coefficient = 4;
//  }
//  BEGIN_SAMPLE_LOOP
//    if (*sync_input_++) {
//      rng_state = data_.no.rng_reset_value;
//    }
//    rng_state = (rng_state >> 1) ^ (-(rng_state & 1) & 0xb400);
//    uint8_t noise_sample = rng_state >> 8;
//    // This trick is used to avoid having a DC component (no innovation) when
//    // the parameter is set to its minimal or maximal value.
//    data_.no.lp_noise_sample = U8Mix(
//        data_.no.lp_noise_sample,
//        noise_sample,
//        filter_coefficient);
//    if (parameter_ >= 64) {
//      *buffer++ = noise_sample - data_.no.lp_noise_sample - 128;
//    } else {
//      *buffer++ = data_.no.lp_noise_sample;
//    }
//  END_SAMPLE_LOOP
//  data_.no.rng_state = rng_state;
//}

}  // namespace shruthi

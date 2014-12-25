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

// ###### ADDED ######
void Oscillator::RenderSimpleWavetableHMC(uint8_t* buffer, uint8_t* buffer2, uint8_t* buffer3, uint8_t* buffer4, bool pulse_width){
	// swap byte halves
	uint8_t balance_index = U8Swap4(note_ - 12);
	//// remove bottom half value
	//uint8_t gain_2 = balance_index & 0xf0;
	//// set gain_1 to 2s complement of gain_2
	//uint8_t gain_1 = ~gain_2;

	// determine wave index in wavetable
	uint8_t wave_index = balance_index & 0xf;
	// determine shape -- SAW / SQUARE / TRIANGLE
	uint8_t base_resource_id = (shape_ == WAVEFORM_SAW || shape_ == WAVEFORM_SAW2) ?
		WAV_RES_BANDLIMITED_SAW_0 :
		((shape_ == WAVEFORM_SQUARE || shape_ == WAVEFORM_SQUARE2) ? 
		WAV_RES_BANDLIMITED_SQUARE_0  :  
		((shape_ == WAVEFORM_TRIANGLE || shape_ == WAVEFORM_TRIANGLE2) ? 
		WAV_RES_BANDLIMITED_TRIANGLE_0 :
		WAV_RES_SINE
		));

	// grab wave 1 (129 bytes?)
	const prog_uint8_t* wave_1;
	if(base_resource_id != WAV_RES_SINE)
	{
		wave_1 = waveform_table[base_resource_id + wave_index];
	}
	else
	{
		wave_1 = waveform_table[base_resource_id];
	}

	BEGIN_SAMPLE_LOOP_DIV  
	if (pulse_width)
	{
		// the pulse width phase shift amount
		uint16_t parameter_phase = parameter_ << 9;
		// the location of the shift end
		uint16_t stretch_position = 16384 + parameter_phase;//~(~parameter_phase >> 1);
		while (size--) {
			UPDATE_PHASE_DIV
			// Only update Pulse Width every 2 samples
			// ROOT
			if (phase.integral < parameter_phase)	// Stretch Part
			{
				*buffer++ = InterpolateSample(wave_1, 0);
			}
			else if (phase.integral < stretch_position)		// Shifted Part
			{
				*buffer++ = InterpolateSample(wave_1, phase.integral - parameter_phase);
			}
			else	// Final bits of square
			{
				*buffer++ = InterpolateSample(wave_1, phase.integral);
			}
			//// DIV 1
			//if (phase2.integral < parameter_phase)	// Stretch Part
			//{
			//	*buffer2++ = InterpolateSample(wave_1, 0);
			//}
			//else if (phase2.integral < stretch_position)		// Shifted Part
			//{
			//	*buffer2++ = InterpolateSample(wave_1, phase2.integral - parameter_phase);
			//}
			//else	// Final bits of square
			//{
				*buffer2++ = InterpolateSample(wave_1, phase2.integral);
			//}
			//// DIV 2
			//if (phase3.integral < parameter_phase)	// Stretch Part
			//{
			//	*buffer3++ = InterpolateSample(wave_1, 0);
			//}
			//else if (phase3.integral < stretch_position)		// Shifted Part
			//{
			//	*buffer3++ = InterpolateSample(wave_1, phase3.integral - parameter_phase);
			//}
			//else	// Final bits of square
			//{
				*buffer3++ = InterpolateSample(wave_1, phase3.integral);
			//}
		}
	}
	else   // Oscillators with very simple Pulse Phase Modulation
	{
		int16_t warp_add;
		warp_ = parameter_ << 9;
		while (size--) {
			UPDATE_PHASE_DIV
			// warp update
			if (phase.integral & warp_check)
			{
				warp_add = warp_;
			}
			else
			{
				warp_add = -warp_;
			}
			// sample update
			*buffer++ = InterpolateSample(wave_1, phase.integral + warp_add);
			*buffer2++ = InterpolateSample(wave_1, phase2.integral + warp_add);
			*buffer3++ = InterpolateSample(wave_1, phase3.integral + warp_add);
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
  uint16_t wave_index_3 = ResourcesManager::Lookup<uint8_t, uint8_t>(
      wavetable_definition,
      1);
  uint8_t gain = pointer & 0xff;
  const prog_uint8_t* wave_1 = wav_res_waves + U8U8Mul(
      wave_index_1,
      129);
  const prog_uint8_t* wave_2 = wav_res_waves + U8U8Mul(
      wave_index_2,
      129);
  const prog_uint8_t* wave_3 = wav_res_waves + U8U8Mul(
      wave_index_3,
      129);
  BEGIN_SAMPLE_LOOP_DIV
  while (size--) {
    UPDATE_PHASE_DIV
		*buffer++ = InterpolateTwoTables(wave_1, wave_2,
										phase.integral >> 1, ~gain, gain);
		//*buffer2++ = InterpolateTwoTables(wave_1, wave_2,
		//								phase2.integral >> 1, ~gain, gain);
		//*buffer3++ = InterpolateTwoTables(wave_1, wave_2,
					//					phase3.integral >> 1, ~gain, gain);
		//*buffer++ = InterpolateSample(wave_3, phase.integral >> 1);
		*buffer2++ = InterpolateSample(wave_3, phase2.integral >> 1);
		*buffer3++ = InterpolateSample(wave_3, phase3.integral >> 1);
  }
  END_SAMPLE_LOOP_DIV
}  

}  // namespace shruthi

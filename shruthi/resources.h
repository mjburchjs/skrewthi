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
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef SHRUTHI_RESOURCES_H_
#define SHRUTHI_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace shruthi {

typedef uint16_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table32_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint8_t* const character_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_env_portamento_increments[] PROGMEM;
extern const prog_uint16_t lut_res_oscillator_increments[] PROGMEM;
extern const prog_uint16_t lut_res_fm_frequency_ratios[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_palas_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint32_t lut_res_tempo_phase_increment[] PROGMEM;
extern const prog_uint8_t wav_res_formant_sine[] PROGMEM;
extern const prog_uint8_t wav_res_formant_square[] PROGMEM;
extern const prog_uint8_t wav_res_sine[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_square_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_5[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_triangle_5[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_env_expo[] PROGMEM;
extern const prog_uint8_t wav_res_ssm2164_linearization[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
extern const prog_uint8_t wav_res_version[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
#define STR_RES_SHAPE 0  // shape
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RESONANCE 2  // resonance
#define STR_RES_PRM 3  // prm
#define STR_RES_RANGE 4  // range
#define STR_RES_RNG 5  // rng
#define STR_RES_OP_ 6  // op.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_DETUNE 8  // detune
#define STR_RES_OSC_MIX 9  // osc mix
#define STR_RES_SUB_OSC_ 10  // sub osc.
#define STR_RES_ENV1TVCF 11  // env1~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_ATTACK 13  // attack
#define STR_RES_ATK 14  // atk
#define STR_RES_DECAY 15  // decay
#define STR_RES_SUSTAIN 16  // sustain
#define STR_RES_RELEASE 17  // release
#define STR_RES_RATE 18  // rate
#define STR_RES_MODULATION 19  // modulation
#define STR_RES_OPERATORS 20  // operators
#define STR_RES_MOD_ 21  // mod.
#define STR_RES_SOURCE 22  // source
#define STR_RES_SRC 23  // src
#define STR_RES_DEST_ 24  // dest.
#define STR_RES_DST 25  // dst
#define STR_RES_AMOUNT 26  // amount
#define STR_RES_AMT 27  // amt
#define STR_RES_MODE 28  // mode
#define STR_RES_OVERDRIVE 29  // overdrive
#define STR_RES__FM 30  // fm
#define STR_RES_FLAVOUR 31  // flavour
#define STR_RES_TIME 32  // time
#define STR_RES_LEVEL 33  // level
#define STR_RES_FDB 34  // fdb
#define STR_RES_FEEDBACK 35  // feedback
#define STR_RES_EQ_ 36  // eq.
#define STR_RES_FDBCK_EQ_ 37  // fdbck eq.
#define STR_RES_TEMPO 38  // tempo
#define STR_RES_BPM 39  // bpm
#define STR_RES_GROOVE 40  // groove
#define STR_RES_DIRECTION 41  // direction
#define STR_RES_PATTERN 42  // pattern
#define STR_RES_DIVISION 43  // division
#define STR_RES_START 44  // start
#define STR_RES_LENGTH 45  // length
#define STR_RES_OCTAVE 46  // octave
#define STR_RES_RAGA 47  // raga
#define STR_RES_PORTA 48  // porta
#define STR_RES_PRT 49  // prt
#define STR_RES_LEGATO 50  // legato
#define STR_RES_TUNING 51  // tuning
#define STR_RES_MIDI_CHAN 52  // midi chan
#define STR_RES_CHN 53  // chn
#define STR_RES_MIDI_OUT 54  // midi out
#define STR_RES_PAUSE 55  // pause
#define STR_RES_STARTPAGE 56  // startpage
#define STR_RES_SNAP 57  // snap
#define STR_RES_OSCILLATOR_1 58  // oscillator 1
#define STR_RES_OSCILLATOR_2 59  // oscillator 2
#define STR_RES_MIXER 60  // mixer
#define STR_RES_FILTER 61  // filter
#define STR_RES_FILTERS 62  // filter+
#define STR_RES_MODE_1 63  // mode 1
#define STR_RES_MODE_2 64  // mode 2
#define STR_RES_MD1 65  // md1
#define STR_RES_MD2 66  // md2
#define STR_RES_ENVELOPE_1 67  // envelope 1
#define STR_RES_ENVELOPE_2 68  // envelope 2
#define STR_RES_SEQUENCER 69  // sequencer
#define STR_RES_ARPEGGIO 70  // arpeggio
#define STR_RES_CH1 71  // ch1
#define STR_RES_CH2 72  // ch2
#define STR_RES_11 73  // 1
#define STR_RES_12 74  // 2
#define STR_RES_STEP_SEQUENCER 75  // step sequencer
#define STR_RES_KEYBOARD 76  // keyboard
#define STR_RES_MIDI 77  // midi
#define STR_RES_SYSTEM 78  // system
#define STR_RES_PERFORMANCE 79  // performance
#define STR_RES_PARAM__1 80  // param. 1
#define STR_RES_PARAM__2 81  // param. 2
#define STR_RES_PR1 82  // pr1
#define STR_RES_PR2 83  // pr2
#define STR_RES_FX_ 84  // fx.
#define STR_RES_FX_PROG_ 85  // fx prog.
#define STR_RES_LPF 86  // lpf
#define STR_RES_BPF 87  // bpf
#define STR_RES_HPF 88  // hpf
#define STR_RES_LPL 89  // lp<
#define STR_RES_BPL 90  // bp<
#define STR_RES_HPL 91  // hp<
#define STR_RES_SLP 92  // +lp
#define STR_RES_SBP 93  // +bp
#define STR_RES_SHP 94  // +hp
#define STR_RES_GLP 95  // >lp
#define STR_RES_GBP 96  // >bp
#define STR_RES_GHP 97  // >hp
#define STR_RES_LP4 98  // lp4
#define STR_RES_LP3 99  // lp3
#define STR_RES_LP2 100  // lp2
#define STR_RES_LP1 101  // lp1
#define STR_RES_HP1 102  // hp1
#define STR_RES_HP2 103  // hp2
#define STR_RES_HP3 104  // hp3
#define STR_RES_BP2 105  // bp2
#define STR_RES_BP4 106  // bp4
#define STR_RES_NOTCH 107  // notch
#define STR_RES_PHASER 108  // phaser
#define STR_RES_H2LP 109  // h2lp
#define STR_RES_H3LP 110  // h3lp
#define STR_RES_NSLP 111  // n+lp
#define STR_RES_PSLP 112  // p+lp
#define STR_RES_LP 113  // lp
#define STR_RES_BP 114  // bp
#define STR_RES_HP 115  // hp
#define STR_RES_AP 116  // ap
#define STR_RES_LIQUID 117  // liquid
#define STR_RES_MS 118  // ms
#define STR_RES_WOBBLY 119  // wobbly
#define STR_RES_WHACKY 120  // whacky
#define STR_RES_PW1 121  // pw1					// START SHORT DESTINATIONS
//#define STR_RES_PW2 122  // pw2
#define STR_RES_51 122  // 1
//#define STR_RES_52 124  // 2
//#define STR_RES_5 125  // 
#define STR_RES_5F 123  // f
#define STR_RES_MIX 124  // mix
//#define STR_RES_NOI 128  // noi
//#define STR_RES_SUB 129  // sub

// ### ADDED ###
#define STR_RES_RT_VOL 125
#define STR_RES_D1_VOL 126
#define STR_RES_D2_VOL 127
#define STR_RES_OD_TYPE 128
#define STR_RES_SHF_AMT 129
#define STR_RES_SH_FINE 130
#define STR_RES_WRP_DEST 131
#define STR_RES_DIVS 132

#define STR_RES_CUT 133  // cut
#define STR_RES_RES 134  // res
#define STR_RES_VCA 135  // vca
#define STR_RES_CV1 136  // cv1
#define STR_RES_CV2 137  // cv2
#define STR_RES_TR1 138  // tr1
#define STR_RES_A1 139  // a1
#define STR_RES_D1 140  // d1
#define STR_RES_S1 141  // s1
#define STR_RES_R1 142  // r1
#define STR_RES_TR2 143  // tr2
#define STR_RES_A2 144  // a2
#define STR_RES_D2 145  // d2
#define STR_RES_S2 146  // s2
#define STR_RES_R2 147  // r2
#define STR_RES__ATK 148  // atk
#define STR_RES__LF1 149  // lf1
#define STR_RES__LF2 150  // lf2
#define STR_RES_IN1 151  // in1
#define STR_RES_IN2 152  // in2
#define STR_RES_OUT 153  // out
#define STR_RES___OFF 154  // off
#define STR_RES_ADD 155  // add
#define STR_RES_PRD 156  // prd
#define STR_RES_MAX 157  // max
#define STR_RES_MIN 158  // min
#define STR_RES__XOR 159  // xor
#define STR_RES_GE 160  // >=
#define STR_RES_LE 161  // <=
#define STR_RES_QTZ 162  // qtz
#define STR_RES_LAG 163  // lag
#define STR_RES_PWM1 164  // pwm1					// START MOD DEST LIST
#define STR_RES_OSC1 165  // osc1
#define STR_RES_FINE 166  // fine
#define STR_RES__MIX 167  // fuzz
//#define STR_RES_PWM2 162  // pwm2
//#define STR_RES_OSC2 164  // osc2
//#define STR_RES_OSC1S2 165  // osc1+2
//#define STR_RES_NOISE 168  // noise
//#define STR_RES_SUBOSC 169  // subosc
// ### ADDED ###
#define STR_RES_ROOT_VOL 168
#define STR_RES_DIV1_VOL 169
#define STR_RES_DIV2_VOL 170
#define STR_RES_DIV3_VOL 171
#define STR_RES_SHIFT_AMT 172
#define STR_RES_SHIFT_FINE 173
#define STR_RES_WARP 174
#define STR_RES_DIVISIONS 175

#define STR_RES_CUTOFF 176  // cutoff
#define STR_RES_RESO 177  // reso
#define STR_RES__VCA 178  // vca
#define STR_RES_CV_1 179  // cv 1
#define STR_RES_CV_2 180  // cv 2
#define STR_RES_TRG_E1 181  // trg e1
#define STR_RES_ATK__1 182  // atk. 1
#define STR_RES_DEC__1 183  // dec. 1
#define STR_RES_SUS__1 184  // sus. 1
#define STR_RES_REL__1 185  // rel. 1
#define STR_RES_TRG_E2 186  // trg e2
#define STR_RES_ATK__2 187  // atk. 2
#define STR_RES_DEC__2 188  // dec. 2
#define STR_RES_SUS__2 189  // sus. 2
#define STR_RES_REL__2 190  // rel. 2
#define STR_RES_ATK1S2 191  // atk1+2
#define STR_RES__LFO_1 192  // lfo 1
#define STR_RES__LFO_2 193  // lfo 2
#define STR_RES_DISTRT 194  // distrt
#define STR_RES_CRUSHR 195  // crushr
#define STR_RES_SCMBFL 196  // +cmbfl
#define STR_RES_CMBFL 197 // -cmbfl
#define STR_RES_RINGMD 198  // ringmd
#define STR_RES_DELAY 199  // delay
#define STR_RES_FB_DLY 200  // fb dly
#define STR_RES_DUBDLY 201  // dubdly
#define STR_RES__FBDLY 202  // !fbdly
#define STR_RES__DBDLY 203  // !dbdly
#define STR_RES__16_DL 204  // /16 dl
#define STR_RES__12_DL 205  // /12 dl
#define STR_RES__8_DLY 206  // /8 dly
#define STR_RES_3_16DL 207  // 3/16dl
#define STR_RES_LOOPER 208  // looper
#define STR_RES_PITCH 209  // pitch
#define STR_RES_LGF 210  // l>f
#define STR_RES_HGF 211  // h>f
#define STR_RES_FGL 212  // f>l
#define STR_RES_FGH 213  // f>h
#define STR_RES_GFX 214  // >fx
#define STR_RES_LF1 215  // lf1
#define STR_RES_LF2 216  // lf2
#define STR_RES_SEQ 217  // seq
#define STR_RES__SQ1 218  // sq1
#define STR_RES__SQ2 219  // sq2
#define STR_RES_ARP 220  // arp
#define STR_RES_WHL 221  // whl
#define STR_RES_AFT 222  // aft
#define STR_RES_BND 223  // bnd
#define STR_RES_OFS 224  // ofs
#define STR_RES__CV1 225  // cv1
#define STR_RES__CV2 226  // cv2
#define STR_RES_CV3 227  // cv3
#define STR_RES_CV4 228  // cv4
#define STR_RES_CCA 229  // ccA
#define STR_RES_CCB 230  // ccB
#define STR_RES_BRE 231  // bre
#define STR_RES_PED 232  // ped
#define STR_RES__NOI 233  // noi
#define STR_RES_EN1 234  // en1
#define STR_RES_EN2 235  // en2
#define STR_RES_VEL 236  // vel
#define STR_RES_RND 237  // rnd
#define STR_RES_NOT 238  // not
#define STR_RES_GAT 239  // gat
#define STR_RES_AUD 240  // aud
#define STR_RES_OP1 241  // op1
#define STR_RES_OP2 242  // op2
#define STR_RES_E4 243  // =4
#define STR_RES_E8 244  // =8
#define STR_RES_E16 245  // =16
#define STR_RES_E32 246  // =32
#define STR_RES_LFO_1 247  // lfo 1
#define STR_RES_LFO_2 248  // lfo 2
#define STR_RES_STPSEQ 249  // stpseq
#define STR_RES_STPSQ1 250  // stpsq1
#define STR_RES_STPSQ2 251  // stpsq2
#define STR_RES__ARP 252  // arp
#define STR_RES_MWHEEL 253  // mwheel
#define STR_RES_AFTTCH 254  // afttch
#define STR_RES_BENDER 255  // bender
#define STR_RES_OFFSET 256  // offset
#define STR_RES__CV_1 257  // cv 1
#define STR_RES__CV_2 258  // cv 2
#define STR_RES_CV_3 259  // cv 3
#define STR_RES_CV_4 260  // cv 4
#define STR_RES_CC_A 261  // cc A
#define STR_RES_CC_B 262  // cc B
#define STR_RES_BREATH 263  // breath
#define STR_RES_PEDAL 264  // pedal
#define STR_RES__NOISE 265  // noise
#define STR_RES_ENV_1 266  // env 1
#define STR_RES_ENV_2 267  // env 2
#define STR_RES_VELO 268 // velo
#define STR_RES_RANDOM 269  // random
#define STR_RES_NOTE 270  // note
#define STR_RES_GATE 271  // gate
#define STR_RES_AUDIO 272  // audio
#define STR_RES_OP__1 273  // op. 1
#define STR_RES_OP__2 274  // op. 2
#define STR_RES_E_4 275  // = 4
#define STR_RES_E_8 276  // = 8
#define STR_RES_E_16 277  // = 16
#define STR_RES_E_32 278  // = 32
#define STR_RES_PATCH 279  // patch
#define STR_RES_SEQUENCE 280  // sequence
#define STR_RES_SAVE_MIDI_KBD 281  // save midi/kbd
#define STR_RES_SETTINGS_ 282  // settings?
#define STR_RES_START_FULL_MIDI 283  // start full midi
#define STR_RES_BACKUP_ 284  // backup?
#define STR_RES_BROWSE 285  // browse
#define STR_RES_SAVE 286  // save
#define STR_RES_COMPARE 287  // compare
#define STR_RES_ 288  // ----
#define STR_RES_V 289  // v
#define STR_RES_MUTABLE____V1_02 290  // mutable    v1.02
#define STR_RES_INSTRUMENTS_671 291  // instruments -1
#define STR_RES_SHRUTHI_CLASSIC 292  // shruthi classic
#define STR_RES_4_KNOBS 293  // (4 knobs)
#define STR_RES_SHRUTHI_XT 294  // shruthi xt
#define STR_RES_CLASSIC_FCD72 295  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 296  // shruthi xt
#define STR_RES_FULL_CONTROL 297  // (full control)
#define STR_RES_LETS_JAM_ 298  // let's jam!
#define STR_RES_EXTERN 299  // extern
#define STR_RES_SUM 300  // sum
#define STR_RES_SYNC 301  // sync
#define STR_RES_RING 302  // ring
#define STR_RES_XOR 303 // xor
#define STR_RES_FUZZ 304  // fuzz
#define STR_RES_GG4 305  // >>4	
#define STR_RES_GG8 306  // >>8
#define STR_RES_FOLD 307  // fold
#define STR_RES_BITS 308  // bits
#define STR_RES_DUO 309  // duo
#define STR_RES_2STEPS 310  // 2steps
#define STR_RES_4STEPS 311  // 4steps
#define STR_RES_8STEPS 312  // 8steps
#define STR_RES_DIST_TYPE 313  // disttype
#define STR_RES_STP 314  // stp
#define STR_RES___ARP 315  // arp
#define STR_RES__SEQ 316  // seq
#define STR_RES_FREE 317  // free
#define STR_RES_SLAVE 318  // slave
#define STR_RES_MASTER 319  // master
#define STR_RES_1SHOT 320  // 1shot
#define STR_RES_1_1 321  // 1/1
#define STR_RES_1_2 322  // 1/2
#define STR_RES_1_3 323  // 1/3
#define STR_RES_1_4 324  // 1/4
#define STR_RES_1_6 325  // 1/6
#define STR_RES_1_8 326  // 1/8
#define STR_RES__12 327  // /12
#define STR_RES__16 328  // /16
#define STR_RES__24 329  // /24
#define STR_RES__32 330  // /32
#define STR_RES__48 331  // /48
#define STR_RES__96 332  // /96
#define STR_RES_SWING 333  // swing
#define STR_RES_SHUFFLE 334  // shuffle
#define STR_RES_PUSH 335  // push
#define STR_RES__LAG 336  // lag
#define STR_RES_HUMAN 337  // human
#define STR_RES_MONKEY 338  // monkey
#define STR_RES__OFF 339  // off
#define STR_RES_THRU 340  // thru
#define STR_RES___SEQ 341  // seq
#define STR_RES_CTRL 342  // ctrl
#define STR_RES_FULL 343  // full
#define STR_RES_1TV 344  // 1~|
#define STR_RES_2T1 345  // 2~1
#define STR_RES_3T2 346  // 3~2
#define STR_RES_4T3 347  // 4~3
#define STR_RES_5T4 348  // 5~4
#define STR_RES_6T5 349  // 6~5
#define STR_RES_7T6 350  // 7~6
#define STR_RES_8T7 351  // 8~7
#define STR_RES_TRI 352  // tri
#define STR_RES_SQR 353  // sqr
#define STR_RES_S_H 354  // s&h
#define STR_RES_RAMP 355  // ramp
#define STR_RES_STEP 356  // step
#define STR_RES_3 357  // 
#define STR_RES_4 358  // 
#define STR_RES_34 359  // 
#define STR_RES__ 360  // ?
#define STR_RES_PLAYED 361  // played
#define STR_RES_OFF 362  // off
#define STR_RES_ON 363  // on
#define STR_RES_SQ1 364  // sq1
#define STR_RES__TR1 365  // tr1
#define STR_RES_PL1 366  // pl1
#define STR_RES_SQ2 367  // sq2
#define STR_RES__TR2 368  // tr2
#define STR_RES_PL2 369  // pl2
#define STR_RES_CLICK 370  // click	
#define STR_RES_GLITCH 371  // glitch
#define STR_RES_BLOW 372  // blow
#define STR_RES_METAL 373  // metal
#define STR_RES_POP 374  // pop	
#define STR_RES_NONE 375  // none					// START WAVEFORM LIST
#define STR_RES_SAW 376  // saw
#define STR_RES_SQUARE 377  // square
#define STR_RES_TRIANG 378  // triang
#define STR_RES_8BITS 379  // 8bits
#define STR_RES_CRUSH 380  // crush
#define STR_RES_WAVES 381  // waves
#define STR_RES_TAMPUR 382  // tampur
#define STR_RES_DIGITL 383  // digitl
#define STR_RES_METALL 384  // metall
#define STR_RES_BOWED 385  // bowed
#define STR_RES_SLAP 386  // slap
#define STR_RES_ORGAN 387  // organ
#define STR_RES_MALE 388  // male
#define STR_RES_BELISH 389  // belish
#define STR_RES_POLATD 390  // polatd
#define STR_RES_CELLO 391  // cello
#define STR_RES_CLPSWP 392  // clpswp
#define STR_RES_FEMALE 393  // female
#define STR_RES_FMTVOC 394  // fmtvoc
#define STR_RES_FRMNT2 395  // frmnt2
#define STR_RES_RES3HP 396  // res3hp
#define STR_RES_ELECTP 397  // electp
#define STR_RES_VIBES 398  // vibes
//#define STR_RES_ZSAW 379  // zsaw
//#define STR_RES_ZRESO 380  // zreso
//#define STR_RES_ZTRI 381  // ztri
//#define STR_RES_ZPULSE 382  // zpulse
//#define STR_RES_ZSYNC 383  // zsync
//#define STR_RES_PAD 384  // pad
//#define STR_RES_FM 385  // fm
//#define STR_RES_USER 394  // user
//#define STR_RES_PWM 397  // pwm
//#define STR_RES___NOISE 398  // noise
//#define STR_RES_VOWEL 399  // vowel
#define STR_RES__LPF 410  // lpf
#define STR_RES_SSM 411  // ssm
#define STR_RES_SVF 412  // svf
#define STR_RES_DSP 413  // dsp
#define STR_RES_PVK 414  // pvk
#define STR_RES_4PM 415  // 4pm
#define STR_RES_DLY 416  // dly
#define STR_RES_SP 417  // sp
#define STR_RES_SPLASH 418  // splash
#define STR_RES__FILTER 419  // filter
#define STR_RES_PRESET 420  // preset
#define STR_RES_EQUAL 421  // equal
#define STR_RES_JUST 422  // just
#define STR_RES_PYTHAG 423  // pythag
#define STR_RES_1_4_EB 424  // 1/4 eb
#define STR_RES_1_4_E 425  // 1/4 e
#define STR_RES_1_4_EA 426  // 1/4 ea
#define STR_RES_BHAIRA 427  // bhaira
#define STR_RES_GUNAKR 428  // gunakr
#define STR_RES_MARWA 429  // marwa
#define STR_RES_SHREE 430  // shree
#define STR_RES_PURVI 431  // purvi
#define STR_RES_BILAWA 432  // bilawa
#define STR_RES_YAMAN 433  // yaman
#define STR_RES_KAFI 434  // kafi
#define STR_RES_BHIMPA 435  // bhimpa
#define STR_RES_DARBAR 436  // darbar
#define STR_RES_BAGESH 437  // bagesh
#define STR_RES_RAGESH 438  // ragesh
#define STR_RES_KHAMAJ 439  // khamaj
#define STR_RES_MIMAL 440  // mi'mal
#define STR_RES_PARAME 441  // parame
#define STR_RES_RANGES 442  // ranges
#define STR_RES_GANGES 443  // ganges
#define STR_RES_KAMESH 444  // kamesh
#define STR_RES_PALAS_ 445  // palas
#define STR_RES_NATBHA 446  // natbha
#define STR_RES_M_KAUN 447  // m.kaun
#define STR_RES_BAIRAG 448  // bairag
#define STR_RES_B_TODI 449  // b.todi
#define STR_RES_CHANDR 450  // chandr
#define STR_RES_KAUSHI 451  // kaushi
#define STR_RES_JOGESH 452  // jogesh
#define STR_RES_RASIA 453  // rasia
// ### ADDED ###
#define STR_RES_ROOTLVL 454	// rlvl
#define STR_RES_ROOTLEVEL 455	//root lvl
#define STR_RES_DIV1LVL 456	// 1lvl
#define STR_RES_DIV1LEVEL 457	// div1 lvl
#define STR_RES_DIV2LVL 458	// 2lvl
#define STR_RES_DIV2LEVEL 459	// div2 lvl
#define STR_RES_DIV3LVL 460	// 3lvl
#define STR_RES_DIV3LEVEL 461	// div3 lvl
#define STR_RES_DIVISION 462	// division
#define STR_RES_DIV 463	// div
#define STR_RES_SHIFT_TYPE 464	// shft typ
#define STR_RES_STY 465	// sty
#define STR_RES_SHIFT_LN 466	// shft amt
#define STR_RES_SHF 467	// shf
#define STR_RES_SHIFT_FINE 468	// shift fine
#define STR_RES_FIN 469	// fine
#define STR_RES_WARP_AMT 470	// warp amt
#define STR_RES_WRP 471	// wrp

#define STR_RES_123 472 // 123
#define STR_RES_124 473 // 124
#define STR_RES_125 474 // 125
#define STR_RES_126 475  // 126
#define STR_RES_127 476  // 127
#define STR_RES_128 477  // 128
#define STR_RES_134 478  // 134
#define STR_RES_135 479  // 135
#define STR_RES_136 480  // 136
#define STR_RES_137 481  // 137
#define STR_RES_138 482  // 138
#define STR_RES_145 483  // 145
#define STR_RES_146 484  // 146
#define STR_RES_147 485  // 147
#define STR_RES_148 486  // 148
#define STR_RES_156 487  // 156
#define STR_RES_157 488  // 157
#define STR_RES_158 489  // 158
#define STR_RES_167 490  // 167
#define STR_RES_168 491  // 168
#define STR_RES_178 492  // 178
#define STR_RES_234 493	// 234
#define STR_RES_235 494	// 235
#define STR_RES_236 495	// 236
#define STR_RES_237 496	// 237
#define STR_RES_238 497	// 238
#define STR_RES_245 498	// 245
#define STR_RES_246 499	// 246

#define STR_RES_FSH 500	// fsh
#define STR_RES_FEV 501	// esh
#define STR_RES_PSH 502	// psh
#define STR_RES_FSR 503	// fsy
#define STR_RES_FS1 504	// esy
#define STR_RES_FER 505	// psy

#define SHIFT_MIN_VAL -63
#define SHIFT_MAX_VAL 63

#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS 1
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS_SIZE 128
#define LUT_RES_OSCILLATOR_INCREMENTS 2
#define LUT_RES_OSCILLATOR_INCREMENTS_SIZE 97
#define LUT_RES_FM_FREQUENCY_RATIOS 3
#define LUT_RES_FM_FREQUENCY_RATIOS_SIZE 25
#define LUT_RES_SCALE_JUST 4
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 5
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 6
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 7
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 8
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_BHAIRAV 9
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 10
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 11
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 12
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 13
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 14
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 15
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 16
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 17
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 18
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 19
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 20
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 21
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 22
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 23
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 24
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 25
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 26
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PALAS_KAFI 27
#define LUT_RES_SCALE_PALAS_KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 28
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 29
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 30
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 31
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 32
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 33
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 34
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 35
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 36
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 15
#define LUT_RES_GROOVE_SWING 37
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 38
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 39
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 40
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 41
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 42
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define LUT_RES_TEMPO_PHASE_INCREMENT 0
#define LUT_RES_TEMPO_PHASE_INCREMENT_SIZE 201
//#define WAV_RES_FORMANT_SINE 0
//#define WAV_RES_FORMANT_SINE_SIZE 256
//#define WAV_RES_FORMANT_SQUARE 1
//#define WAV_RES_FORMANT_SQUARE_SIZE 256
#define WAV_RES_SINE 2
#define WAV_RES_SINE_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_0 3
#define WAV_RES_BANDLIMITED_SQUARE_0_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_1 4
#define WAV_RES_BANDLIMITED_SQUARE_1_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_2 5
#define WAV_RES_BANDLIMITED_SQUARE_2_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_3 6
#define WAV_RES_BANDLIMITED_SQUARE_3_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_4 7
#define WAV_RES_BANDLIMITED_SQUARE_4_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_5 8
#define WAV_RES_BANDLIMITED_SQUARE_5_SIZE 257
#define WAV_RES_BANDLIMITED_SQUARE_6 9
#define WAV_RES_BANDLIMITED_SQUARE_6_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 10
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 11
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 12
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 13
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 14
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 15
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 16
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_0 17
#define WAV_RES_BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES__BANDLIMITED_TRIANGLE_0 18
#define WAV_RES__BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES___BANDLIMITED_TRIANGLE_0 19
#define WAV_RES___BANDLIMITED_TRIANGLE_0_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_3 20
#define WAV_RES_BANDLIMITED_TRIANGLE_3_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_4 21
#define WAV_RES_BANDLIMITED_TRIANGLE_4_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_5 22
#define WAV_RES_BANDLIMITED_TRIANGLE_5_SIZE 257
#define WAV_RES_BANDLIMITED_TRIANGLE_6 23
#define WAV_RES_BANDLIMITED_TRIANGLE_6_SIZE 257
//#define WAV_RES_VOWEL_DATA 24
//#define WAV_RES_VOWEL_DATA_SIZE 63
//#define WAV_RES_DISTORTION 25
//#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_ENV_EXPO 26
#define WAV_RES_ENV_EXPO_SIZE 257
#define WAV_RES_SSM2164_LINEARIZATION 27
#define WAV_RES_SSM2164_LINEARIZATION_SIZE 64
#define WAV_RES_WAVES 28
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 29
#define WAV_RES_WAVETABLES_SIZE 324
#define WAV_RES_VERSION 30
#define WAV_RES_VERSION_SIZE 2
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace shruthi

#endif  // SHRUTHI_RESOURCES_H_

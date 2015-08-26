#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/string.h"
#include "mruby/hash.h"
#include "ev3if.h"

typedef struct tone_info {
  const char *tone;
  mrb_int freq;
} tone_info;

#define ROUND(x) ((mrb_int)(x + 0.5))

static const tone_info _tones[] =
{
  {"c4",  ROUND( 261.63)}, {"cs4", ROUND( 277.18)}, {"d4",  ROUND( 293.66)},
  {"ds4", ROUND( 311.13)}, {"e4",  ROUND( 329.63)}, {"f4",  ROUND( 349.23)},
  {"fs4", ROUND( 369.99)}, {"g4",  ROUND( 392.00)}, {"gs4", ROUND( 415.30)},
  {"a4",  ROUND( 440.00)}, {"as4", ROUND( 466.16)}, {"b4",  ROUND( 493.88)},
  {"c5",  ROUND( 523.25)}, {"cs5", ROUND( 554.37)}, {"d5",  ROUND( 587.33)},
  {"ds5", ROUND( 622.25)}, {"e5",  ROUND( 659.25)}, {"f5",  ROUND( 698.46)},
  {"fs5", ROUND( 739.99)}, {"g5",  ROUND( 783.99)}, {"gs5", ROUND( 830.61)},
  {"a5",  ROUND( 880.00)}, {"as5", ROUND( 932.33)}, {"b5",  ROUND( 987.77)},
  {"c6",  ROUND(1046.50)}, {"cs6", ROUND(1108.73)}, {"d6",  ROUND(1174.66)},
  {"ds6", ROUND(1244.51)}, {"e6",  ROUND(1318.51)}, {"f6",  ROUND(1396.91)},
  {"fs6", ROUND(1479.98)}, {"g6",  ROUND(1567.98)}, {"gs6", ROUND(1661.22)},
  {"a6",  ROUND(1760.00)}, {"as6", ROUND(1864.66)}, {"b6",  ROUND(1975.53)},
  {"c6",  ROUND(1046.50)}, {"cs6", ROUND(1108.73)}, {"d6",  ROUND(1174.66)},
  {"ds6", ROUND(1244.51)}, {"e6",  ROUND(1318.51)}, {"f6",  ROUND(1396.91)},
  {"fs6", ROUND(1479.98)}, {"g6",  ROUND(1567.98)}, {"gs6", ROUND(1661.22)},
  {"a6",  ROUND(1760.00)}, {"as6", ROUND(1864.66)}, {"b6",  ROUND(1975.53)}
};


/*
 *  call-seq:
 *     Sound.tone(t, ms)  # => nil
 *
 *  Play a tone, given its tone and duration.
 *    tone: <k>[s]<o>   (e.g. cs4)
 *      k: Key of tone
 *        c   DO
 *        d   RE
 *        e   MI
 *        f   FA
 *        g   SOL
 *        a   LA
 *        b   SI
 *      s: Sharp
 *      o: Octave (4 to 6)
 *
 *  Parameters:
 *    +t+     Tone of sound
 *        Symbol: Symbol of tone (:c4, :cs4, :d4, ds4, ... :b5)
 *        String: String of tone ("c4", "cs4", "d4", "ds4", ... "b5")
 *        Float:  Frequency of tone (Hz)
 *    +ms+    Duration of the tone. (milliseconds)
 *
 *  Returns nil
 */
static mrb_value
mrb_sound_tone(mrb_state *mrb, mrb_value self)
{
  mrb_value map = mrb_const_get(mrb, self, mrb_intern_lit(mrb, "TONE"));
  mrb_value obj, tone = mrb_nil_value();
  mrb_int ms;
  mrb_sym sym;

  mrb_get_args(mrb, "oi", &obj, &ms);
  if (mrb_fixnum_p(obj)) {
    tone = obj;
  }
  else if (mrb_float_p(obj)) {
    tone = mrb_fixnum_value((mrb_int)(mrb_float(obj) + 0.5));
  }
  else if (mrb_symbol_p(obj)) {
    tone = mrb_hash_get(mrb, map, obj);
  }
  else if (mrb_string_p(obj)) {
    sym = mrb_intern_cstr(mrb, mrb_string_value_cstr(mrb, &obj));
    tone = mrb_hash_get(mrb, map, mrb_symbol_value(sym));
  }
  if (mrb_nil_p(tone)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid tone (%S)", obj);
  }

  ev3_speaker_play_tone(mrb_fixnum(tone), ms);
  return mrb_nil_value();
}

/*
 *  call-seq:
 *     Sound.volume = vol  # => nil
 *
 *  Set volume level.
 *
 *  Parameters:
 *    +vol+   Volume level (0 to 100)
 *
 *  Returns nil
 */
static mrb_value
mrb_sound_set_volume(mrb_state *mrb, mrb_value self)
{
  mrb_int vol;
  mrb_get_args(mrb, "i", &vol);
  ev3_speaker_set_volume((uint16_t)vol);
  return mrb_nil_value();
}

/*
 *  call-seq:
 *     Sound.stop  # => nil
 *
 *  Stop sound.
 *
 *  Returns nil
 */
static mrb_value
mrb_sound_stop(mrb_state *mrb, mrb_value self)
{
  ev3_speaker_stop();
  return mrb_nil_value();
}


void
mrb_ev3_sound_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *snd;
  mrb_value sndo;
  mrb_value tones;
  int i;

  /* Sound class */
  snd = mrb_define_class_under(mrb, ev3, "Sound", mrb->object_class);
  sndo = mrb_obj_value(snd);

  tones = mrb_hash_new(mrb);
  for (i=0; i<sizeof(_tones)/sizeof(_tones[0]); i++) {
    mrb_hash_set(mrb, tones, mrb_symbol_value(mrb_intern_cstr(mrb, _tones[i].tone)), mrb_fixnum_value(_tones[i].freq));
  }
  mrb_const_set(mrb, sndo, mrb_intern_lit(mrb, "TONE"), tones);

  mrb_define_class_method(mrb, snd, "tone",     mrb_sound_tone,       MRB_ARGS_REQ(2));
  mrb_define_class_method(mrb, snd, "volume=",  mrb_sound_set_volume, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, snd, "stop",     mrb_sound_stop,       MRB_ARGS_NONE());
}

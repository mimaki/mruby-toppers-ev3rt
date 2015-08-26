#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/hash.h"
#include "ev3if.h"


/*
 *  call-seq:
 *     LED.color = col  # => nil
 *
 *  Light LED.
 *
 *  Parameters:
 *    +col+     LED color
 *       LED::OFF
 *       LED::RED
 *       LED::GREEN
 *       LED::ORANGE
 *
 *  Returns nil.
 */
static mrb_value
mrb_led_color(mrb_state *mrb, mrb_value self)
{
  mrb_value cmap = mrb_const_get(mrb, self, mrb_intern_lit(mrb, "COLOR"));
  mrb_sym col;
  mrb_value colv;

  mrb_get_args(mrb, "n", &col);
  colv = mrb_hash_get(mrb, cmap, mrb_symbol_value(col));
  if (mrb_nil_p(colv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid color :%S", mrb_sym2str(mrb, col));
  }

  ev3_led_set_color(mrb_fixnum(colv));
  return mrb_nil_value();
}

/*
 *  call-seq:
 *     LED.off  # => nil
 *
 *  LED turn off.
 *
 *  Returns nil.
 */
static mrb_value
mrb_led_off(mrb_state *mrb, mrb_value self)
{
  ev3_led_set_color(LED_OFF);
  return mrb_nil_value();
}


void
mrb_ev3_led_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *led;
  mrb_value ledo;
  mrb_value col;

  /* LED class */
  led = mrb_define_class_under(mrb, ev3, "LED", mrb->object_class);
  ledo = mrb_obj_value(led);

  col = mrb_hash_new(mrb);
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "off")),    mrb_fixnum_value(LED_OFF));
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "red")),    mrb_fixnum_value(LED_RED));
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "green")),  mrb_fixnum_value(LED_GREEN));
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "orange")), mrb_fixnum_value(LED_ORANGE));
  mrb_const_set(mrb, ledo, mrb_intern_lit(mrb, "COLOR"), col);

  mrb_define_class_method(mrb, led, "color=", mrb_led_color,  MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, led, "off",    mrb_led_off,    MRB_ARGS_NONE());
}

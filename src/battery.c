#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "ev3if.h"


/*
 *  call-seq:
 *     Battery.mA  # => Fixnum
 *
 *  Get the current draw from the battery
 *
 *  Returns current in mA
 */
static mrb_value
mrb_battery_mA(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(ev3_battery_current_mA());
}

/*
 *  call-seq:
 *     Battery.mV  # => Fixnum
 *
 *  Get battery battery voltage.
 *
 *  Returns battery voltage in mV
 */
static mrb_value
mrb_battery_mV(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(ev3_battery_voltage_mV());
}


void
mrb_ev3_battery_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *bat;

  /* Battery class */
  bat = mrb_define_class_under(mrb, ev3, "Battery", mrb->object_class);

  mrb_define_class_method(mrb, bat, "mA", mrb_battery_mA, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, bat, "mV", mrb_battery_mV, MRB_ARGS_NONE());
}

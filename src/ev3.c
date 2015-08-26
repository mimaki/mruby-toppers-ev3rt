#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/array.h"
#include "ev3if.h"

extern void mrb_ev3_lcd_init(mrb_state*, struct RClass*);
extern void mrb_ev3_led_init(mrb_state*, struct RClass*);
extern void mrb_ev3_button_init(mrb_state*, struct RClass*);
extern void mrb_ev3_sound_init(mrb_state*, struct RClass*);
extern void mrb_ev3_battery_init(mrb_state*, struct RClass*);
extern void mrb_ev3_motor_init(mrb_state*, struct RClass*, struct RClass*);
extern void mrb_ev3_sensor_init(mrb_state*, struct RClass*, struct RClass*);
extern void mrb_ev3_serial_init(mrb_state*, struct RClass*);


/*
 *  call-seq:
 *     Balancer.new   # => Balancer
 *     bal.reset      # => Balancer
 *
 *  Initialize Balancer API.
 *
 *  Returns left and right motor's PWM value.
 *  [pwml, pwmr]
 */
static mrb_value
mrb_balance_init(mrb_state *mrb, mrb_value self)
{
  balance_init();
  return self;
}

/*
 *  call-seq:
 *     bal.control(fwd, trn, gyr, off, anl, anr, vlt)  # => Array
 *
 *  Call Balancer API.
 *
 *  Returns left and right motor's PWM value.
 *  [pwml, pwmr]
 */
static mrb_value
mrb_balance_control(mrb_state *mrb, mrb_value self)
{
  mrb_float fwd, trn, gyr, off, anl, anr, vlt;
  signed char pwml, pwmr;
  mrb_value ary;

  mrb_get_args(mrb, "fffffff", &fwd, &trn, &gyr, &off, &anl, &anr, &vlt);

  balance_control(fwd, trn, gyr, off, anl, anr, vlt, &pwml, &pwmr);

  ary = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, ary, mrb_fixnum_value(pwml));
  mrb_ary_push(mrb, ary, mrb_fixnum_value(pwmr));

  return ary;
}

void
mrb_mruby_toppers_ev3rt_gem_init(mrb_state *mrb)
{
  struct RClass *ev3;
  struct RClass *dev;
  struct RClass *bal;

  /* EV3RT module */
  ev3 = mrb_define_module(mrb, "EV3RT");

  /* EV3 parts */
  mrb_ev3_lcd_init(mrb, ev3);     /* LCD */
  mrb_ev3_led_init(mrb, ev3);     /* LED */
  mrb_ev3_button_init(mrb, ev3);  /* Button */
  mrb_ev3_sound_init(mrb, ev3);   /* Sound */
  mrb_ev3_battery_init(mrb, ev3); /* Battery */
  mrb_ev3_serial_init(mrb, ev3);  /* SerialPort */

  /* EV3 Devices */
  dev = mrb_define_class_under(mrb, ev3, "Device", mrb->object_class);

  mrb_ev3_motor_init(mrb, ev3, dev);  /* Motor */
  mrb_ev3_sensor_init(mrb, ev3, dev); /* Sensor, ColorSensor, GyroSensor, TouchSensor, UltrasonicSensor */

  /* Balancer */
  bal = mrb_define_class_under(mrb, ev3, "Balancer", mrb->object_class);

  mrb_define_method(mrb, bal, "initialize", mrb_balance_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, bal, "reset",      mrb_balance_init,     MRB_ARGS_NONE());
  mrb_define_method(mrb, bal, "control",    mrb_balance_control,  MRB_ARGS_REQ(7));

#ifndef EV3
  mrb_gv_set(mrb, mrb_intern_lit(mrb, "$ev3_host"), mrb_true_value());
#endif
}

void
mrb_mruby_toppers_ev3rt_gem_final(mrb_state *mrb)
{
}

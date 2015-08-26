#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/hash.h"
#include "ev3if.h"

/*
 *  call-seq:
 *     Motor.new(port, type=:large)  # => Motor
 *
 *  Creates Motor object.
 *
 *  Parameters:
 *    +port+    Motor port
 *       :port_a    PORT A
 *       :port_b    PORT B
 *       :port_c    PORT C
 *       :port_d    PORT D
 *    +type+    Motor type
 *       Motor::NONE      none
 *       Motor::MEDIUM    medium motor
 *       Motor::LARGE     large motor
 *       Motor::UNKNOWN   Unregulated motor
 *
 *  Returns Motor object.
 */
static mrb_value
mrb_motor_init(mrb_state *mrb, mrb_value self)
{
  struct RClass *mtr = mrb_obj_class(mrb, self);
  mrb_value pmap = mrb_const_get(mrb, mrb_obj_value(mtr), mrb_intern_lit(mrb, "PORT"));
  mrb_value tmap = mrb_const_get(mrb, mrb_obj_value(mtr), mrb_intern_lit(mrb, "TYPE"));
  mrb_sym port;
  mrb_sym type = mrb_intern_lit(mrb, "large");
  mrb_value portv;
  mrb_value typev;

  mrb_get_args(mrb, "n|n", &port, &type);

  portv = mrb_hash_get(mrb, pmap, mrb_symbol_value(port));
  if (mrb_nil_p(portv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid motor port :%S", mrb_sym2str(mrb, port));
  }

  typev = mrb_hash_get(mrb, tmap, mrb_symbol_value(type));
  if (mrb_nil_p(typev)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid motor type :%S", mrb_sym2str(mrb, type));
  }

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@port"), portv);
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@type"), typev);

  ev3_motor_config(mrb_fixnum(portv), mrb_fixnum(typev));

  return self;
}

/*
 *  call-seq:
 *     motor.power = pwr  # => Fixnum
 *
 *  Sets motor power.
 *
 *  Parameters:
 *    +pwr+     Motor power (-100 to 100)
 *         > 0:   Motor forwards
 *         < 0:   Motor backwards
 *
 *  Returns power value.
 */
static mrb_value
mrb_motor_set_power(mrb_state *mrb, mrb_value self)
{
  mrb_int port;
  mrb_int v;

  mrb_get_args(mrb, "i", &v);
  if      (v > EV3_MOTOR_FMAX) v = EV3_MOTOR_FMAX;
  else if (v < EV3_MOTOR_BMAX) v = EV3_MOTOR_BMAX;

  port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  ev3_motor_set_power(port, v);

  return mrb_fixnum_value(v);
}

/*
 *  call-seq:
 *     motor.power  # => Fixnum
 *
 *  Gets motor current power.
 *
 *  Returns power value.
 */
static mrb_value
mrb_motor_get_power(mrb_state *mrb, mrb_value self)
{
  mrb_int port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  return mrb_fixnum_value(ev3_motor_get_power(port));
}

/*
 *  call-seq:
 *     motor.stop(brk=false)  # => nil
 *
 *  Stop the motor.
 *
 *  Parameters:
 *    +brk+
 *         true:  Brake motor
 *         false: Turn off motor
 *
 *  Returns nil
 */
static mrb_value
mrb_motor_stop(mrb_state *mrb, mrb_value self)
{
  mrb_int port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  mrb_bool brake = FALSE;

  mrb_get_args(mrb, "|b", &brake);
  ev3_motor_stop(port, brake ? TRUE : FALSE);
  return mrb_nil_value();
}

/*
 *  call-seq:
 *     motor.rotate(deg, spd, blk)  # => nil
 *
 *  Rotate the motor.
 *
 *  Parameters:
 *    +deg+   Rotates through `deg` degrees
 *      > 0:    Rotate forward
 *      < 0:    Rotate backward
 *    +spd+   Rotate speed. (0 to 100)
 *    +blk+   Blocking mode
 *      false:  No blocking (default)
 *      true:   Blocking until completion
 *
 *  Returns nil
 */
static mrb_value
mrb_motor_rotate(mrb_state *mrb, mrb_value self)
{
  mrb_int port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  mrb_int deg, spd, blk = 1;

  mrb_get_args(mrb, "ii|i", &deg, &spd, &blk);
  spd = (spd < 0) ? 0 : (spd > 100) ? 100 : spd;
  ev3_motor_rotate(port, deg, spd, blk);
  return mrb_nil_value();
}

/*
 *  call-seq:
 *     motor.count  # => Fixnum
 *
 *  Gets motor counter.
 *
 *  Returns counter value.
 */
static mrb_value
mrb_motor_get_count(mrb_state *mrb, mrb_value self)
{
  mrb_int port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  return mrb_fixnum_value(ev3_motor_get_counts(port));
}

/*
 *  call-seq:
 *     motor.reset  # => nil
 *
 *  Resets motor counter.
 *
 *  Returns counter value.
 */
static mrb_value
mrb_motor_reset_count(mrb_state *mrb, mrb_value self)
{
  mrb_int port = mrb_fixnum(mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port")));
  ev3_motor_reset_counts(port);
  return mrb_nil_value();
}


void
mrb_ev3_motor_init(mrb_state *mrb, struct RClass *ev3, struct RClass *dev)
{
  struct RClass *mtr;
  mrb_value mtro;
  mrb_value port;
  mrb_value type;

  /* Motor class */
  mtr = mrb_define_class_under(mrb, ev3, "Motor", dev);
  mtro = mrb_obj_value(mtr);

  port = mrb_hash_new(mrb);
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "port_a")), mrb_fixnum_value(EV3_PORT_A));
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "port_b")), mrb_fixnum_value(EV3_PORT_B));
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "port_c")), mrb_fixnum_value(EV3_PORT_C));
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "port_d")), mrb_fixnum_value(EV3_PORT_D));
  mrb_const_set(mrb, mtro, mrb_intern_lit(mrb, "PORT"), port);

  type = mrb_hash_new(mrb);
  mrb_hash_set(mrb, type, mrb_symbol_value(mrb_intern_lit(mrb, "medium")),  mrb_fixnum_value(MEDIUM_MOTOR));
  mrb_hash_set(mrb, type, mrb_symbol_value(mrb_intern_lit(mrb, "large")),   mrb_fixnum_value(LARGE_MOTOR));
  mrb_hash_set(mrb, type, mrb_symbol_value(mrb_intern_lit(mrb, "unknown")), mrb_fixnum_value(UNREGULATED_MOTOR));
  mrb_const_set(mrb, mtro, mrb_intern_lit(mrb, "TYPE"), type);

  mrb_define_method(mrb, mtr, "initialize",   mrb_motor_init,         MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, mtr, "power=",       mrb_motor_set_power,    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mtr, "power",        mrb_motor_get_power,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mtr, "stop",         mrb_motor_stop,         MRB_ARGS_OPT(1));
  mrb_define_method(mrb, mtr, "rotate",       mrb_motor_rotate,       MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, mtr, "count",        mrb_motor_get_count,    MRB_ARGS_NONE());
  mrb_define_method(mrb, mtr, "reset_count",  mrb_motor_reset_count,  MRB_ARGS_NONE());
}

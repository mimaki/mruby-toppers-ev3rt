#include <stdio.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/hash.h"
#include "ev3if.h"

#define E_IO_ERROR (mrb_class_get(mrb, "IOError"))

MRB_API void mrb_file_attach(mrb_value, FILE*);

/*
 *  call-seq:
 *     SerialPort.new(port)  # => SerialPort
 *
 *  Open serial port.
 *
 *  Parameters:
 *    +port+    font size.
 *       :default   Default serial port
 *       :uart      UART
 *       :bt        Bluetooth
 *
 *  Returns SerialPort object.
 */
static mrb_value
mrb_serial_init(mrb_state *mrb, mrb_value self)
{
  struct RClass *ser = mrb_obj_class(mrb, self);
  mrb_value pmap = mrb_const_get(mrb, mrb_obj_value(ser), mrb_intern_lit(mrb, "PORT"));
  mrb_sym port;
  mrb_value portv;
  FILE *fp;

  mrb_get_args(mrb, "n", &port);

  portv = mrb_hash_get(mrb, pmap, mrb_symbol_value(port));
  if (mrb_nil_p(portv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid port :%S", mrb_sym2str(mrb, port));
  }

  fp = ev3_serial_open_file((serial_port_t)mrb_fixnum(portv));
  if (fp == NULL) {
    mrb_raisef(mrb, E_IO_ERROR, "Serial port cannot open :%S", mrb_sym2str(mrb, port));
  }

  mrb_file_attach(self, fp);

  return self;
}

void
mrb_ev3_serial_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *file = mrb_class_get(mrb, "File");
  struct RClass *ser;
  mrb_value sero;
  mrb_value port;

  /* SerialPort class */
  ser = mrb_define_class_under(mrb, ev3, "SerialPort", file);
  sero = mrb_obj_value(ser);

  port = mrb_hash_new(mrb);
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "default")), mrb_fixnum_value(EV3_SERIAL_DEFAULT));
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "uart")),    mrb_fixnum_value(EV3_SERIAL_UART));
  mrb_hash_set(mrb, port, mrb_symbol_value(mrb_intern_lit(mrb, "bt")),      mrb_fixnum_value(EV3_SERIAL_BT));
  mrb_const_set(mrb, sero, mrb_intern_lit(mrb, "PORT"), port);

  mrb_define_method(mrb, ser, "initialize", mrb_serial_init, MRB_ARGS_REQ(1));
}

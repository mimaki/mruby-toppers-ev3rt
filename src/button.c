#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "mruby/hash.h"
#include "ev3if.h"

/*
 *  call-seq:
 *     Button.new(key)  # => Button
 *
 *  Creates Button object.
 *
 *  Parameters:
 *    +key+     Button name
 *       :left    Left button
 *       :right   Right button
 *       :up      Up button
 *       :down    Down button
 *       :enter   Enter button
 *       :back    Back button
 *
 *  Returns Butotn object.
 */
static mrb_value
mrb_btn_init(mrb_state *mrb, mrb_value self)
{
  struct RClass *btn = mrb_obj_class(mrb, self);
  mrb_value map = mrb_const_get(mrb, mrb_obj_value(btn), mrb_intern_lit(mrb, "KEY"));
  mrb_sym key;
  mrb_value keyv;

  mrb_get_args(mrb, "n", &key);
  keyv = mrb_hash_get(mrb, map, mrb_symbol_value(key));

  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@key"), keyv);

  return self;
}

/*
 *  call-seq:
 *     Button[key]  # => Button
 *
 *  Get button object.
 *
 *  Parameters:
 *    +key+     Button name
 *       :left    Left button
 *       :right   Right button
 *       :up      Up button
 *       :down    Down button
 *       :enter   Enter button
 *       :back    Back button
 *
 *  Returns Button object
 */
static mrb_value
mrb_btn_get(mrb_state *mrb, mrb_value self)
{
  mrb_sym sym;
  mrb_value symv;

  mrb_get_args(mrb, "n", &sym);
  symv = mrb_symbol_value(sym);

  return mrb_obj_new(mrb, mrb_class_ptr(self), 1, &symv);
}

/*
 *  call-seq:
 *     btn.pressed?  # => true/false
 *
 *  Get button status.
 *
 *  Returns button status. (true:pressed, false:released)
 */
static mrb_value
mrb_btn_pressed(mrb_state *mrb, mrb_value self)
{
  int32_t pressed = FALSE;
  mrb_value key;

  key = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@key"));
  if (!mrb_nil_p(key)) {
    pressed = ev3_button_is_pressed((int16_t)mrb_fixnum(key));
  }

  return mrb_bool_value(pressed);
}


void
mrb_ev3_button_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *btn;
  mrb_value btno;
  mrb_value keys;

  /* Button class */
  btn = mrb_define_class_under(mrb, ev3, "Button", mrb->object_class);
  btno = mrb_obj_value(btn);

  keys = mrb_hash_new(mrb);
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "left")), mrb_fixnum_value(LEFT_BUTTON));
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "right")), mrb_fixnum_value(RIGHT_BUTTON));
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "up")), mrb_fixnum_value(UP_BUTTON));
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "down")), mrb_fixnum_value(DOWN_BUTTON));
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "enter")), mrb_fixnum_value(ENTER_BUTTON));
  mrb_hash_set(mrb, keys, mrb_symbol_value(mrb_intern_lit(mrb, "back")), mrb_fixnum_value(BACK_BUTTON));
  mrb_const_set(mrb, btno, mrb_intern_lit(mrb, "KEY"), keys);

  mrb_define_class_method(mrb, btn, "[]", mrb_btn_get, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, btn, "initialize", mrb_btn_init,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, btn, "pressed?",   mrb_btn_pressed,  MRB_ARGS_NONE());
}

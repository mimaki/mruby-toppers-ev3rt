#include <stdio.h>
#include <string.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/string.h"
#include "mruby/hash.h"
#include "mruby/data.h"
#include "ev3if.h"

typedef struct ev3_font_size {
  int32_t w;
  int32_t h;
} ev3_font_size;

static ev3_font_size _font_size[2] = {{0, 8}, {0, 16}};

/* LCD information */
typedef struct mrb_lcd_t {
  mrb_int font;   /* Font size (0:small, 1:medium) */
  mrb_int left;   /* screen left */
  mrb_int top;    /* screen top */
  mrb_int width;  /* screen width */
  mrb_int height; /* screen height */
  mrb_int color;  /* foreground color */
  mrb_int cx;     /* X coordinate of cursor */
  mrb_int cy;     /* Y coordinate of cursor */
} mrb_lcd_t;

static void
mrb_lcd_free(mrb_state *mrb, void *data)
{
  mrb_free(mrb, data);
}
const static struct mrb_data_type mrb_lcd_type = {"LCD", mrb_lcd_free};

/*
 *  call-seq:
 *     LCD.new(font, x, y, width, height, color)  # => LCD
 *
 *  Creates LCD object.
 *
 *  Parameters:
 *    +font+    font size.
 *       :small   small font (6x8, default)
 *       :medium  medium font (8x16)
 *    +x+       Window origin (left) X coordinate. (default: 0)
 *    +y+       Window origin (top) Y coordinate. (default: 0)
 *    +width+   Width of window. (default: LCD::WIDTH)
 *    +height+  Height of window. (default: LCD::HEIGHT)
 *    +color+   LCD foreground color.
 *       :black   black (default)
 *       :white   while
 *
 *  Returns LCD object.
 */
static mrb_value
mrb_lcd_init(mrb_state *mrb, mrb_value self)
{
  struct RClass *lcd = mrb_obj_class(mrb, self);
  mrb_value fmap = mrb_const_get(mrb, mrb_obj_value(lcd), mrb_intern_lit(mrb, "FONT"));
  mrb_value cmap = mrb_const_get(mrb, mrb_obj_value(lcd), mrb_intern_lit(mrb, "COLOR"));
  mrb_sym font = mrb_intern_lit(mrb, "small");
  mrb_sym col = mrb_intern_lit(mrb, "black");
  mrb_value fontv;
  mrb_value colv;
  mrb_lcd_t *plcd;

  DATA_TYPE(self) = &mrb_lcd_type;
  plcd = (mrb_lcd_t*)mrb_malloc(mrb, sizeof(mrb_lcd_t));
  DATA_PTR(self) = plcd;
  memset(plcd, 0, sizeof(mrb_lcd_t));
  plcd->width  = EV3_LCD_WIDTH;
  plcd->height = EV3_LCD_HEIGHT;

  mrb_get_args(mrb, "|niiiin", &font, &plcd->left, &plcd->top, &plcd->width, &plcd->height, &col);

  fontv = mrb_hash_get(mrb, fmap, mrb_symbol_value(font));
  if (mrb_nil_p(fontv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid font size :%S", mrb_sym2str(mrb, font));
  }
  plcd->font = mrb_fixnum(fontv);
  if (_font_size[plcd->font].w == 0) {
    /* initialize font size at 1st time */
    ev3_font_get_size(plcd->font, &_font_size[plcd->font].w, &_font_size[plcd->font].h);
  }

  colv = mrb_hash_get(mrb, cmap, mrb_symbol_value(col));
  if (mrb_nil_p(colv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid foreground color :%S", mrb_sym2str(mrb, col));
  }
  plcd->color = mrb_fixnum(colv);

  return self;
}

/*
 *  call-seq:
 *     LCD.font = font  # => nil
 *
 *  Set the current font.
 *
 *  Parameters:
 *    +font+    font size.
 *       :small     small font
 *       :medium    medium font (8x16)
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_set_font(mrb_state *mrb, mrb_value self)
{
  mrb_value fmap = mrb_const_get(mrb, self, mrb_intern_lit(mrb, "FONT"));
  mrb_sym font;
  mrb_value fontv;

  mrb_get_args(mrb, "n", &font);
  fontv = mrb_hash_get(mrb, fmap, mrb_symbol_value(font));
  if (mrb_nil_p(fontv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid font size :%S", mrb_sym2str(mrb, font));
  }

  ev3_lcd_set_font(mrb_fixnum(fontv));
  mrb_cv_set(mrb, self, mrb_intern_lit(mrb, "@@font"), fontv);

  return mrb_nil_value();
}

/*
 *  call-seq:
 *     LCD.font # => Fixnum
 *
 *  Get the current font.
 *
 *  Parameters: None.
 *
 *  Returns font id. (0:small, 1:medium)
 */
static mrb_value
mrb_lcd_get_font(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->font);
}

/*
 *  call-seq:
 *     LCD.left # => Fixnum
 *
 *  Get screen left.
 *
 *  Parameters: None.
 *
 *  Returns X coordinate.
 */
static mrb_value
mrb_lcd_get_left(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->left);
}

/*
 *  call-seq:
 *     LCD.top # => Fixnum
 *
 *  Get screen top.
 *
 *  Parameters: None.
 *
 *  Returns Y coordinate.
 */
static mrb_value
mrb_lcd_get_top(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->top);
}

/*
 *  call-seq:
 *     LCD.width # => Fixnum
 *
 *  Get screen width.
 *
 *  Parameters: None.
 *
 *  Returns screen width (pixels).
 */
static mrb_value
mrb_lcd_get_width(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->width);
}

/*
 *  call-seq:
 *     LCD.height # => Fixnum
 *
 *  Get screen height.
 *
 *  Parameters: None.
 *
 *  Returns screen height (pixels).
 */
static mrb_value
mrb_lcd_get_height(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->height);
}

/*
 *  call-seq:
 *     LCD.csrx # => Fixnum
 *
 *  Get X coordinate of cursor.
 *
 *  Parameters: None.
 *
 *  Returns cursor X character coordinate.
 */
static mrb_value
mrb_lcd_get_csrx(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->cx);
}

/*
 *  call-seq:
 *     LCD.csry # => Fixnum
 *
 *  Get Y coordinate of cursor.
 *
 *  Parameters: None.
 *
 *  Returns cursor Y character coordinate.
 */
static mrb_value
mrb_lcd_get_csry(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->cy);
}

/*
 *  call-seq:
 *     LCD.color # => Fixnum
 *
 *  Get foreground color.
 *
 *  Parameters: None.
 *
 *  Returns foreground color.
 */
static mrb_value
mrb_lcd_get_color(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  return mrb_fixnum_value(plcd->color);
}

static void
mrb_lcd_get_font_size(mrb_state *mrb, mrb_value lcd, mrb_int *fw, mrb_int *fh)
{
  mrb_value font = mrb_cv_get(mrb, lcd, mrb_intern_lit(mrb, "@@font"));
  ev3_font_get_size(mrb_fixnum(font), fw, fh);
}

static void
ev3_set_current_font(mrb_state *mrb, mrb_value self)
{
  static mrb_bool first = TRUE;
  struct RClass *lcd = mrb_obj_class(mrb, self);
  mrb_int current = mrb_fixnum(mrb_cv_get(mrb, mrb_obj_value(lcd), mrb_intern_lit(mrb, "@@font")));
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  mrb_int target  = plcd->font;

  if (first || current != target) {
    ev3_lcd_set_font((uint16_t)target);
    mrb_cv_set(mrb, mrb_obj_value(lcd), mrb_intern_lit(mrb, "@@font"), mrb_fixnum_value(target));
    first = FALSE;
  }
}

static void
mrb_lcd_lf(mrb_state *mrb, mrb_value lcd)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(lcd);
  ev3_font_size *f = &_font_size[plcd->font];

  mrb_assert(plcd->font == EV3_FONT_SMALL || plcd->font == EV3_FONT_MEDIUM);
  mrb_assert(f->w != 0 && f->h != 0);

#ifdef EV3
  ev3_lcd_fill_rect(
    plcd->left  + plcd->cx * f->w,
    plcd->top   + plcd->cy * f->h,
    plcd->width - plcd->cx * f->w,
    f->h,
    plcd->color ? 0 : 1
  );
#else
  MRBEV3_PUTS("");
#endif

  plcd->cx = 0;
  plcd->cy = (plcd->cy + 1) % (plcd->height / f->h);
}

static void
mrb_lcd_print_line(mrb_state *mrb, mrb_value lcd, mrb_value *str)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(lcd);
  const char *src = mrb_string_value_cstr(mrb, str);
  size_t len = strlen(src);
  char *buf = mrb_malloc(mrb, len+1);
  ev3_font_size *f = &_font_size[plcd->font];
  mrb_int cw;
  mrb_int csr = plcd->cx;
  char *dst;
  mrb_bool lf;

  mrb_assert(plcd->font == EV3_FONT_SMALL || plcd->font == EV3_FONT_MEDIUM);
  mrb_assert(f->w != 0 && f->h != 0);

  cw = plcd->width / f->w;

  memset(buf, 0, len+1);
  dst = buf;
  while (len--) {
    lf = FALSE;
    if (*src == '\n') {
      lf = TRUE;
      src++;
    }
    else {
      *dst++ = *src++;
      csr++;
      if (csr >= cw) {
        lf = TRUE;
      }
    }
    if (lf) {
      *dst = '\0';
      ev3_lcd_draw_string(
        buf,
        plcd->left + plcd->cx * f->w,
        plcd->top  + plcd->cy * f->h
      );

      /* line feed */
#ifdef EV3
      ev3_lcd_fill_rect(
        plcd->left  + csr * f->w,
        plcd->top   + plcd->cy * f->h,
        plcd->width - csr * f->w,
        f->h,
        plcd->color ? 0 : 1
      );
#else
      MRBEV3_PUTS("");
#endif
      plcd->cy = (plcd->cy + 1) % (plcd->height / f->h);
      plcd->cx = csr = 0;

      memset(buf, 0, strlen(src)+1);
      dst = buf;
    }
  }
  *dst = '\0';
  if (dst != buf) {
    ev3_lcd_draw_string(
      buf,
      plcd->left + plcd->cx * f->w,
      plcd->top  + plcd->cy * f->h
    );
  }

  mrb_free(mrb, buf);

  /* update cursor */
  plcd->cx = csr;
}

/*
 *  call-seq:
 *     lcd.print(...)  # => nil
 *
 *  Prints the string at cursor position on window.
 *
 *  Parameters:
 *    +...+   The target for print.
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_print(mrb_state *mrb, mrb_value self)
{
  mrb_int argc;
  mrb_value *args;
  mrb_int i;
  mrb_value s;

  mrb_get_args(mrb, "*", &args, &argc);

  ev3_set_current_font(mrb, self);

  for(i=0; i<argc; i++,args++) {
    s = mrb_funcall(mrb, *args, "to_s", 0);
    mrb_lcd_print_line(mrb, self, &s);
  }

  return mrb_nil_value();
}

/*
 *  call-seq:
 *     lcd.puts(...)  # => nil
 *
 *  Puts the string that added newline at current cursor position
 *  on window.
 *
 *  Parameters:
 *    +...+   The target for put.
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_puts(mrb_state *mrb, mrb_value self)
{
  mrb_int argc;
  mrb_value *args;
  mrb_int i;
  mrb_value s;

  mrb_get_args(mrb, "*", &args, &argc);

  ev3_set_current_font(mrb, self);

  if (argc == 0) {
    mrb_lcd_lf(mrb, self);
  }
  for(i=0; i<argc; i++,args++) {
    s = mrb_funcall(mrb, *args, "to_s", 0);
    mrb_lcd_print_line(mrb, self, &s);
    mrb_lcd_lf(mrb, self);
  }

  return mrb_nil_value();
}

/*
 *  call-seq:
 *     LCD.draw(x, y, str)  # => nil
 *
 *  Draw the string at specified coordinate of LCD.
 *
 *  Parameters:
 *    +x+     X-coordinate of the string left edge
 *    +y+     Y-coordinate of the string top edge
 *    +str+   The target for drawing.
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_draw_string(mrb_state *mrb, mrb_value self)
{
  mrb_value obj, str;
  mrb_int x, y;
  mrb_int fw, fh;
  mrb_int cw, ch;

  mrb_lcd_get_font_size(mrb, self, &fw, &fh);
  cw = EV3_LCD_WIDTH  / fw;
  ch = EV3_LCD_HEIGHT / fh;

  mrb_get_args(mrb, "iio", &x, &y, &obj);

  if (mrb_string_p(obj)) {
    str = obj;
  }
  else {
    str = mrb_funcall(mrb, obj, "to_s", 0);
  }

  ev3_lcd_draw_string(mrb_string_value_cstr(mrb, &str), x*cw, y*ch);

  return mrb_nil_value();
}

/*
 *  call-seq:
 *     lcd.locate(cx, cy)  # => nil
 *
 *  Set the cursor position on window.
 *
 *  Parameters:
 *    +cx+    X-coordinate of cursor
 *    +cy+    Y-coordinate of cursor
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_locate(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  mrb_int x, y = -1;

  mrb_get_args(mrb, "i|i", &x, &y);

  plcd->cx = x;
  if (y >= 0) {
    plcd->cy = y;
  }

  return mrb_nil_value();
}

/*
 *  call-seq:
 *     lcd.clear(col)  # => nil
 *
 *  Clear window.
 *
 *  Parameters:
 *    +col+     LCD foreground color.
 *       :black   black (default)
 *       :white   while
 *
 *  Returns nil.
 */
static mrb_value
mrb_lcd_clear(mrb_state *mrb, mrb_value self)
{
  mrb_lcd_t *plcd = (mrb_lcd_t*)DATA_PTR(self);
  struct RClass *lcd = mrb_obj_class(mrb, self);
  mrb_value cmap = mrb_const_get(mrb, mrb_obj_value(lcd), mrb_intern_lit(mrb, "COLOR"));
  mrb_sym col = mrb_intern_lit(mrb, "black");
  mrb_value colv;

  mrb_get_args(mrb, "|n", &col);

  colv = mrb_hash_get(mrb, cmap, mrb_symbol_value(col));
  if (mrb_nil_p(colv)) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "invalid foreground color :%S", mrb_sym2str(mrb, col));
  }

  ev3_lcd_fill_rect(
    plcd->left,
    plcd->top,
    plcd->width,
    plcd->height,
    mrb_fixnum(colv) ? 0 : 1
  );
  plcd->cx = plcd->cy = 0;

  return mrb_nil_value();
}

void
mrb_ev3_lcd_init(mrb_state *mrb, struct RClass *ev3)
{
  struct RClass *lcd;
  mrb_value lcdo;
  mrb_value font;
  mrb_value col;

  /* LCD class */
  lcd = mrb_define_class_under(mrb, ev3, "LCD", mrb->object_class);
  lcdo = mrb_obj_value(lcd);

  font = mrb_hash_new(mrb);
  mrb_hash_set(mrb, font, mrb_symbol_value(mrb_intern_lit(mrb, "small")),   mrb_fixnum_value(EV3_FONT_SMALL));
  mrb_hash_set(mrb, font, mrb_symbol_value(mrb_intern_lit(mrb, "medium")),  mrb_fixnum_value(EV3_FONT_MEDIUM));
  mrb_const_set(mrb, lcdo, mrb_intern_lit(mrb, "FONT"), font);

  col = mrb_hash_new(mrb);
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "white")), mrb_fixnum_value(EV3_LCD_WHITE));
  mrb_hash_set(mrb, col, mrb_symbol_value(mrb_intern_lit(mrb, "black")), mrb_fixnum_value(EV3_LCD_BLACK));
  mrb_const_set(mrb, lcdo, mrb_intern_lit(mrb, "COLOR"), col);

  mrb_const_set(mrb, lcdo, mrb_intern_lit(mrb, "WIDTH"),        mrb_fixnum_value(EV3_LCD_WIDTH));
  mrb_const_set(mrb, lcdo, mrb_intern_lit(mrb, "HEIGHT"),       mrb_fixnum_value(EV3_LCD_HEIGHT));

  mrb_mod_cv_set(mrb, lcd, mrb_intern_lit(mrb, "@@font"),       mrb_fixnum_value(EV3_FONT_SMALL));

  mrb_define_class_method(mrb, lcd, "font=", mrb_lcd_set_font,    MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, lcd, "draw",  mrb_lcd_draw_string, MRB_ARGS_REQ(3));

  mrb_define_method(mrb, lcd, "initialize", mrb_lcd_init,       MRB_ARGS_OPT(6));
  mrb_define_method(mrb, lcd, "print",      mrb_lcd_print,      MRB_ARGS_ANY());
  mrb_define_method(mrb, lcd, "puts",       mrb_lcd_puts,       MRB_ARGS_ANY());
  mrb_define_method(mrb, lcd, "locate",     mrb_lcd_locate,     MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, lcd, "clear",      mrb_lcd_clear,      MRB_ARGS_OPT(1));

  mrb_define_method(mrb, lcd, "font",       mrb_lcd_get_font,   MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "left",       mrb_lcd_get_left,   MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "top",        mrb_lcd_get_top,    MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "width",      mrb_lcd_get_width,  MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "height",     mrb_lcd_get_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "cx",         mrb_lcd_get_csrx,   MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "cy",         mrb_lcd_get_csry,   MRB_ARGS_NONE());
  mrb_define_method(mrb, lcd, "color",      mrb_lcd_get_color,  MRB_ARGS_NONE());

  // mrb_undef_method(mrb, mrb->kernel_module, "__printstr__");
  // mrb_define_method(mrb, mrb->kernel_module, "__printstr__", mrb_lcd_print, MRB_ARGS_ANY());
}

#include <stdio.h>
#include <stdint.h>
#include "ev3if.h"

#ifndef EV3
typedef struct ev3_motor {
  int32_t power;
  int32_t count;
} ev3_motor;

static ev3_motor gMotor[4];

int32_t
ev3_lcd_set_font(int32_t font)
{
  return 0;
}

int32_t
ev3_font_get_size(int32_t font, int32_t *pwidth, int32_t *pheight)
{
  switch(font) {
  case 0:
    *pwidth  = 6;
    *pheight = 8;
    break;

  case 1:
  default:
    *pwidth  = 10;
    *pheight = 16;
    break;
  }
  return 0;
}

int32_t
ev3_lcd_draw_string(const char *buf, int32_t x, int32_t y)
{
  MRBEV3_PRINTF("%s", buf);
  return 0;
}

int32_t
ev3_lcd_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t color)
{
  return 0;
}

int32_t
ev3_button_is_pressed(int32_t key)
{
  return 0;
}

int32_t
ev3_led_set_color(int32_t col)
{
  return 0;
}


int32_t
ev3_motor_config(int32_t port, int32_t type)
{
  return 0;
}

int32_t
ev3_motor_set_power(int32_t port, int32_t speed)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return 0;
  }
  gMotor[port].power  = (speed > EV3_MOTOR_FMAX) ? EV3_MOTOR_FMAX
                      : (speed < EV3_MOTOR_BMAX) ? EV3_MOTOR_BMAX : speed;
  return gMotor[port].power;
}

int32_t
ev3_motor_get_power(int32_t port)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return 0;
  }
  return gMotor[port].power;
}

int32_t
ev3_motor_stop(int32_t port, int32_t brake)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return -1;
  }
  return 0;
}

int32_t
ev3_motor_rotate(int32_t port, int32_t deg, int32_t spd, int32_t blk)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return -1;
  }
  gMotor[port].count = deg;
  return 0;
}

int32_t
ev3_motor_get_counts(int32_t port)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return 0;
  }
  return gMotor[port].count;
}

int32_t
ev3_motor_reset_counts(int32_t port)
{
  if (port < 0 && port >= TNUM_MOTOR_PORT) {
    return -1;
  }
  gMotor[port].count = 0;
  return 0;
}

int
ev3_battery_current_mA(void)
{
  return 100;
}

int
ev3_battery_voltage_mV(void)
{
  return 8900;
}

int32_t
ev3_speaker_play_tone(uint16_t freq, int32_t ms)
{
  return 0;
}

int32_t
ev3_speaker_set_volume(uint8_t vol)
{
  return 0;
}

int32_t
ev3_speaker_play_file(const memfile_t *p_memfile, int32_t duration)
{
  return 0;
}

int32_t
ev3_speaker_stop(void)
{
  return 0;
}

int32_t
ev3_sensor_config(int32_t port, int32_t type)
{
  return 0;
}

int32_t
ev3_color_sensor_get_ambient(int32_t port)
{
  return 0;
}

int32_t
ev3_color_sensor_get_color(int32_t port)
{
  return 0;
}

int32_t
ev3_color_sensor_get_reflect(int32_t port)
{
  return 0;
}

void
ev3_color_sensor_get_rgb_raw(int32_t port, rgb_raw_t *prgb)
{
  prgb->r = 0;
  prgb->g = 0;
  prgb->b = 0;
}

int32_t
ev3_gyro_sensor_get_angle(int32_t port)
{
  return 0;
}

int32_t
ev3_gyro_sensor_get_rate(int32_t port)
{
  return 0;
}

int32_t
ev3_gyro_sensor_reset(int32_t port)
{
  return 0;
}

int32_t
ev3_touch_sensor_is_pressed(int32_t port)
{
  return 0;
}

int32_t
ev3_ultrasonic_sensor_get_distance(int32_t port)
{
  return 0;
}

int32_t
ev3_sdcard_opendir(const char *path)
{
  return 0;
}

int32_t
ev3_sdcard_readdir(int32_t dirid, fileinfo_t *p_fileinfo)
{
  return 0;
}

int32_t
ev3_sdcard_closedir(int32_t dirid)
{
  return 0;
}

int32_t
ev3_memfile_load(const char *path, memfile_t *p_memfile)
{
  return 0;
}

int32_t
ev3_memfile_free(memfile_t *p_memfile)
{
  return 0;
}

static FILE *
__fopen(const char *path)
{
  FILE *fp = fopen(path, "r+");
  if (fp == NULL) {
    fp = fopen(path, "w+");
  }
  return fp;
}

FILE *
ev3_serial_open_file(serial_port_t port)
{
  switch(port) {
  case EV3_SERIAL_DEFAULT:  return __fopen("./port0");
  case EV3_SERIAL_UART:     return __fopen("./port1");
  case EV3_SERIAL_BT:       return __fopen("./port2");
  default:                  break;
  }
  return NULL;
}

int32_t
ev3_ultrasonic_sensor_listen(int32_t port)
{
  return 0;
}

void balance_init(void)
{
}

void balance_control(float forward, float turn,
  float gyro, float gyro_offset,
  float theta_l, float theta_r, float battery,
  signed char *pwm_l, signed char *pwm_r)
{
  *pwm_l = *pwm_r = 0;
}

#endif

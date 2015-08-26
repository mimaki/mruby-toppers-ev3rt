#ifndef _EV3IF_H
#define _EV3IF_H

#include <stdio.h>

#define EV3_LCD_WIDTH   178
#define EV3_LCD_HEIGHT  128

#define EV3_FONT_SMALL  0   /*  6x 8 pixels */
#define EV3_FONT_MEDIUM 1   /* 10x16 pixels */

#define EV3_LCD_WHITE   0
#define EV3_LCD_BLACK   1

#define EV3_MOTOR_FMAX  (100)
#define EV3_MOTOR_BMAX  (-100)

#define NOTE_C4  (261.63)  //!< \~English Frequency of musical note C4  \~Japanese ノートC4の周波数
#define NOTE_CS4 (277.18)  //!< \~English Frequency of musical note C#4 \~Japanese ノートC#4の周波数
#define NOTE_D4  (293.66)  //!< \~English Frequency of musical note D4  \~Japanese ノートD4の周波数
#define NOTE_DS4 (311.13)  //!< \~English Frequency of musical note D#4 \~Japanese ノートD#4の周波数
#define NOTE_E4  (329.63)  //!< \~English Frequency of musical note E4  \~Japanese ノートE4の周波数
#define NOTE_F4  (349.23)  //!< \~English Frequency of musical note F4  \~Japanese ノートF4の周波数
#define NOTE_FS4 (369.99)  //!< \~English Frequency of musical note F#4 \~Japanese ノートF#4の周波数
#define NOTE_G4  (392.00)  //!< \~English Frequency of musical note G4  \~Japanese ノートG4の周波数
#define NOTE_GS4 (415.30)  //!< \~English Frequency of musical note G#4 \~Japanese ノートG#4の周波数
#define NOTE_A4  (440.00)  //!< \~English Frequency of musical note A4  \~Japanese ノートA4の周波数
#define NOTE_AS4 (466.16)  //!< \~English Frequency of musical note A#4 \~Japanese ノートA#4の周波数
#define NOTE_B4  (493.88)  //!< \~English Frequency of musical note B4  \~Japanese ノートB4の周波数
#define NOTE_C5  (523.25)  //!< \~English Frequency of musical note C5  \~Japanese ノートC5の周波数
#define NOTE_CS5 (554.37)  //!< \~English Frequency of musical note C#5 \~Japanese ノートC#5の周波数
#define NOTE_D5  (587.33)  //!< \~English Frequency of musical note D5  \~Japanese ノートD5の周波数
#define NOTE_DS5 (622.25)  //!< \~English Frequency of musical note D#5 \~Japanese ノートD#5の周波数
#define NOTE_E5  (659.25)  //!< \~English Frequency of musical note E5  \~Japanese ノートE5の周波数
#define NOTE_F5  (698.46)  //!< \~English Frequency of musical note F5  \~Japanese ノートF5の周波数
#define NOTE_FS5 (739.99)  //!< \~English Frequency of musical note F#5 \~Japanese ノートF#5の周波数
#define NOTE_G5  (783.99)  //!< \~English Frequency of musical note G5  \~Japanese ノートG5の周波数
#define NOTE_GS5 (830.61)  //!< \~English Frequency of musical note G#5 \~Japanese ノートG#5の周波数
#define NOTE_A5  (880.00)  //!< \~English Frequency of musical note A5  \~Japanese ノートA5の周波数
#define NOTE_AS5 (932.33)  //!< \~English Frequency of musical note A#5 \~Japanese ノートA#5の周波数
#define NOTE_B5  (987.77)  //!< \~English Frequency of musical note B5  \~Japanese ノートB5の周波数
#define NOTE_C6  (1046.50) //!< \~English Frequency of musical note C6  \~Japanese ノートC6の周波数
#define NOTE_CS6 (1108.73) //!< \~English Frequency of musical note C#6 \~Japanese ノートC#6の周波数
#define NOTE_D6  (1174.66) //!< \~English Frequency of musical note D6  \~Japanese ノートD6の周波数
#define NOTE_DS6 (1244.51) //!< \~English Frequency of musical note D#6 \~Japanese ノートD#6の周波数
#define NOTE_E6  (1318.51) //!< \~English Frequency of musical note E6  \~Japanese ノートE6の周波数
#define NOTE_F6  (1396.91) //!< \~English Frequency of musical note F6  \~Japanese ノートF6の周波数
#define NOTE_FS6 (1479.98) //!< \~English Frequency of musical note F#6 \~Japanese ノートF#6の周波数
#define NOTE_G6  (1567.98) //!< \~English Frequency of musical note G6  \~Japanese ノートG6の周波数
#define NOTE_GS6 (1661.22) //!< \~English Frequency of musical note G#6 \~Japanese ノートG#6の周波数
#define NOTE_A6  (1760.00) //!< \~English Frequency of musical note A6  \~Japanese ノートA6の周波数
#define NOTE_AS6 (1864.66) //!< \~English Frequency of musical note A#6 \~Japanese ノートA#6の周波数
#define NOTE_B6  (1975.53) //!< \~English Frequency of musical note B6  \~Japanese ノートB6の周波数
#define NOTE_C6  (1046.50) //!< \~English Frequency of musical note C6  \~Japanese ノートC6の周波数
#define NOTE_CS6 (1108.73) //!< \~English Frequency of musical note C#6 \~Japanese ノートC#6の周波数
#define NOTE_D6  (1174.66) //!< \~English Frequency of musical note D6  \~Japanese ノートD6の周波数
#define NOTE_DS6 (1244.51) //!< \~English Frequency of musical note D#6 \~Japanese ノートD#6の周波数
#define NOTE_E6  (1318.51) //!< \~English Frequency of musical note E6  \~Japanese ノートE6の周波数
#define NOTE_F6  (1396.91) //!< \~English Frequency of musical note F6  \~Japanese ノートF6の周波数
#define NOTE_FS6 (1479.98) //!< \~English Frequency of musical note F#6 \~Japanese ノートF#6の周波数
#define NOTE_G6  (1567.98) //!< \~English Frequency of musical note G6  \~Japanese ノートG6の周波数
#define NOTE_GS6 (1661.22) //!< \~English Frequency of musical note G#6 \~Japanese ノートG#6の周波数
#define NOTE_A6  (1760.00) //!< \~English Frequency of musical note A6  \~Japanese ノートA6の周波数
#define NOTE_AS6 (1864.66) //!< \~English Frequency of musical note A#6 \~Japanese ノートA#6の周波数
#define NOTE_B6  (1975.53) //!< \~English Frequency of musical note B6  \~Japanese ノートB6の周波数

// #define MRUBY_EV3_DEBUG
#ifdef MRUBY_EV3_DEBUG
  #define MRBEV3_PRINTF(fmt, ...) printf(fmt, __VA_ARGS__)
  #define MRBEV3_PUTS(x) puts(x)
#else
  #define MRBEV3_PRINTF(...)
  #define MRBEV3_PUTS(x)
#endif

typedef void (*ISR)(intptr_t);

typedef struct {
	void*    buffer;   //!< \~English Pointer of the buffer where this file is stored. NULL means a invalid memory file. \~Japanese このファイルが格納されているバッファへのポインタ．NULLは無効なメモリファイル．
	uint32_t filesz;   //!< \~English Actual size of this file	 					                                     \~Japanese ファイルの実際のサイズ
	uint32_t buffersz; //!< \~English Maximum size of the buffer to store this file   									 \~Japanese バッファの最大サイズ
} memfile_t;

#define	TMAX_FILENAME_LEN (255)    //!< \~English Maximum length of a file name \~Japanese ファイル名の最大の長さ

typedef struct {
	uint32_t size;							//!< \~English File size          \~Japanese ファイルのサイズ
	uint16_t date;							//!< \~English Last modified date \~Japanese ファイルのLast modified date
	uint16_t time;							//!< \~English Last modified time \~Japanese ファイルのLast modified time
  int is_dir;                        //!< \~English Flag of a folder   \~Japanese フォルダであることを表すフラグ
  int is_readonly;                   //!< \~English Flag of read-only  \~Japanese 読み出し専用であることを表すフラグ
  int is_hidden;                     //!< \~English Flag of hidden     \~Japanese 隠しファイルであることを表すフラグ
	char	 name[TMAX_FILENAME_LEN + 1];	//!< \~English File name          \~Japanese ファイル名
} fileinfo_t;

typedef enum {
    LEFT_BUTTON  = 0, //!< \~English Left button       \~Japanese 左ボタン
    RIGHT_BUTTON = 1, //!< \~English Right button    \~Japanese 右ボタン
    UP_BUTTON    = 2, //!< \~English Up button         \~Japanese 上ボタン
    DOWN_BUTTON  = 3, //!< \~English Down button       \~Japanese 下ボタン
    ENTER_BUTTON = 4, //!< \~English Enter button      \~Japanese 中央ボタン
    BACK_BUTTON  = 5, //!< \~English Back button       \~Japanese 戻るボタン
    TNUM_BUTTON  = 6, //!< \~English Number of buttons \~Japanese ボタンの数
} button_t;

typedef enum {
  LED_OFF    = 0,           //!< \~English Turn off \~Japanese オフにする
  LED_RED    = 1 << 0,        //!< \~English Red      \~Japanese 赤
  LED_GREEN  = 1 << 1,        //!< \~English Green    \~Japanese 緑
  LED_ORANGE = LED_RED | LED_GREEN, //!< \~English Orange   \~Japanese オレンジ色
} ledcolor_t;

typedef enum {
  EV3_PORT_A = 0,   //!< \~English Port A        \~Japanese ポートA
  EV3_PORT_B = 1,   //!< \~English Port B          \~Japanese ポートB
  EV3_PORT_C = 2,   //!< \~English Port C          \~Japanese ポートC
  EV3_PORT_D = 3,   //!< \~English Port D            \~Japanese ポートD
  TNUM_MOTOR_PORT = 4 //!< \~English Number of motor ports \~Japanese モータポートの数
} motor_port_t;

typedef enum {
  NONE_MOTOR = 0,    //!< \~English Not connected         \~Japanese モータ未接続
  MEDIUM_MOTOR,    //!< \~English Medium servo motor    \~Japanese サーボモータM
  LARGE_MOTOR,     //!< \~English Large servo motor     \~Japanese サーボモータL
  UNREGULATED_MOTOR, //!< \~English Unregulated motor     \~Japanese 未調整モータ
  TNUM_MOTOR_TYPE    //!< \~English Number of motor types \~Japanese モータタイプの数
} motor_type_t;/* EV3 API wrapper functions */

typedef enum {
    EV3_PORT_1 = 0,     //!< \~English Port 1           \~Japanese ポート1
    EV3_PORT_2 = 1,       //!< \~English Port 2               \~Japanese ポート2
    EV3_PORT_3 = 2,     //!< \~English Port 3             \~Japanese ポート3
    EV3_PORT_4 = 3,       //!< \~English Port 4           \~Japanese ポート4
    TNUM_SENSOR_PORT = 4, //!< \~English Number of sensor ports \~Japanese センサポートの数
} sensor_port_t;

typedef enum {
    NONE_SENSOR = 0,   //!< \~English Not connected      \~Japanese センサ未接続
    ULTRASONIC_SENSOR, //!< \~English Ultrasonic sensor    \~Japanese 超音波センサ
    GYRO_SENSOR,     //!< \~English Gyroscope sensor     \~Japanese ジャイロセンサ
    TOUCH_SENSOR,    //!< \~English Touch sensor       \~Japanese タッチセンサ
    COLOR_SENSOR,    //!< \~English Color sensor       \~Japanese カラーセンサ
    TNUM_SENSOR_TYPE   //!< \~English Number of sensor types \~Japanese センサタイプの数
} sensor_type_t;

typedef enum {
    COLOR_NONE   = 0, //!< \~English None         \~Japanese 無色
    COLOR_BLACK  = 1, //!< \~English Black        \~Japanese 黒
    COLOR_BLUE   = 2, //!< \~English Blue         \~Japanese 青
    COLOR_GREEN  = 3, //!< \~English Green        \~Japanese 緑
    COLOR_YELLOW = 4, //!< \~English Yellow       \~Japanese 黄
    COLOR_RED    = 5, //!< \~English Red          \~Japanese 赤
    COLOR_WHITE  = 6, //!< \~English White          \~Japanese 白
    COLOR_BROWN  = 7, //!< \~English Brown        \~Japanese 茶
    TNUM_COLOR      //!< \~English Number of colors \~Japanese 識別できるカラーの数
} colorid_t;

typedef enum {
    EV3_SERIAL_DEFAULT = 0, //!< \~English Default SIO port     \~Japanese デフォルトのシリアルポート（ログタスク用ポート）
    EV3_SERIAL_UART = 1,	//!< \~English UART (Sensor port 1) \~Japanese UARTポート（センサポート1）
    EV3_SERIAL_BT = 2,	    //!< \~English Bluetooth SPP        \~Japanese Bluetooth仮想シリアルポート
} serial_port_t;

/* LCD */
int32_t ev3_lcd_set_font(int32_t);
int32_t ev3_font_get_size(int32_t, int32_t*, int32_t*);
int32_t ev3_lcd_draw_string(const char*, int32_t, int32_t);
int32_t ev3_lcd_fill_rect(int32_t, int32_t, int32_t, int32_t, int32_t);
/* Button */
int32_t ev3_button_is_pressed(int32_t);
int32_t ev3_button_set_on_clicked(int32_t, ISR, intptr_t);
/* Battery */
int ev3_battery_current_mA(void);
int ev3_battery_voltage_mV(void);
/* LED */
int32_t ev3_led_set_color(int32_t);
/* Sound */
int32_t ev3_speaker_play_tone(uint16_t, int32_t);
int32_t ev3_speaker_set_volume(uint8_t);
int32_t ev3_speaker_play_file(const memfile_t*, int32_t);
int32_t ev3_speaker_stop(void);
/* Motor */
int32_t ev3_motor_config(int32_t, int32_t);
int32_t ev3_motor_set_power(int32_t, int32_t);
int32_t ev3_motor_get_power(int32_t);
int32_t ev3_motor_stop(int32_t, int32_t);
int32_t ev3_motor_rotate(int32_t, int32_t, int32_t, int32_t);
int32_t ev3_motor_get_counts(int32_t);
int32_t ev3_motor_reset_counts(int32_t);
/* Sensor */
int32_t ev3_sensor_config(int32_t, int32_t);
int32_t ev3_color_sensor_get_ambient(int32_t);
int32_t ev3_color_sensor_get_color(int32_t);
int32_t ev3_color_sensor_get_reflect(int32_t);
int32_t ev3_gyro_sensor_get_angle(int32_t);
int32_t ev3_gyro_sensor_get_rate(int32_t);
int32_t ev3_gyro_sensor_reset(int32_t);
int32_t ev3_touch_sensor_is_pressed(int32_t);
int32_t ev3_ultrasonic_sensor_get_distance(int32_t);
int32_t ev3_ultrasonic_sensor_listen(int32_t);
/* File System */
int32_t ev3_sdcard_opendir(const char*);
int32_t ev3_sdcard_readdir(int32_t, fileinfo_t*);
int32_t ev3_sdcard_closedir(int32_t);
int32_t ev3_memfile_load(const char*, memfile_t*);
int32_t ev3_memfile_free(memfile_t*);
FILE* ev3_serial_open_file(serial_port_t);
/* balancer.c */
void balance_init(void);
void balance_control(float, float, float, float, float, float, float,
  signed char*, signed char*);

#endif /* _EV3IF_H */

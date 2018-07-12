mruby-toppers-ev3rt
===

[TOPPERS/EV3RT](http://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT) library for mruby.

## Classes and methods

### EV3RT::Balancer
|method|description|
|:--|:--|
|Balancer.new|Initialize balancer|
|Balancer#control|Call balancer API|
|Balancer#reset|Reset balancer|

### EV3RT::Battery
|method|description|
|:--|:--|
|Battery.mA|Get the current draw from the battery|
|Battery.mV|Get battery battery voltage|

### EV3RT::Button  
|method|description|
|:--|:--|
|Button.new|Create Button object|
|Button.[]|Get Button object|
|Button#pressed?|Get button status|

### EV3RT::GyroSensor
|method|description|
|:--|:--|
|GyroSensor.new|Create GyroSensor object|
|GyroSensor#angle|Get gyro angle|
|GyroSensor#rate|Get gyro rate|
|GyroSensor#reset|Reset gyro sensor|
|GyroSensor#calibrate|calibrate gyro sensor|
|GyroSensor#offset|Get gyro offset|

### EV3RT::LCD
|method|description|
|:--|:--|
|LCD.new|Initialize LCD|
|LCD#font=|Set current font size|
|LCD#font|Get current font size|
|LCD#left|Get X-coordinate of screen left|
|LCD#top|Get Y-coordinate of screen top|
|LCD#width|Get screen width (pixels)|
|LCD#csrx|Get X-charactor-coordinate of cursor|
|LCD#csry|Get Y-charactor-coordinate of cursor|
|LCD#color=|Set foreground color|
|LCD#print|Prints the string at cursor position on window|
|LCD#puts|Puts the string that added newline at current cursor position on window|
|LCD#draw|Draw the string at specified coordinate of LCD|
|LCD#locate|Set the cursor position on window|
|LCD#clear|Clear window|

### EV3RT::LED
|method|description|
|:--|:--|
|LED.color=c|Light LED|
|LED.off|LED turn off|

### EV3RT::Motor
|method|description|
|:--|:--|
|Motor.new|Create Motor object|
|Motor#power=|Sets motor power|
|Motor#power|Gets motor current power|
|Motor#stop|Stop the motor|
|Motor#rotate|Rotate the motor|
|Motor#count|Get motor counter|
|Motor#reset|Resets motor counter|

### EV3RT::ColorSensor
|method|description|
|:--|:--|
|ColorSensor.new|Create ColorSensor object|
|ColorSensor#ambient|Get ambient light level|
|ColorSensor#color|Get color|
|ColorSensor#reflect|Get reflected light level from red lED|
|ColorSensor#black?|It is determined whether black using the color sensor|
|ColorSensor#blue?|It is determined whether blue using the color sensor|
|ColorSensor#green?|It is determined whether green using the color sensor|
|ColorSensor#yellow?|It is determined whether yellow using the color sensor|
|ColorSensor#red?|It is determined whether red using the color sensor|
|ColorSensor#white?|It is determined whether white using the color sensor|
|ColorSensor#brown?|It is determined whether brown using the color sensor|

### EV3RT::SerialPort
|method|description|
|:--|:--|
|SerialPort.new|Open serial port|

### EV3RT::Sound
|method|description|
|:--|:--|
|Sound.tone|Play a tone, given its tone and duration|
|Sound.volume=|Set volume level|
|Sound.stop|Stop sound|

### EV3RT::TouchSensor
|method|description|
|:--|:--|
|TouchSensor.new|Create TouchSensor object|
|TouchSensor#pressed?|Get touch sensor status|

### EV3RT::UltrasonicSensor
|method|description|
|:--|:--|
|UltrasonicSensor.new|Create UltrasonicSensor object|
|UltrasonicSensor#distance|Measure distance to object in front of sensor|
|UltrasonicSensor#listen|Listen for the presence of other ultrasonic sensor|

## How to use

### 1. Prepare the files.
Please prepare the following files.

#### build_config.rb
Add the following lines to the `build_config.rb`
```ruby
# Difine arm-none-eabi build settings
MRuby::CrossBuild.new('arm-ev3rt') do |conf|
  toolchain :gccarm

  conf.build_mrbtest_lib_only

  conf.gembox 'arm-ev3rt'

  conf.cc.defines = %w(EV3)

  conf.bins = %w()
end

MRuby::CrossBuild.new('arm-ev3rt-debug') do |conf|
  toolchain :gccarm

  conf.build_mrbtest_lib_only

  enable_debug

  conf.gembox 'arm-ev3rt'

  conf.cc.defines += %w(EV3)
  conf.cc.defines += %w(ENABLE_DEBUG)

  conf.bins = %w()
end
```
#### gccarm.rake
Create `/mruby/tasks/toolchains/gccarm.rake`, writes the following lines.
```ruby
MRuby::Toolchain.new(:gccarm) do |conf|
  # C compiler settings
  [conf.cc, conf.cxx, conf.objc, conf.asm].each do |cc|
    cc.command = ENV['CC'] || 'arm-none-eabi-gcc'
    cc.flags = [ENV['CFLAGS'] || %w(
      -std=gnu99
      -mlittle-endian
      -O2
      -Wall
      -Wl,--no-warn-mismatch
    )]
    cc.defines = %w(
    )
  end

  # Archiver settings
  conf.archiver do |archiver|
    archiver.command = ENV['AR'] || 'arm-none-eabi-ar'
    archiver.archive_options = 'rcs %{outfile} %{objs}'
  end
end
```

#### arm-ev3rt.gembox
Create `/mruby/mrbgems/arm-ev3rt.gembox`, writes the following lines.
```ruby
MRuby::GemBox.new do |conf|
  (list of mrbgems you want to use...)

  # Use EV3RT libraries
  conf.gem :git => "https://github.com/mimaki/mruby-toppers-ev3rt.git"
end
```

### 2. Generate a mruby Library.
Type the `make` in `/mruby`.
`libmruby.a` is stored in `/mruby/build/arm-ev3rt/lib/`.

### 3. Link a mruby Library.
It shows an example of `Makefile.inc`.
```
LIBS += -L../../../mruby/build/arm-ev3rt/lib/ -lmruby -lm
INCLUDES += -I../../../mruby/include
```

### 4. Code the mruby of start-up program.
It shows an example of `app.c`.

```c
#include "ev3api.h"
#include "app.h"
#include "mruby.h"
#include "mruby/dump.h"
#include "mruby/hash.h"
#include "mruby/variable.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

void _fini(void)
{
}

void main_task(intptr_t unused)
{
	mrb_state *mrb = mrb_open();
	mrbc_context *c;
	FILE* rbfp;

	c = mrbc_context_new(mrb);

	rbfp = fopen("app.mrb", "rb");
	if(rbfp != 0) {
		mrb_load_irep_file_cxt(mrb, rbfp, c);
		fclose(rbfp);
	}

	mrb_close(mrb);
	ext_tsk();
}
```

## License
mruby-toppers-ev3rt is released under the [MIT License](LICENSE).

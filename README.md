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
Coming soon.

## License
MIT

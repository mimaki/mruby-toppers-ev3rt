# EV3RT::Sensor class

assert('Sensor', "class") do
  EV3RT::Sensor.class == Class
end

assert('Sensor', 'superclass') do
  EV3RT::Sensor.superclass == EV3RT::Device
end

assert('Sensor', 'PORT') do
  EV3RT::Sensor::PORT[:port_1] == 0 &&
  EV3RT::Sensor::PORT[:port_2] == 1 &&
  EV3RT::Sensor::PORT[:port_3] == 2 &&
  EV3RT::Sensor::PORT[:port_4] == 3
end

assert('Sensor', 'TYPE') do
  EV3RT::Sensor::TYPE[:ultrasonic] == 1 &&
  EV3RT::Sensor::TYPE[:gyro]       == 2 &&
  EV3RT::Sensor::TYPE[:touch]      == 3 &&
  EV3RT::Sensor::TYPE[:color]      == 4
end

assert('Sensor', 'port') do
  EV3RT::ColorSensor.new(:port_1).port       == EV3RT::Sensor::PORT[:port_1] &&
  EV3RT::GyroSensor.new("port_2").port       == EV3RT::Sensor::PORT[:port_2] &&
  EV3RT::TouchSensor.new(:port_3).port       == EV3RT::Sensor::PORT[:port_3] &&
  EV3RT::UltrasonicSensor.new("port_4").port == EV3RT::Sensor::PORT[:port_4]
end

assert('Sensor', 'type') do
  EV3RT::ColorSensor.new(:port_1).type      == EV3RT::Sensor::TYPE[:color] &&
  EV3RT::GyroSensor.new(:port_2).type       == EV3RT::Sensor::TYPE[:gyro] &&
  EV3RT::TouchSensor.new(:port_3).type      == EV3RT::Sensor::TYPE[:touch] &&
  EV3RT::UltrasonicSensor.new(:port_4).type == EV3RT::Sensor::TYPE[:ultrasonic]
end


#
# EV3RT::ColorSensor class
#

assert('ColorSensor', 'new') do
  sen = EV3RT::ColorSensor.new(:port_1)
  sen &&
  sen.class.superclass == EV3RT::Sensor
  sen.instance_variable_get("@port") == EV3RT::Sensor::PORT[:port_1] &&
  sen.instance_variable_get("@type") == EV3RT::Sensor::TYPE[:color]
end

assert('ColorSensor', 'COLOR') do
  EV3RT::ColorSensor::COLOR[:none]   == 0 &&
  EV3RT::ColorSensor::COLOR[:black]  == 1 &&
  EV3RT::ColorSensor::COLOR[:blue]   == 2 &&
  EV3RT::ColorSensor::COLOR[:green]  == 3 &&
  EV3RT::ColorSensor::COLOR[:yellow] == 4 &&
  EV3RT::ColorSensor::COLOR[:red]    == 5 &&
  EV3RT::ColorSensor::COLOR[:white]  == 6 &&
  EV3RT::ColorSensor::COLOR[:brown]  == 7
end

assert('ColorSensor', 'ambient') do
  sen = EV3RT::ColorSensor.new(:port_2)
  sen.ambient
end

assert('ColorSensor', 'color') do
  sen = EV3RT::ColorSensor.new(:port_3)
  sen.color
end

assert('ColorSensor', 'reflect') do
  sen = EV3RT::ColorSensor.new(:port_4)
  sen.reflect
end

assert('ColorSensor', 'rgb') do
  sen = EV3RT::ColorSensor.new(:port_1)
  rgb = sen.rgb
  rgb.class == Array &&
  rgb.size == 3 #&&
  rgb[0].class == Fixnum &&
  rgb[1].class == Fixnum &&
  rgb[2].class == Fixnum
end

assert('ColorSensor', 'black?') do
  EV3RT::ColorSensor.new(:port_1).black? == false
end

assert('ColorSensor', 'blue?') do
  EV3RT::ColorSensor.new(:port_1).blue? == false
end

assert('ColorSensor', 'green?') do
  EV3RT::ColorSensor.new(:port_1).green? == false
end

assert('ColorSensor', 'yellow?') do
  EV3RT::ColorSensor.new(:port_1).yellow? == false
end

assert('ColorSensor', 'red?') do
  EV3RT::ColorSensor.new(:port_1).red? == false
end

assert('ColorSensor', 'white?') do
  EV3RT::ColorSensor.new(:port_1).white? == false
end

assert('ColorSensor', 'brown?') do
  EV3RT::ColorSensor.new(:port_1).brown? == false
end

#
# EV3RT::GyroSensor class
#

assert('GyroSensor', 'new') do
  sen = EV3RT::GyroSensor.new(:port_1)
  sen &&
  sen.class.superclass == EV3RT::Sensor
  sen.instance_variable_get("@port") == EV3RT::Sensor::PORT[:port_1] &&
  sen.instance_variable_get("@type") == EV3RT::Sensor::TYPE[:gyro]
end

assert('GyroSensor', 'angle') do
  sen = EV3RT::GyroSensor.new(:port_2)
  sen.angle
end

assert('GyroSensor', 'rate') do
  sen = EV3RT::GyroSensor.new(:port_3)
  sen.rate
end

assert('GyroSensor', 'reset') do
  sen = EV3RT::GyroSensor.new(:port_4)
  sen.reset == nil
end

assert('GyroSensor', 'calibrate') do
  sen = EV3RT::GyroSensor.new(:port_1)
  sen.calibrate == nil
end

assert('GyroSensor', 'offset') do
  sen = EV3RT::GyroSensor.new(:port_2)
  sen.offset
end


#
# EV3RT::TouchSensor class
#

assert('TouchSensor', 'new') do
  sen = EV3RT::TouchSensor.new(:port_1)
  sen &&
  sen.class.superclass == EV3RT::Sensor
  sen.instance_variable_get("@port") == EV3RT::Sensor::PORT[:port_1] &&
  sen.instance_variable_get("@type") == EV3RT::Sensor::TYPE[:touch]
end

assert('TouchSensor', 'pressed?') do
  sen = EV3RT::TouchSensor.new(:port_2)
  sen.pressed? == false
end


#
# EV3RT::UltrasonicSensor class
#

assert('UltrasonicSensor', 'new') do
  sen = EV3RT::UltrasonicSensor.new(:port_1)
  sen &&
  sen.class.superclass == EV3RT::Sensor
  sen.instance_variable_get("@port") == EV3RT::Sensor::PORT[:port_1] &&
  sen.instance_variable_get("@type") == EV3RT::Sensor::TYPE[:ultrasonic]
end

assert('UltrasonicSensor', 'distance') do
  sen = EV3RT::UltrasonicSensor.new(:port_2)
  sen.distance
end

assert('UltrasonicSensor', 'listen') do
  sen = EV3RT::UltrasonicSensor.new(:port_3)
  sen.listen == false
end

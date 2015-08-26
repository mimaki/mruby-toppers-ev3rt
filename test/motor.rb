# EV3RT::Motor class

assert('Motor', "class") do
  EV3RT::Motor.class == Class
end

assert('Motor', 'superclass') do
  EV3RT::Motor.superclass == EV3RT::Device
end

assert('Motor', 'PORT') do
  EV3RT::Motor::PORT[:port_a] == 0 &&
  EV3RT::Motor::PORT[:port_b] == 1 &&
  EV3RT::Motor::PORT[:port_c] == 2 &&
  EV3RT::Motor::PORT[:port_d] == 3
end

assert('Motor', 'TYPE') do
  EV3RT::Motor::TYPE[:medium]  == 1 &&
  EV3RT::Motor::TYPE[:large]   == 2 &&
  EV3RT::Motor::TYPE[:unknown] == 3
end

assert('Motor', 'new') do
  mtr = []
  mtr << EV3RT::Motor.new(:port_a)
  mtr << EV3RT::Motor.new("port_b", "medium")
  mtr << EV3RT::Motor.new(:port_c,  "large")
  mtr << EV3RT::Motor.new("port_d", "unknown")
  mtr.size == 4
end

assert('Motor', 'new: parameter error') do
  e1 = e2 = nil
  begin
    EV3RT::Motor.new
  rescue => e1
  end
  begin
    EV3RT::Motor.new(:port_a)
  rescue => e2
  end
  e1 && !e2
end

assert('Motor', 'port') do
  EV3RT::Motor.new(:port_a).port == EV3RT::Motor::PORT[:port_a] &&
  EV3RT::Motor.new(:port_b).port == EV3RT::Motor::PORT[:port_b] &&
  EV3RT::Motor.new(:port_c).port == EV3RT::Motor::PORT[:port_c] &&
  EV3RT::Motor.new(:port_d).port == EV3RT::Motor::PORT[:port_d]
end

assert('Motor', 'type') do
  EV3RT::Motor.new(:port_a).type           == EV3RT::Motor::TYPE[:large] &&
  EV3RT::Motor.new(:port_b, :medium).type  == EV3RT::Motor::TYPE[:medium] &&
  EV3RT::Motor.new(:port_c, :large).type   == EV3RT::Motor::TYPE[:large] &&
  EV3RT::Motor.new(:port_d, :unknown).type == EV3RT::Motor::TYPE[:unknown]
end

assert('Motor', 'power') do
  b = true
  mtr = EV3RT::Motor.new(:port_a)
  [0, 100, -100, 200, -200].each {|pwr|
    mtr.power = pwr
    pwr = 100 if pwr > 100
    pwr = -100 if pwr < -100
    b &= (mtr.power == pwr)
  }
  b
end

assert('Motor', 'stop') do
  e = nil
  begin
    mtr = EV3RT::Motor.new(:port_a)
    mtr.stop
    mtr.stop(true)
  rescue => e
  end
  !e
end

assert('Motor', 'rotate') do
  mtr = EV3RT::Motor.new(:port_a)
  mtr.rotate(10, 20)
  b = (mtr.count == 10)
  mtr.rotate(-100, 100, 1)
  b & (mtr.count == -100)
end

assert('Motor', 'rotate: parameter error') do
  mtr = EV3RT::Motor.new(:port_a)
  e1 = e2 = nil
  begin
    mtr.rotate
  rescue => e1
  end
  begin
    mtr.rotate(10)
  rescue => e2
  end
  e1 && e2
end

assert('Motor', 'count') do
  mtr = EV3RT::Motor.new(:port_a)
  mtr.rotate(123, 100)
  mtr.count == 123
end

assert('Motor', 'reset_count') do
  mtr = EV3RT::Motor.new(:port_a)
  mtr.rotate(10, 20)
  mtr.reset_count
  mtr.count == 0
end

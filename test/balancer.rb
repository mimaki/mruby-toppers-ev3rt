# EV3RT::Balancer class

assert('Balancer', "class") do
  EV3RT::Balancer.class == Class
end

assert('Balancer', 'new') do
  EV3RT::Balancer.new
end

assert('Balancer', 'reset') do
  EV3RT::Balancer.new.reset
end

assert('Balancer', "control") do
  pwm = EV3RT::Balancer.new.control(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0)
  pwm.class == Array &&
  pwm.size == 2
end

assert('Balancer', "control: parameter error") do
  bal = EV3RT::Balancer.new
  eary = []
  begin
    bal.control
  rescue => e
    eary << e
  end
  begin
    bal.control(1.0)
  rescue => e
    eary << e
  end
  begin
    bal.control(1.0, 2.0, 3.0, 4.0, 5.0, 6.0)
  rescue => e
    eary << e
  end
  begin
    bal.control(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0)
  rescue => e
    eary << e
  end
  eary.size == 4
end

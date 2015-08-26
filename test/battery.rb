# EV3RT::Battery class

assert('Battery', "class") do
  EV3RT::Battery.class == Class
end

assert('Battery', "mA") do
  EV3RT::Battery.mA.class == Fixnum
end

assert('Battery', "mV") do
  EV3RT::Battery.mV.class == Fixnum
end

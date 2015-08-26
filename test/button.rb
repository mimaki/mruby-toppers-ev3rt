# EV3RT::Button class

assert('Button', "class") do
  EV3RT::Button.class == Class
end

assert('Button', 'new') do
  bl = EV3RT::Button.new(:left)
  br = EV3RT::Button.new(:right)
  bu = EV3RT::Button.new(:up)
  bd = EV3RT::Button.new(:down)
  be = EV3RT::Button.new(:enter)
  bb = EV3RT::Button.new(:back)
  bl.instance_variable_get('@key') == 0 &&
  br.instance_variable_get('@key') == 1 &&
  bu.instance_variable_get('@key') == 2 &&
  bd.instance_variable_get('@key') == 3 &&
  be.instance_variable_get('@key') == 4 &&
  bb.instance_variable_get('@key') == 5
end

assert('Button', '[]') do
  bl = EV3RT::Button[:left]
  br = EV3RT::Button[:right]
  bu = EV3RT::Button[:up]
  bd = EV3RT::Button[:down]
  be = EV3RT::Button[:enter]
  bb = EV3RT::Button[:back]
  bl.instance_variable_get('@key') == 0 &&
  br.instance_variable_get('@key') == 1 &&
  bu.instance_variable_get('@key') == 2 &&
  bd.instance_variable_get('@key') == 3 &&
  be.instance_variable_get('@key') == 4 &&
  bb.instance_variable_get('@key') == 5
end

assert('Button', 'pressed?') do
  EV3RT::Button[:left].pressed?  == false &&
  EV3RT::Button[:right].pressed? == false &&
  EV3RT::Button[:up].pressed?    == false &&
  EV3RT::Button[:down].pressed?  == false &&
  EV3RT::Button[:enter].pressed? == false &&
  EV3RT::Button[:back].pressed?  == false
end

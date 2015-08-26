# EV3RT::LED class

assert('LED', "class") do
  EV3RT::LED.class == Class
end

assert('LED', 'COLOR') do
  EV3RT::LED.const_defined?(:COLOR) &&
  EV3RT::LED::COLOR[:off]    == 0 &&
  EV3RT::LED::COLOR[:red]    == 1 &&
  EV3RT::LED::COLOR[:green]  == 2 &&
  EV3RT::LED::COLOR[:orange] == 3
end

assert('LED', "color=") do
  e = nil
  begin
    EV3RT::LED.color = :red
    EV3RT::LED.color = :green
    EV3RT::LED.color = :orange
    EV3RT::LED.color = :off
  rescue => e
  end
  !e
end

assert('LED', "off") do
  e = nil
  begin
    EV3RT::LED.off
  rescue => e
  end
  !e
end

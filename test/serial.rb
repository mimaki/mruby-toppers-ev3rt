# EV3RT::Serial class

assert('SerialPort', "class") do
  EV3RT::SerialPort.class == Class
end

assert('SerialPort', 'superclass') do
  EV3RT::SerialPort.superclass == File
end

assert('SerialPort', 'PORT') do
  EV3RT::SerialPort::PORT[:default] == 0 &&
  EV3RT::SerialPort::PORT[:uart]    == 1 &&
  EV3RT::SerialPort::PORT[:bt]      == 2
end

assert('SerialPort', 'new :default') do
  f = EV3RT::SerialPort.new(:default)
  b = (f.class == EV3RT::SerialPort)
  f.close
  b
end

assert('SerialPort', 'new :uart') do
  f = EV3RT::SerialPort.new(:uart)
  b = (f.class == EV3RT::SerialPort)
  f.close
  b
end

assert('SerialPort', 'new :bt') do
  f = EV3RT::SerialPort.new(:bt)
  b = (f.class == EV3RT::SerialPort)
  f.close
  b
end

assert('SerialPort', 'new :unknown') do
  e = nil
  begin
    EV3RT::SerialPort.new(:unknown)
  rescue => e
  end
  e.class == ArgumentError
end

assert('SerialPort', "read/write") do
  t = "1234567890\nabcdefghijklmnopqrstuvwxyz"
  s = ''
  EV3RT::SerialPort.open(:bt) {|f|
    f.write(t)
  }
  EV3RT::SerialPort.open(:bt) {|f|
    s = f.read
  }
  t == s
end

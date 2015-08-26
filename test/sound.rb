# EV3RT::Sound class

assert('Sound', "class") do
  EV3RT::Sound.class == Class
end

assert('Sound', 'TONE') do
  EV3RT::Sound.const_defined?(:TONE) #&&
  EV3RT::Sound::TONE[:c4]
end

assert('Sound', 'tone') do
  EV3RT::Sound.tone(0,    0) == nil &&
  EV3RT::Sound.tone(0.0,  0) == nil &&
  EV3RT::Sound.tone(:d4,  0) == nil &&
  EV3RT::Sound.tone("d5", 0) == nil
end

assert('Sound', 'tone: parameter error') do
  e1 = e2 = nil
  begin
    EV3RT::Sound.tone
  rescue => e1
  end
  begin
    EV3RT::Sound.tone(1)
  rescue => e2
  end
  e1 && e2
end

assert('Sound', 'tone: Unknown tone') do
  e = nil
  begin
    EV3RT::Sound.tone(:unknown, 0)
  rescue => e
  end
  e.class == ArgumentError
end

assert('Sound', 'volume=') do
  e = nil
  begin
    EV3RT::Sound.volume = 0
    EV3RT::Sound.volume = 100
    EV3RT::Sound.volume = 101
  rescue => e
  end
  !e
end

assert('Sound', 'stop') do
  e = nil
  begin
    EV3RT::Sound.stop
  rescue => e
  end
  !e
end

# EV3RT::LCD class

assert('LCD', "class") do
  EV3RT::LCD.class == Class
end

assert('LCD', 'WIDTH/HEIGHT') do
  EV3RT::LCD.const_defined?(:WIDTH) &&
  EV3RT::LCD.const_defined?(:HEIGHT)
end

assert('LCD', 'FONT') do
  EV3RT::LCD.const_defined?(:FONT) &&
  EV3RT::LCD::FONT[:small] &&
  EV3RT::LCD::FONT[:medium]
end

assert('LCD', 'COLOR') do
  EV3RT::LCD.const_defined?(:COLOR) &&
  EV3RT::LCD::COLOR[:white] &&
  EV3RT::LCD::COLOR[:black]
end


#
# LCD#cx, cy
#
assert('LCD', 'cx/cy') do
  lcd = EV3RT::LCD.new
  lcd.cx == 0 && lcd.cy == 0
end


#
# LCD#locate
#
assert('LCD', 'locate(x, y)') do
  lcd = EV3RT::LCD.new
  lcd.locate(1, 2)
  lcd.cx == 1 && lcd.cy == 2
end

assert('LCD', 'locate(x)') do
  lcd = EV3RT::LCD.new
  lcd.locate(1, 2)
  lcd.locate(10)
  lcd.cx == 10 && lcd.cy == 2
end

assert('LCD', 'puts+locate') do
  lcd = EV3RT::LCD.new
  lcd.locate(2, 4)
  lcd.puts "abcde\n12345567890"
  lcd.locate(1, 2)
  lcd.cx == 1 && lcd.cy == 2
end


#
# LCD.#new
#
assert('LCD', 'new') do
  l1 = EV3RT::LCD.new
  # l1.instance_variable_get('@font')   == EV3RT::LCD::FONT[:small] &&
  l1.font == EV3RT::LCD::FONT[:small] &&
  # l1.instance_variable_get('@left')   == 0 &&
  # l1.instance_variable_get('@top')    == 0 &&
  l1.left   == 0 &&
  l1.top    == 0 &&
  # l1.instance_variable_get('@width')  == EV3RT::LCD::WIDTH &&
  # l1.instance_variable_get('@height') == EV3RT::LCD::HEIGHT &&
  l1.width  == EV3RT::LCD::WIDTH &&
  l1.height == EV3RT::LCD::HEIGHT &&
  # l1.instance_variable_get('@color')  == EV3RT::LCD::COLOR[:black]
  l1.color  == EV3RT::LCD::COLOR[:black]
end

assert('LCD', 'new(font)') do
  l1 = EV3RT::LCD.new(:small)
  l2 = EV3RT::LCD.new(:medium)
  # l1.instance_variable_get('@font') == EV3RT::LCD::FONT[:small]
  l1.font == EV3RT::LCD::FONT[:small] &&
  # l2.instance_variable_get('@font') == EV3RT::LCD::FONT[:medium]
  l2.font == EV3RT::LCD::FONT[:medium]
end

assert('LCD', 'new(font, x, y, w, h)') do
  l1 = EV3RT::LCD.new(:small, 1, 2, 3, 4)
  l1.left   == 1 &&
  l1.top    == 2 &&
  l1.width  == 3 &&
  l1.height == 4
end

assert('LCD', 'new(font, x, y, w, h, col)') do
  l1 = EV3RT::LCD.new(:small, 1, 2, 3, 4, :white)
  l2 = EV3RT::LCD.new(:small, 1, 2, 3, 4, :black)
  # l1.instance_variable_get('@color') == EV3RT::LCD::COLOR[:white] &&
  # l2.instance_variable_get('@color') == EV3RT::LCD::COLOR[:black]
  l1.color == EV3RT::LCD::COLOR[:white] &&
  l2.color == EV3RT::LCD::COLOR[:black]
end

#
# LCD#print
#
assert('LCD', 'print') do
  lcd = EV3RT::LCD.new
  lcd.print
  lcd.cx == 0 && lcd.cy == 0
end

assert('LCD', 'print: single line') do
  lcd = EV3RT::LCD.new
  lcd.print '1234567890'
  lcd.cx == 10 && lcd.cy == 0
  true
end

assert('LCD', 'print: multiple line') do
  lcd = EV3RT::LCD.new
  lcd.print '123456789012345678901234567890'
  lcd.cx == 1 && lcd.cy == 1
end

assert('LCD', "print: multiple parameters") do
  lcd = EV3RT::LCD.new
  lcd.print 1, "234", [6, 9]
  lcd.cx == 10 && lcd.cy == 0
end

assert('LCD', 'print: line feed') do
  lcd = EV3RT::LCD.new
  lcd.print "1234567890\n12345678901234567890"
  lcd.cx == 20 && lcd.cy == 1
end

assert('LCD', 'print: window(SMALL_FONT)') do
  lcd = EV3RT::LCD.new(:small, 60, 16, 60, 16)
  lcd.print "12345678901234567890"
  lcd.cx == 0 && lcd.cy == 0
end

assert('LCD', 'print: window(MEDIUM_FONT') do
  lcd = EV3RT::LCD.new(:medium, 60, 20, 100, 32)
  lcd.print "12345678901234567890"
  lcd.cx == 0 && lcd.cy == 0
end

#
# LCD#puts
#
assert('LCD', 'puts') do
  lcd = EV3RT::LCD.new
  lcd.puts
  lcd.cx == 0 && lcd.cy == 1
end

assert('LCD', 'puts: single line') do
  lcd = EV3RT::LCD.new
  lcd.puts '1234567890'
  lcd.cx == 0 && lcd.cy == 1
  true
end

assert('LCD', 'puts: multiple line') do
  lcd = EV3RT::LCD.new
  lcd.puts '123456789012345678901234567890'
  lcd.cx == 0 && lcd.cy == 2
end

assert('LCD', "puts: multiple parameters") do
  lcd = EV3RT::LCD.new
  lcd.puts 1, "234", [6, 9]
  lcd.cx == 0 && lcd.cy == 3
end

assert('LCD', 'puts: line feed') do
  lcd = EV3RT::LCD.new
  lcd.puts "1234567890\n12345678901234567890"
  lcd.cx == 0 && lcd.cy == 2
end

assert('LCD', 'puts: window') do
  lcd = EV3RT::LCD.new(:small, 60, 16, 60, 16)
  lcd.puts "12345678901234567890"
  lcd.cx == 0 && lcd.cy == 1
end

assert('LCD', 'puts: window(MEDIUM_FONT') do
  lcd = EV3RT::LCD.new(:medium, 60, 20, 100, 32)
  lcd.puts "12345678901234567890"
  lcd.cx == 0 && lcd.cy == 1
end


# LCD#clear
assert('LCD', 'clear') do
  lcd = EV3RT::LCD.new
  lcd.puts "abcdefghijklmnopqrstuvwxyz"
  lcd.clear
  lcd.cx == 0 && lcd.cy == 0
end

assert('LCD', 'clear(col)') do
  lcd1 = EV3RT::LCD.new
  lcd1.puts "abcdefghijklmnopqrstuvwxyz"
  lcd1.clear(:white)
  lcd2 = EV3RT::LCD.new
  lcd2.puts "abcdefghijklmnopqrstuvwxyz"
  lcd2.clear(:black)
  lcd1.cx == 0 && lcd1.cy == 0 &&
  lcd2.cx == 0 && lcd2.cy == 0
end

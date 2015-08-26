MRuby::Gem::Specification.new('mruby-toppers-ev3rt') do |spec|
  spec.license = 'MIT'
  spec.author  = 'Hiroshi Mimaki'
  spec.summary = 'LEGO MINDSTORMS EV3 (TOPPERS/EV3RT) library for mruby'
  spec.version = '0.1.0'

  spec.add_dependency('mruby-rtos-toppers')
  spec.add_dependency('mruby-tiny-io')
end

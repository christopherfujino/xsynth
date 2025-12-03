#!/usr/bin/env ruby

require 'csv'

# Ensure cwd is //tool
Dir.chdir __dir__

write_fd = File.open('../common/pitches.h', 'w')

write_fd.write "// Generated from //tool/csv-to-cpp.rb\n\n"
write_fd.write "#pragma once\n\n"
write_fd.write "namespace Pitches {\n\n"

frequencies_by_name = []
frequencies_by_number = []

CSV.open('./pitches.csv').each do |pitch|
  midi = pitch[0]
  name = pitch[1]
  octave = pitch[2]
  frequency = pitch[3]

  frequencies_by_name.push (lambda do
    pitchName = name.sub('#', 'Sharp')
    left_pad = ' ' * (6 - pitchName.length)
    "constexpr double #{left_pad}name#{pitchName}#{octave} = #{frequency};\n"
  end.call)

  frequencies_by_number.push (lambda do
    leftPad = ' ' * (3 - midi.length)
    "constexpr double #{leftPad}midi#{midi} = #{frequency};\n"
  end.call)
end

frequencies_by_name.each { |line| write_fd.write line }

write_fd.write "\n"

frequencies_by_number.each { |line| write_fd.write line }

write_fd.write "\n} // namespace Pitches\n"

write_fd.close()

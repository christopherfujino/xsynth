#!/usr/bin/env ruby

require 'csv'

write_fd = File.open('./pitches.h', 'w')

write_fd.write "// Generated from //tool/csv-to-cpp.rb\n\n"
write_fd.write "#pragma once\n\n"
write_fd.write "namespace Pitches {\n\n"

CSV.open('./pitches.csv').each do |pitch|
  midi = pitch[0]
  name = pitch[1]
  octave = pitch[2]
  frequency = pitch[3]
  write_fd.write "const double #{name.sub('#', '_sharp').rjust(7, ' ')}#{octave} = #{frequency};\n"
end

write_fd.write "\n} // namespace Pitches\n"

write_fd.close()

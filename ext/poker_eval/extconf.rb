# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'
# Give it a name
extension_name = 'extpokereval'

# The destination
dir_config(extension_name)

`tar --strip-components 1 -xkzvf poker-eval-138.0.tar.gz -C .`
puts `CC='gcc -fPIC' ./configure --prefix=#{Dir.pwd}/../../lib/poker_eval`

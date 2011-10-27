# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'
require 'rake'

def link_static?
  res = `echo 'int main() { return 0; }' > conftest.c; #{link_command("-Wl,-Bstatic")} 2>&1 | grep -c 'unknown option: -Bstatic'`
  res.to_i == 0
end

extension_name = 'poker_eval_api'

dir_config('poker-eval')

#ldflags = "-Wl,-Bstatic -lpoker-eval -L../../lib/poker_eval/lib -Wl,-Bdynamic"


if find_header("poker_defs.h", "../poker_eval/include/poker-eval") && find_header("enumdefs.h", "../poker-eval/include/poker-eval")

    with_ldflags("-Wl,-Bstatic -lpoker-eval -L../poker_eval/lib -Wl,-Bdynamic") do
        create_makefile(extension_name)
    end
else
  puts "ERROR: No poker-eval support"
  puts "Install poker-eval library from pokersource project:"
  puts "http://download.gna.org/pokersource/sources/poker-eval-138.0.tar.gz"
end
  

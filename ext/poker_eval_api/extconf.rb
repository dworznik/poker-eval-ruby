# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'
require 'rake'

#Rake::Task["ffi_generate"].execute

def link_static?
  res = `echo 'int main() { return 0; }' > conftest.c; #{link_command("-Wl,-Bstatic")} 2>&1 | grep -c 'unknown option: -Bstatic'`
  res.to_i == 0
end

extension_name = 'poker_eval_api'
dir_config(extension_name)

with_cflags("-I../../lib/poker_eval/include/poker-eval") do
  if link_static?
    ldflags = "-Wl,-Bstatic -lpoker-eval -L../../lib/poker_eval/lib -Wl,-Bdynamic"
  else
    #ldflags = "-Wl,-R. -lpoker-eval -L../lib"
    ldflags = "-lpoker-eval -L../../lib/poker_eval/lib"
  end
  with_ldflags(ldflags) do
    create_makefile(extension_name)
  end
end

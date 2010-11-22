# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

def link_static?
  res = `echo 'int main() { return 0; }' > conftest.c; #{link_command("-Wl,-Bstatic")} 2>&1 | grep -c 'unknown option: -Bstatic'`
  res.to_i == 0
end

extension_name = 'extpokereval'
dir_config(extension_name)

with_cflags("-I../poker-eval/include") do
  if link_static?
    ldflags = "-Wl,-Bstatic -lpoker-eval -L../lib -Wl,-Bdynamic"
  else
    #ldflags = "-Wl,-R. -lpoker-eval -L../lib"
    ldflags = "-lpoker-eval -L../lib"
  end
  with_ldflags(ldflags) do
    create_makefile(extension_name)
  end
end

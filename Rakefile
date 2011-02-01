desc "generate FFI structs"
task :ffi_generate do
    require 'ffi'
    require 'ffi/tools/generator'
    require 'ffi/tools/struct_generator'

    ffi_files = ["lib/enum_result.rb.ffi"]
    ffi_options = { :cflags => "-Iext/poker_eval/include" }
    ffi_files.each do |ffi_file|
        ruby_file = ffi_file.gsub(/\.ffi$/,'')
        unless uptodate?(ruby_file, ffi_file)
            puts "generating: #{ffi_file} => #{ruby_file}"
            FFI::Generator.new ffi_file, ruby_file, ffi_options
        end
    end
end

desc "generate FFI structs"
task :ffi_generate do
    require 'ffi'
    require 'ffi/tools/generator'
    require 'ffi/tools/struct_generator'

<<<<<<< HEAD
    module FFI
        class StructGenerator
            def generate_layout
                buf = ""
                @fields.each_with_index do |field, i|
                    colon = ':' unless field.type.class == Array
                    if buf.empty?
                        buf << "layout :#{field.name}, #{colon}#{field.type}, #{field.offset}"
                    else
                        buf << "       :#{field.name}, #{colon}#{field.type}, #{field.offset}"
                    end

                    if i < @fields.length - 1
                        buf << ",\n"
                    end
                end
                buf
            end
        end
    end


=======
>>>>>>> e42ead3192b84f6b90b86ba2a5fa67e33dac0d0a
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

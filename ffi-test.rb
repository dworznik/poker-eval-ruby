#!/usr/bin/env ruby
require 'ffi'

module PokerEval
    extend FFI::Library
    ffi_lib 'ext/extpokereval.so'
end


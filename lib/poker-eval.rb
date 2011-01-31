#!/usr/bin/env ruby
require 'ffi'
require File.join(File.dirname(__FILE__), 'enum_result.rb')

module FFIPokerEval
    extend FFI::Library
    begin
        ffi_lib File.join(File.dirname(__FILE__), 'poker_eval_api.bundle')
    rescue
        ffi_lib File.join(File.dirname(__FILE__), 'poker_eval_api.so')
    end
    attach_function :eval_holdem, [:pointer, :int, :string, :int, :pointer], :int
    attach_function :create_enum_result, [], :pointer
    attach_function :free_enum_result, [:pointer], :void

    def ffi_holdem(pockets, board)
        n = pockets.size
        result_ptr = create_enum_result()
        err = eval_holdem(copy_pockets_array(pockets), n, board, board.length / 2, result_ptr)
        result = EnumResult.new(result_ptr)
        result_args = []
        result_args << [] << [] << []
        [:nwinhi, :nlosehi, :ntiehi, :ev].each do |r|
            result_args << result[r].to_a.first(n).map { |v| v * ( r == :ev ? 1 : 100.0) / result[:nsamples] }
        end
        free_enum_result(result_ptr)
        raise "Invalid input" if err > 0
        result_args
    end

    def copy_pockets_array(pockets)
        ptrs = []
        pockets.each do |p|
            ptrs << FFI::MemoryPointer.from_string(p)
        end
        ptrs << nil
        pockets_ptr = FFI::MemoryPointer.new(:pointer, ptrs.length)
        ptrs.each_with_index do |p, i|
            pockets_ptr[i].put_pointer(0, p)
        end
        pockets_ptr
    end

end

class PokerEval
    extend FFIPokerEval
    class << self
        def holdem(pockets, board)
            Result.new(*ffi_holdem(pockets, board))
        end
    end
end

class PokerEval::Result
    attr_reader :pockets, :board, :dead, :win, :lose, :tie, :ev

    def initialize(pockets, board, dead, win, lose, tie, ev)
        @pockets = pockets
        @board = board
        @win = win
        @lose = lose
        @tie = tie
        @ev = ev
    end
end


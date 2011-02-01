# This file is generated by rake. Do not edit.

module FFIPokerEval
    class EnumResult < FFI::Struct
        layout :game, :pointer, 0,
               :sampleType, :pointer, 4,
               :nsamples, :int, 8,
               :nplayers, :int, 12,
               :nwinhi, [:int, 12], 16,
               :ntiehi, [:int, 12], 64,
               :nlosehi, [:int, 12], 112,
               :nwinlo, [:int, 12], 160,
               :ntielo, [:int, 12], 208,
               :nloselo, [:int, 12], 256,
               :nscoop, [:int, 12], 304,
               :nsharehi, :pointer, 352,
               :nsharelo, :pointer, 976,
               :nshare, :pointer, 1600,
               :ev, [:double, 12], 9712,
               :ordering, :pointer, 9808





    end
end
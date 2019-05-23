scriptencoding utf-8

" type {{{
syntax keyword cppType i8 i16 i32 i64 i128
syntax keyword cppType u8 u16 u32 u64 u128

syntax keyword cppType f32 f64 f80 f128

syntax keyword cppType complex32 complex64 complex80

syntax keyword cppType Formatter

syntax keyword cppType BoolArray

syntax keyword cppType IDENTITY

syntax keyword cppType ModP

syntax keyword cppType MaxHeap MinHeap

syntax keyword cppType procon_hash
syntax keyword cppType HashSet HashMap HashMultiset HashMultimap
" }}}

" constant {{{
syntax keyword cppConstant INF
syntax keyword cppConstant FINF
syntax keyword cppConstant MOD
syntax keyword cppConstant EPS
syntax keyword cppConstant PI
" }}}

" statement {{{
syntax keyword cppStatement assert ASSERT

syntax keyword cppStatement SFINAE

syntax keyword cRepeat REP FOR

syntax keyword cppStatement DBG DBG_CARRAY DBG_RANGE
" }}}

" function {{{
syntax keyword Function ALL SLICE

syntax keyword Function GENERIC

syntax keyword Function FIX
syntax keyword Function MEMOIZE

syntax keyword Function FST SND

syntax keyword Function MAX MIN
syntax keyword Function ABS

syntax keyword Function SIZE

syntax keyword Function chmax chmin

syntax keyword Function is_odd is_even

syntax keyword Function divmod div_ceil div_floor modulo

syntax keyword Function GCD LCM

syntax keyword Function feq

syntax keyword Function FOLD FOLD1
syntax keyword Function SUM
syntax keyword Function transform_self
syntax keyword Function UNIQ

syntax keyword Function ON LT_ON GT_ON EQ_ON NE_ON

syntax keyword Function JOIN

syntax keyword Function RD        RD1
syntax keyword Function RD_ARRAY  RD1_ARRAY
syntax keyword Function RD_ARRAY2 RD1_ARRAY2
syntax keyword Function RD_PAIR   RD1_PAIR
syntax keyword Function RD_TUPLE  RD1_TUPLE

syntax keyword Function PRINT PRINTLN

syntax keyword Function EXIT

syntax keyword Function POP POP_BACK POP_FRONT
" }}}

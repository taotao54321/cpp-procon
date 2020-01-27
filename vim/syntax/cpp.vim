scriptencoding utf-8

" type {{{
syntax keyword cppType i8 i16 i32 i64 i128
syntax keyword cppType u8 u16 u32 u64 u128

syntax keyword cppType f32 f64 f80
syntax keyword cppType Real

syntax keyword cppType Array

syntax keyword cppType Scan Fmt Dbg

syntax keyword cppType ModIntT ModIntC ModInt

syntax keyword cppType ProconHash
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

syntax keyword cRepeat REP FOR LOOP

syntax keyword cppStatement DBG DBG_DP DBG_GRID
" }}}

" function {{{
syntax keyword Function PROCON_INF

syntax keyword Function ALL SLICE

syntax keyword Function LIFT

syntax keyword Function FIX FIXMEMO

syntax keyword Function MAX MIN
syntax keyword Function ABS

syntax keyword Function SIZE

syntax keyword Function chmax chmin

syntax keyword Function is_odd is_even

syntax keyword Function bisect_integer bisect_real

syntax keyword Function divmod div_ceil div_floor modulo

syntax keyword Function GCD LCM EXTGCD

syntax keyword Function FOLD FOLD1
syntax keyword Function SUM
syntax keyword Function UNIQ SORT_UNIQ

syntax keyword Function ON LT_ON GT_ON

syntax keyword Function RD      RD1
syntax keyword Function RD_VEC  RD1_VEC
syntax keyword Function RD_VEC2 RD1_VEC2

syntax keyword Function PRINT PRINTLN

syntax keyword Function EXIT

syntax keyword Function POP
" }}}

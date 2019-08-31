: evaluated-by ( c-addr u -- )
  CREATE HERE DUP >R 2 CELLS ALLOT ! R@ 1 CELLS + ! R> ,
  DOES> DUP 1 CELLS + @ SWAP @ EVALUATE
;

S" 2 +" evaluated-by add2

S" add2 add2" evaluated-by add4

S\" \" add4 add4\" evaluated-by add8"
evaluated-by def-add8

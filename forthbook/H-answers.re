= 練習問題の解答・解説

=== 第 2 章

==== 問題 1

//emlist[]{
6 7 8 * - 9 +
//}

==== 問題 2

//emlist[]{
( x1 x2 x3 x4 -- x3 x4 x1 x2 )
//}

==== 問題 3

//emlist[]{
: word2-3  ( n1 n2 -- n3 )  * + ;
//}

==== 問題 4

//emlist[解答例 1]{
: word2-4  ( n1 n2 -- n3 )  SWAP 3 MOD SWAP 4 / - ;
//}

//emlist[解答例 2]{
: word2-4  ( n1 n2 -- n3 )  -4 / SWAP 3 MOD + ;
//}

==== 問題 5

//emlist[]{
: word2-5  ( x1 x2 -- x2 )  SWAP DROP ;
//}

=== 第 3 章

==== 問題 2

//emlist[]{
: fib  ( n1 -- n2 )
  CASE
    0 OF 0 ENDOF
    1 OF 1 ENDOF
    0 1 ROT 0 DO 2DUP + ROT DROP LOOP
  ENDCASE
;
//}

==== 問題 3

//emlist[]{
: OVER  >R DUP R> SWAP ;
//}

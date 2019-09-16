= コンパイラ変形

ここまで扱ってきた内容を総合すると以下のようになる。

 * 処理系はコンパイラ・インタプリタの 2 つの間を状態遷移する
 * ワードの意味論は処理系の状態に依存して切り替わる
 * 制御構造を作り出すワードがコンパイル状態で利用できる
 * メモリへのデータ書き込み・読み出しのための手段が用意されている
 * @<code>{DOES>} ワードで、メモリ番地を返すワードの実行時意味論を上書きできる

== IMMEDIATE / POSTPONE

//list[ip][][forth]{
IMMEDIATE POSTPONE
//}

== EVALUATE

//list[eval][][forth]{
EVALUATE
//}

== パーサの利用

//list[parser][][forth]{
PARSE WORD
//}

== コンパイル中断

//list[interrupt][][forth]{
[ ] LITERAL SLITERAL STATE
//}

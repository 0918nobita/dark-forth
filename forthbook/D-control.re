= 制御構造

FORTH では、「条件分岐」や「繰り返し」はコンパイル状態でのスタックを活用して構築されている。
この章では、コンパイル状態で利用できる制御フロー関連の機能に触れていく。

== 条件分岐

条件分岐を作り出すためには @<code>{IF}, @<code>{ELSE}, @<code>{THEN} ワードを用いる。
ただし、他の言語の具象構文と見比べて語順が異なっていることに注意してほしい。
この 3 つのワードはコンパイル状態でしか呼び出すことができず、解釈時意味論は未定義である。
その代わり、それぞれ実行時意味論が定義されている。

@<list>{branch}を見てほしい。これは、スタックに積まれた 1 つの数が 2 の倍数の場合に @<code>{Multiple of 2} と
出力するワード @<code>{word3-1} の定義だ。

//list[branch][IF THEN による条件分岐][forth]{
: word3-1  ( n -- )  2 MOD 0 = IF ." Multiple of 2" THEN ;
//}

@<code>{IF}, @<code>{THEN} ワードの組が特別扱いされているわけではなく、それぞれ独立したワードとして定義されている。
@<code>{IF} ワードは「先にスタックに積まれた 1 つの数を条件として、それが偽だった場合のジャンプ先を定めないまま、
真だった場合のコンパイルを開始する」という役割を持つ。そして @<code>{THEN} ワードは「未解決だったジャンプ先を解決する」
という役割を持つ。@<list>{branch-test}では、実際に @<code>{word3-1} ワードを解釈させて挙動を確認している。
1 行目を解釈させても何も主力されないが、2 行目を解釈させると @<code>{Multiple of 2} と出力されたはずだ。

//list[branch-test][word3-1 の動作確認][forth]{
3 word3-1
4 word3-1
//}

@<code>{IF}, @<code>{THEN} ワードは、「コンパイル状態で呼び出されるとコンパイラに働きかけて、
実際に定義されるワードの挙動に特別な影響を与える」ワードである。
このようなワードによって実現される意味論を@<hidx>{走行時意味論}@<b>{走行時意味論} (runtime semantics) という。

@<code>{ELSE} ワードは「未解決だった『条件が偽の場合のジャンプ先』を解決し、
『条件が真の状態で @<code>{ELSE} ワードに達したときのジャンプ先』を未解決にしたままコンパイルを続行する」という役割を持つ。
@<list>{branch2} で定義している @<code>{word3-2} は、スタック上の 2 数のうち小さい方をスタックに残して、
もう一方をスタックから取り除く。

//list[branch2][ELSE を用いた条件分岐][forth]{
: word3-2  ( n1 n2 -- n3 )  2DUP < IF DROP ELSE NIP THEN ;
7 10 word3-2 .
10 7 word3-2 .
//}

スタック上の値の違いに応じた多方向への分岐を実現するには、
@<code>{CASE}, @<code>{OF}, @<code>{ENDOF}, @<code>{ENDCASE} ワードを用いる。
@<list>{branch3} では、先にスタックに積まれていた数が
@<code>{1}, @<code>{2}, @<code>{3} の場合に、それぞれ異なる文字列を出力する。
それ以外の値の場合には、@<code>{Other number:[数値]} の形式で出力する。

@<code>{CASE} ワードまでにスタックの一番上に積まれた値 (以下、「入力値」) が、@<code>{OF} ワードの前に積んだ値 (以下、「基準値」) と一致した場合には、
その後の @<code>{ENDOF} ワードまでを実行して @<code>{ENDCASE} ワードまでジャンプする。
@<code>{OF}, @<code>{ENDOF} ワードを用いないことで、それまで挙げたどの基準値にも一致しなかった場合の処理を記述できる。

@<code>{OF} ワードの走行時意味論は「直前に積まれた入力値と基準値のうち、基準値だけをポップすること」であり、
@<code>{ENDCASE} ワードの走行時意味論は「入力値をポップして実行を継続すること」である。
そのため、スタック上の入力値を消費する操作をする場合には @<code>{DUP} して入力値を複製しておくことが必要となる。
@<list>{branch3} でも、@<code>{Other number:} を出力した後に入力値を出力するために、
予め @<code>{DUP} ワードを呼び出している。

//list[branch3][CASE による多方向への分岐][forth]{
: word3-3  ( n1 n2 -- n3 )
  CASE
    1 OF ." It is one." ENDOF
    2 OF ." It is two." ENDOF
    3 OF ." It is three." ENDOF
    ." Other number: " DUP .
  ENDCASE
;
1 word3-3
2 word3-3
3 word3-3
4 word3-3
//}

「ワードの呼び出しを終了する」という走行時意味論を持った @<code>{EXIT} ワードを用いると、
どこからでも定義内容の最後まで跳躍することができる。

== 繰り返し

=== 確定ループ

回数を指定してループを発生させる場合は、

=== 不定ループ

条件に応じてループ発生させる場合は、

//list[loop][][forth]{
DO LOOP I J K ?DO +LOOP
LEAVE UNLOOP
//}

== 再帰

//list[rec][][forth]{
RECURSE
//}

== リターンスタック

今まで「スタックは 1 つだけ」のように説明してきたが、実はもう 1 つある。
@<hidx>{リターンスタック}@<b>{リターンスタック}という、
「ワードの呼び出しが完了した後にジャンプする先」を記録するためのスタックである。
今まで扱ってきたスタックは、今後リターンスタックと区別して@<hidx>{データスタック}@<b>{データスタック}と呼ぶことにする。

実は FORTH ではこのリターンスタックの内容を操作することが可能である。
以下ではリターンスタックの操作に関する組み込みワードである @<code>{>R}, @<code>{R>}, @<code>{R@} ワードを紹介しているが、
データスタックのスタック表記に加えて、 @<code>{( R: before -- after )} の形式でリターンスタックのスタック表記も記述している。

 : @<idx>{>R}
    解釈時: 未定義動作@<br>{}実行時: @<code>{( x -- ) ( R: -- x )}@<br>{}データスタックから 1 つ要素をポップし、それをリターンスタックにプッシュする。
 : @<idx>{R>}
    解釈時: 未定義動作@<br>{}実行時: @<code>{( -- x ) ( R: x -- )}@<br>{}リターンスタックから 1 つ要素をポップし、それをデータスタックにプッシュする。
 : @<idx>{R@}
    解釈時: 未定義動作@<br>{}実行時: @<code>{( -- x ) ( R: x -- x )}@<br>{}リターンスタックの一番上の要素をコピーして、データスタックにプッシュする。

== 練習問題

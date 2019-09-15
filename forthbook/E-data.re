= データ・辞書

ここまではスタック上のデータの操作や制御構造について触れてきたが、
この章では「データを保存する手段」に関して解説していく。

== 辞書

辞書は「すでに定義されたワードのデータとコードの置き場所」である。
実際には辞書はメモリ中にロードされており、FORTH インタプリタ・コンパイラに関わるコアなワードの定義も含めて、
そこに書き込まれている。辞書に名前とコードを対にして登録すれば、当然それ以降は名前をワードとして扱える。
辞書は、定数や変数を管理するグローバル環境としても利用される。

ここからは、実際に定数や変数、ワードを辞書に書き込ませて辞書の内容の変化を追いながら、
辞書の扱い方や意義について探っていくことにしよう。

=== 定数

FORTH において定数は、@<b>{呼び出されると値を積むワード}として表現される。
そのようなワードを定義するには、@<code>{CONSTANT ( x -- )} ワードを用いる。
先に初期値をスタックに積んでおいて、直後のソースコード中に定数名を記述する。
@<code>{CONSTANT} ワードには、後ろの１単語を切り出すパーサとしての挙動もあわせて定義されている。

//list[const][定数定義][forth]{
100 CONSTANT foo
foo 2 * .
//}

//emlist[実行結果]{
200
//}

=== 変数

FORTH において変数は、@<b>{呼び出されるとスタックに参照先アドレスを積むワード}として表現される。
そのようなワードを定義するには、@<code>{VALUE ( x -- )} ワードを用いる。
@<code>{CONSTANT} ワードと同様に、スタックのトップの要素を初期値、
直後のソースコード中の１単語を変数名として変数を宣言・初期化する。
「スタックのトップの要素をアドレスとしてポップして、
書き込まれている値をプッシュする」@<code>{@ ( a-addr -- x )} ワードを通じて、
代入されている値を取得できる。

@<list>{variable} では、@<code>{270} を初期値として変数 @<code>{bar} を宣言・初期化している。
代入には @<code>{!( x a-addr -- )} ワードを用いる。
@<code>{!} ワードは、@<code>{a-addr} で指定したメモリ番地に @<code>{x} で指定した値を書き込む。

//list[variable][VALUE ワードによる変数宣言と初期化][forth]{
270 VALUE bar
bar @ .   \ 変数 bar の値を出力
42 bar !  \ 変数 bar に 42 を代入
bar @ .
//}

//emlist[実行結果]{
270 42
//}

//list[variable2][][forth]{
VARIABLE baz
80 baz !
baz @ .
//}

//list[dict][][forth]{
[DEFINED]
FIND
HERE UNUSED
, C,
ALLIGN ALLIGNED
//}

== 匿名ワードと XT

定義済みのワードをデータとして扱い、
識別するためのフォーマットが @<hidx>{XT}@<b>{XT} (eXecution Token) だ。
@<code>{'} (ティック) ワードを用いて既定義ワードの XT を取得できる。
XT をもとに実際に呼び出しを発生させるには @<hidx>{EXECUTE}@<code>{EXECUTE} ワードを用いる。

//list[xt][XT の取得と間接的な呼び出し][forth]{
: hello  ( -- )  ." HELLO!" ;

' hello EXECUTE
//}

//emlist[実行結果]{
HELLO!
//}

@<code>{'} ワードの実行時意味論は
「後続するソースコードから１単語をパースして、その名前がついたワードの XT をプッシュすること」であるから、
@<list>{2times} のような高等的なワードを定義することが可能である。

//list[2times][間接的な呼び出しを複数回発生させる][forth]{
: hello ." HELLO!" ;

: 2times  ( xt -- i * x )
  DUP EXECUTE EXECUTE
;

: ntimes  ( xt n -- i * x )
  0 ?DO DUP EXECUTE LOOP DROP
;

' hello 2times CR
' hello 4 ntimes
//}

//emlist[実行結果]{
HELLO!HELLO!
HELLO!HELLO!HELLO!HELLO!
//}

//list[anonymous][][forth]{
:NONAME
DEFER
'
ACTION-OF
IS
//}


== DOES>

//list[does][][forth]{
CREATE DOES>
//}

== 練習問題

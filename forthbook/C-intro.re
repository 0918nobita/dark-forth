= FORTH 序論

この章では、FORTH の学習を始める上で把握しておくべき周辺の基礎概念と、
FORTH の中核をなす諸概念について扱っていく。

== ワードとインタプリタ

FORTH のシンタックスは、要は「文字列を空白文字で区切って並べただけ」だ。
この極限まで単純化されたシンタックスが、
後述する多彩な意味論と相まって、高い融通性を発揮する。

これから少しの間、Gforth を「電卓」として使っていく。
Gforth を起動し、@<list>{arith}を書き写してみよう。
入力が終わったら、改行してみてほしい。

//list[arith][はじめての FORTH プログラム][forth]{
6 3 4 + *　.
//}

正しく動いていれば、たった今書き込んだコードのすぐ左に @<code>{42 ok 0} と表示されたはずだ。
@<code>{ok} と出力されたのは、入力されたコードを Gforth がすべて解釈実行し終えたからだ。
Gforth は、この瞬間にどんな流れで、どう@<list>{arith}を解釈したのだろうか。

#@# textlint-disable ja-technical-writing/max-comma
Gforth は手続きに必要なパラメータをスタック上で管理しながら、
ソースコードを先頭から一直線に解釈する。@<list>{arith}を構成している文字列は
@<code>{6}, @<code>{3}, @<code>{4}, @<code>{+}, @<code>{*}, @<code>{.} の 6 つだ。
#@# textlint-enable ja-technical-writing/max-comma

 * 最初の 3 つは 32 ビット符号付き整数値として解釈され、それぞれ順番にスタックにプッシュされる。

 * あと 3 つの、数値として認識できない文字列は「@<b>{ワード}(word)」として解釈される。

ワードは、簡単に言えば手続きに名前をつけたものだ。
これは、他の言語における関数やサブルーチンのようなものとして理解される。

FORTH 処理系がインタプリタとして動作しているときにワードを認識すると、
対応する@<hidx>{解釈時意味論}@<b>{解釈時意味論}(interpretation semantics)に従って呼び出しが発生する。
後述するが、「～時意味論」のようにワードには複数の意味論が存在し、
呼び出し時の処理系の状態によって、ワードの挙動は異なる(ように作為的にワードを定義できる)。

FORTH 処理系はデフォルトではインタプリタとして動作しており、
この段階では解釈時意味論だけ考慮していれば問題ない。

@<list>{arith}でのインタプリタの挙動は以下のようになる。

 1. @<code>{6 3 4} まで解釈した直後には、スタックにはそのまま底から @<code>{6}, @<code>{3}, @<code>{4} が積まれている。
 2. @<code>{+} を読み込んだインタプリタは、ワード名とその定義を紐付けて保存している@<b>{辞書}(dictionary)からその定義を見つけ出し、呼び出す。@<hidx>{+}@<code>{+} ワードはスタックの一番上に積まれている 2 つの数 @<code>{3}, @<code>{4} をポップし、和 @<code>{7} をプッシュする。
 3. @<code>{*} を読み込んだインタプリタは同様に定義を見つけ出して呼び出す。@<hidx>{* (アスタリスク)}@<code>{*} ワードはスタックの一番上に積まれている 2 つの数 @<code>{6}, @<code>{7} をポップし、積 @<code>{42} をプッシュする。
 4. @<code>{.} ワードの解釈時意味論は「スタックのトップの要素をポップして出力すること」であるから、スタックは空になり、 @<code>{42} が出力される。

つまり、@<list>{arith} は @<m>{(3 + 4) × 6} を評価させて、結果を出力させるプログラムだったわけだ。
FORTH において算術式の評価を表現すると、自然に「被演算子を先に並べて、最後に演算子を書く記法」になる。
この記法は一般的には@<hidx>{逆ポーランド記法}@<b>{逆ポーランド記法}と呼ばれており、スタックとの相性が良い。

今後は、特に指定のない限り、Gforth を起動した直後の状態を想定してサンプルコードを
扱っていく。@<hidx>{BYE}@<code>{BYE}@<fn>{bye} ワードを呼び出せば Gforth を終了できる。

//footnote[bye][アルファベットの大文字小文字の区別はないため、bye と入力しても構わない。]

スタックの要素数と各要素の値を出力する @<hidx>{.S}@<code>{.S} ワードと、
改行コードを出力する @<hidx>{CR}@<code>{CR} ワードも使用して、
@<list>{arith} でのスタックの変化を探ってみよう。(@<list>{watch-stack})

//list[watch-stack][スタックの変化を探る][forth]{
CR .S 6 3 4 CR .S + CR .S * CR .S
//}

//emlist[実行結果]{
<0>
<3> 6 3 4
<2> 6 7
<1> 42
//}

スタック上で正しく計算されていることがわかる。

== 基本的な算術

@<code>{+} ワードや @<code>{*} ワードと同様に、
以下のワードを用いて基本的な算術を行う。

 : @<idx>{- (マイナス)}
    減算
 : @<idx>{/ (スラッシュ)}
    除算
 : @<idx>{MOD}
    剰余
 : @<idx>{/MOD}
    「剰余」「商」を順にプッシュする
 : @<idx>{NEGATE}
    符号を反転する
 : @<idx>{ABS}
    絶対値

//list[basic-arith][]{
23 8 - 3 / .
7 4 MOD .
7 4 /MOD .S
2 NEGATE .
//}

== スタック操作ワード

FORTH にはスタックの内容を操作するための組み込みワードが用意されている。
その 1 つが @<hidx>{DUP}@<code>{DUP} ワードだ。
スタックの一番上に積まれている要素を複製する。

//list[dup-word][DUP ワードの利用][forth]{
8 DUP * .
//}

@<list>{dup-word}を実行すると、すぐ右側に @<code>{ 64 ok 0} と表示される。
@<hidx>{. (ドット)}@<code>{.}(ドット)ワードを呼び出すと、スタックの一番上の要素をポップして出力する。
つまり @<code>{DUP} ワードによって複製が行われスタックにはふたつの 8 が残り、
それらは @<code>{*} ワードによってポップされ 2 数の積 @<code>{64} が残る。

他にもいろいろなスタック操作用のワードが用意されている。

 : @<idx>{DROP}
    一番上の要素を破棄する。
 : @<idx>{NIP}
    一番上から 2 つ目の要素を破棄する。
 : @<idx>{SWAP}
    一番上の 2 つの要素の順序を入れ替える。
 : @<idx>{OVER}
    一番上から 2 つ目の要素をコピーして、それをプッシュする。
 : @<idx>{ROT}
    一番上から 3 つの要素を逆順にする。

スタック上の 2 つの要素をまとめて操作するためのワードも用意されている。

 : @<idx>{2DROP}
    一番上から 2 つの要素を破棄する。
 : @<idx>{2SWAP}
    スタック上の(底の方から) @<code>{a b c d} を、 @<code>{c d a b} に並び替える。
 : @<idx>{2OVER}
    スタック上の @<code>{a b c d} のうち @<code>{a b} をコピーしてプッシュする。
    プッシュ操作が完了すると @<code>{a b c d a b} のようになっている。
 : @<idx>{2DUP}
    一番上から 2 つの要素をコピーして、同じ順でプッシュする。

@<code>{2SWAP} ワードと @<code>{2OVER} ワードの説明では、スタック上の要素に識別名をつけた上で、
呼び出しの前後でそれがどう変化するかを示している。
こういった記法については、後の@<hd>{C-intro|スタック表記法}でより厳密に定義して使っていくことにする。

== コメント

//list[comments][コメントの書き方][forth]{
\ コメント
( コメント )
//}

上のような書き方をすれば、@<code>{コメント}の部分は無視される。
@<code>{\\} と @<code>{(} はそれぞれひとつのワードとして独立に定義されており、
これらを呼び出すために、後ろに空白文字が必要になる。
@<code>{\\} ワードは、後続するソースコードを行末まで読み飛ばす。
@<code>{(} ワードは、後続するソースコードを @<code>{)} まで読み飛ばす。
この 2 つのワードのように、後ろに続いているソースコードをパースして引数に取ることが可能なワードも存在している。
後述するが、そのようなワードをユーザが定義することも可能である。

== セル

FORTH で扱われるデータのサイズの最小単位は@<hidx>{セル}@<b>{セル} (cell) である。
スタックに積まれる要素のサイズもすべて 1 セルとなっている。
1 セルあたりの実際のサイズは処理系依存だが、
標準仕様に含まれている @<hidx>{CELLS}@<code>{CELLS} ワードを用いて、
使用中の処理系でのサイズを知ることができる。

//list[cells][1 セルあたりのバイト数を調べる][forth]{
1 CELLS .
//}

@<code>{CELLS} ワードは、スタックに積まれている整数値 1 つをポップし、
それに 1 セルあたりのバイト数を掛けてプッシュする。
例えば 64 ビット OS 向けの Gforth では 1 セル @<m>{=} 8 バイトなので、
@<list>{cells}を実行すると @<code>{8} と出力されるはずだ。

== 文字列・印字

FORTH においては、文字列は「書き込み先の先頭アドレス」「文字数」の 2 つの値で表現される。
メモリ上に文字列を書き込んでこの 2 つをスタックに積む役割をもつのが @<hidx>{S"}@<code>{S"} ワードだ。
書き込まれる文字列はソースコード上に直接記述し、 @<code>{"} をデリミタとしている。
スタック上の 2 値をポップして文字列として出力するには @<code>{TYPE} ワードを用いる。

//list[str][][forth]{
S" HELLO WORLD" TYPE
//}

ダブルクォートやタブ文字、バックスペース文字といった文字も扱いたい場合、
エスケープシーケンスに対応している @<code>{S\"} ワードを用いる。

//list[str-opt][][forth]{
S\" \l\"Hello,\lFORTH\x21\""
//}

扱えるエスケープシーケンスは @<table>{escape-chars} にまとめてある。

//table[escape-chars][エスケープシーケンス一覧]{
記号	意味
-------------------------------
@<hidx>{\\a}@<code>{\a}	アラート
@<hidx>{\\b}@<code>{\b}	バックスペース
@<hidx>{\\e}@<code>{\e}	エスケープ
@<hidx>{\\f}@<code>{\f}	改ページ
@<hidx>{\\l}@<code>{\l}	改行 (LF)
@<hidx>{\\m}@<code>{\m}	改行 (CR/LF)
@<hidx>{\\q}@<code>{\q または \"}	ダブルクォート
@<hidx>{\\x}@<code>{\x[16進数]}	ASCII 文字 (16 進数で ASCII コードを指定)
@<code>{\\\\}	バックスラッシュ
//}

単にソースコード中の文字列を切り出して出力するだけの @<hidx>{."}@<code>{."} ワードもある。
いわゆる printf デバッグに用いられることが多い。

//list[out][][forth]{
." DEBUG"
//}

実際にメモリ上に文字列が格納されていることを確認するには、@<hidx>{DUMP}@<code>{DUMP} ワードが便利だ。
「先頭アドレス」と「バイト数」をスタックからポップし、その領域の内容をダンプしてくれる。
出力形式については規定されておらず処理系依存となる。以下に、筆者の環境でテストした結果を載せておく。

//list[dump][文字列 ABC を書き込み、ダンプさせるサンプル][forth]{
S" ABC" 2DUP DUMP TYPE
//}

//emlist[実行結果]{
60008EB40: 41 42 43                 -                           ABC
ABC
//}

3 バイトの領域に、A, B, C それぞれの ASCII コードが書き込まれていることがわかる。

== スタック表記法

ワードを呼び出した際のスタックへの影響を記述するための記法を紹介する。
これは、 FORTH のリファレンス等でワードの挙動を説明する際に多用される。
基本的には、以下のようなフォーマットになっている。

//list[stack-notation][スタック表記法]{
( before -- after )
//}

@<code>{before}, @<code>{after} の部分には、スペース区切りで@<hidx>{シンボル}@<b>{シンボル}が 0 個以上並ぶ。
シンボルは、FORTH におけるデータ型や、その値のサイズを表現するための記号である。
Forth 2012 Standard において用いられているシンボルについて、@<table>{symbols}にまとめておく。
現段階では扱っていない言語機能に関するシンボルも含まれているが、今後参照する資料として一旦読み流しておいてほしい。

//table[symbols][スタック表記法で用いられるシンボル]{
シンボル	データ型	サイズ
-------------------------------
@<hidx>{flag}@<code>{flag}	フラグ	1 セル
@<hidx>{char}@<code>{char}	文字	1 セル
@<hidx>{n}@<code>{n}	符号付き整数	1 セル
@<hidx>{u}@<code>{u}	符号無し整数	1 セル
@<hidx>{x}@<code>{x}	指定のない 1 セル分のデータ	1 セル
@<hidx>{xt}@<code>{xt}	エグゼキューショントークン	1 セル
@<hidx>{addr}@<code>{addr}	アドレス	1 セル
@<hidx>{a-addr}@<code>{a-addr}	アラインメントされた領域のアドレス	1 セル
@<hidx>{c-addr}@<code>{c-addr}	文字用にアライメントされた領域のアドレス	1 セル
@<hidx>{d}@<code>{d}	2 セル符号付き整数	2 セル
@<hidx>{ud}@<code>{ud}	2 セル符号無し整数	2 セル
@<code>{i * x, j * x, k * x}	任意	0 セル以上
//}

== 比較・論理演算

先にスタックに積んだ 2 つの数値をポップして比較・論理演算を行うためのワードが用意されている。
ただし、FORTH において偽は @<code>{0} 、真は @<code>{0} 以外の数で表されるので注意が必要だ。
真を表す値としては、 @<code>{-1} がよく用いられる@<fn>{true}。

 : @<idx>{=}
    @<code>{( x1 x2 -- flag )}@<br>{}2 数が等しいなら真、等しくないなら偽を返す
 : @<idx>{<>}
    @<code>{( x1 x2 -- flag )}@<br>{}2 数が等しくないなら真、等しければ偽を返す
 : @<idx>{<}, @<idx>{>}, @<idx>{<=}, @<idx>{>=}
    @<code>{( n1 n2 -- flag )}@<br>{}大小比較
 : @<idx>{AND}, @<idx>{OR}, @<idx>{XOR}
    @<code>{( x1 x2 -- x3 )}@<br>{}ビットごとの論理積 / 論理和 / 排他的論理和を求める
 : @<idx>{INVERT}
    @<code>{( x1 -- x2 )}@<br>{}ビットを反転する

//footnote[true][-1 をビット反転すると 0 になる。0 をビット反転すると -1 になる。]

== ワード定義の基本

ユーザがワード定義する、つまり辞書に新たな項目を追加する方法を紹介する。
基本的には、@<hidx>{: (コロン)}@<code>{:} ワードを使用する。

//list[word-def][ワード定義][forth]{
: square ( n -- n ) DUP * ;
//}

@<list>{word-def} では、新たに @<code>{square} というワードを定義している。
@<code>{( n -- n )} の部分はコメントとして扱われ、プログラマに対して
@<code>{square} ワードの挙動をスタック表記法で示す「ドキュメント」としての役割を担っている。

//list[word-interp][square ワードの利用][forth]{
8 square .
//}

@<code>{square} ワードの解釈時意味論は「スタックの一番上の要素を複製し、上 2 つの要素を掛け合わせること」となるため、
実際に @<code>{square} ワードを呼び出す @<list>{word-interp} を実行すると @<code>{64} が出力される。

@<code>{:} ワードは、呼び出されるとまず後続するソースコードを空白文字の直前まで読み込む。
それを名前として保存した後、処理系を@<hidx>{コンパイル状態}@<b>{コンパイル状態} (compilation state) に移行させる。
コンパイル状態のときにワードを認識すると、先述した解釈時意味論ではなく
@<hidx>{コンパイル時意味論}@<b>{コンパイル時意味論} (compilation semantics) に従って呼び出しが発生する。

一部のワードを除いて、多くのワードのコンパイル時意味論は「自らの解釈時意味論を定義に追加すること」である。
ただし、解釈時意味論と「他のワードの呼び出し中に間接的に呼び出されたときとで挙動」が異なる場合には、
後者を特に@<hidx>{実行時意味論}@<b>{実行時意味論} (execution semantics) と呼ぶ。

== ソースファイルの利用

=== Gforth でソースファイルを指定して実行する

ソースファイルに書き込まれたソースコードを Gforth で実行できる。
例えば @<code>{file1.4th} というソースファイルと、
@<code>{file2.4th} というソースファイルを順に実行したい場合、次のようなコマンドとなる。

//cmd{
gforth file1.4th file2.4th
//}

===[column] ソースファイルの拡張子

一般的には @<code>{.fs, .fth, .4th, .forth} などが用いられる。
筆者は @<code>{.4th} を用いることが多い。
(@<code>{.fs} だと F# のソースファイルの拡張子と被ってしまう)

===[/column]

=== 実行中に別のソースファイルを読み込む

先にソースファイルを文字列で指定し、@<hidx>{INCLUDED}@<code>{INCLUDED} ワード @<code>{( i * x c-addr u -- j * x )} を呼び出すことで、
そのソースファイルを読み込むことができる。

//list[include][file.4th を読み込む][forth]{
S" file.4th" INCLUDED
//}

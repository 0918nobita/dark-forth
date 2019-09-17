= コンパイラ変形

ここまで扱ってきた内容を総合すると以下のようになる。

 * ワードの意味論は処理系の状態に依存して切り替わる
 * 制御構造を作り出すワードがコンパイル状態で利用できる
 * メモリへのデータ書き込み・読み出しのための手段が用意されている

@<code>{:} や @<code>{;} 、@<code>{DOES>} ワードを除くと原則「処理系の状態に直接影響を与えることのない」機能である。
処理系がコンパイラ・インタプリタのどちらとして動作しているかに従って、
事前に定義されたワードの定義内容を実行する、ということに変わりはない。

コンパイラ「変形」と題した本章では、コンパイル状態の処理系に対して直接的に影響を与えるいくつかの手法について述べる。
ここで述べられる内容はどれもアドホックなコンパイルをするための断片的な機能だが、それぞれの特性を知り上手く組み合わせることで、
いわゆるメタプログラミングが可能になる。

== メタプログラミングとは

ロジックを直接記述するのではなく、あるパターンを持ったロジックを生成する高位ロジックを用いて実装していく手法である。
FORTH においては「コンパイル状態の処理系に対して影響を与えるワードを用いて、パターンに従ったワードを定義させる手法」と対応する。

== IMMEDIATE

コンパイル状態の処理系に対して作用するワードを定義するには、
@<b>{コンパイル状態であっても認識されたときに呼び出しが発生する}という特性を持ったワードが定義できる必要がある。
それを可能にするのが @<hidx>{IMMEDIATE}@<code>{IMMEDIATE} ワードだ。

@<code>{IMMEDIATE} ワードは、直前に定義されたワードに対して作用し、
そのワードがコンパイル状態でも呼び出されるようにできる。
@<code>{IMMEDIATE} ワードによってコンパイル状態でも呼び出せるようになったワードを @<hidx>{即時ワード}@<b>{即時ワード}と呼ぶ。
組み込みワードのなかにも即時ワードは含まれており、中でも一番我々にとって馴染みが深いのが @<code>{;} ワードだ。
@<code>{;} ワードが即時ワードであるから「ワードのコンパイルを終了し解釈状態に戻る」という意味論を実現できている。

@<list>{immediate} を、ソースファイルに記述するのではなく対話環境で 1 行ずつ入力して実行してみてほしい。

//list[immediate][][forth]{
: say-hello  ." HELLO" ; IMMEDIATE
: new-word
  say-hello
;
//}

@<code>{new-word} のコンパイル中、@<code>{say-hello} を入力して確定したときに @<code>{HELLO} と出力されるはずだ。
コンパイル状態で呼び出しが発生していることがわかる。

この @<code>{new-word} ワードは、解釈状態でも呼び出せる。
即時ワードで、自らが呼び出されているときにコンパイル状態なのか解釈状態なのかを判別するには @<hidx>{STATE}@<code>{STATE ( -- a-addr )} ワードを用いる。
@<code>{STATE} ワードが返すアドレスは「処理系の状態を表す値の書き込み先」であり、@<code>{@} ワードで参照先の値を取り出してその時々での処理系の状態を取得できる。
@<code>{-1} ならばコンパイル状態であり、その他の値については処理系依存である。
つまり @<code>{STATE} ワードで確実に判別できるのは「コンパイル状態であるか否か」だけである。

//list[state][STATE ワードで処理系の状態を取得する][forth]{
: check-state
  STATE @ -1 =
  IF
    ." Compilation state"
  ELSE
    ." Other state"
  THEN
; IMMEDIATE

check-state

: new-word  check-state ;
//}

//emlist[実行結果]{
Other state
Compilation state
//}

== POSTPONE

即時ワードの処理を抑制して、定義中のワードの実行時意味論に含まれるように「延期」するのが
@<hidx>{POSTPONE}@<code>{POSTPONE} ワードだ。@<code>{POSTPONE} ワード自体も即時ワードであり、
直後のソースコードから 1 単語をワード名としてパースして、それを延期して呼び出すようにコンパイルさせる。

@<list>{postpone}では、@<list>{state}で定義した @<code>{check-state} ワードを用いて @<code>{POSTPONE} ワードの挙動を確認している。

//list[postpone][POSTPONE][forth]{
: after-compilation  POSTPONE check-state ;
: new-word  after-compilation ;

new-word CR
after-compilation
//}

//emlist[実行結果]{
Other state
Other state
//}

@<code>{check-state} ワードの呼び出しが、@<code>{new-word} ワードの実行時まで延期されていることがわかる。

== EVALUATE とパーサ

文字列をそのままソースコードとして解釈実行できてしまうのが @<hidx>{EVALUATE}@<code>{EVALUATE} ワードだ。
スタックに文字列 (メモリ上の先頭アドレス + 文字数) を積んでおけば動作するが、
(@<code>{VALUE} や @<code>{CONSTANT} ワードのように) 直後のソースコードをパースして
利用する方法もある。

//list[eval][先に文字列をスタック上に用意しておく例][forth]{
S\" .\" evaluated\"" EVALUATE
//}

//emlist[実行結果]{
evaluated
//}

直後のソースコードをパースするための最も低レベルなワードが @<hidx>{PARSE}@<code>{PARSE ( char -- c-addr u )} ワードだ。
@<code>{PARSE} ワードは、データスタックのトップに積まれている ASCII コードと対応する文字をデリミタとして、
直後のソースコードをパースする。パース結果は文字列としてデータスタックにプッシュされる。

最後に、@<code>{!} (ASCII コードは @<code>{33}) をデリミタとするパーサを作ってみよう。

//list[parser][! までをパースするパーサ][forth]{
: !parser  33 PARSE ;

!parser Thank you for reading! TYPE
//}

//emlist[実行結果]{
Thank you for reading
//}

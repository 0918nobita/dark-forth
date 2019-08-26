= はじめに

この章では，まず本書で推奨する読み方と，本文中での記法に関してのいくつかの約束事について紹介してから，
処理系のインストールなどの準備について述べる．
最後に FORTH の略史や役立つリファレンスを紹介する．

== 推奨する読み方

FORTH における用語はできる限り説明した上で導入するようにしているが，
逐次実行・条件分岐・繰り返しといった手続き型プログラミングの基礎的な概念については説明を省いている．
また，データ構造については適宜説明するため，必ずしも精通している必要はない．
2章からはそれぞれ練習問題を設けている．本文中の内容を確認するために，実際に頭と手を動かすことを推奨する．

== 本文中での記法

//list[fs][]{
." HELLO WORLD"
//}

== 準備

GNU forth を使用する

=== Windows

http://gforth.org からインストーラを入手する

=== macOS

//cmd{
$ brew install gforth
//}

== FORTH の歴史

チャールズ・ムーアによって開発された．

== 役立つリファレンス

また，FORTH ではなく iMops という派生言語について書かれているこのサイトも役に立つ．

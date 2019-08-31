= 文字列・印字

この章では、FORTH で文字列を扱う上で最低限知っておく必要のある言語機能について述べる。

== HELLO WORLD

@<code>{."} ワードは、後続するソースコードを @<code>{"} まで切り出してそのまま出力する。
いわゆる printf デバッグに用いられることが多い。

//list[hello-world][][forth]{
." HELLO WORLD"
//}

== 通常の文字列



== Unicode 文字列

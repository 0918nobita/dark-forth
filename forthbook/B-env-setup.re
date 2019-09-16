= はじめに

この章では、本書の対象読者と目的について説明した後、処理系のインストールなどの準備について述べる。
最後に FORTH の略史や役立つリファレンスを紹介する。

== 対象の読者

FORTH に触れたことはないが、逐次実行・条件分岐・繰り返しと言った手続き型プログラミングの
基礎的な概念をある程度理解している人を対象としている。
また、FORTH における独特な用語はできる限り説明した上で導入するようにしているが、
配列・スタックといった基本的なデータ構造についての説明は省いている。

== 本書の目的

本書での具体的な目的は「FORTH の特徴的な言語機能とその活用方法を理解して、
仕様書等を参照しながら探求していく土台をつくること」である。
この目的のために、あえて FORTH の算術・文字列操作などの細かな API には深入りせず、
よりコアな言語機能の説明を優先している。その関係上、はじめは辞書的な読み方ではなく
連続したチュートリアルとして、先頭の章から順番に読み進めることを推奨する。

== Gforth のインストール作業

本書では、FORTH 処理系のひとつである GNU forth (以降、Gforth) を使用する。
著者が使用している Gforth のバージョンは @<code>{0.7.9} である。
@<href>{http://gforth.org} (@<img>{gforth-org}) で
インストール方法に関する情報やチュートリアル(英語)が提供されている。

//image[gforth-org][Gforth 公式サイト]

=== Windows

@<href>{http://www.complang.tuwien.ac.at/forth/gforth/} から、
「Win32 self installing」と記載されたインストーラを入手し、
それを実行して指示に従ってインストールする。

=== macOS

Homebrew 経由で導入できる。

//cmd{
brew install gforth
//}

=== Ubuntu

@<code>{apt} コマンドでインストールできる。

//cmd{
sudo apt install gforth
//}

=== Arch linux

AUR @<fn>{aur}で提供されているので、@<code>{yay} 等を利用してインストールする。

//cmd{
yay -S gforth
//}

//footnote[aur][パッケージ詳細ページ: https://aur.archlinux.org/packages/gforth/]

== FORTH の歴史と標準

FORTH は、1958 年からチャールズ・ムーアが個人開発していたプログラミングシステムから考案された。
1968 年に、このソフトウェアをミニコンピュータ上で FORTRAN で実装したものが FORTH の原型とされている。
FORTH が他のプログラマに対して最初に公開されたのは 1970 年代で、
アメリカ国立天文台 (NARO) にいたエリザベス・ラザーによって始められたものである。
NARO にいた 2 人は制御用ソフト開発において FORTH を完成させ、後に FORTH, Inc. を設立した(1973 年)。
ムーアの仕事の関係上、言語開発の初期段階では移植性の高さが求められていた。
当時の FORTH は現在のスクリプト言語のような立ち位置ではなく、
FORTH 処理系自体が軽量 OS として用いられていた。そういった処理系のひとつである MacFORTH は、
アップル Macintosh の最初の常駐開発システムとして採用されていた。

その後も FORTH は様々な環境に移植され、1979 年に言語仕様の標準化が始まった。
1979 年に成分化された FORTH-79、1983 年に成分化された FORTH-83 は「事実上の標準@<fn>{standard}」である。
これらの標準は 1994 年に ANSI によって統合され、ANS Forth と名付けられた。
1979 年には ISO/IEC においても標準化されている@<fn>{iso}。

本書で扱う Gforth は Forth 2012 Standard という規格に沿って現在も盛んに開発されており、
Forth 2012 Standard は Forth 200x 標準化委員会によって策定されている。

//footnote[standard][デファクトスタンダードとも呼ばれる。標準化機関等が定めた規格ではなく、市場における競争や広く採用された結果として「事実上標準化した基準」を指している。]
//footnote[iso][ISO/IEC 15145:1997 https://www.iso.org/standard/26479.html]

== 役立つリファレンス

 : Gforth Manual
    @<href>{http://gforth.org/manual/}@<br>{}FORTH と Gforth の仕様を学べるマニュアル
 : Forth Standard
    @<href>{https://forth-standard.org/}@<br>{}Forth 2012 Standard に関する情報が共有され、さらなる技術仕様 (プロポーザル) がまとめられている。
 : Starting FORTH
    @<href>{https://forth.com/starting-forth}@<br>{}FORTH 入門者向けに、基本からコンパイラ変形まで網羅的に解説している本
 : iMops-forth @Wiki
    @<href>{https://w.atwiki.jp/imops-forth/}@<br>{}FORTH からの派生言語である「iMops」について、様々な記事が公開されている Wiki

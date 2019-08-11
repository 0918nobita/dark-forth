# DARK FORTH

- FORTH 言語の入門書
- PDF で内容を無料公開
- A5 サイズ無線綴じ製本冊子にして、技術書典7で頒布したい

## 内容

- 基本的なスタック操作ワードの使い方・インタプリタモードでの動作原理
- Interpretation / Compilation / Execution / Runtime / Initiation Semantics の違い
- ``IMMEDIATE`` / ``POSTPONE`` ワードについて
- メモリ操作ワード・変数・配列・固定長文字列について
- Compilation Words を用いたマクロの作成
- データ構造とその実装

(できたらいいかも)

- Forth とデザインパターン
- Forth リアクティブプログラミング

## 環境構築

SATySFi を事前にインストールしてください。

### フォントの追加

1. [こちら](https://www.dafont.com/optimusprinceps.font) からフォントをダウンロード

2. `OptimusPrincepsSemiBold.ttf` を `/usr/local/share/satysfi/fonts` ディレクトリ内にコピー

3. `/usr/local/share/satysfi/hash/fonts.satysfi-hash` に以下の項目を追加:

```
"optimus": <Single: {"src": "dist/fonts/OptimusPrincepsSemiBold.ttf"}>
```

### ビルド

```
satysfi dark-forth.saty
```

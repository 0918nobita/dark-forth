## 環境構築

実行環境として Gforth を導入します。

### Windows

### macOS

Homebrew を利用してインストールできます。

```bash
brew install gforth
```

### Linux

#### Ubuntu

以下のコマンドでインストールできます。

```bash
sudo apt-get install gforth
```

#### Arch Linux

AUR で提供されています。(著者は ``yay`` を用いてインストールしました)

### コラム1: Forth 処理系探訪

Forth の処理系は多数存在しており、実行形式や対応している標準仕様がそれぞれ異なっています。

### コラム2: Forth の標準仕様

| 標準仕様 | 時期 |
| --- | --- |
| Forth-77 | 1977年〜 |
| FIG-Forth (Forth-78) | 1978年〜 |
| Forth-79 (事実上の標準) | 1979年〜 |
| Forth-83 (事実上の標準) | 1983年〜 |
| ANS Forth (Forth 94) | 1994年〜 |
| ISO/IEC Forth | 1997年〜 |
| Forth 2012 | 2012年〜 |

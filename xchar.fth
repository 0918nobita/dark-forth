: ua ( -- xchar ) [CHAR] あ ;
: ui ( -- xchar ) [CHAR] い ;
: uu ( -- xchar ) [CHAR] う ;
: ue ( -- xchar ) [CHAR] え ;
: uo ( -- xchar ) [CHAR] お ;

: emit-text ( xc-addr u -- )
  0 DO XC@+ XEMIT LOOP DROP
;

CREATE text 5 CELLS ALLOT
ua text XC!+
ui SWAP XC!+
uu SWAP XC!+
ue SWAP XC!+
uo SWAP XC!+ DROP

text 5 emit-text
BYE

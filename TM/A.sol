; A.sol
;   Mode 0  Everything Off

solenoid Achop 50 51 0 ; Chopper A

; This setup uses a decimal encoding to indicate the mode number
; dtoa S 0x00 { O:0 A:1 B:2 C:3 D:4 E:5 F:6 }

; This setup uses a decimal encoding to indicate both the mode
; number (in the tens column) and the status of the chopper
; (in the ls-bit)
dtoa S 0x1001 { Z:1 _:10 O:11 A:20 B:21 C:30 D:31 E:40 F:41 G:60 H:61 I:70 J:71 }
Command_Set = 'A';

resolution = 1/1

mode 0 {
  initialize Achop: _
}

mode 1 {
  Achop: OO:__^
  S:     __:OO
}

mode 2 {
  Achop: OOOO:OO:____^
  S:     AAAA:AA:BBBB
}

mode 3 {
  Achop: OOOO:____:____:____:____:____:____:__^
  S:     CCCC:DDDD:DDDD:DDDD:DDDD:DDDD:DDDD:DD
}

mode 4 {
  Achop: O_^
  S:     EF
}

mode 5 {
  Achop: _
  S:     Z
  select 0
}

mode 6 {
  Achop: OO__^
  S:     GGHH
}

mode 7 {
  Achop: OOOOOOOO__^
  S:     IIIIIIIIJJ^
}

mode 8 {
  Achop: OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:__^
  S:     KKKK:KKKK:KKKK:KKKK:KKKK:KKKK:KKKK:LL
}

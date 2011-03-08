; B.sol
;   Mode 0  Everything Off

solenoid Bchp 52 53 0 ; Chopper B

; This setup uses a decimal encoding to indicate the mode number
; dtoa S 0x00 { Z:0 A:1 B:2 C:3 D:4 E:5 F:6 }

; This setup uses a decimal encoding to indicate both the mode
; number (in the tens column) and the status of the chopper
; (in the ls-bit)
dtoa S1 0x00 { Z:0 _:10 O:11 }
dtoa S2 0x00 { Z:0 _:20 O:21 }
dtoa S3 0x00 { Z:0 _:30 O:31 }
dtoa S4 0x00 { Z:0 _:40 O:41 }
dtoa S5 0x00 { Z:0 _:50 O:51 }
Command_Set = 'B';

resolution = 1/1

mode 0 {
  initialize Bchp:_
  initialize S1:  Z
}

mode 1 {
  Bchp: OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:__^
  S1:   OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:__^ 
}

mode 2 {
  Bchp: OOOOOO:____^
  S2:   OOOOOO:____^
}

mode 3 {
  Bchp: OOOO:OOOO:__^
  S3:   OOOO:OOOO:__^
}

mode 4 {
  Bchp: OO:__^
  S4:   OO:__^
}

mode 5 {
  select 0
}

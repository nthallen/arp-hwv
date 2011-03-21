; C.sol
;   Mode 0  Everything Off

solenoid Chop 54 55 0 ; Chopper C

; This setup uses a decimal encoding to indicate both the mode
; number (in the tens column) and the status of the chopper
; (in the ls-bit)
dtoa S1 0x00 { Z:0 _:10 O:11 }
dtoa S2 0x00 { Z:0 _:20 O:21 }
dtoa S3 0x00 { Z:0 _:30 O:31 }
dtoa S4 0x00 { Z:0 _:40 O:41 }
dtoa S5 0x00 { Z:0 _:50 O:51 }
Command_Set = 'C';

resolution = 1/1

mode 0 {
  initialize Chop:_
  initialize S1:  Z
}

mode 1 {
  Chop: OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:__^
  S1:   OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:OOOO:__^ 
}

mode 2 {
  Chop: OOOOOO:____^
  S2:   OOOOOO:____^
}

mode 3 {
  Chop: OOOO:OOOO:__^
  S3:   OOOO:OOOO:__^
}

mode 4 {
  Chop: OO:__^
  S4:   OO:__^
}

mode 5 {
  select 0
}

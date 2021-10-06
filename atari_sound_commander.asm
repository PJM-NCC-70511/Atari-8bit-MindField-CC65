
SND_ADDR_LO        = _SOUND_COMMANDER_VARIABLE_AREA + $0000
SND_ADDR_HI        = _SOUND_COMMANDER_VARIABLE_AREA + $0001
SND_DELAY_TIME     = _SOUND_COMMANDER_VARIABLE_AREA + $0008
SND_DELAY_RATE     = _SOUND_COMMANDER_VARIABLE_AREA + $0009

SND_LENGTH_LO      = _SOUND_COMMANDER_VARIABLE_AREA + $0010
SND_LENGTH_HI      = _SOUND_COMMANDER_VARIABLE_AREA + $0011
SND_CHANNEL_IN_USE = _SOUND_COMMANDER_VARIABLE_AREA + $0018
MUS_DIST_START     = _SOUND_COMMANDER_VARIABLE_AREA + $0019
MUS_VOLUME         = _SOUND_COMMANDER_VARIABLE_AREA + $0020
MUS_MIN_VOL        = _SOUND_COMMANDER_VARIABLE_AREA + $0021
MUS_DISTORTION     = _SOUND_COMMANDER_VARIABLE_AREA + $0028
NX_SND_CHNL        = _SOUND_COMMANDER_VARIABLE_AREA + $0029
MUSIC_NOTE         = _SOUND_COMMANDER_VARIABLE_AREA + $002B
    
    




NC3  = 0
NCS3 = 1
ND3 = 2
NDS3 = 3
NE3 = 4
NF3 =5
NFS3 =6
NG3 =7
NGS3 = 8
NA3 = 9
NAS3 = 10
NB3 = 11

NC4 = 12
NCS4 = 13
ND4 = 14
NDS4 = 15
NE4 = 16
NF4 =17
NFS4 =18
NG4 =19
NGS4 = 20
NA4 = 21
NAS4 = 22
NB4 = 23

NC5 =  24 
NCS5 = 25
ND5 = 26
NDS5 = 27
NE5 = 28
NF5 = 29
NFS5 = 30
NG5 = 31
NGS5 = 32
NA5 = 33
NAS5 = 34
NB5 = 35

NC6 = 36
NCS6 = 36
ND6 = 38
NDS6 = 39
NE6 = 40
NF6 =41
NFS6 =42
NG6 =43
NGS6 = 44
NA6 = 45
NAS6 = 46
NB6 = 47

NC7 = 48
NCS7 = 49
ND7 = 50
NDS7 = 51
NE7 = 52
NF7 =53
NFS7 =54
NG7 =55
NGS7 = 56
NA7 = 57
NAS7 = 58
NB7 = 59

NC8 = 60
NCs8 = 61
ND8 = 62
NDs8 = 63






_PROCESS_SOUNDS:
    .export _PROCESS_SOUNDS      
    LDX #$06
    LDA #$00
    STA _NDX0
PLAY_SOUND_LOOP:
    LDA SND_CHANNEL_IN_USE,X
    BEQ DEC_CHANNEL_INDEX
    BPL NO_MUSIC_DECAY    
    LDA SND_DELAY_TIME,X
    LSR 
    BCC NO_MUSIC_DECAY
    LDA MUS_VOLUME
    CMP MUS_MIN_VOL
    BEQ NO_MUSIC_DECAY
    DEC MUS_VOLUME
    LDA MUS_VOLUME
    STA AUDC1,X
NO_MUSIC_DECAY:    
    DEC SND_DELAY_TIME,X
    BNE DEC_CHANNEL_INDEX
    LDA SND_CHANNEL_IN_USE,X
    BPL NO_MUSIC_NOTE
    JSR _GET_NEXT_MUSIC_NOTE
    JMP DEC_SOUND_LENGTH 
NO_MUSIC_NOTE:            
    LDA SND_DELAY_RATE,X
    STA SND_DELAY_TIME,X
GET_SOUND_PART_ADDRESS:       
    LDY SND_ADDR_LO,X
    LDA SND_ADDR_HI,X
    STA _NDX1
    LDA SND_CHANNEL_IN_USE,X     
    LDA (_NDX0),Y
    STA AUDC1,X
    INY    
    BNE NO_SND_INC_ADDR_HI1
    INC SND_ADDR_HI,X
    INC _NDX1
NO_SND_INC_ADDR_HI1:   
    LDA (_NDX0),Y
    STA AUDF1,X 
    INY 
    BNE NO_SND_INC_ADDR_HI2
    INC SND_ADDR_HI,X    
NO_SND_INC_ADDR_HI2:   
    TYA
    STA SND_ADDR_LO,X
DEC_SOUND_LENGTH:
    DEC SND_LENGTH_LO,X
    BNE DEC_CHANNEL_INDEX
END_SOUND:
    LDA #0
    STA SND_CHANNEL_IN_USE,X
    STA AUDC1,X 
    BEQ DEC_CHANNEL_INDEX
            
DEC_CHANNEL_INDEX:
    DEX
    DEX
    BPL PLAY_SOUND_LOOP    
    RTS

END_SOUND_CHECK:
    LDA #0
    STA SND_CHANNEL_IN_USE,X
    STA AUDC1,X  
    JMP DEC_CHANNEL_INDEX



_START_SOUND:
      .export _START_SOUND
        PHA
SouND_Channel_Again:
        LDY NX_SND_CHNL
        LDA SND_CHANNEL_IN_USE,Y
        BPL No_Playing_Music_In_Channel
        JSR ADVANCE_SOUND_CHANNEL
        JMP SouND_Channel_Again 
No_Playing_Music_In_Channel:    
               
        PLA
        STA SND_DELAY_RATE,Y
        LDA START_SOUND_ADDR_LO,X
        STA SND_ADDR_LO,Y 
        LDA START_SOUND_ADDR_HI,X
        STA SND_ADDR_HI,Y         
        LDA START_SOUND_LENGTH_LO,X
        BEQ PLAY_SOUND_ERROR  
        STA SND_LENGTH_LO,Y 
        LDA START_SOUND_LENGTH_HI,X
        STA SND_LENGTH_HI,Y
        BPL NO_SET_SOUND_MUSIC
        AND #$0F
        STA SND_LENGTH_HI,Y
        LDA #192
        STA MUSIC_NOTE
        LDA #$00
        STA MUS_VOLUME
        STA MUS_MIN_VOL
        STA MUS_DISTORTION    
        LDA #$81
        .byte $2C
NO_SET_SOUND_MUSIC:    
        LDA #$01
        STA SND_CHANNEL_IN_USE,Y
        AND #$01
        STA SND_DELAY_TIME,Y
ADVANCE_SOUND_CHANNEL:
        LDA NX_SND_CHNL
        CLC
        ADC #2
        CMP #8
        BCC NO_SND_CHNL_RESET
        LDA #0
        STA AUDCTL    
NO_SND_CHNL_RESET:    
        STA NX_SND_CHNL    
PLAY_SOUND_ERROR:
        RTS
        
        
_GET_NEXT_MUSIC_NOTE:
        .export _GET_NEXT_MUSIC_NOTE      
      LDA #0
      STA AUDC1,X
      LDY SND_ADDR_LO,X
      LDA SND_ADDR_HI,X
      STA _NDX1
      LDA (_NDX0),Y ;DISTORTION + VOLUME
      STA MUS_VOLUME
      AND #$F0
      STA MUS_MIN_VOL
      INY
      BNE NO_MUS_INC_ADDR_HI1
      INC SND_ADDR_HI,X
      INC _NDX1
NO_MUS_INC_ADDR_HI1:
      LDA (_NDX0),Y
      AND #$C0    
      BEQ SET_2_DELAY
      CMP #$40
      BEQ SET_3_DELAY
      CMP #$80
      BEQ SET_4_DELAY
      CMP #$C0
      BEQ SET_5_DELAY
SET_2_DELAY:    
      LDA #$05         
      .BYTE $2C
SET_3_DELAY:
      LDA #$07
      .BYTE $2C
SET_4_DELAY:
      LDA #$09 
      .BYTE $2C
SET_5_DELAY:
      LDA #$11        
      STA SND_DELAY_TIME,X               
      LDA (_NDX0),Y
      AND #$3F
      STA _M9
      INY 
      BNE NO_MUS_INC_ADDR_HI2
      INC SND_ADDR_HI,X
      INC _NDX1
NO_MUS_INC_ADDR_HI2:  
      TYA 
      STA SND_ADDR_LO,X
CHECK_MUSIC_BASS1:
      LDY _M9      
      LDA MUS_MIN_VOL
      CMP #$C0
      BNE CHECK_MUSIC_BASS2
      LDA MUSIC_NOTE_BASS1_TABLE,Y
      STA AUDF1,X  
      JMP CHECK_ALT_START_DISTORTION
CHECK_MUSIC_BASS2:
      CMP #$E0
      BNE DO_MUSIC_MAIN    
      LDA MUSIC_NOTE_BASS2_TABLE,Y
      STA AUDF1,X
      LDA MUS_VOLUME
      AND #$0F
      ORA #$C0
      STA MUS_VOLUME
      AND #$F0
      STA MUS_MIN_VOL
      JMP CHECK_ALT_START_DISTORTION
DO_MUSIC_MAIN:        
      LDA MUSIC_NOTE_MAIN_TABLE,Y
      STA AUDF1,X
CHECK_ALT_START_DISTORTION:
      LDA MUS_DIST_START
      BEQ NO_ALT_START_DISTORTION
      LDA MUS_VOLUME
      AND #$0F
      ORA MUS_DIST_START
      .BYTE $2C      
NO_ALT_START_DISTORTION:      
      LDA MUS_VOLUME
      STA AUDC1,X 


        RTS    


_Kill_Playing_Music:
  .export _Kill_Playing_Music 
  LDY #6
Kill_Music_Loop:  
  LDA SND_CHANNEL_IN_USE,Y
  BPL No_Kill_Music_Channel
  LDA #0
  STA SND_CHANNEL_IN_USE,Y
  STA AUDC1,Y
  STA AUDF1,Y 
No_Kill_Music_Channel:
  DEY
  DEY
  BPL Kill_Music_Loop
No_END_Prior_Music:  
  RTS



STOP_SOUND:
;   TYA
;   ASL @
;   TAY
;   LDA #0
;   STA SND_CHANNEL_IN_USE,Y
;   STA SND_LENGTH_LO,Y
;   STA SND_LENGTH_HI,Y
;   STA AUDC1,Y
;   STA AUDF1,Y    
;   RTS

_SILENCE:
    .export _SILENCE 
    LDA #0
    STA AUDCTL
    LDY #6
NEXT_SILENCE:    
    
;    STA SND_LENGTH_HI,Y
    LDA SND_CHANNEL_IN_USE,Y
    BMI No_Disable_Music_Channel
    LDA #0
    STA SND_CHANNEL_IN_USE,Y
    STA SND_ADDR_LO,Y
    STA SND_LENGTH_LO,Y
    STA SND_DELAY_TIME,Y
;    STA SND_ADDR_HI,Y
No_Disable_Music_Channel:    
    LDA #0     
    STA AUDC1,Y
    STA AUDF1,Y
    DEY
    DEY
    BPL NEXT_SILENCE
    RTS     

EXPLOSION_SOUND_DATA:  
  .byte $8F,248,$8F,240,$8E,232,$8E,224,$0D,216,$8D,208,$8C,200,$6C,192
  .byte $8B,252,$6B,244,$0A,236,$8A,228,$89,220,$89,212,$88,204,$88,196
  .byte $07,248,$87,240,$86,232,$66,224,$85,216,$85,208,$84,200,$84,192
  .byte $83,252,$83,244,$83,236,$82,228,$82,220,$62,212,$01,204,$81,196
EXPLOSION_SOUND_SIZE = (*- EXPLOSION_SOUND_DATA) / 2

BELL_01_SOUND_DATA:                                                           ; 14
  .byte $CF,236,$AE,120,$CD,236,$AC,112
  .byte $CB,137,$AA,120,$C8,242,$A6,112
  .byte $C4,136,$A3,120,$C2,251,$A1,112
BELL_01_SOUND_SIZE = (*- BELL_01_SOUND_DATA)/2

BELL_02_SOUND_DATA:    
  .byte $AF,064,$AE,064,$AD,065,$AC,064                                       ; 12
  .byte $AB,064,$AA,063,$A8,064,$A6,064
  .byte $A4,065,$A3,064,$A2,064,$A1,063
BELL_02_SOUND_SIZE = (*- BELL_02_SOUND_DATA) / 2  

GET_ITEM_SOUND_DATA: 
  .byte $AF,128,$AF,128,$AE,128,$AE,128                                       ; 12
  .byte $CD,206,$CC,206,$CB,206,$CA,206
  .byte $6F,048,$AF,048,$AE,048,$AE,048                                       ; 12
  .byte $CD,080,$CC,080,$CB,080,$CA,080  
GET_ITEM_SOUND_SIZE = (*- GET_ITEM_SOUND_DATA) / 2

ALERT_SOUND_DATA:
    .byte $2A,26,$29,023,$28,020,$27,017,$26,014,$25,11,$20,00,$20,00,$20,00,$20,00,$20,00
    .byte $2A,26,$29,023,$28,020,$27,017,$26,014,$25,11,$20,00,$20,00,$20,00,$20,00,$20,00
ALERT_SIZE = (*- ALERT_SOUND_DATA) / 2 + 1

GAME_OVER_SOUND_DATA:
    .byte $CC,$7B,004,$7A,003,$79,002,$78,001,$77,000
GAME_OVER_SIZE = (*- GAME_OVER_SOUND_DATA) / 2 + 1

EXTRA_LIFE_SOUND_DATA:
  .byte $AF,064,$AF,065,$2F,064,$AE,065,$AE,066,$8E,067, $AC,016,$2C,015,$AC,016,$2C,017,$AB,018,$8B,019
  .byte $A9,032,$A9,033,$29,032,$A8,033,$A8,034,$87,034, $A6,008,$26,009,$A6,008,$26,009,$A6,010,$87,011
  .byte $A4,016,$A4,017,$24,016,$A4,018,$A4,018,$84,019, $A2,004,$22,005,$A2,004,$22,005,$A2,006,$82,007        
EXTRA_LIFE_SOUND_SIZE = (*-EXTRA_LIFE_SOUND_DATA) /2 + 1

_SF_EXPLOSION =   0
_SF_BELL_01 =     1
_SF_BELL_02 =     2
_SF_EXTRA_LIFE =  3
_SF_GET_ITEM =    4
_SF_ALERT =       5
_SF_GAME_OVER =   6

    .export _SF_EXPLOSION 
    .export _SF_BELL_01 
    .export _SF_BELL_02 
    .export _SF_EXTRA_LIFE
    .export _SF_GET_ITEM 
    .export _SF_ALERT 
    .export _SF_GAME_OVER 

START_SOUND_ADDR_LO:                       
    .byte <EXPLOSION_SOUND_DATA
    .byte <BELL_01_SOUND_DATA, <BELL_02_SOUND_DATA
    .byte <EXTRA_LIFE_SOUND_DATA, <GET_ITEM_SOUND_DATA
    .byte <ALERT_SOUND_DATA, <GAME_OVER_SOUND_DATA
    
START_SOUND_ADDR_HI:                                                                                                                                                                                                                                                                       
    .byte >EXPLOSION_SOUND_DATA
    .byte >BELL_01_SOUND_DATA, >BELL_02_SOUND_DATA
    .byte >EXTRA_LIFE_SOUND_DATA, >GET_ITEM_SOUND_DATA
    .byte >ALERT_SOUND_DATA, >GAME_OVER_SOUND_DATA

START_SOUND_LENGTH_LO:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    .byte <EXPLOSION_SOUND_SIZE
    .byte <BELL_01_SOUND_SIZE, <BELL_02_SOUND_SIZE
    .byte <EXTRA_LIFE_SOUND_SIZE, <GET_ITEM_SOUND_SIZE
    .byte <ALERT_SIZE, <GAME_OVER_SIZE
 
START_SOUND_LENGTH_HI:
    .byte >ALERT_SIZE, >GAME_OVER_SIZE, >EXPLOSION_SOUND_SIZE
    .byte >BELL_01_SOUND_SIZE, >BELL_02_SOUND_SIZE
    .byte >EXTRA_LIFE_SOUND_SIZE, >GET_ITEM_SOUND_SIZE
    .byte >ALERT_SIZE, >GAME_OVER_SIZE



MUSIC_NOTE_MAIN_TABLE:  ;Pure Tone  from RMT 
;      C  C#   D   D#  E   F   F#  G  G#  A    A#  B
	.byte $F3,$E6,$D9,$CC,$C1,$B5,$AD,$A2,$99,$90,$88,$80 ;O1  00
  .byte $79,$72,$6C,$66,$60,$5B,$55,$51,$4C,$48,$44,$40 ;O2  12
  .byte $3C,$39,$35,$32,$2F,$2D,$2A,$28,$25,$23,$21,$1F ;O3  24
  .byte $1D,$1C,$1A,$18,$17,$16,$14,$13,$12,$11,$10,$0F ;O4  36
	.byte $0E,$0D,$0C,$0B,$0A,$09,$08,$07,$06,$05,$04,$03 ;O5  48
  .byte $02,$01,$00,$00                                 ;O6  60
;      C  C#   D   D#  E   F   F#  G  G#  A    A#  B
MUSIC_NOTE_BASS1_TABLE:
	.byte $BF,$B6,$AA,$A1,$98,$8F,$89,$80,$F2,$E6,$DA,$CE ;O1  00
	.byte $BF,$B6,$AA,$A1,$98,$8F,$89,$80,$7A,$71,$6B,$65 ;O2  12
	.byte $5F,$5C,$56,$50,$4D,$47,$44,$3E,$3C,$38,$35,$32 ;O3  24
	.byte $2F,$2D,$2A,$28,$25,$23,$21,$1F,$1D,$1C,$1A,$18 ;O4  36
	.byte $17,$16,$14,$13,$12,$11,$10,$0F,$0E,$0D,$0C,$0B ;O5  48
	.byte $0A,$09,$08,$07                                 ;O6  60
;      C  C#   D   D#  E   F   F#  G  G#  A    A#  B  
MUSIC_NOTE_BASS2_TABLE:
	.byte $FF,$F1,$E4,$D8,$CA,$C0,$B5,$AB,$A2,$99,$8E,$87 ;O1  00
	.byte $7F,$79,$73,$70,$66,$61,$5A,$55,$52,$4B,$48,$43 ;O2  12
	.byte $3F,$3C,$39,$37,$33,$30,$2D,$2A,$28,$25,$24,$21 ;O3  24
	.byte $1F,$1E,$1C,$1B,$19,$17,$16,$15,$13,$12,$11,$10 ;O4  36
	.byte $0F,$0E,$0D,$0C,$0B,$0A,$09,$08,$07,$06,$05,$04 ;O5  48
	.byte $03,$02,$01,$00                                 ;O6  60
        
BIT_MUSIC_LOOP:
  .byte $40
BIT_SOUND_IS_MUSIC:
  .byte $80


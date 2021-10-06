

  
_CHARSET_GAME:
  .incbin         "MINDFIELD.FNT"
_CHARSET_TITLE:
  .incbin         "MIND FIELD TITLE.FNT"
_TITLE_DATA:
  .incbin         "Mind Field Title Screen.txt"

      _CHARSET_GAME_HI = > _CHARSET_GAME
      _CHARSET_TITLE_HI = > _CHARSET_TITLE

      
      .export _CHARSET_GAME
      .export _CHARSET_TITLE
      .export _CHARSET_GAME_HI 
      .export _CHARSET_TITLE_HI
      .export _TITLE_DATA

;     _CHARSET_TITLE_HI         = .hibyte(_CHARSET_TITLE)
;     _CHARSET_GAME_HI          = .hibyte(_CHARSET_GAME)
;     .export _CHARSET_TITLE_HI
;     .export _CHARSET_GAME_HI
      
_display_list_title:
     .byte $70,$C0,$44
     .byte <_TITLE_DATA
     .byte >_TITLE_DATA
     .byte $04,$04,$04,$04,$04,$04,$84,$00,$44
     .byte <_GAME_SCREEN_ADDR
     .byte >_GAME_SCREEN_ADDR
     .byte $00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$00,$04,$41
     .byte <_display_list_title 
     .byte >_display_list_title
    
_display_list_game:
     .byte $70,$70,$44
     .byte <_SCREEN_ADDR
     .byte >_SCREEN_ADDR
     .byte $10,$44
     .byte <_GAME_SCREEN_ADDR
     .byte >_GAME_SCREEN_ADDR
     .byte $04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$04,$41
     .byte <_display_list_game 
     .byte >_display_list_game
      
      .export _display_list_title
      .export _display_list_game


_SCRREN_ROW_LOW:
    .byte <(_GAME_SCREEN_ADDR +   0),<(_GAME_SCREEN_ADDR +   40), <(_GAME_SCREEN_ADDR +  80), <(_GAME_SCREEN_ADDR + 120), <(_GAME_SCREEN_ADDR + 160)
    .byte <(_GAME_SCREEN_ADDR + 200), <(_GAME_SCREEN_ADDR + 240), <(_GAME_SCREEN_ADDR + 280), <(_GAME_SCREEN_ADDR + 320), <(_GAME_SCREEN_ADDR + 360)  
  	.byte <(_GAME_SCREEN_ADDR + 400), <(_GAME_SCREEN_ADDR + 440), <(_GAME_SCREEN_ADDR + 480), <(_GAME_SCREEN_ADDR + 520), <(_GAME_SCREEN_ADDR + 560)
  	.byte <(_GAME_SCREEN_ADDR + 600), <(_GAME_SCREEN_ADDR + 640), <(_GAME_SCREEN_ADDR + 680), <(_GAME_SCREEN_ADDR + 720), <(_GAME_SCREEN_ADDR + 760)
    .byte <(_GAME_SCREEN_ADDR + 800), <(_GAME_SCREEN_ADDR + 840), <(_GAME_SCREEN_ADDR + 880), <(_GAME_SCREEN_ADDR + 920), <(_GAME_SCREEN_ADDR + 960)
    .byte <(_GAME_SCREEN_ADDR + 1000) 
    
_SCRREN_ROW_HIGH:
	  .byte >(_GAME_SCREEN_ADDR +   0), >(_GAME_SCREEN_ADDR +  40), >(_GAME_SCREEN_ADDR +  80), >(_GAME_SCREEN_ADDR + 120), >(_GAME_SCREEN_ADDR + 160)
  	.byte >(_GAME_SCREEN_ADDR + 200), >(_GAME_SCREEN_ADDR + 240), >(_GAME_SCREEN_ADDR + 280), >(_GAME_SCREEN_ADDR + 320), >(_GAME_SCREEN_ADDR + 360)
  	.byte >(_GAME_SCREEN_ADDR + 400), >(_GAME_SCREEN_ADDR + 440), >(_GAME_SCREEN_ADDR + 480), >(_GAME_SCREEN_ADDR + 520), >(_GAME_SCREEN_ADDR + 560)
  	.byte >(_GAME_SCREEN_ADDR + 600), >(_GAME_SCREEN_ADDR + 640), >(_GAME_SCREEN_ADDR + 680), >(_GAME_SCREEN_ADDR + 720), >(_GAME_SCREEN_ADDR + 760)
  	.byte >(_GAME_SCREEN_ADDR + 800), >(_GAME_SCREEN_ADDR + 840), >(_GAME_SCREEN_ADDR + 880), >(_GAME_SCREEN_ADDR + 920), >(_GAME_SCREEN_ADDR + 960)
  	.byte >(_GAME_SCREEN_ADDR + 1000)  

      .export _SCRREN_ROW_LOW
      .export _SCRREN_ROW_HIGH




P000:
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00101000; $28  40
     .byte %00101000; $28  40
     .byte %00101000; $28  40
     .byte %00101000; $28  40

P001:
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %01111000; $78  120
     .byte %01111000; $78  120
     .byte %01111100; $7C  124
     .byte %01111110; $7E  126
     .byte %00111010; $3A  58
     .byte %00111010; $3A  58
     .byte %00111000; $38  56
     .byte %00101000; $28  40
     .byte %00101100; $2C  44
     .byte %00100100; $24  36
     .byte %00100000; $20  32

P002:
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00001100; $0C  12
     .byte %00011110; $1E  30
     .byte %00111110; $3E  62
     .byte %00111110; $3E  62
     .byte %00011110; $1E  30
     .byte %00011100; $1C  28
     .byte %00011000; $18  24
     .byte %00011000; $18  24
     .byte %00011000; $18  24
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00010100; $14  20

P003:
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %01111100; $7C  124
     .byte %11111100; $FC  252
     .byte %10111000; $B8  184
     .byte %10111000; $B8  184
     .byte %00111000; $38  56
     .byte %00101000; $28  40
     .byte %00101100; $2C  44
     .byte %00100100; $24  36
     .byte %00100000; $20  32

P004:
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00011000; $18  24
     .byte %00111100; $3C  60
     .byte %00111110; $3E  62
     .byte %00111110; $3E  62
     .byte %00111100; $3C  60
     .byte %00011100; $1C  28
     .byte %00001100; $0C  12
     .byte %00001100; $0C  12
     .byte %00001100; $0C  12
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00010100; $14  20

P005:
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %01111100; $7C  124
     .byte %11111100; $FC  252
     .byte %10111000; $B8  184
     .byte %10111000; $B8  184
     .byte %00111000; $38  56
     .byte %00101000; $28  40
     .byte %01101000; $68  104
     .byte %01001000; $48  72
     .byte %01001000; $48  72

P006:
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00001100; $0C  12
     .byte %00011100; $1C  28
     .byte %00011110; $1E  30
     .byte %00011101; $1D  29
     .byte %00111110; $3E  62
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00011000; $18  24
     .byte %00100100; $24  36
     .byte %00100010; $22  34
     .byte %01000001; $41  65
     .byte %01000001; $41  65

P007:
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %01111000; $78  120
     .byte %01111000; $78  120
     .byte %01111100; $7C  124
     .byte %01111110; $7E  126
     .byte %00111010; $3A  58
     .byte %00111010; $3A  58
     .byte %00111000; $38  56
     .byte %00101000; $28  40
     .byte %01101000; $68  104
     .byte %01001000; $48  72
     .byte %01001000; $48  72

P008:
     .byte %00011100; $1C  28
     .byte %00011100; $1C  28
     .byte %00011000; $18  24
     .byte %00011100; $1C  28
     .byte %00111100; $3C  60
     .byte %01011100; $5C  92
     .byte %00111110; $3E  62
     .byte %00011110; $1E  30
     .byte %00001100; $0C  12
     .byte %00001100; $0C  12
     .byte %00010010; $12  18
     .byte %00100010; $22  34
     .byte %01000001; $41  65
     .byte %01000001; $41  65

P009:
     .byte %11000011; $C3  195
     .byte %11000011; $C3  195
     .byte %01100110; $66  102
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00111100; $3C  60
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %00111100; $3C  60
     .byte %00011000; $18  24

P010:
     .byte %00000000; $00  0
     .byte %11000110; $C6  198
     .byte %11000110; $C6  198
     .byte %01101100; $6C  108
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %00111000; $38  56
     .byte %00010000; $10  16

P011:
     .byte %00000000; $00  0
     .byte %01100110; $66  102
     .byte %01100110; $66  102
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00011000; $18  24
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00000000; $00  0

P012:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %11000011; $C3  195
     .byte %01100110; $66  102
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00111100; $3C  60
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %01111110; $7E  126
     .byte %00011000; $18  24
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P013:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %11000110; $C6  198
     .byte %01101100; $6C  108
     .byte %00111000; $38  56
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %01111100; $7C  124
     .byte %00111000; $38  56
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P014:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %01100110; $66  102
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00011000; $18  24
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00111100; $3C  60
     .byte %00011000; $18  24
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P015:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %01101100; $6C  108
     .byte %00111000; $38  56
     .byte %00010000; $10  16
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00111000; $38  56
     .byte %00010000; $10  16
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P016:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00011000; $18  24
     .byte %00100100; $24  36
     .byte %00100100; $24  36
     .byte %00100100; $24  36
     .byte %00100100; $24  36
     .byte %00011000; $18  24
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P017:
     .byte %00000000; $00  0
     .byte %00000000; $00  0
     .byte %00011000; $18  24
     .byte %00100100; $24  36
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %00100100; $24  36
     .byte %00011000; $18  24
     .byte %00000000; $00  0
     .byte %00000000; $00  0

P018:
     .byte %00000000; $00  0
     .byte %00011000; $18  24
     .byte %00100100; $24  36
     .byte %01000010; $42  66
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %01000010; $42  66
     .byte %00100100; $24  36
     .byte %00011000; $18  24
     .byte %00000000; $00  0

P019:
     .byte %00111100; $3C  60
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %10000001; $81  129
     .byte %01000010; $42  66
     .byte %01000010; $42  66
     .byte %00111100; $3C  60

     
_SPRITEADDR_PLY0LO:
      .byte <P000,<P001,<P002,<P003,<P004,<P005,<P006,<P007,<P008,<P009,<P010,<P011,<P012,<P013,<P014,<P015
      .byte <P016,<P017,<P018,<P019
_SPRITEADDR_PLY0HI: 
      .byte >P000,>P001,>P002,>P003,>P004,>P005,>P006,>P007,>P008,>P009,>P010,>P011,>P012,>P013,>P014,>P015
      .byte >P016,>P017,>P018,>P019
     
_SPRITEADDR_PLY0W:
      .word P000,P001,P002,P003,P004,P005,P006,P007,P008,P009,P010,P011,P012,P013,P014,P015
      .word P016,P017,P018,P019


      .export _SPRITEADDR_PLY0LO      ; Makes Sprite Address Table available to C compiled program
      .export _SPRITEADDR_PLY0HI      ; Makes Sprite Address Table available to C compiled program
      .export _SPRITEADDR_PLY0W       ; Makes Sprite Address Table available to C compiled program


#include <atari.h>
#include <peekpoke.h>
#include <string.h>
    
#define	PRIOR									 0xD01B
#define	TEMP0									 0xC0
#define	TEMP1									 0xC1
#define	TEMP2									 0xC2
#define	TEMP3									 0xC3
#define	TEMP4									 0xC4
#define	TEMP5									 0xC5
#define	TEMP6									 0xC6
#define	TEMP7									 0xC7
#define	TEMP8									 0xC8
#define	TEMP9									 0xC9
#define	NDX0									 0xCA
#define	NDX1									 0xCB
#define	NDX2									 0xCC
#define	NDX3									 0xCD
#define	HOLDX									 0xCE
#define	HOLDY									 0xCF
    

#define	screen_adr  				     		             0x4000
#define	PMBANK                                   0x1800
#define	VARBANK                                  0x0600

#define	SCREEN_ADDR						                  0x$0800;           
#define	GAME_SCREEN						                  0xSCREEN_ADDR + 40
#define	LOCALVAR                                0xVARBANK + $E0   
#define	CHARSET_GAME                            0x$A400           
#define	CHARSET_TITLE                           0x$A800           
#define	TITLE_DATA			                        0x$AC00           
#define	SOUND_COMMANDER                         0x$AE00           
#define	CHARSET_BASE			                      0x$A4             

#define	PLAY_SOUNDS ((unsigned char *)          (SOUND_COMMANDER + $0000))	    
#define	START_SOUND ((unsigned char *)          (SOUND_COMMANDER + $009F))      
#define	GET_NEXT_MUSIC_NOTE ((unsigned char *)  (SOUND_COMMANDER + $00F6))      
#define	STOP_SOUND ((unsigned char *)           (SOUND_COMMANDER + $0189))      
#define	SILENCE ((unsigned char *)              (SOUND_COMMANDER + $019E))      

#define	SPRITENUM	((unsigned char *)             (PMBANK+0x0180))
#define	SETSP0COLOR ((unsigned char *)           (PMBANK+0x0190))
#define	SETSP1COLOR ((unsigned char *)           (PMBANK+0x01A0))
#define	SETSPWIDTH ((unsigned char *)            (PMBANK+0x01B0))
#define	SPRITENHOZ ((unsigned char *)            (PMBANK+0x01C0))
#define	SPRITENVRT ((unsigned char *)            (PMBANK+0x01E0))
#define	SPHOZNEXT  ((unsigned char *)            (PMBANK+0x01F0))
#define	SCREEN_LINE_ADDR_LOW ((unsigned char *)	 (PMBANK+0x0000))
#define	SCREEN_LINE_ADDR_HIGH ((unsigned char *) (PMBANK+0x0020))
#define	CHARSET_ADDRESS ((unsigned char *)       0xA400

#define SPRHZ0	((unsigned char *)	            (PMBANK+0x0200)) 
#define SPRHZ1	((unsigned char *)	            (PMBANK+0x0210)) 
#define SPRHZ2	((unsigned char *)	            (PMBANK+0x0220)) 
#define SPRHZ3	((unsigned char *)	            (PMBANK+0x0230)) 
#define SPZONT  ((unsigned char *)              (PMBANK+0x0240))
#define SPZONB  ((unsigned char *)              (PMBANK+0x0250))
#define SPSRC0  ((unsigned char *)              (PMBANK+0x0260)) 
#define SPSRC1  ((unsigned char *)              (PMBANK+0x0278))
#define SPSRC2  ((unsigned char *)              (PMBANK+0x0290))
#define SPSRC3  ((unsigned char *)              (PMBANK+0x02A8))
#define SPSRC4  ((unsigned char *)              (PMBANK+0x02C0))
#define SPRITEUSE ((unsigned char *)           	(PMBANK+0x02D8))
                                            
#define MIBANK ((unsigned char *)              	(PMBANK+0x0300))
#define PMBNK0 ((unsigned char *)               (PMBANK+0x0400))
#define PMBNK1 ((unsigned char *)	              (PMBANK+0x0500))
#define PMBNK2 ((unsigned char *)               (PMBANK+0x0600))
#define PMBNK3 ((unsigned char *)	              (PMBANK+0x0700))
                                                                                                                          
unsigned char i; 
unsigned char j; 
unsigned char k; 
unsigned char l;

unsigned char titlephase=0;
unsigned int score=4250;

unsigned short int hiscore [11] = {0,7500,5500,3500,2500,0500,00,00,00,00,0};
unsigned short int topMem; 
unsigned char chbase1;


// void   DisplayList =
unsigned char  display_list_title [] =
{
	0x70,0x30,0x43,
  screen_adr,
  0x03,0x03,0x03,0x03,0x00,
  0x03,0x03,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x03,
  0x03,0x03,0x41,0xFF,0xFF  
};

unsigned char  screen_row_low[] = {
    (screen_adr +   0) & 0xff,(screen_adr +   40) & 0xff, (screen_adr +  80) & 0xff, (screen_adr + 120) & 0xff, (screen_adr + 160) & 0xff,
    (screen_adr + 200) & 0xff, (screen_adr + 240) & 0xff, (screen_adr + 280) & 0xff, (screen_adr + 320) & 0xff, (screen_adr + 360) & 0xff,  
  	(screen_adr + 400) & 0xff, (screen_adr + 440) & 0xff, (screen_adr + 480) & 0xff, (screen_adr + 520) & 0xff, (screen_adr + 560) & 0xff,
  	(screen_adr + 600) & 0xff, (screen_adr + 640) & 0xff, (screen_adr + 680) & 0xff, (screen_adr + 720) & 0xff, (screen_adr + 760) & 0xff,
    (screen_adr + 800) & 0xff, (screen_adr + 840) & 0xff, (screen_adr + 880) & 0xff, (screen_adr + 920) & 0xff, (screen_adr + 960) & 0xff,
    (screen_adr + 1000) & 0xff
};    
    
unsigned char screen_row_high[] = {
	  (screen_adr +   0) >> 8, (screen_adr +  40) >> 8, (screen_adr +  80) >> 8, (screen_adr + 120) >> 8, (screen_adr + 160) >> 8,
  	(screen_adr + 200) >> 8, (screen_adr + 240) >> 8, (screen_adr + 280) >> 8, (screen_adr + 320) >> 8, (screen_adr + 360) >> 8,
  	(screen_adr + 400) >> 8, (screen_adr + 440) >> 8, (screen_adr + 480) >> 8, (screen_adr + 520) >> 8, (screen_adr + 560) >> 8,
  	(screen_adr + 600) >> 8, (screen_adr + 640) >> 8, (screen_adr + 680) >> 8, (screen_adr + 720) >> 8, (screen_adr + 760) >> 8,
  	(screen_adr + 800) >> 8, (screen_adr + 840) >> 8, (screen_adr + 880) >> 8, (screen_adr + 920) >> 8, (screen_adr + 960) >> 8,
  	(screen_adr + 1000) >> 8 
};
  




///;;};	


unsigned char P000 [] = {
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00101000,  // $28  40
     0b00101000,  // $28  40
     0b00101000,  // $28  40
     0b00101000}; // $28  40

unsigned char P001[] = {
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b01111000,  // $78  120
     0b01111000,  // $78  120
     0b01111100,  // $7C  124
     0b01111110,  // $7E  126
     0b00111010,  // $3A  58
     0b00111010,  // $3A  58
     0b00111000,  // $38  56
     0b00101000,  // $28  40
     0b00101100,  // $2C  44
     0b00100100,  // $24  36
     0b00100000}; // $20  32

unsigned char P002[] = {
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00001100,  // $0C  12
     0b00011110,  // $1E  30
     0b00111110,  // $3E  62
     0b00111110,  // $3E  62
     0b00011110,  // $1E  30
     0b00011100,  // $1C  28
     0b00011000,  // $18  24
     0b00011000,  // $18  24
     0b00011000,  // $18  24
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00010100}; // $14  20

unsigned char P003[] = {
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b01111100,  // $7C  124
     0b11111100,  // $FC  252
     0b10111000,  // $B8  184
     0b10111000,  // $B8  184
     0b00111000,  // $38  56
     0b00101000,  // $28  40
     0b00101100,  // $2C  44
     0b00100100,  // $24  36
     0b00100000}; // $20  32

unsigned char P004[] = {
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00011000,  // $18  24
     0b00111100,  // $3C  60
     0b00111110,  // $3E  62
     0b00111110,  // $3E  62
     0b00111100,  // $3C  60
     0b00011100,  // $1C  28
     0b00001100,  // $0C  12
     0b00001100,  // $0C  12
     0b00001100,  // $0C  12
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00010100}; // $14  20

unsigned char P005[] = {
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b01111100,  // $7C  124
     0b11111100,  // $FC  252
     0b10111000,  // $B8  184
     0b10111000,  // $B8  184
     0b00111000,  // $38  56
     0b00101000,  // $28  40
     0b01101000,  // $68  104
     0b01001000,  // $48  72
     0b01001000}; // $48  72

unsigned char P006[] = {
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00001100,  // $0C  12
     0b00011100,  // $1C  28
     0b00011110,  // $1E  30
     0b00011101,  // $1D  29
     0b00111110,  // $3E  62
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00011000,  // $18  24
     0b00100100,  // $24  36
     0b00100010,  // $22  34
     0b01000001,  // $41  65
     0b01000001}; // $41  65

unsigned char P007[] = {
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b01111000,  // $78  120
     0b01111000,  // $78  120
     0b01111100,  // $7C  124
     0b01111110,  // $7E  126
     0b00111010,  // $3A  58
     0b00111010,  // $3A  58
     0b00111000,  // $38  56
     0b00101000,  // $28  40
     0b01101000,  // $68  104
     0b01001000,  // $48  72
     0b01001000}; // $48  72

unsigned char P008[] = {
     0b00011100,  // $1C  28
     0b00011100,  // $1C  28
     0b00011000,  // $18  24
     0b00011100,  // $1C  28
     0b00111100,  // $3C  60
     0b01011100,  // $5C  92
     0b00111110,  // $3E  62
     0b00011110,  // $1E  30
     0b00001100,  // $0C  12
     0b00001100,  // $0C  12
     0b00010010,  // $12  18
     0b00100010,  // $22  34
     0b01000001,  // $41  65
     0b01000001}; // $41  65

unsigned char P009[] = {
     0b11000011,  // $C3  195
     0b11000011,  // $C3  195
     0b01100110,  // $66  102
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00111100,  // $3C  60
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b00111100,  // $3C  60
     0b00011000}; // $18  24

unsigned char P010[] = {
     0b00000000,  // $00  0
     0b11000110,  // $C6  198
     0b11000110,  // $C6  198
     0b01101100,  // $6C  108
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b00111000,  // $38  56
     0b00010000}; // $10  16

unsigned char P011[] = {
     0b00000000,  // $00  0
     0b01100110,  // $66  102
     0b01100110,  // $66  102
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00011000,  // $18  24
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00000000}; // $00  0

unsigned char P012[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b11000011,  // $C3  195
     0b01100110,  // $66  102
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00111100,  // $3C  60
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b01111110,  // $7E  126
     0b00011000,  // $18  24
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P013[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b11000110,  // $C6  198
     0b01101100,  // $6C  108
     0b00111000,  // $38  56
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b01111100,  // $7C  124
     0b00111000,  // $38  56
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P014[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b01100110,  // $66  102
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00011000,  // $18  24
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00111100,  // $3C  60
     0b00011000,  // $18  24
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P015[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b01101100,  // $6C  108
     0b00111000,  // $38  56
     0b00010000,  // $10  16
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00111000,  // $38  56
     0b00010000,  // $10  16
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P016[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00011000,  // $18  24
     0b00100100,  // $24  36
     0b00100100,  // $24  36
     0b00100100,  // $24  36
     0b00100100,  // $24  36
     0b00011000,  // $18  24
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P017[] = {
     0b00000000,  // $00  0
     0b00000000,  // $00  0
     0b00011000,  // $18  24
     0b00100100,  // $24  36
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b00100100,  // $24  36
     0b00011000,  // $18  24
     0b00000000,  // $00  0
     0b00000000}; // $00  0

unsigned char P018[] = {
     0b00000000,  // $00  0
     0b00011000,  // $18  24
     0b00100100,  // $24  36
     0b01000010,  // $42  66
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b01000010,  // $42  66
     0b00100100,  // $24  36
     0b00011000,  // $18  24
     0b00000000}; // $00  0

unsigned char P019[] = {
     0b00111100,  // $3C  60
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b10000001,  // $81  129
     0b01000010,  // $42  66
     0b01000010,  // $42  66
     0b00111100}; // $3C  60


unsigned char spriteaddrlo[] = {&&P000 & 0xff,&&P001 & 0xff,&&P002 & 0xff,&&P003 & 0xff,&&P004 & 0xff,
                                &&P005 & 0xff,&&P006 & 0xff,&&P007 & 0xff,&&P008 & 0xff,&&P009 & 0xff,
                                &&P010 & 0xff,&&P011 & 0xff,&&P012 & 0xff,&&P013 & 0xff,&&P014 & 0xff,
                                &&P015 & 0xff,&&P016 & 0xff,&&P017 & 0xff,&&P018 & 0xff,&&P019 & 0xff
};
  
unsigned CHAR spriteaddrhi[20] = {&&P000 >> 8, &&P001 >> 8, &&P002 >> 8, &&P003 >> 8, &&P004 >> 8, &&P005 >> 8, &&P006 >> 8,&&P007 >> 8, &&P008 >> 8, &&P009 >> 8,
  										            &&P010 >> 8, &&P011 >> 8, &&P012 >> 8, &&P013 >> 8, &&P014 >> 8, &&P015 >> 8, &&P016 >> 8,&&P017 >> 8, &&P018 >> 8, &&P019 >> 8};
 




void  display_list_game = 
{0x70,0x50,0x43,
  &&screen_adr, 
  0x00,0x04,0x00,0x04,0x00,0x04,
  0x00,0x04,0x00,0x04,0x00,0x04,
  0x00,0x04,0x00,0x04,0x00,0x04,
  0x00,0x04,0x00,0x04,0x00,0x04,
  0x00,0x04,0x00,0x04,0x00,0x04,
  0x00,0x04,0x00,0x04,0x41    
  &&display_list_game
};         


//{***************************************************************************************}
//{************************************** MAIN *******************************************}
//{***************************************************************************************}

void TopGameLogic()
{
TopLogicLoop:
			ShowTitleScreen();

			goto TopLogicLoop 
}



// CHARSET_ADDRESS rcdata 'Mind Field\MINDFIELD.FNT'



extern unsigned char  CHARSET_GAME;
extern unsigned char  SPRITEADDR_PLY0LO;    
extern unsigned char  SPRITEADDR_PLY0HI;    
extern unsigned char  CHARSET_TITLE;
//extern unsigned char const  CHARSET_GAME_HI;
//extern unsigned char const  CHARSET_TITLE_HI;        
extern unsigned int   TITLE_DATA;           
extern unsigned int   display_list_title;   
extern unsigned int   display_list_game;    
extern unsigned int   PMBANK;         
extern unsigned int   VARBANK;         
extern unsigned int   SCREEN_ADDR;         
extern unsigned int   GAME_SCREEN_ADDR[];         
extern unsigned char  PLAY_SOUNDS;             
extern unsigned char  START_SOUND;             
extern unsigned char  GET_NEXT_MUSIC_NOTE;     
extern unsigned char  STOP_SOUND;              
extern unsigned char  SILENCE;                 
extern unsigned char  SPRITENUM;	              
extern unsigned char  SETSP0COLOR;             
extern unsigned char  SETSP1COLOR;             
extern unsigned char  SETSPWIDTH;              
extern unsigned char  SPRITENHOZ;              
extern unsigned char  SPRITENVRT;              
extern unsigned char  SPHOZNEXT;               
extern unsigned char  SCREEN_LINE_ADDR_LOW;    
extern unsigned char  SCREEN_LINE_ADDR_HIGH;   
extern unsigned char  SPRHZ0;	                
extern unsigned char  SPRHZ1;	                
extern unsigned char  SPRHZ2;	                
extern unsigned char  SPRHZ3;	                
extern unsigned char  SPZONT;                  
extern unsigned char  SPZONB;                  
extern unsigned char  SPSRC0;                  
extern unsigned char  SPSRC1;                  
extern unsigned char  SPSRC2;                  
extern unsigned char  SPSRC3;                  
extern unsigned char  SPSRC4;                  
extern unsigned char  SPRITEUSE;               
extern unsigned char  MIBANK;                  
extern unsigned char  PMBNK0;                 
extern unsigned char  PMBNK1;                  
extern unsigned char  PMBNK2;                  
extern unsigned char  PMBNK3;                  
extern unsigned char  ZA;
extern unsigned char  ZB;
extern unsigned char  ZC;
extern unsigned char  ZD;
extern unsigned char  ZE;
extern unsigned char  ZF;
extern unsigned char  ZG;
extern unsigned char  ZH;
extern unsigned char  ZI;
extern unsigned char  ZJ;
extern unsigned char  ZK;
extern unsigned char  ZL;
extern unsigned char  ZM;
extern unsigned char  ZN;
extern unsigned char  ZO;
extern unsigned char  ZP;
extern unsigned char character_px;              
extern unsigned char	character_py;       
extern unsigned char	character_status;
extern unsigned char	prior_py;               
extern unsigned char	stick_read;             
extern unsigned char	prior_rt_clock;         
extern unsigned char	menu_selection;         
extern unsigned char	find_option;            
extern unsigned char	bombs_on_option;        
extern unsigned char	walls_on_option;        
extern unsigned char	shooters_option;        
extern unsigned char	mind_color;             
extern unsigned char	show_countdown;         
extern unsigned char	minds_found;            
extern unsigned char	minds_under;            
extern unsigned char	titlephase;
extern unsigned int   score;
extern unsigned char	lives;
extern unsigned char	level;
extern unsigned int   topMem;
extern unsigned char  chbase1;
extern unsigned int   row_addr;
extern unsigned char  exit_cx;
extern unsigned char  exit_cy; 
extern unsigned char  exit_p0;
extern unsigned char  exit_p1; 


#include <atari.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <joystick.h>
#include <peekpoke.h>
#include <atari_equates.h>

#pragma codeseg("BANK0")
#pragma rodataseg("BANK0")

#pragma regvaraddr(on)  // Allow taking the address of register variables.
                      
   
                     








// extern const ;
// extern const ;
// extern const ;
// extern const ;

                                                                                                                          

unsigned char	TEMP0;
unsigned char	TEMP1;
unsigned char	TEMP2;
unsigned char	TEMP3;
unsigned char	TEMP4;
unsigned char	TEMP5;
unsigned char	TEMP6;
unsigned char	TEMP7;
unsigned char	TEMP8;
unsigned char	TEMP9;

unsigned char a; 
unsigned char b; 
unsigned char c; 
unsigned char d;
unsigned char e; 
unsigned char f; 
unsigned char g; 
unsigned char h;
unsigned char i; 
unsigned char j; 
unsigned char k; 
unsigned char l;

unsigned char difficulty = 0;


unsigned short int hiscore [11] = {0,0,0,0,0,0,0,0,0,0,0}; //Set High Scores to 0 

unsigned int  SCREEN_ROW_ADDR[] = {   //Left most memory address of each screen line, incrementing 40 bytes per line.
    (GAME_SCREEN_ADDR +   0),(GAME_SCREEN_ADDR +   40), (GAME_SCREEN_ADDR +  80), (GAME_SCREEN_ADDR + 120), (GAME_SCREEN_ADDR + 160),
    (GAME_SCREEN_ADDR + 200), (GAME_SCREEN_ADDR + 240), (GAME_SCREEN_ADDR + 280), (GAME_SCREEN_ADDR + 320), (GAME_SCREEN_ADDR + 360),  
  	(GAME_SCREEN_ADDR + 400), (GAME_SCREEN_ADDR + 440), (GAME_SCREEN_ADDR + 480), (GAME_SCREEN_ADDR + 520), (GAME_SCREEN_ADDR + 560),
  	(GAME_SCREEN_ADDR + 600), (GAME_SCREEN_ADDR + 640), (GAME_SCREEN_ADDR + 680), (GAME_SCREEN_ADDR + 720), (GAME_SCREEN_ADDR + 760),
    (GAME_SCREEN_ADDR + 800), (GAME_SCREEN_ADDR + 840), (GAME_SCREEN_ADDR + 880), (GAME_SCREEN_ADDR + 920), (GAME_SCREEN_ADDR + 960),
    (GAME_SCREEN_ADDR + 1000) 
};    

#pragma codeseg("CODE")
  
void Display_Information_Line(void)
// Displays Current Score, Lives, and Level
	{
	gotoxy(0, 0);
	printf("SCORE:\n");
	gotoxy(6, 0);
	printf (score);
  if(lives!=255)
      {
    	gotoxy(12, 0);
    	printf("LIVES:\n");
    	gotoxy(18, 0);
    	printf (lives);
      }
	gotoxy(26, 0);
	printf("LEVEL:\n");
	gotoxy(32, 0);
	printf (level);
  }

void ShowTitleScreen(void)
{
  //memcpy   (void* dest, const void* src, size_t count);
  //memmove   (void* dest, const void* src, size_t count);
  
    POKE(82,0);
    POKE(710,0);
    POKE(709,12);
    POKE(NMIEN,0);
    POKE(DMACTL,0);
    POKE(PRIOR,0);
    POKE(HITCLR,0);
    
    POKE (COLPF2,68);
    POKE (COLBAK,15);
    
//  asm ("JSR SILENCE");
    memset(MIBANK, 0, 1279);
    memset(SCREEN_ADDR, 0, 1024);                        

    titlephase = 0;  
    i = 6;
    k = 6;

     while (i > 0)
     {
        if(score > hiscore[i])
        {
          k=i;                
        }
     i = i - 1;
     }
     if (k < 5)
     {
      i = 5;  
      do
      {
        hiscore[i] = hiscore[i - 1];
        i = i - 1;    
      }
      while (i != k);
      hiscore[k] = score;
     }  
	   POKEW (DLISTW,&display_list_title); 	 
	   POKEW (SDLSTW,&display_list_title); 
	   POKEW (SAVMSC,&SCREEN_ADDR); 
	   POKE  (CHBAS,(&CHARSET_GAME)>>8);     
     clrscr();
	   gotoxy(0, 0); 
	   printf("           ATARI 8-BIT C VERSION        \n");
	   printf(" PROGRAMMING             PETER J. MEYER \n");
	   printf("                                        \n");
	   printf(" GRAPHICS                               \n");
	   printf(" SOUND AND MUSIC                        \n");        
	   TEMP5 = 0; 
	   POKE (PRIOR,1);
	   k = 6;
	   i = 5;
     POKE (COLOR0,0xD8);	
	   POKE (COLOR1,06);
     POKE (COLOR2,0xAA);
     POKE (COLOR3,54);
	   POKE (COLOR4,34);

     POKE (GRACTL,0);        
     POKE (NMIEN,192);
     POKE (DMACTL,34);
     Display_Information_Line;

    while (TEMP5 = 0)
    {     
        if (PEEK(CONSOL) & 0x01 == 0)
          {
            TEMP5 = 255;
          }
        POKE (NMIEN,64);
     while (PEEK(CONSOL) & 0x01 == 0)
     {
     } 
}





void Display_Game_Over(void)
	{ //Display Game Over Message
	gotoxy(12, 0);
	printf("GAME OVER    \n");
  }


void Initialize_Level(void)
{
	clrscr();
	mind_color=70;
  for( i = 10; i < 255; i = i + 1 ){

//asm {
//	LDA RANDOM
//	CLC
//	ADC #<game_screen
//	STA NDX0
//	LDA RANDOM
//	AND #3
//	ADC #>game_screen
//	STA NDX1
//	LDA RANDOM
//	AND #3
//	ORA #68
//	LDY #0
//	STA (NDX0),Y
//};
}

    // Randomly place 64 minds on the screen using some assembly language.
	for( i = 10; i <= 255; i = i + 1 ){
//asm {
			//LDA RANDOM
			//CLC
			//ADC #<game_screen
			//STA NDX0
			//LDA RANDOM
			//AND #3
			//ADC #>game_screen
			//STA NDX1
			//LDA #193
			//LDY #0
			//STA (NDX0),Y
//};
}
	
        character_px =124;
        character_py =216;
        character_status =0;
        a = (character_px - 48) / 4;
				b = (character_py - 24) / 8;
        for( j = b - 2; j <= b + 3; j = j + 1 ){			
				  for( i = a - 2; i <= a + 3; i = i + 1 ){
								c = GAME_SCREEN_ADDR + i + 40 * j;
								e = PEEK(c);
								if(e==193)
                {
                  POKE(c,0);
                } 
					}
        }
			exit_cx = (rand()) * 2;
			exit_cy = 0;
			exit_p0 = exit_cx * 4 + 46;
			exit_p1 = exit_p0 + 8;
      c = GAME_SCREEN_ADDR + exit_cx;           
      POKEW(c+00,19274);
			//POKE (c+00,74);
      //POKE (c+01,75);
			POKEW (c+40,0);
      //POKE (c+41,0);
}



void Main_Game_Loop(void)
    {
    while (character_status <= 127);
      {			
            if (prior_rt_clock != PEEK(RTCLOK+0))
                {				              
				        prior_rt_clock = PEEK(RTCLOK+0);																							
        		    if (show_countdown >0)
                    {
        			      show_countdown = show_countdown - 1;
                    }			  					
        		    else if (mind_color > 0x32)
                    {
                    mind_color = mind_color - 1;			  						
					          if (mind_color = 0x32) 
                        {
                        mind_color = 0x22;
                        }
                    }					  					
        	  	  }										
        	     if ((mind_color = 0x22) && (show_countdown = 0))
                  {											                                                                                                                                                                                     						  				                                            
                  a = (character_px - 47) / 4;
                  b = (character_py - 24) / 8;
                	if (minds_found > 0)
                  	{
                  	  for (j = b - 2; j <= b + 3; j = j + 1)
                  	  {
                  		  if ((j >= 0) && (j < 25))
                  		  {
                  			  row_addr = screen_rows[j] + a;
                  			  for (c = row_addr - 2; c <= row_addr + 3; c = c +1)
                  			  {
                  				  e = PEEK(c);
                  				  if (e == 65)
                  				  {
                  					 POKE (c,193);
                  				  }
                  			  }
                  		  }
                  	  }
                  	}
                  }								  
                  if (character_status = 0)
                    { 
									   stick_read = (PORTA & 15);
                    }				
						        g = (PEEK(RTCLOK+0) & 4); 
									//		asm {
									//		lda RT_CHECK
									//		AND #4
									//		STA G
								    //};		
									  f=0;  
				          	if (stick_read & 1==0) 
                      {
				          		character_py = character_py - 1;
				          		f=1+g;
				          	  }
				          	if (stick_read & 2==0)
                      {
				          		character_py = character_py + 1;
				          		if (character_py>232)
                          {
                          character_py = 232;
                          }
					          	f=3+g;
                      }                                                    
								if (stick_read && 4 == 0)
								{
										character_px = character_px - 1;
										if (character_px < 48)
										{
											character_px = 48;
										}
										f = 2 + g;
								}
									  if (stick_read && 8 == 0)
									  {
										  character_px = character_px + 1;
										  if (character_px > 200)
										  {
											  character_px = 200;
										  }
										  f = 4 + g;
									  }
									a = (character_px - 47) / 4;
									b = (character_py - 24) / 8;
									POKE (PCOLR0,202);
									g = 0;
									  for (j = b - 2; b + 3; j=j+1)
									  {
										if (j >= 0 && j < 25)
										  {
						          row_addr = screen_rows[j + a];
						          h = 0;
						          for (c = row_addr - 2; row_addr + 3; c=c+1)
						              {
													e = PEEK(c);
													if (e == 193)
  													{
  								          POKE(c,65);
  								          minds_found = +1;
  								          if (((g == 1) || (g == 2)) & ((h == 2) || (h == 3)))
  								            {
  									          POKE (PCOLR0,15);
  									          character_status = 1;
  														// Start_Sound_Effect(0,1);
  														}
  													}
							            h = h + 1;
											    }
										  }
									  }
									if (character_py < 38)
									{
										  character_py = 38;
										if ((character_px > exit_p0) && (character_px < exit_p1))
										{
											 if (character_status == 0)
											 {
												 character_status = 32;
												// Start_Sound_Effect(1,1);
											}
										}
									}
								if ((character_status > 0) && (character_status < 31))
								{
									character_status = character_status + 1;
									if (character_status == 30)
									{
										character_status = 128;
									}
									if (character_status < 16)
									 {
					           f = 16 + (character_status/4);
				           }
									if (character_status > 15)
									{
										f = 19;
										character_px = 0;
									}
								}
								if ((character_status > 31) && (character_status < 64))
								{
									character_status = character_status + 1;
									if (character_status == 64)
									{
										character_status = 144;
									}
									if (character_status && 1 == 1)
									{
										POKEW(GAME_SCREEN_ADDR + exit_cx,19274);
									}
									else
									{
										POKEW(GAME_SCREEN_ADDR + exit_cx,0);
								  }
							  }  
		  if (PEEK(53279U) != 7) 
        {
        character_status = 132;
        }
	   }
  }


//{***************************************************************************************}
//{************************************** MAIN *******************************************}
//{***************************************************************************************}

void main(void)
{
  topMem = chbase1 * 256;
//  TopLogicLoop:
	while (1)		
    {
      ShowTitleScreen();
		  score = 0;
	    lives = 5;
	    level = 1;
	    character_status  =  0;
//	    CRT_INIT (SCREEN_ADDR,40,26);
	            
// Game Initialization here
	    clrscr();  
	    memset(MIBANK, 0, 1279);	    
	    POKEW (DLISTW,display_list_game);
      POKEW (SDLSTW,display_list_game); 	  
	    POKEW (SAVMSC,SCREEN_ADDR); 
	    // POKE SETCHARSET(HI(CHARSET_GAME));
	    POKE  (CHBAS,(CHARSET_GAME)>>8);
	    while (character_status != 159);
        {		
    		    Initialize_Level();
//  		    asm ("JSR SILENCE");
      	    POKE (COLOR0,142);	
      	    POKE (COLOR1,212);
      	    POKE (COLOR3,150);
      	    POKE (COLOR4,34);
      	    POKE (COLPM0,202);
      	    POKE (COLPM1,250);
      	    POKE (COLPM2,136);
      	    POKE (COLPM3,36);				
      	    POKE (SIZEP0, PMG_SIZE_NORMAL);
      	    POKE (SIZEP1, PMG_SIZE_NORMAL);
      	    POKE (SIZEP2, PMG_SIZE_NORMAL);
      	    POKE (SIZEP3, PMG_SIZE_NORMAL);
            POKE (PMBASE,(PMBANK)>>8);
            POKE (GRACTL,3);
  //    	        PMG_Init(hi(PMBANK), 48  OR PMG_sdmctl_DMA_both OR PMG_sdmctl_oneline OR PMG_sdmctl_screen_normal);
	          Display_Information_Line;
//			SetVBLI(@GameVBI);	        
            POKE (NMIEN,192);
            POKE (DMACTL,62);
	
      			show_countdown =  180;
      			mind_color = 0x3F;	
			
            f  = 0; 				
            prior_rt_clock  =  PEEK(RTCLOK+0);
            Main_Game_Loop();
	  		
	  		if (character_status == 128) 
            { 
              lives  =  lives - 1; 
              if (lives == 255) 
                {
                character_status  =  159;
                character_px  = 0;
                Display_Game_Over;
                }              
            }  
		    if (character_status = 144)
          {
		    	   score  = score + 10;
		    	   level  = level + 1;
          }
	     } 
	    if (character_status == 159)
        {
			    while (character_status != 80)
          { 				
				   if (prior_rt_clock != PEEK(RTCLOK+0))
            {
					   character_status  =  character_status - 1;
					   prior_rt_clock  =  PEEK(RTCLOK+0);
            }
				  }
		    } 						              
    }
}


// CHARSET_ADDRESS rcdata 'Mind Field\MINDFIELD.FNT'



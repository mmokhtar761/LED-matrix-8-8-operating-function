/*
 * File:   mainLMv4.c
 * Author: Mohamed Mokhtar
 *
 * Created on March 13, 2020, 9:08 PM
 */
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "Config.h"
#define _XTAL_FREQ 4000000 

void write_led(unsigned char ti , char wrds[]  );

void main(void) {
    while (1){
    write_led(240,"MOHAMED  AHMED");
    }
    return;
}

void write_led( unsigned char ti, char wrds[]){
    
    TRISD = 0x00;
    TRISB = 0x00;
    //Arrays of the characters 
    unsigned char UR [] =  {0b00111111,0b0111111,0b11000000,0b11000000,0b11000000,0b11000000,0b0111111,0b00111111};
    unsigned char IR [] =  {0b11000011,0b11000011,0b11000011,0b11111111,0b11111111,0b11000011,0b11000011,0b11000011};
    unsigned char AR [] =  {0b11000000,0b00111000,0b00011110,0b000011011,0b000011011,0b00011110,0b00111000,0b11000000};
    unsigned char MR [] =  {0xFF,0xFF,0b00000110,0b00011000,0b00011000,0b00000110,0xFF,0xFF};
    unsigned char OR [] =  {0b00111100,0b01111110,0b11000011,0b11000011,0b11000011,0b11000011,0b01111110,0b00111100};
    unsigned char HR [] =  {0xFF,0xFF,0b0011000,0b0011000,0b0011000,0b0011000,0xFF,0xFF};
    unsigned char KR [] =  {0xFF,0xFF,0b00011000,0b00100100,0b01100110,0b11000011,0b10000001,0b10000001};
    unsigned char ER [] =  {0xFF,0xFF,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011};
    unsigned char DR [] =  {0xFF,0xFF,0b11000011,0b11000011,0b11000011,0b11000011,0b01111110,0b00111100};
    unsigned char RR [] =  {0b11111111,0b11111111,0b00011011,0b00011011,0b00111011,0b01111011,0b11011110,0b10011100};
    unsigned char SRr[] =  {0b11011111,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11111011,0b11111011};
    //special shapes
    unsigned char _H[]  = {0b00001100,0b00011110,0b00111100,0b01111100,0b01111100,0b00111100,0b00011110,0b00001100};
    //unsigned char _H2[] = {0b00001110,0b00011111,0b00111110,0b11111100,0b00111110,0b00011111,0b00001110,0x00};
    unsigned char _SM[] = {0b00110000,0b01110110,0b11000110,0b11000000,0b11000000,0b11000110,0b01110110,0b00110000};
    unsigned char spc[] =  {0,0,0,0,0,0,0,0};
    
    unsigned char cc = 0b10000000;
    float sp = 50.0-((float)ti/255.0)*50.0;
    unsigned char t ;                             //time coefficient
    unsigned char* FR ;
    unsigned char* SR=spc ;
    
 
    
    for (unsigned char w=0  ; w<strlen(wrds); w++)
    {
      FR =SR;
     
      if      (wrds[w]=='H') SR = HR;
      else if (wrds[w]=='U') SR = UR;
      else if (wrds[w]=='K') SR = KR;
      else if (wrds[w]=='A') SR = AR;
      else if (wrds[w]=='O') SR = OR;
      else if (wrds[w]=='E') SR = ER;
      else if (wrds[w]=='M') SR = MR;
      else if (wrds[w]=='D') SR = DR;
      else if (wrds[w]=='S') SR =SRr;
      else if (wrds[w]=='R') SR = RR;
      else if (wrds[w]=='I') SR = IR;
      else if (wrds[w]==' ') SR =spc;

      else if (wrds[w]=='*') SR = _H;
      else if (wrds[w]=='@') SR =_SM;
      
      for ( unsigned char j=0;j<9;j++)    // incrementing the col
      { 
        do{                            
           t=t+1;
           for (unsigned char i=0;i<8;i++)
            {
             PORTB = ~(cc>>i);
             if (i+j<8){PORTD = FR[i+j];}
             else if (i+j==8){PORTD = 0x00;}
             else if (i+j>8) {PORTD = SR [i+j-9];}
             __delay_ms(5);
            }
        } while (t < sp ) ;
        t=0;
        __delay_ms(20);
      }
    }
    return;
}

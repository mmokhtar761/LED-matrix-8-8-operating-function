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
#include <stdlib.h>
#define _XTAL_FREQ 3686400 


void write_led(unsigned char ti , char wrds[]  );
void ST_UART_Rc (void) ;
char READ_UART  (void) ;
//void ST_UART_Tr (void) ;
//void WRITE_UART (char word);

void main(void) {
    unsigned char i ;
    char STRdis [20];
    unsigned char n[3];
    ST_UART_Rc ()   ;
    n[0]  = READ_UART(); // Getting required data length in two digits _ limited to 20
    n[1]  = READ_UART() ;  
    n[2]  = '\0';
    for ( i=0;i<atoi (n);i++) STRdis[i] = READ_UART ();// Store aimed data with length n 
    STRdis[atoi (n)] = '\0';
    for ( i = 0 ;i < 3 ;i++) write_led(240,STRdis);    //Repeat for 3 times
    return;
}

void write_led( unsigned char ti, char wrds[]){
    
   TRISD = 0x00;                                  // Port D represent rows (positive of LEDs)
   TRISB = 0x00;                                  // Port B represent columns (GND of LEDs)
    
    //Arrays of the characters 
   const unsigned char UR [] =  {0b00111111,0b0111111,0b11000000,0b11000000,0b11000000,0b11000000,0b0111111,0b00111111};
   const unsigned char IR [] =  {0b11000011,0b11000011,0b11000011,0b11111111,0b11111111,0b11000011,0b11000011,0b11000011};
   const unsigned char AR [] =  {0b11000000,0b00111000,0b00011110,0b000011011,0b000011011,0b00011110,0b00111000,0b11000000};
   const unsigned char MR [] =  {0xFF,0xFF,0b00000110,0b00011000,0b00011000,0b00000110,0xFF,0xFF};
   const unsigned char OR [] =  {0b00111100,0b01111110,0b11000011,0b11000011,0b11000011,0b11000011,0b01111110,0b00111100};
   const unsigned char HR [] =  {0xFF,0xFF,0b0011000,0b0011000,0b0011000,0b0011000,0xFF,0xFF};
   const unsigned char KR [] =  {0xFF,0xFF,0b00011000,0b00100100,0b01100110,0b11000011,0b10000001,0b10000001};
   const unsigned char ER [] =  {0xFF,0xFF,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011};
   const unsigned char DR [] =  {0xFF,0xFF,0b11000011,0b11000011,0b11000011,0b11000011,0b01111110,0b00111100};
   const unsigned char RR [] =  {0b11111111,0b11111111,0b00011011,0b00011011,0b00111011,0b01111011,0b11011110,0b10011100};
   const unsigned char SRr[] =  {0b11011111,0b11011011,0b11011011,0b11011011,0b11011011,0b11011011,0b11111011,0b11111011};
    //special shapes
   const unsigned char _HEART[] = {0b00001100,0b00011110,0b00111100,0b01111100,0b01111100,0b00111100,0b00011110,0b00001100};
    //unsigned char _H2[] = {0b00001110,0b00011111,0b00111110,0b11111100,0b00111110,0b00011111,0b00001110,0x00};
   const unsigned char _SMILE[] = {0b00110000,0b01110110,0b11000110,0b11000000,0b11000000,0b11000110,0b01110110,0b00110000};
   const unsigned char spc[]    =  {0,0,0,0,0,0,0,0};
    
    unsigned char cc = 0b10000000;
    float sp = 50.0-((float)ti/255.0)*50.0;      //TIME for scrolling 
    unsigned char t ;                            //time coefficient
    unsigned char* FR ;                          // pointer to the first active row 
    unsigned char* SR=spc ;                      // pointer to the second active row (start with space)
    
 
    
    for (unsigned char w=0  ; w<strlen(wrds); w++){
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
      else if (wrds[w]==' ') SR =spc;    //............
      
      else if (wrds[w]=='*') SR = _HEART;
      else if (wrds[w]=='@') SR =_SMILE;
      
      for ( unsigned char j=0;j<9;j++){     // incrementing the col
        do{                            
           t=t+1;
           for (unsigned char i=0;i<8;i++){
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
void ST_UART_Rc (void){        //Starting UART communication
    BRGH = 1 ;                 // HIGH speed baud rate
    SPBRG = 23 ;
    SYNC = 0 ;                 // Asynchronous mode 
    SPEN = 1 ;                 // Enabling serial pins 
    TX9  = 0 ;                 // Only 8 bit data 
    RCIE = 1 ;
    GIE  = 1;
    PEIE = 1;
    CREN = 1;                  // Enable Data continuous Reception
}
char READ_UART (void){         // Reading the buffer
    char r ;
    while (!RCIF);
    r  =  RCREG  ;
    RCIF = 0 ;
    return r; 
}

//based on code from https://www.best-microcontroller-projects.com/max7219.html

// Space invader By RaymondoH

// Based on https://gist.github.com/nrdobie/8193350


#include <SPI.h> 
#define SS_PIN 10 //Chip select

// MAX7219 SPI LED Driver
#define MAX7219_TEST 0x0f // in real code put into a .h file
#define MAX7219_BRIGHTNESS 0x0a // in real code put into a .h file
#define MAX7219_SCAN_LIMIT 0x0b // in real code put into a .h file
#define MAX7219_DECODE_MODE 0x09 // in real code put into a .h file
#define MAX7219_SHUTDOWN 0x0C // in real code put into a .h file
//11 x 8 Sprites
int sprite1[18] = {0, 112, 24, 253, 182, 188, 60, 188, 182, 253, 24, 112, 0, 0, 0, 0, 0, 0};//arms down
int sprite2[18] = {0, 14, 24, 189, 118, 60, 60, 60, 118, 189, 24, 14, 0, 0, 0, 0, 0, 0};//arms up

int motion[][9] = { {12, 13, 14, 15, 1, 2, 3, 4},
                   {11, 12, 13, 14, 15, 1, 2, 3},
                   {10, 11, 12, 13, 14, 15, 1, 2}, 
                   {9, 10, 11, 12, 13, 14, 15, 1},
                   {8, 9, 10, 11, 12, 13, 14, 15},
                   {7, 8, 9, 10, 11, 12, 13, 14},
                   {6, 7, 8, 9, 10, 11, 12, 13},
                   {5, 6, 7, 8, 9, 10, 11, 12},
                   {4, 5, 6, 7, 8, 9, 10, 11},
                   {3, 4, 5, 6, 7, 8, 9, 10},
                   {2, 3, 4, 5, 6, 7, 8, 9},
                   {1, 2, 3, 4, 5, 6, 7, 8},
                   {15, 1, 2, 3, 4, 5, 6, 7},
                   {14, 15, 1, 2, 3, 4, 5, 6},
                   {13, 14, 15, 1, 2, 3, 4, 5}, 
                   {12, 13, 14, 15, 1, 2, 3, 4},
                   {11, 12, 13, 14, 15, 1, 2, 3}}; //array to move the sprite across the display
                   
void maxTransferCMD(uint8_t address, uint8_t value) {  
uint8_t i;


  digitalWrite(SS_PIN, LOW);   
  SPI.transfer(address);      // Send address.
  SPI.transfer(value);        // Send the value.
  SPI.transfer(address);      // Send address. 
  SPI.transfer(value);        // Send the value.
  digitalWrite(SS_PIN, HIGH); // Finish transfer.
}

void maxTransferDATA(uint8_t address, uint8_t value, uint8_t v2) {  
uint8_t i;

  digitalWrite(SS_PIN, LOW);   

  SPI.transfer(address);      // Send address.
  SPI.transfer(value);        // Send the value.
  SPI.transfer(address);      // Send address. 
  SPI.transfer(v2);           // Send the value.

  digitalWrite(SS_PIN, HIGH); // Finish transfer.
}

void setup() {

  
  Serial.begin(9600);

  Serial.println("Debug MAX7219");

  pinMode(SS_PIN, OUTPUT);  

  SPI.setBitOrder(MSBFIRST);   // Reverse the SPI Data o/p. 
  SPI.begin();                 // Start SPI


  // Run test - All LED segments lit. 
  maxTransferCMD(MAX7219_TEST, 0x01);  delay(1000);  
  maxTransferCMD(MAX7219_DECODE_MODE, 0x00); // Disable BCD mode. 
  maxTransferCMD(MAX7219_BRIGHTNESS, 0x00);  // Use lowest intensity. 
  maxTransferCMD(MAX7219_SCAN_LIMIT, 0x0f);  // Scan all digits.
  maxTransferCMD(MAX7219_SHUTDOWN, 0x01);    // Turn on chip.
  maxTransferCMD(MAX7219_TEST, 0x00);        // Finish test mode.
  for (int clr = 0; clr <=8; clr++)
  {
    maxTransferDATA(clr,0 ,0 ); //clears display after tesy
  }
}

void loop() {  

int i; // Need signed numbers.
int Del = 500;//delay between sprite displays
   for(i=1;i<=15;i++) 
   {   
    //Display sprite (arms up)         
      maxTransferDATA(1,0 ,sprite1[motion[i][0]]); //Column 1
      //delay(Del);  
      maxTransferDATA(2,0 ,sprite1[motion[i][1]]); //Column 2
       //delay(Del);
      maxTransferDATA(3,0 ,sprite1[motion[i][2]]); //etc.
       //delay(Del);
      maxTransferDATA(4,0 ,sprite1[motion[i][3]]);
       //delay(Del);
      maxTransferDATA(5,0 ,sprite1[motion[i][4]]);
       //delay(Del);
      maxTransferDATA(6,0, sprite1[motion[i][5]]);
       //delay(Del);
      maxTransferDATA(7,0 ,sprite1[motion[i][6]]);
       //delay(Del);
      maxTransferDATA(8,0 ,sprite1[motion[i][7]]);
       delay(Del);

            
      //Display sprite (arms down)  
      maxTransferDATA(1,0 ,sprite2[motion[i][0]]);
      //delay(Del);  
      maxTransferDATA(2,0 ,sprite2[motion[i][1]]);
       //delay(Del);
      maxTransferDATA(3,0 ,sprite2[motion[i][2]]);
       //delay(Del);
      maxTransferDATA(4,0 ,sprite2[motion[i][3]]);
       //delay(Del);
      maxTransferDATA(5,0 ,sprite2[motion[i][4]]);
       //delay(Del);
      maxTransferDATA(6,0, sprite2[motion[i][5]]);
       //delay(Del);
      maxTransferDATA(7,0 ,sprite2[motion[i][6]]);
       //delay(Del);
      maxTransferDATA(8,0 ,sprite2[motion[i][7]]);
       delay(Del);
      
  
   }
}

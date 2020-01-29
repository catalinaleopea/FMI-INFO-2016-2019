#include "LedControl.h"
LedControl lc=LedControl(12,11,10,1);
unsigned long delaytime=1000;

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void c(){
 for(int row=1;row<=6;row++)
    for(int col=1;col<=5;col++){
        if((row==1||row==6)&&(col>1))
          lc.setLed(0,row,col,true);
         if((row==2||row==5)&&(col>0))
          lc.setLed(0,row,col,true);
         if((row==3||row==4)&&(col==1||col==2))
          lc.setLed(0,row,col,true);
    }
    delay(delaytime);
    lc.clearDisplay(0);
}
void a(){
   for(int row=1;row<=6;row++)
    for(int col=1;col<=6;col++){
       if((row==1)&&(col>1&&col<6))
          lc.setLed(0,row,col,true);
        if((row==2||row==4)&&(col>0))
          lc.setLed(0,row,col,true);
         if((row==3||row==4||row==5||row==6)&&(col==1||col==2||col==5||col==6))
          lc.setLed(0,row,col,true);
    }
    delay(delaytime);
    lc.clearDisplay(0);
}
void t(){
    for(int row=1;row<=6;row++)
    for(int col=1;col<=6;col++){
        if((row==1||row==2)&&(col>0))
          lc.setLed(0,row,col,true);
         if((row>=3)&&(col==3||col==4))
          lc.setLed(0,row,col,true);
    }
    delay(delaytime);
    lc.clearDisplay(0);
}
void loop() { 
  c();
  a();
  t();
  a();
}

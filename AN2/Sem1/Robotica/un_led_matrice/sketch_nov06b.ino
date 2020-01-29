#include "LedControl.h"
#define delaytime 100
LedControl lc=LedControl(12,11,10,1);
void setup() {
    lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
//  lc.setLed(0,2,2,true);

}

void loop() {
    for(int i=0;i<=8;i++)
    for(int j=0;j<=8;j++)
    if(i==j){
      lc.setLed(0,i,j,true);
       lc.setLed(0,i,7-i,true);
       delay(delaytime);
     }
   for(int i=8;i>=0;i--)
    for(int j=8;j>=0;j--)
    if(i==j){
      lc.setLed(0,i,j,false);
      lc.setLed(0,i,7-i,false);
      delay(delaytime);
     }
/*mareste c
  for(int var=3;var<9;var++){  
    for(int i=0;i<var;i++)
    {
      lc.setLed(0,0,i,true);
      lc.setLed(0,var,i,true);
      lc.setLed(0,i,0,true);
    }  
    delay(50);
    for(int i=0;i<var;i++)
    {
      lc.setLed(0,0,i,false);
      lc.setLed(0,var,i,false);
      lc.setLed(0,i,0,false);
    }
}*/
}

/*
 Autor:Leopea Catalina,grupa 243
 
 Nume joc: Repeater
 
 Tip: Single player

 Hardware: Arduino Uno, display matrice 8x8 cu driver 7219, 4x butoane, display LCD, potentiometru de 10K ohm,
4x rezistente 10K ohm, fire de legatura, 3x breadboard mare,1x breadbard mic

Am asamblat componentele dupa modelele urmatoare:
-matricea dupa modelul de la laborator
-butoanele https://www.arduino.cc/en/Tutorial/Button
-display-ul LCD  https://www.arduino.cc/en/Tutorial/HelloWorld

 Software:
Ideea joculului e de a afisa o secventa de sageti pe matrice, iar jucatorul sa o reproduca cu ajutorul a 4 butoane (stanga, dreapta,
sus, jos) avand doar doua vieti.  
Daca a introdus corect secventa trece la nivelul urmator, unde va fi generata o alta secventa de dimensiune mai mare cu o unitate.
Jocul se termina atunci cand utilizatorul introduce o secventa gresita, mai exact la prima sageata gresita din secventa.
La primele doua greseli viata jucatorului scade si se repeta nivelul la care a gresit cu o noua secventa generata de sageti, la a treia
greseala jocul s-a terminat.
Cu ajutorul display-ului LCD afisez un mesaj de inceput, pentru a sugera jucatorului sa apese un buton pentru a juca, apoi incepe
afisarea secventei, urmata de un afisaj special "GO" care indica randul jucatorului si un “smiley face” daca datele au fost corecte sau
“sad face” altfel. La sfarsitul jocului ecranul LCD va afisa un mesaj de final, dupa o apasare de buton scorul, iar inca o apasare 
va insemna optiunea de intoarcere la nivelul 1.

Evolutie in timp:
-doua vieti
-nivel
-dificultate: consta in numarul de sageti care apar pe display
       Ex:  La nivelul k apar k sageti pe display
            La nivelul k+1 apar k+1 sageti

 */
#include <LedControl.h>
#include <LiquidCrystal.h>

LedControl lc = LedControl(13, 10, 9, 1);
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);

const int buttonUp = A4;     //sus 
const int buttonDown = A5;   //jos
const int buttonLeft = A2;   //stanga
const int buttonRight = A3;  //dreapta

int buttonState1 = LOW; //sus
int buttonState2 = LOW; //jos
int buttonState3 = LOW; //stanga
int buttonState4 = LOW; //dreapta 

int randomArray[100]; //il setez pana la nivelul 100 maxim
unsigned long delayTime = 1000;
int level = 0;

int lifeLed1 = A0;
int lifeLed2 = A1;
int lives = 2;

void setup(){
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  lcd.begin(16, 2);

  pinMode(buttonUp, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonDown, INPUT);

  pinMode(lifeLed1, OUTPUT);
  pinMode(lifeLed2, OUTPUT);

}

//urmatoarele functii afiseaza intuitiv, dupa nume, un model pe matricea de LED-uri
//delay-urile din functiile pentru afisarea pe matrice au rolul de a lasa modelul pe ecran de delayTime ori
//pana sa trec la urmatoarea instructiune si sa curat matricea

//modelul de baza pentru fata
void face(){
  for(int row = 0; row <= 7; row++)
    for(int col = 0; col <= 7; col++){
      if(((row == 0 || row == 7) && (col > 1 && col < 6)) ||
        ((col == 0 || col == 7) && (row > 1 && row < 6))){
        lc.setLed(0, row, col, true);
      }
    }
  lc.setLed(0, 1, 1, true);
  lc.setLed(0, 1, 6, true);
  lc.setLed(0, 2, 2, true);
  lc.setLed(0, 2, 5, true);  
}

void smileyFaceDisplay(){
  face();
  lc.setLed(0, 4, 2, true);
  lc.setLed(0, 4, 5, true);
  lc.setLed(0, 5, 3, true);
  lc.setLed(0, 5, 4, true);
  lc.setLed(0, 6, 1, true);
  lc.setLed(0, 6, 6, true);
  delay(delayTime);
  lc.clearDisplay(0);  
}

void sadFaceDisplay(){
  face();
  lc.setLed(0, 4, 3, true);
  lc.setLed(0, 4, 4, true);
  lc.setLed(0, 5, 2, true);
  lc.setLed(0, 5, 5, true);
  lc.setLed(0, 6, 1, true);
  lc.setLed(0, 6, 6, true);
  delay(delayTime);
  lc.clearDisplay(0);
}

//indica randul jucatorului
void goDisplay(){
  for(int row = 1; row <= 6; row++)
    for(int col = 0; col <= 7; col++){
      if((col == 0 || col == 5 || col == 7) ||
        (((row == 1) || (row == 6)) && (col != 4)) ||
        ((row == 4) && (col == 2 || col == 3)) ||
        (row ==5 && col == 3)){
        lc.setLed(0, row, col, true);
      }
    }
  delay(delayTime);
  lc.clearDisplay(0);
}

//acestea sunt pentru sageti
int upDisplay(){
  for(int row = 1; row <= 6; row++)
    for(int col = 1; col <= 5; col++){
      if((col == 3) ||
        ((row == 2) && (col == 2 || col == 4)) ||
        ((row == 3) && (col == 1 || col == 5))){
        lc.setLed(0, row, col, true);
      }
    }
  delay(delayTime);
  lc.clearDisplay(0);
  return 1;
}

int downDisplay(){
  for(int row = 1; row <= 6; row++)
    for(int col = 2; col <= 6; col++){
      if((col == 4) ||
        ((row == 4) && (col == 2 || col == 6)) ||
        ((row == 5) && (col == 3 || col == 5))){ 
        lc.setLed(0, row, col, true);
      }
    }
  delay(delayTime);
  lc.clearDisplay(0);
  return 2;
}

int leftDisplay(){
  for(int row = 2; row <= 6; row++)
    for(int col = 1; col <= 6; col++){
      if((row == 4) ||
        ((col == 2) && (row == 3 || row == 5)) ||
        ((col == 3) && (row == 2 || row == 6))){ 
        lc.setLed(0,row,col,true);
      }
    }
  delay(delayTime);
  lc.clearDisplay(0);
  return 3;
}

int rightDisplay(){
  for(int row = 1; row <= 5; row++)
    for(int col = 1; col <= 6; col++){
      if((row == 3) ||
        ((col == 4) && (row == 1 || row == 5)) ||
        ((col == 5) && (row == 2 || row == 4))){ 
        lc.setLed(0, row, col, true);
      }
    }
  delay(delayTime);
  lc.clearDisplay(0);
  return 4;
}

//citirea unui buton si afisarea sagetii corespunzatoare pe matricea de LED-uri
int readButton(){
  do{
   //astept apasarea unui buton pentru reproducerea secventei
   buttonState1 = digitalRead(buttonUp);
   buttonState2 = digitalRead(buttonDown);
   buttonState3 = digitalRead(buttonLeft);
   buttonState4 = digitalRead(buttonRight);
  }while(buttonState1 == LOW && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW); 
  
  if (buttonState1 == HIGH) {
    return upDisplay();
  }

  if (buttonState2 == HIGH) {
    return downDisplay();
  }  
  if (buttonState3 == HIGH) {
    return leftDisplay();
  }
    
  if (buttonState4 == HIGH) {
    return rightDisplay();
  }
}

//afisarea randomizata a modelului pe matricea de LED-uri
void show(){
  for(int i = 0; i < level; i++){
    int arrow = random(1, 4);  //limitele min si max(sunt 4 sageti posibile)
    randomArray[i] = arrow;    //pune sageata in secventa
    if(i > 0 && randomArray[i - 1] == arrow){
      //daca  sunt elemente consecutive identice in secventa
      //aprind LED-urile din colturile matricei, altfel ar fi fost mai greu sa imi dau seama ca o sageata se repeta
      lc.setLed(0, 0, 0, true);
      lc.setLed(0, 0, 7, true);
      lc.setLed(0, 7, 0, true);
      lc.setLed(0, 7, 7, true);
      delay(delayTime);
      lc.clearDisplay(0);
    }
    switch(arrow){
      case 1:{
        upDisplay();
        break;
      }
      case 2:{
        downDisplay();
        break;
      }
      case 3:{
        leftDisplay();
        break;
      }
      case 4:{
        rightDisplay();
        break;
      }
    }
  }
}

//aceasta functie verifica rezultatul jucatorului
int go(){
  int isEqual = 1;                   //daca butonul apasat de user corespunde cu ce se astepta din model
  for(int i = 0; i < level && isEqual; i++){
    //citeste in continuare input de la user
    if(readButton() != randomArray[i]){
      //altfel se opreste la prima greseala
      isEqual=0;
    }
  }
  return isEqual;
}

//aceasta functie ii afiseaza user-ului un raspuns pozitiv sau negativ in functie de raspunsul sau
int play(){
  level++;
  show();
  goDisplay();
  if(go()){
    smileyFaceDisplay();
    return 1;                        // corect
  }
  else{
    sadFaceDisplay();
    return 0;                        //gresit
  }
}

//instructiunile pe care trebuie sa le execute in cazul in care jocul s-a terminat
void fail(){
  lives = 2;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game Over!");
  lcd.setCursor(0, 1);
  lcd.print("Press for score");
  do{
    buttonState3 = digitalRead(buttonLeft);
    if(buttonState3 == HIGH){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Score is ");
      lcd.setCursor(10, 0);
      level--;
      lcd.print(level);
      lcd.setCursor(0, 1);
      lcd.print("Press to replay"); //reiau jocul de la zero
    }
    //astept apasarea unui buton pentru a afisa scorul
  }while(buttonState3 != HIGH);
  do{
   buttonState2 = digitalRead(buttonDown);
   //astept apasarea unui buton pentru a reincepe jocul
  }while(buttonState2 != HIGH);
}

void Menu(){
  level = 0;
  digitalWrite(lifeLed1, HIGH);
  digitalWrite(lifeLed2, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("REPEATER");
  lcd.setCursor(0, 1);
  lcd.print("Press left key");   //asteapta raspuns pentru a incepe jocul
  buttonState3 = digitalRead(buttonLeft);
  if(buttonState3 == HIGH){
      //am apasat butonul
      int result = 1;
      do{                        //repeta asta pana cand jocul se termina
        lcd.clear();
        result = play();
        if(result == 0){
         if(lives == 2){//la prima greseala scad o viata
          digitalWrite(lifeLed2, LOW);
          lives--;
          level--;
         }
         else
          if(lives == 1){//la a doua greseala mai scad o viata
            digitalWrite(lifeLed1, LOW);
            lives--;
            level--;
          }
          else
            if(lives == 0){//am gresit si nu mai am vieti
              lives--;
            }
        }
      }while(lives >= 0);       //se termina cand nu mai am vieti
      fail();
      lcd.clear();
  }
}

void loop() {
  Menu();
}

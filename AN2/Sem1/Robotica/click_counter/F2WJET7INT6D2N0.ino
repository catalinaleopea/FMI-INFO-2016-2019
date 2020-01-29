//Code wtiren by YAHAV HADAD
// 2016
//All Rights Reserved ©

//ENJOY!!

//Initialize the 7 segment pins
int A = 3;
int B = 2;
int C = 4;
int D = 5;
int DP = 7;
int E = 6;
int F = 8;
int G = 9;

//Initialize the push buttons pins, push buttons states, and the counter
int switchUpPin = 13;
int switchDownPin = 12;
int counter = 0;
int buttonUpState = 0;
int lastButtonUpState = 0;
int buttonDownState = 0;
int lastButtonDownState = 0;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  //Start with the deceimal point off
  digitalWrite(DP ,HIGH);
}

void loop() 
{
  //Getting the reads from the buttons
  buttonUpState = digitalRead(switchUpPin);
  buttonDownState = digitalRead(switchDownPin);

  //Detecting button press and getting the button status
  //Do this for the button up
  if (buttonUpState != lastButtonUpState) 
  {
    if (buttonUpState == HIGH) 
    {
      //Reset the counter to -1
      if(counter == 9)
      {
        counter = -1;
      }
      //Increase the counter by 1
      counter++;
      //Print the counter to the console and calling the function
      Serial.println(counter);
      changeNumber(counter);
      //Delaying by 250 ms
      delay(250);
    }
    else
    {
        Serial.println("OFF");
    }
    //Delay to avoid button bouncing
   delay(50);
  }

  //Do this for the button down
  if (buttonDownState != lastButtonDownState) 
  {
    if (buttonDownState == HIGH) 
    {
      //Set the counter to 10
      if(counter == 0)
      {
        counter = 10;
      }
      //Decreases the counter by 1
      counter--;
      ////Print the counter to the console and calling the function
      Serial.println(counter);
      changeNumber(counter);
      //Delaying by 250 ms
      delay(250);
    }
    else
    {
        Serial.println("OFF");
    }
    //Delay to avoid button bouncing
   delay(50);
  }
  //Calling the function changeNumber with the arg counter
  changeNumber(counter);
}

//The function to display the numbers
void changeNumber(int buttonPress)
{
  switch (buttonPress)
  {
    //number 0
    case 0:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    //number 1
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    //number 2
    case 2:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    //number 3
    case 3:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    //number 4
    case 4:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 6
    case 6:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 7
    case 7:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    //number 8
    case 8:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 9
    case 9:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
  }
}


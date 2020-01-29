#define led_pin 11
#define led2 10
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val_senzor=analogRead(A0);//potentiometru
  /*if(val_senzor>500)
  {
    digitalWrite(led_pin,HIGH);
    delay(1000);
  }else{
    digitalWrite(led_pin,LOW);
    delay(1000);
  }*/
  int mappedval=map(val_senzor,0,1023,0,255);
  int mappedval2=map(val_senzor,0,1023,255,0);
  analogWrite(led_pin,mappedval);//cand intensitatea lui creste
  analogWrite(led2,mappedval2);//a lui scade si invers
  Serial.println(val_senzor);
// delay(1);
}

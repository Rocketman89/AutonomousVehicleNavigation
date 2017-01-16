int MpinP = 11; //pos lead motor
int MpinN = 10; //neg lead motor
void setup() {
  // put your setup code here, to run once:
pinMode(MpinP,OUTPUT);
pinMode(MpinN,OUTPUT);
Serial.begin(9600);
}

void loop() {
  int F = 1;
  // put your main code here, to run repeatedly:
if(F == 1){
  digitalWrite(MpinP,HIGH);
  digitalWrite(MpinN,LOW);
  delay(9000);
  Serial.print("Right Start\n");
  Serial.print("Right Finish\n");
  digitalWrite(MpinP,LOW);
  digitalWrite(MpinN,LOW);
  delay(100);
  
  F=0;
}
if(F == 0){
  digitalWrite(MpinP,LOW);
  digitalWrite(MpinN,HIGH);
  delay(9000);
  Serial.print("Left Start\n");
  Serial.print("Left Finish\n");
  digitalWrite(MpinP,LOW);
  digitalWrite(MpinN,LOW);
  delay(100);
  
  F=1;
  
}

}

int Ain1 = 11;
int Ain2 = 10;
int Bin3 = 6;
int Bin4 = 5;

void setup() {
// put your setup code here, to run once:
//                                             *EXAMPLE DRIVING FORWARD*
//int drivet = 5000; //seconds
//int sped = 150;
//forward(drivet, sped);
//forward(5000,0);
//                                             *EXAMPLE TURN*
//int turnt = 500; //seconds
//left(turnt);
//                                             *INSTRUCTION START HERE*  
int sppeed=150;
//Serial.begin(9600);
//Serial.println("3");
//delay(1000);
//Serial.println("2");
//delay(1000);
//Serial.println("1");
//delay(1000);
//Serial.println("BEGIN");
//delay(1000);
//                                             *ACTION STARTS HERE*
//backward(4000,sppeed);
accelF(sppeed);
forward(4000,sppeed);
left(500);
forward(4000,sppeed);
right(500);
right(500);
forward(4000,sppeed);
left(500);
deccelF(sppeed);
stopdrive();
delay(2000);
backward(4000,sppeed);
stopdrive();
}

void loop() {
  // put your main code here, to run repeatedly:

//int SensorValueOne = analogRead(A0);
//Serial.println(SensorValueOne);
//delay(500);
}

void accelF(int spd){
  int dt = 50;
  for(int dspd=20; dspd<=spd; dspd++){
    analogWrite(Ain1, 0);
    analogWrite(Ain2, dspd);
    delay(dt);
    readHall();
  }
}
void deccelF(int spd){
  int dt = 50;
  for(int dspd=spd; dspd>0; dspd--){
    analogWrite(Ain1, 0);
    analogWrite(Ain2, dspd);
    delay(dt);
    readHall();
  }
  stopdrive();
}

void forward(int dt, int spd){
  for(int i=dt; i>0; i-=6){
  analogWrite(Ain1, 0);
  analogWrite(Ain2, spd);
  delay(1);
  //delay(dt);
  readHall();
  }
}
void backward(int dt, int spd){
  for(int i=dt; i>0; i-=6){
  analogWrite(Ain1, spd);
  analogWrite(Ain2, 0);
  delay(1);
  //delay(dt);
  readHall();
  }
}
void right(int tt){       //500 right left and middle
  analogWrite(Bin3, 0);
  analogWrite(Bin4, 150);
  delay(tt);
  analogWrite(Bin3, 0);
  stopturn();
  readHall();
}
void left(int tt){        //500 right left and middle
  analogWrite(Bin4, 0);
  analogWrite(Bin3, 150);
  delay(tt);
  stopturn();
  readHall();  
}
void stopturn(){
  analogWrite(Bin3, 0);
  analogWrite(Bin4, 0);
}
void stopdrive(){
  analogWrite(Ain1, 0);
  analogWrite(Ain2, 0);
  
  analogWrite(Ain1, 40);
  analogWrite(Ain2, 0);
  delay(100);
  analogWrite(Ain1, 0);
  analogWrite(Ain2, 0);
  
}
void readHall(){
  int SensorValueOne = analogRead(A0);
  Serial.println(SensorValueOne);

}


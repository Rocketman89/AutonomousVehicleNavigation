//DRIFT CAR PORCHE 1
//RONALD WHITING

  //Actuators
  int Forward  = 1;
  int Backward = 2;
  int TLeft    = 3;
  int TRight   = 4;
  int HLight   = 5;
  int BLight   = 6;
  int LTSig    = 7;
  int RTSig    = 8;
  int          = 9;
  int          = 10;
  int          = 11;
  int          = 12;
  int          = 13;
  //Sensors
  int UltraSFront = 0;
  int UltraSLeft  = 1;
  int UltraSRight = 2;
  int             = 3;
  int             = 4;
  int             = 5;

void setup()
{
  pinMode(Forward,OUTPUT);
  pinMode(Backward,OUTPUT);
  pinMode(TLeft,OUTPUT);
  pinMode(TRight,OUTPUT);
  pinMode(HLight,OUTPUT);
  pinMode(BLight,OUTPUT);
  pinMode(LTSig,OUTPUT);
  pinMode(RTSig,OUTPUT);
  
  pinMode(UltraSFront,INPUT);
  pinMode(UltraSLeft,INPUT);
  pinMode(UltraSRight,INPUT);
  
}
For(MagF,Dist)
{
  analogWrite(Forward,Mag);
  Go=Mag
  delay(Go); 
}
Back(MagB)
{
  analogWrite(Backward,Mag);
  Go=Mag
  delay(Go); 

}
Left(DegL)
{
  analogWrite(TLeft,DegL);
  cDeg=
  delay(cDeg)
}
Right(DegR)
{
  analogWrite(TRight,DegL);
  cDeg=
  delay(cDeg)

}



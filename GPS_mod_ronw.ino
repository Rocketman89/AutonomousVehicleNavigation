#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// SERVO INITIALIZATIONS //
Servo myservo;
int pos =0;

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false  //ORIGINAL TRUE APPROVED KEEP FALSE!!

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup()  
{
  //SERVO PIN //
  myservo.attach(9);   
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);//ORIGINAL ON
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY); //NO SATELLITE# NO ALTITUDE NO QUALITY
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate ORIGINAL ON
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA); //ORIGINAL ON

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c; //THIS IS THE LINE WITH ALL DATA_RonW inserted(Serial.print("");) 
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    //Serial.print("\nTime: ");
    //Serial.print(GPS.hour, DEC); Serial.print(':');
    //Serial.print(GPS.minute, DEC); Serial.print(':');
    //Serial.print(GPS.seconds, DEC); Serial.print('.');
    //Serial.println(GPS.milliseconds);
    //Serial.print("Date: ");
    //Serial.print(GPS.day, DEC); Serial.print('/');
    //Serial.print(GPS.month, DEC); Serial.print("/20");
    //Serial.println(GPS.year, DEC);
    //Serial.print("Fix: "); Serial.print((int)GPS.fix);
    //Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    if (GPS.fix) {
      //Serial.print("Location: ");
      //Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      //Serial.print(", "); 
      //Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      //Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(GPS.longitudeDegrees, 4);
      
      //Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Heading Angle: "); Serial.println(GPS.angle);
      //Serial.print("Altitude (cm): "); Serial.println(GPS.altitude);
      //Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
      
      // NEW GEO LOCATION //////////////////////////////////////////////////
      double lat2=39.601558;    //28.1371;
      double lon2=-75.817613;   //-64.5643;
      Serial.print(lat2);
      Serial.print(", ");
      Serial.println(lon2);
      
      // BEARING CALCULATION/////////////////////////////////////////////////
      //Haversine Formula       
      double lat1=GPS.latitudeDegrees;
      double lon1=GPS.longitudeDegrees;
      
      double dlat=lat2-lat1;
      double dlon=lon2-lon1;
      
      double x=(sin(dlon*(PI/180)))*(cos(lat2*(PI/180)));
      double y=(cos(lat1*(PI/180))*sin(lat2*(PI/180)))-(sin(lat1*(PI/180))*cos(lat2*(PI/180))*cos(dlon*(PI/180)));
      double B=atan2(x,y)*(180/PI);
      int Heading = round(B);
      if (B < 0) {
          Heading=B+180;
          Serial.print("New Heading ");
          Serial.println(Heading); //if neg add 180
      }else{ 
          Heading=B;
          Serial.print("New Heading: ");
          Serial.println(Heading);
      }
      
      // COURSE CORRECTION //////////////////////////////////////////////////
      int CH = round(GPS.angle);
      //CH=66;
      int DH = Heading;
      int dCD=CH-DH;
      if ((CH-DH)>180) {
        pos=90+(DH+(360-CH));
        if (pos>=180){
          pos=180; //full right
        }
      }
      if ((dCD)>0){
        if((dCD)<180) {
          pos=CH-DH;
          if(pos>=90){
            pos=0; //full left
          }else if ((CH-DH)<0){
            pos=90+(DH-CH);
          }
        }
      }
    }
      //Serial.print("Course Correction: ");
      //Serial.println(CourseCor);

      Serial.print("\nServo Movement: ");
      Serial.println(pos);
      
      // DIRECTIONAL SERVO MOVEMENT /////////////////////////////////////////
          myservo.write(pos);
          delay(30);
      
      // SPACING FOR SERIAL BEAUTIFICATION
      Serial.print("\n\n");
      
    } 
  }

#include <Wire.h>
#include <HMC5883L.h>
#include <Servo.h> 

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

const int lenghtMsgmax = 4;
unsigned char msg[lenghtMsgmax];
int nbBytesRecus=0;
float angle = 0;
int wheelBase = 223;
float mmpd = (float)(wheelBase * PI / 360.0);
int speedTurn = 75;
int speedDrive = 200;
unsigned char wall = 0;
int epsilon = 3;
int epsilon2 = 5;

Servo myservo;

//unsigned long time;

//############################     SETUP FUNCTIONS      ##################################

//start the communication with the roomba
void rStart (){
    Serial1.write(128);
  delay(50);
}

//Put the roomba in full mode
void rFull(){
    Serial1.write(132);
  delay(50);
}

//Put the roomba in safe mode
void rSafe(){
    Serial1.write(131);
  delay(50);
}

//#############################    ROOMBA COMMAND FUNCTIONS  ###########################

//command motor function
void drive(uint16_t velocity1, uint16_t velocity2){
  // velocity from -255 to +255 mm/s

    int rv_high = (velocity1 >> 8 ) & 255;
    int rv_low = velocity1 & 255;
    int lv_high = (velocity2 >> 8) & 255;
    int lv_low = velocity2 & 255;

     Serial1.write(145);      
     Serial1.write(rv_high);
     Serial1.write(rv_low);
     Serial1.write(lv_high);
     Serial1.write(lv_low);
     delay(10);
     Serial1.flush();
}

void drive2(uint16_t velocity, uint16_t radius){
  // velocity from -255 to +255 mm/s

    int v_high = (velocity >> 8 ) & 255;
    int v_low = velocity & 255;
    int r_high = (radius >> 8) & 255;
    int r_low = radius & 255;

     Serial1.write(137);      
     Serial1.write(v_high);
     Serial1.write(v_low);
     Serial1.write(r_high);
     Serial1.write(r_low);
     delay(10);
     Serial1.flush();
}

void driveMMS(int value){
  int moveSpeed = speedDrive;
  if(value < 0){
    moveSpeed = -speedDrive;
    value *= -1;
  }
  drive(moveSpeed, moveSpeed);
  delay(value);
  drive(0,0);
  Serial.write(100);
}

//Deprecated
void turnOld(int angleWanted){
  float pauseTime;
  int dir = -1;
  if(angleWanted < 0){
    angleWanted *= -1;
    dir = 1;
  }
  pauseTime = (mmpd * angleWanted / speedTurn);
  drive2(speedTurn, dir);
  delay((int)(pauseTime * 1000));
  drive(0,0);
}

void turn(int angleWanted){
  int dir = -1;
  int diff = 0;
  int diffOld = 0;
  int turning = 1;
  if(angleWanted < 0){
    angleWanted = 0;
  }
  else if(angleWanted > 360){
    angleWanted = 360;
  }
  diff = angle - angleWanted;
  if(diff > 0){
    dir = 1;
  }
  drive2(speedTurn, dir);
  do{
    diffOld = diff;
    angle = (int)readCompass();
    diff = angle - angleWanted;
    if(abs(diff) > abs(diffOld) + epsilon){
      turning = 0;
    }
  }while( (abs(diff)) > epsilon);//((abs(diff)) > epsilon) &&
  drive(0,0);
  Serial.write(116);
}

//Do the action asked
void cmd(int id, int value){
  switch(id){
    case 1:
      drive(value,value);
      break;
    case 2:
      turn(value);
      /*angle += value;
      if(angle < 0){
        angle = 360 - angle;
      }
      else if(angle > 360){
        angle -= 360;
      }*/
      break;
    case 3:
      drive(0,0);
      break;
    case 4:
      Serial.print(angle);
      break;
    case 5:
      driveMMS(value);
      break;
    case 6:
      turnServo(value);
      
  }  
}

void turnServo(int angle){
  if(angle > 180){
    angle = 180;
  }
  if(angle < 0){
    angle = 0;
  }
  myservo.write(angle);
}


//#############################   SENSORS FUNCTIONS  ###########################

void askSensor(int id){
  Serial1.write(142);
  Serial1.write(id);
  delay(50);
  
  Serial1.flush();
}

float readCompass(){
  // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.readRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.readScaledAxis();
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -2��37' which is -2.617 Degrees, or (which we need) -0.0456752665 radians, I will use -0.0457
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.00436332313;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 

  delay(50);//of course it can be delayed longer.
  
  return headingDegrees;
}

void readSensors(){
  askSensor(7);
  delay(50);
  if(Serial1.available()){
    wall = Serial1.read() ;
  }
  else{
    wall = -1;
  }
  float compass = readCompass();
  angle = compass;
  //Serial.println((angle >> 8) & 255);
  //Serial.println(angle & 255);
}
  
  
//########################## SETUP AND LOOP  ##########################

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  
  //Compass setup
  Wire.begin(); // Start the I2C interface.
  error = compass.setScale(1.3); // Set the scale of the compass.
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS);
  
  myservo.attach(8);
  
  for (int i=0; i<lenghtMsgmax; i++) {
    msg[i] = -1;
  }
  
  rStart();
  rSafe();
}

void loop(){
  int byte1 = 0;
  int byte2 = 0;
  int value = 0;
  int sign = 0;
  int id = 0; // 1 = move - 2 = turn - 3 = stop - 4 = askAngle - 5 = drive - 6 turn servo
  while (Serial.available() > 0){
    if(nbBytesRecus==lenghtMsgmax){
      nbBytesRecus = 0;
    }
    for (int i=0; i<lenghtMsgmax; i++) { //read the inpu       
      if (Serial.available() > 0) {
        unsigned char readByte = Serial.read();
        nbBytesRecus++;
        msg[i] = readByte;
        delay(10);
      }        
    }
    
    if(nbBytesRecus==lenghtMsgmax){
      // Get the type of command asked
      if(msg[0] == 109){ //Command move
        id = 1;
      }
      else if(msg[0] == 116){ //Command turn
        id = 2;
      }
      else if(msg[0] == 115){ //Command stop
        id = 3;
      }
      else if(msg[0] == 97){ //ask data
        id = 4;
      }
      else if(msg[0] == 100){ //drive for specific duration
        id = 5;
      }
      else if(msg[0] == 99){ //turn the servo motor
        id = 6;
      }
      if(msg[1]==43) { // présence of sign "+"
        sign = 1;
      }
      else if(msg[1]==45) { // présence of sign "-"
        sign = -1;
      }
      byte1 = msg[2];
      byte2 = msg[3];
      value = sign * (byte1 * 256 + byte2);
      cmd(id,value);
      //Serial.flush();
    }
  }
  readSensors();
  //Serial.println(millis() - time);
  //time = millis();
}

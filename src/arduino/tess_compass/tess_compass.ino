#include <Wire.h>
#include <HMC5883L.h>

// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;

int nbIter = 180;
int speedRot = 70;




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







//#############################   SENSORS FUNCTIONS  ###########################


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

  delay(45);//of course it can be delayed longer.
  
  return headingDegrees;
}
  
  
//########################## SETUP AND LOOP  ##########################

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);
  
  //Compass setup
  Wire.begin(); // Start the I2C interface.
  error = compass.setScale(1.3); // Set the scale of the compass.
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS);
  
  rStart();
  rSafe();
}

void loop(){
  drive(-speedRot, speedRot);
  for(int i = 0; i < nbIter ; i++){
    Serial.println(readCompass());
  }
  drive(0,0);
  delay(1000000);
}

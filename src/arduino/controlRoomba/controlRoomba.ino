#define PI 3.141592

const int lenghtMsgmax = 4;
unsigned char msg[lenghtMsgmax];
int nbBytesRecus=0;
float angle = 0;
int wheelBase = 223;
float mmpd = (float)(wheelBase * PI / 360.0);
int speedTurn = 300;
int speedDrive = 200;



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

void driveMMS(uint16_t value){
  drive(speedDrive, speedDrive);
  delay(value);
  drive(0,0);
}

void turn(int angle){
  float pauseTime;
  int dir = -1;
  if(angle < 0){
    angle *= -1;
    dir = 1;
  }
  pauseTime = (mmpd * angle / speedTurn);
  drive2(speedTurn, dir);
  delay((int)(pauseTime * 1000));
  drive(0,0);
}

//Do the action asked
void cmd(int id, int value){
  switch(id){
    case 1:
      drive(value,value);
      break;
    case 2:
      turn(value);
      angle += value;
      if(angle < 0){
        angle = 360 - angle;
      }
      else if(angle > 360){
        angle -= 360;
      }
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
      
  }  
}


//#############################    ROOMBA SENSORS FUNCTIONS  ###########################

unsigned int readEncoder(){
  unsigned int result = 0;
  Serial1.write(142);
  Serial1.write(44);
  delay(50);
  
  if (Serial1.available() >= 2){
    unsigned char readByte1 = Serial1.read();
    unsigned char readByte2 = Serial1.read();

    result = (readByte1 <<8) + readByte2;
  }
  Serial1.flush();
  return result;
}


void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  
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
  int id = 0; // 1 = move - 2 = turn - 3 = stop - 4 = askAngle - 5 = drive
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
      else if(msg[0] == 97){ //ask angle
        id = 4;
      }
      else if(msg[0] == 100){ //drive for specific duration
        id = 5;
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
      Serial.flush();
    }
  }
}

const int lenghtMsgmax = 3;
char msg[lenghtMsgmax];
int nbBytesRecus=0;


//############################     FONCTIONS CONNEXION  REVEIL ROOMBA       ##################################

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

//#############################    COMMAND GENERIQUE DE DÉPLACEMENT R_DRIVE    ###########################

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

//Do the action asked
void cmd(int id, int value){
  switch(id){
    case 1:
      drive(value,value);
      break;
    case 2:
      drive(value, -value);
      break;
    case 3:
      drive(0,0);
      break;
  }  
}

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  
  for (int i=0; i<lenghtMsgmax; i++) {
    msg[i] = -1;
  }
  
  rStart();
  rFull();
}

void loop(){
  int value = 0;
  int id = 0; // 1 = move - 2 = turn - 3 = stop
  while (Serial.available() > 0){
    if(nbBytesRecus==3){
      nbBytesRecus = 0;
    }
    for (int i=0; i<lenghtMsgmax; i++) { //read the inpu       
      if (Serial.available() > 0) {
        char readByte = Serial.read();
        nbBytesRecus++;
        msg[i] = readByte;
        delay(10);
      }        
    }
    
    if(nbBytesRecus==3){
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
      if(msg[1]==43) { // présence of sign "+"
        value = int(msg[2]);
      }
      else if(msg[1]==45) { // présence of sign "-"
        value = - (int(msg[2]));
      }
      cmd(id,value);
      Serial.flush();
    }
  }
  
}

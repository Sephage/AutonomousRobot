const int lenghtMsgmax = 3;
char msg[lenghtMsgmax];

//############################     FONCTIONS CONNEXION  REVEIL ROOMBA       ##################################

void rStart (){
    Serial1.write(128);
  delay(50);
}

void rFull(){
    Serial1.write(132);
  delay(50);
}

void rSafe(){
    Serial1.write(131);
  delay(50);
}

//#############################    COMMAND GENERIQUE DE DÉPLACEMENT R_DRIVE    ###########################


void rDrive(uint16_t velocity, uint16_t radius){
  // velocity de -500 à +500 mm/s
  // radius de -2000 mm à +2000 mm

    int v_high = (velocity >> 8 ) & 255;
    int v_low = velocity & 255;
    int r_high = (radius >> 8) & 255;
    int r_low = radius & 255;
//  usage de la liasion serial1 avec l'ordi pour tracer les infos envoyées au roomba
      Serial1.write(137);
      
      Serial1.write(v_high);
      Serial1.write(v_low);
      Serial1.write(r_high);
      Serial1.write(r_low);
      delay(10);
      Serial1.flush();
      
      return;
}

void cmd(int id, int value){
  
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
    int nbBytesRecus=0;
    for (int i=0; i<lenghtMsgmax; i++) { // boucle pour lecture successive des caractères en attente jusqu'à épuisement de la chaine        
      if (Serial.available() > 0) {
        char readByte = Serial.read(); //
        nbBytesRecus++;
        msg[i] = readByte; //
      }        
    }
    
    if(nbBytesRecus=3){
      if(msg[0]==){
        id = 
      }
      else if(msg[0]==){
        id = 
      }
      else if(msg[0]==){
        id = 
      }
      if(msg[1]==43) { // présence du signe "+" positi en deuxième caractère
        value = int(msg[2]);
      }
      else if(msg[1]==45) { // présence du signe "-" négatif en deuxième caractère 
        value = - (int(msg[2]));
      }
    }
  }
}



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

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  
  rStart();
  rFull();
}

void loop(){

}

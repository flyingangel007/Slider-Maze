// **************************************
// Touch - Detect
// **************************************
boolean touchDetect() {
  
  long total = capSens.capacitiveSensor(30);
//Serial.println(total);
  if(total > touchSensitive) {        // Schwellwert überschritten?
    return true;
  }
  else {
    return false;
  }
}


// **************************************
// Mappen der Schritte (0-10) auf die Position am Slider-Pot (10-1010)
// **************************************
int mapPos(int x) {
  x = (x*100)+10;
  return x;
}


// **************************************
// Einlesen des Level-Selector
// **************************************
byte levelRead() {
  
  byte var;
  
  var = !digitalRead(LEVSELPIN3);   // einlesen höchstes Bit und invertieren des Bits da PullUp aktiviert
  var <<= 1;                        // um ein Bit nach links schieben
  var |= !digitalRead(LEVSELPIN2);  // einlesen Bit inkl. oder-Verknüpfung und invertieren des Bits da PullUp aktiviert
  var <<= 1;
  var |= !digitalRead(LEVSELPIN1);  // einlesen Bit inkl. oder-Verknüpfung und invertieren des Bits da PullUp aktiviert
  var <<= 1;
  var |= !digitalRead(LEVSELPIN0);  // einlesen niedrigstes Bit und invertieren des Bits da PullUp aktiviert
  
  return var;
}


// *****************************************
// printout on serial
// *****************************************
void printAll() {

  // printout sequence
  for (int i = 0; i <= 10; i++) {    // 
    Serial.print(sequence[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println("------------------");

  // printout matrix
  for (int i = 0; i <= 10; i++) {
    for (int j = 0; j <= 10; j++) {
      Serial.print(field[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println("++++++++++++++++++");
}

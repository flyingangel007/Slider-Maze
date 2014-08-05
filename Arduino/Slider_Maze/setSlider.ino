// **************************************
// den Slider auf eine definierte Position (0-10) setzen
// die Funktion wird erst bei erreichen des Ziels verlassen
// **************************************
void setSlider(int potPosTar) {

  potPosTar = mapPos(potPosTar);      // Mappen der anzusteuernden Position 
  
  int potPosDis = analogRead(SLIPOTPIN) - potPosTar;   // Entfernung zwischen Aktuell und Ziel
  
  // Motor starten wenn notwendig:
  if (abs(potPosDis) > 2) {            // ist Bewegung erforderlich?
    digitalWrite(MOTBRKPIN, LOW);         // lösen der Bremse
    while (abs(potPosDis) > 2) {       // weitermachen solange Distanz > 5
      
      if (potPosDis>0) {               // Drehrichtung
        digitalWrite(MOTDIRPIN, LOW);
      }
      else {
        digitalWrite(MOTDIRPIN, HIGH);
      }
  
      if (abs(potPosDis) > 40) {       // Geschwindigkeit je nach Entfernung
        analogWrite(MOTSPDPIN, 150);      // Motor schneller
      }
      else {
        analogWrite(MOTSPDPIN, 120);       // Motor langsamer
      }
      delay(8);                         // warten, ob Motor weiterrutscht
      potPosDis = analogRead(SLIPOTPIN) - potPosTar;  // wie weit bis zum Ziel
    }
    digitalWrite(MOTBRKPIN, HIGH);        // anziehen der Bremse
  }
}

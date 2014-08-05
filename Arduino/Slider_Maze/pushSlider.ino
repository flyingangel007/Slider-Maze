// **************************************
// Regler auf Rasterpunkte setzen und gibt Endposition des Reglers zurück
// Die Funktion wird in einer Ruheposition des Reglers verlassen
// **************************************
byte pushSlider(byte clkPos[]) {

  int potPosDis;           // Entfernung zum nächsten Ziel

  do {
  
    int distLow=5000;        // extremer Wert für unteres Ende der Skala
    int distHigh=5000;       // extremer Wert für oberes Ende der Skala
    int potPosAkt = analogRead(SLIPOTPIN);
   
    /*
    Diese Schleife sucht die beiden nächsten Einrastpunkte, ausgehend von der 
    aktuellen Reglerposition.
    Bei jedem Schleifendurchlauf werden 2 Punkte geprüft:
    1. Von unten nach oben (0-10): ist der entsprechende Punkt ein Einrastpunkt und 
       steht der Regler darüber?
       wenn ja, berechne den Abstand des Reglers zum Einrastpunkt
    2. Von oben nach unten (10-0): ist der entsprechende Punkt ein Einrastpunkt und 
       steht der Regler darunter?
       wenn ja, berechne deb Abstand des Reglers zum Einrastpunkt
  
    Am Ende der 11 Durchgänge sind die beiden Einrastpunkte vor und hinter dem Regler 
    bekannt.
    Sollte kein Einrastpunkt vor bzw. hinter dem Regler sein, wird automatisch der 
    Wert 5000 zugewiesen. Damit ist sichergestellt, dass dieser Punkt nicht ausgewählt
    wird.
    */ 
    for(int i = 0; i <= 10; i++) {
      
      // Ist dieser Punkt ein Einrastpunkt UND steht der Regler oberhalb dieses Punktes
      if(clkPos[i] !=11 && potPosAkt >= mapPos(i)) {
        distLow = potPosAkt - mapPos(i);            // Distanz zum Einrastpunkt
      }
      // Ist dieser Punkt ein Einrastpunkt UND steht der Regler unterhalb dieses Punktes
      if(clkPos[abs(i-10)] !=11 && potPosAkt < mapPos(abs(i-10))) {
        distHigh = potPosAkt - mapPos(abs(i-10));   // Distanz zum Einrastpunkt
      }
    }
  
    if(distLow < abs(distHigh)) {   // ist der untere Einrastpunkt näher?
      potPosDis = distLow;
    }
    else {                          // sonst wird der obere Einrastpunkt gewählt
      potPosDis = distHigh;
    }
  
    if (abs(potPosDis) > 5) {          // ist Bewegung erforderlich?
      digitalWrite(MOTBRKPIN, LOW);    // lösen der Bremse
      
      if (potPosDis>0) {               // Drehrichtung
        digitalWrite(MOTDIRPIN, LOW);
      }
      else {
        digitalWrite(MOTDIRPIN, HIGH);
      }
      analogWrite(MOTSPDPIN, 120);     // Motor aktivieren
    }
    else {                             // Ruheposition erreicht
      digitalWrite(MOTBRKPIN, HIGH);   // anziehen der Bremse
      return potPosAkt/100;            // aktuelle Schleiferposition (0-10) zurückgeben
    }
  
  } while (abs(potPosDis) > 5);        // Schleife, solange keine Ruheposition erreicht
}


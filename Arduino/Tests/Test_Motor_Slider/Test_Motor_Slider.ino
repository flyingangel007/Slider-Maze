/*
Test, automatisch zufällige Positionen anzufahren
*/

// Definitionen Arduino Motor-Shield:
#define MotDirPin 12     // Drehrichtung Motor
#define MotBrkPin 9      // Motor-Bremse
#define MotSpdPin 3      // Motor-Geschwindigkeit

#define SliPotPin A2     // Slider-Pot Schleiferkontakt

void setup() {
  
  // aktivieren Serielle Schnittstelle
Serial.begin(9600);

  //Setup Channel A
  pinMode(MotDirPin, OUTPUT); //Initiates Motor Channel A pin
  pinMode(MotBrkPin, OUTPUT); //Initiates Brake Channel A pin
}

void loop() {
    
  
  // wo muss der Regler hin?
  int i = random(11);   // Auswahl einer zufälligen Position von 0-10

Serial.println(i);

  setPos(i);            // die anzusteuernde Position
  delay(2000);
  
}

// den Slider auf eine definierte Position (0-10) setzen
// die Funktion wird erst bei erreichen des Ziels verlassen
void setPos(int potPosTar) {

  potPosTar = mapPos(potPosTar);      // Mappen der anzusteuernden Position 
  
  int potPosDis = analogRead(SliPotPin) - potPosTar;   // Entfernung zwischen Aktuell und Ziel
  
  // Motor starten wenn notwendig:
  if (abs(potPosDis) > 2) {            // ist Bewegung erforderlich?
    digitalWrite(MotBrkPin, LOW);         // lösen der Bremse
    while (abs(potPosDis) > 2) {       // weitermachen solange Distanz > 5
      
      if (potPosDis>0) {               // Drehrichtung
        digitalWrite(MotDirPin, HIGH);
      }
      else {
        digitalWrite(MotDirPin, LOW);
      }
  
      if (abs(potPosDis) > 40) {       // Geschwindigkeit je nach Entfernung
        analogWrite(MotSpdPin, 150);      // Motor schneller
      }
      else {
        analogWrite(MotSpdPin, 120);       // Motor langsamer
      }
      delay(8);                         // warten, ob Motor weiterrutscht
      potPosDis = analogRead(SliPotPin) - potPosTar;  // wie weit bis zum Ziel
    }
    digitalWrite(MotBrkPin, HIGH);        // anziehen der Bremse
  }
}


// Mappen der Regler-Stufe auf einen Schleifer-Wert
int mapPos(int x) {
  x = (x*100)+10;
  return x;
}



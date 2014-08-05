/*
Auslesen des zu spielenden Levels am Level-Schalter
Ansteuern der 3 LEDs
*/

// Definitionen Level-Selektor (ist an den Pins 4-7 angeschlossen)
#define LevSelPin0 4
#define LevSelPin1 5
#define LevSelPin2 6
#define LevSelPin3 7

// Definitionen LEDs (sind an Analog 3-5 angeschlossen)
#define LedGrnPin A3  // Grüne LED
#define LedYelPin A4  // gelbe LED
#define LedRedPin A5  // rote LED


void setup() {
  
  //setzen der Pins
  
  // Level-Wähler
  pinMode(LevSelPin0, INPUT_PULLUP);      // Pin 4 -> Eingang & PullUp aktivieren
  pinMode(LevSelPin1, INPUT_PULLUP);      // Pin 5 -> Eingang & PullUp aktivieren
  pinMode(LevSelPin2, INPUT_PULLUP);      // Pin 6 -> Eingang & PullUp aktivieren
  pinMode(LevSelPin3, INPUT_PULLUP);      // Pin 7 -> Eingang & PullUp aktivieren
  
  
  //LEDs
  pinMode(LedGrnPin, OUTPUT);
  pinMode(LedYelPin, OUTPUT);
  pinMode(LedRedPin, OUTPUT);
  
  
  // aktivieren der Seriellen Schnittstelle
  Serial.begin(9600);
  
}

void loop() {
  
  Serial.println(levelRead());    // auslesen des Level-Wählers und Ausgabe auf Schnittstelle
  delay(1000);
  
  digitalWrite(LedGrnPin, HIGH);  // aktivieren der grünen LED
  delay(500);
  
  digitalWrite(LedYelPin, HIGH);  // aktivieren der gelben LED
  delay(500);
  
  digitalWrite(LedRedPin, HIGH);  // aktivieren der roten LED
  delay(1000);
  
  digitalWrite(LedGrnPin, LOW);   // deaktivieren aller LEDs
  digitalWrite(LedYelPin, LOW);
  digitalWrite(LedRedPin, LOW);
  
}


byte levelRead() {
  
  byte var;
  
  var = !digitalRead(LevSelPin3);   // einlesen höchstes Bit
  var <<= 1;              // um ein Bit nach links schieben
  var |= !digitalRead(LevSelPin2);  // einlesen Bit inkl. oder-Verknüpfung
  var <<= 1;
  var |= !digitalRead(LevSelPin1);
  var <<= 1;
  var |= !digitalRead(LevSelPin0);  // einlesen niedrigstes Bit
  
  
  
  return var;
}

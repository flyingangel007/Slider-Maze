/*
Einfache Steuerung eines Motor-Slider-Pot


*/

// einbetten des TouchSensor-Plugins
#include <CapacitiveSensor.h>

// Definitionen Arduino Motor-Shield:
#define MOTDIRPIN 12     // Drehrichtung Motor
#define MOTBRKPIN 9      // Motor-Bremse
#define MOTSPDPIN 3      // Motor-Geschwindigkeit

// Definitionen Level-Selektor (ist an den Pins 4-7 angeschlossen)
#define LEVSELPIN0 4     // niedrigstes Bit
#define LEVSELPIN1 5
#define LEVSELPIN2 6
#define LEVSELPIN3 7     // höchstes Bit

// Definitionen LEDs (sind an Analog 3-5 angeschlossen)
#define LEDGRNPIN A5  // Grüne LED
#define LEDYELPIN A4  // gelbe LED
#define LEDREDPIN A3  // rote LED

#define SLIPOTPIN A2     // Slider-Pot Schleiferkontakt (rot = +; gelb = -; grün = Schleifer)

const int touchTimeout = 200;   // Zeit zwischen Usereingabe und Computer-Move
const int touchSensitive = 200;  // Empfindlichkeit des Sensors

byte sequence[11];      // die Ziele des Labyrinths (0, Zufall(1-9), 10)
byte field[11][11];     // das gesamte Labyrinth
byte snapSequence[] = {11, 1, 11, 3, 11, 11, 6, 11, 11, 11, 10};  // Beispiel-Einrastpunkte

// definieren des Touch-Sensors
CapacitiveSensor capSens = CapacitiveSensor(10,2);        // 1 megohm resistor between pins 10 & 2, pin 2 is sensor pin


void setup() {
  
  // aktivieren Serielle Schnittstelle
  Serial.begin(9600);

  //setzen der Pins
  
  // Level-Wähler
  pinMode(LEVSELPIN0, INPUT_PULLUP);      // Pin 4 -> Eingang & PullUp aktivieren
  pinMode(LEVSELPIN1, INPUT_PULLUP);      // Pin 5 -> Eingang & PullUp aktivieren
  pinMode(LEVSELPIN2, INPUT_PULLUP);      // Pin 6 -> Eingang & PullUp aktivieren
  pinMode(LEVSELPIN3, INPUT_PULLUP);      // Pin 7 -> Eingang & PullUp aktivieren
  
  //LEDs
  pinMode(LEDGRNPIN, OUTPUT);
  pinMode(LEDYELPIN, OUTPUT);
  pinMode(LEDREDPIN, OUTPUT);

  //Setup Arduino Motor-Shield - Channel A
  pinMode(MOTDIRPIN, OUTPUT); // Initiates Motor Channel A pin
  pinMode(MOTBRKPIN, OUTPUT); // Initiates Brake Channel A pin

}


void loop() {

  digitalWrite(LEDREDPIN, HIGH);   // rote LED aktivieren

  byte usrInput;                     // Variable der Usereingabe
  byte playLevel = levelRead();      // einlesen des Level-Selektors  

  // *** generieren der Game-Matrix
  switch(playLevel) {
    case 0:
      maze0();
      break;
    case 1:
      maze1();
      break;
    case 2:
      maze2();
      break;
    case 3:
      maze3();
      break;
    case 4:
      maze4();
      break;
    case 5:
      maze5();
      break;
    case 6:
      maze6();
      break;
    case 7:
      maze7();
      break;
    case 8:
      maze8();
      break;
    case 9:
      maze9();
      break;
  }
      
  printAll();


  // *** Beginn des Labyrinths und Schleife bis Ziel erreicht
  int target = 0;               // Ziel des Computer-Zuges
  setSlider(target);            // Slider in die Ausgangsposition schieben
  

  while(target != 10) {         // solange Zielbedingung nicht erreicht ist
    
    // einlesen der aktuellen snapSequence
    for (int i = 0; i <= 10; i++) {
      snapSequence[i] = field[target][i];
    }


    // *** User-Eingabe
    digitalWrite(LEDREDPIN, LOW);   // rote LED deaktivieren
    digitalWrite(LEDGRNPIN, HIGH);  // grüne LED aktivieren
    
    capSens.reset_CS_AutoCal();        // Calibrierung des TouchSensors

    while(touchDetect() == 0) {      // auf Berührung des Reglers warten
      if(playLevel != levelRead()) { // neue Position des Level-Selektors - loop neustarten
        return;
      }
    }
    
    unsigned long time = millis();           // speichern der aktuellen Laufzeit
    
    while(millis() -time < touchTimeout) {   // Dauer, die Regler nicht berührt werden darf, um Eingabe abzuschließen 
      
      if(touchDetect() == 1) {               // wurde Regler berührt?
        digitalWrite(LEDYELPIN, HIGH);        // gelbe LED aktivieren
        usrInput = pushSlider(snapSequence); // Übergabe der Einrastpunkte und warten auf Usereingabe
        time = millis();                     // zurücksetzen des Zählers
      }
      else {
        digitalWrite(LEDYELPIN, LOW);        // gelbe LED deaktivieren
      }

    }


    // *** Regler automatisch auf beliebige Position schieben

    digitalWrite(LEDGRNPIN, LOW);    // grüne LED deaktivieren
    digitalWrite(LEDREDPIN, HIGH);   // rote LED aktivieren
  
    // wo muss der Regler hin?
    target = field[target][usrInput];   // Computerzug nach dem entsprechenden Feldinhalt der Matrix

    setSlider(target);            // die Position ansteuern
    
  }
  
  // Ziel erreicht

  setSlider(9);
  delay(20);
  setSlider(10);
  delay(20);
  setSlider(9);
  delay(20);
  setSlider(10);
  delay(20);
  setSlider(9);
  delay(20);
  setSlider(10);
  delay(300);  

}


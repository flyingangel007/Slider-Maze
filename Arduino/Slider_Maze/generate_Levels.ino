// *****************************************
// generate sequence (0, random order 1-9, 10)
// *****************************************
void generateSequence() {
 
  int i, j, temp;
 
  // generate sorted sequence from 0-10
  for (i = 0; i <= 10; i++) {    
    sequence[i] = i;
  }

  // random permutation of position 1-9 (algorithm by Ronald Fisher and Frank Yates)  
  randomSeed(millis());         // really random
  for (i = 9; i>1; i--) {
    j = random(1,i+1);
    temp = sequence[i];         // swap sequence[i] with sequence[j]
    sequence[i] = sequence[j];
    sequence[j] = temp;
  }
}


// *****************************************
// generate Matrix 0
// jeder Punkt ist ein Rasterpunkt und stimmt
// *****************************************
void maze0() {
  
  // fülle alle Felder mit dem Wert der Spalte
  for (int x = 0; x <= 10; x++) {
    for (int y = 0; y <= 10; y++) {
      field[x][y] = y;
    }
  }
}


// *****************************************
// generate Matrix 1
// Computer zieht ein Feld weiter
// *****************************************
void maze1() {
  
  for (int x = 0; x <= 10; x++) {
    for (int y = 0; y <= 10; y++) {
      field[x][y] = (y+1) % 11; // (Feld + 1) Modulo 10, um Überlauf zu verhindern
    }
    field[x][x] = x;   // das aktuelle Feld bleibt aktuelles Feld
  }
}
  
  
// *****************************************
// generate Matrix 2
//   Computer spiegelt eigenen Zug
// *****************************************
void maze2() {
  
  for (int x = 0; x <= 10; x++) {
    for (int y = 0; y <= 10; y++) {
      field[x][y] = abs(y-10); // (Feld + 1) Modulo 10, um Überlauf zu verhindern
    }
    field[x][x] = x;   // das aktuelle Feld bleibt aktuelles Feld
  }
}


// *****************************************
// generate Matrix 3
// Belgian Maze
// *****************************************
void maze3() {

  fillAll();           // fülle alle Felder mit "11"
  generateSequence();  // generiere Sequenz
  
  // generate first row
  field[0][0] = 0;
  field[0][sequence[1]] = sequence[1];     // first goal

  for (int i = 1; i < 10; i++) {
    field[sequence[i]][sequence[i-1]] = sequence[i+1];  // last field = next goal (forward in maze)
    field[sequence[i]][sequence[i+1]] = sequence[i-1];  // next field = last goal (step back)
    field[sequence[i]][sequence[i]] = sequence[i];      // current field
  }
}


// *****************************************
// generate Matrix 4
// schieben = richtig, berühren = 0
// *****************************************
void maze4() {

  boolean again;

  fillAll();           // fülle alle Felder mit "11"
  
  do {
    again = false;
    generateSequence();

    for (int i = 1; i < 10; i++) {   // neue Sequenz generieren, wenn das Zielfeld gleich dem aktuellen Schritt ist
      if(sequence[i] == i) {
        again = true;
      }
    }
  } while(again == true);
    
  for (int i = 0; i < 10; i++) {
    field[sequence[i]][sequence[i+1]] = sequence[i+1];  // next field = next goal
    field[i][i] = 0;                                    // aktuelles Feld ist "0"
  }
}

  
// *****************************************
// generate Matrix 5
//   2 Möglichkeiten; falsch = 0
// *****************************************
void maze5() {
  
  fillAll();           // fülle alle Felder mit "11"
  generateSequence();
  
  // generieren der "richtigen" Ziele
  for (int i = 0; i < 10; i++) {
    field[sequence[i]][sequence[i+1]] = sequence[i+1];  // next field = next goal
    field[i][i] = i;                                    // aktuelles Feld
  }
    
  // generieren der "falschen" Ziele
  for (int x = 0; x < 10; x++) {

    byte wrongField;
    do {
      wrongField = random(11);            // erstellen eines "falschen" Zieles
    } while(field[x][wrongField] != 11);  // das Feld darf noch nicht anderwertig belegt sein
    
    field[x][wrongField] = 0;             // zuweisen des "falschen" Zieles
  }
}


// *****************************************
// generate Matrix 6
// 2 Möglichkeiten; falsch = Schritt zurück
// *****************************************
void maze6() {
  
  fillAll();           // fülle alle Felder mit "11"
  generateSequence();
  
  // generieren der "richtigen" Ziele
  for (int i = 0; i < 10; i++) {
    field[i][i] = i;    // aktuelles Feld
    field[sequence[i]][sequence[i+1]] = sequence[i+1];  // next field = next goal
  }
  
  // generieren der "falschen" Ziele
  for (int i = 1; i < 10; i++) {
  
    byte wrongField;
    do {
      wrongField = random(11);                      
    } while(field[sequence[i]][wrongField] != 11);  // das Feld darf noch nicht anderwertig belegt sein
    field[sequence[i]][wrongField] = sequence[i-1]; // zuweisen des vorherigen Zieles

  }  
}


// *****************************************
// generate Matrix 7
// 3 Möglichkeiten: 
// richtig = Einrastfeld; falsch = Schritt zurück oder "0"
// *****************************************
void maze7() {
  
  fillAll();           // fülle alle Felder mit "11"
  generateSequence();
  
  //generieren der "richtigen" Ziele
  for (int i = 0; i < 10; i++) {
    field[i][i] = i;    // aktuelles Feld
    field[sequence[i]][sequence[i+1]] = sequence[i+1];  // next field = next goal
  }
  
  //generieren der "falschen" Ziele
  for (int i = 0; i < 10; i++) {
    byte wrongField = random(11);
    
    // einem Feld die "0" zuweisen
    do {
      wrongField = random(11);                      
    } while(field[sequence[i]][wrongField] != 11);  // das Feld darf noch nicht anderwertig belegt sein
    field[sequence[i]][wrongField] = 0;             // zuweisen der "0"
    
    // einem Feld das vorige Ziel zuweisen
    if (i >= 1) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-1];   // zuweisen des vorherigen Zieles
    }
  }
}


// *****************************************
// generate Matrix 8
// 4 Möglichkeiten:
// richtig = zufälliges Feld; falsch = bis zu 2 Schritte zurück oder "0"
// *****************************************
void maze8() {
  
  fillAll();           // fülle alle Felder mit "11"
  generateSequence();
  
  //generieren der "richtigen" Ziele
  for (int i = 0; i < 10; i++) {
    byte rightField = random(11);
    field[sequence[i]][rightField] = sequence[i+1];  // next field = next goal
  }
  
  //generieren der "falschen" Ziele
  for (int i = 0; i < 10; i++) {
    byte wrongField = random(11);
    
    // einem Feld die "0" zuweisen
    do {
      wrongField = random(11);                      
    } while(field[sequence[i]][wrongField] != 11);  // das Feld darf noch nicht anderwertig belegt sein
    field[sequence[i]][wrongField] = 0;             // zuweisen der "0"
    
    // einem Feld das vorige Ziel zuweisen
    if (i >= 1) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-1];   // zuweisen des vorherigen Zieles
    }

    // einem Feld das vorletzte Ziel zuweisen
    if (i >= 2) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-2];   // zuweisen des vorherigen Zieles
    }
  }
}


// *****************************************
// generate Matrix 9
// 6 Möglichkeiten:
// richtig = zufälliges Feld; falsch = bis zu 3 Schritte zurück oder 2x "0"
// *****************************************
void maze9() {
  
  fillAll();           // fülle alle Felder mit "11"
  generateSequence();
  
  //generieren der "richtigen" Ziele
  for (int i = 0; i < 10; i++) {
    byte rightField = random(11);
    field[sequence[i]][rightField] = sequence[i+1];  // next field = next goal
  }
  
  //generieren der "falschen" Ziele
  for (int i = 0; i < 10; i++) {
    byte wrongField = random(11);
    
    // 2 Feldern die "0" zuweisen
    for (int j= 0; j<=1; j++) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);  // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = 0;             // zuweisen der "0"
    }
    
    // einem Feld das vorige Ziel zuweisen
    if (i >= 1) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-1];   // zuweisen des vorherigen Zieles
    }
    
    // einem Feld das vorletzte Ziel zuweisen
    if (i >= 2) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-2];   // zuweisen des vorherigen Zieles
    }
    
    // einem Feld das vorvorletzte Ziel zuweisen
    if (i >= 3) {
      do {
        wrongField = random(11);                      
      } while(field[sequence[i]][wrongField] != 11);    // das Feld darf noch nicht anderwertig belegt sein
      field[sequence[i]][wrongField] = sequence[i-3];   // zuweisen des vorherigen Zieles
    }
  }
}


// *****************************************
// fill all 121 fields with "11" (11 = no "click")
// *****************************************
void fillAll() {

  for (int x = 0; x <= 10; x++) {
    for (int y = 0; y <= 10; y++) {
      field[x][y] = 11;
    }
  }
}




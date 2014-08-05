int sequence[11];
int field[11][11];
  

void setup() {
  
  Serial.begin(9600);
  
}


void loop() {

  generateSequence();
  belgianMaze();

  printAll();
  
  delay(10000);
  
}


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
// generate Matrix for "Belgian Maze"
// *****************************************
void belgianMaze() {

  // fill all 121 fields with "11" (11 = no "click")
  for (int i = 0; i <=10; i++) {
    for (int j = 0; j <=10; j++) {
      field[i][j] = 11;
    }
  }

  // generate first row
  field[0][0] = 0;
  field[0][sequence[1]] = sequence[1];     // first goal

  for (int i = 1; i <= 9; i++) {
    field[sequence[i]][sequence[i-1]] = sequence[i+1];  // last field = next goal (forward in maze)
    field[sequence[i]][sequence[i+1]] = sequence[i-1];  // next field = last goal (step back)
    field[sequence[i]][sequence[i]] = sequence[i];      // current field
  }
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
  

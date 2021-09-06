

// constants dont't change, used to set pin numbers:
const int buzzerPin = 14;

const int redButtonPin = 2;     // the number of the pushbutton pin
const int redLedPin =  16;      // the number of the LED pin

const int greenButtonPin = 0;     
const int greenLedPin =  15;      

const int yellowButtonPin = 13;    
const int yellowLedPin =  12;      

//tones assigned to each color
const int redTone = 165;
const int greenTone = 196;
const int yellowTone = 220;


int level = 1;
int patternArray[10]= { }; //array with 10 elements. Initialized and assigned 0 for each element
int ctrArray[3]={ 1, 1, 1 }; //array that keeps track of the total number of times each button was pressed throughout the program 


// variable for reading the pushbutton status
int redButtonState = 0;
int greenButtonState = 0;
int yellowButtonState = 0;
boolean correctPattern=false;

boolean levelCleared = true; 
int startGame=0;

/*void setup() {
  // initialize LED pins as an output:
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  // initialize pushbutton pin as an input:
  pinMode(redButtonPin, INPUT);
  pinMode(greenButtonPin, INPUT);
  pinMode(yellowButtonPin, INPUT);
  Serial.begin(9600);
  Serial.println("------- Start Serial Monitor ------");
  genNextPatternKey(); //Initializes the first
}
*/

boolean pressToStart(){
  // check for any states changes on the blue button
  redButtonState = digitalRead(redLedPin);
  if(redButtonState == 0 ){
    return true;
  }else{
    return false;
  }
}

void genNextPatternKey(){
  int nextKey = random(1,4); //generate a random number between 1 and 3
  Serial.println("nextKey");
  patternArray[level-1]=nextKey;
}//end method appendToBasePattern

void resetGame(){
  level = 1;
    for(int i=0; i < (sizeof(patternArray) / sizeof(patternArray[0])); i++){
      patternArray[i]= 0;
    }
  genNextPatternKey();
  startGame = 0;
}


void turnLightsOn(){
  //digitalWrite(blueLedPin,HIGH);
  digitalWrite(redLedPin,HIGH);
  digitalWrite(greenLedPin,HIGH);
  digitalWrite(yellowLedPin,HIGH);
}

void turnLightsOff(){
  //digitalWrite(blueLedPin,LOW);
  digitalWrite(redLedPin,LOW);
  digitalWrite(greenLedPin,LOW);
  digitalWrite(yellowLedPin,LOW);
}

void youLose(){
  for(int i = 0; i<3; i++){
    tone(buzzerPin, 912, 250);
    delay(300);
    tone(buzzerPin, 535, 250);
    turnLightsOn();
    tone(buzzerPin, 912, 250);
    delay(300);
    tone(buzzerPin, 535, 250);
    turnLightsOff();
    tone(buzzerPin, 912, 250);
    delay(300);
    tone(buzzerPin, 535, 250);
  }
  delay(100);
}

void showPatternOnTerminal(){
  int n = 0;
  for(int i = 0; i < (sizeof(patternArray) / sizeof(patternArray[0])); i++){
    n = patternArray[i];
    switch(n){
      case 1:
        Serial.print(" R,");
        break;
      case 2:
        Serial.print(" G,");
        break;
      case 3:
        Serial.print(" Y,");
        break;
      default:
        //if nothing matches do nothing
        break;
    } //end switch statement
    delay(100);
  } //end for loop
} //end method showPatternOnTermnial


void letsGo(){
  delay(200);
  turnLightsOn();
  tone(buzzerPin,415,300); //G#
  delay(400);
  tone(buzzerPin,493,200); //B4
  delay(250);
  turnLightsOff();
  tone(buzzerPin,415,200); //G#
  delay(250);
  tone(buzzerPin,493,200); //B4
  delay(250);
  turnLightsOn();
  tone(buzzerPin,493,200); //B4
  delay(250);
  tone(buzzerPin,415,300); //G#
  delay(400);
  turnLightsOff();
  tone(buzzerPin,369,300); //F#
  delay(400);
  tone(buzzerPin,466,250); //A#
  delay(250);
  turnLightsOn();
  tone(buzzerPin,369,250); //F#
  delay(250);
  tone(buzzerPin,329,250); //E
  delay(250);
  turnLightsOff();
}

void displayPattern(){
  //method that sends the current pattern that must be input to continue the game
  int n = 0;
  for(int i = 0; i < (sizeof(patternArray) / sizeof(patternArray[0])); i++){
    n = patternArray[i];
    switch(n){
      case 1:
        tone(buzzerPin, redTone, 250);
        digitalWrite(redLedPin,HIGH);
        delay(300);
        digitalWrite(redLedPin,LOW);
        delay(200);
        break;
      case 2:
        tone(buzzerPin, greenTone, 250);
        digitalWrite(greenLedPin,HIGH);
        delay(300);
        digitalWrite(greenLedPin,LOW);
        delay(200);
        break;
      case 3:
        //send power to LED and ring buzzer
        tone(buzzerPin, yellowTone, 250);
        digitalWrite(yellowLedPin,HIGH);
        delay(300);
        digitalWrite(yellowLedPin,LOW);
        delay(200);
        break;
      default:
        //if nothing matches do nothing
        break;
    } //end switch statement
  } //end for loop
}//end displayPattern method

int checkButtonStates(){
  // check for any state changes on the 3 buttons
  redButtonState = digitalRead(redButtonPin);
  greenButtonState = digitalRead(greenButtonPin);
  yellowButtonState = digitalRead(yellowButtonPin);
  
  if ( redButtonState == LOW ) {
    // turn LED on:
    ctrArray[1] += 1;
    Serial.print("Pressed Red ");
    Serial.println(ctrArray[1]);
    tone(buzzerPin, redTone, 250);
    digitalWrite(redLedPin, HIGH);
    delay(200);
    digitalWrite(redLedPin, LOW);
    return(1);
  } else if ( greenButtonState == LOW ) {
    // turn LED on:
    ctrArray[2] += 1;
    Serial.print("Pressed Green ");
    Serial.println(ctrArray[2]);
    tone(buzzerPin, greenTone, 250);
    digitalWrite(greenLedPin, HIGH);
    delay(200);
    digitalWrite(greenLedPin, LOW);
    return(2);
  } else if ( yellowButtonState == LOW ) {
    // turn LED on:
    ctrArray[3] += 1;
    Serial.print("Pressed yellow ");
    Serial.println(ctrArray[3]);
    tone(buzzerPin, yellowTone, 250);
    digitalWrite(yellowLedPin, HIGH);
    delay(200);
    digitalWrite(yellowLedPin, LOW);
    return(3);
  } else {
    //return 0 if no state changes where detected on the cycle
    return 0;
  }
}//end method checkButtonStates


boolean userInputAndValidation(){
  //method
  boolean inputMatching = true;
  int input; //holds user input
  int ctr = 0; //used as array pointer
  int currentKey = 0; //holds current pattern key (where pointer is)

  //while user input matches pattern, continue to next key.
  while( inputMatching == true && ctr < level ){
    delay(.01);
    input = 0; //resets input to zero after each outer while loop
    currentKey = patternArray[ctr];
    while( input == 0 ){
      delay(.01);
      input = checkButtonStates();
    }
    if( input != currentKey ){
      inputMatching = false;
      // break out of while loop when user input doesn't match
    }
    ctr++;
  } //end while loop
  Serial.println("-------------------------------------End of userInputAndValidation -----------------------------------------\n");
  return inputMatching; // Note: Anything after this return will not be executed. Method will end at this line.
} //end method userInput&Validation()



// --------------------------- Extra Feature ----------------------------
void lampMode(){
  // read the state of the pushbutton value:
  redButtonState = digitalRead(redButtonPin);
  greenButtonState = digitalRead(greenButtonPin);
  yellowButtonState = digitalRead(yellowButtonPin);
  
  if ( redButtonState == LOW ) {
    // turn LED on:
    ctrArray[1] += 1;
    Serial.print("Pressed Red ");
    Serial.println(ctrArray[1]);
    tone(buzzerPin, redTone, 250);
    if ( ctrArray[1]%2==0 ) {
      //turn on red LED if ctr is even
      digitalWrite(redLedPin, HIGH);
    } else if( ctrArray[1]%2!=0 ) {
      // turn off red LED if ctr is not even
      digitalWrite(redLedPin, LOW); 
    }
    delay(200);
  }

  if ( greenButtonState == LOW ) {
    // turn LED on:
    ctrArray[2] += 1;
    Serial.print("Pressed Green ");
    Serial.println(ctrArray[2]);
    tone(buzzerPin, greenTone, 250);
    if ( ctrArray[2]%2==0 ) {
      //turn on green LED if ctr is even
      digitalWrite(greenLedPin, HIGH);
    } else if( ctrArray[2]%2!=0 ) {
      // turn off green LED if ctr is not even
      digitalWrite(greenLedPin, LOW); 
    }
    delay(200);
  }

  if ( yellowButtonState == LOW ) {
    // turn LED on:
    ctrArray[3] += 1;
    Serial.print("Pressed yellow ");
    Serial.println(ctrArray[3]);
    tone(buzzerPin, yellowTone, 250);
    if ( ctrArray[3]%2==0 ) {
      //turn on yellow LED if ctr is even
      digitalWrite(yellowLedPin, HIGH);
    } else if( ctrArray[3]%2!=0 ) {
      // turn off yellow LED if ctr is not even
      digitalWrite(yellowLedPin, LOW); 
    }
    delay(200);
  }
}//end method lampMode



/*void loop() {
  //lampMode();
  displayPattern();
  showPatternOnTerminal();
  levelCleared = userInputAndValidation();
  if( levelCleared == true ){
    letsGo();
    level++;
    genNextPatternKey();
    Serial.println("Level Cleared is: " + (String)levelCleared);
  } else if ( levelCleared == false){
    youLose();
  }
  
}//end loop method
*/

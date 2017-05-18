
// 6 consecutive digital pins for the LEDs
const int first_led = 2;
const int second_led = 3;
const int third_led = 4;
const int fourth_led = 5;
const int fifth_led = 6;
const int sixth_led = 7;

// pin for the button switch
const int button = 12;

// value to check state of button switch
int pressed = 0;

void setup() {
  // set all LED pins to OUTPUT
  
    pinMode(first_led, OUTPUT);
    pinMode(second_led, OUTPUT);
    pinMode(third_led, OUTPUT);
    pinMode(fourth_led, OUTPUT);
    pinMode(fifth_led, OUTPUT);
    pinMode(sixth_led, OUTPUT);

 
  // set button pin to INPUT
  pinMode(button, INPUT);
  
  // initialize random seed by noise from analog pin 0 (should be unconnected)
  // randomSeed is a function that uses any of the unconnected analog pins as 
  // a noise source to generate random numbers. Here we use the first analog pin (0) Zero
  randomSeed(analogRead(0));

}


// this function is used to create an effect before the dice dice is thrown
// Lights turn on individually from first to the last and last to frist repeatedly

void buildUpTension() {
  // light LEDs from left to right and back to build up tension
  // while waiting for the dice to be thrown
  // left to right
  for (int i=first_led; i<=sixth_led; i++) {
    if (i!=first_led) {
      digitalWrite(i-1, LOW);
    }
    digitalWrite(i, HIGH);
    delay(100);
  }
  // right to left
  for (int i=sixth_led; i>=first_led; i--) {
    if (i!=sixth_led) {
      digitalWrite(i+1, LOW);
    }
    digitalWrite(i, HIGH);
    delay(100);
  }
}


///the following function (showNumber) turns on the LEDs that corresponds to a given number using this logic:
// Since 1 is the lowest number it will turn on the first LED by default
// other LEDs will be turned on by checking their values incrementally
// for example if the given number is >= 2, the second LED is turned on, if >=3 third number is turned on, etc
//So if the given number is say 2 (two), only the first and second LED will come on. The third LED will be off 
// because 2 is not >= 3, same as the fourth, fifth and sixth LED. Simple Logic.

void showNumber(int number) {
  
  digitalWrite(first_led, HIGH);  // turn on first LED by default
  
  if (number >= 2) {
    digitalWrite(second_led, HIGH);
  }
  if (number >= 3) {
    digitalWrite(third_led, HIGH);    
  }
  if (number >= 4) {
    digitalWrite(fourth_led, HIGH);    
  }
  if (number >= 5) {
    digitalWrite(fifth_led, HIGH);    
  }
  if (number == 6) {
    digitalWrite(sixth_led, HIGH);    
  }
}



/// function to throw dice -- Returns an int of the random number generated
int throwDice() 
  {
    // generate a random number in the range from 1 to 6
    int randNumber = random(1,7);
    
    return randNumber;  // return the random number
  }



///function to set all LEDs to a particular value
void setAllLEDs(boolean value) 
    {
        for (int i=first_led; i<=sixth_led; i++) 
        {
          digitalWrite(i, value);
        }
    }


void loop() {
  // if button is pressed - throw the dice
  pressed = digitalRead(button);

  if (pressed == LOW) {
    // remove previous number
    setAllLEDs(LOW);    /// turns off all LEDs setting all to LOW
    
    buildUpTension();
    int thrownNumber = throwDice();
    showNumber(thrownNumber);
    
  } 

}

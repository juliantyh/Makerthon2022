//YWROBOT

//Compatible with the Arduino IDE 1.0

//Library version:1.1

// https://www.youtube.com/watch?v=1cg9mXA2XRE
// https://github.com/makertut/counter-lcd-push-btn/blob/master/code1.ino

// sample code that i used to randomise messages
// https://stackoverflow.com/questions/65276615/arduino-pick-a-random-word-from-array-every-time-sketch-is-ran
// https://forum.arduino.cc/t/picking-a-random-word/45792/5

// Updates: introduced the random messages feature

#include <Wire.h>

#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);    // set the LCD address to 0x27 for a 16 chars and 2 line display


// this constant won't change

const int  Home_buttonPin   = 2;    // the pin that the pushbutton is attached to
const int  Quote_buttonPin = 3;



// Variables will change:
char *msgesline1[]={"Remember to take", "Acads are not", "Go do some", "Drink more"}; //array of good messages line 1
char *msgesline2[]={"deep breaths!", "everything!", "exercise!", "water!"}; //array of good messages line 2

long random_index;
long randNumber;

String displaymsgline1;   // create variable
String displaymsgline2;

int Home_buttonState = LOW;         // current state of the home button
int Home_lastButtonState = LOW;     // previous state of the home button


int Quote_buttonState = LOW;         // current state of the quote button
int Quote_lastButtonState = LOW;     // previous state of the quote button

bool bPress = false;


void setup()

{
  Serial.begin(9600);

  pinMode( Home_buttonPin , INPUT_PULLUP);
  
  pinMode( Quote_buttonPin , INPUT_PULLUP);

  lcd.init();                      // initialize the lcd

  // Print a message to the LCD.
  // this is the starting msg printed on LCD

  lcd.backlight();

  lcd.setCursor(0,0);

  lcd.print("  Mindfulness");

  lcd.setCursor(2,1);

  lcd.print(" Cat Clock");
 

}


void loop()

{
   checkHome();
   checkQuote();


   if( bPress){

       bPress = false;

      // clear the screen before next btnpress
      
      lcd.setCursor(0,0);

      lcd.print("                ");
      
      lcd.setCursor(2,1);

      lcd.print("                ");

      lcd.setCursor(0,0);

      lcd.print(displaymsgline1);
      
      lcd.setCursor(2,1);

      lcd.print(displaymsgline2);

   }

}


void checkQuote()

{

  Quote_buttonState = digitalRead(Quote_buttonPin);

  // compare the buttonState to its previous state

  if (Quote_buttonState != Quote_lastButtonState) {

    // if the state has changed, generate new message

    if (Quote_buttonState == LOW) {

        bPress = true;

      // if the current state is HIGH then the button went from off to on:
      
      // generate new displaymsg
      
      randNumber = random(300); //generate random number
      randomSeed(randNumber); //randomise the seed

      // only need to randomize index of one line then use the same number for the next line
      
      random_index = random(sizeof(msgesline1)/sizeof(char*)); 

      Serial.println("on");

      displaymsgline1 = msgesline1[random_index];
      displaymsgline2 = msgesline2[random_index];
      
      Serial.println(displaymsgline1); //Prints random msg in serial
      Serial.println(displaymsgline2); //Prints random msg in serial

    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing

    delay(50);

  }

  // save the current state as the last state, for next time through the loop

  Quote_lastButtonState = Quote_buttonState;

}

void checkHome()

{

  Home_buttonState = digitalRead(Home_buttonPin);



  // compare the buttonState to its previous state

  if (Home_buttonState != Home_lastButtonState) {

    // if the state has changed, increment the counter

    if (Home_buttonState == LOW) {

        bPress = true;

      // if the current state is HIGH then the button went from off to on:  
      // make display msg empty
      
      Serial.println("on");

      displaymsgline1 = "    15:12:21";
      displaymsgline2 = "Thu 16/12/21";

      Serial.println(displaymsgline1);
      Serial.println(displaymsgline2);


    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing

    delay(50);

  }

  // save the current state as the last state, for next time through the loop

  Home_lastButtonState = Home_buttonState;

}

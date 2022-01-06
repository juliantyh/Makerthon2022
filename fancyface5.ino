// similar to mindfulnessbot3 code
// made home face blink twice and say i'm here to help and changed ouch to meow like petting

#include <LCD03.h>

LCD03 lcd;

uint8_t empty[8]  = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1};
uint8_t eyebrow_happy[8]  = {0x0,0x0,0x0,0xe,0x11,0x0,0x0,0x0};
uint8_t eyebrow_angry_right[8]  = {0x0,0x0,0x0,0x10,0x8,0x4,0x2,0x1};
uint8_t eyebrow_close[8]  = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f};
uint8_t eyebrow_angry_left[8]  = {0x0,0x0,0x0,0x1,0x2,0x4,0x8,0x10};
uint8_t eye_left[8] = {0xe,0x11,0x17,0x17,0x17,0x17,0x11,0xe};
uint8_t eye_right[8] = {0xe,0x11,0x1d,0x1d,0x1d,0x1d,0x11,0xe};
uint8_t eye_front[8] = {0xe,0x11,0x15,0x15,0x15,0x15,0x11,0xe};
uint8_t eye_close[8] = {0x0,0x0,0x0,0x11,0x1f,0x0,0x0,0x0};
uint8_t mouth_happy[8]  = {0x4,0xe,0xe,0x0,0x0,0x11,0xe};
uint8_t mouth_sad[8] = {0x4,0xe,0xe,0x0,0x0,0xe,0x11};

// this constant won't change

const int  React_buttonPin   = 2;    // the pin that the pushbutton is attached to
const int  Study_buttonPin = 3;

// Variables will change:

int React_buttonState = LOW;         // current state of the React button
int React_lastButtonState = LOW;     // previous state of the React button


int Study_buttonState = LOW;         // current state of the study button
int Study_lastButtonState = LOW;     // previous state of the study button

bool bPress = false;

void setup() {
   lcd.begin(20,4); 

   pinMode( React_buttonPin , INPUT_PULLUP);
   pinMode( Study_buttonPin , INPUT_PULLUP);
   
   //lcd.init(); 
   lcd.createChar(0, eyebrow_happy);
   lcd.createChar(1, eyebrow_angry_right);
   lcd.createChar(2, eyebrow_angry_left);
   lcd.createChar(3, eye_right);
   lcd.createChar(4, eye_front);
   lcd.createChar(5, eye_close);
   lcd.createChar(6, mouth_happy);
   lcd.createChar(7, mouth_sad);
   // deleted these characters because cannot exceed 8 characters if not error appears
   //lcd.createChar(3, eye_left);
   //lcd.createChar(0, empty);
   //lcd.createChar(10, eyebrow_close);

   lcd.backlight();
   lcd.home();
   // eyebrow
   lcd.setCursor(1,0);
   lcd.write(0);
   lcd.setCursor(3,0);
   lcd.write(0);
   // eyes
   lcd.setCursor(1,1);
   lcd.write(3);
   lcd.setCursor(3,1);
   lcd.write(3);
   // mouth
   lcd.setCursor(2,2);
   lcd.write(6);
   // words
   lcd.setCursor(9,1);
   lcd.print("Meow! I'm");
   lcd.setCursor(8,2);
   lcd.print("Mindful Cat!");
   delay(1000);

   delay(2000);
   // eyes close
   lcd.setCursor(1,1);
   lcd.write(5);
   lcd.setCursor(3,1);
   lcd.write(5);
   delay(1000);
   // eyes right
   lcd.setCursor(1,1);
   lcd.write(3);
   lcd.setCursor(3,1);
   lcd.write(3);
   delay(1000);
   // clear old text so can print new words
   lcd.setCursor(9,1);
   lcd.print("         ");
   lcd.setCursor(8,2);
   lcd.print("            ");
   // words
   lcd.setCursor(8,1);
   lcd.print("I'm here to");
   lcd.setCursor(8,2);
   lcd.print("help you!");
}

//string str[20];
void loop() {

   checkReact();
   checkStudy();

   if( bPress){

       bPress = false;

      // clear the screen before next btnpress
      
      lcd.clear();

      //default face
      
      // eyebrow
      lcd.setCursor(1,0);
      lcd.write(0);
      lcd.setCursor(3,0);
      lcd.write(0);
      // eyes
      lcd.setCursor(1,1);
      lcd.write(3);
      lcd.setCursor(3,1);
      lcd.write(3);
      // mouth
      lcd.setCursor(2,2);
      lcd.write(6);
      // words
      lcd.setCursor(9,1);
      lcd.print("Meow! I'm");
      lcd.setCursor(8,2);
      lcd.print("Mindful Cat!");
      
      delay(3000);
      // eyes close
      lcd.setCursor(1,1);
      lcd.write(5);
      lcd.setCursor(3,1);
      lcd.write(5);
      delay(1000);
      // eyes right
      lcd.setCursor(1,1);
      lcd.write(3);
      lcd.setCursor(3,1);
      lcd.write(3);
      delay(1000);
      // clear old text so can print new words
      //lcd.setCursor(9,1);
      //lcd.print("         ");
      //lcd.setCursor(8,2);
      //lcd.print("            ");
      // words
      //lcd.setCursor(8,1);
      //lcd.print("I'm here to");
      //lcd.setCursor(8,2);
      //lcd.print("help you!");
   }

}

void checkStudy()

{

  Study_buttonState = digitalRead(Study_buttonPin);

  // compare the buttonState to its previous state

  if (Study_buttonState != Study_lastButtonState) {

    // if the state has changed, generate new message

    if (Study_buttonState == LOW) {

        bPress = true;

      // if the current state is HIGH then the button went from off to on:
      
      // Study timer 1h

      lcd.clear();
      
      // normal face, Your 1 hour study session starts now

      lcd.setCursor(1,0);
      lcd.write(0);
      lcd.setCursor(3,0);
      lcd.write(0);
      // eyes
      lcd.setCursor(1,1);
      lcd.write(3);
      lcd.setCursor(3,1);
      lcd.write(3);
      // mouth
      lcd.setCursor(2,2);
      lcd.write(6);
      // words
      lcd.setCursor(7,1);
      lcd.print("1h study time");
      lcd.setCursor(8,2);
      lcd.print("starts now!");

      delay(5000); //shld be 20 mins
      lcd.clear();

      // tired face. Push on! Mug strong!

      lcd.setCursor(1,0);
      lcd.write(1);
      lcd.setCursor(3,0);
      lcd.write(2);
      // eyes
      lcd.setCursor(1,1);
      lcd.write(3);
      lcd.setCursor(3,1);
      lcd.write(3);
      // mouth
      lcd.setCursor(2,2);
      lcd.write(6);
      // words
      lcd.setCursor(9,1);
      lcd.print("Push on!");
      lcd.setCursor(8,2);
      lcd.print("Mug Strong!");

      delay(5000);
      lcd.clear();

      // more tired face. ‘Last 20mins, you can do it!’
      
      lcd.setCursor(1,0);
      lcd.write(1);
      lcd.setCursor(3,0);
      lcd.write(2);
      // eyes
      lcd.setCursor(1,1);
      lcd.write(4);
      lcd.setCursor(3,1);
      lcd.write(4);
      // mouth
      lcd.setCursor(2,2);
      lcd.write(6);
      // words
      lcd.setCursor(8,1);
      lcd.print("Last 20mins");
      lcd.setCursor(8,2);
      lcd.print("All the way!");

      delay(5000);
      lcd.clear();
      
      // ded face. ‘Go take a break!’

      lcd.setCursor(1,0);
      lcd.write(1);
      lcd.setCursor(3,0);
      lcd.write(2);
      // eyes
      lcd.setCursor(1,1);
      lcd.write(5);
      lcd.setCursor(3,1);
      lcd.write(5);
      // mouth
      lcd.setCursor(2,2);
      lcd.write(7);
      // words
      lcd.setCursor(9,1);
      lcd.print("Go take");
      lcd.setCursor(9,2);
      lcd.print("a break!");

      delay(5000);
      lcd.clear();

    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing

    delay(50);

  }

  // save the current state as the last state, for next time through the loop

  Study_lastButtonState = Study_buttonState;

}

void checkReact()

{

  React_buttonState = digitalRead(React_buttonPin);



  // compare the buttonState to its previous state

  if (React_buttonState != React_lastButtonState) {

    // if the state has changed, increment the counter

    if (React_buttonState == LOW) {

        bPress = true;

        // if the current state is HIGH then the button went from off to on:  
  
        // clear screen first
  
        lcd.clear();
        // print the react
  
        lcd.setCursor(1,0);
        lcd.write(0);
        lcd.setCursor(3,0);
        lcd.write(0);
        // eyes
        lcd.setCursor(1,1);
        lcd.write(5);
        lcd.setCursor(3,1);
        lcd.write(5);
        // mouth
        lcd.setCursor(2,2);
        lcd.write(6);
         
        // words
        lcd.setCursor(9,1);
        lcd.print("Meow <3");
        lcd.setCursor(8,2);
        lcd.print("");
        delay(2000);

    } else {

      // if the current state is LOW then the button went from on to off:

      Serial.println("off");

    }

    // Delay a little bit to avoid bouncing

    delay(50);

  }

  // save the current state as the last state, for next time through the loop

  React_lastButtonState = React_buttonState;

}

   

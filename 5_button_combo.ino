/* Arduino 5 Button Combination Lock
   Author - Gtr_Stitch
   06/22/2013                           */


// Here we include our libraries

#include <Servo.h>                          
#include <LiquidCrystal.h>

// Initialize the libraries and set the pins for the LCD

LiquidCrystal lcd(2,3,4,5,6,7);       
Servo myservo;

// const int means Constant Integer. Constants don't change. Fitting since we are using buttons. Don't want our Arduino to get
// confused!

const int button1 = A0;                       
const int button2 = A1;                           
const int button3 = A2;
const int button4 = A3;
const int button5 = A4;

// We will be using "countx" to keep track of how many times a button is pressed

int count1 = 0;                               
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

// "statex" will keep track of the state of the button. Was it just pressed?

int state1 = 0;                                  
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;

// These keep tabs on the previous state of the button. Was it high? Low?

int prev1 = 0;                                     
int prev2 = 0;
int prev3 = 0;
int prev4 = 0;
int prev5 = 0;

// totalcount is how many times each button was pressed...like a combination.

int totalcount = 0;                            

// This applies to the LCD. It will be used to display an asterisk when inputting the combination.

int rows = 0;                                    

// And declare the LEDs :)

int red = 8;                                    
int green = 10;

// Here we setup how the pins will function (input/output), start the LCD, and designate which
// pin we have the servo attached to. We will also start off with the servo at 0 degrees.

void setup(){                               
  pinMode(button1, INPUT);              
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("  :ENTER CODE:  ");
  Serial.begin(9600);     // For debug. Visually see the button presses.
  myservo.attach(9);
  myservo.write(0);
}

// Start off by reading the state of the pins.

void loop(){                                                    
  state1 = digitalRead(button1);
  state2 = digitalRead(button2);
  state3 = digitalRead(button3);
  state4 = digitalRead(button4);
  state5 = digitalRead(button5);

// If the state of the button does not equal it's previous state (1 = HIGH, 0 = LOW), which basically
// means, was it just pressed or released? If the state of the button is HIGH (1)
// we increment the count of that button.

 
  if (state1 != prev1){                                 
    delay(10);                                                  
    if (state1 == HIGH){                                     
      count1++;                                              
    }  
// Note the delay(10). This is important. It facilitates a debounce. Buttons have an intert
// bounciness. You can't feel it, but when you press a button, it sometimes makes
// contact more than once, and the Arduino will see that as multiple presses. The delay
// pauses the program for 10 milliseconds, allowing the button to "settle", and then
// resumes. 10 milliseconds should be long enough, but adjust longer if needed.

            
    else{}              
  }                                 

// We do that for each button.
            
  if (state2 != prev2){                               
    delay(10);
    if (state2 == HIGH){
      count2++;
    }
    else{}
  }
 
  if (state3 != prev3){
    delay(10);
    if (state3 == HIGH){
      count3++;
    }
    else{}
  }
 
  if (state4 != prev4){
    delay(10);
    if (state4 == HIGH){
      count4++;
    }
    else{}
  }
 
  if (state5 != prev5){
    delay(10);
    if (state5 == HIGH){
      count5++;
    }
    else{}
  }

// This will help keep track of what kind of actions are going on with
// the buttons. When the button is pushed, its state does not match
// it's previous state, indicating a change. Here we set the previous
// state to the current state, so that the moment you push or
// release, the Arduino knows it, and acts accordingly.
 
  prev1 = state1;                               
  prev2 = state2;                               
  prev3 = state3;                              
  prev4 = state4;                              
  prev5 = state5;

// Then we tally up how many times each button was pressed.
 
  totalcount = count1 + count2 + count3 + count4 + count5;             
 
// This is where we write an asterisk ("*") to the LCD each time a button is pressed.

  for (rows = 0; rows < totalcount; rows+1){                              
    lcd.setCursor(rows,1);                                                             
    lcd.print("*");                                                                              
    rows++;
  }

// "rows" is where the cursor is (left to right) on the LCD.
//For each time a button is pressed, we increment "rows" by one, and
// set that as the cursor location. We do this up to a certain point (5)
//because that is how many digits are in our combination.
 
// Now, if our totalcount reaches 5, we will start looking at how many times
// each button was pressed. If it matches what our predetermined combo... 

   if (totalcount == 5){                               
    if (count1 == 2 && count2 == 0 && count3 == 1 && count4 == 2 && count5 == 0){           
      lcd.clear();                                                                                                          
      lcd.print(" CODE  ACCEPTED ");  // Code Accepted!
      myservo.write(90);            // the servo moves to 90 degrees, as if unlocking a door.
      digitalWrite(green, HIGH);   // green equals good, thus the green LED is on

// make sure the red LED stays off if you didn't get the code right the first time
      digitalWrite(red, LOW);   
      count1 = 0;   // Reset all our conunters to 0, starting the process over again.
      count2 = 0;
      count3 = 0;
      count4 = 0;
      count5 = 0;
      totalcount = 0;
      delay(10000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  :ENTER CODE:  ");   // And we're back at the beginning.
      myservo.write(0);
      digitalWrite(green, LOW);
    }
    else if (count1 != 2 && count2 != 0 && count3 != 1 && count4 != 2 && count5 != 0 && totalcount == 5){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" CODE  REJECTED ");   // This and the part below are where if the count of each button
      digitalWrite(red, HIGH); // does not equal the predetermined count, or if it's greater than the count,
      digitalWrite(green, LOW); //and the number of total presses equals 5 (indicating that a 5 digit 
      count1 = 0; // combination was entered but is wrong) then the code is rejected. Rejected!
      count2 = 0;
      count3 = 0;
      count4 = 0;
      count5 = 0;
      totalcount = 0;
      delay(5000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  :ENTER CODE:  ");
      digitalWrite(red, LOW);
    }
    else if (count1 > 2 && count2 > 0 && count3 > 1 && count4 > 2 && count5 > 0 || totalcount == 5){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" CODE  REJECTED ");
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      count1 = 0;
      count2 = 0;
      count3 = 0;
      count4 = 0;
      count5 = 0;
      totalcount = 0;
      delay(5000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  :ENTER CODE:  ");
      digitalWrite(red, LOW);
    }
  }
}

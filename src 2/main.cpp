/** @file ButtonTest.ino
 *  @brief This example sketch tests the basic LCD, backlight, and button
 *  functionality of the CheapLCD library.
 *
 *  This sketch displays "Hello World!!!" on the LCD for 1 second, then displays
 *  the name of the button being pressed. The backlight is turned on while a
 *  a button is being pressed and turned off when all buttons are released.
 *
 *  @author    Daniel Hooper
 *  @copyright Copyright Daniel Hooper 2018
 *  @date      2018
 *  @license   LGPL. See LICENSE file.
 *
 *  @bug No known bugs.
 */


#include "CheapLCD.h"

#include <NewPing.h>

CheapLCD lcd;

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 

void setup() {

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  Serial.begin(115200);
  // put your setup code here, to run once:
  lcd.begin();

  lcd.clear();
  lcd.write("Heeeello World!!!");
  delay(1000);
  lcd.backlightOff();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  static CLCD_Button_t lastButton = BTN_NONE;

  Serial.print("Ping Dat: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");

  CLCD_Button_t newReading = lcd.readButton();

  if (newReading != lastButton) {   // button changed
    lastButton = newReading;
    lcd.clear();

    if (newReading != BTN_NONE) {   // button was pressed
      switch(newReading) {
        case BTN_RIGHT:
          lcd.write("RITE!");
          break;
        case BTN_UP:
          lcd.write("Up");
          break;
        case BTN_DOWN:
          lcd.write("Down");
          break;
        case BTN_LEFT:
          lcd.write("Left");
          break;
        case BTN_SELECT:
          lcd.write("Select");
          break;
        default:
          lcd.write("ERROR");
          break;
      }

      lcd.backlightOn();

    }
    else {                        // button was released
      lcd.backlightOff();
      lcd.clear();
    }
  }

}
#include <Arduino.h>
#include <Joystick.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include <Button.h>
#include <Potentiometer.h>

const char * ssid = ""; //Skriv wifi her
const char * password = ""; //Skriv wifi password her

AsyncUDP udp;

Joystick joystick_left = Joystick(34, 35); 
//This joystick controls the movement of the drone. Forward/backwards/left/right.

Joystick joystick_right = Joystick(33, 32); 
//This joystick's x-value controls the direction of the drone, and turns it 45 degrees for each turn. 
//The y-value controls the speed of the drone. 

Potentiometer height = Potentiometer(39); 
//The potentiometer controls the altitude of the drone. 

Button redbutton = Button(17); 
//The red button is the takeoff function.

Button bluebutton = Button(05); 
//The blue button is the the land function. 

Button mysteryButton = Button(16); 
//This is our mystery button, that makes the drone do some dance moves. 

void sendMessage(String msg){
  udp.writeTo((const uint8_t *)msg.c_str(), msg.length(),
              IPAddress(192, 168,  1, 84), 6000);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }

  if (udp.listen(4000)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
  }
  sendMessage("Controller is connected");
}


void takeoff(Button & redbutton){
  if(redbutton.isPressed()){
    sendMessage("takeoff");
    delay(500);
  }
}

void land(Button & bluebutton){
  if(bluebutton.isPressed()){
    sendMessage("land");
    delay(500);
  }
}

void goBackAndForth(Joystick & joystick_left){
  if (joystick_left.getJoystickValuesY() <= 300){
    sendMessage("forward");
    delay(150);
  } else if (joystick_left.getJoystickValuesY() >= 3800){
    sendMessage("backwards");
    delay(150);
  }
}

void goSideways(Joystick & joystick_left){
  if (joystick_left.getJoystickValuesX() <= 300){
    sendMessage("left");
    delay(300);
  } else if (joystick_left.getJoystickValuesX() >= 3800){
    sendMessage("right");
    delay(300);
  }
}

void altitude(Potentiometer & height){
  if (height.getPotentiometerValue() >= 3000){
    sendMessage("up");
    delay(500);
  } else if (height.getPotentiometerValue() <= 1400){
    sendMessage("down");
    delay(500);
  }
}

void turn(Joystick & joystick_right){
  if (joystick_right.getJoystickValuesY() <= 300){
    sendMessage("turnright");
    delay(300);
  } else if (joystick_right.getJoystickValuesY() >= 3800){
    sendMessage("turnleft");
    delay(300);
  }
}

void speed(Joystick & joystick_right){
  if (joystick_right.getJoystickValuesX() <= 300){
    sendMessage("slower");
    delay(500);
  } else if (joystick_right.getJoystickValuesX() >= 3800){
    sendMessage("faster");
    delay(500);
  }
}

void dance(Button mysteryButton){
  if (mysteryButton.isPressed()){
  sendMessage("forward");
  delay(750);
  sendMessage("backwards");
  delay(750);
  sendMessage("right");
  delay(750);
  sendMessage("left");
  delay(750);
  sendMessage("up");
  delay(750);
  sendMessage("down");
  delay(750);
  }
}

void loop() {

  takeoff(redbutton);

  land(bluebutton);

  goBackAndForth(joystick_left);

  goSideways(joystick_left);

  altitude(height);

  turn(joystick_right);

  speed(joystick_right);

  dance(mysteryButton);

}

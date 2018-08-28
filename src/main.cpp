#include <Arduino.h>
#include <Servo.h>
#include <RCSwitch.h>

Servo switchServo;
RCSwitch mySwitch = RCSwitch();

int pos = 0;
const int offPosition = 10;
const int neutralPosition = 60;
const int onPosition = 100;
void switchNeutral(){
    switchServo.attach(9);
    switchServo.write(neutralPosition);
    delay(500);
    switchServo.detach();
}
void switchOn(){
    switchServo.attach(9);
    for(pos = neutralPosition; pos < onPosition; pos += 1)  // goes from 60 degrees to 100 degrees 
    {                                  // in steps of 1 degree 
        switchServo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    }
    for(pos = onPosition; pos>=neutralPosition; pos-=1)     // goes from 100 degrees to 60 degrees 
    {                                
        switchServo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    switchServo.detach();
}
void switchOff(){
    switchServo.attach(9);
    for(pos = neutralPosition; pos>=offPosition; pos-=1)     // goes from 60 degrees to 20 degrees 
    {                                
        switchServo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    }
    for(pos = offPosition; pos < neutralPosition; pos += 1)  // goes from 20 degrees to 60 degrees 
    {                                  // in steps of 1 degree 
        switchServo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    }
    switchServo.detach();
}

void setup() {
    Serial.begin(9600);
    switchNeutral();
    mySwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2
}
void loop() {
    if (mySwitch.available()) {
        long deviceCode = mySwitch.getReceivedValue();
        Serial.print("Received ");
        Serial.println(deviceCode);
        if(mySwitch.getReceivedValue() == 8400646){
            switchOn();
        } else if(deviceCode == 8400664){
            switchOff();
        }
        mySwitch.resetAvailable();
    }
}
// -----------------------------------------
// Function and Variables 
// -----------------------------------------
// In this example, we're going to register a Particle.variable() with the cloud
// We'll also register a Particle.function so that we can turn the LED on and off remotely.

// We're going to start by declaring which pins everything is plugged into.

int led = D7; // This is where your onboard LED is plugged in. 

double timeSinceLastCall =0; // Here we are declaring the variable sinceLastCall, which we will use later to store the time since the function was last activated.
double lastCall =0; //value that stores the time of the last LED toggle;
int ledState = 0; // stores the current status of the LED
// Next we go into the setup function.

void setup() {

    // First, declare all of our pins. This lets our device know which ones will be used for outputting voltage, and which ones will read incoming voltage.
    pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)


    // We are going to declare a Particle.variable() here so that we can see how long since the last instruction was issued.
    Particle.variable("timeElapsed", &timeSinceLastCall, DOUBLE);
    // This is saying that when we ask the cloud for "timeElapsed", this will reference the variable timeSinceLastCall in this app, which is an double variable.

    // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
    Particle.function("led",ledToggle);
    // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
    
    Particle.variable("ledStatus", &ledState, INT); // we can check if the LED is on or off by calling this variable
}


// Next is the loop function...

void loop() {

    timeSinceLastCall = millis()-lastCall;
    // update our variable

}


// Finally, we will write out our ledToggle function, which is referenced by the Particle.function() called "led"

int ledToggle(String command) {
lastCall = millis();
    if (command=="on") {
        digitalWrite(led,HIGH);
        ledState =1;
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        ledState =0;
        return 0;
    }
    else  if (command=="toggle") {
        if (ledState==0){
        digitalWrite(led,HIGH);
        ledState =1;
        return 1;
        }
    
        
        else{
        digitalWrite(led,LOW);
        ledState =0;
        return 0;   
            
        }
    }
        else  if (command=="blink") {
        digitalWrite(led,LOW);
        delay(100);
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        delay(100);
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        if(ledState ==1){
        digitalWrite(led,HIGH);
        return 1;
        }
        else{
         return 0;   
            
        }
        
        
        
        }
    else {
        return -1;
    }

}


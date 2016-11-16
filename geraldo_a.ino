//This sketch sends data to Geraldo_B. 

int buttonPin = D3;
bool triggered = false;
long triggerTime;

//int lightPin = A5;
//int lightValue;
//int lightPublishTime;


void setup() {
//Particle.variable("sensorValue", &lightValue, INT); 
pinMode(buttonPin,INPUT_PULLDOWN);
Serial.begin(9600);

}

void loop() {

    if(digitalRead(buttonPin) &&(!triggered))
    {
        Serial.println("pressed, now going to publish it");
        Particle.publish("GeraldoA","pressed");
        triggered= true;
        triggerTime = millis();
    }
    
    else if(!digitalRead(buttonPin) &&(triggered))
    {
         Serial.println("released, now going to publish it");
        Particle.publish("GeraldoA","released");
        triggered = false;
    }
    /*
    lightValue = analogRead(lightPin);

    
    if(millis()>lightPublishTime +2000)
    {
        Serial.print("Light Value : ");
        Serial.print(lightValue); 
        Serial.println(",  now going to publish it");
       Particle.publish("GeraldoA", String(lightValue));
       lightPublishTime = millis();
    }
    */
}

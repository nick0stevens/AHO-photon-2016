/* This is the first of two webhooks for this sketch


{
    "event": "getWeather",
    "url": "https://api.darksky.net/forecast/YOUR DARK SKY KEY HERE59.920311,10.767249",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{currently.temperature}}",
    "query": {
        "units": "si",
        "exclude": "minutely,hourly,daily,alerts,flags"
    }
}
Here is the second webhook
{
    "event": "getOldWeather",
    "url": "https://api.darksky.net/forecast/YOUR DARK SKY KEY HERE/59.920311,10.767249,{{{PARTICLE_EVENT_VALUE}}}",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{currently.temperature}}",
    "query": {
        "units": "si",
        "exclude": "minutely,hourly,daily,alerts,flags"
    }
}


*/


// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>
//----------------- LED Handling ------------------------
#define PIXEL_COUNT 11
#define pin 3
#define PIXEL_TYPE WS2812B

STARTUP(pinMode(pin, INPUT_PULLDOWN);)

Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, pin, PIXEL_TYPE);



double oldTemp = 1;
double newTemp = 5;
double diff;
bool triggered = false;
bool calcTriggered = false;
int interval = 10; // time between weather readings

void setup() {
Serial.begin(9600);

Particle.variable("oldWeather",oldTemp);
Particle.variable("newWeather",newTemp);
Particle.variable("difference", diff);
Particle.function("calculate", calculate);
Particle.function("freshData", grabData);
Particle.subscribe("hook-response/getWeather", weatherHandler, MY_DEVICES);
Particle.subscribe("hook-response/getOldWeather", oldWeatherHandler, MY_DEVICES);
Time.zone(+1);  // setup a time zone, which is part of the ISO6801 format
 
     ring.begin();
     ring.setPin(pin);
    ring.show();
    ring.setBrightness(64);
 
}

void loop() {
    
    

  if(Time.minute()%interval==0) {   // check to see if current minute is divisable by 10
  if(!triggered){
      triggered = true;
      grabData("now");

  }
 }
 else{
     triggered = false;
 }
   if(Time.minute()%interval==1) {   // check to see if current minute is divisable by 10
  if(!calcTriggered){
      calcTriggered = true;
      calculate("now");

  }
 }
 else{
     calcTriggered = false;
 }
 
 setLights();
 
}

void weatherHandler(const char *event, const char *data) {
  // Handle the integration response
   String temp = String(data);
    newTemp = temp.toFloat();
  
}
          


void oldWeatherHandler(const char *event, const char *data) {
  // Handle the integration response
   String temp = String(data);
    oldTemp = temp.toFloat();
     // oldTemp = temp.toInt();

}
   
 int calculate(String command) {
     
     diff = newTemp -oldTemp;
     return 1;
 }

 int grabData(String command) {
     
  time_t time = Time.now(); // get current Tiem in UNIX
  time = time -31556926; // subtract one year from UNIX time (time in second)
  String data = Time.format(time, TIME_FORMAT_ISO8601_FULL); //  convert UNIX time to ISO8601 ie.2004-01-10T08:22:04-05:15


  Serial.println("grabbing data now!");
  Particle.publish("getOldWeather", data, PRIVATE);
  Particle.publish("getWeather", "data", PRIVATE);
  return 1;
 }
 
 void setLights(){
     diff = int(diff);
     
     if(diff>5){
         diff=5;
     }
     if(diff<-5){
         diff=-5;
     }
     for(int i = -5;i<6;i++){
         if(diff<0){
         if(i>=diff&&i<0){
             
             ring.setPixelColor(i+5, ring.Color(0,0,50));
         }
         else  {ring.setPixelColor(i+5, ring.Color(0,0,0));}
         }
         
         if(diff>0){
         if(i<=diff&&i>0){
             
             ring.setPixelColor(i+5, ring.Color(50,0,0));
         }
         else  {ring.setPixelColor(i+5, ring.Color(0,0,0));}
         }
         
     }
     ring.setPixelColor(0+5, ring.Color(50,50,50));
      ring.show();
 }

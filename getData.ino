/*
this sketch triggers a webhook called "getData" every 2 mins
the data it obtains is then available as numerical and text variable, getNumber and getText.

webhook details
{
    "event": "getData",
    "url": "http://api.open-notify.org/iss-now.json",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{iss_position.latitude}}"
}

*/

double inputValue = -3.4;
String inputText = "aaa";
bool triggered = false;

void setup() {
  Particle.subscribe("hook-response/getData", myHandler, MY_DEVICES);
  Particle.function("getFreshData", getData);
  Particle.variable ( "getNumber", inputValue);
  Particle.variable ( "getText", inputText);
}

void loop() {

 if(Time.minute()%2==0) {   // check to see if current minute is divisable by 15
  if(!triggered){
      triggered = true;
getData("");
  }
 }
 else{
     triggered = false;
 }
}

void myHandler(const char *event, const char *inData) {

    inputText = String(inData);
    inputText=inputText.replace(" ","");
    inputValue=atoll(inputText);
   
}

int getData(String outData){  
Particle.publish("getData", outData, PRIVATE);
}

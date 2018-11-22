/*
this sketch triggers a webhook called "getData" every 2 mins
the data it obtains is then available as numerical and text variable, getNumber and getText.
*/

double inputValue = -3.4;
String inputText = "aaa";
bool triggered = false;

void setup() {
  Particle.subscribe("hook-response/getData", myHandler, MY_DEVICES);
  Particle.variable ( "getNumber", inputValue);
  Particle.variable ( "getText", inputText);
}

void loop() {

 if(Time.minute()%2==0) {   // check to see if current minute is divisable by 15
  if(!triggered){
      triggered = true;
  Particle.publish("getData", "outData", PRIVATE);
  }
 }
 else{
     triggered = false;
 }
}

void myHandler(const char *event, const char *inData) {
   
    inputText = String(inData);
    inputValue = inputText.toFloat();
    
}

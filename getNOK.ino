/*
This sketch grabs the 30 most recent entrys from the webhook, parses them and enters them into an array. the fires a second webhook to grab the second 30 entries

More than 30 entries (of 13 digits) will be delivered to the photon in two packets and will cause the array to be overwritten.

NOTE: the name of the second webhook must be suitably differnt than the first otherwise it will trigger the first one.
ie getNOK and get2NOK works ok

*/

*/
an example webhook, Note that the mustache template is filled with static numbers in this case!


{
    "event": "get2NOK",
    "url": "https://www.nbim.no/LiveNavHandler/Current.ashx?",
    "requestType": "POST",
    "noDefaults": false,
    "rejectUnauthorized": true,
    "responseTemplate": "8505348589254_8505376679454_8505402919855_8505429694186_8505458161220_8505488667028_8505348589254_8505376679454_8505402919855_8505429694186_8505458161220_8505488667028_8505348589254_8505376679454_8505402919855_8505429694186_8505458161220_8505488667028_8505348589254_8505376679454_8505402919855_8505429694186_8505458161220_8505488667028_8505348589254_8505376679454_8505402919855_8505429694186_8505488667028_7777777777777",
    "query": {
        "t": "1542364730588",
        "PreviousNavValue": "8352138546741",
        "key": "263c30dd-d5ba-41d6-a9b1-c1fb59cf30da",
        "l": "no"
    }
}



*/




double inputValues[60];
String inputText = "aaa";
bool triggered = false;
int interval= 2; // this determines how often new data is collected in minutes

void setup() {
  Particle.subscribe("hook-response/getNOK", myHandler, MY_DEVICES);
  Particle.subscribe("hook-response/get2NOK", myHandler2, MY_DEVICES);
  Particle.function("getFreshData", getData);
  Particle.function("setRate", setData);
  Particle.variable ( "getNumber30", inputValues[29]);
  Particle.variable ( "getNumber59", inputValues[58]);
  Particle.variable ( "getText", inputText);
  

}

void loop() {
Serial.begin(9600);
 if(Time.minute()%interval==0) {   // check to see if current minute is divisable by interval
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
    
   
    inputText = String(inData); // convert char array to string
    inputText=inputText.replace(" ",""); // remove any whitespaces
    char strBuffer[800] = ""; //create  char array
    //Serial.println( str);
    inputText.toCharArray(strBuffer, 500); //string into char array
    inputValues[0]=atoll(strtok(strBuffer, "_")); // remove text upto first underscore and convert to longlong then insert in to first location in array of doubles
    Serial.println(inputValues[0]);
    for(int i =1;i<30;i++){
        inputValues[i]=atoll(strtok(NULL, "_")); // remove 30 subsequent srtings upto next underscore,convert to longlong and insert in to sequential array of doubles
       Serial.println(inputValues[i]); 
    }
   
   Particle.publish("get2NOK", "outData", PRIVATE);
 
}

void myHandler2(const char *event, const char *inData) {
    
   
    inputText = String(inData); // convert char array to string
    inputText=inputText.replace(" ",""); // remove any whitespaces
    char strBuffer[800] = ""; //create  char array
    //Serial.println( str);
    inputText.toCharArray(strBuffer, 500); //string into char array
    inputValues[30]=atoll(strtok(strBuffer, "_")); // remove text upto first underscore and convert to longlong then insert in to 31 location in array of doubles
    Serial.println(inputValues[30]);
    for(int i =30;i<60;i++){
        inputValues[i]=atoll(strtok(NULL, "_")); // remove 30 subsequent srtings upto next underscore,convert to longlong and insert in to sequential array of doubles
       Serial.println(inputValues[i]); 
    }
   
 
}

int getData(String outData){  
Particle.publish("getNOK", outData, PRIVATE);
return 1;
}

int setData(String inData){  
inputValues[29]= atoll(inData); // receive data from function and insert it into the last position in the array of doubles
return 1;
}

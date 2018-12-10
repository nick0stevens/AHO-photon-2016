/*
This sketch grabs the 20 most recent entrys from the webhook, parses them and enters them into an array. the fires a second, then 3rd webhook to grab the sremaining entries

More than 30 entries (of 13 digits) will be delivered to the photon in two packets and will cause the array to be overwritten.

NOTE: the name of the second and third webhooks must be suitably differnt than the first otherwise it will trigger the first one.
ie getNOK and get2NOK works ok

{
    "event": "getNOK",
    "url": "https://www.nbim.no/LiveNavHandler/Current.ashx?",
    "requestType": "POST",
    "noDefaults": false,
    "rejectUnauthorized": true,
    "responseTemplate": "{{d.liveNavList.0.values.0.Value}}_{{d.liveNavList.0.values.1.Value}}_{{d.liveNavList.0.values.2.Value}}_{{d.liveNavList.0.values.3.Value}}_{{d.liveNavList.0.values.4.Value}}_{{d.liveNavList.0.values.5.Value}}_{{d.liveNavList.0.values.6.Value}}_{{d.liveNavList.0.values.7.Value}}_{{d.liveNavList.0.values.8.Value}}_{{d.liveNavList.0.values.9.Value}}_{{d.liveNavList.0.values.10.Value}}_{{d.liveNavList.0.values.11.Value}}_{{d.liveNavList.0.values.12.Value}}_{{d.liveNavList.0.values.13.Value}}_{{d.liveNavList.0.values.14.Value}}_{{d.liveNavList.0.values.15.Value}}_{{d.liveNavList.0.values.16.Value}}_{{d.liveNavList.0.values.17.Value}}_{{d.liveNavList.0.values.18.Value}}_{{d.liveNavList.0.values.19.Value}}",
    "query": {
        "t": "1542364730588",
        "PreviousNavValue": "8352138546741",
        "key": "263c30dd-d5ba-41d6-a9b1-c1fb59cf30da",
        "l": "no"
    }
}


{
    "event": "get2NOK",
    "url": "https://www.nbim.no/LiveNavHandler/Current.ashx?",
    "requestType": "POST",
    "noDefaults": false,
    "rejectUnauthorized": true,
    "responseTemplate": "{{d.liveNavList.0.values.20.Value}}_{{d.liveNavList.0.values.21.Value}}_{{d.liveNavList.0.values.22.Value}}_{{d.liveNavList.0.values.23.Value}}_{{d.liveNavList.0.values.24.Value}}_{{d.liveNavList.0.values.25.Value}}_{{d.liveNavList.0.values.26.Value}}_{{d.liveNavList.0.values.27.Value}}_{{d.liveNavList.0.values.28.Value}}_{{d.liveNavList.0.values.29.Value}}_{{d.liveNavList.0.values.30.Value}}_{{d.liveNavList.0.values.31.Value}}_{{d.liveNavList.0.values.32.Value}}_{{d.liveNavList.0.values.33.Value}}_{{d.liveNavList.0.values.34.Value}}_{{d.liveNavList.0.values.35.Value}}_{{d.liveNavList.0.values.36.Value}}_{{d.liveNavList.0.values.37.Value}}_{{d.liveNavList.0.values.38.Value}}_{{d.liveNavList.0.values.39.Value}}",
    "query": {
        "t": "1542364730588",
        "PreviousNavValue": "8352138546741",
        "key": "263c30dd-d5ba-41d6-a9b1-c1fb59cf30da",
        "l": "no"
    }
}


{
    "event": "get3NOK",
    "url": "https://www.nbim.no/LiveNavHandler/Current.ashx?",
    "requestType": "POST",
    "noDefaults": false,
    "rejectUnauthorized": true,
    "responseTemplate": "{{d.liveNavList.0.values.40.Value}}_{{d.liveNavList.0.values.41.Value}}_{{d.liveNavList.0.values.42.Value}}_{{d.liveNavList.0.values.43.Value}}_{{d.liveNavList.0.values.44.Value}}_{{d.liveNavList.0.values.45.Value}}_{{d.liveNavList.0.values.46.Value}}_{{d.liveNavList.0.values.47.Value}}_{{d.liveNavList.0.values.48.Value}}_{{d.liveNavList.0.values.49.Value}}_{{d.liveNavList.0.values.50.Value}}_{{d.liveNavList.0.values.51.Value}}_{{d.liveNavList.0.values.52.Value}}_{{d.liveNavList.0.values.53.Value}}_{{d.liveNavList.0.values.54.Value}}_{{d.liveNavList.0.values.55.Value}}_{{d.liveNavList.0.values.56.Value}}_{{d.liveNavList.0.values.57.Value}}_{{d.liveNavList.0.values.58Value}}_{{d.liveNavList.0.values.59.Value}}",
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
    Particle.subscribe("hook-response/get3NOK", myHandler3, MY_DEVICES);

  Particle.function("getFreshData", getData);
  Particle.function("setRate44", setData);
  Particle.variable ( "getNumber1", inputValues[0]);
  Particle.variable ( "getNumber20", inputValues[19]);
   Particle.variable ( "getNumber21", inputValues[20]);
  Particle.variable ( "getNumber40", inputValues[39]);
Particle.variable ( "getNumber41", inputValues[40]);
  Particle.variable ( "getNumber60", inputValues[49]);
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
    //Serial.println(inputValues[0]);
    for(int i =1;i<20;i++){
        inputValues[i]=atoll(strtok(NULL, "_")); // remove 30 subsequent srtings upto next underscore,convert to longlong and insert in to sequential array of doubles
       Serial.println(i); 
    }
   
   Particle.publish("get2NOK", "outData", PRIVATE);
 
}

void myHandler2(const char *event, const char *inData) {
    
   
    inputText = String(inData); // convert char array to string
    inputText=inputText.replace(" ",""); // remove any whitespaces
    char strBuffer[800] = ""; //create  char array
    //Serial.println( str);
    inputText.toCharArray(strBuffer, 500); //string into char array
    inputValues[20]=atoll(strtok(strBuffer, "_")); // remove text upto first underscore and convert to longlong then insert in to 31 location in array of doubles
    //Serial.println(inputValues[20]);
    for(int i =21;i<40;i++){
        inputValues[i]=atoll(strtok(NULL, "_")); // remove 20 subsequent srtings upto next underscore,convert to longlong and insert in to sequential array of doubles
       Serial.println(i); 
    }
   
  Particle.publish("get3NOK", "outData", PRIVATE);
}

void myHandler3(const char *event, const char *inData) {
    
   
    inputText = String(inData); // convert char array to string
    inputText=inputText.replace(" ",""); // remove any whitespaces
    char strBuffer[800] = ""; //create  char array
    //Serial.println( str);
    inputText.toCharArray(strBuffer, 500); //string into char array
    inputValues[40]=atoll(strtok(strBuffer, "_")); // remove text upto first underscore and convert to longlong then insert in to 31 location in array of doubles
    //Serial.println(inputValues[40]);
    for(int i =41;i<60;i++){
        inputValues[i]=atoll(strtok(NULL, "_")); // remove 20 subsequent srtings upto next underscore,convert to longlong and insert in to sequential array of doubles
       
       Serial.println(i);
       Serial.println(inputValues[i]); 
        
    }
   
 
}

int getData(String outData){  
Particle.publish("getNOK", outData, PRIVATE);
return 1;
}

int setData(String inData){  
inputValues[43]= atoll(inData); // receive data from function and insert it into the last position in the array of doubles
return 1;
}

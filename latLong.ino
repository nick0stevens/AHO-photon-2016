double mag = 0.4;  
String loc = "place";



void setup() {

Time.zone(+1); // set time zone

Particle.variable("magnitude", mag);
Particle.variable("location", loc);
Particle.subscribe("hook-response/getEarthquakeData", myHandler, MY_DEVICES);



}

void loop() {

Time.zone(+1);  // setup a time zone, which is part of the ISO6801 format
 
time_t time = Time.now(); // get current Tiem in UNIX
time = time -600; // subtract 10 minutes from UNIX time (time in second)
String data = Time.format(time, TIME_FORMAT_ISO8601_FULL); //  convert UNIX time to ISO8601 ie.2004-01-10T08:22:04-05:15


 Particle.publish("getEarthquakeData", data, PRIVATE);
  // Wait 60 seconds
  delay(600000); //Check every 10mins (time in milliseconds )
}



void myHandler(const char *event, const char *data) {
  // Handle the integration response
    String str = String(data);
    char strBuffer[500] = "";
    str.toCharArray(strBuffer, 500);

    double _mag = atof(strtok(strBuffer, "&"));
    String _loc = strtok(NULL, "&");
    
    if(_mag !=0)mag= _mag; //check if the  magnitude data is new and valid
    if(strcmp(_loc,"")!=0) loc = _loc;  //check if the  location data is new and valid
    
    if(mag>5){
        digitalWrite(D7,HIGH);
    }
    else{
      digitalWrite(D7,LOW);  
    }
 
}
          

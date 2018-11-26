/* this webhook retreives the data for the sketch below

{
    "event": "getQuake",
    "url": "https://earthquake.usgs.gov/fdsnws/event/1/query?",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{features.0.properties.mag}}&{{features.0.properties.time}}&\n{{features.1.properties.mag}}&{{features.1.properties.time}}&\n{{features.2.properties.mag}}&{{features.2.properties.time}}",
    "query": {
        "format": "geojson",
        "orderby": "time-asc",
        "starttime": "{{{PARTICLE_EVENT_VALUE}}}"
    }
}

*/



double mag1, mag2, mag3;
unsigned long int time1, time2, time3;
String time1Text,time2Text,time3Text;
int interval = 10;
bool triggered = false;
void checkOldQuakes();
bool noted1 = false;
bool noted2 = false;
bool noted3 = false;


void setup() {
    
 Particle.variable("1stMag",mag1); 
 Particle.variable("1stTime",time1Text); 
 
 Particle.variable("2ndMag",mag2); 
 Particle.variable("2ndTime",time2Text);
 
  Particle.variable("3rdMag",mag3); 
 Particle.variable("3rdTime",time3Text);

  Particle.subscribe("hook-response/getQuake", myHandler, MY_DEVICES);
  Particle.function("freshData",grabData);
  Time.zone(+1);  // setup a time zone, which is part of the ISO6801 format
  
  Serial.begin(9600);
 
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

checkOldQuakes();

}

int grabData(String command){
    Serial.println("grabbing Data");

  time_t time = Time.now(); // get current Tiem in UNIX
  time = time -1800; // subtract 10 minutes from UNIX time (time in second)
  String data = Time.format(time, TIME_FORMAT_ISO8601_FULL); //  convert UNIX time to ISO8601 ie.2004-01-10T08:22:04-05:15

  Particle.publish("getQuake", data, PRIVATE);
    
    
  delay(2000) ; 
  return 1;
}

void myHandler(const char *event, const char *data) {
  // Handle the integration response
    String str = String(data);
    Serial.println( str);
    char strBuffer[500] = "";
    str.toCharArray(strBuffer, 500);

    char Buffer[500] = "";
    
    mag1 = atof(strtok(strBuffer, "&"));
    time1Text = strtok(NULL, "&");
    time1Text.remove(10);
    Serial.println( time1Text);
    time1= atoll(time1Text);
    Serial.println(time1 );

    
    mag2 = atof(strtok(NULL, "&"));
    time2Text = strtok(NULL, "&");
    time2Text.remove(10);
    Serial.println( time2Text);
    time2= atoll(time2Text);
    Serial.println(time2 );
    
    mag3 = atof(strtok(NULL, "&"));
    time3Text = strtok(NULL, "&");
    time3Text.remove(10);
    Serial.println( time3Text);
    time3 = atoll(time3Text);
    Serial.println(time3 );
    

}
 
void checkOldQuakes(){
     
     if(time1!=0){
     if(Time.minute() == Time.minute(time1)+30){
         if(!noted1){
         Serial.println("30mins since earthquake 1");
         noted1 = true;
         }
     }
     else{noted1 = false;}
     }
      if(time2!=0){
          if(Time.minute() == Time.minute(time2)+30){
              if(!noted2){
         Serial.println("30mins since earthquake 2");
         noted2 = true;
              }
     }
     else{noted2 = false;}
      }
      if(time3!=0){
          if(Time.minute() == Time.minute(time3)+30){
              if(!noted3){
         Serial.println("30mins since earthquake 3");
         noted3 = true;
              }
     }
     else{noted3 = false;}
      }
 }         

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


bool quake1motor = false;
bool quake2motor = false;
bool quake3motor = false;
long quake1start;

int led1 = D7;
int motorPin = D1;


int minMag = 1;

long motorPeriod = 3000;

 int onPeriod,offPeriod;
long  lightOnTime, lightOffTime;
  bool     quakeLightSet = false;
    bool     lightsBlinking  = false;

void setup() {
    
 Particle.variable("1stMag",mag1); 
 Particle.variable("1stTime",time1Text); 
 
 Particle.variable("2ndMag",mag2); 
 Particle.variable("2ndTime",time2Text);
 
  Particle.variable("3rdMag",mag3); 
 Particle.variable("3rdTime",time3Text);

  Particle.subscribe("hook-response/getQuake", myHandler, MY_DEVICES);
  Particle.function("freshData",grabData);
   Particle.function("createData",createQuake);
  Time.zone(+1);  // setup a time zone, which is part of the ISO6801 format
  
  Serial.begin(9600);
  
  pinMode(led1, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(led1, HIGH);
  
 //digitalWrite(led1, HIGH); 
 
}

void loop() {
    
    //digitalWrite(led1, HIGH);

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
runMotors();
runLights();
}


int createQuake(String str){
     
     
    Serial.println( str);
    char strBuffer[500] = "";
    str.toCharArray(strBuffer, 500);

    char Buffer[500] = "";
    
    mag1 = atof(strtok(strBuffer, "_"));
    time1Text = strtok(NULL, "_");
    Serial.println( time1Text);
    //time1= atoll(time1Text);
    time1 = time1Text.toInt();
    //time1 = double(time-1800);
    time1 = time1-1735;
    //time1 = holder;
    Serial.println(time1 );
    
    
    

//myHandler("header", str);
    return 1;
     
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
    
    mag1 = atof(strtok(strBuffer, "_"));
    time1Text = strtok(NULL, "_");
    time1Text.remove(10);
    Serial.println( time1Text);
    time1= time1Text.toInt();
    
    Serial.println(time1 );

    
    mag2 = atof(strtok(NULL, "_"));
    time2Text = strtok(NULL, "_");
    time2Text.remove(10);
    Serial.println( time2Text);
    time2= time2Text.toInt();
    Serial.println(time2 );
    
    mag3 = atof(strtok(NULL, "_"));
    time3Text = strtok(NULL, "_");
    time3Text.remove(10);
    Serial.println( time3Text);
    time3 =time3Text.toInt();
    Serial.println(time3 );
    

}
 
void checkOldQuakes(){
  
     if(time1!=0){
          

        
         int quake1min = Time.minute(time1)+30;
          if(quake1min>60){quake1min=quake1min-60;}
         /*          Serial.print("Time1: ");
          Serial.print(time1);
          Serial.print(" current miniutes: ");
          Serial.print(Time.minute());
          Serial.print(" quake miniutes +30: ");
         Serial.print(quake1min);
         Serial.println();
         Serial.println(noted1);
         */
     if(Time.minute() == quake1min){
         //Serial.println("30 mins past quake1");
         if(!noted1){
         Serial.println("30mins since earthquake 1 and first noted");
         lightsBlinking = true;
         earthQuakeWarningLed();
         earthQuakeWarningMotor(1);
         
         noted1 = true;
         Serial.println("setting noted to false");
         }
     }
     else{noted1 = false;}
     }

      if(time2!=0){
                  int quake2min = Time.minute(time2)+30;
          if(quake2min>60){quake2min=quake2min-60;}
          if(Time.minute() == quake2min){
              if(!noted2){
         Serial.println("30mins since earthquake 2");
         lightsBlinking = true;
          earthQuakeWarningLed();
          earthQuakeWarningMotor(2);
         noted2 = true;
              }
     }
     else{noted2 = false;}
      }
  
      
      if(time3!=0){
                int  quake3min = Time.minute(time3)+30;
          if(quake3min>60){quake3min=quake3min-60;}
          if(Time.minute() == quake3min){
              if(!noted3){
         Serial.println("30mins since earthquake 3");
         lightsBlinking = true;
          earthQuakeWarningLed();
          earthQuakeWarningMotor(3);
         noted3 = true;
              }
     }
     else{noted3 = false;}
      }
      
            if(millis()>quake1start+motorPeriod){
          quake1motor = false;
          lightsBlinking = false;
          quakeLightSet = false;
          digitalWrite(led1, HIGH);
          //Serial.println("blinking stops");
      }
      
 } 
 
 void earthQuakeWarningLed(){
              Serial.println("warning ---earthquake");
    if(lightsBlinking){
    if(!quakeLightSet){
         Serial.println("blinking starts");
        onPeriod = random(100,500);
        offPeriod = random(100,500);
        lightOnTime = millis();
        quakeLightSet = true;
       digitalWrite(led1, LOW);
        Serial.println("light off");
    }
    
    }
    
 }
 
 void runLights(){
       if(lightsBlinking){
    
    if(millis()>lightOnTime+offPeriod){
    
    digitalWrite(led1, HIGH);
    Serial.println("light on");
 
    }
        if(millis()>lightOnTime+onPeriod+offPeriod){
    
    digitalWrite(led1, LOW); 
    onPeriod = random(100,500);
    offPeriod = random(100,500);
    lightOnTime = millis();
     Serial.println("flash again");
    }
    } 
     
 }
 
 void earthQuakeWarningMotor(int quakeNum){
    Serial.println("checking motors");
    //if (mag1 > 2) 
    if(quakeNum ==1){ Serial.println("quake1");
        if(mag1>minMag){
             Serial.println("quake over minmage");
           quake1start=millis();
           quake1motor=true;
        }
    }
    
        if(quakeNum ==2){ Serial.println("quake1");
        if(mag1>minMag){
             Serial.println("quake over minmage");
           quake2start=millis();
           quake2motor=true;
        }
    }
    
        if(quakeNum ==3){ Serial.println("quake1");
        if(mag1>minMag){
             Serial.println("quake over minmage");
           quake3start=millis();
           quake3motor=true;
        }
    }
    
 }
 
 void runMotors(){
     if(quake1motor||quake2motor||quake3motor){
         digitalWrite(motorPin,HIGH);
     }
     else{
         digitalWrite(motorPin,LOW);
     }
     
 }​

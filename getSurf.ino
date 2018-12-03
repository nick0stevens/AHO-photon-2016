
/*
this webhook retreives the data for the sketch below

{
    "event": "getSurf",
    "url": "http://api.worldweatheronline.com/premium/v1/marine.ashx?",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{data.weather.0.hourly.0.swellHeight_ft}}_{{data.weather.0.hourly.0.swellPeriod_secs}}_{{data.weather.0.hourly.0.swellDir16Point}}_{{data.weather.0.hourly.0.windspeedKmph}}_{{data.weather.0.hourly.0.winddir16Point}}_{{data.weather.0.tides.0.tide_data.0.tideDateTime}}_{{data.weather.0.tides.0.tide_data.0.tide_type}}_{{data.weather.0.tides.0.tide_data.1.tideDateTime}}_{{data.weather.0.tides.0.tide_data.1.tide_type}}_{{data.weather.0.tides.0.tide_data.2.tideDateTime}}_{{data.weather.0.tides.0.tide_data.2.tide_type}}_{{data.weather.0.tides.0.tide_data.3.tideDateTime}}_{{data.weather.0.tides.0.tide_data.3.tide_type}}",
    "query": {
        "key": "e9d6d8bd1d974f05aaa145946181611",
        "q": "62.124622, 5.154945",
        "format": "json",
        "includelocation": "no",
        "tide": "yes",
        "tp": "1"
    }
}

 /*

hoddevika surf conditions

BAD

example
1_12_E_27_S_2018-12-03 01:58_HIGH_2018-11-28 08:11_LOW


GOOD

example
5_12_W_27_S_2018-12-03 01:58_HIGH_2018-11-28 08:11_LOW

Swell direction: SW-NW
Swell height: 2-7 ft
Swell period: at least 10s

PERFECT

example
5_12_W_2_SE_2018-12-03 01:58_HIGH_2018-12-03 20:55_LOW

Swell direction: SW-NW 
Swell height: 2-7 ft
Swell period: at least 10s
Wind: SE, under 5 km/h (3 mph) ?
Tide: Low-medium (3 hours)

*/

int motorPin=D4;
int lowSpeed = 70;
int highSpeed = 255;
int motorSpeed;

double inputValue = -3.4;
String inputText = "aaa";
bool triggered = false;

double swell, swellPeriod, windSpeed;
unsigned long int highTide1, highTide2, lowTide1,lowTide2;
String swellDir,windDir;

bool swellCk,swellPeriodCk,windSpeedCk,tideCk,swellDirCk,windDirCk;

int surfConditions = 1;

int interval = 2;

void setup() {
  Particle.subscribe("hook-response/getSurf", myHandler, MY_DEVICES);
  Particle.function("getFreshData", getData);
  Particle.variable ( "getSwell", swell);
  Particle.variable ( "getSwPeriod", swellPeriod);
  Particle.variable ( "getSwDir", swellDir);
   Particle.variable ( "getWind", windSpeed);
   Particle.variable ( "getWdDir", windDir);
   Particle.variable ( "getSwDirCk", swellDirCk);
   Particle.variable ( "overall", surfConditions);
   Particle.function("makeWeather", createWeather);
   Serial.begin(9600);
}

void loop() {

 if(Time.minute()%interval==0) {   // check to see if current minute is divisable by 15
  if(!triggered){
      triggered = true;
getData("");
  }
 }
 else{
     triggered = false;
 }
 
 checkConditions();
 runMotor();
}

int createWeather(String newWeather){
    
// accepts upto 63 character ie, 2.6_8.0_SSW_27_S_2018-11-28 01:58_HIGH_2018-11-28 08:11_
   myHandler("header",newWeather);
    
    return 1;
}

void myHandler(const char *event, const char *inData) {
  // Handle the integration response
  
 
    String str = String(inData);
    Serial.println( str);
    char strBuffer[500] = "";
    str.toCharArray(strBuffer, 500);

    char Buffer[500] = "";
    
    swell = atof(strtok(strBuffer, "_"));
    swellPeriod = atof(strtok(NULL, "_"));
    swellDir = strtok(NULL, "_");
    windSpeed = atof(strtok(NULL, "_"));
    windDir = strtok(NULL, "_");
    
    String tideTemp;
    String tideType; 
    
    tideTemp = strtok(NULL, "_");
    Serial.print(" highTide1:");
    Serial.print( tideTemp);
    Serial.println("end");
    tideType = strtok(NULL, "_");
    
    struct tm tm;
    strptime(tideTemp, "%Y-%m-%d %H:%M:%S", &tm);
    if(strcmp(tideType,"HIGH")==0){highTide1 = mktime(&tm);
    }
    else{lowTide1 = mktime(&tm);}
    tideTemp= strtok(NULL, "_");
    Serial.print(" highTide2:");
    Serial.print( tideTemp);
    Serial.println("end");
    String tideType2 = strtok(NULL, "_");
    strptime(tideTemp, "%Y-%m-%d %H:%M:%S", &tm);
    if(strcmp(tideType,"HIGH")==0){lowTide1 = mktime(&tm);}
    else{highTide1 = mktime(&tm);}
    
    tideTemp = strtok(NULL, "_");
    Serial.print(" highTide3:");
    Serial.print( tideTemp);
    Serial.println("end");
    tideType2 = strtok(NULL, "_");
    strptime(tideTemp, "%Y-%m-%d %H:%M:%S", &tm);
    if(strcmp(tideType,"HIGH")==0){highTide2 = mktime(&tm);}
    else{lowTide2 = mktime(&tm);}
    
    tideTemp = strtok(NULL, "_");
    Serial.print(" highTide4:");
    Serial.print( tideTemp);
    Serial.println("end");
    tideType2 = strtok(NULL, "_");
    strptime(tideTemp, "%Y-%m-%d %H:%M:%S", &tm);
    if(strcmp(tideType,"HIGH")==0){lowTide2 = mktime(&tm);}
    else{highTide2 = mktime(&tm);}    
    
    Serial.print(" highTide1: ");
    Serial.println( highTide1);
    Serial.print(" highTide2: ");
    Serial.println( highTide2);
    Serial.print(" lowTide1: ");
    Serial.println( lowTide1);
    Serial.print(" lowTide2: ");
    Serial.println( lowTide2);

}

int getData(String outData){  
Particle.publish("getSurf", outData, PRIVATE);
}

void checkConditions(){


    
   if(swell>2&&swell<7) {
       //Serial.println("yup!");
       swellCk =true;
         } else{swellCk =false; //Serial.println("nope!");
         }
       if(swellPeriod>10) {
       swellPeriodCk =true;
         } else{swellPeriodCk =false;}
    if((strcmp(swellDir,"SW")==0)||(strcmp(swellDir,"WSW")==0)||(strcmp(swellDir,"W")==0)||(strcmp(swellDir,"WNW")==0)||(strcmp(swellDir,"NW")==0)){
       swellDirCk =true; 
            } else{
             swellDirCk =false;   
            }
    long timeFromTide = difftime(lowTide1,Time.now());
    if(timeFromTide>-5400&&timeFromTide<5400){  // 5400 sec is 1.5hr either side of low tide
        tideCk=true;
    }
    else{tideCk=false;}
    
        if((strcmp(windDir,"SE")==0)){
       windDirCk =true; 
            } else{
             windDirCk =false;   
            }
            
               if(windSpeed>3) {
       //Serial.println("yup!");
       windSpeedCk =true;
         } else{windSpeedCk =false; //Serial.println("nope!");
         }
    
}

void runMotor(){
    

    
    if((swellCk)&&(swellDirCk)&&(swellPeriodCk)){
        
        if((windDirCk)&&(windDirCk)&&(tideCk)){
            motorSpeed = highSpeed;
            Serial.println("great Conditions!");
            surfConditions = 3;
        }
        else{
            motorSpeed = lowSpeed;
            Serial.println("surfs ok~~~~~~~~~~~~~~~");
            surfConditions = 2;
        }
    }
    else{
        motorSpeed = 0;
        surfConditions = 1;
    }
    
    
    analogWrite(motorPin, motorSpeed);
}

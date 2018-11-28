
/*
this webhook retreives the data for the sketch below

{
    "event": "getSurf",
    "url": "http://api.worldweatheronline.com/premium/v1/marine.ashx?",
    "requestType": "GET",
    "noDefaults": true,
    "rejectUnauthorized": true,
    "responseTemplate": "{{data.weather.0.hourly.0.swellHeight_ft}}&{{data.weather.0.hourly.0.swellPeriod_secs}}&{{data.weather.0.hourly.0.swellDir16Point}}&{{data.weather.0.hourly.0.windspeedKmph}}&{{data.weather.0.hourly.0.winddir16Point}}&{{data.weather.0.tides.0.tide_data.0.tideDateTime}}&{{data.weather.0.tides.0.tide_data.0.tide_type}}&{{data.weather.0.tides.0.tide_data.1.tideDateTime}}&{{data.weather.0.tides.0.tide_data.1.tide_type}}&{{data.weather.0.tides.0.tide_data.2.tideDateTime}}&{{data.weather.0.tides.0.tide_data.2.tide_type}}&{{data.weather.0.tides.0.tide_data.3.tideDateTime}}&{{data.weather.0.tides.0.tide_data.3.tide_type}}",
    "query": {
        "key": "e9d6d8bd1d974f05aaa145946181611",
        "q": "62.124622, 5.154945",
        "format": "json",
        "includelocation": "no",
        "tide": "yes",
        "tp": "1"
    }
}

*/

double inputValue = -3.4;
String inputText = "aaa";
bool triggered = false;

double swell, swellPeriod, windSpeed;
unsigned long int highTide1, highTide2, lowTide1,lowTide2;
String swellDir,windDir;

bool swellCk,swellPeriodCk,windSpeedCk,tideCk,swellDirCk,windDirCk;


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
   if(swell>2&&swell<5) {
       swellCk =true;
         } else{swellCk =false;}
       if(swellPeriod>2&&swellPeriod<5) {
       swellPeriodCk =true;
         } else{swellPeriodCk =false;}
    if(strcmp(swellDir,"W")==0){
       swellDirCk =true; 
            } else{
             swellDirCk =false;   
            }
            long timeFromTide = difftime(highTide1,Time.now());
    if(timeFromTide>-1200&&timeFromTide<1200){
        tideCk=true;
    }
    else{tideCk=false;}
}

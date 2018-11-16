

/*
converts uint32_t UNIX time to human readable STRING format


*/


String realTime = "now";
uint32_t nowTime;
   
void setup(){ 
Time.zone(+1); // set timezone to CET
Particle.variable("currentTime",realTime);  
Particle.variable("UNIXTime",nowTime);
}

void loop() {
 nowTime = Time.now(); // get current time in UNIX format
 realTime = UNIXtimeToConvert(nowTime);   // convert time to Human readable version

}

String UNIXtimeToConvert(long data){
    
    return Time.timeStr(data);
}

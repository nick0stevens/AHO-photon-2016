time_t nowTime;
time_t thenTime;

bool set = false;
bool get = false;

void setup() {
Serial.begin(9600);
pinMode(D7,OUTPUT);
}

void loop() {
    
    nowTime = Time.now();
    if(Time.minute()%4==0){
        if(!set){
        Serial.println("setting time");
        thenTime = Time.now();
        set = true;
        }
          }
          else{
            set = false;  
          }
          
    if(Time.minute()==Time.minute(thenTime)+2){
            if(!get) { 
                get = true;
              Serial.println("2 mins since setting time");
              digitalWrite(D7,HIGH);
            }
          }
          else{ digitalWrite(D7,LOW); get = false;}

}

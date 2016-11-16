/*
this sketch is to be uploaded to Geraldo_B and listens for data from Geraldo_A. That data can be a text or a value.

*/

long triggeredTime;
bool triggered = false;
//int flashFlash(String command);
//bool flashOn = false;

void setup() {
   //Particle.function("flash", flashFlash);
    Particle.subscribe("GeraldoA", dataHandler); // this listens for and receives any info with the title GeraldoA, it then passes the content to dataHandler
    Serial.begin(9600);
    pinMode(D7,OUTPUT);
    RGB.control(true);
    RGB.color(255, 255, 255);
    RGB.brightness(0);
    
}

void loop() {


}


void dataHandler(const char *event, const char *data)
{

    
  if (strcmp(data,"released")==0) {
    digitalWrite(D7,LOW);

  }
  else if (strcmp(data,"pressed")==0) {

        digitalWrite(D7,HIGH);
        triggeredTime = millis();
  }
  else {
      int ledNum = String(data).toInt();
      
      Serial.print("incoming: ");
      Serial.print(ledNum);
      
      ledNum =map(ledNum,1200,2700,255,0);
      ledNum= constrain(ledNum,0,255);
      
      Serial.print(" ledNum: ");
      Serial.println(ledNum);

      RGB.brightness(ledNum);
  }
}
/*
int flashFlash(String command)
{
    if(!flashOn){
        RGB.brightness(100);
        flashOn = true;
        }
    else {
        RGB.brightness(0);
        flashOn = false;
        }
    return 1;

}
*/

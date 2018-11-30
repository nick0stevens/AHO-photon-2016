/* this arduino sketch outputs three variable 
x, y, z to the serial port and can be read in 
processing

*/

float x,y,z;

void setup() {
// initialize serial communication. 
//This must be the same rate as the processign serial
Serial.begin(9600);
}


void loop() {
// read in the sensors
x = analogRead(A0);
y = analogRead(A1);
z = analogRead(A2);

// map the sensors if needed

// x= map(x,0,1023,0,1);


// print out the value you read:
Serial.print(x);
Serial.print(',');
Serial.print(y);
Serial.print(',');
Serial.println(z);


delay(1); // delay in between reads for stability
}

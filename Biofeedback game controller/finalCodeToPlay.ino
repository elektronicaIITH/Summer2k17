int flexUp = A0; //analog pin 0
int flexRight = A1;
int flexLeft = A2;
void setup(){
  Serial.begin(9600);
}

void loop(){
  int muscle1 = analogRead(flexUp); 
  int flexSensorReading1 = analogRead(flexRight); 
  int flexSensorReading2 = analogRead(flexLeft); 
  int muscle2 = analogRead(A3);


//3.9,3.95,4.1
//3.1(4.1),M2.8,2.95(3.95 right);47K
float voltageUp = muscle1 * (5.0 / 1023.0);
float voltageRight = flexSensorReading1 * (5.0 / 1023.0);
float voltageLeft = flexSensorReading2 * (5.0 / 1023.0);
float voltageDown= muscle2 * (5.0 / 1023.0);
//Serial.print(voltageUp );
//Serial.print(voltageRight );
//Serial.print(voltageLeft );//Serial.print(voltageRight );Serial.println(voltageLeft);
   if(voltageUp > 0.95)
    Keyboard.write(218);
   if(voltageRight < 1.3)
    Keyboard.write(215);
   if(voltageLeft < 1)
    Keyboard.write(216);
   if(voltageDown > 1)
    Keyboard.write(217);
  delay(100); //just here to slow down the output for easier reading
}

int SensorPin = A0; //analog pin 0

void setup(){
  Serial.begin(9600);
}

void loop(){
  int SensorReading = analogRead(SensorPin); 

  Serial.println(SensorReading);



float voltage = SensorReading * (5.0 / 1023.0);
Serial.println(voltage);    
   
  delay(500);//just here to slow down the output for easier reading
}



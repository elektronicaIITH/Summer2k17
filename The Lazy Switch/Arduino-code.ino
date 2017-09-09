#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX
char myChar;
char prev;
bool ledon = true;
#define led1 10  //this 10th digital pin on arduino was input for relay
void setup() 
{
    Serial.begin(9600);   //communication rate between arduino and pc
    mySerial.begin(38400); //communication rate between arduino and bluetooth module  **this may be different depends on your bluetooth module**
    pinMode(led1, OUTPUT);
}

void loop()
{
   while(mySerial.available())  //runs when data is received
    {
        myChar = (byte) mySerial.read();  //storing received data into myChar
        Serial.print(myChar);   //just to verify that we are receiving valid data... you can see it on serial monitor(ctrl+Shift+M)

        if(myChar == '1')  
        {
           off1();
        }
        else if(myChar == '2')
        {
           on1();
        }
        else if(myChar == '5')
        {
          pattern();
        }
        prev = myChar;
    } 
}

void on1()
{
    digitalWrite(led1 , 1);
    Serial.println(":1st on");
}
void off1()
{
    digitalWrite(led1 , 0);
    Serial.println(":1st off");
}
void pattern()
{
    Serial.println("started");
    while(1)
    { 
        if(mySerial.available()) //for stopping while loop
        { 
          myChar = (byte) mySerial.read();
          if(myChar == '5')
            break;
        }

        myChar = (byte) mySerial.read();
        on1();
        delay(1000);
        off1();
        delay(1000);
    }
    if(prev == '1')
    {
        off1();
    }
    else if(prev == '2')
    {
        on1();  
    }
    Serial.println("stopped");
}


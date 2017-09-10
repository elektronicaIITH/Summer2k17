#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX  //defines that there is communication named as 'mySerial' at 0,1 pins where 0 is receiving pin and 1 is transmitting pin of arduino
char myChar;
char prev;
bool ledon = true;
#define led1 10  //this 10th digital pin on arduino was input for relay
void setup() 
{
    Serial.begin(9600);   //communication rate between arduino and pc
    mySerial.begin(38400); //communication rate between arduino and bluetooth module  **this may be different depends on your bluetooth module**
    pinMode(led1, OUTPUT);  //telling arduino that we'll be using 10th digital pin
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
        else if(myChar == '5') //these values(ie 1,2,5) are arbitary u can use characters also but then you have to change in app also..
        {
          pattern();
        }
        prev = myChar;
    } 
}

void on1()
{
    digitalWrite(led1 , 1);  //10th pin HIGH
    Serial.println(":1st on");
}

void off1()
{
    digitalWrite(led1 , 0);  //10th pin LOW
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

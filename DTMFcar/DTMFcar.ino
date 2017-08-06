//pins to control the motors
#define m11 8
#define m12 9
#define m21 10
#define m22 11
// pins for input from the DTMF module
#define D0 4
#define D1 5
#define D2 6
#define D3 7
// Function for forward movement of the bot
void forward(){
	digitalWrite(m11,LOW);
	digitalWrite(m12, HIGH);
	digitalWrite(m21, HIGH);
	digitalWrite(m22,LOW);
}
// Function for backward movement of the bot
void backward(){
	digitalWrite(m11, HIGH);
	digitalWrite(m12, LOW);
	digitalWrite(m21, LOW);
	digitalWrite(m22, HIGH); 
}
// Function for left movement of the bot
void left(){
	digitalWrite(m11, LOW);
	digitalWrite(m12, LOW);
	digitalWrite(m21, HIGH);
	digitalWrite(m22, LOW);
}

// Function for right movement of the bot
void right(){
	digitalWrite(m11, LOW);
	digitalWrite(m12, HIGH);
	digitalWrite(m21, LOW);
	digitalWrite(m22, LOW);
}
// Function to stop the bot
void Stop(){
	digitalWrite(m11, LOW);
	digitalWrite(m12, LOW);
	digitalWrite(m21, LOW);
	digitalWrite(m22, LOW);
}

void setup(){
	Serial.begin(9600);

	pinMode(D0, INPUT);
	pinMode(D1, INPUT);
	pinMode(D2, INPUT);
	pinMode(D3, INPUT);
	pinMode(m11, OUTPUT);
	pinMode(m12, OUTPUT);
	pinMode(m21, OUTPUT);
	pinMode(m22, OUTPUT);
	pinMode(13, OUTPUT);

	digitalWrite(13, HIGH);
}

void loop(){
  
	int t3= digitalRead(D3);
	int t2= digitalRead(D2);
	int t1= digitalRead(D1);
	int t0= digitalRead(D0);

	Serial.print(t3);
	Serial.print(t2);
	Serial.print(t1);
	Serial.print(t0);
	Serial.println("\t");
	// IF pressed 2, move forward
	if(t3==0 && t2==0 && t1==1 && t0==0){
		forward();
	}
	// IF pressed 4, move left
	else if(t3==0 && t2==1 && t1==0 && t0==0){
		left();
	}
	// IF pressed 6, move right
	else if(t3==0 && t2==1 && t1==1 && t0==0){
		right();
	}
	// IF pressed 8, move back
	else if(t3==1 && t2==0 && t1==0 && t0==0){
		backward();
	}
	// IF pressed 5, stop
	else if(t3==0 && t2==1 && t1==0 && t0==1){
		Stop();
	}
	delay(10);
}

// Define the pins for the ultrasonic sensor
#define trigPin 11
#define echoPin 12

//motor pins 
#define ENA 10
#define ENB 5

//set up pins
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

int i = 1;


//line sensor pins + variables 
#define lineRightPin A3
#define lineLeftPin A2
int lineSensorRight = 900;
int lineSensorLeft = 900;

void setup() {
  // put your setup code here, to run once:
  // Initialize serial communication
  //connects bot to serial monitor on laptop
  Serial.begin(9600);

  // Set the trigger pin as an output
  pinMode(trigPin, OUTPUT);

  // Set the echo pin as an input
  pinMode(echoPin, INPUT);

  //setting up the pins to be output
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //makes motors outputs
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  analogWrite(IN1,LOW);
  analogWrite(IN2,HIGH);
  analogWrite(IN3,LOW);
  analogWrite(IN4,HIGH);

  // line sensor setup
  pinMode(lineRightPin, INPUT);
  pinMode(lineLeftPin, INPUT);

  //start motions
  delay(3350);
  
  // forward(80,255);
  // delay(400);
  // forward(255,0);
  // delay(400);
  forward(255,80);
  delay(300);
  
}

void loop() {

  /*
  //start motions
  if (i == 1){//5 second stop
    delay(3500);
    i++;
  }
  else if (i == 2){//wing drop
    forward(0,255);
    delay(400);
    forward(255,0);
    delay(400);
    i++;
  }
  */
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Send a pulse to the eyes 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration of the pulse
  float distance = duration * 0.034 / 2;

  //Print the distance to the serial monitor
//  Serial.print("Distance: "); 
//  Serial.print(distance); 
//  Serial.println(" cm"); 

  if(distance < 15){
    forward(255,255);
  } else if(distance < 40 && distance > 15) {
    forward(200,200);
  } else if(distance > 40){
    forward(0,255);
  }

  //line sensor code
  lineSensorRight = analogRead(lineRightPin);
  lineSensorLeft = analogRead(lineLeftPin);
  //left-sensor
  if(lineSensorLeft <= 300 && lineSensorRight >= 300){
    backward(90,255);
    delay(750);
  } else if (lineSensorLeft>=300 && lineSensorRight<=300){ //right-sensor
    backward(255,90);
    delay(750);
  } 
  
  if (lineSensorLeft<=300 && lineSensorRight<=300){ //both sensors
    backward(255,255);
    delay(500);
  }
}

//changes direction of bot to move forwards at a given speeed
void forward(int rightW, int leftW){
  //delay(2000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, rightW);
  analogWrite(ENB, leftW);
}

//changes direction of bot to move backwards at a given speed
void backward(int rightW, int leftW){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, rightW);
    analogWrite(ENB, leftW);
}

void stopBot(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
/*
  //turns bot a sharp right
  void turnRightS(int speed){
    analogWrite(ENA, 0);
    analogWrite(ENB, speed);
  }
  
  //turns bot a sharp left
  void turnLeftS(int speed){
    analogWrite(ENA, speed);
    analogWrite(ENB, 0);
  }
  
  //turns bot a soft right
  void turnRightST(){
    analogWrite(ENA, 50);
    analogWrite(ENB, 130);
  }
  
  //turns bot a soft left
  void turnLeftST(){
    analogWrite(ENA, 130);
    analogWrite(ENB, 50);
  }

  //line sensor code
  lineSensorRight = analogRead(lineRightPin);
  lineSensorLeft = analogRead(lineLeftPin);
  prints to serial monitor 
  Serial.println("LightL: "); 
  Serial.print(lineSensorLeft); 
  Serial.println("LightL: "); 
  Serial.print(lineSensorRight); 
  if(lineSensorLeft <= 300 || lineSensorRight <= 300){
    backward(140, 140); 
    delay(325);
    forward(0, 170);
    delay(400);
    stopBot();
  }

  //quick rotate (aka opposite direction)
  void rotate(int rightW, int leftW){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, rightW);
    analogWrite(ENB, leftW);
  }
*/
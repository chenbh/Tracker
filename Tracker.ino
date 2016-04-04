// L1     L2        R1        R2        Ation
// --------------------------------------------
// 1    0        1        0        Move forward
// 0    1        0        1        Move backward
// 0    1        1        0        Move left
// 1    0        0        1        Move right
// 0    0        0        0        Stop

int leftMotor1  = 3;
int leftMotor2  = 2;
int rightMotor1 = 5;
int rightMotor2 = 4;


//  Up [0]   Down [1]   Left [2]   Right [3]   Middle [4]
// ----------------------------------------------------------
//    5        6         7           8            9

int echoPin [] = {5, 6, 7, 8, 9};
int trigPin = 10;

int distance [5];

int LED1 = 13;

boolean tracking = false;

void setup() 
{
  //  Serial.begin(9600);
  //  Serial.println("Setting up ...");

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  pinMode (trigPin, OUTPUT);
  for (int i = 0; i < 5; i ++)
  {
    pinMode (echoPin [i], INPUT);
  }
  
  pinMode (LED1, OUTPUT);

  setMotors (0, 0, 0, 0);
}

void setMotors(int left1, int left2, int right1, int right2) 
{
  digitalWrite(leftMotor1, left1 == 1?HIGH:LOW);
  digitalWrite(leftMotor2, left2 == 1?HIGH:LOW);
  digitalWrite(rightMotor1, right1 == 1?HIGH:LOW);
  digitalWrite(rightMotor2, right2 == 1?HIGH:LOW);
}

void readSensors() 
{
  for (int i = 0; i < 5; i ++)
  {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    distance [i] = pulseIn(echoPin [i], HIGH) / 58.2;
  }
}

// Main loop.
void loop() 
{
  readSensors();
  tracking = distance [4]<= 30?true:false;
  digitalWrite (LED1, tracking?HIGH:LOW);

//   for (int i = 0; i < 5; i ++)
//   {
//    Serial.print(distance [i]);
//    Serial.print(" cm ");
//   }
  if (distance [4] >= 38 && distance [4] <= 50) // move up
  {
    setMotors (1, 0, 1, 0);
  }
  else if (distance [4] >= 10 && distance [4] <= 33) // move back
  {
    setMotors (0, 1, 0, 1);
  }
  if (distance [4] < 10 || distance [4] > 50) // out of range
  {
    if (distance [2] >= 10 && distance [2] <= 50) // left
    {
      setMotors (0, 1, 1, 0);
    }
    else if (distance [3] >= 10 && distance [3] <= 50) // right
    {
      setMotors (1, 0, 0, 1);
    }
    else // rotate right
      setMotors (1, 0, 0, 1);
  }
  //  Serial.println ();
  delay(50);
}

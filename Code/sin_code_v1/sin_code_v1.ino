float prevAngle = 0;
float Angle;
float difAngle = 0;
int steps;
const float motorAcc = 1.8;
int Delay = 10; 

#define STEP_PIN 4
#define DIR_PIN 2

bool dirHigh;

void setup()
{
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  dirHigh = true;
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}

void loop()
{
  Angle = ( 180 * (sin (2 * millis())) + 180);
  //Angle = abs( 180 * (sin (0.001 * millis())));
  difAngle = Angle - prevAngle;
  prevAngle = Angle;
  steps = difAngle / motorAcc;
  Serial.println(steps);

  if (steps > 0) {
    dirHigh = true;
    digitalWrite(DIR_PIN, HIGH);
    for(int i = 0; i < abs(difAngle); i++){
      digitalWrite(STEP_PIN, HIGH);
      delay(Delay);
      digitalWrite(STEP_PIN, LOW);
      delay(Delay);
    }
  }

    else if (steps < 0) {
      dirHigh = false;
      digitalWrite(DIR_PIN, LOW);
      for(int i = 0; i < abs(difAngle); i++){
        digitalWrite(STEP_PIN, HIGH);
        delay(Delay);
        digitalWrite(STEP_PIN, LOW);
        delay(Delay);
    }
  }
}

//ORIGINAL CODE FOR REFERENCE
//void loop()
//{
//  // Toggle the DIR pin to change direction.
//  if(dirHigh)
//  {
//    dirHigh = false;
//    digitalWrite(DIR_PIN, LOW);
//  }
//  else
//  {
//    dirHigh = true;
//    digitalWrite(DIR_PIN, HIGH);
//  }
//
//  // Step the motor 50 times before changing direction again.
//  for(int i = 0; i < 100; i++)
//  {
//    // Trigger the motor to take one step.
//    digitalWrite(STEP_PIN, HIGH);
//    delay(1);
//    digitalWrite(STEP_PIN, LOW);
//    delay(1);
//  }
//}

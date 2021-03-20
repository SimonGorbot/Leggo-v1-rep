float prevAngle = 0;
float Angle;
float difAngle = 0;
int steps = 1;
const float motorAcc = 1.8;
int Delay = 1;

#define STEP_PIN 4
#define DIR_PIN 2

void setup()
{
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}

void loop()
{
  Angle = ( 180 * (sin (0.01 * millis())) + 180);
  difAngle = Angle - prevAngle;

  Serial.print(Angle);  Serial.print(" | "); 
  Serial.print(prevAngle);  Serial.print(" | ");  
  Serial.print(difAngle);  Serial.print(" | ");  
  Serial.println(steps);
  
  if (difAngle > (steps * motorAcc)) {
    digitalWrite(DIR_PIN, HIGH);
    for(int i = 0; i < steps; i++){
      digitalWrite(STEP_PIN, HIGH);
      delay(Delay);
      digitalWrite(STEP_PIN, LOW);
      delay(Delay);
    }
    prevAngle = Angle;
  }

    else if (difAngle < -(steps * motorAcc)) {
      digitalWrite(DIR_PIN, LOW);
      for(int i = 0; i < steps; i++){
        digitalWrite(STEP_PIN, HIGH);
        delay(Delay);
        digitalWrite(STEP_PIN, LOW);
        delay(Delay);
    }
      prevAngle = Angle;
  }
}

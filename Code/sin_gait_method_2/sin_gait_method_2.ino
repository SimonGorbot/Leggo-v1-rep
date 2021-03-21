float prevAngle = 0;
float Angle;
int steps;
int stepsDir; 
int stepsFinal;
const float motorAcc = 1.8;
int Delay = 1;

#define difAngle (Angle - prevAngle)
#define difAngleAlt (prevAngle - Angle)
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

int calculate_steps(float x, float y)
{
  float steps1 = x / motorAcc;
  float steps2 = y / motorAcc;
  steps = min(abs(steps1), abs(steps2));
 
  if (steps == abs(steps1)){
    stepsDir = -1+2*(steps1>0);
  }
  else if (steps == abs(steps2)){
    stepsDir = -1+2*(steps2>0);
  }

  stepsFinal = steps * stepsDir;
  return stepsFinal;
}

void loop()
{
  Angle = ( 180 * (sin (0.01 * millis())) + 180);

  Serial.print(Angle);  Serial.print(" | "); 
  Serial.print(prevAngle);  Serial.print(" | ");  
  Serial.print(difAngle);  Serial.print(" | ");  
  Serial.println(steps);
  
  if (difAngle > motorAcc) {
    steps = abs(difAngle / motorAcc);
    digitalWrite(DIR_PIN, HIGH);
    for(int i = 0; i < steps; i++){
      digitalWrite(STEP_PIN, HIGH);
      delay(Delay);
      digitalWrite(STEP_PIN, LOW);
      delay(Delay);
    }
    prevAngle = Angle;
  }

    else if (difAngle < -motorAcc) {
      steps = abs(difAngle / motorAcc);
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

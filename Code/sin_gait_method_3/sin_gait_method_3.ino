long prevAngle = 0;
long angle;
int steps;
int stepsDir; 
int stepsFinal;
int Delay = 1;
const float motorAcc = 0.9;

#define difAngle (angle - prevAngle)
#define STEP_PIN 4
#define DIR_PIN 2

void setup()
{
  Serial.begin(57600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
    
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}

void calculate_steps(float x)
{
  if (fabs(x) < 180){
    steps = fabs(x) / motorAcc;
    stepsDir = (x>0);
  }
  else {
    steps = (360 - fabs(x)) / motorAcc;
    stepsDir = (x<0);
  }

  Serial.print(x);  Serial.print(" | "); 
  Serial.print(steps);  Serial.print(" | ");
  Serial.print(stepsDir);  Serial.println();  
}

void loop()
{
  angle = ( 180 * (sin (0.01 * millis())) + 180);
  calculate_steps(difAngle);
  
  Serial.print(angle);  Serial.print(" | "); 
  
  digitalWrite(DIR_PIN, stepsDir);
  for(int i = 0; i < steps; i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(Delay);
    digitalWrite(STEP_PIN, LOW);
    delay(Delay);
    prevAngle = angle;
  }
}

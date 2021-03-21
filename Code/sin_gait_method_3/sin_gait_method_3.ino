float prevAngle = 0;
float angle;
int steps;
int stepsDir; 
int stepsFinal;
const float motorAcc = 1.8;
int Delay = 1;

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
  if (abs(x) < 180){
    steps = abs(x) / motorAcc;
    stepsDir = (x>0);
  }
  else {
    steps = (360 - abs(x)) / motorAcc;
    stepsDir = (x<0);
  }

  Serial.print(x);  Serial.print(" | "); 
  Serial.print(steps);  Serial.print(" | ");
  Serial.print(stepsDir);  Serial.println();  
}

void loop()
{
  angle = ( 90 * (sin (0.001 * millis())) + 90);
  calculate_steps(difAngle);
  
  Serial.print(angle);  Serial.print(" | "); 
//  Serial.print(prevAngle);  Serial.print(" | ");  
//  Serial.println(steps);
  
  digitalWrite(DIR_PIN, stepsDir);
  for(int i = 0; i < steps; i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(Delay);
    digitalWrite(STEP_PIN, LOW);
    delay(Delay);
    prevAngle = angle;
  Serial.print(".");  Serial.print(" | ");
  }
}

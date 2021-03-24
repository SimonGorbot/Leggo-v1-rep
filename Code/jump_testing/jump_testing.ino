//jump program testing a.k.a I am bored and gave up on debugging for today

float prevAngle = 0;
float angle;
int steps;
int stepsDir; 
int stepsFinal;
const float motorAcc = 0.9;
int Delay = 1;

#define difAngle (angle - prevAngle)
#define STEP_PIN 4
#define DIR_PIN 2

void setup() {
  Serial.begin(57600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);  
  
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}

void jump() {
  digitalWrite(DIR_PIN, LOW);
  stepsDir = 1;
  for(int i = 0; i < 20; i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(20);
    digitalWrite(STEP_PIN, LOW);
    delay(20);
  Serial.print(stepsDir);  Serial.println();  
    }
   
   digitalWrite(DIR_PIN, HIGH);
   stepsDir = 5;
   for(int i = 0; i < 100; i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(Delay);
    digitalWrite(STEP_PIN, LOW);
    delay(Delay);
  Serial.print(stepsDir);  Serial.println();  
    }
}

void loop()
{
jump();
}

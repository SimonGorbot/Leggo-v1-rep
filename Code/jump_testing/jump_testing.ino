//jump program testing a.k.a I am bored and gave up on debugging for today

float prevAngle = 0;
float angle;
int steps;
int stepsDir; 
int stepsFinal;
const float motorAcc = 0.9;
int Delay = 1;

#define STEP_PINa 4
#define DIR_PINa 2
#define STEP_PINb 5
#define DIR_PINb 3

void setup() {
  Serial.begin(57600);
  pinMode(DIR_PINa, OUTPUT);
  pinMode(STEP_PINa, OUTPUT);
  pinMode(DIR_PINb, OUTPUT);
  pinMode(STEP_PINb, OUTPUT);  
  
  digitalWrite(DIR_PINa, HIGH);
  digitalWrite(STEP_PINa, LOW);
  digitalWrite(DIR_PINb, HIGH);
  digitalWrite(STEP_PINb, LOW);

  while (!Serial.available()){}
}

void jump() {
  digitalWrite(DIR_PINa, LOW);
  digitalWrite(DIR_PINb, HIGH);

  stepsDir = 1;
  for(int i = 0; i < 45; i++){
    digitalWrite(STEP_PINa, HIGH);
    digitalWrite(STEP_PINb, HIGH);
    delay(20);
    digitalWrite(STEP_PINa, LOW);
    digitalWrite(STEP_PINb, LOW);
    delay(20);
    }
   
   digitalWrite(DIR_PINa, HIGH);
   digitalWrite(DIR_PINb, LOW);

   stepsDir = 5;
   for(int i = 0; i < 100; i++){
    digitalWrite(STEP_PINa, HIGH);
    digitalWrite(STEP_PINb, HIGH);
    delay(Delay);
    digitalWrite(STEP_PINa, LOW);
    digitalWrite(STEP_PINb, LOW);
    delay(Delay);
    }
}

void loop()
{
jump();
}

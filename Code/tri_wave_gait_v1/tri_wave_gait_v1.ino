int x = 1;
int y = 0;
int Max = 90;
int Min = 0;
int steps;
int stepsDir; 
int stepsFinal;
const float motorAcc = 0.9;
int Delay = 1;

#define steps (abs(x) / motorAcc)
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


void loop()
{
  digitalWrite(DIR_PIN, (x > 0));
  for(int i = 0; i < ((abs(x) / motorAcc) * 1.1); i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(Delay);
    digitalWrite(STEP_PIN, LOW);
    delay(Delay);
  //Serial.print(steps);  Serial.print(" | "); Serial.print(x); Serial.print(" | "); Serial.println(y);
    y += x;
    Serial.println(y);
    if (y >= Max) {
      x = -x;
      Serial.println("y");
    }
    else if (y <= Min) {
      x = -x;
      Serial.println("x");
    }
  }
}

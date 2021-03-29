#define STEP_PINa 4
#define DIR_PINa 2
#define STEP_PINb 5
#define DIR_PINb 3

bool dirHigh;

void setup()
{  
  Serial.begin(57600);
  //left motor
  dirHigh = true;
  pinMode(DIR_PINa, OUTPUT);
  pinMode(STEP_PINa, OUTPUT);
  digitalWrite(DIR_PINa, HIGH);
  digitalWrite(STEP_PINa, LOW);


  //right motor
  pinMode(DIR_PINb, OUTPUT);
  pinMode(STEP_PINb, OUTPUT);
  digitalWrite(DIR_PINb, HIGH);
  digitalWrite(STEP_PINb, LOW);

}

void loop()
{
  // Toggle the DIR pin to change direction.
  if(dirHigh)
  {
    dirHigh = false;
    digitalWrite(DIR_PINa, LOW);
    digitalWrite(DIR_PINb, HIGH);
  }
  else
  {
    dirHigh = true;
    digitalWrite(DIR_PINa, HIGH);
    digitalWrite(DIR_PINb, LOW  );
  }

  // Step the motor 50 times before changing direction again.
  for(int i = 0; i < (90 * 1.1); i++)
  {
    digitalWrite(STEP_PINa, HIGH);
    digitalWrite(STEP_PINb, HIGH);
    delay(1);
    digitalWrite(STEP_PINa, LOW);
    digitalWrite(STEP_PINb, LOW);
    delay(1);
  }
}

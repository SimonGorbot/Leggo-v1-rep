/* Simple step test for Pololu stepper motor driver carriers
This code can be used with the A4988, DRV8825, DRV8824, and
DRV8834 Pololu stepper motor driver carriers.  It sends a pulse
every 500 ms to the STEP pin of a stepper motor driver that is
connected to pin 2 and changes the direction of the stepper motor
every 50 steps by toggling pin 3. */

#define STEP_PIN 4
#define DIR_PIN 2

bool dirHigh;

void setup()
{
  dirHigh = true;
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void loop()
{
  // Toggle the DIR pin to change direction.
  if(dirHigh)
  {
    dirHigh = false;
    digitalWrite(DIR_PIN, LOW);
  }
  else
  {
    dirHigh = true;
    digitalWrite(DIR_PIN, HIGH);
  }

  // Step the motor 50 times before changing direction again.
  for(int i = 0; i < 100; i++)
  {
    // Trigger the motor to take one step.
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(1);
  }
}

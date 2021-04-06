#define motorAcc 0.9
#define num_points 6
#define STEP_PIN 4
#define DIR_PIN 2

long motor1_angle[num_points] = {0, 60, 30, 90, 30, 0};
long motor1_time[num_points] = {0, 2000, 4000, 6000, 8000, 10000};

long timeCurrent;
long timePrevious;
long number_cycles = 0;
int steps;
int stepsDir;
int i = 0;

#define cycle_time (number_cycles * motor1_time[num_points - 1])

void setup() {
  Serial.begin(57600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
    
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
  Serial.println("ENTER KEY TO START");
}

float calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  stepsDir = (angle > 0);
  steps = abs(angle / motorAcc);
  Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

void move_motor(int dir,float stp){
  digitalWrite(DIR_PIN, stepsDir);
  for(int i = 0; i < (int)stp; i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(1);
  }
}

void loop() {
  float time1A = motor1_time[i];
  float time1B = motor1_time[i+1];
  float angle1A = motor1_angle[i];
  float angle1B = motor1_angle[i+1];
  float slope1 = ((angle1B - angle1A) / (time1B - time1A));
  //Serial.print(time1A); Serial.print(" | "); Serial.print(angle1A); Serial.print(" | "); Serial.println(slope1);

  while ((time1B - timeCurrent) >= 0){
    timeCurrent = millis() - cycle_time;
    calculate_angle(slope1, timeCurrent, timePrevious);
    if (steps > 0){
      move_motor(stepsDir, steps);
      timePrevious = timeCurrent;
    }
  }

  i++;
  if (i == 5){
    i = 0;
    timeCurrent = 0;
    timePrevious = 0;
    number_cycles += 1;
  }
}

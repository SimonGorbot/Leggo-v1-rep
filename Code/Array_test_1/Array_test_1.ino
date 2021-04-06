#define motorAcc 0.9
#define num_points 17
#define STEP_PIN1 4
#define DIR_PIN1 2
#define STEP_PIN2 5
#define DIR_PIN2 3

int motor1_angle[num_points] = {49,52,54,57,73,83,87,89,90,85,70,57,40,32,35,43,49};
long motor1_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
int motor2_angle[num_points] = {49,43,35,32,40,57,70,85,90,89,87,83,73,57,54,52,49};
long motor2_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};

long timeCurrent;
long timePrevious1;
long timePrevious2;
long number_cycles = 0;
int steps;
int stepsDir;
int i = 0;

#define cycle_time (number_cycles * motor1_time[num_points - 1])

float m1_calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  stepsDir = (angle < 0);
  steps = abs(angle / motorAcc);
  //Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

float m2_calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  stepsDir = (angle > 0);
  steps = abs(angle / motorAcc);
  //Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

void m1_move_motor(int dir,float stp){
  digitalWrite(DIR_PIN1, dir);
  for(int i = 0; i < (int)stp; i++){
    digitalWrite(STEP_PIN1, HIGH);
    delay(1);
    digitalWrite(STEP_PIN1, LOW);
    delay(1);
  }
}

void m2_move_motor(int dir,float stp){
  digitalWrite(DIR_PIN2, dir);
  for(int i = 0; i < (int)stp; i++){
    digitalWrite(STEP_PIN2, HIGH);
    delay(1);
    digitalWrite(STEP_PIN2, LOW);
    delay(1);
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(STEP_PIN1, OUTPUT);
  pinMode(DIR_PIN2, OUTPUT);
  pinMode(STEP_PIN2, OUTPUT);
    
  digitalWrite(DIR_PIN1, HIGH);
  digitalWrite(STEP_PIN1, LOW);
  digitalWrite(DIR_PIN2, HIGH);
  digitalWrite(STEP_PIN2, LOW);
  //Serial.println("ENTER KEY TO START");
  m1_move_motor((motor1_angle[0] < 0), (motor1_angle[0]/motorAcc));
  m2_move_motor((motor2_angle[0] > 0), (motor2_angle[0]/motorAcc));
  delay(3000);
}

void loop() {
  float time1A = motor1_time[i];
  float time1B = motor1_time[i+1];
  float angle1A = motor1_angle[i];
  float angle1B = motor1_angle[i+1];
  float slope1 = ((angle1B - angle1A) / (time1B - time1A));
  //second motor set//
  float time2A = motor2_time[i];
  float time2B = motor2_time[i+1];
  float angle2A = motor2_angle[i];
  float angle2B = motor2_angle[i+1];
  float slope2 = ((angle2B - angle2A) / (time2B - time2A));
//  Serial.print(time1A); Serial.print(" | "); Serial.print(angle1A); Serial.print(" | "); Serial.println(slope1);
//  Serial.print(time2A); Serial.print(" | "); Serial.print(angle2A); Serial.print(" | "); Serial.println(slope2);


  while ((time1B - timeCurrent) >= 0){
    timeCurrent = millis() - cycle_time;
    m1_calculate_angle(slope1, timeCurrent, timePrevious1);
    if (steps > 0){
      m1_move_motor(stepsDir, steps);
      timePrevious1 = timeCurrent;
    }
    m2_calculate_angle(slope2, timeCurrent, timePrevious2);
    if (steps > 0){
      m2_move_motor(stepsDir, steps);
      timePrevious2 = timeCurrent;
      Serial.println(steps);
    }
  }

  i++;
  if (i == 5){
    i = 0;
    timeCurrent = 0;
    timePrevious1 = 0; timePrevious2 = 0;
    number_cycles += 1;
  }
}
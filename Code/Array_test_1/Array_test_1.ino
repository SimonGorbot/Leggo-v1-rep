#define motorAcc 0.9
#define num_points 17
#define 1STEP_PIN 4
#define 1DIR_PIN 2
#define 2STEP_PIN 5
#define 2DIR_PIN 3

int motor1_angle[num_points] = {49,52,54,57,73,83,87,89,90,85,70,57,40,32,35,43,49};
int motor1_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
int motor2_angle[num_points] = {49,43,35,32,40,57,70,85,90,89,87,83,73,57,54,52,49}
int motor2_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};

long timeCurrent;
long timePrevious;
int number_cycles = 0;
int steps;
int stepsDir;
int i = 0;

#define cycle_time (number_cycles * motor1_time[num_points - 1])

void setup() {
  Serial.begin(57600);
  pinMode(1DIR_PIN, OUTPUT);
  pinMode(1STEP_PIN, OUTPUT);
  pinMode(2DIR_PIN, OUTPUT);
  pinMode(2STEP_PIN, OUTPUT);
    
  digitalWrite(1DIR_PIN, HIGH);
  digitalWrite(1STEP_PIN, LOW);
  digitalWrite(2DIR_PIN, HIGH);
  digitalWrite(2STEP_PIN, LOW);
  //Serial.println("ENTER KEY TO START");
}

float m1_calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  stepsDir = (angle > 0);
  steps = abs(angle / motorAcc);
  Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

float m2_calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  stepsDir = (angle < 0);
  steps = abs(angle / motorAcc);
  Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

void m1_move_motor(int dir,float stp){
  digitalWrite(1DIR_PIN, stepsDir);
  for(int i = 0; i < (int)stp; i++){
    digitalWrite(1STEP_PIN, HIGH);
    delay(1);
    digitalWrite(1STEP_PIN, LOW);
    delay(1);
  }
}

void m2_move_motor(int dir,float stp){
  digitalWrite(2DIR_PIN, stepsDir);
  for(int i = 0; i < (int)stp; i++){
    digitalWrite(2STEP_PIN, HIGH);
    delay(1);
    digitalWrite(2STEP_PIN, LOW);
    delay(1);
  }
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
  //Serial.print(time1A); Serial.print(" | "); Serial.print(angle1A); Serial.print(" | "); Serial.println(slope1);

  while ((time1B - timeCurrent) >= 0){
    timeCurrent = millis() - cycle_time;
    m1_calculate_angle(slope1, timeCurrent, timePrevious);
    if (steps > 0){
      m1_move_motor(stepsDir, steps);
      timePrevious = timeCurrent;
    }
    m2_calculate_angle(slope2, timeCurrent, timePrevious);
    if (steps > 0){
      m2_move_motor(stepsDir, steps);
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

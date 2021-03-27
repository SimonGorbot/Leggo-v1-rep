int motor1_angles[] = {};
int motor1_times[] = {};

int time1A;
int angle1A;
int time1B;
int angle1B;
int timeCurrent;
int timeSegment;
int timePrevious;
int i = 0;

#define motorAcc 0.9
#define slope ((angleB - angleA) / (timeB - timeA))
#define STEP_PIN 4
#define DIR_PIN 2

void setup() {
  Serial.begin(57600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
    
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(STEP_PIN, LOW);
}

void calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
  int stepsDir = (angle > 0);
  int steps = angle / motorAcc;
}

void move_motor(int dir,float stp){
  digitalWrite(DIR_PIN, stepsDir);
  for(int i = 0; i < (int)abs(stp); i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(1);
}

void loop() {
  time1A = motor1_time[i];
  time1B = motor1_time[i+1];
  angle1A = motor1_angle[i];
  angle1B = motor1_angle[i+1];

  while ((timeB - timeCurrent) >= 0){
    timeCurrent = millis();
    calculate_angle(slope, timeCurrent, timePrevious);
    move_motor(stepDir, steps);
    timePrevious = timeCurrent;
  }
  
  i++;
  if (i == final time){
    i = 0; 
  }
}

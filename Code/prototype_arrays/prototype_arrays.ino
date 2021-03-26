int timeA;
int angleA;
int timeB;
int angleB;
int timeCurrent;
int timeSegment;
int timePrevious;
bool dirHigh;

#define slope ((angleB - angleA) / (timeB - timeA))

void setup() {
  Serial.begin(57600);
}

void calculate_angle(float m,int t,int tp){
  float angle = m * (t - tp);
}

void move_motor(int dir,float stp){
  dirHigh = dir;
  digitalWrite(DIR_PIN, dir);
  for(int i = 0; i < abs(stp); i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(1);
}

void loop() {
  timeA = __;
  timeB = __;
  angleA = __;
  angleB = __;

  while ((timeB - timeCurrent) >= 0){
    timeCurrent = millis();
    calculate_angle(slope, timeCurrent, timePrevious);
    timePrevious = timeCurrent;
    
  }
  
}

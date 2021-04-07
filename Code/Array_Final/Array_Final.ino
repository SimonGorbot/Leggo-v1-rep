#define motorAcc 0.9    //motor accuracy of the motor (full step = 1.8, 1/2 step = 0.9)
#define num_points 17   //number of cords for leg tip
#define STEP_PIN1 4
#define DIR_PIN1 2
#define STEP_PIN2 5
#define DIR_PIN2 3

//int motor1_angle[num_points] = {49,52,54,57,73,83,87,89,90,85,70,57,40,32,35,43,49}; //28 offset
int motor1_angle[num_points] = {38,42,45,48,62,68,67,62,60,58,49,40,26,20,23,31,38}; //26 offset
long int motor1_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
//long int motor1_time[num_points] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000};
//int motor2_angle[num_points] = {49,43,35,32,40,57,70,85,90,89,87,83,73,57,54,52,49}; //28 offset
int motor2_angle[num_points] = {38,31,23,20,26,40,49,58,60,62,67,68,62,48,45,42,38}; //26 offset;
long int motor2_time[num_points] = {0, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000, 3200};
//long int motor2_time[num_points] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000};
//the arrays calculated using a combination of trig. and ik. that can be found in the Google Sheet --> https://docs.google.com/spreadsheets/d/1tOTrF-Jd6Reod60cDrReuFHqYUPKIEgyeVbVYCuEUuk/edit?usp=sharing

long timeCurrent;
long timeStart;
long timePrevious1;
long timePrevious2;
long number_cycles = 0;   //keeps track of full array loops
int steps;
int stepsDir;
int i = 0;
int wait = 20;    //delay in milliseconds
float angle;
float slope1;
float slope2;

#define cycle_time (number_cycles * motor1_time[num_points - 1])    //cumulative time taken to complete cycles

float m1_calculate_angle(float m,int t,int tp){
  angle = abs(m * (t - tp));
  stepsDir = (slope1 < 0);
  steps = abs(angle / motorAcc); 
  //Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

float m2_calculate_angle(float m,int t,int tp){
  angle = abs(m * (t - tp));
  stepsDir = (slope2 > 0);
  steps = abs(angle / motorAcc);
  //Serial.print(angle); Serial.print(" | "); Serial.print(steps); Serial.print(" | "); Serial.println(stepsDir);
}

void m1_move_motor(int dir,float stp){
  digitalWrite(DIR_PIN1, dir);
  delay(wait);
  for(int k = 0; k < (int)stp; k++){
    digitalWrite(STEP_PIN1, HIGH);
    delay(1);
    digitalWrite(STEP_PIN1, LOW);
    delay(1);
  }
}

void m2_move_motor(int dir,float stp){
  digitalWrite(DIR_PIN2, dir);
  delay(wait);
  for(int k = 0; k < (int)stp; k++){
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
  m1_move_motor((motor1_angle[0] < 0), (motor1_angle[0]/motorAcc));   //assumes set position (home state) before starting loop
  m2_move_motor((motor2_angle[0] > 0), (motor2_angle[0]/motorAcc));
  delay(2000);                                                        //2 second delay before walk gait starts
  timeStart = millis();
  timeCurrent = 0;
  timePrevious1 = 0;
  timePrevious2 = 0;
}

void loop() {
  float time1A = motor1_time[i];
  float time1B = motor1_time[i+1];
  float angle1A = motor1_angle[i];
  float angle1B = motor1_angle[i+1];
  slope1 = ((angle1B - angle1A) / (time1B - time1A));
  //second motor set//
  float time2A = motor2_time[i];
  float time2B = motor2_time[i+1];
  float angle2A = motor2_angle[i];
  float angle2B = motor2_angle[i+1];
  slope2 = ((angle2B - angle2A) / (time2B - time2A));
//  Serial.print(time1A); Serial.print(" | "); Serial.print(angle1A); Serial.print(" | "); Serial.println(slope1);
//  Serial.print(time2A); Serial.print(" | "); Serial.print(angle2A); Serial.print(" | "); Serial.println(slope2);

  Serial.print("New segment: i="); Serial.println(i);
  Serial.print("tC="); Serial.println(timeCurrent);
  
  while ((time1B - timeCurrent) >= 0){
    timeCurrent = millis() - cycle_time - timeStart;
    m1_calculate_angle(slope1, timeCurrent, timePrevious1);
    if (steps > 0){
      m1_move_motor(stepsDir, steps);
      timePrevious1 = timeCurrent - ((angle - (steps * motorAcc))/ abs(slope1));
//      Serial.print("ONE\t"); 
//      Serial.print(timeCurrent); Serial.print(" | "); 
//      Serial.print(time1B); Serial.print(" | "); 
//      Serial.print(slope1,4); Serial.print(" | "); 
//      Serial.print(angle,4); Serial.print(" | "); 
//      Serial.print(steps*motorAcc); Serial.print(" | ");
//      Serial.print(timePrevious1); Serial.print(" | ");
//      Serial.println();
    }
    m2_calculate_angle(slope2, timeCurrent, timePrevious2);
    if (steps > 0){
      m2_move_motor(stepsDir, steps);
      timePrevious2 = timeCurrent - ((angle - (steps * motorAcc))/ abs(slope2));
      //Serial.print("TWO\t"); Serial.print(timeCurrent); Serial.print(" | "); Serial.print(timePrevious2); Serial.print(" | "); Serial.println(slope2);
    }
  }

  i++;
  if (i == (num_points-1)){
    i = 0;
    timeCurrent = 0;
    timePrevious1 = 0; timePrevious2 = 0;
    number_cycles += 1;
  }
}

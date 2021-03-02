float prevAngle = 0;
float Angle;
float difAngle = 0;
float steps;
const float motorAcc = 1.8;                           //1.8 is the step degree accuracy of the motor

void setup()
{
 Serial.begin(9600);
}

void loop()
{
  Angle = (180 * (sin((0.001) * millis())) + 180);
  difAngle = Angle - prevAngle;
  prevAngle = Angle;
  Serial.println(Angle);
  
//  if (difAngle > 0) {                                 //turn clock wise
//    steps = difAngle / motorAcc
//    //write step number with direction to motor driver                       
//  }
//  else {                                              //turn counter clock wise
//    steps = difAngle / motorAcc
//    //write step number with opposite direction to motor driver
//  }
}

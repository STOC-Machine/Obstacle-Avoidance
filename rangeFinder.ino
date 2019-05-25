/**
 * Obstacle Avoidance for Drones Operating Inside Buildings
 * ------------------- 
 *
 * Simple obstacle avoidance program using ultrasonic sensors for drones
 * operating inside a building. 
 * 
 * WARNING: The unit of distance used is in (cm).
 * 
 * 2019 St.Olaf-Carleton Enginnering Team
 * @author: 
 * @hardware:
 */

const unsigned int TRIG_PIN=13;
const unsigned int ECHO_PIN=12;
const unsigned int BAUD_RATE=9600;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  int range = rangeFinder();
  Serial.print(range);
  Serial.println("cm");
  Serial.print(multiObjectDetection(range));
 }

/**
 * Activates the ultrasonic sensor.
 */
int activateUltrasonicSensor(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  }

 bool simpleObjectDetection(int distance){
 if(distance<=30){  //set the distance to flag an object to 60 cm
   Serial.println("true");
   return true;
   } 
  else{
    Serial.println("false");
    return false;
  }
 }

 int multiObjectDetection(int distance){
 if(distance<=30){  //set the distance to flag an object to 60 cm
   Serial.println("HAULT!");
   // return 0;
   } 
 else if(distance>30 && distance<=60){  //set the distance to flag an object to 60 cm
   Serial.println("SLOW DOWN QUICKLY ");
   // return 1;
   } 
 else if(distance>60 && distance <=100){  //set the distance to flag an object to 60 cm
   Serial.println("SLOW DOWN");
   // return 2;
   } 
  else if(distance>100 && distance<=300){  //set the distance to flag an object to 60 cm
   Serial.println("KEEP GOING CAREFULLY");
   // return 3;
   } 
  else{
    Serial.println("KEEP GOING");
    // return 4;
  }
 }

int rangeFinder(){
  /**
   * Activates the ultrasonic sensor and takes 5 measurements of the distance 
   * with 10 Hertz.
   * @return Average of the 5 readings.
   */
  unsigned long sum = 0;
  for(int i = 0; i < 5; i++){
    sum += simpleRangeFinder();
    delay(100);
  }
  return round(sum/5);
  }

/**
 * Helper function for the rangeFinder(). 
 * Activates the ultrasonic sensor.
 * Returns the calculated distance to the nearest object in (cm).
 * /
 */
int simpleRangeFinder(){
  activateUltrasonicSensor();
  const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
  int distance= duration/29/2; 
  return distance;
}

#include <Arduino.h>

#define safe_min_start_speed 125
#define safe_min_run_speed 65
#define speed_resolution 4

//Button definitions
int button_pin = 13;
int button_state = 0;

//Pot Meter definitions
int pot_meter_pin = A0;
int pot_meter_value = 0;

//IC digital pin definitions
int ic_pin_1 = 10;
int ic_pin_2 = 11;

//IC PWM definitions
int ic_pwm_pin = 9;

boolean direction = false;
boolean hasStopped = true;

int speed = 0;
int last_speed = 0;

void setup() {
  //Setup button
  pinMode(button_pin, INPUT_PULLUP);

  //Setup Pot Meter
  pinMode(pot_meter_pin, INPUT);

  //Setup IC
  pinMode(ic_pin_1, OUTPUT);
  pinMode(ic_pin_2, OUTPUT);
  pinMode(ic_pwm_pin, OUTPUT);

  //Serial
  Serial.begin(9600);
}

//Method to set IC Motor control values
void setMotor(int _speed, boolean _direction) {
  //Set IC digital input (motor direction)
  digitalWrite(ic_pin_1, ! _direction);
  digitalWrite(ic_pin_2, _direction);

  //Set IC PWM input (speed)
  analogWrite(ic_pwm_pin, _speed);
  
  //Print _speed if changed from last_speed with a margin (to prevent serial spam)
  if (_speed != last_speed && abs(_speed - last_speed) > 4) {
    Serial.print("Real Speed: ");
    Serial.println(_speed);

    last_speed = _speed;
  }
}

//Lerp between two values with a given speed/amount
int lerp(int e, int t, float r) {
  return r * (t - e) + e;
}

//Toggle motor direction, by smoothly bringing the motor to a stop, and then up to speed again.
//Will also prevent motor hanging from too low voltage.
void toggleMotorDirection() {
  int currentSpeed = speed;
  boolean reachedSpeed = false;

  //only change direction if motor has stopped
  if (hasStopped) {
    Serial.println("Toggeling Motor --- Changed direction");
    direction = ! direction;
    return;
  }

  Serial.println("Toggeling Motor --- Started smoothing");

  Serial.print("Current Speed: ");
  Serial.println(currentSpeed);

  //Run loop until motor is at desired speed
  while(reachedSpeed == false) {

    //Slow motor down to 0 before speeding up to desired speed in other directions.
    if(hasStopped == false) {
      currentSpeed = lerp(currentSpeed, 0, 0.2);

      //Detect if motor has stopped, and change direction
      if(currentSpeed <= 1) {
        hasStopped = true;
        direction = !direction;
      }
    } else {
      //Gradually reach safe_min_start_speed to get the motor spinning
      currentSpeed = lerp(currentSpeed, max(safe_min_start_speed, speed), 0.2);

      //Detect if motor has reached safe_min_start_speed, and set speed to desired speed
      if(currentSpeed >= max(safe_min_start_speed, speed) - 4) {
        reachedSpeed = true;
        currentSpeed = speed;
      }
    }

    Serial.print("Current Speed: ");
    Serial.println(currentSpeed);

    //Set motor speed and direction
    setMotor(currentSpeed, direction);
    delay(10);
  }

  Serial.println("Toggeling Motor --- Ended smoothing");
}


//Read Pot Meter and set speed
void readPotMeter() {
  //Smooth pot_meter_value, so that it doesn't jump around too much
  pot_meter_value = lerp(pot_meter_value, analogRead(pot_meter_pin), 0.1);
  
  //Map pot_meter_value from 0-1023 to safe_min_run_speed to 255, to utilise the full range of the meter.
  //(no deadzones on the potmeter from force stopping the motor below safe_min_run_speed)
  speed = map(pot_meter_value, 0,  1023, safe_min_run_speed - 1, 255);

  //Print speed if changed from last speed between a margine (to prevent serial spam)
  if(speed != last_speed && abs(speed - last_speed) > 5) {
    Serial.print("Pot Speed: ");
    Serial.println(speed);
    last_speed = speed;
  }
}

//Read button state
//and toggle motor direction on button press, from low to high
void readButtonEvents() {
  if(button_state != digitalRead(button_pin)) {
    button_state = digitalRead(button_pin);

    //Toggle motor direction if button is pressed
    if(button_state) {
      toggleMotorDirection();
    }
  }
}

//Logic for running motor safely and smoothly.
// 1: Limits motor to run below safe_min_run_speed
// 2: Allows motor to climb down to safe_min_run_speed
// 3: Prevents motor from hanging from too low voltage when starting up
// 4: Sets motor speed to desired speed
void updateMotorValues() {

  //If speed is lower than safe_min_run_speed, turn motor off
  if(speed < safe_min_run_speed) {
    setMotor(0, direction);
    hasStopped = true;

    delay(100); //Wait for motor to stop
    return;
  }

  //Allow motor to reach safe_min_run_speed if speed it being rolled down
  if(last_speed > speed && hasStopped == false) {
    speed = max(safe_min_run_speed, speed);
    setMotor(speed, direction);
    hasStopped = false;
    return;
  }

  //If motor has stopped, and speed is above safe_min_run_speed, start motor from safe_min_start_speed
  if(hasStopped == true && speed > safe_min_run_speed) {
    hasStopped = false;

    speed = safe_min_start_speed;
    setMotor(speed, direction);

    delay(100); // Give the motor time to start up
    return;
  }

  //If all else fails, just set the motor speed
  setMotor(speed, direction);
}

void loop() {
  readPotMeter();
  readButtonEvents();
  updateMotorValues();
}
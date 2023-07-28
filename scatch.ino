// conf settings

const int ITERATIONS_NUMBER = 15;

// main code

unsigned long prev_time = 0;
unsigned long current_time = 0;
unsigned long one_iteration_time = 0;
double disc_period = 0;
double RPS = 0;
double angular_velocity;
double approx_vel = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, on_ir_freed, RISING);
}

void on_ir_freed() {
  current_time = millis();

  if (prev_time == 0) { // check if previous time not set
    prev_time = current_time;
    return;
  }
  one_iteration_time = current_time - prev_time; // time that makes one barrier to go throw in milliseconds

  prev_time = current_time; // setting previous time from current for next cycle

  disc_period = one_iteration_time * ITERATIONS_NUMBER; // expected period of disc rotation in milliseconds
  disc_period /= 1000; // convert to seconds

  RPS = 1 / disc_period; // RPS - Rotations Per Seconds (frequency)

  angular_velocity = 2 * 3.1415926535f * RPS; // angular velocity in radians per second
  approx_vel = ((float)((unsigned long)(approx_vel * 1000)))/1000;
  approx_vel *= .7;
  angular_velocity = ((float)((unsigned long)(angular_velocity * 1000)))/1000;
  angular_velocity *= .3;
  approx_vel += angular_velocity;
  // approx_vel = round(0.7f*approx_vel * 100)/100 + round(0.3f*angular_velocity * 100)/100;
  // approx_vel = ((float)((int)(0.3f*angular_velocity * 10000)))/10000 + ((float)((int)(0.7f*approx_vel * 10000)))/10000;

  Serial.println(approx_vel, 10);
}

void loop() {
  // TODO: WEB server
}

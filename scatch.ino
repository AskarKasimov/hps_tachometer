// conf settings

const int ITERATIONS_NUMBER = 5;

// main code

unsigned long prev_time = 0;
unsigned long current_time = 0;
unsigned long one_iteration_time = 0;
double disc_period = 0;
double RPS = 0;
double angular_velocity = 0;
double calc_coefficient = 0;
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

  RPS = 1 / disc_period; // RPS - Rotations Per Second (frequency)

  angular_velocity = 2 * 3.1415926535f * RPS; // angular velocity in radians per second

  // some calculations for alignment:

  angular_velocity = ((float)((unsigned long)(angular_velocity * 1000)))/1000;
  angular_velocity *= .3;

  calc_coefficient = ((float)((unsigned long)(approx_vel * 1000)))/1000;
  calc_coefficient *= .7;

  approx_vel = calc_coefficient + angular_velocity;

  Serial.println(approx_vel, 10);
}

void loop() {
  // TODO: WEB server for websockets and streaming HPS information to site
}

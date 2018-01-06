#include <math.h>

uint32_t time;

class OSC {
    float _frequency;
    
  public:
    void frequency (float);
    double calc(unsigned long);
};

void OSC::frequency (float f) {
  _frequency = f;
  Serial.println("frequency set ~");
}


double OSC::calc(unsigned long t) {
  return sin(t * _frequency);  
}

OSC osc;

void IRAM_ATTR onTimer() {
  time++;
}

hw_timer_t * timer = NULL;

void setup() {
  time = 0;
  Serial.begin(115200);
  
  timer = timerBegin(0, 1, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1814, true);
  timerAlarmEnable(timer);
  
  osc.frequency(440);
}



void loop() {
  Serial.print("Osc: ");
  double output = osc.calc(time);
  Serial.println(output);
  Serial.println(time);
  delay(100);
}

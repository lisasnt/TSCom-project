#if !( ARDUINO_ARCH_NRF52840 && TARGET_NAME == ARDUINO_NANO33BLE )
	#error This code is designed to run on nRF52-based Nano-33-BLE boards using mbed-RTOS platform! Please check your Tools->Board setting.
#endif
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include "TimerInterrupt_Generic.h" 

#define ULONG_MAX       4294967295UL
#define MICROS_TO_CM    58.0
#define MICROS_TO_INCH  148.0

const uint8_t trigPin = 8;
const uint8_t echoPin = 10; 
    
float distance;

volatile bool isEchoOn = false;
volatile uint32_t startTime = 0;
volatile uint32_t endTime = 0;
volatile bool isFirstToggleDone = false;

// Interval in microsecs
#define TIMER_INTERVAL_50mS         50000    
#define TIMER_INTERVAL_10uS         10

volatile uint32_t preMillisTimer0 = 0;

static bool toggle0 = true;

// Depending on the board, you can select NRF52 Hardware Timer from NRF_TIMER_1,NRF_TIMER_3,NRF_TIMER_4 (1,3 and 4)
// If you select the already-used NRF_TIMER_0 or NRF_TIMER_2, it'll be auto modified to use NRF_TIMER_1

NRF52_MBED_Timer ITimer0(NRF_TIMER_3);
NRF52_MBED_Timer ITimer1(NRF_TIMER_4);

void TimerHandler0() {
  
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  if (isFirstToggleDone && toggle0) {
    ITimer0.stopTimer();
    ITimer0.disableTimer();
    isFirstToggleDone = false;
  }
  digitalWrite(trigPin, toggle0);
  toggle0 = !toggle0;
  isFirstToggleDone = true;
} 

void TimerHandler1() {
  ITimer0.attachInterruptInterval(TIMER_INTERVAL_10uS, TimerHandler0);
}

void EchoHandler() {
  if (digitalRead(echoPin) == HIGH) {
    startTime = micros();
    isEchoOn = true;
  } else {
    endTime = micros();
    isEchoOn = false;
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(echoPin), EchoHandler, CHANGE);
  Serial.begin(9600);

  while (!Serial && millis() < 5000);
  delay(500);

  if (ITimer1.attachInterruptInterval(TIMER_INTERVAL_50mS, TimerHandler1))
    Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
}

void loop() {
  static uint32_t lastMeasuredEcho = 0;
  static uint32_t duration;

  if (!isEchoOn && startTime != 0 && endTime != 0) {
    duration = (endTime >= startTime) ? (endTime - startTime) : (ULONG_MAX - startTime + endTime);
    
    if (duration != lastMeasuredEcho) {
      lastMeasuredEcho = duration;
      distance = lastMeasuredEcho / MICROS_TO_CM; 
      Serial.println("Ultrasound distance: " + String(distance) + " cm");
    }

    startTime = 0;
    endTime = 0;
  }
  delay(100);
}
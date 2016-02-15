#include <avr/sleep.h>
#include "SleepManager.h"

int SleepInterrupt = 0;          // use interrupt 0 (pin 2) and run function
int WakePin = 2;                 // pin used for waking up
int sleepStatus = 0;             // variable to store a request for sleep

SleepManager::SleepManager()
{
  pinMode(WakePin, OUTPUT);
  digitalWrite(WakePin, LOW);
//  return;
////  //http://www.kevindarrah.com/download/arduino_code/LowPowerVideo.ino
////  //Save Power by writing all Digital IO LOW - note that pins just need to be tied one way or another, do not damage devices!
////  for (int i = 0; i <= 13; i++) {
////    //if(i != 2)//just because the button is hooked up to digital pin 2
////    pinMode(i, OUTPUT);
////    digitalWrite(i, HIGH);
////  }
//  
//  pinMode(WakePin, INPUT_PULLUP);
//
//  //Disable ADC - don't forget to flip back after waking up if using ADC in your application ADCSRA |= (1 << 7);
//  ADCSRA &= ~(1 << 7);
//
////  //ENABLE SLEEP - this enables the sleep mode
////  SMCR |= (1 << 2); //power down mode
////  SMCR |= 1;//enable sleep
//
//  /* Now it is time to enable an interrupt. In the function call 
//   * attachInterrupt(A, B, C)
//   * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
//   * 
//   * B   Name of a function you want to execute while in interrupt A.
//   *
//   * C   Trigger mode of the interrupt pin. can be:
//   *             LOW        a low level trigger
//   *             CHANGE     a change in level trigger
//   *             RISING     a rising edge of a level trigger
//   *             FALLING    a falling edge of a level trigger
//   *
//   * In all but the IDLE sleep modes only LOW can be used.
//   */
//
////  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                      // wakeUpNow when pin 2 gets LOW 
}


void wakeUpNow()
{
  // execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  // we don't really need to execute any special functions here, since we
  // just want the thing to wake up
}

void SleepManager::sleepNow()
{
  digitalWrite(WakePin, HIGH);
  // Should kill power if on battery
  delay(1000);
  digitalWrite(WakePin, LOW);
//  return;
//    /* Now is the time to set the sleep mode. In the Atmega8 datasheet
//     * http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
//     * there is a list of sleep modes which explains which clocks and 
//     * wake up sources are available in which sleep mode.
//     *
//     * In the avr/sleep.h file, the call names of these sleep modes are to be found:
//     *
//     * The 5 different modes are:
//     *     SLEEP_MODE_IDLE         -the least power savings 
//     *     SLEEP_MODE_ADC
//     *     SLEEP_MODE_PWR_SAVE
//     *     SLEEP_MODE_STANDBY
//     *     SLEEP_MODE_PWR_DOWN     -the most power savings
//     *
//     * For now, we want as much power savings as possible, so we 
//     * choose the according 
//     * sleep mode: SLEEP_MODE_PWR_DOWN
//     * 
//     */  
//    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
//
//    sleep_enable();          // enables the sleep bit in the mcucr register
//                             // so sleep is possible. just a safety pin 
//
//    /* Now it is time to enable an interrupt. We do it here so an 
//     * accidentally pushed interrupt button doesn't interrupt 
//     * our running program. if you want to be able to run 
//     * interrupt code besides the sleep function, place it in 
//     * setup() for example.
//     * 
//     * In the function call attachInterrupt(A, B, C)
//     * A   can be either 0 or 1 for interrupts on pin 2 or 3.   
//     * 
//     * B   Name of a function you want to execute at interrupt for A.
//     *
//     * C   Trigger mode of the interrupt pin. can be:
//     *             LOW        a low level triggers
//     *             CHANGE     a change in level triggers
//     *             RISING     a rising edge of a level triggers
//     *             FALLING    a falling edge of a level triggers
//     *
//     * In all but the IDLE sleep modes only LOW can be used.
//     */
//
//    attachInterrupt(SleepInterrupt, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
//                                       // wakeUpNow when pin 2 gets LOW 
//
//    sleep_mode();            // here the device is actually put to sleep!!
//                             // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
//
//    sleep_disable();         // first thing after waking from sleep:
//                             // disable sleep...
//    detachInterrupt(SleepInterrupt);      // disables interrupt 0 on pin 2 so the 
//                             // wakeUpNow code will not be executed 
//                             // during normal running time.
}

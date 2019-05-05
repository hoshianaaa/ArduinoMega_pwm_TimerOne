#include <TimerOne.h>

volatile int PULSE[14];
const int T = 50;

//サーボの角度をセット (pin 2-13, deg:0-180)
int ServoDegree(int pin, int deg) {
  int pul;
  pul = map(deg, 0, 180, 900, 2100);
  PULSE[pin] = pul;
}

//高速digitalWrite
void SdigitalWrite(int pin, bool state) {
  //PORT- |= _BV(-);
  if (state == true) {
    if (pin == 2)PORTE |= _BV(4);
    if (pin == 3)PORTE |= _BV(5);
    if (pin == 4)PORTG |= _BV(5);
    if (pin == 5)PORTE |= _BV(3);
    if (pin == 6)PORTH |= _BV(3);
    if (pin == 7)PORTH |= _BV(4);
    if (pin == 8)PORTH |= _BV(5);
    if (pin == 9)PORTH |= _BV(6);
    if (pin == 10)PORTB |= _BV(4);
    if (pin == 11)PORTB |= _BV(5);
    if (pin == 12)PORTB |= _BV(6);
    //if (pin == 13)PORTB |= _BV(7);
    if (pin == 13)digitalWrite(13, HIGH);
  }
  if (state == false) {
    if (pin == 2)PORTE &= ~_BV(4);
    if (pin == 3)PORTE &= ~_BV(5);
    if (pin == 4)PORTG &= ~_BV(5);
    if (pin == 5)PORTE &= ~_BV(3);
    if (pin == 6)PORTH &= ~_BV(3);
    if (pin == 7)PORTH &= ~_BV(4);
    if (pin == 8)PORTH &= ~_BV(5);
    if (pin == 9)PORTH &= ~_BV(6);
    if (pin == 10)PORTB &= ~_BV(4);
    if (pin == 11)PORTB &= ~_BV(5);
    if (pin == 12)PORTB &= ~_BV(6);
    //if (pin == 13)PORTB &= _BV(7);
    if (pin == 13)digitalWrite(13, LOW);
  }
}

void flash()
{
  static int timer[14];
  static int flag[14];

  for (int i = 2; i < 14; i++) {
    timer[i] += T;
    if (timer[i] <= PULSE[i]) {
      if (flag[i] == 0) {
        SdigitalWrite(i, HIGH);
        flag[i] = 1;
      }
    }
    else if (timer[i] <= 20000) {
      if (flag[i] == 1) {
        SdigitalWrite(i, LOW);
        flag[i] = 0;
      }
    }
    else timer[i] = 0;
  }
}




void setup()
{
  for (int i = 2; i < 14; i++)pinMode(i, OUTPUT);
  Timer1.initialize(T); //The led will blink in a half second time interval
  Timer1.attachInterrupt(flash);
  Serial.begin(9600);
}

void loop()
{


  for (int i = 2; i < 14; i++)ServoDegree(i, 90);
/*
  for (int i = 70; i < 120; i++) {
    ServoDegree(13, i);
    
    delay(20);

  }

    for (int i = 120; i > 70; i--) {
    ServoDegree(3, i);
    
    delay(20);

  }

  */
}

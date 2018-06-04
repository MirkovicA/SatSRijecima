#include "LedControl.h"
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

/* pin 12 - DataIn
 * pin 11 - CLK
 * pin 10 - LOAD
 * 4 x pločice s LE diodama */
LedControl lc = LedControl(12,11,10,4);

void setup() {
  // paljenje svakog MAX7219 jer je po defaultu ugasen
  for(int i=0; i<4; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,8);
    lc.clearDisplay(i);
  }
  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }

  // provjera da li su postavljeni sat i datum, te ako nisu postavljanje
  #ifdef ADJUST_DATE_TIME
  DateTime d(2018,4,6,11,51,00);
  rtc.adjust(d);
  #endif

}

/* s - sat
 * m - minute */
int s, m;
void loop() {
    //čitanje trenutnog vremena
    DateTime now = rtc.now();
    m = now.minute();
    s = now.hour();

    // prebacivanje iz 24-satnog oblika u 12-satni oblik
    if (s > 12){
      s = s - 12;
    }
    if(s == 0){
      s = 12;  
    }
        
    /* paljenje odredene diode ovisno o satu jer je 
     *  1 SAT
     *  2,3,4 SATA
     *  5 SATI  */
    if(s == 1){
        leds(5,12,3,HIGH);
    }else if (s == 2 || s == 3 || s == 4){
        leds(10,12,4,HIGH);
    }else{
      leds(5,12,4,HIGH);  
    }

    // odredivanje da li ce dioda koja osvjetljava slovo I biti upajena ili ugasena
    if(m == 0){
      leds(15,12,1,LOW);
    }else{
      leds(15,12,1,HIGH);  
    }

    // swtich case za paljenje odredenih dioda ovisno o satu 
    switch(s){
    case 1: leds(0,13,8,LOW);
            leds(3,15,5,HIGH);
            break;
    case 2: leds(3,15,5,LOW);
            leds(5,12,3,LOW);
            leds(0,13,3,HIGH);
            break;
    case 3: leds(0,13,3,LOW);
            leds(0,15,3,HIGH);
            break;
    case 4: leds(0,15,3,LOW);
            leds(0,14,6,HIGH);
            break;
    case 5: leds(0,14,6,LOW);
            leds(10,12,4,LOW);
            leds(13,13,3,HIGH);
            break;
    case 6: leds(13,13,3,LOW);
            leds(0,12,4,HIGH);
            break;
    case 7: leds(0,12,4,LOW);
            leds(6,14,5,HIGH);
            break;
    case 8: leds(6,14,5,LOW);
            leds(12,15,4,HIGH);
            break;
    case 9: leds(12,15,4,LOW);
            leds(8,13,5,HIGH);
            break;
    case 10: leds(8,13,5,LOW);
             leds(11,14,5,HIGH);
             break;
    case 11: leds(11,14,5,LOW);
             leds(3,15,9,HIGH);
             break;
    case 12: leds(3,15,9,LOW);
             leds(0,13,8,HIGH); 
             break;
    
  }

  // switch case za paljenje odredenih dioda ovisno o minutama
  switch(m){
    case 0: leds(9,10,7,LOW);
            leds(0,4,5,LOW);
            leds(0,2,6,LOW);
            delay(2000);
            break;
    case 1: leds(0,5,5,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 2: leds(0,5,5,LOW);
            leds(0,2,6,LOW);
            leds(0,7,5,HIGH);
            leds(7,2,6,HIGH);
            delay(2000);
            break;
    case 3: leds(0,7,5,LOW);
            leds(8,3,3,HIGH);
            leds(7,2,6,HIGH);
            delay(2000);
            break;
    case 4: leds(8,3,3,LOW);
            leds(9,6,6,HIGH);
            leds(7,2,6,HIGH);
            delay(2000);
            break;
    case 5: leds(9,6,6,LOW);
            leds(7,2,6,LOW);
            leds(8,8,3,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 6: leds(8,8,3,LOW);
            leds(11,4,4,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 7: leds(11,4,4,LOW);
            leds(5,5,5,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 8: leds(5,5,5,LOW);
            leds(0,6,4,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 9: leds(0,6,4,LOW);
            leds(0,4,5,HIGH);
            leds(0,2,6,HIGH);
            delay(2000);
            break;
    case 10: leds(0,4,5,LOW);
             leds(11,10,5, HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 11: leds(11,10,5, LOW);
             leds(0,9,9,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 12: leds(0,9,9,LOW);
             leds(0,8,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 13: leds(0,8,8,LOW);
             leds(8,3,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 14: leds(8,3,8,LOW);
             leds(0,3,9,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 15: leds(0,3,9,LOW);
             leds(8,8,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 16: leds(8,8,8,LOW);
             leds(6,7,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 17: leds(6,7,8,LOW);
             leds(5,5,10,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 18: leds(5,5,10,LOW);
             leds(0,6,9,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 19: leds(0,6,9,LOW);
             leds(0,4,10,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 20: leds(0,4,10,LOW);
             leds(8,11,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 21: leds(8,11,8,HIGH);
             leds(0,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 22: leds(0,5,5,LOW);
             leds(0,2,6,LOW);
             leds(8,11,8,HIGH);
             leds(0,7,5,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 23: leds(0,7,5,LOW);
             leds(8,11,8,HIGH);
             leds(8,3,3,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 24: leds(8,3,3,LOW);
             leds(8,11,8,HIGH);
             leds(9,6,6,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 25: leds(9,6,6,LOW);
             leds(7,2,6,LOW);
             leds(8,11,8,HIGH);
             leds(8,8,3,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 26: leds(8,8,3,LOW);
             leds(8,11,8,HIGH);
             leds(11,4,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 27: leds(11,4,4,LOW);
             leds(8,11,8,HIGH);
             leds(5,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 28: leds(5,5,5,LOW);
             leds(8,11,8,HIGH);
             leds(0,6,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 29: leds(0,6,4,LOW);
             leds(8,11,8,HIGH);
             leds(0,4,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 30: leds(8,11,8,LOW);
             leds(0,4,5,LOW);
             leds(0,11,8,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 31: leds(0,11,8,HIGH);
             leds(0,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 32: leds(0,5,5,LOW);
             leds(0,2,6,LOW);
             leds(0,11,8,HIGH);
             leds(0,7,5,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 33: leds(0,7,5,LOW);
             leds(0,11,8,HIGH);
             leds(8,3,3,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 34: leds(8,3,3,LOW);
             leds(0,11,8,HIGH);
             leds(9,6,6,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 35: leds(9,6,6,LOW);
             leds(7,2,6,LOW);
             leds(0,11,8,HIGH);
             leds(8,8,3,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 36: leds(8,8,3,LOW);
             leds(0,11,8,HIGH);
             leds(11,4,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 37: leds(11,4,4,LOW);
             leds(0,11,8,HIGH);
             leds(5,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 38: leds(5,5,5,LOW);
             leds(0,11,8,HIGH);
             leds(0,6,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 39: leds(0,6,4,LOW);
             leds(0,11,8,HIGH);
             leds(0,4,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 40: leds(0,11,8,LOW);
             leds(0,4,5,LOW);
             leds(0,10,9,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 41: leds(0,10,9,HIGH);
             leds(0,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 42: leds(0,5,5,LOW);
             leds(0,2,6,LOW);
             leds(0,10,9,HIGH);
             leds(0,7,5,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 43: leds(0,7,5,LOW);
             leds(0,10,9,HIGH);
             leds(8,3,3,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 44: leds(8,3,3,LOW);
             leds(0,10,9,HIGH);
             leds(9,6,6,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 45: leds(9,6,6,LOW);
             leds(7,2,6,LOW);
             leds(0,10,9,HIGH);
             leds(8,8,3,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 46: leds(8,8,3,LOW);
             leds(0,10,9,HIGH);
             leds(11,4,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 47: leds(11,4,4,LOW);
             leds(0,10,9,HIGH);
             leds(5,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 48: leds(5,5,5,LOW);
             leds(0,10,9,HIGH);
             leds(0,6,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 49: leds(0,6,4,LOW);
             leds(0,10,9,HIGH);
             leds(0,4,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 50: leds(0,10,9,LOW);
             leds(0,4,5,LOW);
             leds(9,10,7, HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 51: leds(9,10,7, HIGH);
             leds(0,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 52: leds(0,5,5,LOW);
             leds(0,2,6,LOW);
             leds(9,10,7, HIGH);
             leds(0,7,5,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 53: leds(0,7,5,LOW);
             leds(9,10,7, HIGH);
             leds(8,3,3,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 54: leds(8,3,3,LOW);
             leds(9,10,7, HIGH);
             leds(9,6,6,HIGH);
             leds(7,2,6,HIGH);
             delay(2000);
             break;
    case 55: leds(9,6,6,LOW);
             leds(7,2,6,LOW);
             leds(9,10,7, HIGH);
             leds(8,8,3,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 56: leds(8,8,3,LOW);
             leds(9,10,7, HIGH);
             leds(11,4,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 57: leds(11,4,4,LOW);
             leds(9,10,7, HIGH);
             leds(5,5,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 58: leds(5,5,5,LOW);
             leds(9,10,7, HIGH);
             leds(0,6,4,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
    case 59: leds(0,6,4,LOW);
             leds(9,10,7,HIGH);
             leds(0,4,5,HIGH);
             leds(0,2,6,HIGH);
             delay(2000);
             break;
  } 
}

// funkcija prima parametre pozicije niza LED dioda koje trebaju promijeniti stanje po x i y osi,broj dioda i stanje koje treba biti
void leds(int x, int y, int N, bool state){
  for(int n=0; n<N; n++){
    led(x+n, y, state);
  }
}

//funkcija za odredivanje rasporeda dioda na spojenim plocicama
void led(int x, int y, bool state){
  x = 15 - x;
  int i = x>7 ? y>7 ? 3 : 1 : y>7 ? 2 : 0;
  int u = i&1 ? x-8 : x;
  int v = i<2 ? 7-y : 15-y;
  lc.setLed(i,u,v,state);
}


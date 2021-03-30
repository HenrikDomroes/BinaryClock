 #include <Wire.h>

//DS3232 I2C Address
#define RTC_ADDRESS 0x68

//DS3232 Register Addresses
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x01
#define RTC_HOURS 0x02

//Times keeping variables
byte seconds;  //00-59
byte minutes;  //00-59
byte hours;    //00-23

//Buttons pins
const int minutesButton = 14;
const int hoursButton = 15;

//LED pins
const int hoursPin10 = 0;       //TX
const int hoursPin20 = 1;       //RX

const int hoursPin1 = 2;
const int hoursPin2 = 3;
const int hoursPin4 = 4;
const int hoursPin8 = 5;

const int minutesPin10 = 6;
const int minutesPin20 = 7;
const int minutesPin40 = 8;

const int minutesPin1 = 9;
const int minutesPin2 = 10;
const int minutesPin4 = 11;
const int minutesPin8 = 12;

//______________________________________________________________

void setup() {
  // put your setup code here, to run once:
  //Set Button pins mode
  pinMode(minutesButton, INPUT);
  pinMode(hoursButton, INPUT);
  
  //Set LED pins mode
  pinMode(hoursPin10, OUTPUT);
  pinMode(hoursPin20, OUTPUT);
  pinMode(hoursPin1, OUTPUT);
  pinMode(hoursPin2, OUTPUT);
  pinMode(hoursPin4, OUTPUT);
  pinMode(hoursPin8, OUTPUT);
  pinMode(minutesPin10, OUTPUT);
  pinMode(minutesPin20, OUTPUT);
  pinMode(minutesPin40, OUTPUT);
  pinMode(minutesPin1, OUTPUT);
  pinMode(minutesPin2, OUTPUT);
  pinMode(minutesPin4, OUTPUT);
  pinMode(minutesPin8, OUTPUT);
  
  //Start the RTC communication
  Wire.begin();
  Serial.begin(9600);

  //Initialize and set time
  seconds = 00;
  minutes = 00;
  hours = 00;
}

//______________________________________________________________

void loop() {
  // put your main code here, to run repeatedly:
  checkInputs();
  getTime();
  displayLights();
  delay(500);

}

//______Button Input Function___________________________________

void checkInputs() {
  if (digitalRead(minutesButton) == HIGH) {
    minutes++;
    seconds = 00;
    if (minutes == 60) {
      minutes = 00;
    }
    setTime();
  }
  
  if (digitalRead(hoursButton) == HIGH) {
    hours++;
    seconds = 00;
    if (hours == 24) {
      hours = 00;
    }
    setTime();
  }
}

//______RTC Functions___________________________________________

void setTime() {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  Wire.endTransmission();
}

void getTime() {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x00);                       //or Wire.write(0)
  Wire.endTransmission();
  
  Wire.requestFrom(RTC_ADDRESS, 3);
  seconds = bcdToDec(Wire.read());   
  minutes = bcdToDec(Wire.read());      
  hours = bcdToDec(Wire.read() & 0b00111111);
}

//______Utility Functions_______________________________________

byte decToBcd(byte val) {
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val) {
  return ( (val/16*10) + (val%16) );
}

//______Display Function________________________________________

void displayLights() {
  if (hours >= 20) {
    digitalWrite(hoursPin20, HIGH);
    digitalWrite(hoursPin10, LOW);
  } else if (hours >= 10) {
    digitalWrite(hoursPin20, LOW);
    digitalWrite(hoursPin10, HIGH);
  } else {
    digitalWrite(hoursPin20, LOW);
    digitalWrite(hoursPin10, LOW);
  }
  
  int hoursUnit = hours % 10;
  if (hoursUnit >= 8) {
    digitalWrite(hoursPin8, HIGH);
    digitalWrite(hoursPin4, LOW);
    digitalWrite(hoursPin2, LOW);
  } else if (hoursUnit >= 6) {
    digitalWrite(hoursPin8, LOW);
    digitalWrite(hoursPin4, HIGH);
    digitalWrite(hoursPin2, HIGH);
  } else if (hoursUnit >= 4) {
    digitalWrite(hoursPin8, LOW);
    digitalWrite(hoursPin4, HIGH);
    digitalWrite(hoursPin2, LOW);
  } else if (hoursUnit >= 2) {
    digitalWrite(hoursPin8, LOW);
    digitalWrite(hoursPin4, LOW);
    digitalWrite(hoursPin2, HIGH);
  } else {
    digitalWrite(hoursPin8, LOW);
    digitalWrite(hoursPin4, LOW);
    digitalWrite(hoursPin2, LOW);
  }
  if (hoursUnit % 2 == 1) {
    digitalWrite(hoursPin1, HIGH);
  } else {
    digitalWrite(hoursPin1, LOW);
  }
  
  
 
  
  
  if (minutes >= 40) {
    digitalWrite(minutesPin40, HIGH);
    digitalWrite(minutesPin20, LOW);
    if (minutes >= 50) {
      digitalWrite(minutesPin10, HIGH);
    } else {
      digitalWrite(minutesPin10, LOW);
    }
  }else if (minutes >= 20) {
    digitalWrite(minutesPin40, LOW);
    digitalWrite(minutesPin20, HIGH);
    if (minutes >= 30) {
      digitalWrite(minutesPin10, HIGH);
    } else {
      digitalWrite(minutesPin10, LOW);
    }
  } else if (minutes >= 10) {
    digitalWrite(minutesPin40, LOW);
    digitalWrite(minutesPin20, LOW);
    digitalWrite(minutesPin10, HIGH);
  } else {
    digitalWrite(minutesPin40, LOW);
    digitalWrite(minutesPin20, LOW);
    digitalWrite(minutesPin10, LOW);
  }
  
  int minutesUnit = minutes % 10;
  if (minutesUnit >= 8) {
    digitalWrite(minutesPin8, HIGH);
    digitalWrite(minutesPin4, LOW);
    digitalWrite(minutesPin2, LOW);
  } else if (minutesUnit >= 6) {
    digitalWrite(minutesPin8, LOW);
    digitalWrite(minutesPin4, HIGH);
    digitalWrite(minutesPin2, HIGH);
  } else if (minutesUnit >= 4) {
    digitalWrite(minutesPin8, LOW);
    digitalWrite(minutesPin4, HIGH);
    digitalWrite(minutesPin2, LOW);
  } else if (minutesUnit >= 2) {
    digitalWrite(minutesPin8, LOW);
    digitalWrite(minutesPin4, LOW);
    digitalWrite(minutesPin2, HIGH);
  } else {
    digitalWrite(minutesPin8, LOW);
    digitalWrite(minutesPin4, LOW);
    digitalWrite(minutesPin2, LOW);
  }
  if (minutesUnit % 2 == 1) {
    digitalWrite(minutesPin1, HIGH);
  } else {
    digitalWrite(minutesPin1, LOW);
  }
}

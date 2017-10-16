int sensorPin = A1;
float sensorValue = 0;
float humidityValue = 0;
int relayPin = 9;
const int buttonPin = 2;
int relayState = LOW;
int buttonState = 0;
unsigned long previousHumidityMillis = 0;
unsigned long previousHumidityReadingMillis = 0;
const long relayInterval = 10000;
const long humidityReadingInterval = 1000; 

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

buttonState = digitalRead(buttonPin);
//Serial.println(buttonState);
if (buttonState == HIGH) {
    relayState = HIGH;
    digitalWrite(relayPin, relayState);
  } else {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousHumidityReadingMillis >= humidityReadingInterval) {
      previousHumidityReadingMillis = currentMillis;
      sensorValue = analogRead(sensorPin);
      humidityValue = toHumidity(sensorValue);  
      Serial.println(humidityValue);
    }
  
  if(humidityValue > 65){
      relayState = HIGH;
      previousHumidityMillis = currentMillis;
      } else {
           if (currentMillis - previousHumidityMillis >= relayInterval) {
           relayState = LOW;
           }
    }    
    digitalWrite(relayPin, relayState);
  }
}

float toHumidity(int analog_val){
float v = 5; // Standard voltage value ( V )
float rel = (analog_val / (1024/v)) * 100;
if(rel > 100){
    rel = 100;
    }
  return rel;
}


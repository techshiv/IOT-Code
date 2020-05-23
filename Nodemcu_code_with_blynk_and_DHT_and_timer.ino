
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <HttpClient.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>


const int ledPin =  D0;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 7500;           // interval at which to blink (milliseconds)




char auth[] = "TtGVPcqUUMtN8vr1xqU680Fv0TXxHEUm";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "home WIFI";
char pass[] = "shivamadappa@123.";
int j = 0;
#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  //  if (isnan(h) || isnan(t)) {
  //    Serial.println("Failed to read from DHT sensor!");
  //    return;
  //  }
 
  j++;
  Blynk.virtualWrite(V5, j);

}

void setup()
{ pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  // Debug console
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
int value;
BLYNK_WRITE(V1)
{
  value = param.asInt(); // Get value as integer


}


void loop()
{
  unsigned long currentMillis = millis();


  //  client.get("");

  if (currentMillis - previousMillis >= interval) {
   
    previousMillis = currentMillis;

   
    if (ledState == LOW) {
      ledState = HIGH;
    
    } else {
      ledState = LOW;
     
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }


  if (value == 1)
  {
    digitalWrite(D1, LOW);

  }
  else {
    digitalWrite(D1, HIGH);

  }
  Blynk.run();
  timer.run();
}

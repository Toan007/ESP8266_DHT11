#include "DHT.h"
#include "EspMQTTClient.h"

#define SECRET_MQTT_USERNAME "EignHDk7NTw3JiYPCBgSMSE"
#define SECRET_MQTT_CLIENT_ID "EignHDk7NTw3JiYPCBgSMSE"
#define SECRET_MQTT_PASSWORD "kzeSUUEoZNsgR3PEMlF6FSks"

#define SECRET_WIFI_NAME "HAPPY NEW YEAR"
#define SECRET_WIFI_PASSWORD "nhutenwifi@#$"
#define CHANNEL_ID "1866652"
#define DHTPIN 5 
#define DHTTYPE DHT11

EspMQTTClient client(
  SECRET_WIFI_NAME,
  SECRET_WIFI_PASSWORD,
  "mqtt3.thingspeak.com",
  SECRET_MQTT_USERNAME,
  SECRET_MQTT_PASSWORD,
  SECRET_MQTT_CLIENT_ID
);



DHT dht(DHTPIN, DHTTYPE);

//unsigned long lastTime = 0;
//unsigned long delayTime = 5000;

void setup(){
  Serial.begin(115200);
 dht.begin();
}
void onConnectionEstablished(){
}

void doc()
{
  if (client.isConnected() ) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
  
   
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print(F("\nTemperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%  "));

    String MY_TOPIC = "channels/" + String(CHANNEL_ID) + "/publish";  
    String payload = "field1=" + String(t) + "&field2=" + String(h);
    client.publish(MY_TOPIC, payload);
}
}
void loop(void)
{
delay(5000);
client.loop(); // Starte den MQTT Client im loop
doc();

}

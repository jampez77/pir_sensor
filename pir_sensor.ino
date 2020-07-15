#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "My_Helper.h"

//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//
//ALL CONFIG CHANGES ARE LOCATED IN My_Helper.h//

int i = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(ledPin, LOW);
  }

  digitalWrite(ledPin, HIGH);

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
   
  // Loop until we're reconnected
  while (!client.connected()) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    String clientId = "MotionDetector-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      getAndSendMotionStatus();
      digitalWrite(ledPin, HIGH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    reconnect();
  }
}

void getAndSendMotionStatus(){
   int motionState = digitalRead(inputPin);

  while(motionState == HIGH){
    //wait
    delay(100);
    //wait a while and check the pin again to make sure we are happy this is legit movement and not a false trigger
    motionState = digitalRead(inputPin);
    if ( motionState == HIGH ) {
       client.publish(topic, "on", true);
       Serial.println("Motion Detected");
       i = 0;
    }
  }

  //only need to send 'No Motion' message once.
  while(motionState == LOW && i == 0){
    client.publish(topic, "off", true);
    Serial.println("No Motion");
    i++;
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  getAndSendMotionStatus();
}

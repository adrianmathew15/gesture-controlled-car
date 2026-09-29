#include <ESP8266WiFi.h>
#include <espnow.h>
#define leftmotor_p 5
#define leftmotor_n 4
#define rigntmotor_p 14
#define rigntmotor_n 12

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    int c;
    int d;
    bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("x-axis: ");
  Serial.println(myData.b);
  Serial.print("y-axis: ");
  Serial.println(myData.c);
  Serial.print("z-axis: ");
  Serial.println(myData.d);
  

}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
pinMode(leftmotor_p,OUTPUT);
pinMode(rigntmotor_p,OUTPUT);
pinMode(leftmotor_n,OUTPUT);
pinMode(rigntmotor_n,OUTPUT);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
if(myData.b<80){
  Serial.println("left");
  digitalWrite(leftmotor_p,LOW);
  digitalWrite(leftmotor_n,HIGH);
    digitalWrite(rigntmotor_p,HIGH);
  digitalWrite(rigntmotor_n,LOW);
  }
  if(myData.b>180){
  Serial.println("right");
    digitalWrite(leftmotor_p,HIGH);
  digitalWrite(leftmotor_n,LOW);
    digitalWrite(rigntmotor_p,LOW);
  digitalWrite(rigntmotor_n,HIGH);
  }
  if(myData.c<80){
  Serial.println("backward");
    digitalWrite(leftmotor_p,LOW);
  digitalWrite(leftmotor_n,HIGH);
    digitalWrite(rigntmotor_p,LOW);
  digitalWrite(rigntmotor_n,HIGH);
  }
  if(myData.c>180){
  Serial.println("forward");
    digitalWrite(leftmotor_p,HIGH);
  digitalWrite(leftmotor_n,LOW);
    digitalWrite(rigntmotor_p,HIGH);
  digitalWrite(rigntmotor_n,LOW);
  }
  if(myData.c<180 && myData.c>80 && myData.b<180 && myData.b>80){
      Serial.println("stop");
    digitalWrite(leftmotor_p,LOW);
  digitalWrite(leftmotor_n,LOW);
    digitalWrite(rigntmotor_p,LOW);
  digitalWrite(rigntmotor_n,LOW);
    }

}

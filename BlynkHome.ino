#include<WiFi.h>
#include<BlynkSimpleEsp32.h>
#include<DHT.h>

BlynkTimer timer;

char token[] = "0ldDObpMr__X9nqU3__6-K8gqdtvQxhT";
const char* ssid = "Le Chi Luan";
const char* password = "0386363677";

int buzzer = 21;
int led = 13;
int relay_light_1 = 18;
int relay_light_2 = 17;
int relay_fan = 19;
int relay_power = 5;
int sensor_flame = 4;
int sensor_gas = 34;
int sensor_PHCD = 22;
int sensor_CO = 32;
int sensor_Air = 35;

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


BLYNK_WRITE(V0){
  int value = param.asInt();
  digitalWrite(2, value);
}

BLYNK_WRITE(V3){
  int value = param.asInt();
  digitalWrite(relay_light_1, value);
}
  
BLYNK_WRITE(V4){
  int value = param.asInt();
  digitalWrite(relay_fan, value);
}

BLYNK_WRITE(V5){
  int value = param.asInt();
  digitalWrite(buzzer, value);
}

BLYNK_WRITE(V6){
  int value = param.asInt();
  digitalWrite(relay_power, value);
}

BLYNK_WRITE(V12){
  int value = param.asInt();
  digitalWrite(relay_light_2, value);
}


void senddata(){
  int value_flame = digitalRead(sensor_flame);
  int value_gas = analogRead(sensor_gas);
  int value_PHCD = digitalRead(sensor_PHCD);
  int value_CO = analogRead(sensor_CO);
  int temperature = dht.readTemperature();
  int humidity  = dht.readHumidity();
  int value = analogRead(sensor_Air);
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V7, value_flame);
  Blynk.virtualWrite(V8, value_gas);
  Blynk.virtualWrite(V9, value_PHCD);
  Blynk.virtualWrite(V10, value);
  Blynk.virtualWrite(V11, value_CO);  
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  
  pinMode(relay_light_1, OUTPUT);
  pinMode(relay_light_2, OUTPUT);
  pinMode(relay_power, OUTPUT);
  pinMode(relay_fan, OUTPUT);
  pinMode(sensor_flame, INPUT);
  pinMode(sensor_gas, INPUT);
  pinMode(sensor_PHCD, INPUT); 
  pinMode(sensor_CO, INPUT); 
  pinMode(led, OUTPUT);
  pinMode(2, OUTPUT);
  
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting WiFi...");
    delay(500);
  }
  
  Serial.println("Connected");
  Blynk.begin(token, ssid, password, IPAddress(192,168,1,8), 8080);
  digitalWrite(2, HIGH);   
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(2, LOW);  
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, HIGH);
  
  digitalWrite(relay_power, LOW);
  Blynk.virtualWrite(V6, 0);
  
  dht.begin();
  timer.setInterval(100L, senddata);
}

void loop() {
  Blynk.run();
  timer.run();
  digitalWrite(led, HIGH);
  int value = analogRead(sensor_gas);
  Serial.print("Sensor = " );                       
  Serial.print(value);      
  Serial.print("\n");                                                                                    
}

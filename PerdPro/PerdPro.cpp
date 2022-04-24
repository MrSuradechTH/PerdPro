#include <PerdPro.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

PerdPro::PerdPro() {
  
}

void PerdPro::Begin(const char* wifi_ssid, const char* wifi_password, String perdpro_username, String perdpro_password) {
  _wifi_ssid = wifi_ssid;
  _wifi_password = wifi_password;
  _perdpro_username = perdpro_username;
  _perdpro_password = perdpro_password;

  Serial.println("");
  Serial.println("....................................................................................................");
  Serial.println("................8...................................................................................");
  Serial.println("................8..8888.888..........................888...8888.888.................................");
  Serial.println("...............8...888...888.........................888....888..888................................");
  Serial.println(".........88....8...888...888.........................888....888..8888...................888.........");
  Serial.println("......8888.....8...888...888.....88.........8.....88.888....888..8888.......8.....88......888.......");
  Serial.println("....888.......88...888...888...88.88...888.888..888.8888....888..888...8888888..88..88......8888....");
  Serial.println(".8888.........8....8888.888...88...88..8888.88..88...888....888.888....888..8..88...88.........888..");
  Serial.println(".888..........8....8888.......88...88..888.....888...888....888........888.....88...888........888..");
  Serial.println("....888......88....888........8888888..888.....888...888....888........888.....88...888.....8888....");
  Serial.println("......888....8.....888........88.......888.....888...888....888........888.....88...888...888.......");
  Serial.println("........888..8.....888........888......888.....888...888....888........888.....88...888.888.........");
  Serial.println("............88.....888........888...8..888......88...888....888........888.....88...88..............");
  Serial.println("............8......8888........88888...888......888.8888...8888........888......88..88..............");
  Serial.println("............8...................888..............88..8...........................888................");
  Serial.println("....................................................................................................");
  Serial.println("");
  Serial.println("Welcome to PerdPro.com");

  pinMode(LED_BUILTIN, OUTPUT);

//  for (uint8_t t = 4; t > 0; t--) {
//    Serial.printf("[SETUP] WAIT %d...\n", t);
//    Serial.flush();
//    delay(1000);
//  }
  WiFi.mode(WIFI_STA);
  Serial.print("Wifi Connecting");
  while((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
    WiFiMulti.addAP(_wifi_ssid, _wifi_password);
    delay(500);
  }
  Serial.println("");
  Serial.println("Wifi Connected");
}

void PerdPro::Send(String value_name, String value_num) {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    
//    String url = "http://192.168.149.212/data_transmission.php?username=MrSuradechTH&value=" + String(value); //get
//    String url = "http://192.168.149.212/data_transmission.php"; //post
    http.begin(client,_server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //เปิดเมื่อ post ปิดเมื่อ get

//    int httpCode = http.GET(); //get
    int httpCode = http.POST("username=" + _perdpro_username + "&" + "password=" + _perdpro_password + "&" + value_name + "=" + value_num); //post
    Serial.print("STATUS[SEND] : ");
    if (httpCode > 0) {
//      Serial.printf("[HTTP] GET... code: %d\n", httpCode); //show code
      Serial.println("success");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
//      if (httpCode == 302) {
//        Serial.println("success");
//      }else {
//        Serial.println("fail same value");
//      }
//      if (httpCode == HTTP_CODE_OK) {
//        String payload = http.getString();
//        Serial.println(payload);
//      }
    } else {
      Serial.println("fail");
//      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); //show error
    }
    http.end();
  }else {
    Serial.println("Wifi Disconnected");
    Serial.print("Wifi Reconnecting");
    while((WiFiMulti.run() != WL_CONNECTED)) {
      Serial.print(".");
      WiFiMulti.addAP(_wifi_ssid, _wifi_password);
      delay(500);
    }
    Serial.println("");
    Serial.println("Wifi Connected");
  }
}
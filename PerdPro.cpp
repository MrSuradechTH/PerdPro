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

void PerdPro::Send(String api_name, String api_value) {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client,_server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	
    int httpCode = http.POST("mode=SEND&username=" + _perdpro_username + "&" + "password=" + _perdpro_password + "&" + "api_name=" + api_name + "&" + "api_value=" + api_value); //post
    Serial.print("STATUS SEND [" + api_name + ":" + api_value + "] : ");
    if (httpCode > 0) {
      Serial.println("SUCCESS");
    } else {
      Serial.println("FAIL");
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

String PerdPro::Recive(String api_name) {
  String recive_value;
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
	HTTPClient http;
		
	http.begin(client,_server);
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	
	int httpCode = http.POST("mode=RECIVE&username=" + _perdpro_username + "&" + "password=" + _perdpro_password + "&" + "api_name=" + api_name);
	recive_value = http.getString();
	Serial.print("STATUS RECIVE [" + api_name + ":" + recive_value + "] : ");
	if (httpCode > 0) {
		Serial.println("SUCCESS");
	}else {
		Serial.println("FAIL");
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
  return recive_value;
}
#include <PerdPro.h>
PerdPro PerdPro;

const char* Wifi_ssid = "wifi_ssid";
const char* Wifi_password = "wifi_password";
String PerdPro_username = "PerdPro_username";
String PerdPro_password = "PerdPro_password";

void setup() {
  Serial.begin(2000000);
  PerdPro.Begin(Wifi_ssid, Wifi_password, PerdPro_username, PerdPro_password);
}
void loop() {
  PerdPro.Recive("api_name");  //return String
}

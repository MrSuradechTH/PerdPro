#include <Arduino.h>

class PerdPro {
  private:
    const char* _wifi_ssid;
    const char* _wifi_password;
    String _server = "http://192.168.8.212/data_transmission.php";
    String _perdpro_username;
    String _perdpro_password;

  public:
    PerdPro();
    void Begin(const char* wifi_ssid, const char* wifi_password, String perdpro_username, String perdpro_password);
    void Send(String value_name, String value_num);
    void Recive();
};
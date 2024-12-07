#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "ESP32_UART_Server";

WebServer server(80);

#define RX2 16
#define TX2 17

String uartData = "";

// Web Server
void handleRoot() {
  String html = "<!DOCTYPE html>"
                "<html lang='en'>"
                "<head>"
                "<meta charset='UTF-8'>"
                "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                "<title>TRACKING RFID CARD</title>"
                "<style>"
                "body {"
                "  margin: 0;"
                "  padding: 0;"
                "  font-family: 'Arial', sans-serif;"
                "  background: linear-gradient(135deg, #6e7bff, #b56de7);"
                "  color: white;"
                "  display: flex;"
                "  justify-content: center;"
                "  align-items: center;"
                "  height: 100vh;"
                "  text-align: center;"
                "}"
                "h1 {"
                "  font-size: 40px;"
                "  margin-bottom: 20px;"
                "  margin-top: 50px;" 
                "  animation: fadeIn 1.5s ease-out;"
                "}"
                "p {"
                "  font-size: 22px;"
                "  margin-bottom: 20px;"
                "  color: #f3f3f3;"
                "}"
                "button {"
                "  font-size: 20px;"
                "  padding: 15px 30px;"
                "  background-color: #ff6b6b;"
                "  color: white;"
                "  border: none;"
                "  border-radius: 5px;"
                "  cursor: pointer;"
                "  transition: all 0.3s ease;"
                "  margin: 10px;"
                "}"
                "button:hover {"
                "  background-color: #f44336;"
                "}"
                "@keyframes blink {"
                "  0% { opacity: 1; }"
                "  50% { opacity: 0.5; }"
                "  100% { opacity: 1; }"
                "}"
                ".blinking {"
                "  animation: blink 1s ease infinite;"
                "}"
                "@keyframes fadeIn {"
                "  from { opacity: 0; }"
                "  to { opacity: 1; }"
                "}"
                ".scrolling-text {"
                "  animation: scroll 15s linear infinite;"
                "  white-space: nowrap;"
                "  font-size: 18px;"
                "  color: #f3f3f3;"
                "  padding: 10px;"
                "}"
                "@keyframes scroll {"
                "  0% { transform: translateX(100%); }"
                "  100% { transform: translateX(-100%); }"
                "}"
                "</style>"
                "<script>"
                "function refreshData() {"
                "  fetch('/uart-data')"
                "    .then(response => response.text())"
                "    .then(data => {"
                "      document.getElementById('uart-data').innerHTML = data;"
                "    });"
                "} "
                "function clearConsole() {"
                "  document.getElementById('uart-data').innerHTML = '';"
                "} "
                "setInterval(refreshData, 1000);  // Cập nhật dữ liệu mỗi 3 giây"
                "</script>"
                "</head>"
                "<body>"
                "<div>"
                "<h1>TRACKING RFID CARD</h1>"
                "<div class='scrolling-text'>Nguyễn Trung Tân - 2213063, Trần Minh Tâm - 2213039, Nguyễn Hà Sơn - 2212942</div>"
                "<p id='uart-data'>" + uartData + "</p>"  // Hiển thị dữ liệu UART
                "<button class='blinking' onclick=\"clearConsole()\">Xóa lịch sử</button>"
                "</div>"
                "</body>"
                "</html>";
  server.send(200, "text/html", html);
}


void handleUartData() {
  server.send(200, "text/plain", uartData);
}


void handleClearConsole() {
  uartData = ""; 
  server.send(200, "text/plain", "Console cleared.");
}

void setup() {
  Serial.begin(115200); 
  Serial2.begin(115200, SERIAL_8N1, RX2, TX2); 


  WiFi.softAP(ssid);
  Serial.println();
  Serial.print("Access Point: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);       
  server.on("/uart-data", handleUartData); 
  server.on("/clear-console", handleClearConsole);

  server.begin();
  Serial.println("Web server started.");
}

void loop() {

  server.handleClient();

  while (Serial2.available()) {
    char c = (char)Serial2.read();
    uartData += c;

    if (c == '\n') {
      uartData += "<br>"; 

      String timeStamp = " [Time: " + String(millis() / 1000) + "s]<br>";
      uartData += timeStamp;
    }

    Serial.print(c);

    if (uartData.length() > 2048) {
      uartData = uartData.substring(uartData.length() - 2048);
    }
  }
}

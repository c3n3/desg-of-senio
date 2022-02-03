#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>



const char* serverName = "http://10.150.150.144:80/genauto/pages/devices/test";

unsigned long timer = 0;
unsigned long timerDelay = 5000;

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void sendString(const char *url)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else
  {
    Serial.println("WiFi Disconnected");
  }
}

void loop()
{
  server.handleClient();
  return;
  if (millis() - timer > timerDelay) {
    sendString(serverName);
    timer += timerDelay;
  }
}

void handle_OnConnect()
{
  if (server.hasArg("test"))
  {
    Serial.print("Arg test=");
    Serial.println(server.arg("test"));
  }
  server.send(200, "text/html", "");
}

void handle_NotFound()
{
  server.send(200, "text/html", "Hello");
}

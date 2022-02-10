#include <WiFi.h>
#include <WebServer.h>

#define PORT (80U)
#define SSID "MaxPlus"         // Enter your SSID
#define PASSWORD "SV21TRC3556" // Enter your password

static void handle_index(void);
static void handle_ledon(void);
static void handle_ledoff(void);
static void handle_not_found(void);
static String response(uint8_t state);

static WebServer server;
static uint8_t led_state = LOW;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, led_state);

    Serial.begin(9600);
    delay(3000);

    WiFi.begin(SSID, PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        while (1)
        {
            Serial.printf("WiFi Failed!\n");
            delay(1000);
        }
    }

    server.on("/", handle_index);
    server.on("/led/on", handle_ledon);
    server.on("/led/off", handle_ledoff);
    server.onNotFound(handle_not_found);

    server.begin(PORT);

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("HTTP server started");
}

void loop()
{
    server.handleClient();

    if (HIGH == led_state)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

static void handle_index(void)
{
    led_state = LOW;
    Serial.println("LED State: OFF");
    server.send(200, "text/html", response(led_state));
}

static void handle_ledon(void)
{
    led_state = HIGH;
    Serial.println("LED State: ON");
    server.send(200, "text/html", response(led_state));
}

static void handle_ledoff(void)
{
    led_state = LOW;
    Serial.println("LED State: OFF");
    server.send(200, "text/html", response(led_state));
}

static void handle_not_found(void)
{
    server.send(404, "text/plain", "Not found");
}

static String response(uint8_t state)
{
    String str = "<!DOCTYPE html><html>\n";
    str += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    str += "<title>LED Control</title>\n";
    str += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    str += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    str += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    str += ".button-on {background-color: #3498db;}\n";
    str += ".button-on:active {background-color: #2980b9;}\n";
    str += ".button-off {background-color: #34495e;}\n";
    str += ".button-off:active {background-color: #2c3e50;}\n";
    str += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    str += "</style>\n";
    str += "</head>\n";
    str += "<body>\n";
    str += "<h1>ESP32 Web Server</h1>\n";

    if (state == HIGH)
    {
        str += "<p>LED State: ON</p><a class=\"button button-off\" href=\"/led/off\">OFF</a>\n";
    }
    else
    {
        str += "<p>LED State: OFF</p><a class=\"button button-on\" href=\"/led/on\">ON</a>\n";
    }

    str += "</body>\n";
    str += "</html>\n";

    return str;
}

#include <WiFi.h>
#include <HTTPClient.h>

#define MAX_LEN (32U)
#define SSID "MaxPlus"                               // Enter your SSID
#define PASSWORD "SV21TRC3556"                       // Enter your password
#define URL_BASE "https://api.nationalize.io/?name=" // Predict nationality based on a name

static void serial_clear(void)
{
    while (Serial.available())
    {
        (void)Serial.read();
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

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
}

void loop()
{
    if (WL_CONNECTED == WiFi.status())
    {
        uint8_t i = sizeof(URL_BASE) - 1;
        char url[sizeof(URL_BASE) + MAX_LEN] = URL_BASE;

        serial_clear();
        Serial.print("\nEnter a name: ");

        while (i < (sizeof(url) - 1))
        {
            if (Serial.available())
            {
                char ch = Serial.read();
                if (ch == '\r')
                {
                    ch = '\n';
                }

                Serial.print(ch);

                if (ch == '\n')
                {
                    serial_clear();
                    break;
                }

                url[i++] = ch;
            }
        }

        Serial.flush();

        if (sizeof(URL_BASE) <= strlen(url))
        {
            HTTPClient http;

            if (http.begin(String(url))) // Predict nationality based on the name
            {
                int status = http.GET();
                if (status == HTTP_CODE_OK)
                {
                    Serial.println(http.getString());
                }
                else
                {
                    Serial.printf("[HTTP] GET failed, error code: %d", status);
                }
                http.end();
            }
            else
            {
                Serial.printf("[HTTP] Unable to connect to the server...");
            }
        }
    }
    else
    {
        Serial.println("WiFi connection error!");
        delay(1000);
    }
}

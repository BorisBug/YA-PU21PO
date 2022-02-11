#include <Arduino.h>
#include <TimeLib.h>

#define LENGTH_DT 19
#define DISPLAY_DT 'D'
#define SYNCHRONIZE_DT 'S'

#define UART Serial1

static bool show_message = true;

void setup()
{
    Serial.begin(9600);
    UART.begin(9600);
    delay(2000);
}

void loop()
{
    if (show_message)
    {
        show_message = false;
        Serial.print("Enter the command [D: Display, S: Synchronize]: ");
    }

    if (Serial.available())
    {
        char chr = toupper(Serial.read());

        if (chr == DISPLAY_DT)
        {
            Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n", year(), month(), day(), hour(), minute(), second());
        }
        else if (chr == SYNCHRONIZE_DT)
        {
            UART.write(chr);

            while (0 == UART.available())
            {
                ;
            }

            char datetime[LENGTH_DT + 1] = "";

            if (LENGTH_DT == UART.readBytes(datetime, LENGTH_DT))
            {
                int yr = 0, mt = 0, dy = 0, hr = 0, mn = 0, sc = 0;

                if (6 == sscanf(datetime, "%04d-%02d-%02d %02d:%02d:%02d", &yr, &mt, &dy, &hr, &mn, &sc))
                {
                    setTime(hr, mn, sc, dy, mt, yr);
                    Serial.println("Synchronized!");
                }
                else
                {
                    Serial.println("Invalid datetime format!");
                }
            }
            else
            {
                Serial.println("An error occurred!");
            }
        }
        else
        {
            if (chr == '\n')
            {
                Serial.println();
            }
        }

        show_message = (chr == DISPLAY_DT) || (chr == SYNCHRONIZE_DT) || (chr == '\n');
    }
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define OLED_WIDTH 128 // OLED display width,  in pixels
#define OLED_HEIGHT 64 // OLED display height, in pixels

#define SENSOR_PIN 2

Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

String temp_str;

void setup(){
    Serial.begin(9600);

    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        Serial.println(F("SSD1306 allocation failed"));
        while (true)
            ;
    }

    delay(1000);
    oled.clearDisplay();

    oled.setTextSize(2);      // text size
    oled.setTextColor(WHITE); // text color
    oled.setCursor(0, 10);    // position to display

    DS18B20.begin();
    temp_str.reserve(10);
}

void loop(){
    DS18B20.requestTemperatures();
    float temp_C = DS18B20.getTempCByIndex(0);

    temp_str = String(temp_C, 2);
    temp_str += char(247) + String("C");

    Serial.println(temp_str);
    show_display(temp_str);
}

void show_display(String text){
    int16_t x1;
    int16_t y1;
    uint16_t width;
    uint16_t height;

    oled.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

    oled.clearDisplay(); // clear display
    oled.setCursor((OLED_WIDTH - width) / 2, (OLED_HEIGHT - height) / 2);
    oled.println(text); // text to display
    oled.display();
}

  #include<Wire.h>
  #include<Adafruit_GFX.h>
  #include<Adafruit_SSD1306.h>

  Adafruit_SSD1306 display(128,64,&Wire,-1);
  void setup()
  {
    display.begin(SSD1306_SWITCHCAPVCC,0x3C);
    display.clearDisplay();
    display.ssd1306_command(SSD1306_SETCONTRAST);
display.ssd1306_command(0xFF); // Maximum contrast

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("HELLO WORLD");

    display.display();

  }
  void loop()
  {

  }
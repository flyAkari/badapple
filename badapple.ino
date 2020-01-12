/* 作者：flyAkari 会飞的阿卡林 bilibili UID:751219
 * 本代码适用于ESP8266 NodeMCU + 12864显示屏
7pin SPI引脚，正面看，从左到右依次为GND、VCC、D0、D1、RES、DC、CS
   ESP8266 ---  OLED
     3V    ---  VCC
     G     ---  GND
     D7    ---  D1
     D5    ---  D0
     D2orD8---  CS
     D1    ---  DC
     RST   ---  RES
4pin IIC引脚，正面看，从左到右依次为GND、VCC、SCL、SDA
     OLED  ---  ESP8266
     VCC   ---  3.3V
     GND   ---  G (GND)
     SCL   ---  D1(GPIO5)
     SDA   ---  D2(GPIO4)
*/

#include <U8g2lib.h>
#include <Wire.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 4, /* dc=*/ 5, /* reset=*/ 3);

void setup()
{
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.clearBuffer();
    Serial.begin(1500000);
}
uint8_t frame[1024] = {};

byte inByte;
void loop()
{
    if (Serial.available() > 0)
    {
        inByte = Serial.read();
        if (inByte == 0xAA)
        {
            if (Serial.available() > 0)
            {
                inByte = Serial.read();
                if (inByte == 0x55)
                {
                    int countnum = 0;
                    for (int i = 0; i < 1024; i++)
                    {
                        while (Serial.available() == 0)
                            ;
                        frame[i] = Serial.read();
                        countnum++;
                    }
                    u8g2.firstPage();
                    do
                    {
                        u8g2.drawXBM(0, 0, 128, 64, frame);
                    } while (u8g2.nextPage());
                }
                else if (inByte == 0x22)
                    return;
            }
        }
    }
}

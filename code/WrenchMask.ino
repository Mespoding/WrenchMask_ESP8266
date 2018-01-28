#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index_html.h"

MDNSResponder mdns;
const char *ssid = "mobi";
const char *password = "mobi";

ESP8266WebServer server(80);

#define XNUM 2			 //define how many modules in x axis
#define YNUM 1			 //define how many modules in y axis

//define an empty arrary
unsigned char XY_Arrary[YNUM][XNUM][8] = {0};
unsigned char font[38][8] = {
  {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C}, //0
  {0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10}, //1
  {0x7E, 0x2, 0x2, 0x7E, 0x40, 0x40, 0x40, 0x7E}, //2
  {0x3E, 0x2, 0x2, 0x3E, 0x2, 0x2, 0x3E, 0x0}, //3
  {0x8, 0x18, 0x28, 0x48, 0xFE, 0x8, 0x8, 0x8}, //4
  {0x3C, 0x20, 0x20, 0x3C, 0x4, 0x4, 0x3C, 0x0}, //5
  {0x3C, 0x20, 0x20, 0x3C, 0x24, 0x24, 0x3C, 0x0}, //6
  {0x3E, 0x22, 0x4, 0x8, 0x8, 0x8, 0x8, 0x8}, //7
  {0x0, 0x3E, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x3E}, //8
  {0x3E, 0x22, 0x22, 0x3E, 0x2, 0x2, 0x2, 0x3E}, //9
  {0x8, 0x14, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x22}, //A
  {0x3C, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x3C, 0x0}, //B
  {0x3C, 0x40, 0x40, 0x40, 0x40, 0x40, 0x3C, 0x0}, //C
  {0x7C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7C, 0x0}, //D
  {0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x7C}, //E
  {0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x40, 0x40}, //F
  {0x3C, 0x40, 0x40, 0x40, 0x40, 0x44, 0x44, 0x3C}, //G
  {0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 0x44}, //H
  {0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C}, //I
  {0x3C, 0x8, 0x8, 0x8, 0x8, 0x8, 0x48, 0x30}, //J
  {0x0, 0x24, 0x28, 0x30, 0x20, 0x30, 0x28, 0x24}, //K
  {0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7C}, //L
  {0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x81}, //M
  {0x0, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x0}, //N
  {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C}, //O
  {0x3C, 0x22, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20}, //P
  {0x1C, 0x22, 0x22, 0x22, 0x22, 0x26, 0x22, 0x1D}, //Q
  {0x3C, 0x22, 0x22, 0x22, 0x3C, 0x24, 0x22, 0x21}, //R
  {0x0, 0x1E, 0x20, 0x20, 0x3E, 0x2, 0x2, 0x3C}, //S
  {0x0, 0x3E, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8}, //T
  {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x22, 0x1C}, //U
  {0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18}, //V
  {0x0, 0x49, 0x49, 0x49, 0x49, 0x2A, 0x1C, 0x0}, //W
  {0x0, 0x41, 0x22, 0x14, 0x8, 0x14, 0x22, 0x41}, //X
  {0x41, 0x22, 0x14, 0x8, 0x8, 0x8, 0x8, 0x8}, //Y
  {0x0, 0x7F, 0x2, 0x4, 0x8, 0x10, 0x20, 0x7F}, //Z
  {0x8, 0x7F, 0x49, 0x49, 0x7F, 0x8, 0x8, 0x8}, //中
  {0xFE, 0xBA, 0x92, 0xBA, 0x92, 0x9A, 0xBA, 0xFE}, //国
};
#define  max_exp 13
byte expxx[max_exp][16] = {
  {B00000011, B00000110, B00001100, B00011000, B00110000, B01100000, B11000000, B10000000, B10000000, B11000000, B01100000, B00110000, B00011000, B00001100, B00000110, B00000011}, // \/
  {B10000000, B11000000, B01100000, B00110000, B00011000, B00001100, B00000110, B00000011, B00000011, B00000110, B00001100, B00011000, B00110000, B01100000, B11000000, B10000000}, // \/
  {B00000000, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B00000000}, //= =
  {B00011000, B00001100, B00000110, B00000011, B00000011, B00000110, B00001100, B00011000, B00011000, B00001100, B00000110, B00000011, B00000011, B00000110, B00001100, B00011000}, //^ ^
  {B00000000, B00000000, B00000000, B10000001, B11000011, B01100110, B00111100, B00011000, B00011000, B00111100, B01100110, B11000011, B10000001, B00000000, B00000000, B00000000}, //><
  {B00000000, B00101000, B00101000, B11111110, B00101000, B11111110, B00101000, B00101000, B00101000, B00101000, B11111110, B00101000, B11111110, B00101000, B00101000, B00000000}, //# #
  {B00000000, B11000011, B01100110, B00111100, B00011000, B00111100, B01100110, B11000011, B11000011, B01100110, B00111100, B00011000, B00111100, B01100110, B11000011, B00000000}, //XX
  {0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c, 0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c}, //love
  {B00000000, B00001100, B00011110, B10110011, B10100001, B00000011, B00000110, B00001100, B00001100, B00011110, B10110011, B10100001, B00000011, B00000110, B00001100, B00000000},//??
  {B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111},//口口
  {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C},
  {0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x14, 0x10, 0x10, 0x10, 0x10, 0x10},
  {0x7E, 0x2, 0x2, 0x7E, 0x40, 0x40, 0x40, 0x7E, 0x7E, 0x2, 0x2, 0x7E, 0x40, 0x40, 0x40, 0x7E}
};


byte exp_9[] = {
  0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c,
  0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c
};


byte IMAGES_1[] = { 0x07, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, };
byte IMAGES_2[] = { 0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c, 0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c};
byte love[] = {
  0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c,
  0x1c, 0x3e, 0x7e, 0xfc, 0xfc, 0x7e, 0x3e, 0x1c
};
unsigned char data[] = {0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00};
unsigned char Table_of_Digits[] = {	0x07, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00,		//0
                                    0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00,		//1
                                    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00,  	//2
                                    0x00, 0x22, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00,  	//3
                                    0x00, 0x0c, 0x14, 0x24, 0x7f, 0x04, 0x00, 0x00,  	//4
                                    0x00, 0x72, 0x51, 0x51, 0x51, 0x4e, 0x00, 0x00,  	//5
                                    0x00, 0x3e, 0x49, 0x49, 0x49, 0x26, 0x00, 0x00,  	//6
                                    0x00, 0x40, 0x40, 0x40, 0x4f, 0x70, 0x00, 0x00,  	//7
                                    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00,  	//8
                                    0x00, 0x32, 0x49, 0x49, 0x49, 0x3e, 0x00, 0x00   	//9
                                  };
//brightness para,form 0x00 to 0x0F
unsigned char  brightness = 0x00;
//define some variables
unsigned char i, j = 0, k = 0, l, m, t;

int	pin_CS = D2;
int	pin_SCK = D3;
int	pin_DIN = D4;

/*
  int  pin_CS = 11;
  int pin_SCK = 13;
  int pin_DIN = 12;*/

unsigned char ROWNUM;
unsigned char COLNUM;
unsigned char TOTALNUM;
#define DECODE_MODE_REGISTER   0x09
#define INTENSITY_REGISTER      0x0A
#define SCAN_LIMIT_REGISTER     0x0B
#define SHUT_DOWN_REGISTER     0x0C
#define DISPLAY_TEST_REGISTER     0x0F
#define SHUT_DOWN_INIT      0x01
#define DECODE_MODE_INIT      0x00
#define SCAN_LIMIT_INIT        0x07
#define DISPLAY_TEST_INIT      0x00

//MAX7219MATRIX ledMatrix8x8(pin_CS, pin_SCK, pin_DIN, XNUM, YNUM);

void Write7219(unsigned char num, unsigned char address, unsigned char dat) {
  unsigned char i, j;
  digitalWrite(pin_CS , LOW);

  for (i = 0; i < (TOTALNUM - num); i++)
    for (j = 0; j < 16; j++)
    {
      //CLK=0;
      //DI=0;
      //CLK=1;
      digitalWrite(pin_SCK , LOW);
      digitalWrite(pin_DIN , LOW);
      digitalWrite(pin_SCK , HIGH);
    }

  for (i = 0; i < 8; i++)
  {
    //CLK=0;
    digitalWrite(pin_SCK , LOW);
    if ((address & 0x80))
    {
      digitalWrite(pin_DIN , HIGH);
    }
    else
    {
      digitalWrite(pin_DIN , LOW);
    }

    address <<= 1;
    digitalWrite(pin_SCK , HIGH);
  }

  for (i = 0; i < 8; i++)
  {
    //CLK=0;
    digitalWrite(pin_SCK , LOW);
    if ((dat & 0x80))
      digitalWrite(pin_DIN , HIGH);
    else
      digitalWrite(pin_DIN , LOW);
    dat <<= 1;
    digitalWrite(pin_SCK , HIGH);
  }
  for (i = 0; i < (num - 1); i++)
    for (j = 0; j < 16; j++)
    {
      digitalWrite(pin_SCK , LOW);
      digitalWrite(pin_DIN , LOW);
      digitalWrite(pin_SCK , HIGH);
    }

  digitalWrite(pin_CS , HIGH);
}
void MAX7219_init() {
  pinMode(pin_CS, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_DIN, OUTPUT);
}
void MAX7219_Setbrightness(unsigned char brightness)
{
  unsigned char i;

  //INTENSITY_INIT = brightness;
  for (i = 1; i <= TOTALNUM; i++)
  {
    Write7219(i, SHUT_DOWN_REGISTER, SHUT_DOWN_INIT);
    Write7219(i, DISPLAY_TEST_REGISTER, DISPLAY_TEST_INIT);
    Write7219(i, DECODE_MODE_REGISTER, DECODE_MODE_INIT);
    Write7219(i, SCAN_LIMIT_REGISTER, SCAN_LIMIT_INIT);
    Write7219(i, INTENSITY_REGISTER, brightness);
  }
}

void MAX7219_test()
{
  unsigned char i;
  for (i = 1; i <= TOTALNUM; i++)
  {
    Write7219(i, DISPLAY_TEST_REGISTER, 0x01);
  }
}
void ArrDisplay(unsigned char partNum, unsigned char rNum, unsigned char *arrPtr, unsigned char arrLen)
{
  unsigned char j;
  unsigned char *p;
  unsigned char address = 0;
  unsigned char temp;
  unsigned char num;

  p = arrPtr;

  if (arrLen <= 0)
  {
    return;
  }

  for (j = 0; j < arrLen; j++)
  {
    address = (j % 8) + rNum;
    temp = (*(p++));
    num = (j >> 3) + partNum;

    Write7219(num, address, temp);
  }
}

void CLEAR_DISPLAY()
{
  unsigned char i, j;
  for (i = 1; i <= TOTALNUM; i++)
  {
    for (j = 1; j <= 8; j++)
    {
      Write7219(i, j, 0x00);
    }
  }
}

void DisplayNColum(unsigned char *arrPtr, unsigned char col, unsigned char n)
{
  unsigned char i, j;
  unsigned char pNum, colNum;

  for (j = 0; j < n; j++)
  {
    if (col <= COLNUM)
    {
      for (i = 0; i < (ROWNUM / 8); i++)
      {
        pNum = ((col - 1) / 8 + 1) + (i * (COLNUM / 8));
        colNum = ((col - 1) % 8) + 1;
        ArrDisplay(pNum, colNum, arrPtr, 1);
        arrPtr++;
      }
    }
    col++;
  }
}
void expression(byte * ex) {
  DisplayNColum((ex), 1, 16);
  delay(150);
  CLEAR_DISPLAY();
  delay(150);
  DisplayNColum((ex), 1, 16);
  delay(150);
  CLEAR_DISPLAY();
  delay(150);
  DisplayNColum((ex), 1, 16);
  delay(150);
  CLEAR_DISPLAY();
  delay(150);

}

/************************setup*******************************************************/
int len = 6;
int display_type = 1;
void setup()
{
  //init matrix
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  server.on("/exp", []() {
    //Serial.print("log :");
    Serial.println(server.arg("message"));
    Serial.print("expression:");

    int num = server.arg("exp").toInt();
    int ligth = server.arg("ligthness").toInt();

    display_type = server.arg("EXPRadio").toInt();
    if (display_type < 1 || display_type > 3)
      display_type = 1;
    if (num != 255)
      len = num;
    if (ligth != 255)
      MAX7219_Setbrightness(ligth);
    Serial.println(num);
    Serial.print("ligthness :");
    Serial.println(ligth);

    server.send(200, "text/html", index_html);
  });


  server.begin();
  Serial.println("HTTP server started");

  pinMode(pin_CS, OUTPUT);
  pinMode(pin_SCK, OUTPUT);
  pinMode(pin_DIN, OUTPUT);
  ROWNUM = 1 * 8;    //计算并保存行数
  COLNUM = 2 * 8;    //计算并保存列数
  TOTALNUM = 2 * 1;
  MAX7219_Setbrightness(0);
  CLEAR_DISPLAY();
  /*//all led on
    ledMatrix8x8.DISPLAY_TEST();
    delay(1000);
    //all led off

    //exit test mode
    ledMatrix8x8.DISPLAY_NORMAL();
    delay(500);

    //display XY_Arrary to the whole screen
    ledMatrix8x8.DisplayFullScreen(&XY_Arrary[0][0][0]);
    delay(500);
  */
  delay(500);


}
/************************loop*******************************************************/


unsigned long timeing;
unsigned long lasttime;
int lastlen;


void loop()
{
  server.handleClient();


  if (millis() - timeing > 3000 || lastlen != len) {
    switch (display_type) {
      case 1:
        expression(expxx[len]);
        //len = random(8);
        DisplayNColum((expxx[len]), 1, 16);
        timeing = millis();
        lastlen = len;
        break;
      case 2:
        expression(expxx[len]);
        len = random(max_exp);
        DisplayNColum((expxx[len]), 1, 16);
        timeing = millis();
        lastlen = len;
        break;
      case 3:
        // expression(expxx[len]);
        DisplayNColum((expxx[len]), 1, 16);
        timeing = millis();
        lastlen = len;
        break;
    }
  }

  //ledMatrix8x8.DisplayNColum((data),1,8);
  //ledMatrix8x8.DisplayFullScreen(IMAGES);
  // delay(350);

}

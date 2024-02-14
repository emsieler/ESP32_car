/*
BILIBILI:技术宅物语
*/

#include <WiFi.h>
#include <WiFiAP.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>

#include "lcd_init.h"
#include "lcd.h"
#include "lcdfont.h"

#define Rheostat_Rx_PIN 34
#define Rheostat_Ry_PIN 35
//#define ButtonA_PIN 15

//#define Rheostat_Rx_PIN 36
//#define Rheostat_Ry_PIN 39
#define ButtonA_PIN 27

WiFiUDP udp;

IPAddress local_IP(192, 168, 1, 1);  
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
// Set these to your desired credentials.
const char *ssid = "esp";
const char *password = "12345678";
char udpAddress[]={"192.168.1.2"};
char localAddress[20]={0};
const uint16_t udpPort = 10000;
uint16_t lcdCanvas[135][240];//画布

uint8_t udp_Rbuff[1024]; //UDP接收缓存
uint8_t id = 0;

int Rheostat_Rx_value;
int Rheostat_Ry_value;
uint8_t ButtonA_value=1;
uint8_t lampValue=0;

// 发送数据
void sendDate(){
  uint8_t buff[4]={0};

  //Serial.printf("RX:%d,RY:%d\r\n",Rheostat_Rx_value,Rheostat_Ry_value);
  
  if(Rheostat_Rx_value>1300){
    buff[0] = 127 + (Rheostat_Rx_value-1300)/7;
  }else if(Rheostat_Rx_value<1260){
    buff[0] = 127 - (1260-Rheostat_Rx_value)/7;
  }else{
    buff[0] = 127;
  }

  if(Rheostat_Ry_value>1300){
    buff[1] = 127 + (Rheostat_Ry_value-1300)/7;
  }else if(Rheostat_Ry_value<1260){
    buff[1] = 127 - (1260-Rheostat_Ry_value)/7;
  }else{
    buff[1] = 127;
  }
  buff[2] = lampValue;
  buff[3] = buff[0] + buff[1] + buff[2];
  
  udp.beginPacket(udpAddress,udpPort);
  udp.write(buff, 4);
  udp.endPacket();
}

void setup() {
  
  Serial.begin(115200);

  pinMode(Rheostat_Rx_PIN, INPUT);
  pinMode(Rheostat_Ry_PIN, INPUT);
  pinMode(ButtonA_PIN, INPUT_PULLUP);

  LCD_Init();
  LCD_Fill(0,0,240,135, BLACK);//填充颜色
  //开机动画
  char wc[] = {"WELCOME"};
  for(int n1=0;n1<4;n1++){
    LCD_ShowChar(111-n1*16,51,wc[3-n1],YELLOW,BLACK,32);
    LCD_ShowChar(111+n1*16,51,wc[3+n1],YELLOW,BLACK,32);
    delay(150);
  }
  for(int n1=0;n1<7;n1++){
    LCD_ShowChar(63+n1*16,51,wc[n1],WHITE,BLACK,32);
    delay(80);
  }
  //LCD_ShowString(63,51,"WELCOME",WHITE,BLACK,32);//显示字符串

  WiFi.softAP(ssid, password,5,0,4);//WIFI名，密码，信道（1-13），隐藏ssid，最大连接数
  WiFi.softAPConfig(local_IP, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("Waiting for device to connect...");
  while(WiFi.softAPgetStationNum()==0){//等待有设备连接
    delay(100);
  }
  Serial.println("Connected");
  delay(1000);
  udp.begin(udpPort);
}

void loop() {
  static uint8_t btaValueOld=1,btTime=0;

  Rheostat_Rx_value = analogRead(Rheostat_Rx_PIN);
  Rheostat_Ry_value = analogRead(Rheostat_Ry_PIN);
  ButtonA_value = digitalRead(ButtonA_PIN);

  //获取按键状态
  if(ButtonA_value!=btaValueOld){
    btTime ++;
    if(btTime >= 100){
      btaValueOld = ButtonA_value;
      if(!ButtonA_value)
        lampValue+=64;
    }
  }else{
    btTime = 0;
  }

  //读取UDP数据
  int len = udp.parsePacket(); //获取接收到的数据量
  /*if((len!=0)&&(len!=963))
    Serial.printf("len = %d\r\n",len);*/
  if(len>0){
    len = udp.read((uint8_t *)udp_Rbuff,len);
    if((len==963)&&(udp_Rbuff[1]<67)){
      /*if(id!=udp_Rbuff[1]){
        Serial.printf("id = %d-%d\r\n",id,udp_Rbuff[1]);
        id = udp_Rbuff[1];
      }
      id ++;*/
      uint16_t *p1,*p2;
      p1 = &lcdCanvas[udp_Rbuff[1]*2][0];
      p2 = (uint16_t *)&udp_Rbuff[2];
      while(p2<=(uint16_t *)&udp_Rbuff[961]){
        *p1 = *p2;
        p1++;
        p2++;
      }
      if(udp_Rbuff[1]==66){
        LCD_ShowGram(0,0,240,135,(uint16_t *)lcdCanvas);
        id = 0;
        sendDate();
      }
    }
  }
}

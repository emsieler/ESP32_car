/*
BILIBILI:技术宅物语
*/
#include "esp_timer.h"
#include "esp_camera.h"
#include "Arduino.h"
#include <WiFiUdp.h>
#include "function.h"
#include "config.h"
#include "stdlib.h"

extern String myPassword;

extern "C"
{
uint8_t temprature_sens_read();
}
uint8_t temprature_sens_read();

SemaphoreHandle_t  camera_state; //图像获取完成信号量
SemaphoreHandle_t  sendJpg_state; //图像发送完成信号量
camera_fb_t * fb = NULL; //图像缓存

WiFiUDP udp;
char udpAddress[20]={"192.168.1.1"};
char localAddress[20]={0};
const uint16_t udpPort = 10000;

// 照明灯初始化
void headlampInit(void)
{
    ledcSetup(Headlamp_Ch,1000,8);  //设置LEDC通道8频率为1000，分辨率为8位
    ledcAttachPin(Headlamp_Pin, Headlamp_Ch); //设置LEDC通道8在Headlamp_Pin上输出
}
// 照明灯设置
void headlampSet(int bri)
{
    ledcWrite(Headlamp_Ch, bri); //输出PWM  
}

// 电机初始化
void motorInit(void)
{
    ledcSetup(MotorL_A_Ch,10000,8);
    ledcAttachPin(MotorL_A_Pin, MotorL_A_Ch); 
    ledcSetup(MotorR_A_Ch,10000,8);
    ledcAttachPin(MotorR_A_Pin, MotorR_A_Ch); 
    pinMode(MotorL_B_Pin, OUTPUT);
    pinMode(MotorR_B_Pin, OUTPUT);
}
// 电机设置
void motorSet(uint8_t motor, int spe)
{
    if(motor == MOTOR_L)
    {
        if(spe>=0)
        {
            digitalWrite(MotorL_B_Pin,HIGH);
            ledcWrite(MotorL_A_Ch, 256-spe); //输出PWM  
        }
        else
        {
            digitalWrite(MotorL_B_Pin,LOW);
            ledcWrite(MotorL_A_Ch, 0-spe); //输出PWM  
        }
    }
    else if(motor == MOTOR_R)
    {
        if(spe>=0)
        {
            digitalWrite(MotorR_B_Pin,HIGH);
            ledcWrite(MotorR_A_Ch, 256-spe); //输出PWM  
        }
        else
        {
            digitalWrite(MotorR_B_Pin,LOW);
            ledcWrite(MotorR_A_Ch, 0-spe); //输出PWM  
        }
    }
}

// 发送图片数据
void sendVideoDate(uint8_t* frame, size_t len, size_t frameCount,int pakt)//pakt=0时发送全部，否则发送指定包
{
    uint8_t tx_buffer[1000] = {0};
    uint8_t *ps = frame;

    for(int ln=0;ln<67;ln++)
    {
        tx_buffer[0] = frameCount;
        tx_buffer[1] = ln;
        for(uint8_t *pb=&tx_buffer[2];pb<&tx_buffer[962];pb++)
        {
            *pb = *ps;
            ps ++;
        }
        //加校验
        for(uint8_t *pb=&tx_buffer[0];pb<&tx_buffer[962];pb++)
            tx_buffer[962] += *pb;

        //发送
        udp.beginPacket(udpAddress,udpPort);
        udp.write((const  uint8_t *)tx_buffer, 963);
        udp.endPacket();
    }
}

//获取图像
int capture_handler(void){
    esp_err_t res = ESP_OK; //结果

    xSemaphoreTake(sendJpg_state, portMAX_DELAY);
    fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return ESP_FAIL;
    }
    xSemaphoreGive(camera_state);
    esp_camera_fb_return(fb);

    return res;
}

// 通信服务
void Communication( void * parameter) {
    char udp_Rbuff[UDP_RBUFF_SIZE]; //UDP接收缓存
    uint8_t id=0; //图像帧号
    int rx_time = 0;
    BaseType_t xReturn;//图像数据是否准备就绪
    camera_fb_t * fbSend;
    
    udp.begin(udpPort);
    xSemaphoreGive(sendJpg_state);//通知获取新图像
    while(1)
    {
        // 图片传输
        xReturn = xSemaphoreTake(camera_state, 1);//查询图像数据，阻塞1ms
        if(xReturn == pdTRUE)
        {
            fbSend = fb;
            int len = fbSend->len;
            if(len>=64800)
            {
                sendVideoDate((uint8_t *)fbSend->buf, 64800, ++id,0);//将图像发送出去
                //Serial.printf("Send complete! Jpg_Len = %u,id=%u\r\n",64800,id);
            }
            xSemaphoreGive(sendJpg_state);//通知获取新图像
        }

        // 接收/运行指令
        int len = udp.parsePacket(); //获取接收到的数据量
        if(len>0)
        {
            
            //Serial.printf("udp_Rbuff len = %d\r\n",len);
            len = udp.read(udp_Rbuff,UDP_RBUFF_SIZE-1);
            //Serial.write((uint8_t *)udp_Rbuff,len);
            //Serial.println(" ");
            //校验接收到的数据
            if((len==4)&&((uint8_t)(udp_Rbuff[0]+udp_Rbuff[1]+udp_Rbuff[2])==udp_Rbuff[3]))
            {
                int lx=0,ly=0,lp=0;
                if(udp_Rbuff[0]>127)
                    lx = (udp_Rbuff[0]-127)*2;
                else if(udp_Rbuff[0]<127)
                    lx = 0-(127-udp_Rbuff[0])*2;

                if(udp_Rbuff[1]>127)
                    ly = (udp_Rbuff[1]-127)*2;
                else if(udp_Rbuff[1]<127)
                    ly = 0-(127-udp_Rbuff[1])*2;

                lp = udp_Rbuff[2];

                headlampSet(lp);
                if(abs(lx)>abs(ly))
                {
                    motorSet(MOTOR_L, lx);
                    motorSet(MOTOR_R, 0-lx);
                }
                else
                {
                    motorSet(MOTOR_L, ly);
                    motorSet(MOTOR_R, ly);
                }
                rx_time = 0;
            }
        }
        else
        {
            if(rx_time<70000)
                rx_time ++; 
        }  
        if(rx_time == 60000) //长时间未接收到数据停止摄像头运行并进入低功耗模式
        {
            Serial.println("Disconnect!");
        }
        else if(rx_time == 500) //长时间未接收到数据停止外设运行
        {
            headlampSet(0);
            motorSet(MOTOR_L, 0);
            motorSet(MOTOR_R, 0);  
        }
    }
}

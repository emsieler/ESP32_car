/*
BILIBILI:技术宅物语
 */

//EEPROM设置
#define EEPROM_WIFINAME_ADDR 100 //信息保存地址
#define EEPROM_WIFIPASSWORD_ADDR 125
#define EEPROM_BLUETOOTHNAME_ADDR 150
#define EEPROM_ROBOTPASSWORD_ADDR 175
#define EEPROM_LOCALIP_ADDR 200
#define EEPROM_RESET_ADDR 225 //连接WIFI后重启次数，1byte

// PWM通道设置
#define Servo_Ch 15 //PWM通道
#define Headlamp_Ch 8 //PWM通道
#define MotorL_A_Ch 9 //PWM通道
#define MotorR_A_Ch 10 //PWM通道
#define MOTOR_L 1
#define MOTOR_R 2

// 其他
#define UDP_RBUFF_SIZE 512 //udp接收缓冲区大小


// 板卡配置

#define batteryVoltage_Pin 37 //电池电压检测

#define Servo_Pin 5 //舵机

#define Headlamp_Pin 4 //照明灯
#define MotorR_A_Pin 18 //马达驱动 Motor drive
#define MotorR_B_Pin 23 //马达驱动 Motor drive
#define MotorL_A_Pin 22 //马达驱动 Motor drive
#define MotorL_B_Pin 19 //马达驱动 Motor drive

// 摄像头
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     27
#define SIOD_GPIO_NUM     2
#define SIOC_GPIO_NUM     15

#define Y9_GPIO_NUM       14
#define Y8_GPIO_NUM       26
#define Y7_GPIO_NUM       25
#define Y6_GPIO_NUM       32
#define Y5_GPIO_NUM       34
#define Y4_GPIO_NUM       38
#define Y3_GPIO_NUM       39
#define Y2_GPIO_NUM       35
#define VSYNC_GPIO_NUM    13
#define HREF_GPIO_NUM     12
#define PCLK_GPIO_NUM     33

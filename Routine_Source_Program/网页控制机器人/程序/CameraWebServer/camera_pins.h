

// 选择开发板
//#define CAMERA_MODEL_AI_THINKER  //ESP32-CAM
//#define CAMERA_MODEL_JSZWY_CYIS  //技术宅物语 ESP32微型侦察机器人
#define CAMERA_MODEL_JSZWY_CYIS_V2  //技术宅物语 ESP32微型侦察机器人
//#define CAMERA_MODEL_JSZWY_CAMERA  //技术宅物语 ESP32摄像头模块


// PWM通道设置
#define Servo_Ch_X 15 //PWM通道
#define Servo_Ch_Y 14 //PWM通道
#define Servo_Ch_Z 13 //PWM通道
#define Headlamp_Ch 8 //PWM通道
#define MotorL_A_Ch 9 //PWM通道
#define MotorR_A_Ch 10 //PWM通道
#define MOTOR_L 1
#define MOTOR_R 2

#if defined(CAMERA_MODEL_AI_THINKER)
#define ButtonF0_Pin 2 //功能A
#define ButtonF1_Pin 14 //功能B

#define ServoX_Pin 12 //舵机X
#define ServoY_Pin 13 //舵机Y
#define ServoZ_Pin 15 //舵机Z

#define Headlamp_Pin 4 //照明灯
#define MotorR_A_Pin -1 //马达驱动
#define MotorR_B_Pin -1 //马达驱动
#define MotorL_A_Pin -1 //马达驱动
#define MotorL_B_Pin -1 //马达驱动

// 摄像头
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#elif defined(CAMERA_MODEL_JSZWY_CYIS)
#define ButtonF0_Pin -1 //功能A
#define ButtonF1_Pin -1 //功能B

#define ServoX_Pin 5 //舵机X
#define ServoY_Pin -1 //舵机Y
#define ServoZ_Pin -1 //舵机Z

#define Headlamp_Pin 4 //照明灯
#define MotorR_A_Pin 9 //马达驱动
#define MotorR_B_Pin 10 //马达驱动
#define MotorL_A_Pin 18 //马达驱动
#define MotorL_B_Pin 23 //马达驱动

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

#elif defined(CAMERA_MODEL_JSZWY_CYIS_V2)
#define ButtonF0_Pin -1 //功能A
#define ButtonF1_Pin -1 //功能B

#define ServoX_Pin 21 //舵机X
#define ServoY_Pin -1 //舵机Y
#define ServoZ_Pin -1 //舵机Z

#define Headlamp_Pin 4 //照明灯
#define MotorR_A_Pin 18 //马达驱动
#define MotorR_B_Pin 23 //马达驱动
#define MotorL_A_Pin 22 //马达驱动
#define MotorL_B_Pin 19 //马达驱动

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

#elif defined(CAMERA_MODEL_JSZWY_CAMERA)
#define ButtonF0_Pin 10 //功能A
#define ButtonF1_Pin 3 //功能B

#define ServoX_Pin 5 //舵机X
#define ServoY_Pin 1 //舵机Y
#define ServoZ_Pin 0 //舵机Z

#define Headlamp_Pin 21 //照明灯
#define MotorR_A_Pin 18 //马达驱动
#define MotorR_B_Pin 23 //马达驱动
#define MotorL_A_Pin 19 //马达驱动
#define MotorL_B_Pin 22 //马达驱动

// 摄像头
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    15
#define XCLK_GPIO_NUM     27
#define SIOD_GPIO_NUM     4
#define SIOC_GPIO_NUM     2

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

#else
#error "Camera model not selected"
#endif

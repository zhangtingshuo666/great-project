const int Trig = 4;                                           // 设定SR04连接的Arduino引脚
const int Echo = 5; 
const int Trig1 = 6;                                        // 设定SR04连接的Arduino引脚
const int Echo1 = 7; 
const int Trig2 = 8;                                           // 设定SR04连接的Arduino引脚
const int Echo2 = 9; 
const int Trig3 = 10;                                        // 设定SR04连接的Arduino引脚
const int Echo3 = 11; 
const int Trig4 = 12;                                        // 设定SR04连接的Arduino引脚
const int Echo4 = 13; 
const int Trig5 = A0;                                        // 设定SR04连接的Arduino引脚
const int Echo5 = A1; 
double distance,time ; 
double distance1,time1;
double distance2,time2 ; 
double distance3,time3 ; 
double distance4,time4 ; 
double distance5,time5 ; 
int n=0,m=0,p;
int n5=0,n2=0,n3=0,n4=0;
int p1,p2;


//引入ESP8266.h头文件，建议使用教程中修改后的文件
#include "ESP8266.h"
#include "SoftwareSerial.h"

//配置ESP8266WIFI设置
#define SSID "Honor V8"    //填写2.4GHz的WIFI名称，不要使用校园网
#define PASSWORD "12345678"//填写自己的WIFI密码
#define HOST_NAME "api.heclouds.com"  //API主机名称，连接到OneNET平台，无需修改
#define DEVICE_ID "642900899"       //填写自己的OneNet设备ID
#define HOST_PORT (80)                //API端口，连接到OneNET平台，无需修改
String APIKey = "jcK5paqnhWIIrICN6duaYaINx2g="; //与设备绑定的APIKey

#define INTERVAL_SENSOR 5000 //定义传感器采样及发送时间间隔


//定义ESP8266所连接的软串口
/*********************
 * 该实验需要使用软串口
 * Arduino上的软串口RX定义为D3,
 * 接ESP8266上的TX口,
 * Arduino上的软串口TX定义为D2,
 * 接ESP8266上的RX口.
 * D3和D2可以自定义,
 * 但接ESP8266时必须恰好相反
 *********************/
SoftwareSerial mySerial(3, 2);
ESP8266 wifi(mySerial);

void setup()
{
  Serial.begin(9600);     //初始化串口
  pinMode(Trig, OUTPUT); 
  
        pinMode(Echo, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance is :");
  mySerial.begin(115200); //初始化软串口
  Serial.begin(9600); 
  Serial.print("setup begin\r\n");

  
 
  pinMode(Trig1, OUTPUT); 
  
        pinMode(Echo1, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance1 is :");
  mySerial.begin(115200); //初始化软串口
  Serial.begin(9600); 
  Serial.print("setup begin\r\n");
  

  pinMode(Trig2, OUTPUT); 
  
        pinMode(Echo2, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance2 is :");
  mySerial.begin(115200); //初始化软串口
 


 
  pinMode(Trig3, OUTPUT); 
  
        pinMode(Echo3, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance3 is :");
  mySerial.begin(115200); //初始化软串口




  pinMode(Trig4, OUTPUT); 
  
        pinMode(Echo4, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance4 is :");
  mySerial.begin(115200); //初始化软串口




  pinMode(Trig5, OUTPUT); 
  
        pinMode(Echo5, INPUT);                                  //要检测引脚上输入的脉冲宽度，需要先设置为输入状态
    Serial.println("The distance5 is :");
  mySerial.begin(115200); //初始化软串口
 
 


  //以下为ESP8266初始化的代码
  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
  } else {
    Serial.print("to station err\r\n");
  }

  //ESP8266接入WIFI
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

Serial.println("");


  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  mySerial.begin(9600);
  Serial.println("setup end\r\n");
}

unsigned long net_time1 = millis(); //数据上传服务器时间

void loop(){
  //以下是超声波测距的代码
   digitalWrite(Trig, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig, LOW);                                
        
        time = pulseIn(Echo, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance = time /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance<80)
        n=n+1;                                                 //计算一层入口人数变化
        delay(1000);
         
         digitalWrite(Trig1, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig1, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig1, LOW);                                
        
        time1 = pulseIn(Echo1, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance1 = time1 /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance1);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance1<40)
        m=m+1;                                                //计算一层出口人数变化
        delay(1000);

digitalWrite(Trig2, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig2, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig2, LOW);                                
        
        time2 = pulseIn(Echo2, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance2 = time2 /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance2);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance2<5)
        n2=n2+1;                                                //计算二层入口人数变化
        delay(1000);

        digitalWrite(Trig3, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig3, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig3, LOW);                                
        
        time3 = pulseIn(Echo3, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance3 = time3 /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance3);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance3<5)
        n3=n3+1;                                               //计算二层出口人数变化
        delay(1000);

        digitalWrite(Trig4, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig4, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig4, LOW);                                
        
        time4 = pulseIn(Echo4, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance4 = time4 /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance4);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance4<5)
        n4=n4+1;                                              //计算三层入口人数变化
        delay(1000);

        digitalWrite(Trig5, LOW);                                 
        delayMicroseconds(2);                                   
        digitalWrite(Trig5, HIGH);                               
        delayMicroseconds(10);                                  //产生一个10us的高脉冲去触发SR04
        digitalWrite(Trig5, LOW);                                
        
        time5 = pulseIn(Echo5, HIGH);                              // 检测脉冲宽度，注意返回值是微秒us
        distance5 = time5 /58 ;                                  //计算出距离,输出的距离的单位是厘米cm
        Serial.print(distance5);                                //把得到的距离值通过串口通信返回给电脑，通过串口监视器显示出来
        Serial.println("cm"); 
        if (distance5<5)
        n5=n5+1;                                                  //计算三层出口人数变化
        delay(1000);
 
  if (net_time1 > millis())
    net_time1 = millis();

  if (millis() - net_time1 > INTERVAL_SENSOR) //发送数据时间间隔
  {

    int chk = distance;
    //以下将各层出口入口变化情况汇总，统计楼层实时人数
    p=n-m;
    p1=n2-n3;
    p2=n4-n5;
    
    Serial.print("Read sensor: ");
    

    float sensor_hum = distance;
    Serial.println("");

//以下将数据传到云端
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
      Serial.print("create tcp ok\r\n");
      char buf[10];
      //拼接发送data字段字符串
      String jsonToSend = "{\"floor1\":";
      dtostrf(p, 1, 0, buf);           //一层的人数
      jsonToSend += "\"" + String(buf) + "\"";
      jsonToSend += ",\"floor2\":";
      dtostrf(p1, 1, 0, buf);          //二层的人数
      jsonToSend += "\"" + String(buf) + "\"";
      jsonToSend += ",\"floor3\":";
      dtostrf(p2, 1, 0, buf);          //三层的人数
      jsonToSend += "\"" + String(buf) + "\"";
      jsonToSend += "}";

      //拼接POST请求字符串
      String postString = "POST /devices/";
      postString += DEVICE_ID;
      postString += "/datapoints?type=3 HTTP/1.1";
      postString += "\r\n";
      postString += "api-key:";
      postString += APIKey;
      postString += "\r\n";
      postString += "Host:api.heclouds.com\r\n";
      postString += "Connection:close\r\n";
      postString += "Content-Length:";
      postString += jsonToSend.length();
      postString += "\r\n";
      postString += "\r\n";
      postString += jsonToSend;
      postString += "\r\n";
      postString += "\r\n";
      postString += "\r\n";

      const char *postArray = postString.c_str(); //将str转化为char数组

      Serial.println(postArray);
      wifi.send((const uint8_t *)postArray, strlen(postArray)); //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
      Serial.println("send success");
      if (wifi.releaseTCP()) { //释放TCP连接
        Serial.print("release tcp ok\r\n");
      } else {
        Serial.print("release tcp err\r\n");
      }
      postArray = NULL; //清空数组，等待下次传输数据
    } else {
      Serial.print("create tcp err\r\n");
    }

    Serial.println("");

    net_time1 = millis();
  }
}

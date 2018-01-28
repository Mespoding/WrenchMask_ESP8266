![](https://github.com/mobier/WrenchMask_ESP8266/blob/master/image/664036ad-3711-4d1d-bed9-47918c58ea93.png?raw=true)
# [制作一个跟Wrench一样的面具](https://nu11.me/?p=554)

通过在ESP8266 搭建一个Web Server 传递字符然后在Max7219显示（待开发），然后可以选择要显示的表情，以及灯的亮度。
## 硬件
* Max7219 *2
* Esp8266
* 5V电池
* Wrench面具
* 杜邦线诺干根
## 软件
```
#include "index_html.h"  //定义我们用bootstrap写的前端网页
unsigned char font[38] //自定义显示的符号 字体存放数组
expxx[max_exp] //自定义表情数据数组
expression() //闪烁特效
DisplayNColum() //Max7219 显示函数
```
## 特效
模拟眨眼特效，随机产生表情，以及不闪。
## 成品
![](https://github.com/mobier/WrenchMask_ESP8266/blob/master/image/88af86df-6fb6-4660-94ee-2d34a001f0b9.png?raw=true)
![](https://github.com/mobier/WrenchMask_ESP8266/blob/master/image/1.png?raw=true)

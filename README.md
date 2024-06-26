# GearDisp

>这是一款 BRZ/FT86/GT86 的档位显示大屏，也可以用于模拟器或者别的车，主要支持档位显示，换挡提示和油温显示，但不限于这些功能，如果想要更多的功能可以自己添加。

关于
-
转速部分的实现是基于标准的OBDII写的，其他部分我基于了15款BRZ CAN总线接口开发，感谢网友 @timurrrr，许多接口数据来自于他的开源资料
https://github.com/timurrrr/RaceChronoDiyBleDevice

除此外的话，如果没有相关接口，并且是手动挡车型，只需要转速和车速数据，然后计算比值，只需要简单的数学知识，每辆车都是可以计算出档位的。如果不装车上的话，装电脑上模拟器上都行,

注意事项
-
* CAN收发使用MCP2515模块，没有集成，因为模块比单买IC（MCP2515+TJA1050）更便宜。
* 在BRZ上支持上电自动开机，开机自检有倒计时动画，如果蓝条卡死，说明自检失败
* 其他车辆移植时注意，OBDII接口是否有自动断电功能，如果没有将会常亮，耗电大概0.6W（12V*0.05A）

OBDII接线
-
![](https://raw.githubusercontent.com/JuncoJet/GearDisp/master/demo/ODBII.jpg)

演示文件
-
![](https://raw.githubusercontent.com/JuncoJet/GearDisp/master/demo/DEMO1.jpg)

视频演示

[视频1](https://github.com/JuncoJet/GearDisp/raw/master/demo/b0658d4480e8a4c6e09b6a2c1a97a18c.mp4)
[视频2](https://github.com/JuncoJet/GearDisp/raw/master/demo/9278196ed49b6dbba883d6622d1ccc43.mp4)

目录结构
-
* mod 包含外壳的3D模型，STP文件和NX12的设计文件
* pcb 包含原理图和PCB文件，可使用立创EDA打开
* src 源代码，Arduino的工程文件

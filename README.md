# WZSerialPort

**windows上的C++串口库，封装系统的原生API**

**参考本项目使用**

## Windows上常见问题：
在Windows上，要打开COM10以后的串口（包括COM10），串口名称不在是“COM10”，而是“\\.\COM10”，因此在open函数中，如果是COM10及以后的串口，串口名应该写“\\\\.\\COM10”，其中“\\\\.\\”为“\\.\”的转义。

---

*即将基于同一个头文件WzSerialPort.h封装一个Linux版本的串口库*

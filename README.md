
# WebRTC Noise Suppression

<figure class="third">
	<img src="https://img.shields.io/github/forks/dqhplhzz2008/WebRTC_Noise_Suppression"> 
	<img src="https://img.shields.io/github/stars/dqhplhzz2008/WebRTC_Noise_Suppression">
	<img src="https://img.shields.io/github/license/dqhplhzz2008/WebRTC_Noise_Suppression">
</figure>

这是一个基于WebRTC的单通道语音增强系统，其为浮点版本。

该工程包括:

1. **common_audio**：处理音频所需要的文件在的文件夹。
2. **ns**：Noise Suppression处理的核心文件在的文件夹
3. **dr_wav.h**：读取和解析wav文件。
4. **main.c**：整个程序的主程序，系统的入口。
5. **timing.h**：计时使用的头文件。

本工程具体算法流程图及函数解释详见[链接1](http://www.yushuai.xyz/2019/05/19/4342.html)和[链接2](http://www.yushuai.xyz/2019/07/01/4396.html)。

## Directory description

|目录|说明|
|--|--|
|WebRTC_NS-GCC|GCC版本的程序|
|WebRTC_NS-VS|VS版本的程序|

以上文件夹各自目录下的工程名称解释如下：

> v**_mm

其中：

 - **表示版本号。如20表示2.0版本。
 - mm表示浮点或顶点，其中float表示浮点版本，fixed表示定点版本。

## Development Environment

### v2.0版本
|项目|内容|
|--|--|
|操作系统（VS环境）|Windows 10 x64|
|VS版本|Microsoft Visual Studio 2019|
|操作系统（GCC环境）|Cent OS6.4|
|操作系统（GCC）|GCC 4.8|

### v1.0版本

|项目|内容|
|--|--|
|操作系统（VS）|Windows 10 x64|
|VS版本|Microsoft Visual Studio 2015|
|操作系统（GCC环境）|Cent OS6.4|
|操作系统（GCC）|GCC 4.8|

## ChangeLog

### v2.0(2019.9.1)

- 将原来参考的程序文件全部替换为从WebRTC中提取的文件，更加忠实于原工程版本。
- 将程序中所有使用C++类的部分、使用函数模板的部分等全部替换为了C语言中的实现。
- 将音频文件读取的函数整合到了主程序之中。
- 2.0版本暂未提供GCC下工程，请暂时参考VS2019工程和1.0版本的GCC下工程，自行修改CMakeList.txt并进行编译。
- 
### v1.0(2019.7.18)

 - 参考[cpuimage](https://github.com/cpuimage/WebRTC_NS)的程序实现了WebRTC_NS的功能。


## Install

Linux下请确认是否安装GCC，确认方式，输入

```sh
$ gcc -v
```
若返回相应的GCC版本信息，则代表安装完成。
具体按照GCC方法请Google即可。			  

## Usage
			
对于VS版本来说，你可以直接打开VS工程进行调试或者生成测试。

对于Linux下版本来说，请在工程目录下执行
```sh
$ mkdir build
$ cd ./build
$ cmake ..
$ make
```
即可编译链接完成，运行的时候，运行下面的命令

```sh
$ ./ns <input> <output>
```
在使用的时候，若文件目录中已存在与输出文件名同名的文件，则系统提示该文件已经存在，需要判断是否覆盖，若键入**N**或**n**，则拒绝覆盖，程序报错退出；若键入**Y**或**y**，则覆盖。

## Result

* Time domain image

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/timedomain1.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/timedomain2.jpg)

* Frequency domain image

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt1.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt2.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt3.jpg)

* SNR & PESQ

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/pesqsnr.jpg)


## Related Efforts

To be continued

## Maintainers

[@dqhplhzz2008](https://github.com/dqhplhzz2008).

## Contact Me

If you have any questions, please [submit](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/issues/new) a message.

### Contributors

You can focus on my WeChat Official Account<br>

![](https://github.com/dqhplhzz2008/dqhplhzz2008.github.io/raw/master/weixingongzhonghao.jpg)  <br>

At same time, welcome to [My blog[Simplified Chinese]](http://www.yushuai.xyz)!


## License

[MIT](LICENSE) © Yushuai Zhang
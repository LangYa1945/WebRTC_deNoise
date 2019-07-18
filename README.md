

# WebRTC Noise Suppression

## Introduction

**Project Name**: Single Channel Noise Suppression based on WebRTC

**Update Date**: July 18th, 2019

**Created By** Yushuai Zhang

**Wesite**: www.yushuai.xyz

**TO DO**：

* Floating point version

 - [x] Visual Studio 2015 based on Windows 10
 
 - [x] GCC based on CentOS 6.4

* Fixed Version[not updated]

 - [ ] Visual Studio 2015 based on Windows 10
 - [ ] GCC based on CentOS 6.4



This is a single-channel speech enhancement (noise suppression) project based on WebRTC's noise suppression module. It can achieve good denoising effect.

**NOTICE**：受某些因素的影响，定点计算版本的程序暂时将不会发布，预计明年6月份毕业之后可能会发布。


## Usage

* VS2015 Version (./WebRTC_NS-VS)
```
./ns.exe <input> <output>
```

* CentOS Version(./WebRTC_NS-gcc)

```
./ns <input> <output>
```

## Result

### Test Condition

|Key| Value |
|-------|--|
|File Name|sp02.wav|
|SampleRate|8000Hz|
|SNR|0dB/5dB/15dB|
|Noise Type|Babble|

### Test Result

* Time domain image

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/timedomain1.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/timedomain2.jpg)

* Frequency domain image

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt1.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt2.jpg)

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/ypt3.jpg)

* SNR & PESQ

![](https://github.com/dqhplhzz2008/WebRTC_Noise_Suppression/raw/master/img/pesqsnr.jpg)

## Others

Reference: https://github.com/cpuimage/WebRTC_NS

## Contact

If you have any question, please contact me.

E-mail: *davidcheungchina@aliyun.com*

You can focus on my WeChat Official Account<br>

![](https://github.com/dqhplhzz2008/dqhplhzz2008.github.io/raw/master/weixingongzhonghao.jpg)  <br>

At same time, welcome to [My blog[Simplified Chinese]](http://www.yushuai.xyz)!






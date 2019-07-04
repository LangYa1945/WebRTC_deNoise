

# WebRTC Noise Suppression

## Introduction

**Project Name**: Single Channel Noise Suppression based on WebRTC

**Create Time**: July 3rd, 2019

**Created By** Yushuai Zhang

**Wesite**: www.yushuai.xyz

**Support Platform**:


* Visual Studio 2015 based on Windows 10[SUPPORTED]
* *GCC based on CentOS 6.4 [WILL SUPPORT IN THE FUTURE]*

This is a single-channel speech enhancement (noise suppression) project based on WebRTC's noise suppression module. It can achieve good denoising effect.

Up to now, this project only implements the input and output of wav files, and the core functions will be updated in the future.

## Usage

* VS2015 Version (./WebRTC_NS-VS)
```
./ns.exe <input> <output>
```

* CentOS Version(./WebRTC_NS-gcc)
Waiting...

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

## Support ME

E-mail: *davidcheungchina@aliyun.com*

You can focus on my WeChat Official Account<br>

![](https://github.com/dqhplhzz2008/dqhplhzz2008.github.io/raw/master/weixingongzhonghao.jpg)  <br>

At same time, welcome to [My blog[Simplified Chinese]](http://www.yushuai.xyz)!






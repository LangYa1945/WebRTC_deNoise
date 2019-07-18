/*
Project: WebRTC Noise Supression
Create Date: July 3rd, 2019
Modified Date : July 3rd, 2019
Created by Yushuai Zhang
WWW.YUSHUAI.XYZ
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define DR_WAV_IMPLEMENTATION

#include "dr_wav.h"
#include "noise_suppression.h"


#ifndef nullptr
#define nullptr 0
#endif // !nullptr

#ifndef MIN
#define MIN(A,B) ((A)<(B))?(A):(B)
#endif // !MIN

//去噪等级，从低到最高
enum nsLevel {
	kLow,
	kModerate,
	kHigh,
	kVeryHigh
};

//读取wav文件
int16_t *wavRead_int16(char *filename, uint32_t *sampleRate, uint64_t *totalSampleCount) {
	unsigned int channels;
	int16_t *buffer = drwav_open_file_and_read_pcm_frames_s16(filename, &channels, sampleRate, totalSampleCount);
	if (buffer == nullptr) {
		printf("READ DATA ERROR.");
	}
	return buffer;
}


//写wav文件
void wavWrite_int16(char *filename, int16_t *buffer, size_t sampleRate, uint64_t totalSampleCount) {
	drwav_data_format format;
	format.container = drwav_container_riff;     // <-- drwav_container_riff = normal WAV files, drwav_container_w64 = Sony Wave64.
	format.format = DR_WAVE_FORMAT_PCM;          // <-- Any of the DR_WAVE_FORMAT_* codes.
	format.channels = 1;
	format.sampleRate = (drwav_uint32)sampleRate;
	format.bitsPerSample = 16;
	drwav *pWav = drwav_open_file_write(filename, &format);
	if (pWav) {
		drwav_uint64 samplesWritten = drwav_write(pWav, totalSampleCount, buffer);
		drwav_uninit(pWav);
		if (samplesWritten != totalSampleCount) {
			fprintf(stderr, "ERROR\n");
			exit(1);
		}
	}
}

int ns_suppression(int16_t *buffer, uint32_t sampleRate, uint64_t samplesCount, enum nsLevel level)
{
	if (buffer == nullptr)
		return -1;
	if (samplesCount == 0)
		return -1;
	size_t samples=MIN(160, sampleRate / 100);
	if (samples == 0)
		return -1;
	uint32_t num_bands = 1;
	int16_t *inbuf = buffer;
	size_t Total = ((size_t)samplesCount / samples);
	NsHandle *nsHandle = WebRtcNs_Create();
	int stat = WebRtcNs_Init(nsHandle, sampleRate);
	if (stat != 0)
	{
		perror("WebRTC initial failed\n");
		return -1;
	}
	else
	{
		printf("WebRTC initial success!\n");
	}
	stat = WebRtcNs_set_policy(nsHandle, level);
	if (stat != 0)
	{
		perror("WebRTC set policy failed\n");
		return -1;
	}
	else
	{
		printf("WebRTC set policy success!\n");
	}
	size_t i;
	for (i = 0; i < Total; ++i)
	{
		int16_t *nsIn[1] = { inbuf };
		int16_t *nsOut[1] = { inbuf };
		WebRtcNs_Analyze(nsHandle, nsIn[0]);
		WebRtcNs_Process(nsHandle, (const int16_t *const *)nsIn, num_bands, nsOut);
		inbuf += samples;
	}
	WebRtcNs_Free(nsHandle);
	return 1;
}



int main(int argc, char *argv[])
{
	printf("Welcome to use WebRTC Noise Suppression.\n");
	printf("Latest Version:0.2\tDate: July 10,2019\n");
	printf("Welcome to my blog:http://www.yushuai.xyz\n");
	printf("\n");
	if (argc < 3)
	{
		perror("Error! Usage: ./ns.exe <input> <output>\n");
		exit(-1);
	}
	char *inwav = argv[1];
	char *outwav = argv[2];
	uint32_t sampleRate = 0;
	uint64_t inSampleCount;
	int16_t *inBuffer = wavRead_int16(inwav, &sampleRate, &inSampleCount);
	printf("Processing...\n");
	if (inBuffer != nullptr)
	{
		ns_suppression(inBuffer, sampleRate, inSampleCount, kVeryHigh);
		wavWrite_int16(outwav, inBuffer, sampleRate, inSampleCount);
		
	}
	free(inBuffer);
	printf("Process finished!\n");

	return 0;
}


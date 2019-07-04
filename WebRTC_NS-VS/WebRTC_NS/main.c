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

#include "include\timing.h"
#include "include\dr_wav.h"


#ifndef nullptr
#define nullptr 0
#endif // !nullptr

#ifndef MIN
#define MIN(A,B) ((A)<(B))?(A):(B)
#endif // !MIN

//去噪等级，从低到最高
enum nsLevel {
	yS,
	yM,
	yL,
	yXL
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
void wavWrite_int16(char *filename, int16_t *buffer, size_t sampleRate, size_t totalSampleCount) {
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




int main(int argc, char *argv[])
{
	printf("Welcome to use WebRTC Noise Suppression.\n");
	printf("Latest Version:0.1\tDate: July 3,2019\n");
	printf("Welcome to my blog:http://www.yushuai.xyz\n");
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

	if (inBuffer != nullptr)
	{
		wavWrite_int16(outwav, inBuffer, sampleRate, inSampleCount);
		free(inBuffer);
	}
	printf("Process finished!\n");

	system("pause");
	return 0;
}


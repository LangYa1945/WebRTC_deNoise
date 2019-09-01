
/*
	WebRTC Single Channel Noise Suppression
	Version:2.0
	Update: Sep 1st, 2019
	Modified By Yushuai Zhang
	www.yushuai.xyz
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <io.h>
#include "common_audio\signal_processing_library.h"

#include "ns\noise_suppression.h"

#define DR_WAV_IMPLEMENTATION

#include "dr_wav.h"
#include "timing.h"
#ifndef nullptr
#define nullptr 0
#endif // !nullptr

#ifndef MIN
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#endif // !MIN

//��ȡwav�ļ�
int16_t* wavRead_int16(char* filename, uint32_t* sampleRate, uint64_t* totalSampleCount) {
	unsigned int channels;
	int16_t* buffer = drwav_open_and_read_file_s16(filename, &channels, sampleRate, totalSampleCount);
	if (buffer == nullptr) {
		printf("ERROR.Read file failed.\n");
	}
	return buffer;
}

//дwav�ļ�
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
			fprintf(stderr, "ERROR,Write File Failed.\n");
			exit(1);
		}
	}
}



//����ȥ��ȼ�
enum nsLevel {
	kLow,
	kModerate,
	kHigh,
	kVeryHigh
};
int noiseSuppression(int16_t* buffer, uint32_t sampleRate, uint64_t samplesCount, enum nsLevel level)
{
	if (buffer == nullptr)//��ȡ������Ϊ�գ�����
		return -1;
	if (samplesCount == 0)//��������Ϊ0������
		return -1;
	size_t samples = MIN(160, sampleRate / 100);//һ֡��������
	if (samples == 0)
		return -1;
	uint32_t num_bands = 1;//ͨ����
	int16_t* inbuf = buffer;
	size_t Total = ((size_t)samplesCount / samples);//��֡��
	NsHandle* nsHandle = WebRtcNs_Create();//�������nsHandle
	int stat = WebRtcNs_Init(nsHandle, sampleRate);//��ʼ�����nsHandle
	if (stat != 0)
	{
		perror("Sorry! WebRTC Initial Failed\n");
		return -1;
	}
	stat = WebRtcNs_set_policy(nsHandle, level);
	if (stat != 0)
	{
		perror("WebRTC Set Policy Failed\n");
		return -1;
	}
	size_t i;
	for (i = 0; i < Total; ++i)
	{
		int16_t* nsIn[1] = { inbuf };
		int16_t* nsOut[1] = { inbuf };
		WebRtcNs_Analyze(nsHandle, nsIn[0]);//WebRTC�������Ʋ���
		WebRtcNs_Process(nsHandle, (const int16_t * const*)nsIn, num_bands, nsOut);//WebRTC���벿��
		inbuf += samples;
	}
	WebRtcNs_Free(nsHandle);//�ͷž��
	return 1;
}

int main(int argc, char* argv[])
{
	printf("Welcome to use WebRTC Noise Suppression.\n");
	printf("Latest Version:2.0\tDate: Sep 1st,2019\n");
	printf("Welcome to my blog:http://www.yushuai.xyz\n");
	printf("\n");
	if (argc < 3)
	{
		perror("Error! Usage: ./ns <input> <output>\n");
		exit(-1);
	}
	char* inwav = argv[1];
	char* outwav = argv[2];
	char writeFlag = 'N';
	//������������ļ�ͬ�����ļ������ж��Ƿ񸲸ǣ�����������ֱ���˳�
	if (!_access(outwav, 0))
	{
		printf("This file exists.Please make sure to overwrite it.[Y/N]");
		scanf("%c%*c", &writeFlag);
		
		if (writeFlag == 'N'||writeFlag=='n')
		{
			printf("File exist Error!\n");
			exit(-1);
		}
	}
	uint32_t sampleRate = 0;//������
	uint64_t inSampleCount;//�ܵ���
	int16_t* inBuffer = wavRead_int16(inwav, &sampleRate, &inSampleCount);//��ȡ��Ƶ�ļ�
	printf("Processing...\n");
	if (inBuffer != nullptr)
	{
		noiseSuppression(inBuffer, sampleRate, inSampleCount, kVeryHigh);
		wavWrite_int16(outwav, inBuffer, sampleRate, inSampleCount);

	}
	free(inBuffer);
	printf("Noise Suppression Finished!\n");
	return 0;
}


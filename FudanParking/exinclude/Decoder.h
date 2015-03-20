#pragma once

#include "DecoderDLLDefine.h"
namespace FFDecoder {

// return results
typedef enum
{
	FAIL_CODEC_FRAME_UNDECODED	= -7,
	FAIL_PARAM_ERROR			= -6,
	FAIL_CODEC_FRAME_UNGETTED	= -5,
	FAIL_CODEC_UNOPEND			= -4,
	FAIL_CODEC_CONTEXT_UNGETTED	= -3,
	FAIL_CODEC_UNSUPPORTED		= -2,
	FAIL						= -1,
	SUCCESS						= 0,
	RESOLUTION_CHANGED			= 1,
} FF_DecodeResult;

//Pix format
typedef enum
{
	PIXFMT_UNKOWN = 0,
	PIXFMT_YUV420P,
	PIXFMT_YUY2,
	PIXFMT_A8R8G8B8,
	PIXFMT_RGB24
} FF_PIXFormat;

//Codec type
typedef enum
{
	CODEC_TYPE_NONE		= 0,
	CODEC_TYPE_H264		,
	CODEC_TYPE_MPEG4	,
	CODEC_TYPE_MJPEG	,
	CODEC_TYPE_MPEG2_VIDEO
} FF_codecType;

//Picture param
typedef struct
{
	int width;
	int height;
	FF_codecType codecType;
	FF_PIXFormat pix_Format;
} FF_PicturePara;


class DECODER_DLL_EXPORT_IMPORT Decoder
{
public:
	 /**
	 * Method		���������캯����
	 * @breif		����δ��ʼ�������������ȳ�ʼ�����������ٽ��н��룻����ֱ�ӽ��н��봦��
	 * @codec[in]	�����������͡�
	 * @pixFormat[in]	������ݵĸ�ʽ��
	 */
	Decoder(FF_codecType codec,FF_PIXFormat outPixFormat);
	virtual ~Decoder();

	static void		decoderInit();

	static Decoder* createDecoder(FF_codecType codec);

	 /**
	 * Method		DecodeFrame
	 * @breif		����δ��ʼ�������������ȳ�ʼ�����������ٽ��н��룻����ֱ�ӽ��н��봦��
	 * @param[in]	const uint8_t* input Դ����
	 * @param[in]	const int inLen Դ���ݵĳ���
	 * @return		SUCCESS �ɹ�
					RESOLUTION_CHANGED �ɹ�������picture �����ı�
					FAIL_PARAM_ERROR ��������
					FAIL ʧ��
	 */
	virtual FF_DecodeResult decodeFrame(const unsigned char* input,const int inLen) = 0;

     /**
	 * Method		GetDecodedResolution
	 * @breif		��ý��������ݶ�Ӧ����
	 * @param[out]	FF_PicturePara para
	 * @return		SUCCESS �ɹ�
					FAIL_CODEC_FRAME_UNDECODED ��δ����
	 */
	virtual FF_DecodeResult getDecodedResolution(FF_PicturePara & para) = 0;
	
	/**
	 * Method		GetDecodedData
	 * @breif		��ý���������
	 * @param[out]	uint8_t* output ���ڴ�Ž��������
	 * @param[out]	int &outLen ������ݳ���
	 * @return		SUCCESS �ɹ�
					FAIL_PARAM_ERROR ��������
					FAIL_CODEC_FRAME_UNDECODED ��δ����
					FALI ʧ��
	 */
	virtual FF_DecodeResult getDecodedData(unsigned char* output,int &outLen) = 0;

	virtual char getFrameType() = 0;
	
protected:
	static	bool	m_bIsInit;
	FF_codecType	m_codec;
	FF_PIXFormat	m_OutPixFormat;
};


extern "C" DECODER_DLL_EXPORT_IMPORT void* createDecoder(int codec);
extern "C" DECODER_DLL_EXPORT_IMPORT int decodeFrame(void *pHandle, unsigned char* input,int inLen);
extern "C" DECODER_DLL_EXPORT_IMPORT int getDecodedResolution(void *pHandle, FF_PicturePara &param);
extern "C" DECODER_DLL_EXPORT_IMPORT int getDecodedData(void *pHandle, unsigned char* output,int *outLen);
extern "C" DECODER_DLL_EXPORT_IMPORT void closeDecoder(void *pHandle);

}
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
	 * Method		解码器构造函数。
	 * @breif		若尚未初始化解码器，就先初始化解码器，再进行解码；否则直接进行解码处理。
	 * @codec[in]	解码器的类型。
	 * @pixFormat[in]	输出数据的格式。
	 */
	Decoder(FF_codecType codec,FF_PIXFormat outPixFormat);
	virtual ~Decoder();

	static void		decoderInit();

	static Decoder* createDecoder(FF_codecType codec);

	 /**
	 * Method		DecodeFrame
	 * @breif		若尚未初始化解码器，就先初始化解码器，再进行解码；否则直接进行解码处理。
	 * @param[in]	const uint8_t* input 源数据
	 * @param[in]	const int inLen 源数据的长度
	 * @return		SUCCESS 成功
					RESOLUTION_CHANGED 成功，但是picture 参数改变
					FAIL_PARAM_ERROR 参数错误
					FAIL 失败
	 */
	virtual FF_DecodeResult decodeFrame(const unsigned char* input,const int inLen) = 0;

     /**
	 * Method		GetDecodedResolution
	 * @breif		获得解码后的数据对应参数
	 * @param[out]	FF_PicturePara para
	 * @return		SUCCESS 成功
					FAIL_CODEC_FRAME_UNDECODED 尚未解码
	 */
	virtual FF_DecodeResult getDecodedResolution(FF_PicturePara & para) = 0;
	
	/**
	 * Method		GetDecodedData
	 * @breif		获得解码后的数据
	 * @param[out]	uint8_t* output 用于存放解码后数据
	 * @param[out]	int &outLen 存放数据长度
	 * @return		SUCCESS 成功
					FAIL_PARAM_ERROR 参数错误
					FAIL_CODEC_FRAME_UNDECODED 尚未解码
					FALI 失败
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
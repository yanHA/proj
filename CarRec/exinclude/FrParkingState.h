/** 
* @file FrParkingState.h
* @brief ��λ״̬�б�ģ��
* @author ShuaiLu
* @version v2.0
* @date 2014-04-01
*/
#ifndef _FrParkingState_H_
#define _FrParkingState_H_

#ifdef FrParkingState_API
#define FrParkingState_API __declspec(dllimport)
#else
#define FrParkingState_API __declspec(dllexport)
#endif

/** @mainpage �Ϻ�����ͣ��λ״̬�б�SDK�ο��ֲ�2.0

<b>һ������ͣ��λ״̬�б�SDK��������֯�ṹ</b>
- @subpage bin.����dll����Ӧ��lib�ļ���Ҳ�������б����������opencv��ص�dll�ͼ��ܹ��豸��������
- @subpage include.����FrParkingState.h,���ļ������˳���ʶ����ȫ���ӿڡ�
- @subpage doc.�����ο��ֲᣬ��html��chm���ָ�ʽ,ͬʱ����һЩ�ĵ����漰�������ʽ��ͣ�ͼƬ��ʽ��
- @subpage data.������������
- @subpage sample.���ӹ���
- @subpage demo.��ִ��demo 
\n

<b>��������Ҫ��</b>
- @subpage ���㷨�����б𵥸�ͣ��λ
- @subpage ���㷨��������Ƕȣ��������㳵������
- @subpage ������������������ʱ�����㷨���ȡ�99%
\n

<b>������������˵��</b>
- @subpage ֧��vs2010���뻷������ֱ�ʹ�ö�Ӧ�汾��lib��dll
\n

<b>�ġ����л���˵��</b>
- @subpage �б������ʱ��Ҫ����opencv1.0��ص�dll
- @subpage ��ҪԤ�Ȱ�װ���ܹ����豸��������
\n

<b>�塢������ʹ��˵��</b>
- @subpage ����1���������ĵ�binĿ¼�µ�etcĿ¼��������ǰ��ĿĿ¼��
- @subpage ����2������FrParkingState.hͷ�ļ�
- @subpage ����3����Ӿ�̬���ӿ�FrParkingState.lib
- @subpage ����4�������б�ӿں���������ɲο�sample�е����̣�
\n

<b>��������˵��</b>
- @subpage v2.0 Ϊ���㹫˾SDK�淶���޸���ģ�����ͽӿ���
\n

<b>�ߡ��ο��ֲ�ʹ��˵��</b>
- @subpage  ��ϸ��Ϣ�����ļ�->ѡ���ļ��б���ͷ�ļ�->�Ķ��ο�
\n

*/

/**
* @brief ��ʼ������
* 
* @param[in]  modelPath �����ļ���·��
* @param[out] param     ����ʼ���Ĳ���
*
* @return true:��ʾ��ʼ���ɹ�
* @return false����ʾ��ʼ��ʧ�ܣ�����ԭ���м��������ļ�ʧ�ܻ�δ���Ӽ��ܹ��豸
*/
bool FrParkingState_API FrPStateInitialize(char *modelPath, void **param);

/**
* @brief ʶ�������ڴ��������뷽ʽ
*
* @param[in] image ����ͼƬ�����ݿ��ַ��ͼ������Ϊ8bit�Ҷ�ͼ��
* @param[in] param ��ʼ��Ĭ�ϲ���
* @param[in] w ͼƬ���
* @param[in] h ͼƬ�߶�
* @param[in] inter Ĭ�ϲ���Ϊ1���ɸ���ʵ������ٸ�ֵ��Ĭ��Ϊ���һ��ͼƬ���Ƿ��г�������
*
* @return -1������ִ��ʧ�ܣ�����ԭ���Ƿ��ʼ�����ʧ�ܻ򴴽�ͼ���ڴ�ģ��ʧ��
* @return 0������ִ�гɹ����б������޳�
* @return 1������ִ�гɹ����б������г�
*/
bool FrParkingState_API FrPStateDiscriminate(const char *image, void *param, int w, int h, int inter = 1);
/**
* @brief �ͷ���Դ���ر�ʱִ��һ��
*
* @param[in] param ��FrPStateInitialize()��ʼ���Ĳ���
*
* @return ��
*/
void FrParkingState_API FrPStateDestroy(void **param);
#endif

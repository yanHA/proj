/** 
* @file FrParkingState.h
* @brief 车位状态判别模块
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

/** @mainpage 上海亚视停车位状态判别SDK参考手册2.0

<b>一、亚视停车位状态判别SDK开发包组织结构</b>
- @subpage bin.包含dll和相应的lib文件，也附带了判别库所依赖的opencv相关的dll和加密狗设备驱动程序
- @subpage include.包含FrParkingState.h,该文件定义了车牌识别库的全部接口。
- @subpage doc.包含参考手册，有html和chm两种格式,同时还有一些文档中涉及到的名词解释（图片形式）
- @subpage data.包含测试数据
- @subpage sample.例子工程
- @subpage demo.可执行demo 
\n

<b>二、数据要求</b>
- @subpage 该算法仅能判别单个停车位
- @subpage 该算法限制拍摄角度：俯视拍摄车辆正面
- @subpage 能拍摄整个车辆正面时，该算法精度≥99%
\n

<b>三、开发环境说明</b>
- @subpage 支持vs2010编译环境，需分别使用对应版本的lib与dll
\n

<b>四、运行环境说明</b>
- @subpage 判别库运行时需要依赖opencv1.0相关的dll
- @subpage 需要预先安装加密狗的设备驱动程序
\n

<b>五、开发包使用说明</b>
- @subpage 步骤1：将开发文档bin目录下的etc目录拷贝到当前项目目录下
- @subpage 步骤2：包含FrParkingState.h头文件
- @subpage 步骤3：添加静态链接库FrParkingState.lib
- @subpage 步骤4：调用判别接口函数（具体可参考sample中的例程）
\n

<b>六、更新说明</b>
- @subpage v2.0 为满足公司SDK规范，修改了模块名和接口名
\n

<b>七、参考手册使用说明</b>
- @subpage  详细信息请点击文件->选择文件列表中头文件->阅读参考
\n

*/

/**
* @brief 初始化函数
* 
* @param[in]  modelPath 配置文件的路径
* @param[out] param     被初始化的参数
*
* @return true:表示初始化成功
* @return false：表示初始化失败，可能原因有加载配置文件失败或未连接加密狗设备
*/
bool FrParkingState_API FrPStateInitialize(char *modelPath, void **param);

/**
* @brief 识别函数，内存数据载入方式
*
* @param[in] image 读入图片的数据块地址。图像数据为8bit灰度图像
* @param[in] param 初始化默认参数
* @param[in] w 图片宽度
* @param[in] h 图片高度
* @param[in] inter 默认参数为1，可根据实际情况再赋值。默认为检测一张图片中是否有车辆存在
*
* @return -1：函数执行失败，可能原因是访问加密锁失败或创建图像内存模型失败
* @return 0：函数执行成功。判别结果：无车
* @return 1：函数执行成功。判别结果：有车
*/
bool FrParkingState_API FrPStateDiscriminate(const char *image, void *param, int w, int h, int inter = 1);
/**
* @brief 释放资源，关闭时执行一次
*
* @param[in] param 由FrPStateInitialize()初始化的参数
*
* @return 无
*/
void FrParkingState_API FrPStateDestroy(void **param);
#endif

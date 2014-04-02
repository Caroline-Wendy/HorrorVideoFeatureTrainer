/*! @file
********************************************************************************
<PRE>
模块名 : 特征存储
文件名 : FeaturesStorage.h 
相关文件 : FeaturesStorage.cpp
文件实现功能 : 特征存储类声明
作者 : C.L.Wang
Email: morndragon@126.com
版本 : 1.0
--------------------------------------------------------------------------------
多线程安全性 : 是
异常时安全性 : 是
--------------------------------------------------------------------------------
备注 : 无
--------------------------------------------------------------------------------
修改记录 :  
日 期              版本   修改人         修改内容 
2014/04/02   1.0    C.L.Wang        创建
</PRE>
********************************************************************************

* 版权所有(c) C.L.Wang, 保留所有权利

*******************************************************************************/ 

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <opencv.hpp>

//视频检测命名空间
namespace vd 
{

	/*! @class
	********************************************************************************
	<PRE>
	类名称 : FeaturesStorage
	功能 : 特征存储
	异常类 : 无
	--------------------------------------------------------------------------------
	备注 : 无
	典型用法 : FeaturesStorage iFS;
	--------------------------------------------------------------------------------
	作者 : C.L.Wang
	</PRE>
	*******************************************************************************/
	class FeaturesStorage
	{

	public:

		FeaturesStorage (
			const std::string& _fileName, 
			const int _label, 
			const cv::Mat& _videoFeature
		); //参数构造函数

		~FeaturesStorage (void); //析构函数

	public:

		const bool storeFeaturesFile (void); //存储特征文件

	private:

		std::string m_fileName; //文件名
		int m_label; //标签
		cv::Mat m_videoFeature; //视频特征

	private:

		static inline std::ostream& __printLog (
			std::ostream& _os, const std::string& _msg); //打印信息

	};

}
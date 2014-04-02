/*! @file
********************************************************************************
<PRE>
模块名 : 视频训练
文件名 : VideoTraining.h 
相关文件 : VideoTraining.cpp
文件实现功能 : 视频训练类声明
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
日 期              版本    修改人         修改内容 
2014/04/02   1.0    C.L.Wang        创建
</PRE>
********************************************************************************

* 版权所有(c) C.L.Wang, 保留所有权利

*******************************************************************************/ 

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SceneIntegration.h"
#include "FeaturesStorage.h"

//视频检测命名空间
namespace vd 
{

	/*! @class
	********************************************************************************
	<PRE>
	类名称 : VideoTraining
	功能 : 视频训练
	异常类 : 无
	--------------------------------------------------------------------------------
	备注 : 无
	典型用法 : VideoTraining iVT;
	--------------------------------------------------------------------------------
	作者 : C.L.Wang
	</PRE>
	*******************************************************************************/
	class VideoTraining
	{

	public:

		VideoTraining (
			const std::string& _featureName,
			const int _label,
			const std::string& _videoName,
			const std::size_t _shotInterval = 100,
			const std::size_t _sceneInterval = 2000
		); //构造函数

		~VideoTraining(void); //析构函数


	public:

		const bool trainVideoFeatures (void); //训练视频

	private:
		
		std::string m_featureName; //特征文件名
		int m_label; //标签
		std::string m_videoName; //视频文件名
		std::size_t m_shotInterval; //镜头间隔
		std::size_t m_sceneInterval; //场景间隔

	private:

		static inline std::ostream& __printLog (
			std::ostream& _os, const std::string& _msg); //打印信息

	};

}
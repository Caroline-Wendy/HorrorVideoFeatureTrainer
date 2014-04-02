/*! @file
********************************************************************************
<PRE>
模块名 : 视频训练
文件名 : VideoTraining.cpp
相关文件 : VideoTraining.h
文件实现功能 : 视频训练类实现
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

#include "stdafx.h"

#include "VideoTraining.h"

using namespace cv;
using namespace std;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
函数名 : VideoTraining
功能 : 参数构造函数
参数 : 
const string& _fileName, 存储文件名;
const int _label, 标签;
const std::string& _videoName, 视频名称;
const std::size_t _shotInterval, 镜头间隔;
const std::size_t _sceneInterval, 场景间隔;
返回值 : 无
抛出异常 : exception, 参数错误
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : VideoTraining iVT(fileName, label, videoName, shotInterval, sceneInterval);
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
VideoTraining::VideoTraining (
	const std::string& _featureName,
	const int _label,
	const std::string& _videoName,
	const std::size_t _shotInterval,
	const std::size_t _sceneInterval
) :
	m_featureName(_featureName),
	m_label(_label),
	m_videoName(_videoName),
	m_shotInterval(_shotInterval),
	m_sceneInterval(_sceneInterval)
{
	std::size_t maxShotInterval(999); 
	std::size_t maxSceneInterval(9999);

	/*判断文件是否存在*/

	cv::VideoCapture iVC (m_videoName);
	if (!iVC.isOpened()) {
		__printLog(std::cerr, "Failed to open the video!");
		throw std::exception("Video Name Error");
	}

	/*镜头间隔判断*/

	if (m_shotInterval < 1 || m_shotInterval > maxShotInterval) {
		__printLog(std::cerr, "The value of the shot interval is invalid.");
		throw std::exception("Shot Interval Error");
	}

	/*场景间隔判断*/

	if (m_sceneInterval < 1 || m_sceneInterval > maxSceneInterval) {
		__printLog(std::cerr, "The value of the scene interval is invalid.");
		throw std::exception("Scene Interval Error");
	}

	return;
}

/*! @function
********************************************************************************
<PRE>
函数名 : ~VideoTraining
功能 : 析构函数
参数 : void
返回值 : 无
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : iVT.~VideoTraining();
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
VideoTraining::~VideoTraining(void)
{
	return;
}

/*! @function
********************************************************************************
<PRE>
函数名 : trainVideoFeatures
功能 : 训练视频特征
参数 : void
返回值 : const bool, 是否成功
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : iVT.trainVideoFeatures();
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool VideoTraining::trainVideoFeatures (void)
{
	/*判断视频是否可读*/

	cv::VideoCapture iVC (m_videoName);

	const std::size_t framesNum(
		static_cast<std::size_t>(iVC.get(CV_CAP_PROP_FRAME_COUNT))); //总帧数

	SceneIntegration iSI(m_videoName, m_shotInterval, m_sceneInterval);

	double finalLabel (0.0); //存储视频结果
	std::size_t beg (0);
	std::size_t sceneNum(0);

	for (std::size_t j=0; j<framesNum; j+=m_sceneInterval)
	{
		/*提取关键帧集合*/

		std::shared_ptr<cv::Mat> pFeatures;
		pFeatures = iSI.extractSceneFeatures(beg);

		if (pFeatures == nullptr) {
			__printLog(std::cerr, "Failed to extract the feature!");
			return false;
		}

		/*视频检测*/

		FeaturesStorage iFS(m_featureName, m_label, (*pFeatures));
		if (!iFS.storeFeaturesFile()) {
			__printLog(std::cerr, "Failed to transform svm files!");
			return false;
		}

		beg += m_sceneInterval;

		++sceneNum;

		pFeatures.reset(new cv::Mat);
	}

	return true;
}

/*! @function
********************************************************************************
<PRE>
函数名 : __printLog
功能 : 打印信息
参数 : 
_os, 打印格式; 
_msg, 打印内容;
返回值 : ostream& 打印流
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : __printLog(cout, "Nothing");
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
std::ostream& VideoTraining::__printLog (
	std::ostream& _os, const std::string& _msg)
{
	if (std::cerr == _os) {
		_os << "Warning : " << _msg << std::endl;
	} else if (std::clog == _os) {
		_os << "Log : " << _msg << std::endl;
	} else {
		_os << "Message : " << _msg << std::endl;
	}

	return _os;
}
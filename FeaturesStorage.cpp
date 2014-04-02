/*! @file
********************************************************************************
<PRE>
模块名 : 特征存储
文件名 : FeaturesStorage.cpp
相关文件 : FeaturesStorage.h
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

#include "stdafx.h"

#include "FeaturesStorage.h"

using namespace cv;
using namespace std;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
函数名 : FeaturesStorage
功能 : 参数构造函数
参数 : 
const string& _fileName, 存储文件名;
const int _label, 标签;
const Mat& _videoFeature, 特征数组;
返回值 : 无
抛出异常 : exception, 参数错误
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : FeaturesStorage iFS(fileName, label, videoFeature);
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
FeaturesStorage::FeaturesStorage(
	const std::string& _fileName, 
	const int _label, 
	const cv::Mat& _videoFeature
) : 
	m_fileName(_fileName),
	m_label(_label),
	m_videoFeature(_videoFeature)
{
	if (_videoFeature.empty()) {
		__printLog(std::cerr, "Sorry, the video feature is empty! ");
		throw std::exception("Video Feature Error! ");
	}

	return;
}

/*! @function
********************************************************************************
<PRE>
函数名 : ~FeaturesStorage
功能 : 析构函数
参数 : void
返回值 : 无
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : iFS.~FeaturesStorage();
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
FeaturesStorage::~FeaturesStorage (void)
{
	return;
}

/*! @function
********************************************************************************
<PRE>
函数名 : storeFeaturesFile
功能 : 存储特征文件
参数 : void
返回值 : const bool, 是否成功
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : iFS.storeFeaturesFile();
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool FeaturesStorage::storeFeaturesFile (void)
{
	cv::Mat averageFeature = 
		cv::Mat::zeros(1, m_videoFeature.cols-3, CV_64FC1);

	for (int j=3; j<m_videoFeature.cols; ++j) {
		for(int i=0; i<m_videoFeature.rows; ++i) {
			averageFeature.at<double>(0, j-3) += m_videoFeature.at<double>(i, j);
		}
		averageFeature.at<double>(0, j-3) /= m_videoFeature.rows;
	}

	ofstream ofs(m_fileName, ios::app);
	ofs << m_label << " ";

	for (int i=0; i<averageFeature.cols; ++i) {	
		ofs << averageFeature.at<double>(0, i) << " ";
	}

	ofs << std::endl;

	return true;
}

/*! @function
********************************************************************************
<PRE>
函数名 : __printLog
功能 : 输出信息
参数 : 
ostream& _os, 输出格式; 
const string& _msg, 输出内容;
返回值 : ostream&;
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : __printLog(cout, "Nothing");
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
std::ostream& FeaturesStorage::__printLog (
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
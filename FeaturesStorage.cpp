/*! @file
********************************************************************************
<PRE>
ģ���� : �����洢
�ļ��� : FeaturesStorage.cpp
����ļ� : FeaturesStorage.h
�ļ�ʵ�ֹ��� : �����洢������
���� : C.L.Wang
Email: morndragon@126.com
�汾 : 1.0
--------------------------------------------------------------------------------
���̰߳�ȫ�� : ��
�쳣ʱ��ȫ�� : ��
--------------------------------------------------------------------------------
��ע : ��
--------------------------------------------------------------------------------
�޸ļ�¼ :  
�� ��              �汾   �޸���         �޸����� 
2014/04/02   1.0    C.L.Wang        ����
</PRE>
********************************************************************************

* ��Ȩ����(c) C.L.Wang, ��������Ȩ��

*******************************************************************************/ 

#include "stdafx.h"

#include "FeaturesStorage.h"

using namespace cv;
using namespace std;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
������ : FeaturesStorage
���� : �������캯��
���� : 
const string& _fileName, �洢�ļ���;
const int _label, ��ǩ;
const Mat& _videoFeature, ��������;
����ֵ : ��
�׳��쳣 : exception, ��������
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : FeaturesStorage iFS(fileName, label, videoFeature);
--------------------------------------------------------------------------------
���� : C.L.Wang
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
������ : ~FeaturesStorage
���� : ��������
���� : void
����ֵ : ��
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : iFS.~FeaturesStorage();
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
FeaturesStorage::~FeaturesStorage (void)
{
	return;
}

/*! @function
********************************************************************************
<PRE>
������ : storeFeaturesFile
���� : �洢�����ļ�
���� : void
����ֵ : const bool, �Ƿ�ɹ�
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : iFS.storeFeaturesFile();
--------------------------------------------------------------------------------
���� : C.L.Wang
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
������ : __printLog
���� : �����Ϣ
���� : 
ostream& _os, �����ʽ; 
const string& _msg, �������;
����ֵ : ostream&;
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : __printLog(cout, "Nothing");
--------------------------------------------------------------------------------
���� : C.L.Wang
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
/*! @file
********************************************************************************
<PRE>
ģ���� : ��Ƶѵ��
�ļ��� : VideoTraining.cpp
����ļ� : VideoTraining.h
�ļ�ʵ�ֹ��� : ��Ƶѵ����ʵ��
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
�� ��              �汾    �޸���         �޸����� 
2014/04/02   1.0    C.L.Wang        ����
</PRE>
********************************************************************************

* ��Ȩ����(c) C.L.Wang, ��������Ȩ��

*******************************************************************************/ 

#include "stdafx.h"

#include "VideoTraining.h"

using namespace cv;
using namespace std;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
������ : VideoTraining
���� : �������캯��
���� : 
const string& _fileName, �洢�ļ���;
const int _label, ��ǩ;
const std::string& _videoName, ��Ƶ����;
const std::size_t _shotInterval, ��ͷ���;
const std::size_t _sceneInterval, �������;
����ֵ : ��
�׳��쳣 : exception, ��������
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : VideoTraining iVT(fileName, label, videoName, shotInterval, sceneInterval);
--------------------------------------------------------------------------------
���� : C.L.Wang
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

	/*�ж��ļ��Ƿ����*/

	cv::VideoCapture iVC (m_videoName);
	if (!iVC.isOpened()) {
		__printLog(std::cerr, "Failed to open the video!");
		throw std::exception("Video Name Error");
	}

	/*��ͷ����ж�*/

	if (m_shotInterval < 1 || m_shotInterval > maxShotInterval) {
		__printLog(std::cerr, "The value of the shot interval is invalid.");
		throw std::exception("Shot Interval Error");
	}

	/*��������ж�*/

	if (m_sceneInterval < 1 || m_sceneInterval > maxSceneInterval) {
		__printLog(std::cerr, "The value of the scene interval is invalid.");
		throw std::exception("Scene Interval Error");
	}

	return;
}

/*! @function
********************************************************************************
<PRE>
������ : ~VideoTraining
���� : ��������
���� : void
����ֵ : ��
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : iVT.~VideoTraining();
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
VideoTraining::~VideoTraining(void)
{
	return;
}

/*! @function
********************************************************************************
<PRE>
������ : trainVideoFeatures
���� : ѵ����Ƶ����
���� : void
����ֵ : const bool, �Ƿ�ɹ�
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : iVT.trainVideoFeatures();
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool VideoTraining::trainVideoFeatures (void)
{
	/*�ж���Ƶ�Ƿ�ɶ�*/

	cv::VideoCapture iVC (m_videoName);

	const std::size_t framesNum(
		static_cast<std::size_t>(iVC.get(CV_CAP_PROP_FRAME_COUNT))); //��֡��

	SceneIntegration iSI(m_videoName, m_shotInterval, m_sceneInterval);

	double finalLabel (0.0); //�洢��Ƶ���
	std::size_t beg (0);
	std::size_t sceneNum(0);

	for (std::size_t j=0; j<framesNum; j+=m_sceneInterval)
	{
		/*��ȡ�ؼ�֡����*/

		std::shared_ptr<cv::Mat> pFeatures;
		pFeatures = iSI.extractSceneFeatures(beg);

		if (pFeatures == nullptr) {
			__printLog(std::cerr, "Failed to extract the feature!");
			return false;
		}

		/*��Ƶ���*/

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
������ : __printLog
���� : ��ӡ��Ϣ
���� : 
_os, ��ӡ��ʽ; 
_msg, ��ӡ����;
����ֵ : ostream& ��ӡ��
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : __printLog(cout, "Nothing");
--------------------------------------------------------------------------------
���� : C.L.Wang
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
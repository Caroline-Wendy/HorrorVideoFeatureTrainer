/*! @file
********************************************************************************
<PRE>
ģ���� : ��Ƶѵ��
�ļ��� : VideoTraining.h 
����ļ� : VideoTraining.cpp
�ļ�ʵ�ֹ��� : ��Ƶѵ��������
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

#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "SceneIntegration.h"
#include "FeaturesStorage.h"

//��Ƶ��������ռ�
namespace vd 
{

	/*! @class
	********************************************************************************
	<PRE>
	������ : VideoTraining
	���� : ��Ƶѵ��
	�쳣�� : ��
	--------------------------------------------------------------------------------
	��ע : ��
	�����÷� : VideoTraining iVT;
	--------------------------------------------------------------------------------
	���� : C.L.Wang
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
		); //���캯��

		~VideoTraining(void); //��������


	public:

		const bool trainVideoFeatures (void); //ѵ����Ƶ

	private:
		
		std::string m_featureName; //�����ļ���
		int m_label; //��ǩ
		std::string m_videoName; //��Ƶ�ļ���
		std::size_t m_shotInterval; //��ͷ���
		std::size_t m_sceneInterval; //�������

	private:

		static inline std::ostream& __printLog (
			std::ostream& _os, const std::string& _msg); //��ӡ��Ϣ

	};

}
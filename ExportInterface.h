/*! @file
********************************************************************************
<PRE>
ģ���� : �����ӿ�
�ļ��� : ExportInterface.h
����ļ� : ExportInterface.cpp
�ļ�ʵ�ֹ��� : �����ӿ�������
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
2014/03/27   1.0    C.L.Wang        Create
</PRE>
********************************************************************************

* ��Ȩ����(c) C.L.Wang, ��������Ȩ��

*******************************************************************************/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>
#include <ctime>

#include <windows.h>

#include "VideoTraining.h"

/*! @function
********************************************************************************
<PRE>
������ : trainVideoSet
���� : ѵ����Ƶ��
���� : 
const string& _featureName, �洢�����ļ�;
const int _label, ��Ƶ��ǩ;
const string& _videoSetPath, ��Ƶ����·��;
const size_t _shotInterval = 100, ��ͷ;
const size_t _sceneNum = 20, ��ͷ��;
����ֵ : const bool, �Ƿ�ɹ�
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : isOK = trainVideoSet (featureName, label, videoSetPath, shotInterval, sceneNum);
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool trainVideoSet (
	const std::string& _featureName, /*�洢�����ļ�*/
	const int _label, /*��Ƶ��ǩ*/
	const std::string& _videoSetPath, /*��Ƶ����·��*/
	const std::size_t _shotInterval = 100, /*��ͷ*/
	const std::size_t _sceneNum = 20 /*��ͷ��*/
); 
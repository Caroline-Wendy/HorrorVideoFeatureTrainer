/*! @file
********************************************************************************
<PRE>
ģ���� : ������
�ļ��� : main.cpp
����ļ� : ��
�ļ�ʵ�ֹ��� : ������ʵ��
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
����                �汾   �޸���         �޸����� 
2014/04/02   1.0    C.L.Wang        Create
</PRE>
********************************************************************************

* ��Ȩ����(c) C.L.Wang, ��������Ȩ��

*******************************************************************************/

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

#include "ExportInterface.h"

int main(void) 
{
	const std::string& featureName("NegtiveFeatureFile.txt"); /*�洢�����ļ�*/
	const int label(0); /*��Ƶ��ǩ*/
	const std::string& videoSetPath("E:/Work/violence/�������и�"); /*��Ƶ����·��*/
	const std::size_t shotInterval = 100; /*��ͷ*/
	const std::size_t sceneNum = 20; /*��ͷ��*/

	if (!trainVideoSet (featureName, label, videoSetPath, shotInterval, sceneNum)) {
		std::cout << "Error! " << std::endl;
	} else {
		std::cout << "Over! " << std::endl;
	}

	return 0;
}

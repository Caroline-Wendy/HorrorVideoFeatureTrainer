/*! @file
********************************************************************************
<PRE>
模块名 : 主函数
文件名 : main.cpp
相关文件 : 无
文件实现功能 : 主函数实现
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
日期                版本   修改人         修改内容 
2014/04/02   1.0    C.L.Wang        Create
</PRE>
********************************************************************************

* 版权所有(c) C.L.Wang, 保留所有权利

*******************************************************************************/

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

#include "ExportInterface.h"

int main(void) 
{
	const std::string& featureName("NegtiveFeatureFile.txt"); /*存储特征文件*/
	const int label(0); /*视频标签*/
	const std::string& videoSetPath("E:/Work/violence/负样本切割"); /*视频集合路径*/
	const std::size_t shotInterval = 100; /*镜头*/
	const std::size_t sceneNum = 20; /*镜头数*/

	if (!trainVideoSet (featureName, label, videoSetPath, shotInterval, sceneNum)) {
		std::cout << "Error! " << std::endl;
	} else {
		std::cout << "Over! " << std::endl;
	}

	return 0;
}

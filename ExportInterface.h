/*! @file
********************************************************************************
<PRE>
模块名 : 导出接口
文件名 : ExportInterface.h
相关文件 : ExportInterface.cpp
文件实现功能 : 导出接口类声明
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
2014/03/27   1.0    C.L.Wang        Create
</PRE>
********************************************************************************

* 版权所有(c) C.L.Wang, 保留所有权利

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
函数名 : trainVideoSet
功能 : 训练视频集
参数 : 
const string& _featureName, 存储特征文件;
const int _label, 视频标签;
const string& _videoSetPath, 视频集合路径;
const size_t _shotInterval = 100, 镜头;
const size_t _sceneNum = 20, 镜头数;
返回值 : const bool, 是否成功
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : isOK = trainVideoSet (featureName, label, videoSetPath, shotInterval, sceneNum);
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool trainVideoSet (
	const std::string& _featureName, /*存储特征文件*/
	const int _label, /*视频标签*/
	const std::string& _videoSetPath, /*视频集合路径*/
	const std::size_t _shotInterval = 100, /*镜头*/
	const std::size_t _sceneNum = 20 /*镜头数*/
); 
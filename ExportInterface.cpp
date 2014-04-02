/*! @file
********************************************************************************
<PRE>
模块名 : 导出接口
文件名 : ExportInterface.cpp
相关文件 : ExportInterface.h
文件实现功能 : 导出接口类实现
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

#include "stdafx.h"

#undef UNICODE

#include "ExportInterface.h"

using namespace std;
using namespace cv;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
函数名 : dfsFileList
功能 : 深度优先遍历文件夹
参数 : const std::string& _folderPath, 文件夹路径;
返回值 : shared_ptr<vector<string> > , 文件集合;
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : pvs = dfsFileList (folderPath);
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
std::shared_ptr<std::vector<std::string> > dfsFileList(const std::string& _folderPath)
{
	static std::shared_ptr<std::vector<std::string> > 
		folderFiles(new std::vector<std::string>); //返回指针, 需要迭代使用

	WIN32_FIND_DATA FindData;
	HANDLE hError;

	int file_count(0);
	std::string filePath(_folderPath); //路径名
	std::string fullFilePath; //全路径名 

	filePath.append("/*.*");
	hError = FindFirstFile(filePath.c_str(), &FindData);
	if (hError == INVALID_HANDLE_VALUE) {
		std::cout << "failed to search files." << std::endl;
		return nullptr;
	}
	while(FindNextFile(hError, &FindData))
	{
		//过虑".", "..", "-q"
		if (0 == strcmp(FindData.cFileName, ".") || 
			 0 == strcmp(FindData.cFileName, "..") || 
			 0 == strcmp(FindData.cFileName, "-q"))
		{
			continue;
		}

		//完整路径
		fullFilePath.append(_folderPath);
		fullFilePath.append("/");
		fullFilePath.append(FindData.cFileName);
		++file_count;

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			//std::cout << file_count << " " << full_file_path << "<Dir>" << std::endl;
			dfsFileList(fullFilePath);
		}else{
			folderFiles->push_back(fullFilePath);
			//std::cout << file_count << " " << full_file_path << std::endl;
		}
		fullFilePath.clear(); //清空目录
	}

	return folderFiles;
}

/*! @function
********************************************************************************
<PRE>
函数名 : trainVideo
功能 : 训练视频
参数 : 
const string& _featureName, 存储特征文件;
const int _label, 视频标签;
const string& _videoName, 视频名称;
const size_t _shotInterval = 100, 镜头;
const size_t _sceneNum = 20, 镜头数;
返回值 : const bool, 是否成功
抛出异常 : 无
--------------------------------------------------------------------------------
复杂度 : 无
备注 : 无
典型用法 : isOK = transVideo (featureName, label, videoName, shotInterval, sceneNum);
--------------------------------------------------------------------------------
作者 : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool transVideo(
	const std::string& _featureName, /*存储特征文件*/
	const int _label, /*视频标签*/
	const std::string& _videoName, /*视频名称*/
	const std::size_t _shotInterval = 100, /*镜头*/
	const std::size_t _sceneInterval = 2000 /*镜头数*/
) 
{
	const std::string& featureName(_featureName);
	const int label(_label);
	const std::string videoName(_videoName);
	const unsigned int shotInterval(_shotInterval);
	const unsigned int sceneInterval(_sceneInterval);

	VideoTraining iVT(featureName, label, videoName, shotInterval, sceneInterval);
	if (!iVT.trainVideoFeatures()) {
		std::cout << "Failed to train video : " << _videoName << std::endl;
		return false;
	}

	return true;
}

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
	const std::size_t _shotInterval, /*镜头*/
	const std::size_t _sceneNum  /*镜头数*/
) 
{
	const std::string& featureName(_featureName);
	const int label(_label);
	const std::string videoSetPath(_videoSetPath);
	const unsigned int shotInterval(_shotInterval);
	const unsigned int sceneInterval(_shotInterval*_sceneNum);

	std::shared_ptr<std::vector<std::string> > folderFiles;
	folderFiles = dfsFileList(videoSetPath);
	if (folderFiles) 
	{
		for (size_t i=0; i != folderFiles->size(); ++i) {
			std::cout << i+1 << " : " << (*folderFiles)[i] << std::endl;

			clock_t start = clock();
			if (!transVideo(featureName, label, (*folderFiles)[i], shotInterval, sceneInterval)){
				return false;
			}
			clock_t end = clock(); 

			double time = static_cast<double>(end-start)/CLOCKS_PER_SEC; 
			std::cout << " time = " << time << std::endl;
		}
	}

	return true;
}
/*! @file
********************************************************************************
<PRE>
ģ���� : �����ӿ�
�ļ��� : ExportInterface.cpp
����ļ� : ExportInterface.h
�ļ�ʵ�ֹ��� : �����ӿ���ʵ��
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

#include "stdafx.h"

#undef UNICODE

#include "ExportInterface.h"

using namespace std;
using namespace cv;
using namespace vd;

/*! @function
********************************************************************************
<PRE>
������ : dfsFileList
���� : ������ȱ����ļ���
���� : const std::string& _folderPath, �ļ���·��;
����ֵ : shared_ptr<vector<string> > , �ļ�����;
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : pvs = dfsFileList (folderPath);
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
std::shared_ptr<std::vector<std::string> > dfsFileList(const std::string& _folderPath)
{
	static std::shared_ptr<std::vector<std::string> > 
		folderFiles(new std::vector<std::string>); //����ָ��, ��Ҫ����ʹ��

	WIN32_FIND_DATA FindData;
	HANDLE hError;

	int file_count(0);
	std::string filePath(_folderPath); //·����
	std::string fullFilePath; //ȫ·���� 

	filePath.append("/*.*");
	hError = FindFirstFile(filePath.c_str(), &FindData);
	if (hError == INVALID_HANDLE_VALUE) {
		std::cout << "failed to search files." << std::endl;
		return nullptr;
	}
	while(FindNextFile(hError, &FindData))
	{
		//����".", "..", "-q"
		if (0 == strcmp(FindData.cFileName, ".") || 
			 0 == strcmp(FindData.cFileName, "..") || 
			 0 == strcmp(FindData.cFileName, "-q"))
		{
			continue;
		}

		//����·��
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
		fullFilePath.clear(); //���Ŀ¼
	}

	return folderFiles;
}

/*! @function
********************************************************************************
<PRE>
������ : trainVideo
���� : ѵ����Ƶ
���� : 
const string& _featureName, �洢�����ļ�;
const int _label, ��Ƶ��ǩ;
const string& _videoName, ��Ƶ����;
const size_t _shotInterval = 100, ��ͷ;
const size_t _sceneNum = 20, ��ͷ��;
����ֵ : const bool, �Ƿ�ɹ�
�׳��쳣 : ��
--------------------------------------------------------------------------------
���Ӷ� : ��
��ע : ��
�����÷� : isOK = transVideo (featureName, label, videoName, shotInterval, sceneNum);
--------------------------------------------------------------------------------
���� : C.L.Wang
</PRE>
*******************************************************************************/ 
const bool transVideo(
	const std::string& _featureName, /*�洢�����ļ�*/
	const int _label, /*��Ƶ��ǩ*/
	const std::string& _videoName, /*��Ƶ����*/
	const std::size_t _shotInterval = 100, /*��ͷ*/
	const std::size_t _sceneInterval = 2000 /*��ͷ��*/
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
	const std::size_t _shotInterval, /*��ͷ*/
	const std::size_t _sceneNum  /*��ͷ��*/
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

#include "ConfigManager.h"
#include <iostream>

FileManager::FileManager()
{  
}

FileManager::~FileManager()
{
	if (fileStream.is_open())
	{
		Close();
	}
}

void FileManager::Open(const std::string& strFileName)
{
	if (!fileStream.is_open())
	{
		fileStream.open(strFileName.c_str(), std::fstream::in | std::fstream::out);
	} 
}

void FileManager::Write(const std::string& writeData)
{	   
	fileStream << writeData << "\n";	
}

void FileManager::Read()
{
	std::string fileData;
	std::map<std::string, std::string> redisMap;

	while (std::getline(fileStream, fileData))
	{
		std::cout << " file Data : " << fileData;
		std::string key = fileData.substr(0,fileData.find_first_of(" "));
		std::string value = fileData.substr(fileData.find_first_of(" "), fileData.length());

		if (!key.empty())
		{
			redisMap[key] = value;
		}  		
	}
	Close();
}

void FileManager::Close()
{
	fileStream.close();
}


//******************************************************************************

ConfigManager* ConfigManager::mInstance = 0;

//******************************************************************************

ConfigManager* ConfigManager::getInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new ConfigManager();
	}
	return mInstance;
}

void ConfigManager::releaseInstance()
{
	delete mInstance;
	mInstance = NULL;	  
}

ConfigManager::ConfigManager()
{ 	
}

void ConfigManager::SetFilePath(const std::string aFileName)
{  
	fileName=aFileName;
	openFile();
}

void ConfigManager::openFile()
{
	try
	{
		fileManager.Open(fileName);
	}
	catch (std::ifstream::failure& ex)
	{
		// throw an error message 
	}
}

void ConfigManager::ReadFromFile()
{
	fileManager.Open(fileName);
	fileManager.Read();
}

void ConfigManager::WriteToFile(const std::string& writeData)
{
	fileManager.Open(fileName);
	fileManager.Write(writeData);
	fileManager.Close();
}

void ConfigManager::updateMap(const std::string aKey, const std::string aValue)
{
	redisMap[aKey] = aValue;
}


std::vector<std::string> ConfigManager::getMap()
{
	std::vector< std::string>mapValue;	  

	for (auto& av : redisMap)
	{
		std::string strMap;
		strMap = av.first;
		strMap += " ";
		strMap += av.second;
		mapValue.push_back(strMap);
	}							   
	return mapValue;
}
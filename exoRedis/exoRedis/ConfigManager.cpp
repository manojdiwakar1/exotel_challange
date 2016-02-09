
#include "ConfigManager.h"

FileManager::FileManager()
{  
}

FileManager::~FileManager()
{
	if (fileStream.is_open())
	{
		fileStream.close();
	}
}

void FileManager::Open(const std::string& strFileName)
{
	fileStream.open(strFileName.c_str(), std::fstream::out);
}

ConfigManager::ConfigManager(const std::string& fileName)
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
#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <string>
#include <fstream>
#include <exception>

class FileManager
{
public:
	FileManager();
	~FileManager();
public:
	void Open(const std::string& strFileName);
	void Write();
	void GetFileData();
	void Read(std::string& strFileName);
	void Close();
private:
	std::string fileData;
	std::fstream fileStream;
};

class ConfigManager
{
public:
	ConfigManager(const std::string& fileName);
private:
	FileManager fileManager;
};

#endif
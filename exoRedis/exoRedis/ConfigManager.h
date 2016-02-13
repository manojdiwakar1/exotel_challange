#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <vector>

class FileManager
{
public:
	FileManager();
	~FileManager();
public:
	void Open(const std::string& strFileName);
	void Write(const std::string& writeData);

	void Read();
	void Close();
private:
	std::string fileData;
	std::fstream fileStream;
};

class ConfigManager
{
public:
	ConfigManager();

	void WriteToFile(const std::string& fileName);
	void ReadFromFile();

	static ConfigManager* getInstance();
	static void releaseInstance();
	void SetFilePath(const std::string aFileName);
	void updateMap(const std::string aKey, const std::string aValue);
	std::vector<std::string> getMap();
private:
	void openFile();

	static ConfigManager* mInstance;
	FileManager fileManager;

	std::map<std::string, std::string> redisMap;

	std::string fileName;
};

#endif
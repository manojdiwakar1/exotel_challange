#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <string>
#include <fstream>
#include <exception>
#include <map>
#include <vector>
#include <algorithm>

class FileManager
{
public:
	FileManager();
	~FileManager();
public:
	void Open(const std::string& strFileName);
	void Write(const std::string& writeData);
	void Close();

	std::map<std::string, std::multimap<int, std::string> > Read();
private:
	std::string fileData;
	std::fstream fileStream;

	std::multimap<int, std::string> Tokanizestring(const std::string& inputCMD, const std::string& delimiters = " ");
};

class ConfigManager
{
public:
	ConfigManager();

	void WriteToFile(const std::string& fileName);
	void ReadFromFile();

	static ConfigManager* getInstance();
	static void releaseInstance();
	void SetFilePath(const std::string& aFileName);
	void updateMap(const std::string& aKey, const std::string aValue);
	void updateMap(const std::string& aKey, const std::multimap<int, std::string>& aValueVec);

	std::string getMap();
	std::multimap<int, std::string> getKeyValue(const std::string aKey);
	bool getKey(const std::string& aKey);
	int KeyCount(const std::string& aKey, const std::string aValue1, const std::string aValue2);
	std::vector<std::string> KeyRange(const std::string& aKey, const std::string aValue1, const std::string aValue2);

private:
	void openFile();

	static ConfigManager* mInstance;
	FileManager fileManager;

	std::map<std::string, std::multimap<int, std::string> > redisMap;	

	std::string fileName; 
};

#endif

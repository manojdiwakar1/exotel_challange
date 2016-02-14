
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

std::map<std::string, std::multimap<int, std::string>> FileManager::Read()
{
	std::string fileData;
	std::map<std::string, std::multimap<int, std::string>> localMap;

	std::cout << " file Data : " << "\n";
	while (std::getline(fileStream, fileData))
	{
		if (fileData.empty())
		{
			continue;
		}

		std::cout << fileData<<"\n";
		std::string key = fileData.substr(0,fileData.find_first_of(" "));
		std::multimap<int, std::string> value = Tokanizestring(fileData.substr(fileData.find_first_of(" "), fileData.length()));

		if (!key.empty())
		{
			localMap[key] = value;
		}  		
	}
	std::cout << "\n";
	Close();
	return localMap;
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

void ConfigManager::SetFilePath(const std::string& aFileName)
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
		std::cout << " Exception : " << ex.what();
	}
	catch (std::exception& ex)
	{
		std::cout << " Exception : " << ex.what();
	}
}

void ConfigManager::ReadFromFile()
{
	fileManager.Open(fileName);
	redisMap = fileManager.Read();
}

void ConfigManager::WriteToFile(const std::string& writeData)
{
	fileManager.Open(fileName);
	fileManager.Write(writeData);
}

void ConfigManager::updateMap(const std::string& aKey, const std::string aValue)
{
	int i = 1;
	std::multimap<int, std::string> myMap;
	std::pair<int, std::string> mapPair(i, aValue);

	myMap.insert(mapPair);	
	redisMap[aKey] = myMap; 
}

void ConfigManager::updateMap(const std::string& aKey, const std::multimap<int, std::string>& aValueVec)
{
	std::multimap<int, std::string> tmp;
	tmp = getKeyValue(aKey);
	for (auto& av : aValueVec)
	{
		std::pair<int, std::string> mapPair(av.first, av.second);
		tmp.insert(mapPair);
	}

	// update the redisMap.
	redisMap[aKey] = tmp;
}


std::multimap<int, std::string> ConfigManager::getKeyValue(const std::string aKey)
{
	std::multimap<int, std::string> rec; 
	std::map<std::string, std::multimap<int, std::string> >::iterator it;

	it = redisMap.find(aKey);
	if (it != redisMap.end())
	{
		rec = it->second;
	}
	else
	{
		std::cerr << "\n Key : " << aKey << " not found \n";
	}
	return rec;
}


bool ConfigManager::getKey(const std::string& aKey)
{
	bool res = false;

	std::map<std::string, std::multimap<int, std::string> >::iterator it;
	it = redisMap.find(aKey);
	if (it != redisMap.end())
	{
		res = true;
	}
	else
	{
		std::cerr << "\n Key : " << aKey << " not found \n";
	}

	return res;
}

int ConfigManager::KeyCount(const std::string& aKey, const std::string aValue1, const std::string aValue2)
{
	int res = 0;
	if (getKey(aKey))
	{
		std::multimap<int, std::string> value = getKeyValue(aKey);

		std::multimap<int, std::string>::iterator it1;

		if (!(aValue1.substr(0, 1)).compare("-"))
		{
			it1 = value.begin();
		}
		else if (!(aValue1.substr(0, 1)).compare("+"))
		{
			it1 = value.find(std::stoi(aValue1.substr(1, aValue1.length())));
		}
		else
		{
			it1 = value.find(std::stoi(aValue1));
		}
					
		std::multimap<int, std::string>::iterator it2 = value.find(std::stoi(aValue2));

		if (it1 != value.end() && it2 != value.end())
		{
			for (it1; it1 == it2; it1++)
			{
				res++;
			}
		}
	}
	else
	{
		std::cerr << "\n Key : " << aKey << " not found \n";
	}

	return res;
}

std::vector<std::string> ConfigManager::KeyRange(const std::string& aKey, const std::string aValue1, const std::string aValue2)
{
	int res = 0;
	std::vector<std::string>scoreValue;

	if (getKey(aKey))
	{
		std::multimap<int, std::string> value = getKeyValue(aKey);

		std::multimap<int, std::string>::iterator it1;
		std::multimap<int, std::string>::iterator it2;
		

		if (!(aValue1.substr(0, 1)).compare("-"))
		{
			it1 = value.begin();
				
		}
		else if (!(aValue2.substr(0, 1)).compare("-"))
		{
			it2 = value.end();
		}
		else if (!(aValue1.substr(0, 1)).compare("+") )
		{
			it1 = value.find(std::stoi(aValue1.substr(1, aValue1.length())));
			
		}
		else if (!(aValue2.substr(0, 1)).compare("+"))
		{
			it2 = value.find(std::stoi(aValue2.substr(1, aValue2.length())));
		}
		else
		{
			it1 = value.find(std::stoi(aValue1));
			it2 = value.find(std::stoi(aValue2));
		}

		for (it1; it1 != it2; it1++)
		{
			scoreValue.push_back(it1->second);
		}
	}
	else
	{
		std::cerr << "\n Key : " << aKey << " not found \n";
	}

	if (scoreValue.size())
	{
		std::sort(scoreValue.begin(), scoreValue.end());
	}
	

	return scoreValue;
}

std::string ConfigManager::getMap()
{
	std::string mapValue;	  

	for (auto& av : redisMap)
	{
		std::string strMap;
		strMap = av.first;
		strMap += " ";

		for (auto& avs : av.second)
		{		
			strMap += std::to_string((int)avs.first);
			strMap += " ";
			strMap += avs.second;
			strMap += " ";
		}
		strMap += '\n';
		mapValue.append(strMap);
	}							   
	return mapValue;
}


std::multimap<int, std::string> FileManager::Tokanizestring(const std::string& inputCMD, const std::string& delimiters)
{
	std::multimap<int, std::string> mapValue;
	std::vector<std::string> tmp;
	mapValue.clear();

	// Skip delimiters at beginning.
	std::string::size_type lastPos = inputCMD.find_first_not_of(delimiters, 0);

	// Find first "non-delimiter".
	std::string::size_type pos = inputCMD.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tmp.push_back(inputCMD.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = inputCMD.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = inputCMD.find_first_of(delimiters, lastPos);
	}

	for (unsigned int i = 0; i < tmp.size(); i+= 2)
	{
		int key = std::stoi(tmp[i]);
		std::pair<int, std::string> mapPair(key, tmp[i + 1]);	 
		mapValue.insert(mapPair);
	}

	return mapValue;
}
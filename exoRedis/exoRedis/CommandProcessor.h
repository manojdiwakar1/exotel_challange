#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>
#include "ConfigManager.h"

class CommandProcessor
{
public:
	CommandProcessor();
	bool ProcessCMD(const std::string& inputCMD);
	void executeCMD(const std::string& inputCMD);
private: 
	void ConstructCmd();
	bool validateCMD(const std::string& inputCMD);
	std::string GetCMD(const std::string& inputCMD);

	void executeGetCmd(const std::string& inputCMD);
	void executeSetCmd(const std::string& inputCMD);
	void executeSaveCmd();
	void executeZaddCmd(const std::string& inputCMD);
	void executeZcardCmd(const std::string& inputCMD);
	void executeZcountCmd(const std::string& inputCMD);
	void executeZrangeCmd(const std::string& inputCMD);	 

	void TokanizeCmd(const std::string& inputCMD, const std::string& delimiters = " ");
	bool IsValidInt(const char* x);

	std::vector<std::string>cmd;
	std::vector<std::string>cmdTokens;
	std::string command;

	ConfigManager* configManager;
};

#endif
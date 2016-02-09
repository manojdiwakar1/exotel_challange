#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <vector>

class CommandProcessor
{
public:
	CommandProcessor();
	void ProcessCMD(std::string& inputCMD);
private: 
	void ConstructCmd();
	bool validateCMD(const std::string& inputCMD);

	std::vector<std::string>cmd;
	std::string command;
};

#endif
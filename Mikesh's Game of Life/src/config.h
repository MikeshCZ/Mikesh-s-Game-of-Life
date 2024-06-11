#pragma once
#include <string>

class Config
{
public:
	Config() = default;
	// Inicialization of the confing reading. If file not exist create the default one
	int	Initialization();
	// Return config file name
	std::string	GetFileName();

private:
	// Create default config to the file
	void CreateDefaultConfigFile();
	// config file name
	const std::string configFilename = "ini/config.ini";
};


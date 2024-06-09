#pragma once
#include <string>

class Config
{
public:
				Config() = default;
	int			Initialization();
	std::string	GetFileName();

private:
	void				CreateDefaultConfigFile();
	const std::string	configFilename = "config.ini";
};


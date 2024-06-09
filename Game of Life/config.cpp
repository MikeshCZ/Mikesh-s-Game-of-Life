#include "config.h"
#include <INIReader.h>
#include <iostream>
#include <fstream>

int Config::Initialization()
{
	std::ifstream infile(configFilename);
	if (!infile.good()) {
		std::cout << "Config file not found, creating default config file...\n";
		CreateDefaultConfigFile();
	}

	INIReader reader(configFilename);

	if (reader.ParseError() < 0) {
		std::cout << "Can't load '" + configFilename + "'\n";
		return 1;
	}
	else
	{
		return 0;
	}
}

std::string Config::GetFileName()
{
	return configFilename;
}

void Config::CreateDefaultConfigFile()
{
	std::ofstream file(configFilename);
	if (file.is_open()) {
		file << "[window]\n";
		file << "width=1280\n";
		file << "height=720\n";
		file << "fps=30\n";
		file << "fullscreen=false\n";
		file << "[cell]\n";
		file << "size=5\n";
		file << "edgeColorR=60\n";
		file << "edgeColorG=60\n";
		file << "edgeColorB=60\n";
		file << "edgeColorA=255\n";
		file << "edgeWidth=1\n";
		file << "randomColors=true\n";
		file.close();
	}
	else {
		std::cerr << "Unable to create config file: " << configFilename << std::endl;
	}
}

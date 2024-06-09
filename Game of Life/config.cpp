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
		file << "width=1280				; 2560, 1920\n";
		file << "height=720				; 1440, 1080\n";
		file << "fps=30	 				; target FPS\n";
		file << "fullscreen=false		; start with fullscreen\n";
		file << "[cell]\n";
		file << "size=5					; cell size\n";
		file << "edgeColorR=60			; cell edge color RED\n";
		file << "edgeColorG=60			; cell edge color GREEN\n";
		file << "edgeColorB=60			; cell edge color BLUE\n";
		file << "edgeWidth=1				; default cell edge width\n";
		file << "randomColors=true		; default random color effect\n";
		file.close();
	}
	else {
		std::cerr << "Unable to create config file: " << configFilename << std::endl;
	}
}

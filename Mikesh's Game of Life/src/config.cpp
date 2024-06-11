#include "config.h"
#include <INIReader.h>
#include <iostream>
#include <filesystem>
#include <fstream>

int Config::Initialization()
{
	std::string dir = "ini";	// folder for ini file

	if (!std::filesystem::exists(dir)) {	// If the folder does not exist, we will try to create it
		if (std::filesystem::create_directory(dir)) {
			std::cout << "Folder 'ini' was successfully created." << std::endl;
		}
		else {
			std::cerr << "Error creating the 'ini' folder." << std::endl;
			return 1;
		}
	}
	else {
		std::cout << "The 'ini' folder already exists." << std::endl;
	}
	
	std::ifstream infile(configFilename); // Check if the ini file exist
	if (!infile.good()) {
		std::cout << "Config file not found, creating default config file...\n";
		CreateDefaultConfigFile();
	}

	INIReader reader(configFilename); // Reader for config file

	if (reader.ParseError() < 0) { // Can't load the file
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
		file << "width			= 1280		; 2560, 1920\n";
		file << "height			= 720		; 1440, 1080\n";
		file << "fps				= 30		; target FPS\n";
		file << "fullscreen		= false		; start with fullscreen\n";
		file << "\n[cell]\n";
		file << "size			= 5			; cell size\n";
		file << "edgeWidth		= 1			; default cell edge width\n";
		file << "randomColors	= true		; default random color effect\n";
		file << "randomSize		= 10		; random color +/- range\n";
		file << "\n[color]\n";
		file << "liveColorR		= 0			; live cell color RED\n";
		file << "liveColorG		= 170		; live cell color GREEN\n";
		file << "liveColorB		= 170		; live cell color BLUE\n";
		file << "liveColorA		= 255		; live cell color ALPHA\n";
		file << "deadColorR		= 140		; dead cell color RED\n";
		file << "deadColorG		= 100		; dead cell color GREEN\n";
		file << "deadColorB		= 80		; dead cell color BLUE\n";
		file << "deadColorA		= 130		; dead cell color APLHA\n";
		file << "edgeColorR		= 60		; cell edge and background color RED\n";
		file << "edgeColorG		= 60		; cell edge and background color GREEN\n";
		file << "edgeColorB		= 60		; cell edge and background color BLUE\n";
		file.close();
	}
	else {
		std::cerr << "Unable to create config file: " << configFilename << std::endl;
	}
}
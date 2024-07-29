#include <fstream>
#include <iostream>
#include <raylib.h>
#include <sstream>

using namespace std;

// Define a struct to hold settings
struct Settings
{
  int width;
  int height;
  int fps;
  bool fullscreen;
  bool music;
  bool playIntro;
  int size;
  int edgeWidth;
  bool randomColors;
  int randomSize;
  int liveColorR;
  int liveColorG;
  int liveColorB;
  int liveColorA;
  int deadColorR;
  int deadColorG;
  int deadColorB;
  int deadColorA;
  int edgeColorR;
  int edgeColorG;
  int edgeColorB;
  
  void Startup();
  // Save settings to file
  void SaveSettings (const string &filename);
  // Load settings from file
  bool LoadSettings (const string &filename);
};
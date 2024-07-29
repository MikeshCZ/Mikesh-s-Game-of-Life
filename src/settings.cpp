#include "settings.hpp"

void
Settings::Startup ()
{
  if (!LoadSettings ("config.ini"))
    {
      SaveSettings ("config.ini");
      cerr << "Using default " << endl;
    }
}

void
Settings::SaveSettings (const string &filename)
{
  ofstream file (filename);
  if (file.is_open ())
    {
      file << "width: " << width << endl;
      file << "height: " << height << endl;
      file << "fps: " << fps << endl;
      file << "fullscreen: " << (fullscreen ? "true" : "false") << endl;
      file << "music: " << (music ? "true" : "false") << endl;
      file << "playIntro: " << (playIntro ? "true" : "false") << endl;
      file << "size: " << size << endl;
      file << "edgeWidth: " << edgeWidth << endl;
      file << "randomColors: " << (randomColors ? "true" : "false") << endl;
      file << "randomSize: " << randomSize << endl;
      file << "liveColorR: " << liveColorR << endl;
      file << "liveColorG: " << liveColorG << endl;
      file << "liveColorB: " << liveColorB << endl;
      file << "liveColorA: " << liveColorA << endl;
      file << "deadColorR: " << deadColorR << endl;
      file << "deadColorG: " << deadColorG << endl;
      file << "deadColorB: " << deadColorB << endl;
      file << "deadColorA: " << deadColorA << endl;
      file << "edgeColorR: " << edgeColorR << endl;
      file << "edgeColorG: " << edgeColorG << endl;
      file << "edgeColorB: " << edgeColorB << endl;
      file.close ();
    }
  else
    {
      cerr << "Unable to open file for writing: " << filename << endl;
    }
}

bool
Settings::LoadSettings (const string &filename)
{
  ifstream file (filename);
  if (file.is_open ())
    {
      string line;
      while (getline (file, line))
        {
          istringstream iss (line);
          string key;
          if (getline (iss, key, ':'))
            {
              string value;
              if (getline (iss, value))
                {
                  value.erase (0, value.find_first_not_of (" \t"));
                  if (key == "width")
                    {
                      width = stoi (value);
                    }
                  else if (key == "height")
                    {
                      height = stoi (value);
                    }
                  else if (key == "fps")
                    {
                      fps = stoi (value);
                    }
                  else if (key == "fullscreen")
                    {
                      fullscreen = (value == "true");
                    }
                  else if (key == "music")
                    {
                      music = (value == "true");
                    }
                  else if (key == "playIntro")
                    {
                      playIntro = (value == "true");
                    }
                  else if (key == "size")
                    {
                      size = stoi (value);
                    }
                  else if (key == "edgeWidth")
                    {
                      edgeWidth = stoi (value);
                    }
                  else if (key == "randomColors")
                    {
                      randomColors = (value == "true");
                    }
                  else if (key == "randomSize")
                    {
                      randomSize = stoi (value);
                    }
                  else if (key == "liveColorR")
                    {
                      liveColorR = stoi (value);
                    }
                  else if (key == "liveColorG")
                    {
                      liveColorG = stoi (value);
                    }
                  else if (key == "liveColorB")
                    {
                      liveColorB = stoi (value);
                    }
                  else if (key == "liveColorA")
                    {
                      liveColorA = stoi (value);
                    }
                  else if (key == "deadColorR")
                    {
                      deadColorR = stoi (value);
                    }
                  else if (key == "deadColorG")
                    {
                      deadColorG = stoi (value);
                    }
                  else if (key == "deadColorB")
                    {
                      deadColorB = stoi (value);
                    }
                  else if (key == "deadColorA")
                    {
                      deadColorA = stoi (value);
                    }
                  else if (key == "edgeColorR")
                    {
                      edgeColorR = stoi (value);
                    }
                  else if (key == "edgeColorG")
                    {
                      edgeColorG = stoi (value);
                    }
                  else if (key == "edgeColorB")
                    {
                      edgeColorB = stoi (value);
                    }
                }
            }
        }
      file.close ();
      return true;
    }
  else
    {
      cerr << "Unable to open file for reading: " << filename << endl;
      return false;
    }
}

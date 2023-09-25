#pragma once
#include "raylib.h"
#include <string>
#include <vector>
class Config{
	public:
		Config();
		Font getFont(int i);
		Color getColor(int i);
		Texture2D* getImg(int i);
	private:
		std::vector<Font> fonts;
		std::vector<Color> colorPallet;
		std::vector<Texture2D> img;
};
	

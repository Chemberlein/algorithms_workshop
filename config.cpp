#include "config.h"

Config::Config(){
	fonts.push_back(LoadFontEx("assets/fonts/Ubuntu-Regular.ttf",16,0,250));
	fonts.push_back(LoadFontEx("assets/fonts/Ubuntu-Regular.ttf",8,0,250));
	colorPallet.push_back(BLACK);
	colorPallet.push_back(WHITE);
	colorPallet.push_back(GRAY);
	Texture2D tmp = LoadTexture("assets/img/logo.png");
	img.push_back(tmp);
	Texture2D tmp2 = LoadTexture("assets/img/info.png");
	img.push_back(tmp2);
}
Font Config::getFont(int i){
	if(i>=fonts.size())
		return fonts[0];
	else
		return fonts[i];
}
Texture2D* Config::getImg(int i){
	return &img[i];
}
Color Config::getColor(int i){
	if(i>=colorPallet.size())
		return colorPallet[0];
	else
		return colorPallet[i];
}


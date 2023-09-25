#pragma once
#include <string>
#include <vector>
#include <map>
#include "raylib.h"
#include <tuple>
#include "element.h"
#include "config.h"
enum class LayoutType{
	VERTICALLAYOUT,
	HORIZONTALLAYOUT,
	CANVAS
};
class Config;
class Element;
class Scene{
	public:
		Scene(LayoutType l);
		~Scene()= default;
		// TODO mange copy and move constractors 
		void draw();
		void setDimentions(int width,int height);
		void addElement(Element* elem);
		void setConfig(Config *c);
		Element* mouseAction(Vector2 mp);
	private:
		int width;
		int height;
		Element* layout;
		Config* conf;
};

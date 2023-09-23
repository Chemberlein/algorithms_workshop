#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <map>
#include "scene.h"
#include "element.h"
#include "config.h"
class Scene;
class Config;
class App{
	public:
		App();
		App(int width,int height,std::string title, bool windowResizeble);
		~App() noexcept;
		// TODO delete copy constructer and move constracter as well;
		void run();
		void add(Scene* scene,std::string name);
		void setScene(std::string name);
	private:
		int height=800;
		int width=600;
		std::string title = "";
		bool windowResizeble = true;
		int targetFPS=120;
		Config* conf;
		void tick();
		void draw();
		void update();
		void windowResizeTreatment();
		Scene* current=NULL;
		std::map<std::string, Scene*> scenes;
		Element* onFocus=NULL;	
		void mouseAction();
		void keyboardAction();
		bool windowWasCreated=false;
};

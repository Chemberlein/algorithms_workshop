#include <map>
#include <string>
#include <vector>
#include "app.h"
#include "scene.h"
#include "raylib.h"
#include "element.h"
App::App(){
	// Takes initial values from class definition
}
App::App(int width,int height,std::string title,bool windowResizeble):width(width),height(height),title(title),windowResizeble(windowResizeble){
	// Takes initial values from input
}
App::~App(){
	delete conf;
	if(windowWasCreated){
		CloseWindow();
	}
}
void App::run(){
	if(windowResizeble){
		SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	}
	InitWindow(width,height,title.c_str());
	SetTargetFPS(targetFPS);
	conf = new Config();
	for(auto i:scenes){
		i.second->setConfig(conf);
	}
	while(!WindowShouldClose()){
		tick();
	}	
}

void App::tick(){
	update();
	draw();
}

void App::windowResizeTreatment(){
	if(IsWindowResized() && !IsWindowFullscreen()){
		width= GetScreenWidth();
		height= GetScreenHeight();
		if(current)
			current->setDimentions(width,height);
	}
	if(IsKeyPressed(KEY_F11)){
		int display = GetCurrentMonitor();
		if(IsWindowFullscreen()){
			SetWindowSize(width,height);
		}else{
			SetWindowSize(GetMonitorWidth(display),GetMonitorHeight(height));
		}
		ToggleFullscreen();
	}
}

void App::draw(){
	BeginDrawing();
	if(current!=NULL){
		current->draw();
	}
	EndDrawing();
}

void App:: mouseAction(){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		Vector2 mousePoint = { 0.0f, 0.0f };
		mousePoint = GetMousePosition();
		Element* newOnFocus;
		newOnFocus = current->mouseAction(mousePoint);
		if(newOnFocus!=onFocus && onFocus!=NULL)
			onFocus->stopFocus();
		onFocus = newOnFocus;
	}
}

void App::keyboardAction(){
	int key = GetCharPressed();
	if(key!= 0 && onFocus!= NULL){
		onFocus->charPressed(key);
	}
	if(IsKeyDown(KEY_BACKSPACE)&&onFocus!=NULL){
		onFocus->keyPressed(KEY_BACKSPACE);
	}
	if(IsKeyDown(KEY_ENTER)&&onFocus!=NULL){
		onFocus->keyPressed(KEY_ENTER);
	}
}

void App::update(){	
	if(windowResizeble)
		windowResizeTreatment();
	mouseAction();
	keyboardAction();
}

void App::add(Scene* scene , std::string name){
	scenes[name] = scene;
}

void App::setScene(std::string name){
	current = scenes[name];
	current->setDimentions(width,height);
}





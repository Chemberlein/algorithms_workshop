#include "scene.h"
#include <vector>
#include <string>
#include <tuple>
#include "element.h"
#include "config.h"
Scene::Scene(LayoutType l){
	switch(l){
		case LayoutType::VERTICALLAYOUT:
			layout = new VerticalLayout(0,0,width,height);
			break;
		case LayoutType::HORIZONTALLAYOUT:
			layout = new HorizontalLayout(0,0,width,height);
			break;
		case LayoutType::CANVAS:
			layout= new Canvas(0,0,width,height);
			break;
	}
}

void Scene::draw(){
	ClearBackground(WHITE);
	layout->draw();
}

void Scene::setDimentions(int w,int h){
	width=w;
	height=h;
	layout->newDimentions(0,0,w,h);
}
Element* Scene::mouseAction(Vector2 mp){
	return layout->mouseAction(mp);
}
void Scene::addElement(Element *elem){
	layout->addElement(elem);
}

void Scene::setConfig(Config* c){
	conf = c;
	layout->setConfig(c);
}

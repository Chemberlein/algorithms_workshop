#pragma once
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include "raylib.h"
#include "config.h"
#include <functional>
#include <ctime>


enum class ElementType{
	LINE,
	CIRCLE,
	BOX,
	LABEL,
	TEXT,
	BUTTON,
	TEXTINPUT,
	DROPDOWN,
	CONTAINER,
	RADIOBUTTON,
	CHECKBOX,
	CANVAS,
	HORIZONTALSPACE,
	VERTICALSPACE,
	IMAGE,
	HORIZONTALLAYOUT,
	VERTICALLAYOUT
};
class Config;
class Element{
	public:
		Element(ElementType type):type(type){};
		virtual ~Element()= default;
		virtual void draw(){
			std::cout<<"somethings goes wrong with element drawing\n";
		};
		virtual void draw(int l,int r,int t,int b){
			std::cout<<"somethings goes wrong with element drawing\n";
		};
		virtual void draw(std::vector<double> a,std::vector <double>){
			std::cout<<"somethings goes wrong with element drawing\n";
		}
		virtual int getTopCoord(){	
			std::cout<<"Error get top coord declaration for this element\n";
			return 0;
		};
		virtual int getBottomCoord(){	
			std::cout<<"error get bottom coord declaration for this element\n";
			return 0;
		};
		virtual int getRightCoord(){	
			std::cout<<"Error get right coord declaretion for this element\n";
			return 0;
		};
		virtual int getLeftCoord(){	
			std::cout<<"Error  get left coord declaretion for this element\n";
			return 0;
		};
		virtual void newDimentions(int xa,int ya,int w,int h){	
			std::cout<<"Don't soupose to change dimentions/error in declareton of newDimention fo rthis element \n";
		};
		virtual bool doesNeedToExpand(){
			//std::cout<<"Error expand doesnt specified to this element\n";
			return false;
		};
		virtual void addElement(Element* elem){
			std::cout<<"Error adding element";
		};
		virtual void setConfig(Config* c){
			conf = c;
		};
		virtual std::vector<int> getXCoord(){
			std::cout<<"ERROR somethig goes wrong\n";
			return {};
		};
		virtual std::vector<int> getYCoord(){
			std::cout<<"ERROR somethig goes wrong\n";
			return {};
		};
		virtual Element* mouseAction(Vector2 mp){
			return NULL;
		}
		virtual void keyPressed(int k){
		};
		virtual void charPressed(int k){};
		virtual void stopFocus(){
			onFocus = false;
		};
		virtual void removeElem(int i){
		}
		virtual void setEnterFunction(std::function<void(std::string)>){};
		ElementType getElementType(){
			return type;
		}
		virtual void setLabel(std::string l){};

		virtual void setImage(int imgnb){};
		virtual void setText(std::string s){};
	protected:
		ElementType type;
		Config* conf;
		bool onFocus=false;
};
class Line: public Element{
	public:
		Line(int x1,int y1,int x2,int y2,int th,Color c):Element(ElementType::LINE),x1(x1),x2(x2),y1(y1),y2(y2),th(th),c(c){};
		void draw();
		void draw(std::vector<double>,std::vector<double>);
		std::vector<int> getXCoord();
		std::vector<int> getYCoord();
		int getTopCoord();
		int getBottomCoord();
		int getRightCoord();
		int getLeftCoord();
	private:
		int x1,x2,y1,y2,th;
		Color c;
};
class Circle: public Element{
	public:
		Circle(int x,int y,int r,Color c):Element(ElementType::CIRCLE),x(x),y(y),r(r),c(c){};
		void draw();	
		void draw(std::vector<double>,std::vector<double>);
		std::vector<int> getXCoord();
		std::vector<int> getYCoord();
		int getTopCoord();
		int getBottomCoord();
		int getRightCoord();
		int getLeftCoord();
		void setLabel(std::string l){
			label=l;
		};
	private:
		int x,y,r;
		Color c;
		bool border =true;
		std::string label = "";
};
class Box: public Element{
	public:
		Box():Element(ElementType::BOX){};
};
class Label: public Element{
	public:
		Label():Element(ElementType::LABEL){};
};
class Text: public Element{
	public:
		Text(int x,int y,int width,int height):Element(ElementType::TEXT),x(x),y(y),width(width),height(height){}
		void draw(int l,int r,int t,int b);
		void addNewLine(std::string s);
		int getTopCoord();
		int getBottomCoord();
		int getRightCoord();
		int getLeftCoord();
		bool doesNeedToExpand();
	private:
		int x,y,width,height;
		std::string text="";
		bool expand = true;
		int padding = 10;
};
class Button:public Element{
	public:
		Button(int x,int y,int width,int height):Element(ElementType::BUTTON),x(x),y(y),width(width),height(height){};
		void setEnterFunction(std::function<void(std::string str)> f);
		int getTopCoord();
		int getBottomCoord();
		int getRightCoord();
		int getLeftCoord();
		void setLabel(std::string s){
			label = s;
		};
		void setText(std::string s){
			text = s;
		};
		void setImage(int imgnb){
			img = imgnb;
		};
		void draw(int l,int r, int t,int b);
		Element* mouseAction(Vector2 mp);
	private:
		int x,y,width,height;
		std::function<void(std::string str)> fun=NULL;
		std::string label="";
		std::string text ="";
		int img=-1;
		int padding = 10;
};
class TextInput:public Element{
	public:
		TextInput(int x,int y,int w,int h):Element(ElementType::TEXTINPUT),x(x),y(y),width(w),height(h){};
		TextInput(int w,int h):Element(ElementType::TEXTINPUT),x(0),y(0),width(w),height(h){};
		int getTopCoord();
		int getBottomCoord();
		int getRightCoord();
		int getLeftCoord();
		void draw(int l,int r, int t,int b);
		Element* mouseAction(Vector2 mp);
		void keyPressed(int key);
		void charPressed(int k);
		void setEnterFunction(std::function<void(std::string)> f);
	private:
		std::string cursor = "_";
		clock_t cursorT = clock();
		clock_t lastEnter = clock();
		clock_t lastBackspace = clock();
		struct timeval tv;
		bool cursorB = true;
		int x,y,width,height;
		std::string text = "";
		std::function<void(std::string str)> enterFun=NULL;
};
class Dropdown: public Element{
	public:
		Dropdown():Element(ElementType::DROPDOWN){};
};
class Container:public Element{
	public:
		Container():Element(ElementType::CONTAINER){};
};
class RadioButton:public Element{
	public:
		RadioButton():Element(ElementType::RADIOBUTTON){};
};
class CheckBox:public Element{
	public:
		CheckBox():Element(ElementType::CHECKBOX){};
};
class Canvas:public Element{
	public:
		Canvas(int x,int y,int width,int height):Element(ElementType::CANVAS),x(x),y(y),width(width),height(height){};
		Canvas(int x,int y,int width,int height,bool expand):Element(ElementType::CANVAS),x(x),y(y),width(width),height(height),expand(expand){};
		Canvas():Element(ElementType::CANVAS),x(0),y(0),width(0),height(0),expand(true){};
		void draw();
		void draw(int l,int r,int t,int b);
		void addElement(Element* elem); 
		void newDimentions(int xa,int ya,int width,int height);
		bool doesNeedToExpand();
		void setConfig(Config* c);
		void removeElem(int i );
	private:
		int x,y,width,height;
		int minX= 0, maxX=0,minY=0,maxY=0;
		bool initLim =false;
		std::vector<Element*> elements;
		bool expand;
		int padding = 10;
};
class HorizontalSpace: public Element{
	public:
		HorizontalSpace(int x,int y,int width,int height):Element(ElementType::HORIZONTALSPACE),x(x),y(y),width(width),height(height){};
		void draw(int l,int r,int t,int b){
		};
		bool doesNeedToExpand();
		int getRightCoord(){return 0;}
		int getLeftCoord(){return 0;};
		int getTopCoord(){return 0;};
		int getBottomCoord(){return 0;};

	private:
		bool expand = true;
		int x,y,width,height;
};
class VerticalSpace: public Element{
	public:
		VerticalSpace(int x,int y,int width,int height):Element(ElementType::VERTICALSPACE),x(x),y(y),width(width),height(height){};
	private:
		int x,y,width,height;
};
class MyImage: public Element{
	public:
		MyImage(int x,int y,int width,int height):Element(ElementType::IMAGE),x(x),y(y),width(width),height(height){};
		void draw(int l,int r,int t,int b);
		int getRightCoord();
		int getLeftCoord();
		int getTopCoord();
		int getBottomCoord();
		void setConfig(Config* c){
			conf = c;
			texture = conf->getImg(0);
		};
	private:
		Texture2D* texture;
		int x,y,width,height;
};

class HorizontalLayout: public Element{
	public:
		HorizontalLayout(int x,int y,int width,int height):Element(ElementType::HORIZONTALLAYOUT),x(x),y(y),width(width),height(height){};
		void draw();
		void draw(int l,int r,int t,int b);
		void addElement(Element* elem);
		void newDimentions(int xa,int ya,int w,int h);
		void setConfig(Config* c);
		int getRightCoord();
		int getLeftCoord();
		int getTopCoord();
		int getBottomCoord();
		Element* mouseAction(Vector2 mp);
	private:
		int x,y,width,height;
		std::vector<Element*> elements;
		std::vector<Rectangle> setting;
};
class VerticalLayout: public Element{
	public:
		VerticalLayout(int x,int y,int width,int height):Element(ElementType::VERTICALLAYOUT),x(x),y(y),width(width),height(height){};
		void draw();
		void draw(int l,int r,int t,int b);
		void addElement(Element* elem);
		void newDimentions(int xa,int ya,int w,int h);
		void setConfig(Config* c);
		Element* mouseAction(Vector2 mp);
		int getRightCoord();
		int getLeftCoord();
		int getTopCoord();
		int getBottomCoord();
	private:
		int x,y,width,height;
		std::vector<Element*> elements;
		std::vector<Rectangle> setting;
};

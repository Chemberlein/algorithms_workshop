#include"element.h"
#include"raylib.h"
#include <iostream>
#include <math.h>
#include "config.h"
#include <vector>
#include <functional>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <string>

#define MAX(a,b) a>b?a:b
#define MIN(a,b) a>b?b:a
//########## Line ##########
void Line::draw(){
	DrawLineEx(Vector2{(float)x1,(float)y1},Vector2{(float)x2,(float)y2},th,c);
}

void Line::draw(std::vector<double> a,std::vector<double> b){
	DrawLineEx(Vector2{(float)a[0],(float)b[0]},Vector2{(float)a[1],(float)b[1]},th,c);
}

std::vector<int> Line::getXCoord(){
	return std::vector<int>{x1,x2};
}
std::vector<int> Line::getYCoord(){
	return std::vector<int>{y1,y2};
}
int Line::getTopCoord(){
	return MAX(y1,y2)+th;
}
int Line::getBottomCoord(){
	return MIN(y1,y2)-th;
}
int Line::getRightCoord(){
	return MAX(x1,x2)+th;
}
int Line::getLeftCoord(){
	return MIN(x1,x2)-th;
}

//########## Circle ##########
void Circle::draw(){
	DrawCircle(x,y,r,c);
}

void Circle::draw(std::vector<double> a,std::vector<double> b){	
	DrawCircle(a[0],b[0],r,c);
	if(border){
		DrawCircleLines(a[0],b[0],r,BLACK);
	}
	if(!label.empty()){
		DrawTextPro(conf->getFont(1),label.c_str(), (Vector2){(float)a[0]+7,(float)b[0]+7},(Vector2){(float)0,(float)0},0, 8, 1, BLACK);
	}
}

std::vector<int> Circle::getXCoord(){
	return std::vector<int>{x};
}

std::vector<int> Circle::getYCoord(){
	return std::vector<int>{y};
}
int Circle::getTopCoord(){
	return y+r;
}
int Circle::getBottomCoord(){
	return y-r;
}
int Circle::getRightCoord(){
	return x+r;
}
int Circle::getLeftCoord(){
	return x-r;
}

//########## Canvas ##########

void Canvas::draw(){
	for(int i =0;i<elements.size();i++){
		//elements[i]->draw(std::vector<double>{x,x+width},std::vector<double>{y,y+height});
	}
}

void Canvas::draw(int l,int r,int t,int b){
	l=l+padding;
	r=r-padding;
	t=t+padding;
	b=b-padding;
	if(elements.empty()){
		std::string text = "Nothing to show";
		width = r-l;
		height=b-t;
		int textWidth=MeasureTextEx(conf->getFont(0), text.c_str(), (float)16, 2).x;
		int textHeght=MeasureTextEx(conf->getFont(0), text.c_str(), (float)16, 2).y;
		DrawTextPro(conf->getFont(0),text.c_str(), (Vector2){(float)x+width/2,(float)y+height/2},(Vector2){(float)textWidth/2,(float)textHeght/2},0, 16, 2, BLACK);
		return;
	}
	// oud - one unit of distance	
	// This is not great fix 
	if(!initLim)
		return;
	double oudX = (double) std::abs(r-l)/std::abs(maxX-minX);
	double oudY = (double) std::abs(b-t)/std::abs(maxY-minY);
	double sx,sy,oud;
	if(oudX<oudY){
		oud=oudX;
		sy=((double)std::abs(b-t)-std::abs(maxY-minY)*oudX)/2;
		sx=0;
	}else{
		oud = oudY;
		sx=((double)std::abs(r-l)-std::abs(maxX-minX)*oudY)/2;
		sy=0;
	}	
	for(int i=0;i<elements.size();i++){
		std::vector<double> nx,ny;
		std::vector<int> ox,oy;
		ox = elements[i]->getXCoord();
		for(auto j:ox){
			nx.push_back(l+sx+std::abs(j-minX)*oud);
		}
		oy = elements[i]->getYCoord();
		for(auto j:oy){
			ny.push_back(t+sy+std::abs(j-maxY)*oud);
		}
		elements[i]->draw(nx,ny);
	}
}
void Canvas::newDimentions(int xa,int ya,int w,int h){
	x=xa;y=ya;width=w;height=h;
}
void Canvas::addElement(Element* elem){
	if(!initLim){
		initLim = true;
		minX=elem->getLeftCoord();
		maxX=elem->getRightCoord();
		minY=elem->getBottomCoord();
		maxY=elem->getTopCoord();
	}else{
		minX=MIN(elem->getLeftCoord(),minX);
		maxX=MAX(elem->getRightCoord(),maxX);
		minY=MIN(elem->getBottomCoord(),minY);
		maxY=MAX(elem->getTopCoord(),maxY);
	}
	elem->setConfig(conf);
	elements.push_back(elem);
}

bool Canvas::doesNeedToExpand(){
	return expand;
}

void Canvas::setConfig(Config* c){
	conf = c;
	for(auto i: elements){
		i->setConfig(c);
	}
}

void Canvas::removeElem(int i){
	elements.erase(elements.begin()+i);
	if(elements.empty()){
		maxX=0;
		minX=0;
		maxY=0;
		minY=0;
		initLim = true;
	}
}
//########## Vertical layout ##########

void VerticalLayout::draw(){
	DrawRectangle(x,y,width,height,RAYWHITE);
	int hu=0;
	int ite=0;
	for(int i =0;i<elements.size();i++){
		if(elements[i]->doesNeedToExpand()){
			ite++;
		}else{
			hu+=(elements[i]->getBottomCoord()-elements[i]->getTopCoord());
		}
	}

	int exps = 0;
	if(ite!=0)
		exps=(height-hu)/ite;
	
	int c=y;

	for(int i =0;i<elements.size();i++){	
		if(elements[i]->doesNeedToExpand()){
			elements[i]->draw(x,x+width,c,c+exps);
			setting[i]=(Rectangle){(float)x,(float)c,(float)width,(float)exps};
			c+=exps;
		}else{
			elements[i]->draw(x,x+width,c,c+(elements[i]->getBottomCoord()-elements[i]->getTopCoord()));
			setting[i] = (Rectangle){(float)x,(float)c,(float)width,(float)(elements[i]->getBottomCoord()-elements[i]->getTopCoord())};
			c+=(elements[i]->getBottomCoord()-elements[i]->getTopCoord());
		}
	}
	if(c>height){
		std::cout<<"Overflow of layout.\n";
	}
}

void VerticalLayout::draw(int l,int r,int t,int b){
	newDimentions(l,t,r-l,b-t);
	draw();	
}

void VerticalLayout::addElement(Element* elem){
	setting.push_back((Rectangle){0,0,0,0});
	elements.push_back(elem);
}

void VerticalLayout::newDimentions(int xa,int ya,int w,int h){
	x=xa;y=ya;width=w;height=h;
}

void VerticalLayout::setConfig(Config* c){
	conf = c;
	for(auto i: elements){
		i->setConfig(c);
	}
}
Element* VerticalLayout::mouseAction(Vector2 mp){
	for(int i=0;i<elements.size();i++){
		if(CheckCollisionPointRec(mp,setting[i])){
			return elements[i]->mouseAction(mp);
		}	
	}
	return NULL;
}
int VerticalLayout::getRightCoord(){
	return x+width;
}
int VerticalLayout::getLeftCoord(){
	return x;
}
int VerticalLayout::getTopCoord(){
	return y;
}
int VerticalLayout::getBottomCoord(){
	return y+height;
}
//########## Horizontal layout ##########

void HorizontalLayout::draw(){
	int wu=0;
	int ite=0;
	for(int i =0;i<elements.size();i++){
		if(elements[i]->doesNeedToExpand()){
			ite++;
		}else{
			wu+=(elements[i]->getRightCoord()-elements[i]->getLeftCoord());
		}
	}
	int exps = 0;
	if(ite != 0)
		exps=(width-wu)/ite;
	int c=x;
	for(int i =0;i<elements.size();i++){	
		if(elements[i]->doesNeedToExpand()){
			elements[i]->draw(c,c+exps,y,y+height);
			setting[i]=(Rectangle){(float)c,(float)y,(float)exps,(float)height};
			c+=exps;
		}else{
			elements[i]->draw(c,c+(elements[i]->getRightCoord()-elements[i]->getLeftCoord()),y,y+height);
			setting[i] = (Rectangle){(float)c,(float)y,(float)(elements[i]->getRightCoord()-elements[i]->getLeftCoord()),(float)height};
			c+=(elements[i]->getRightCoord()-elements[i]->getLeftCoord());
		}
	}
	if(c>width+x){
		std::cout<<ite<<" Overflow of layout H.\n";
	}
}

void HorizontalLayout::draw(int l,int r,int t,int b){
	newDimentions(l,t,r-l,b-t);
	draw();	
}

void HorizontalLayout::addElement(Element* elem){
	setting.push_back((Rectangle){0,0,0,0});
	elements.push_back(elem);
}

void HorizontalLayout::newDimentions(int xa,int ya,int w,int h){
	x=xa;y=ya;width=w;height=h;
}

void HorizontalLayout::setConfig(Config* c){
	conf = c;
	for(auto i: elements){
		i->setConfig(c);
	}
}
Element* HorizontalLayout::mouseAction(Vector2 mp){
	for(int i=0;i<elements.size();i++){
		if(CheckCollisionPointRec(mp,setting[i])){
			return elements[i]->mouseAction(mp);
		}	
	}
	return NULL;
}
int HorizontalLayout::getRightCoord(){
	return x+width;
}
int HorizontalLayout::getLeftCoord(){
	return x;
}
int HorizontalLayout::getTopCoord(){
	return y;
}
int HorizontalLayout::getBottomCoord(){
	return y+height;
}
//########## TextInput ##########

int TextInput::getTopCoord(){
	return y;
}
int TextInput::getBottomCoord(){
	return y+height;
}
int TextInput::getRightCoord(){
	return x+width;
}
int TextInput::getLeftCoord(){
	return x;
}
void TextInput::draw(int l,int r,int t,int b){
	DrawRectangleLines(l,t,r-l,b-t,GRAY);
	int padding = 5;
	std::string texttoprint=text;
	if(!text.empty()){
		int pos = 1;
		while(MeasureTextEx(conf->getFont(0),texttoprint.substr(pos).c_str(),16.0,1).x >r-l-4*padding){
			pos++;
		}
		texttoprint = texttoprint.substr(pos-1);
		DrawTextPro(conf->getFont(0),texttoprint.c_str(), (Vector2){(float)l+padding,(float)t+padding},(Vector2){(float)0,(float)0},0, 16, 1, BLACK);
	}
	clock_t currT=clock();
	if(std::abs(currT - cursorT)/(1000)>32){
		cursorT=currT;
		cursorB=!cursorB;
	}
	if(cursorB && onFocus){
		int textWidth=MeasureTextEx(conf->getFont(0), texttoprint.c_str(), 16.0, 1).x;
		DrawTextPro(conf->getFont(0),cursor.c_str(), (Vector2){(float)l+textWidth+padding,(float)t+padding},(Vector2){(float)0,(float)0},0, 16, 1, BLACK);
	}
}
Element* TextInput::mouseAction(Vector2 mp){
	onFocus=true;
	return this;
}
void TextInput::keyPressed(int k){
	clock_t currT=clock();
	if(KEY_BACKSPACE == k && !text.empty() && (std::abs(currT - lastBackspace)/1000>2.5)){
		lastBackspace = currT;
		text.pop_back();
	}
	if(KEY_ENTER == k && enterFun != NULL && (std::abs(currT - lastEnter)/1000>2.5)){
		lastEnter = currT;
		enterFun(text);
		text = "";
	}
}
void TextInput::charPressed(int k){
		text.push_back((char) k);
}

void TextInput::setEnterFunction(std::function<void(std::string)> f){
	enterFun = f;
};
//########## Button ##########
void Button::setEnterFunction(std::function<void(std::string)> f){
	fun = f;
};
int Button::getTopCoord(){
	return y;
}
int Button::getBottomCoord(){
	return y+height;
}
int Button::getRightCoord(){
	return x+width;
}
int Button::getLeftCoord(){
	return x;
}
void Button::draw(int l,int r,int t,int b){
	int sx = ((r-l)-width)/2;
	int sy = ((b-t)-height)/2;
	if(!text.empty() && img == -1){
		DrawRectangleLines(l+sx,t+sy,width,height,BLACK);
		int textWidth=MeasureTextEx(conf->getFont(0), text.c_str(), 16.0, 1).x;
		int textHeight=MeasureTextEx(conf->getFont(0), text.c_str(), 16.0, 1).y;
		DrawTextPro(conf->getFont(0),text.c_str(), (Vector2){(float)l+width/2,(float)t+height/2},(Vector2){(float)textWidth/2,(float)textHeight/2},0, 16, 1, BLACK);
	}else if(text.empty() && img!=-1){
		Texture2D* texture = conf->getImg(img);
		float scaleX = (float)50/texture->width;
		float scaleY = (float)50/texture->height;
		float scale;
		if(scaleX>scaleY){
			scale=scaleY;
		}else{
			scale=scaleX;
		}
		sx=(width-(texture->width*scale))/2;
		sy=(height-(texture->height*scale))/2;
		DrawTextureEx((*texture),Vector2{(float)sx+l,(float) sy+t},0,scale, WHITE);
	}else if(!text.empty() && img !=-1){
		DrawRectangleLines(l+sx,t+sy,width,height,BLACK);
		int textWidth=MeasureTextEx(conf->getFont(0), text.c_str(), 16.0, 1).x;
		int textHeight=MeasureTextEx(conf->getFont(0), text.c_str(), 16.0, 1).y;
		DrawTextPro(conf->getFont(0),text.c_str(), (Vector2){(float)l+width/2+padding-25,(float)t+height/2},(Vector2){(float)textWidth/2,(float)textHeight/2},0, 16, 1, BLACK);
		Texture2D* texture = conf->getImg(img);
		float scaleX = (float)25/texture->width;
		float scaleY = (float)25/texture->height;
		float scale;
		if(scaleX>scaleY){
			scale=scaleY;
		}else{
			scale=scaleX;
		}
		DrawTextureEx((*texture),Vector2{(float)l+width/2-25+textWidth,(float) t+height/2-12},0,scale, WHITE);
	}
}
Element* Button::mouseAction(Vector2 mp){
	fun(label);
	return NULL;
}
//########## Text ##########
void Text::draw(int l,int r,int t,int b){
	if(!text.empty()){
		std::stringstream ss(text);
		std::string word="Test";
		int xp=l,yp=t,ys=MeasureTextEx(conf->getFont(0),word.c_str(),16.0,1).y;
		while(!ss.eof()){
			ss>>word;
			word=word+" ";
			int textWidth=MeasureTextEx(conf->getFont(0), word.c_str(), 16.0, 1).x;
			if(xp+textWidth>(r))
				xp=l,yp+=ys;
			DrawTextPro(conf->getFont(0),word.c_str(), (Vector2){(float)xp,(float)yp},(Vector2){(float)0,(float)0},0, 16, 1, BLACK);
			xp+=textWidth;
			if(ss.peek() =='\n'){
				yp+=ys;
				xp=l;
			}
			word = "";
		}
	}
}
void Text::addNewLine(std::string s){
	text= "# "+s+"\n";
}
int Text::getTopCoord(){
	return y;
}
int Text::getBottomCoord(){
	return y+height;
}
int Text::getLeftCoord(){
	return x;
}
int Text::getRightCoord(){
	return x+width;
}
bool Text::doesNeedToExpand(){
	return expand;
}

//########## MyImage ##########
void MyImage::draw(int l,int r,int t,int b){
	float scaleX = (float)(r-l-10)/texture->width;
	float scaleY = (float)(b-t-10)/texture->height;
	int sx = 5;
	int sy = 5;
	float scale;	
	if(scaleX>scaleY){
		scale=scaleY;
		sx=(width-(texture->width*scale))/2;
	}else{
		scale=scaleX;
		sy=(height-(texture->height*scale))/2;
	}
	DrawTextureEx((*texture),Vector2{(float)sx+l,(float) sy+t},0,scale, WHITE);
}
int MyImage::getRightCoord(){
	return x+width;
};
int MyImage::getLeftCoord(){
	return x;
};
int MyImage::getTopCoord(){
	return y;
};
int MyImage::getBottomCoord(){
	return y+height;
};
//########## HorizontalSpace ##########
bool HorizontalSpace::doesNeedToExpand(){
	return expand;
}

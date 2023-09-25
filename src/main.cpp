#include "ChemberleinRaylibUILib/app.h"
#include "ChemberleinRaylibUILib/element.h"
#include "ChemberleinRaylibUILib/scene.h"
#include <string>
#include "raylib.h"
#include <iostream>
#include <functional>
#include <tuple>
#include <string.h>
#include <random>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include "Algorithms/TravelSalesmanProblem/MSTTSP.h"
#include "Algorithms/TravelSalesmanProblem/NearestNeighborTSP.h"
#include "Algorithms/MinimumSpanningTree/MST.h"
#include "Algorithms/TravelSalesmanProblem/InsertionHeuristicTSP.h"
#include "Algorithms/ConvexHull/ConvexHull.h"
#include "Algorithms/TravelSalesmanProblem/ConvexHullHeuristicTSP.h"
Canvas* gCanvas;
Text* logs;
std::vector<Element*> elems;

class Action{
	public: 
		Action(){};
		static void task(std::string str){
			if(str.empty())
				return;
			std::stringstream ss(str);
			std::string token;
			ss>>token;
			if(strcmp("random_graph",token.c_str())==0 || strcmp("rg",token.c_str())==0){
				ss>>token;
				generateRandonGraph(atoi(token.c_str()));
				logs->addNewLine("New graph with "+token+" point is generated");
			}else if(strcmp("clear",token.c_str())==0){
				clearCanvas();
				logs->addNewLine("Canvas is cleared");
			}else if(strcmp("mstp",token.c_str())==0){
				solveMST(computePrimMST,"Prime");
			}else if(strcmp("mstk",token.c_str())==0){
				solveMST(computeKruskalMST,"Kruskal");
			}else if(strcmp("chj",token.c_str())==0){
				solveConvexHull(computeConvexHullJarvis,"Jarvis");
			}else if(strcmp("chgs",token.c_str())==0){
				solveConvexHull(computeConvexHullGrahamScan,"Graham Scan");
			}else if(strcmp("nntsp",token.c_str())==0){
				solveTSP(computeNearestNeighborTSP,"Nearest Neighbor");
			}else if(strcmp("kmsttsp",token.c_str())==0){
				solveTSP(computeKruscalMSTTSP,"Kruskal MST");
			}else if(strcmp("pmsttsp",token.c_str())==0){
				solveTSP(computePrimMSTTSP,"Prim MST");	
			}else if(strcmp("nitsp",token.c_str())==0){
				solveTSP(computeNearestInsertionHeuristicTSP,"Nearest Insertion Heuristic");
			}else if(strcmp("fitsp",token.c_str())==0){
				solveTSP(computeFarthestInsertionHeuristicTSP,"Farthest Insertion Heuristic");
			}else if(strcmp("citsp",token.c_str())==0){
				solveTSP(computeCheapestInsertionHeuristicTSP,"Cheapest Insertion Heuristic");
			}else if(strcmp("ritsp",token.c_str())==0){
				solveTSP(computeRandomInsertionHeuristicTSP,"Random Insertion Heuristic");
			}else if(strcmp("chnitsp",token.c_str())==0){
				solveTSP(computeConvexHullHeuristicNearestInsertionTSP,"Convex Hull Heuristic Nearest Insertion");
			}else if(strcmp("chfitsp",token.c_str())==0){
				solveTSP(computeConvexHullHeuristicFarthestInsertionTSP,"Convex Hull Heuristic Farthest Insertion");
			}else if(strcmp("chritsp",token.c_str())==0){
				solveTSP(computeConvexHullHeuristicRandomInsertionTSP,"Convex Hull Heuristic Random Insertion");
			}else if(strcmp("chcitsp",token.c_str())==0){
				solveTSP(computeConvexHullHeuristicCheapestInsertionTSP,"Convex Hull Heuristic Cheapest Insertion");
			}else if(strcmp("about",token.c_str())==0){
				logs->addNewLine("Hello and welcome , this application may help you to see resual of exection of different algorithms(mostly on graph). Please look at info to understand which functionality is avalible.\n");
			}else if(strcmp("info",token.c_str())==0){
				logs->addNewLine("rg <n> - generate random graph with n points\n clear - clear canvas\n ch[ni|fi|ri|ci]tsp Convex hull heuristic to solve tsp using nierest insertion (ni) or farthest insertion (fi) or random insertion (ri) or cheapest insertion (ci)\n chgs - convex hull Graham Scan\n chj - convex hull jarvis algorithm\n ritsp random insertion heuristic to solve tsp\n citsp cheapest insertion heuristic to sove tsp\n fitsp farthest insertion heuristic to solve tsp\n nitsp nearest insertion tsp solution\n mstp - show minimal spanding tree computed with Prim algorithm\n mstk - show minimal spanding tree computed with Kruscal algorithm\n nntsp - solve tsp with neares neigbor algorithm\n kmsttsp- tsp solution using Kruscal mst\n pmsttsp - tspsolution using Prim mst\n");
			}else{
				logs->addNewLine("Unknown comand:"+str);
			}
		};
		static void solveMST(std::function<std::vector<std::tuple<int,int>>(std::vector<std::tuple<int,int>>)> f,std::string name){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			if(coord.size()==0){
				logs->addNewLine("You need to open/generate graph");
				return;
			}
			std::vector<std::tuple<int,int>> ST = f(coord);
			clearCanvas();
			std::string logstr=name+" MST:\n Pairs:\n "; 
			int s =0;
			for(int i =0;i<ST.size();i++){
				int x1 = std::get<0>(coord[std::get<0>(ST[i])]);
				int x2 = std::get<0>(coord[std::get<1>(ST[i])]);
				int y1 = std::get<1>(coord[std::get<0>(ST[i])]);
				int y2 = std::get<1>(coord[std::get<1>(ST[i])]);
				s+=std::sqrt(std::pow(x2-x1,2)+std::pow(y2-y1,2));
				logstr=logstr+"("+std::to_string(std::get<0>(ST[i]))+","+std::to_string(std::get<1>(ST[i]))+")\n";
				Element* elem = new Line(x1,y1,x2,y2,2,BLACK);
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			logstr=logstr+"\n Size :"+std::to_string(s)+"\n";		
			for(int i = 0;i<coord.size();i++){
				Element* elem = new Circle(std::get<0>(coord[i]),std::get<1>(coord[i]),8,ORANGE);
				elem->setLabel(std::to_string(i));

				gCanvas->addElement(elem);
				elems.push_back(elem);
			}

			logs->addNewLine(logstr);
		}
		static void solveConvexHull(std::function<std::vector<int>(std::vector<std::tuple<int,int>>)> f,std::string name){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			if(coord.size()==0){
				logs->addNewLine("You need to open/generate graph");
				return;
			}
			std::vector<int> ConvHull = f(coord);
			clearCanvas();
			std::string logstr=name+" convex hull solution:\n Path: "+std::to_string(ConvHull[0])+"-";
			double d = 0;
			for(int i =1;i<ConvHull.size();i++){
				int x1 = std::get<0>(coord[ConvHull[i-1]]);
				int x2 = std::get<0>(coord[ConvHull[i]]);
				int y1 = std::get<1>(coord[ConvHull[i-1]]);
				int y2 = std::get<1>(coord[ConvHull[i]]);
				d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				logstr=logstr+std::to_string(i)+"-";
				Element* elem = new Line(x1,y1,x2,y2,2,BLACK);
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			int x1 = std::get<0>(coord[ConvHull[0]]);
			int x2 = std::get<0>(coord[ConvHull[ConvHull.size()-1]]);
			int y1 = std::get<1>(coord[ConvHull[0]]);
			int y2 = std::get<1>(coord[ConvHull[ConvHull.size()-1]]);
			d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
			logstr=logstr+std::to_string(ConvHull[0])+"\n Total distance: "+std::to_string(d)+"\n";
			for(int i = 0;i<coord.size();i++){
				Element* elem = new Circle(std::get<0>(coord[i]),std::get<1>(coord[i]),8,ORANGE);
				elem->setLabel(std::to_string(i));
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			logs->addNewLine(logstr);
		};
		static void solveTSP(std::function<std::vector<int>(std::vector<std::tuple<int,int>>)> f,std::string name){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			if(coord.size()==0){
				logs->addNewLine("You need to open/generate graph");
				return;
			}
			std::vector<int> MSTResult = f(coord);
			clearCanvas();
			std::string logstr= name+" TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
			double d = 0;
			for(int i =1;i<MSTResult.size();i++){
				int x1 = std::get<0>(coord[MSTResult[i-1]]);
				int x2 = std::get<0>(coord[MSTResult[i]]);
				int y1 = std::get<1>(coord[MSTResult[i-1]]);
				int y2 = std::get<1>(coord[MSTResult[i]]);
				d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				logstr=logstr+std::to_string(i)+"-";
				Element* elem = new Line(x1,y1,x2,y2,2,BLACK);
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			int x1 = std::get<0>(coord[MSTResult[0]]);
			int x2 = std::get<0>(coord[MSTResult[MSTResult.size()-1]]);
			int y1 = std::get<1>(coord[MSTResult[0]]);
			int y2 = std::get<1>(coord[MSTResult[MSTResult.size()-1]]);
			d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
			logstr=logstr+std::to_string(MSTResult[0])+"\n Total distance: "+std::to_string(d)+"\n";
			for(int i = 0;i<coord.size();i++){
				Element* elem = new Circle(std::get<0>(coord[i]),std::get<1>(coord[i]),8,ORANGE);
				elem->setLabel(std::to_string(i));
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			logs->addNewLine(logstr);
		};
		static void generateRandonGraph(int n){
			clearCanvas();
			std::random_device rd;     // Only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> uni1(0,n*n); // Guaranteed unbiased
			std::uniform_int_distribution<int> uni2(0,n*n); // Guaranteed unbiased
			for(int i = 0; i<n;i++){
				int x = uni1(rng);
				int y = uni2(rng);
				Element* elem = new Circle(x,y,8,ORANGE);
				elem->setLabel(std::to_string(i));
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
		}
		static void clearCanvas(){
			while(!elems.empty()){
				gCanvas->removeElem(0);
				Element* e = elems[0];
				elems.erase(elems.begin()+0);
				delete e;
			}
		}
	private:

};
void printText(std::string str){
	std::cout<<str<<std::endl;
}
int main(void){
	App app = App(1024,800,"CAW",true);
	Scene scene = Scene(LayoutType::HORIZONTALLAYOUT);
	Canvas can = Canvas(0,0,0,800,true);
	gCanvas = &can;
	Action act = Action();
	scene.addElement(&can);
	VerticalLayout l =  VerticalLayout(0,0,320,200);
	MyImage logo = MyImage(0,0,320,200);
	HorizontalLayout hl(0,0,320,50);
	HorizontalSpace hs(0,0,0,0);
	hl.addElement(&hs);
	Button b1(0,0,75,50);
	b1.setEnterFunction(act.task);
	Button b2(0,0,75,50);
	b2.setEnterFunction(act.task);
	b1.setLabel("info");
	b1.setText("Info");
	b2.setLabel("about");
	b2.setText("About");
	hl.addElement(&b1);
	hl.addElement(&b2);

	TextInput ti = TextInput(30,30);
	ti.setEnterFunction(act.task);
	l.addElement(&hl);
	l.addElement(&logo);
	l.addElement(&ti);
	Text logAff = Text(0,0,0,0);
	logs = &logAff;
	l.addElement(&logAff);
	scene.addElement(&l);
	app.add(&scene,"Main scene");
	app.setScene("Main scene");

	
	app.run();
	return 0;
}

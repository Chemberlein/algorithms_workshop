#include "app.h"
#include "scene.h"
#include "element.h"
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
#include "MSTTSP.h"
#include "NearestNeighborTSP.h"
#include "MST.h"
#include "InsertionHeuristicTSP.h"
#include "ConvexHull.h"
#include "ConvexHullHeuristicTSP.h"
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
			}else if(strcmp("nntsp",token.c_str())==0){
				solveTSPNearestNeighbor();
			}else if(strcmp("mstp",token.c_str())==0){
				solvePrimeMST();
			}else if(strcmp("mstk",token.c_str())==0){
				solveKruskalMST();
			}else if(strcmp("clear",token.c_str())==0){
				clearCanvas();
				logs->addNewLine("Canvas is cleared");
			}else if(strcmp("kmsttsp",token.c_str())==0){
				solveKruskalMSTTSP();	
			}else if(strcmp("nitsp",token.c_str())==0){
				solveNearestInsertionHeuristicTSP();
			}else if(strcmp("fitsp",token.c_str())==0){
				solveFarthestInsertionHeuristicTSP();
			}else if(strcmp("citsp",token.c_str())==0){
				solveCheapestInsertionHeuristicTSP();
			}else if(strcmp("ritsp",token.c_str())==0){
				solveRandomInsertionHeuristicTSP();
			}else if(strcmp("chnitsp",token.c_str())==0){
				solveConvexHullHeuristicNearestInsertionTSP();
			}else if(strcmp("chfitsp",token.c_str())==0){
				solveConvexHullHeuristicFarthestInsertionTSP();
			}else if(strcmp("chritsp",token.c_str())==0){
				solveConvexHullHeuristicRandomInsertionTSP();
			}else if(strcmp("chcitsp",token.c_str())==0){
				solveConvexHullHeuristicCheapestInsertionTSP();
			}else if(strcmp("pmsttsp",token.c_str())==0){
				solvePrieMSTTSP();	
			}else if(strcmp("chj",token.c_str())==0){
				solveConvexHullJarvis();
			}else if(strcmp("chgs",token.c_str())==0){
				solveConvexHullGrahamScan();
			}else if(strcmp("about",token.c_str())==0){
				logs->addNewLine("Hello and welcome , this application may help you to see resual of exection of different algorithms(mostly on graph). Please look at info to understand which functionality is avalible.\n");
			}else if(strcmp("info",token.c_str())==0){
				logs->addNewLine("rg <n> - generate random graph with n points\n clear - clear canvas\n ch[ni|fi|ri|ci]tsp Convex hull heuristic to solve tsp using nierest insertion (ni) or farthest insertion (fi) or random insertion (ri) or cheapest insertion (ci)\n chgs - convex hull Graham Scan\n chj - convex hull jarvis algorithm\n ritsp random insertion heuristic to solve tsp\n citsp cheapest insertion heuristic to sove tsp\n fitsp farthest insertion heuristic to solve tsp\n nitsp nearest insertion tsp solution\n mstp - show minimal spanding tree computed with Prim algorithm\n mstk - show minimal spanding tree computed with Kruscal algorithm\n nntsp - solve tsp with neares neigbor algorithm\n kmsttsp- tsp solution using Kruscal mst\n pmsttsp - tspsolution using Prim mst\n");
			}else{
				logs->addNewLine("Unknown comand:"+str);
			}
		};
		static void solveKruskalMST(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<std::tuple<int,int>> ST = computeKruskalMST(coord);
			clearCanvas();
			std::string logstr="Kruskal MST:\n Pairs:\n "; 
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
		static void solvePrimeMST(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<std::tuple<int,int>> ST = computePrimMST(coord);
			clearCanvas();
			std::string logstr="Prim MST:\n Pairs:\n "; 
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
		};
		static void solveConvexHullGrahamScan(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> ConvHull = computeConvexHullGrahamScan(coord);
			clearCanvas();
			std::string logstr="Convex Hull solution:\n Path: "+std::to_string(ConvHull[0])+"-";
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
		static void solveConvexHullJarvis(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> ConvHull = computeConvexHullJarvis(coord);
			clearCanvas();
			std::string logstr="Convex Hull solution:\n Path: "+std::to_string(ConvHull[0])+"-";
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
		static void solveConvexHullHeuristicNearestInsertionTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeConvexHullHeuristicNearestInsertionTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveConvexHullHeuristicFarthestInsertionTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeConvexHullHeuristicFarthestInsertionTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveConvexHullHeuristicRandomInsertionTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeConvexHullHeuristicRandomInsertionTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveConvexHullHeuristicCheapestInsertionTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeConvexHullHeuristicCheapestInsertionTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveNearestInsertionHeuristicTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeNearestInsertionHeuristicTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveFarthestInsertionHeuristicTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeFarthestInsertionHeuristicTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveCheapestInsertionHeuristicTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeCheapestInsertionHeuristicTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveRandomInsertionHeuristicTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeRandomInsertionHeuristicTSP(coord);
			clearCanvas();
			std::string logstr="Nearest insertion TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-";
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
		static void solveKruskalMSTTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computeKruscalMSTTSP(coord);
			clearCanvas();
			std::string logstr="Kruscal MST TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-"; 
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
		static void solvePrieMSTTSP(){
			std::vector<std::tuple<int,int>> coord;
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> MSTResult = computePrimMSTTSP(coord);
			clearCanvas();
			std::string logstr="Prim MST TSP solution:\n Path: "+std::to_string(MSTResult[0])+"-"; 
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
		static void solveTSPNearestNeighbor(){
			std::vector<std::tuple<int,int>> coord;
			
			for(auto i : elems){
				if(i->getElementType() == ElementType::CIRCLE){
					coord.push_back(std::make_tuple(i->getXCoord()[0],i->getYCoord()[0]));
				}
			}
			std::vector<int> greedyResult = computeNearestNeighborTSP(coord);
			clearCanvas();
			std::string logstr="Greedy solution:\n Path: "+std::to_string(greedyResult[0])+"-"; 
			double d = 0;	
			for(int i =1;i<greedyResult.size();i++){
				int x1 = std::get<0>(coord[greedyResult[i-1]]);
				int x2 = std::get<0>(coord[greedyResult[i]]);
				int y1 = std::get<1>(coord[greedyResult[i-1]]);
				int y2 = std::get<1>(coord[greedyResult[i]]);
				d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
				logstr=logstr+std::to_string(i)+"-";
				Element* elem = new Line(x1,y1,x2,y2,2,BLACK);
				gCanvas->addElement(elem);
				elems.push_back(elem);
			}
			int x1 = std::get<0>(coord[greedyResult[0]]);
			int x2 = std::get<0>(coord[greedyResult[greedyResult.size()-1]]);
			int y1 = std::get<1>(coord[greedyResult[0]]);
			int y2 = std::get<1>(coord[greedyResult[greedyResult.size()-1]]);
			d+=std::sqrt(pow(x2-x1,2)+pow(y2-y1,2));
			logstr=logstr+std::to_string(greedyResult[0])+"\n Total distance: "+std::to_string(d)+"";
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

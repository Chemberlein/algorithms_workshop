* Algorithms workshop 
(Warning : application still in development)

** How To compile :
1) clone this git repository
2) go to build directory (cd build)
3) run "cmake -S ../ -B ."
4) run "make"
5) execute program "./algorithms_workshop"
** Functionality :
***	rg <n> - generate a random graph with n points
***	clear - clear canvas
***	ch[ni|fi|ri|ci]tsp Convex hull heuristic to solve tsp using nearest insertion (ni) or farthest insertion (fi) or random insertion (ri) or cheapest insertion (ci)
***	chgs - convex hull Graham Scan
***	chj - convex hull Jarvis algorithm
***	ritsp random insertion heuristic to solve tsp
***	citsp cheapest insertion heuristic to solve tsp
***	fitsp the farthest insertion heuristic to solve tsp
***	nitsp nearest insertion tsp solution
***	mstp - show minimal spanning tree computed with Prim algorithm
***	mstk - show minimal spanning tree computed with Kruscal algorithm
***	nntsp - solve tsp with neares neigbor algorithm
***	kmsttsp- tsp solution using Kruscal mst
***	pmsttsp - tspsolution using Prim mst

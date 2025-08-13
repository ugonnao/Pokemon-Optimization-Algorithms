//Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <math.h>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

class OPTTSP{
    private:
       struct prims{ //a separate struct of prims table, not every part needs a prims table
            bool kv = 0; // whether vertex v has been added to MST
            double dv = numeric_limits<double>::infinity(); // lowest distance to MST
            int32_t pv = -1; // index of vertex's parent
        };//prims

        struct Coordinate{
            int x, y; 
        };
        
        vector<Coordinate> list; 
        vector<size_t> path;
        vector<size_t> bestPath;
        double infinity = numeric_limits<double>::infinity();
        double bestCost = infinity;
        
        double calcDist(const Coordinate &uno, const Coordinate &dos){
            double xDiff = uno.x - dos.x; 
            double yDiff = uno.y - dos.y;
            double dist = (xDiff * xDiff) + (yDiff * yDiff);
            return sqrt(dist);
        }//calcDist

        double mst_alg(const size_t permLength){
            vector<prims> vecPrims;
            for(size_t i = 0; i < list.size(); i++){
                prims vertex;
                vecPrims.push_back(vertex);
            }//for
            for(size_t i = permLength; i < vecPrims.size(); i++){
                vecPrims[path[i]].dv = infinity; 
                vecPrims[path[i]].kv = 0; 
                vecPrims[path[i]].pv = -1; 
            }//for
            double weight = 0.0;
          
            //starting index of MST distance is 0
            size_t currNode = permLength;
            vecPrims[path[currNode]].dv = 0;
            for(size_t i = permLength; i < vecPrims.size(); i++){
                vecPrims[path[currNode]].kv = true;
                for(size_t j = permLength; j < vecPrims.size(); j++){
                    if(vecPrims[path[currNode]].kv){//if currNode is discovered
                        double distance = calcDist(list[path[currNode]], list[path[j]]);
                        if(distance < vecPrims[path[j]].dv && currNode != j && vecPrims[path[j]].kv == false ){// distance comparison between current node and j node
                            vecPrims[path[j]].dv = distance;      
                            vecPrims[path[j]].pv = static_cast<int32_t>(currNode); //parent node, trainer is now at this location the next iteration
                        }
                    }//if
                }//2nd for
                double minimumDist = infinity;
                for(size_t j = permLength; j < vecPrims.size(); j++){
                    if(vecPrims[path[j]].dv < minimumDist && vecPrims[path[j]].kv == false){
                        minimumDist = vecPrims[path[j]].dv; //
                        currNode = j; // smallest edge distance
                    }
                }//2nd for
            }//first for
            for(size_t i = permLength; i < vecPrims.size(); i++){
                weight += vecPrims[path[i]].dv;
            }//for
            return weight;
        }//MST

        double arbitraryInsertion(){
            //arbitrary Insertion
            size_t n = list.size(); 
            vector<size_t> tour;
            vector<bool>visited(n, false);

            //intialize first vertex
            tour.push_back(0);
            visited[0] = true; 
            // arbitrary pick second vertex
            tour.push_back(1);
            tour.push_back(2);
            tour.push_back(0);
            visited[1] = true; 
            visited[2] = true; 
            //add remaining verticies to tour
            while(tour.size() < n + 1){
                size_t toInsert = numeric_limits<size_t>::max();
                //find vertex that hasn't been visited
                for(size_t i = 0; i < n; i++){
                    if(!visited[i]){
                        toInsert = i;
                        break;
                    }
                }//for

                //finding best place to insert "toInsert"
                double minDist = numeric_limits<double>::infinity();
                auto bestLocation = 0;

                for(size_t pos = 0; pos < tour.size() - 1; pos++){
                    size_t j = tour[pos];
                    size_t k = tour[pos + 1];
                    double distance = calcDist(list[j], list[toInsert]) +
                                        calcDist(list[toInsert], list[k]) - 
                                        calcDist(list[j], list[k]);

                    if(distance < minDist){
                        minDist = distance; 
                        bestLocation = static_cast<int>(pos + 1);
                    }
                }//for
                tour.insert(tour.begin() + bestLocation, toInsert);
                visited[toInsert] = true; 
            }//while

            double totalCost = 0.0;
            for(size_t i = 0; i < tour.size() - 1; i++){
                totalCost += calcDist(list[tour[i]], list[tour[i + 1]]);
            }//for
            return totalCost; 
        }//fasttsp

        void genPerms(std::size_t permLength){
            double cost = 0.0; 
            if(permLength == path.size()){
                // Do something with the path
                for(size_t i = 0; i < path.size() - 1; i++){
                    cost += calcDist(list[path[i]], list[path[i+1]]);
                }//for

                cost += calcDist(list[path.back()], list[path[0]]);
                if(cost < bestCost){
                    bestCost = cost; 
                    bestPath = path; 
                }
                return;
            }  // if ..complete path

            if(!promising(permLength)){
                return;
            }  // if ..not promising
        //     // Prune if current cost exceeds best cost

            for(size_t i = permLength; i < path.size(); ++i){
                swap(path[permLength], path[i]);
                double distance = calcDist(list[path[i]], list[path[permLength-1]]);
                cost += distance; 
                genPerms(permLength + 1);
                cost -= distance; 
                swap(path[permLength], path[i]);
            }  // for ..unpermuted elements
        }  // genPerms()

        bool promising(size_t permLength){
            if(path.size() - permLength < 5){
                 return true; 
             }else{
                double currCost = 0.0, arm1 = infinity, arm2 = infinity;
                double mstCost = 0.0, totalEst = 0.0;
                bool promise = false; 
                //two variables for my two arms with for loop
                //add up mst and arm length, if total < best, promise is true
                for(size_t i = 0; i < permLength - 1; i++){
                    currCost += calcDist(list[path[i]], list[path[i+1]]);
                }//cost of the current permuation
                for(size_t i = 0; i < path.size() - permLength; i++){
                    double distance1 = calcDist(list[path[0]], list[path[i + permLength]]);
                    double distance2 = calcDist(list[path[permLength - 1]], list[path[i + permLength]]);
                    if(distance1 < arm1){
                        arm1 = distance1; 
                    }
                    if(distance2 < arm2){
                        arm2 = distance2; 
                    }
                }//for 
                mstCost = mst_alg(permLength);
                totalEst = mstCost + arm1 + arm2 + currCost; 
                promise = totalEst < bestCost; 
                return promise; 
            }//else
        }//promising
        
    public:
        void read_input(){
            size_t num_verticies;
            cin >> num_verticies;
            list.reserve(num_verticies);
            while(list.size() < num_verticies){
                Coordinate coord;
                cin >> coord.x >> coord.y;
                list.push_back(coord);
            }//for
            bestCost = arbitraryInsertion();
        }//read_input

        void TSP_Algorithm(){
            size_t n = list.size(); 
            path.resize(n);
            for(size_t i = 0; i < n; i++){
                path[i] = i;
            }
            // bestCost = 336.74;
            // vector<size_t> tour = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
            // path = tour; 
            //size_t size = tour.size(); 
            bestPath = path; 
            genPerms(1);
            cout << bestCost << "\n";
            for(size_t pokemon : bestPath){
                cout << pokemon << " ";
            }
            cout << "\n";
        }//TSP
};//opttsp
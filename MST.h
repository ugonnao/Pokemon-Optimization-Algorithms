//Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <math.h>
#include <queue>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;


class MST{
    private:
        enum class Terrain{Land, Ocean, Coast};

        struct prims{ //a separate struct of prims table, not every part needs a prims table
            bool kv = 0; // whether vertex v has been added to MST
            double dv = numeric_limits<double>::infinity(); // lowest distance to MST
            int32_t pv = -1; // index of vertex's parent
        };//prims
 
        struct Coordinate{
            int x;
            int y;
            Terrain terrain;
        };//coordinate

        vector<prims> vecPrims;
        vector<Coordinate> coordList; 
        double infinity = numeric_limits<double>::infinity();
        double weight = 0;

        double calcDist(const Coordinate &uno, const Coordinate &dos){
            if ((uno.terrain == Terrain::Ocean && dos.terrain == Terrain::Land)
             || (uno.terrain == Terrain::Land && dos.terrain == Terrain::Ocean)){
                return infinity;
            }else{
                double xDiff = uno.x - dos.x; 
                double yDiff = uno.y - dos.y;
                double dist = (xDiff * xDiff) + (yDiff * yDiff);
                return sqrt(dist);
            }
        }//calcDist

    public:
        void read_MST(){
            Coordinate coord;
            size_t num_verticies;
            cin >> num_verticies;
            coordList.reserve(num_verticies);
            while(coordList.size() < num_verticies){
                cin >> coord.x >> coord.y;
                if(coord.x == 0 && coord.y == 0){
                    coord.terrain = Terrain::Coast;
                }else if(coord.x <= 0 && coord.y == 0){
                    coord.terrain = Terrain::Coast;
                }else if(coord.x == 0 && coord.y <= 0){
                     coord.terrain = Terrain::Coast;
                }else if(coord.x > 0){
                    coord.terrain = Terrain::Land;
                }else{
                    coord.terrain = (coord.y > 0) ? Terrain::Land:Terrain::Ocean; 
                }
                coordList.push_back(coord);
            }//while
        }//read_input

        void MST_Algorithm(){
            for(size_t i = 0; i < coordList.size(); i++){
                prims vertex;
                vecPrims.push_back(vertex);
            }//for
            //starting index of MST distance is 0
            size_t currNode = 0; 
            vecPrims[currNode].dv = 0;
            for(size_t i = 0; i < vecPrims.size(); i++){
                vecPrims[currNode].kv = true;
                for(size_t j = 0; j < vecPrims.size(); j++){
                    if(vecPrims[currNode].kv){//if currNode is discovered
                        double distance = calcDist(coordList[currNode], coordList[j]);
                        if(distance < vecPrims[j].dv && currNode != j && vecPrims[j].kv == false ){// distance comparison between current node and j node
                            vecPrims[j].dv = distance;      
                            vecPrims[j].pv = static_cast<int32_t>(currNode); //parent node, trainer is now at this location the next iteration
                        }
                    }//if
                }//2nd for
                double minimumDist = infinity;
                for(size_t j = 0; j < vecPrims.size(); j++){
                    if(vecPrims[j].dv < minimumDist && vecPrims[j].kv == false){
                        minimumDist = vecPrims[j].dv; //
                        currNode = j; // smallest edge distance
                    }
                }//2nd for
            }//first for
            for(size_t i = 0; i < vecPrims.size(); i++){
                if(vecPrims[i].dv == infinity){ //if infinity, MST invalid
                    // error
                    cerr << "Cannot construct MST\n";
                    exit(1);
                }else{
                    weight += vecPrims[i].dv;
                }
            }//for
            cout << weight << "\n";
            for(size_t i = 1; i < vecPrims.size(); ++i){
                if(i < static_cast<size_t>(vecPrims[i].pv)){
                    cout << i << " " << vecPrims[i].pv << "\n";
                }else{// print parent first
                    cout << vecPrims[i].pv << " " << i << "\n";
                }
            }//for
        }//MST
};//mst
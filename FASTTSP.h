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

class FASTTSP{
    private:
        struct Coordinate{
            int x;
            int y;
        };//coordinate

        vector<Coordinate> list;

        double calcDist(const Coordinate &uno, const Coordinate &dos){
            double xDiff = abs(uno.x - dos.x); 
            double yDiff = abs(uno.y - dos.y);
            double xSquared = xDiff * xDiff;
            double ySquared = yDiff * yDiff;
            double dist = xSquared + ySquared; 
            return sqrt(dist);
        }//calcDist

    public:
        void read_fasttsp(){
            Coordinate coord;
            size_t num_verticies;
            cin >> num_verticies;
            list.reserve(num_verticies);
            while(list.size() < num_verticies){
                cin >> coord.x >> coord.y;
                list.push_back(coord);
            }//while
        }//read_input
        void arbitraryInsertion(){
            //arbitrary Insertion
            size_t n = list.size(); 
            vector<size_t> tour;
            vector<bool>visited(n, false);

            //intialize first vertex
            tour.push_back(0);
            visited[0] = true; 
            // arbitrary pick second vertex
            tour.push_back(1);
            tour.push_back(0);
            visited[1] = true; 
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
            cout << totalCost << "\n";
            for(size_t pokemon = 0; pokemon < tour.size() - 1; pokemon++){
                cout << tour[pokemon] << " ";
            }//for
            cout << "\n";

            //Nearest Neighbor

            // size_t currNode = 0;
            // size_t n = list.size();
            // vector<bool> visited(n, false);
            // path.push_back(currNode);
            // visited[currNode] = true; 

            // for(size_t i = 1; i < n; i++){
            //     double minDist = infinity;
            //     size_t nextPokemon = numeric_limits<size_t>::max();
            //     for(size_t pokemon = 0; pokemon < n; pokemon++){
            //         double distance = calcDist(list[currNode], list[pokemon]);
            //         if(!visited[pokemon]  && distance < minDist){
            //             minDist = distance;
            //             nextPokemon = pokemon; 
            //         }
            //     }//for
            //     weight += minDist; 
            //     visited[nextPokemon] = true; 
            //     currNode = nextPokemon;
            //     path.push_back(currNode);
            // }//for
            // //return to starting position
            // weight += calcDist(list[currNode], list[0]);
            // cout << weight << "\n";
            // for(auto pokemon : path){
            //     cout << pokemon << " ";
            // }
            // cout << "\n";

            //Nearest Insertion

        //     size_t n = list.size();
        //     vector<bool> visited(n, false);
        //     vector<size_t> path;

        //    //Start with an initial partial tour of two nodes
        //     path.push_back(0);
        //     visited[0] = true;
        //     size_t closest = 1;
        //     double minDist = infinity;

        //     // Find the closest node to the starting node
        //     for(size_t i = 1; i < n; i++){
        //         double distance = calcDist(list[0], list[i]);
        //         if (distance < minDist) {
        //             minDist = distance;
        //             closest = i;
        //         }
        //     }//for

        //     path.push_back(closest);
        //     visited[closest] = true;
        //     double weight = minDist;

        //     //add nodes to the tour
        //     for(size_t i = 2; i < n; i++){
        //         //closest unvisited node to any node in path
        //         size_t nextPokemon = numeric_limits<size_t>::max();
        //         double minDist = infinity;

        //         for(size_t pokemon = 0; pokemon < n; pokemon++){
        //             if(!visited[pokemon]){
        //                 for(size_t node : path){
        //                     double distance = calcDist(list[pokemon], list[node]);
        //                     if(distance < minDist){
        //                         minDist = distance;
        //                         nextPokemon = pokemon;
        //                     }
        //                 }//3rd for
        //             }
        //         }//2nd for

        //         // best place to insert the node 
        //         double bestIncrease = infinity;
        //         auto insertPos = 0;

        //         for(size_t j = 0; j < path.size(); j++){
        //             size_t u = path[j];
        //             size_t v = path[(j + 1) % path.size()];

        //             double currIncrease = calcDist(list[u], list[nextPokemon]) +
        //                                 calcDist(list[nextPokemon], list[v]) -
        //                                 calcDist(list[u], list[v]);

        //             if(currIncrease < bestIncrease){
        //                 bestIncrease = currIncrease;
        //                 insertPos = static_cast<int>(j + 1);  // Insert after position j
        //             }
        //         }//for

        //         // Insert node
        //         path.insert(path.begin() + insertPos, nextPokemon);
        //         visited[nextPokemon] = true;
        //         weight += bestIncrease;
        //     }

        //     //Return to the starting node
        //     weight += calcDist(list[path.back()], list[path[0]]);

        //     cout << weight << "\n";
        //     for(auto pokemon : path){
        //         cout << pokemon << " ";
        //     }
        //     cout << "\n";
        }//arbitrary
};//fasttsp
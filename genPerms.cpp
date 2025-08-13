//Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include "OPTTSP.h"

using namespace std; 

template <typename T>
void genPerms(std::vector<T> &path, std::size_t permLength){
  if(permLength == path.size()){
    // Do something with the path
    return;
  }  // if ..complete path

  if (!promising(path, permLength)) {
    return;
  }  // if ..not promising

  for (size_t i = permLength; i < path.size(); ++i) {
    swap(path[permLength], path[i]);
    genPerms(path, permLength + 1);
    swap(path[permLength], path[i]);
  }  // for ..unpermuted elements
}  // genPerms()

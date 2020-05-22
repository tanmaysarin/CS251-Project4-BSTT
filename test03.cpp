/*test03.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(3) clear function and the destroy function") 
{
    
    bstt<int, int>  tree;

    REQUIRE(tree.size() == 0);
    
    int value;
    
    //insert some value in the tree
    tree.insert(30, value);
    tree.insert(15, value);
    tree.insert(50, value);
    tree.insert(70, value);
    tree.insert(8, value);
    tree.insert(25, value);
    tree.insert(20, value);
    tree.insert(28, value);
    
    REQUIRE(tree.size() == 8);
    
    //use the search function to search the keys
    bool a = tree.search(30, value);
    REQUIRE(a); //return true
    
    tree.clear();
    
    REQUIRE(tree.size() == 0);
}
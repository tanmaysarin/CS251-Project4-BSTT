/*test02.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(2) insert function and search function") 
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
    
    //trying to insert a key already present in the tree
    tree.insert(50, value);
    //check to see whether it is inserted or not
    REQUIRE(tree.size() == 8); //size should remain the same because the key was not inserted in the tree
    
    //use the search function to search the keys
    bool a = tree.search(30, value);
    REQUIRE(a); //return true
    
    bool b = tree.search(70, value);
    REQUIRE(b); //retrun true
    
    bool c = tree.search(8, value);
    REQUIRE(c); //return true
    
    bool d = tree.search(20, value);
    REQUIRE(d); //return true
    
    bool e = tree.search(100, value);
    REQUIRE(!e); //return false
}
/*test04.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(4) begin function and next function") 
{
    
    bstt<int, int>  tree;

    REQUIRE(tree.size() == 0);
    
    int value, key;
    
    //testing the empty tree
    tree.begin();
    bool d = tree.next(key);
    REQUIRE(d == false); //should return false
    
    //insert some value in the tree
    tree.insert(30, value);
    tree.insert(15, value);
    tree.insert(50, value);
    tree.insert(70, value);
    tree.insert(8, value);
    tree.insert(25, value);
    tree.insert(20, value);
    tree.insert(28, value);
    tree.insert(60, value);
    
    REQUIRE(tree.size() == 9);
    
    //use the search function to search the keys
    bool a = tree.search(30, value);
    REQUIRE(a); //return true
    
    //testing the begin functoin
    tree.begin();
    //testing the next function
    bool b = tree.next(key);
    REQUIRE(b); //should return true
    REQUIRE(key == 8); //the value of the key at this point is 15
    
    tree.next(key);
    REQUIRE(key == 15);
    
    tree.next(key);
    REQUIRE(key == 20);
    
    tree.next(key);
    REQUIRE(key == 25);
    
    tree.next(key);
    REQUIRE(key == 28);
    
    tree.next(key);
    REQUIRE(key == 30);
    
    tree.next(key);
    REQUIRE(key == 50);
    
    tree.next(key);
    REQUIRE(key == 60);
    
    tree.next(key);
    REQUIRE(key == 70);
    
    bool c = tree.next(key);
    REQUIRE(c == false); //should return false as there is no next key
    
    bool e = tree.next(key);
    REQUIRE(e == false); //should return false as there is no next key
}
/*test06.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(6) begin function and next function") 
{
    
    bstt<int, int>  tree;

    REQUIRE(tree.size() == 0);
    
    int value, key;
    
    //testing the empty tree
    tree.begin();
    bool d = tree.next(key);
    REQUIRE(d == false); //should return false
    
    //insert some value in the tree
    tree.insert(15, value);
    tree.insert(14, value);
    tree.insert(13, value);
    tree.insert(12, value);
    tree.insert(10, value);
    tree.insert(7, value);
    tree.insert(5, value);
    tree.insert(3, value);
    tree.insert(1, value);
    
    REQUIRE(tree.size() == 9);
    
//     tree.dump(cout);
    
    //use the search function to search the keys
    bool a = tree.search(5, value);
    REQUIRE(a); //return true
    
//     //testing the begin functoin
//     tree.begin();
//     //testing the next function
//     bool b = tree.next(key);
//     REQUIRE(b); //should return true
//     REQUIRE(key == 3); //the value of the key at this point is 15
    
//     tree.next(key);
//     REQUIRE(key == 5);
    
//     tree.next(key);
//     tree.next(key);
//     REQUIRE(key == 10);
    
//     tree.next(key);
//     REQUIRE(key == 12);
    
//     tree.next(key);
//     REQUIRE(key == 13);
    
//     tree.next(key);
//     REQUIRE(key == 14);
    
//     tree.next(key);
//     REQUIRE(key == 15);
    
//     bool c = tree.next(key);
//     REQUIRE(c == false); //should return false as there is no next key
    
//     bool e = tree.next(key);
//     REQUIRE(e == false); //should return false as there is no next key
}
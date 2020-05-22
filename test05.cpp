/*test05.cpp*/

//
// Unit tests for threaded binary search tree
//

#include <iostream>
#include <vector>

#include "bstt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(5) dump function") 
{
    
    bstt<int, int>  tree;

    REQUIRE(tree.size() == 0);
    
    int value, key;
    
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
    
//     tree.dump(cout);
    
    REQUIRE(tree(15) == 25);
    REQUIRE(tree(50) == 70);
    REQUIRE(tree(70) == key);
    
//     bstt<int, int> tree1(tree);
    
//     REQUIRE(tree1.size() == 9);
    
//     tree1.dump(cout);

      
}
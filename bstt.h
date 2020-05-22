/*bstt.h*/
// Name : Tanmay Sarin
// Project 4
// University of Illinois at Chicago - CS Undergrad
//
// Threaded binary search tree
// : Make a threaded bst implementation
//   to effectively use half of the null 
//   pointers in a normal bst.
//

#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded; //true=>right is threaded; false=>non-threaded
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* ptr = nullptr; //pointer to copy the node data from the begin function to the next function

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  bstt()
  {
    Root = nullptr;
    Size = 0;
  }
  
  //Operator function
  void insertPreorder(NODE* other) {
      
      if (other == NULL) 
          return; 
      if(other != NULL){
          /* first print data of node */
          insert(other->Key,other->Value);

          /* then recur on left subtree */
          insertPreorder(other->Left);  

          /* now recur on right subtree */
          if(!(other->isThreaded)){
              insertPreorder(other->Right); 
          }else{ //if it is a thread, then return from the function
              return;
          }
      }  
  }

  //
  // copy constructor
  //
  bstt(const bstt& other)
  {
      Root = NULL;
      Size = 0;
      insertPreorder(other.Root);
  }
  
  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~bstt()
  {
    destroy(Root);
  }
  
  //
  //destroy:
  //
  //Helper function to delete the nodes and free up the space
  //
  void destroy(NODE* cur)
  {
      if(cur == NULL) 
          return;
      else{
          destroy(cur->Left);
          if(cur->isThreaded == true){
              cur->Right = nullptr;
          }
          destroy(cur->Right);
          delete cur;
      }
      
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  bstt& operator=(const bstt& other)
  {
      clear();
      NODE* temp = other.Root;
      insertPreorder(temp);
      Size = other.Size;
      return *this;

  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    destroy(Root);
    Size = 0;
    Root = NULL;
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  // Time complexity:  O(1) 
  //
  int size() const
  {
    return Size;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) on average
  //
  bool search(KeyT key, ValueT& value) const
  {
      NODE* cur = Root;

      while (cur != nullptr)
      {
        if (key == cur->Key){ // already in tree
            value = cur->Value;
            return true;
        }  
          
        if (key < cur->Key)  // search left:
        {
          cur = cur->Left;
        }
        else //searches right
        {
            if(cur->isThreaded){ //if the right is threaded
                cur = nullptr; //declare the right as null ptr and stop the transversal
            }else{ //if right is not threaded
                cur = cur->Right;
            }
        }
      }//while  
  
      // if get here, not found
      return false;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  // Time complexity:  O(lgN) on average
  //
  void insert(KeyT key, ValueT value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // the key is in current/root
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        if(cur->isThreaded) //if the right is threaded
            cur = nullptr; //stop the transversal, meaning the thread is not there
        else //not threaded, meaning there is a node to go to
            cur = cur->Right;
      }
    }//while
    
    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    
    NODE* newNode = new NODE;
    newNode->Key = key;
    newNode->Value = value;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    newNode->isThreaded = true; //Mark all nodes as having a thread..
    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //

      if(prev == nullptr)
      {
         Root = newNode;  
      } 
      
      //Whenever we add a new node, we only have to worry about the right node of the new node...
      
      else if(key < prev->Key) //When we are adding a left node, we only have to worry about the right node of the new node
      {
         newNode->Right = prev; //make a thread to connect the right node of the new ptr to the parent node...
         prev->Left = newNode;//declare the new node
      }
      else //When we are adding the right node, we only have to worry about the right node of the new node
      {
         newNode->Right = prev->Right; // prev->right is a thread pointing to its parent
                                       //We connect the right pointer from the new node
                                       //to the "old thread pointer" of its parent.
         prev->isThreaded = false; //Mark the thread of the previous node to be non-existant now
         prev->Right = newNode; //declare the new node..
      }
    // 
    // 4. update size and we're done:
    //
    
    Size++;
  }

  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  ValueT operator[](KeyT key) const
  {
    NODE* prev = nullptr;
    NODE* cur = Root;
    
    while (cur != nullptr)
    {
      if (key == cur->Key)  // the key is in current/root
        return cur->Value;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        if(cur->isThreaded) //if the right is threaded
            cur = nullptr; //stop the transversal, meaning the thread is not there
        else //not threaded, meaning there is a node to go to
            cur = cur->Right;
      }
    }//while
    return ValueT{ };
  }

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  KeyT operator()(KeyT key) const
  {
    NODE* cur = Root;
    
    while (cur != nullptr)
    {
      if (key == cur->Key){  // the key is in current/root, i.e the key has been found...
      
          if(cur->isThreaded == true && cur->Right == nullptr){
              return KeyT{ }; //no right key exists, then break and return the default value
          }
          else if(cur->isThreaded == true && cur->Right != nullptr){
              cur = cur->Right; //transverse the thread to go to they key connected with the thread...
              return cur->Key; //return the key at the threaded link
          }
          else if (cur->isThreaded == false){
              cur = cur->Right;
              return cur->Key; //if there is no thread then just return the key to the right of the required key 
          }
      }

      if (key < cur->Key)  // search left:
      {
          cur = cur->Left;
      }
      else
      {
          if(cur->isThreaded) //if the right is threaded
              cur = nullptr; //stop the transversal, meaning the thread is not there
          else //not threaded, meaning there is a node to go to
              cur = cur->Right;
      }
    }//while

    return KeyT{ };
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  {
    NODE* cur = Root;
     
    if(cur == nullptr){ //check if the current node is null or not
        ptr = cur; // copy the data of the cur node to the ptr node
        return;
    }
    
    while(cur->Left != NULL){
        cur = cur->Left;
    }
    
    ptr = cur; //copy the data of the cur node to the ptr node
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    NODE* cur = ptr;
    // base case
    if(cur == nullptr){
        return false;
    }else{
    
        key = cur->Key; //return the key
        
        //Increment the pointer to the next inorder key
        if(cur->Left == NULL && cur->isThreaded == true){
            cur = cur->Right;
        }
        else if(cur->Left == NULL && cur->isThreaded == false){
            cur = cur->Right;
            while(cur->Left != NULL){ //check if anything is on the left, if yes, then go there
                cur = cur->Left;
            }
        }
        else if(cur->Left != NULL && cur->isThreaded == false){
                cur = cur->Right; //go to right node
                while(cur->Left != NULL){ //check if there is anything on the left
                    cur = cur->Left;
                }
        }
        else if(cur->Left != NULL && cur->isThreaded == true){

                cur = cur->Right;
        }

        ptr = cur; //copy the data of the cur node to the ptr node
        return true;
        
    }
    return false;
  }
  
  //
  // printInOrder:
  //
  // Helper function to print out
  // the keys in the dump function
  // in order.
  //
  void printInOrder(NODE* cur, ostream& output)const {
      if(cur == NULL){
          return;
      }
      else{
          printInOrder(cur->Left, output);
          
          if(cur->isThreaded == true && cur->Right != nullptr){
              output <<"(" << cur->Key << "," << cur->Value << "," << cur->Right->Key << ")" << endl;
              cur->Right = NULL;
          }else{
              output <<"(" << cur->Key << "," << cur->Value << ")" << endl;
          }
          
          printInOrder(cur->Right, output);
      }
   }

  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* BSTT ***********************" << endl;

    output << "** size: " << this->size() << endl;
    
    //
    // inorder traversal, with one output per line: either 
    // (key,value) or (key,value,THREAD)
    //
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
    
    printInOrder(Root,output);
    
    
    output << "**************************************************" << endl;
  }
	
};


/*
 * Copyright (C) 2023. Roger Doss. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * REFERENCES:
 * http://www.algolist.net/Data_structures/Binary_search_tree
 */
#ifndef _BST_H
#define _BST_H

#include <iostream>
using std::cout;
using std::endl;

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

class ValueList {
    public:
	unsigned int value;
	ValueList *next;
    ValueList(unsigned int _value)
        : value(_value)
    {
        next = NULL;
    }
};

class Value {
    public:
    unsigned int  value;
    unsigned int rvalue;
    Value()
        : value(0), rvalue(0)
    {
    }
    Value(int _value)
        : rvalue(_value)
    {
        value = inthash(_value);
        //cout << value << "," << rvalue << endl;
    }
    Value(const Value &obj)
    {
        this->value  = obj.value;
        this->rvalue = obj.rvalue;
    }
    Value &operator=(const Value &obj)
    {
        if(this == &obj) {
            return *this;
        }
        this->value  = obj.value;
        this->rvalue = obj.rvalue;
        return *this;
    }
    ~Value()
    {
    }
    operator int ()
    {
        return value;
    }

};

class BSTNode {
     
     private:
      
     Value value;
             
     BSTNode* left;
     BSTNode* right;

     BSTNode* next;

     public:
                            
     BSTNode(Value value) {
         this->value = value;
         left  = NULL;
         right = NULL;
         next  = NULL;
     }
     bool add(Value value);
     bool search(Value value);
     BSTNode *remove(Value value, BSTNode *parent);
     int  minValue();
     void setLeftChild(BSTNode *obj)
     {
         left = obj;
     }
     void setRightChild(BSTNode *obj)
     {
         right = obj;
     }
     BSTNode *getLeft()
     {
         return left;
     }
     BSTNode *getRight()
     {
         return right;
     }
     Value getValue()
     {
         return value;
     }
     void print(BSTNode *node)
     {
         if(node == NULL) {
             return;
         }
         print (node->left);
         printf("%d\n", node->value.rvalue);
         BSTNode *ptr = node->next;
         while(ptr) {
            printf("%d\n", ptr->value.rvalue);
            ptr = ptr->next;
         }
         print (node->right);
     }
};
 
class BinarySearchTree {
        
     private:
         
     ValueList *next;
     BSTNode* root;

     BinarySearchTree(const BinarySearchTree &obj);
     BinarySearchTree &operator=(const BinarySearchTree &obj);

     public:
                 
     BinarySearchTree() {
         next = NULL;
         root = NULL;
     }

     ~BinarySearchTree() {
        ValueList *ptr = next, *tmp;
        while(ptr) {
            remove(ptr->value);
            tmp = ptr;
            ptr = ptr->next;
            delete tmp;
        }
     }
     bool add(Value value);
     bool search(Value value);
     bool remove(Value value);
     void print()
     {
        root->print(root);
     }
};



// add
bool BinarySearchTree::add(Value value) {
 
      if (next == NULL) {
            next = new ValueList(value);
      } else if(next) {
            ValueList *ptr = new ValueList(value);
            ptr->next = next;
            next = ptr;
      }
      if (root == NULL) {
            root = new BSTNode(value);
            return true;
      } else
            return root->add(value);
}
 
bool BSTNode::add(Value value) {
      if (value.value == this->value.value) {
            // This is a collision.
            if(value.rvalue != this->value.rvalue) {
                if(!next) {
                    next = new BSTNode(value);
                } else {
                    BSTNode *ptr = new BSTNode(value);
                    ptr->next = next;
                    next = ptr;
                }
                return true;
            }
            return false;
      }
      else if (value.value < this->value.value) {
            if (left == NULL) {
                  left = new BSTNode(value);
                  return true;
            } else
                  return left->add(value);
      } else if (value.value > this->value.value) {
            if (right == NULL) {
                  right = new BSTNode(value);
                  return true;
            } else
                  return right->add(value);
      }
      return false;
}

// search
bool BinarySearchTree::search(Value value) {
      if (root == NULL)
            return false;
      else
            return root->search(value);
}
 
bool BSTNode::search(Value value) {
      if (value.value == this->value.value) {
            if(value.rvalue != this->value.rvalue) {
                BSTNode *ptr = next;
                while(ptr) {
                    if(ptr->value.rvalue == value.rvalue) {
                        return true;
                    }
                    ptr = ptr->next;
                }
                return false;
            }
            return true;
      }
      else if (value.value < this->value.value) {
            if (left == NULL) {
                  return false;
            }
            else
                  return left->search(value);
      } else if (value.value > this->value.value) {
            if (right == NULL) {
                  return false;
            }
            else
                  return right->search(value);
      }
      return false;
}

// delete
bool BinarySearchTree::remove(Value value) {

      if (root == NULL)
            return false;
      else {
            if (root->getValue() == value.value) {
                  BSTNode auxRoot(0);
                  auxRoot.setLeftChild(root);
                  BSTNode* removedNode = root->remove(value, &auxRoot);
                  root = auxRoot.getLeft();
                  if (removedNode != NULL) {
                        delete removedNode;
                        return true;
                  } else
                        return false;
            } else {
                  BSTNode* removedNode = root->remove(value, NULL);
                  if (removedNode != NULL) {
                        delete removedNode;
                        return true;
                  } else
                        return false;
            }
      }
}

BSTNode* BSTNode::remove(Value value, BSTNode *parent) {

      if (value.value < this->value.value) {
            if (left != NULL)
                  return left->remove(value, this);
            else
                  return NULL;
      } else if (value.value > this->value.value) {
            if (right != NULL)
                  return right->remove(value, this);
            else
                  return NULL;
      } else {
            if (this->value.rvalue == value.rvalue && next) {
                this->value = next->value;
                BSTNode *ptr = next;
                next = next->next;
                delete ptr;
                return NULL;
            } else if(this->value.rvalue != value.rvalue && next) {
                BSTNode *ptr = next, *prev = next;
                bool found = false;
                while(ptr) {
                    if(ptr->value.rvalue == value.rvalue) {
                        found = true;
                        if(prev == ptr) {
                            // Delete at root.
                            if(!ptr->next) {
                                delete ptr;
                                next = NULL;
                                return NULL;
                            } else {
                                next = next->next;
                                delete ptr;
                                return NULL;
                            }
                        } else {
                            // Delete a list node.
                            prev->next = ptr->next;
                            delete ptr;
                            return NULL;
                        }
                    }
                    prev = ptr;
                    ptr  = ptr->next;
                }
                if(!found) {
                    // Node was not found.
                }
                return NULL;
            }
            // Normal deletion otherwise.
            if (left != NULL && right != NULL) {
                  // This is the case where we are the parent of
                  // a left and right subtree.
                  this->value = right->minValue();
                  return right->remove(this->value, this);
            } else if (parent->left == this) {
                  // We are the left subtree.
                  parent->left = (left != NULL) ? left : right;
                  return this;
            } else if (parent->right == this) {
                  // Same as above.
                  parent->right = (left != NULL) ? left : right;
                  return this;
            }
      }
      return NULL;
}

int BSTNode::minValue() {
      if (left == NULL)
            return value.value;
      else
            return left->minValue();
}

#endif

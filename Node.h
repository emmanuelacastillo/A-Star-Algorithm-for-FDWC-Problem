/* Description:
* This file contains the data model
* and other methods that deals
* with the Nodes.
*
*/


#ifndef NODE_H
#define NODE_H

#include <queue>
#include <vector>

#include "State.h"

using namespace std;

class Node
{
private:
   Node *parentNode;
   State *state;
   int actualCost; // g
   int heuristicCost; // h
public:
   Node *getNode();
   State *getState();
   void setState(State *state);
   void setParentNode(Node *node);
   int getPathCost() const;  // f
   int getActualCost() const;
   void setActualCost(int actualCost);
   int getHeuristicCost() const;
   void setHeuristicCost(int heuristicCost);
};

struct CompareNodes
{
   bool operator()(Node *p1, Node *p2)
   {
      return p1->getPathCost() > p2->getPathCost();
   }
};

bool isBetterPathCostNode(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, Node *nodeToCheck);

void swapNode(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, Node *nodeToReplace);

Node *getInitialNode();

#endif
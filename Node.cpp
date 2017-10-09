#include "Node.h"
#include "State.h"

using namespace std;

State *Node::getState()
{
   return Node::state;
}

void Node::setState(State *state)
{
   Node::state = state;
}

Node *Node::getNode()
{
   return Node::parentNode;
}

void Node::setParentNode(Node *node)
{
   Node::parentNode = node;
}

int Node::getPathCost() const
{
   return Node::actualCost + Node::heuristicCost;
}

int Node::getActualCost() const
{
   return Node::actualCost;
}

void Node::setActualCost(int actualCost)
{
   Node::actualCost = actualCost;
}

int Node::getHeuristicCost() const
{
   return Node::heuristicCost;
}

void Node::setHeuristicCost(int heuristicCost)
{
   Node::heuristicCost = heuristicCost;
}

bool operator < (const Node &lhs, const Node &rhs)
{
   return lhs.getPathCost() > rhs.getPathCost();
}

bool isBetterPathCostNode(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, Node *nodeToCheck)
{
   priority_queue<Node*, vector<Node*>, CompareNodes> copiedFrontier = frontier;
   while (!copiedFrontier.empty())
   {
      Node *node = copiedFrontier.top();
      if (isEqual(node->getState(), nodeToCheck->getState()))
      {
         if (nodeToCheck->getPathCost() < node->getPathCost())
         {
            return true;
         }
      }
      copiedFrontier.pop();
   }

   return false;
}

void swapNode(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, Node *nodeToReplace)
{
   priority_queue<Node*, vector<Node*>, CompareNodes> copiedFrontier = frontier;
   priority_queue<Node*, vector<Node*>, CompareNodes> newFrontier;
   while (!copiedFrontier.empty())
   {
      Node *node = copiedFrontier.top();
      if (isEqual(node->getState(), nodeToReplace->getState()))
      {
         newFrontier.push(nodeToReplace);
      }
      else
      {
         newFrontier.push(node);
      }
      
      copiedFrontier.pop();
   }
   
   while(!frontier.empty())
   {
      frontier.pop();
   }
   
   while(!newFrontier.empty())
   {
      frontier.push(newFrontier.top());
      newFrontier.pop();
   }
}

Node *getInitialNode()
{
   State *initialState = getInitialState();
   Node *initialNode = new Node();
   initialNode->setState(initialState);
   initialNode->setActualCost(0);
   initialNode->setHeuristicCost(3);

   return initialNode;
}

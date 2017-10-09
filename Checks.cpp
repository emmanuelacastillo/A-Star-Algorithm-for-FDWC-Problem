#include "Checks.h"

bool isStateExistInVector(vector<State*> states, State *stateToFind)
{
   vector<State*>::iterator it;
   for (it = states.begin(); it != states.end(); it++)
   {
      if (isEqual(*it, stateToFind))
         return true;
   }
   return false;
}

bool isStateExistInQueue(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, State *stateToFind)
{
   priority_queue<Node*, vector<Node*>, CompareNodes> copiedFrontier = frontier;

   while (!copiedFrontier.empty())
   {
      Node *node = copiedFrontier.top();
      if (isEqual(node->getState(), stateToFind))
      {
         return true;
      }
      copiedFrontier.pop();
   }

   return false;
}

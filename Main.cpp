/* Programming Assignment 1: Farmer, Duck, Wolf, Corn (FDWC)
 * Author: Emmanuel A. Castillo
 * Description:
 * An A* algorithm is implemented against the FDWC problem.
 * With the provided initial state, nodes are expanded and other nodes
 * are generated until the goal state is reached. Valid states
 * are those where a Wolf and Duck are not alone in one side and
 * a Duck and Corn is also not alone in one side.
 *
 */
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

#include "State.h"
#include "Node.h"
#include "Action.h"
#include "Checks.h"

using namespace std;

/* Goal state and Actions */
State *goalState = getGoalState();
vector<Action*> actions = getActions();

/* Methods to print to screen */
inline string getItemChar(Item item)
{
   if (item == FARMER)
      return "F";
   if (item == WOLF)
      return "W";
   if (item == DUCK)
      return "D";
   if (item == CORN)
      return "C";

   return "";
}

inline void printItems(Node *node)
{
   vector<Item> leftItems;
   vector<Item> rightItems;
   vector<Item>::iterator it;

   cout << "[";
   leftItems = node->getState()->getLeftSide();
   for (it = leftItems.begin(); it != leftItems.end(); it++)
   {
      cout << getItemChar(*it).c_str();
   }

   cout << "||";

   rightItems = node->getState()->getRightSide();
   for (it = rightItems.begin(); it != rightItems.end(); it++)
   {
      cout << getItemChar(*it).c_str();
   }
   cout << "] ";
   cout << "h=" << node->getHeuristicCost() << " ";
   cout << "g=" << node->getActualCost() << " ";
   cout << "f=" << node->getPathCost() << " ";
}

inline void printFrontier(priority_queue<Node*, vector<Node*>, CompareNodes> frontier)
{
   cout << "Fontier nodes are: ";

   priority_queue<Node*, vector<Node*>, CompareNodes> copiedFrontier = frontier;

   while (!copiedFrontier.empty())
   {
      printItems(copiedFrontier.top());
      copiedFrontier.pop();
   }
   cout << "\n";
}

inline void printExpand(Node *node)
{
   cout << "Expand: ";
   printItems(node);
   cout << "\n";
}

inline void printGenerated(Node *node, const char *regenerated, Node *expandedNode)
{
   const char *updatedF = node->getPathCost() != expandedNode->getPathCost() ? "Yes" : "No";

   cout << "Generated: \n";
   cout << "\tState and Value is ";
   printItems(node);
   cout << "\n";
   cout << "\tRegenerated is ";
   cout << "\t" << regenerated;
   cout << "\n";
   cout << "\tUpdated f?";
   cout << "\t" << updatedF;
   cout << "\n";
}


int main()
{
   /* Frontier is initialize to a priority queue that puts the *
    * node with the lowest path cost on top of the queue.      */
   priority_queue<Node*, vector<Node*>, CompareNodes> frontier;
   frontier.push(getInitialNode());

   /* Explored states are kept track to determine whether they *
    * should be added to the frontier.                         */
   vector<State*> exploredStates;

   /* Frontier is loop through searching for the goal state or *
    * until all nodes are searched through on the frontier.    */
   do
   {
      printFrontier(frontier);

      if (frontier.size() <= 0)
      {
         cout << "No Goal Found.\n";
         return 1;
      }

      /* The node with the lowest cost is expanded its children *
       * is added to the frontier if it is a valid state        */
      Node *expandedFrontierNode = frontier.top();

      printExpand(expandedFrontierNode);

      frontier.pop();
      exploredStates.push_back(expandedFrontierNode->getState());

      if (isEqual(expandedFrontierNode->getState(), goalState))
      {
         cout << "Goal Found.\n";
         return 0;
      }
      else
      {
         Node *possibleChildNode;
         vector<Action*>::iterator it;
         /* As long as the goal is found, the expanded node's     *
          * children are added to the frontier based on the       *
          * possible actions that can occur on the currents state */
         for (it = actions.begin(); it != actions.end(); it++)
         {
            possibleChildNode = (*it)->doAction(expandedFrontierNode);
            /* If a null pointer is returned, that means the state   *
             * transition from the action is not a valid state       */
            if (possibleChildNode == NULL)
            {
               continue;
            }
            else
            {
               /* Children nodes are added to the frontier if it has not been explored yet and  *
                * it is not in the frontier                                                     */
               if (!isStateExistInVector(exploredStates, possibleChildNode->getState()) &&
                   !isStateExistInQueue(frontier, possibleChildNode->getState()))
               {
                  printGenerated(possibleChildNode, "No", expandedFrontierNode);
                  frontier.push(possibleChildNode);
               }
               /* Children node is swapped if its state exist in the frontier already and *
                * it has a better cost than the one in the frontier                       */
               else if (isStateExistInQueue(frontier, possibleChildNode->getState()))
               {
                  if (isBetterPathCostNode(frontier, possibleChildNode))
                  {
                     printGenerated(possibleChildNode, "Yes", expandedFrontierNode);
                     swapNode(frontier, possibleChildNode);
                  }
               }
            }
         }
      }
   } while (true);
}

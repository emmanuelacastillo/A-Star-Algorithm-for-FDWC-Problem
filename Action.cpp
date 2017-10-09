#include <algorithm>
#include <list>
#include <vector>

#include "Action.h"
#include "State.h"

using namespace std;

inline bool isMovingItemsExist(vector<Item> items, Item item1, Item item2)
{
   vector<Item>::iterator it;
   int maxCount = 0;

   int itemExistCount = 0;
   if (item1 != INVALID)
      itemExistCount++;
   if (item2 != INVALID)
      itemExistCount++;

   for (it = items.begin(); it != items.end(); it++)
   {
      if ((*it) == item1 || ((*it) == item2))
         maxCount++;

      if (maxCount == itemExistCount)
         return true;
   }

   return false;
}

inline State *moveItemsToNewState(bool isLeftSideUpdate, vector<Item> sideToUpdate, vector<Item> sideToRemove, Item firstItemToMove, Item secondItemToMove)
{
   if (firstItemToMove != INVALID)
      sideToUpdate.push_back(firstItemToMove);

   if (secondItemToMove != INVALID)
      sideToUpdate.push_back(secondItemToMove);

   for (unsigned i = 0; i < sideToRemove.size(); i++) {
      if (sideToRemove.at(i) == firstItemToMove || sideToRemove.at(i) == secondItemToMove)
      {
         sideToRemove.erase(sideToRemove.begin() + i);
         i--;
      }
   }

   State *newState = new State();
   if (isLeftSideUpdate)
   {
      newState->setLeftSide(sideToUpdate);
      newState->setRightSide(sideToRemove);
   }
   else
   {
      newState->setRightSide(sideToUpdate);
      newState->setLeftSide(sideToRemove);
   }

   return newState;
}

inline Node *getChildNode(Node *parentNode, bool isLeftSideUpdate, vector<Item> sideToUpdate, vector<Item> sideToRemove, Item firstItemToMove, Item secondItemToMove)
{
   State *newState = moveItemsToNewState(isLeftSideUpdate, sideToUpdate, sideToRemove, firstItemToMove, secondItemToMove);

   if (isInvalidState(newState))
      return NULL;

   int g = parentNode->getPathCost();
   int h = newState->getRightSide().size();
   
   if(isMovingItemsExist(newState->getRightSide(), FARMER, INVALID))
      h = h - 1;

   Node *node = new Node();
   node->setState(newState);
   node->setParentNode(parentNode);
   node->setActualCost(g);
   node->setHeuristicCost(h);

   return node;
}

Node *FarmerTakeWolfLeft::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getRightSide(), FARMER, WOLF) || parentNode->getState()->getRightSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, true, parentNode->getState()->getLeftSide(), parentNode->getState()->getRightSide(), FARMER, WOLF);
}

Node *FarmerTakeWolfRight::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getLeftSide(), FARMER, WOLF) || parentNode->getState()->getLeftSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, false, parentNode->getState()->getRightSide(), parentNode->getState()->getLeftSide(), FARMER, WOLF);
}

Node *FarmerTakeDuckLeft::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getRightSide(), FARMER, DUCK) || parentNode->getState()->getRightSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, true, parentNode->getState()->getLeftSide(), parentNode->getState()->getRightSide(), FARMER, DUCK);
}

Node *FarmerTakeDuckRight::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getLeftSide(), FARMER, DUCK) || parentNode->getState()->getLeftSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, false, parentNode->getState()->getRightSide(), parentNode->getState()->getLeftSide(), FARMER, DUCK);
}

Node *FarmerTakeCornLeft::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getRightSide(), FARMER, CORN) || parentNode->getState()->getRightSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, true, parentNode->getState()->getLeftSide(), parentNode->getState()->getRightSide(), FARMER, CORN);
}

Node *FarmerTakeCornRight::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getLeftSide(), FARMER, CORN) || parentNode->getState()->getLeftSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, false, parentNode->getState()->getRightSide(), parentNode->getState()->getLeftSide(), FARMER, CORN);
}

Node *FarmerTakeHimselfLeft::doAction(Node *parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getRightSide(), FARMER, INVALID) || parentNode->getState()->getRightSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, true, parentNode->getState()->getLeftSide(), parentNode->getState()->getRightSide(), FARMER, INVALID);
}

Node *FarmerTakeHimselfRight::doAction(Node * parentNode)
{
   if (!isMovingItemsExist(parentNode->getState()->getLeftSide(), FARMER, INVALID) || parentNode->getState()->getLeftSide().size() == 0)
      return NULL;

   return getChildNode(parentNode, false, parentNode->getState()->getRightSide(), parentNode->getState()->getLeftSide(), FARMER, INVALID);
}

inline bool isInvalidItemCombo(std::vector<Item> items)
{
   if(isMovingItemsExist(items, WOLF, DUCK) && !isMovingItemsExist(items, FARMER, INVALID))
      return true;

   if (isMovingItemsExist(items, DUCK, CORN) && !isMovingItemsExist(items, FARMER, INVALID))
      return true;

   return false;
}

vector<Action*> getActions()
{
   vector<Action*> actions;

   actions.push_back(new FarmerTakeWolfLeft());
   actions.push_back(new FarmerTakeWolfRight());
   actions.push_back(new FarmerTakeDuckLeft());
   actions.push_back(new FarmerTakeDuckRight());
   actions.push_back(new FarmerTakeCornLeft());
   actions.push_back(new FarmerTakeCornRight());
   actions.push_back(new FarmerTakeHimselfLeft());
   actions.push_back(new FarmerTakeHimselfRight());

   return actions;
}

bool isInvalidState(State *state)
{
   return (isInvalidItemCombo(state->getLeftSide()) || isInvalidItemCombo(state->getRightSide()));
}

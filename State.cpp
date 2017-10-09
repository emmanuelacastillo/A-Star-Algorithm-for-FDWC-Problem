#include <algorithm>
#include <queue>
#include <vector>

#include "State.h"

using namespace std;

bool isEqual(State *lState, State *rState)
{
   vector<Item> lVectorLeftSide = lState->getLeftSide();
   vector<Item> rVectorLeftSide = rState->getLeftSide();

   sort(lVectorLeftSide.begin(), lVectorLeftSide.end());
   sort(rVectorLeftSide.begin(), rVectorLeftSide.end());

   if (lVectorLeftSide != rVectorLeftSide)
      return false;

   vector<Item> lVectorRightSide = lState->getRightSide();
   vector<Item> rVectorRightSide = rState->getRightSide();

   sort(lVectorRightSide.begin(), lVectorRightSide.end());
   sort(rVectorRightSide.begin(), rVectorRightSide.end());


   return lVectorRightSide == rVectorRightSide;
}

State *getInitialState()
{
   vector<Item> initialLeftSide;
   vector<Item> initialRightSide;
   initialRightSide.push_back(FARMER);
   initialRightSide.push_back(WOLF);
   initialRightSide.push_back(DUCK);
   initialRightSide.push_back(CORN);

   State *state = new State();
   state->setLeftSide(initialLeftSide);
   state->setRightSide(initialRightSide);

   return state;
}

State *getGoalState()
{
   vector<Item> goalLeftSide;
   goalLeftSide.push_back(FARMER);
   goalLeftSide.push_back(WOLF);
   goalLeftSide.push_back(DUCK);
   goalLeftSide.push_back(CORN);

   vector<Item> goalRightSide;

   State *state = new State();
   state->setLeftSide(goalLeftSide);
   state->setRightSide(goalRightSide);

   return state;
}

vector<Item> State::getLeftSide()
{
   return State::leftSide;
}

void State::setLeftSide(vector<Item> items)
{
   State::leftSide = items;
}

vector<Item> State::getRightSide()
{
   return State::rightSide;
}

void State::setRightSide(vector<Item> items)
{
   State::rightSide = items;
}

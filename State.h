/* Description:
 * This file contains the data model
 * for the State as well as the Items
 * that can be contains in the States.
 *
 */

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <queue>

using namespace std;

enum Item { FARMER, WOLF, DUCK, CORN, INVALID };

class State
{
private:
   vector<Item> leftSide;
   vector<Item> rightSide;
public:
   vector<Item> getLeftSide();
   void setLeftSide(vector<Item> items);
   vector<Item> getRightSide();
   void setRightSide(vector<Item> items);
};

bool isEqual(State *lState, State *rState);

State *getInitialState();

State *getGoalState();

#endif
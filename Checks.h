/* Description:
* This file is a utility class that checks if a state
* exist in either the explored state or frontier.
*
*/

#ifndef CHECKS_H
#define CHECKS_H

#include <vector>
#include <queue>

#include "State.h"
#include "Node.h"

bool isStateExistInVector(vector<State*> states, State *stateToFind);

bool isStateExistInQueue(priority_queue<Node*, vector<Node*>, CompareNodes> frontier, State *stateToFind);

#endif
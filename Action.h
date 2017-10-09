/* Description:
 * This file contains the base class and implementation
 * of Actions that can occur on states within
 * the FDWC problem.
 *
 */

#ifndef ACTION_H
#define ACTION_H

#include "Node.h"
#include <list>

class Action
{
public:
   virtual Node *doAction(Node *parentNode) = 0;
};

class FarmerTakeWolfLeft : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeWolfRight : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeDuckLeft : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeDuckRight : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeCornLeft : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeCornRight : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeHimselfLeft : public Action
{
public:
   Node *doAction(Node *parentNode);
};

class FarmerTakeHimselfRight : public Action
{
public:
   Node *doAction(Node *parentNode);
};

list<Action *> getActions();

bool isInvalidState(State *state);

#endif
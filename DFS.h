//
// Created by oem on 15/01/2020.
//

#ifndef EXX4_DFS_H
#define EXX4_DFS_H

#include "CommonSearcher.h"
#include <iostream>
#include <algorithm>
#include "stack"

using namespace std;

template<class T>
class DFS : public CommonSearcher<string, T> {
public:
    string search(Searchable<T> *searchable) override {
        int numEvaluatedNodes = 0;
        vector<State<T> *> visited;
        stack<State<T> *> openStack;
        this->setSearchable(searchable);
        State<T> *startState = this->getSearchable()->getInitialeState();

        visited.push_back(startState);
        openStack.push(startState);
        while (openStack.size() > 0) {

            State<T> *curState = openStack.top();
            openStack.pop();
            // updating the number of states we visited in
            this->evaluatedNodes++;
            numEvaluatedNodes++;

            // ending condition to the recursion
            if ((*curState).Equals((this->getSearchable())->getGoalState())) {
                string line = this->backTrace(curState);
                return line;
            }
            // entering the successors to the priority list too
            list<State<T> *> successors = (this->getSearchable())->createSuccessors(curState);
            for (State<T> *n: successors) {
                if (!checkIfVisitedContains(visited, n)) {
                    n->setCameFRom(curState);
                    n->setTrailCost(curState->getTrailCost() + n->getCost());
                    openStack.push(n);
                    visited.push_back(n);
                }
            }
        }
        // if there is no solution
        return "";
    }

    /** iterating over the visited vector in order to see if a certain state is already in it**/
    bool checkIfVisitedContains(vector<State<T> *> visited, State<T> *curState) {
        for (auto it = visited.begin(); it != visited.end(); ++it) {
            if (curState->Equals(*it)) {
                return true;
            }
        }
        return false;
    }
};

#endif //EXX4_DFS_H

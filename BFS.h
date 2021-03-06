//
// Created by oem on 15/01/2020.
//

#ifndef EXX4_BFS1_H
#define EXX4_BFS1_H
//
// Created by oem on 14/01/2020.
//

#ifndef EXX4_BFS_H
#define EXX4_BFS_H

#include "CommonSearcher.h"
#include <iostream>
#include <algorithm>
#include "queue"

using namespace std;

template<class T, class solution>
class BFS : public CommonSearcher<solution, T> {
private:
    int numevaluatedNodes = 0;
public:
    /** looking for a path to the given goal state with the smallest cost **/
    solution search(Searchable<T> *searchable) override {
        numevaluatedNodes = 0;
        vector<State<T> *> visited;
        // we use queue in order to get the first element we entered
        queue<State<T> *> openQueue;
        this->setSearchable(searchable);

        visited.push_back(searchable->getInitialeState());
        openQueue.push(searchable->getInitialeState());
        while (!openQueue.empty()) {
            State<T> *curState = openQueue.front();
            openQueue.pop();
            numevaluatedNodes++;
            visited.push_back(curState);

            if ((*curState).Equals(searchable->getGoalState())) {
                return this->backTrace(curState);
            }

            // entering the successors to the priority list too
            list<State<T> *> successors = searchable->createSuccessors(curState);
            for (State<T> *n: successors) {
                auto iter = find(visited.begin(), visited.end(), n);
                // if we didn't visit in this state before
                if (iter == visited.end()) {
                    visited.push_back(n);
                    openQueue.push(n);
                    n->setCameFRom(curState);
                    n->setTrailCost(curState->getTrailCost() + n->getCost());
                }
            }
        }
        // if there is no solution
        throw "no solution";
    }

    /** clone **/
    BFS *copy() {
        return new BFS();
    }

    /** returns the number of nodes we visited in the algorithm**/

    int getNumberOfNodesEvaluated() override {
        return this->numevaluatedNodes;
    }
};

#endif //EXX4_BFS_H

#endif //EXX4_BFS_H

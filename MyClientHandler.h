//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_MYCLIENTHANDLER_H
#define EXX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Server.h"
#include "Searchable.h"
#include "Point.h"
#include "deque"
#include "State.h"

//template<class problem, class solution>
class MyClientHandler : public ClientHandler {
private:
    deque<string> dequeStrings;
    Solver<Searchable<Point>, string> *solver;
    CacheManager<string, string> *cm;
    Searchable<Point> *matrix;
    string problem = "";
public:
    // the server's problen is from type Searchable that is from type Point
    MyClientHandler(Solver<Searchable<Point>, string> *solverIn, CacheManager<string, string> *cmIn);

    void handleClient(int client_socket);

    void buildProblem();

    string edit(string s);

    void buildMatrix(int rows, int cols);
};


#endif //EXX4_MYCLIENTHANDLER_H

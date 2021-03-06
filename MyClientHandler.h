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
#include "MatrixMySearch.h"

class MyClientHandler : public ClientHandler {
private:
    deque<string> dequeStrings;
    Solver<Searchable<Point> *, string> *solver;
    CacheManager<string, string> *cm;
public:
    // the server's problen is from type Searchable that is from type Point
    MyClientHandler(Solver<Searchable<Point> *, string> *solverIn, CacheManager<string, string> *cmIn);

    MyClientHandler(const MyClientHandler &);

    void handleClient(int client_socket);

    MatrixMySearch *buildProblem();

    string edit(string s);

    MatrixMySearch *buildMatrix(int rows, int cols);

    void deleteDeque(deque<string> *deque);

    ClientHandler *copy();
};


#endif //EXX4_MYCLIENTHANDLER_H

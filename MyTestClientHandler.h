//
// Created by oem on 09/01/2020.
//

#ifndef EXX4_MYTESTCLIENTHANDLER_H
#define EXX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"


class MyTestClientHandler : public ClientHandler {
private:
    Solver<string, string> *solver;
    CacheManager<string, string> *cm;

public:
    MyTestClientHandler(Solver<string, string> *solverIn, CacheManager<string, string> *cashIn);

    MyTestClientHandler(const MyTestClientHandler &obj);

    void handleClient(int client_socket);

    ClientHandler *copy() override;
};


#endif //EXX4_MYTESTCLIENTHANDLER_H

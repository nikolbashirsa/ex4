//
// Created by oem on 09/01/2020.
//
#include <unistd.h>
#include "MyClientHandler.h"
#include "Searchable.h"
#include "MatrixMySearch.h"
#include "SearchSolver.h"

using namespace std;

MyClientHandler::MyClientHandler(Solver<Searchable<Point> *, string> *solverIn,
                                 CacheManager<string, string> *cmIn) : solver(solverIn), cm(cmIn) {}

/** read line by line
//when getting to last two lines get the point x,y of the first
//create searchable matrix
//call matrix constructor with start point end point **/
void MyClientHandler::handleClient(int client_socket) {
    std::size_t sizeLine = 0;
    string megaLine = "";
    string line = "";
    char buffer[1] = {0};
    int flag = 1;
    deleteDeque(&this->dequeStrings);
    while (true) {
        while (flag) {
            ::read(client_socket, buffer, 1);
            if (buffer[0] != '\n') {
                line = line + buffer;
                if (line.find("end") != std::string::npos) {
                    flag = 0;
                }
            } else {
                flag = 0;
            }
        }
        if (line.find("end") != std::string::npos) {
            break;
        }
        // building a mega line for the FileCacheManager
        dequeStrings.push_back(line);
        megaLine += line;
        flag = 1;
        line = "";
    }
    // building the problem - the matrix
    MatrixMySearch *matrixProb = buildProblem();
    //Searchable<Point> *matrix = &matrixProb;
    // checking if the problem has a solution in the cashManeger
    if (this->cm->isSolutionExist(megaLine)) {
        // there is a solution - returning it to the client
        string sol = cm->getSolution(megaLine);
        sizeLine = sol.length();
        char const *solution = (sol).c_str();
        //std::cout << solution << endl;
        int is_sent = send(client_socket, solution, sizeLine, 0);
        if (is_sent == -1) {
            std::cout << "Error sending message reveres" << std::endl;
        } else {
            std::cout << "solution  message sent to server" << std::endl;
        }
    } else {
        // there is'nt a solution - solving the problem, saving it in the cache
        string solution1 = "";
        try {
            solution1 = solver->solve(matrixProb);
            cm->saveSolution(megaLine, &solution1);
        } catch (const char *e) {
            //std::cout << "there is'nt a solution to the problem" << endl;
            solution1 = "there is'nt a solution to the problem";
        }
        sizeLine = solution1.size();
        // returning to the client the solution
        char const *solution = (solution1).c_str();
        //std::cout << solution << endl;
        int is_sent = send(client_socket, solution, sizeLine, 0);
        if (is_sent == -1) {
            std::cout << "Error sending message reveres" << std::endl;
        } else {
            std::cout << "solution  message sent to server" << std::endl;
        }
    }
}

/** building Matrix class - it's the problen we need to solve in this class **/
MatrixMySearch *MyClientHandler::buildProblem() {
    // minus 2 because we also have the start and end in the deque
    int rows = this->dequeStrings.size() - 2;
    int cols = 1;
    // receiving a line of a row from the deque
    string line = this->dequeStrings.front();
    for (unsigned int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            cols += 1;
        }
    }
    // building a matrix
    return buildMatrix(rows, cols);
}

string MyClientHandler::edit(string s) {
    size_t prev = 0, pos;
    while ((pos = s.find_first_of(" ", prev)) != std::string::npos) {
        string cut1 = s.substr(prev, pos);
        string cut2 = s.substr(pos + 1, s.length());
        s = cut1 + cut2;
    }
    return s;
}

/** building a matrix **/
MatrixMySearch *MyClientHandler::buildMatrix(int rows, int cols) {
    const int r = rows;
    const int c = cols;
    MatrixMySearch *m = (new MatrixMySearch(r, c, this->dequeStrings));
    return m;
}

/** deleting the elements in the deque**/
void MyClientHandler::deleteDeque(deque<string> *deque) {
    while (deque->size() > 0) {
        deque->pop_front();
    }
}

MyClientHandler::MyClientHandler(const MyClientHandler &obj) {
    dequeStrings = *(new deque<string>());
    solver = new SearchSolver<Searchable<Point> *, string, Point>((Searcher<string, Point> *) (obj.solver->copy()));
    cm = obj.cm->copy();
}

/** clone **/
ClientHandler *MyClientHandler::copy() {
    return new MyClientHandler(*this);
}



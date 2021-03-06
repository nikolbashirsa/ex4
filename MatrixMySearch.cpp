//
// Created by oem on 10/01/2020.
//
#include "MatrixMySearch.h"
#include "Point.h"

MatrixMySearch::MatrixMySearch(const int rowsIn, const int columnsIn, deque<string> dequeStringsIn) {
    this->rows = rowsIn;
    this->columns = columnsIn;
    const int rowsConst = const_cast<int &>(this->rows);
    const int colsConst = const_cast<int &>(this->columns);
    this->matrixOfStates = static_cast<State<struct Point> ***>(malloc(rowsConst * sizeof(State<Point> *)));
    for (int i = 0; i < rows; i++) {
        this->matrixOfStates[i] = static_cast<State<struct Point> **>(malloc(colsConst * sizeof(State<Point> *)));
    }
    this->dequeStrings = dequeStringsIn;
    // initializing the matrix
    initializeMatrix();
}

/** returns the start state in the matrix**/
State<Point> *MatrixMySearch::getInitialeState() {
    return this->startState;
}

/** returns the goal state in the matrix**/
State<Point> *MatrixMySearch::getGoalState() {
    return this->goalState;
}

/** returns the cost (x and y) of a state in the matrix**/
double MatrixMySearch::getCostInMatrix(int row, int col) {
    return this->matrixOfStates[row][col]->getCost();
}

/** returns the location (x and y) of a state in the matrix**/
std::pair<int, int> MatrixMySearch::getLocationInSearchable(State<Point> *state) {
    int x = state->getState().x;
    int y = state->getState().y;
    return std::make_pair(x, y);
}

/** entering all the valis neighbor states into a list nd returning it**/
list<State<Point> *> MatrixMySearch::createSuccessors(State<Point> *s) {
    Point p = (s->getState());
    int rowP = p.x;
    int colP = p.y;
    list<State<Point> *> *listStates = new list<State<Point> *>();

    if (rowP != this->rows - 1) {
        if (isValidState(this->matrixOfStates[rowP + 1][colP])) {
            listStates->push_back(this->matrixOfStates[rowP + 1][colP]);
        }
    }
    if (rowP != 0) {
        if (isValidState(this->matrixOfStates[rowP - 1][colP])) {
            listStates->push_back(this->matrixOfStates[rowP - 1][colP]);
        }
    }
    if (colP != this->columns - 1) {
        if (isValidState(this->matrixOfStates[rowP][colP + 1])) {
            listStates->push_back(this->matrixOfStates[rowP][colP + 1]);
        }
    }
    if (colP != 0) {
        if (isValidState(this->matrixOfStates[rowP][colP - 1])) {
            listStates->push_back(this->matrixOfStates[rowP][colP - 1]);
        }
    }
    return *listStates;
}

/** checks that a state in the matrix is valid and we can move to it**/
bool MatrixMySearch::isValidState(State<Point> *s) {
    return s->getCost() != -1;
}

/** check if a state is one of the goal's states**/
bool MatrixMySearch::isGoal(State<Point> *s) {
    return (s->Equals(this->getGoalState()));
}

/** building a matrix of states according to the strings in the deque**/
void MatrixMySearch::initializeMatrix() {
    int col = 0, row = 0;
    for (; row < this->rows; row++, col = 0) {
        string line = this->dequeStrings.front();
        int *arrayOfNum = this->editcomma(line);
        for (; col < this->columns; col++) {
            int cost = arrayOfNum[col];
            const int x = row;
            const int y = col;
            Point *p = new Point(x, y);
            (this->matrixOfStates)[row][col] = (new State<Point>(*p, cost, cost));
        }
        this->dequeStrings.pop_front();
    }
    // initialize start state
    initializeStates();
}

/** removes spaces in line**/
string MatrixMySearch::edit(string s) {
    size_t prev = 0, pos;
    while ((pos = s.find_first_of(" ", prev)) != std::string::npos) {
        string cut1 = s.substr(prev, pos);
        string cut2 = s.substr(pos + 1, s.length());
        s = cut1 + cut2;
    }
    return s;
}

/** makes an array of int according to the line we received from the client**/
int *MatrixMySearch::editcomma(string line) {
    string c = "";
    int j = 0;
    int *arrayOfNums = new int[this->columns];
    int len = line.length();
    for (int i = 0; i < len; i++) {
        if (line[i] != ',') {
            if (line[i] != '\n')
                c += line[i];
        } else if (line[i] == ',') {
            arrayOfNums[j] = atoi(c.c_str());
            c = "";
            j += 1;
        }
    }
    // entering the last in line
    arrayOfNums[j] = atoi(c.c_str());
    return arrayOfNums;
}

/** creating the initial and goal states according to the information we received from the client**/
void MatrixMySearch::initializeStates() {
    string start1 = edit(this->dequeStrings.front());
    int *startArr = editcomma(start1);
    this->start = (new Point(startArr[0], startArr[1]));
    int costStart = getCostInMatrix(startArr[0], startArr[1]);
    this->startState = new State<Point>(*this->start, costStart, costStart);
    this->dequeStrings.pop_front();
    // initialize end state
    string end = edit(this->dequeStrings.front());
    int *endArr = editcomma(end);
    this->destination = (new Point(endArr[0], endArr[1]));
    int costDest = getCostInMatrix(endArr[0], endArr[1]);
    this->goalState = new State<Point>(*this->destination, costDest, costDest);
}

string MatrixMySearch::noPath() {
    return "";
}



#include <random>

#ifndef PROJECT3PLANNING_RANDOM_H
#define PROJECT3PLANNING_RANDOM_H


/*
   The random class was provided by professor Joshua Fox.
   He provided the classes when assigning the final project for programming 2 (Minesweeper)
   which also dealt with SFML and we decided to use them since our project was also helped by their functionality.
   The random class simply generates a random number within a given range.
*/

class Random {
    static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);


};


#endif //PROJECT3PLANNING_RANDOM_H

#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP
#include <map>
#include <string>
#include <iostream>
#include "Direction.hpp"
using std::string;
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

namespace ariel
{
    class Notebook
    {
        private:
        map<int, map<int, char*>> n;
        

    public:
        void write(int, int , int , ariel::Direction, string );
        string read(int , int , int , ariel::Direction, int );
        void erase(int , int , int , ariel::Direction, int );
        string show(int);
        ~Notebook();
    };
}
#endif //NOTEBOOK_HPP
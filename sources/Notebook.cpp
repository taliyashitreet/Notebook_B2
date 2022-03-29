#include "Notebook.hpp"
using ariel::Direction;
using std::string;
using namespace std;
int const bound = 100;
int const till =600;

namespace ariel
{

    void Notebook::write(int page, int row, int col, Direction d, string text)
    {
        if (page < 0 || row < 0 || col < 0)
        {
            throw invalid_argument("invalid input");
        }
        if (d==Direction::Horizontal && (unsigned int)col + text.length() > bound)
        {
            throw invalid_argument("to long text");
        }
        if( d==Direction::Vertical && (unsigned int)col >=bound){
            throw invalid_argument("to long text");
        }

        for (char c : text)
        {
            if (isprint(c) == 0 || c == '~')
            {
                throw invalid_argument("invalid text");
            }
        }
        if (!this->n.contains(page))
        {
            map<int, char *> put;
            this->n.insert({page, put});
        }
        int tmpRow = row;
        int tmpCol = col;
        for (int i = 0; i < text.length(); i++)
        {
            if (this->n.at(page).contains(tmpRow) &&
                this->n.at(page).at(tmpRow)[(unsigned int)tmpCol] != '_')
            {
                throw invalid_argument("already written here");
            }
            if (d == Direction::Horizontal)
            {
                tmpCol++;
            }
            else
            {
                tmpRow++;
            }
        }

        for (size_t c = 0; c < text.length(); c++)
        {
            if (!this->n.at(page).contains(row))
            {
                char *put = new char[bound+1];
                for (int i = 0; i < bound+1; i++)
                {
                    put[i] = '_';
                }
                put[bound] = '\0';
                this->n.at(page).insert({row, put});
            }

            this->n.at(page).at(row)[(unsigned int)col] = text.at(c);
            if (d == Direction::Horizontal)
            {
                col++;
            }
            else
            {
                row++;
            }
        }
    }

    string Notebook::read(int page, int row, int col, Direction d, int len)
    {
        if (page < 0 || row < 0 || col < 0 || len<0)
        {
            throw invalid_argument("invalid input");
        }
        if (d== Direction::Horizontal &&  col + len > bound)
        {
            throw invalid_argument("to long text");
        }
        if(d==Direction::Vertical && col >=bound){
             throw invalid_argument("to long text");
        }
        if (!this->n.contains(page))
        {
        string st;
        for (int i = 0; i < len; i++)
        {
            st += '_';
        }
        return st;
        }
        string ans;
        for (int i = 0; i < len; i++)
        {
            if (!this->n.at(page).contains(row))
            {
                ans += '_';
            }
            else
            {
                ans += this->n.at(page).at(row)[(unsigned int)col];
            }
            if (d == Direction::Horizontal)
            {
                col++;
            }
            else
            {
                row++;
            }
        }
        return ans;
    }

    void Notebook::erase(int page, int row, int col, Direction d, int len)
    {
        if (page < 0 || row < 0 || col < 0 || len<0)
        {
            throw invalid_argument("invalid input");
        }
        if (d== Direction::Horizontal &&  col + len > bound)
        {
            throw invalid_argument("to long text");
        }
        if(d==Direction::Vertical && col >=bound){
             throw invalid_argument("to long text");
        }
        if (!this->n.contains(page))
        {
            map<int, char *> put;
            this->n.insert({page, put});
        }
        for (int i = 0; i < len; i++)
        {
            if (!this->n.at(page).contains(row))
            {
                char *put = new char[bound+1];
                for (int i = 0; i < bound+1; i++)
                {
                    put[i] = '_';
                }
                put[bound] = '\0';
                this->n.at(page).insert({row, put});
            }
            this->n.at(page).at(row)[(unsigned int)col] = '~';
            if (d == Direction::Horizontal)
            {
                col++;
            }
            else
            {
                row++;
            }
        }
    }
    string Notebook::show(int page)
    {
        if(page < 0) {
            throw invalid_argument("invalid input");
        }
        string ans;    
        for(int i=0; i<till; i++){
             ans+=this->read(page,i,0,Direction::Horizontal,bound-1);
             ans+='\n';
         }
         return ans;
    
    }
    Notebook::~Notebook()
    {
        for (map<int, map<int, char *>>::iterator it = this->n.begin(); it != this->n.end(); ++it)
        {
            map<int, char *> tmpMap = this->n.at(it->first);
            for (map<int, char *>::iterator it2 = tmpMap.begin(); it2 != tmpMap.end(); ++it2)
            {
                delete this->n.at(it->first).at(it2->first);
            }
        }
    }
}
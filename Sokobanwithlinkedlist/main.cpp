

//I implemented the doubly linked list and node classes

#include <bits/stdc++.h>
using namespace std;

// A linked list node
template <class Sokoban>
class Node
{
public:
    Node *prev;
    Node *next;
    Sokoban data;
    Node(Sokoban mdata)
    {
        data = mdata;
    }
};

template <class Sokoban>
class dlist
{
public:
    Node<Sokoban> *head;
    Node<Sokoban> *tail;

    dlist()
    {
        head = tail = nullptr;
    }
    ~dlist()
    {
        destroy();
    }

    void push_back(Sokoban &mydata)
    {
        Node<Sokoban> *node = new Node<Sokoban>(mydata);
        if (head == NULL)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void destroy()
    {
        Node<Sokoban> *walk = head;
        while (walk)
        {
            Node<Sokoban> *node = walk;
            walk = walk->next;
            delete node;
        }
        head = tail = nullptr;
    }
};

template <class Sokoban>
class StackQueue
    {
        private:
            dlist<Sokoban> list;
            int top;
        public:
            StackQueue()
            {
                top = -1;
            } //constructor

            void push(Sokoban &item)
            {


                // increment top ptr and copy item into list

                top++;
                list.push_back(item);


            }

            Sokoban pop()
            {


                Sokoban tempo;



                Node<Sokoban> *tail = list.tail;

                if (tail == list.head)
                {
                    //only one element in the list
                    tempo = tail->data;
                    delete tail;
                    list.head = list.tail = nullptr;
                }
                else
                {
                    Node<Sokoban> *temp = list.tail->prev;
                    tempo = list.tail->data;
                    delete list.tail;
                    list.tail = temp;
                    list.tail->next = nullptr;
                }


                // if stack empty nothing to pop
                if (top==-1)
                    {
                        cout<<"Stack empty"<<endl;
                        exit(1);
                    }

                //decrement top and return the earlier top element
                top--;
                return tempo;


            }


            //return 1 if empty 0 if not
            int StackEmpty(void) const
            {
                if (top == -1)
                    return 1;
                else
                    return 0;

            }
    };

class Sokoban
{
    private:
    int atrow; //stores the movable characters positions
    int atcolumn;

    char state[6][9] ; //stores the map state

    public:

    Sokoban()  //empty constructor
    {

    }

    Sokoban(char mstate[6][9]) //c.tor for char array
    {
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<9; j++)
            {
                state[i][j] = mstate[i][j];
            }
        }

        for(int i=0; i<6; i++)
        {
            for(int j=0; j<9; j++)
            {
                if (state[i][j] == '@') //in the array, @ location found
                {
                    atrow = i;
                    atcolumn = j;
                }
            }
        }
    }

    Sokoban(string p) //c.tor for text file
    {
        char data[6][8];
        char dummy; //newline char read in dummy

        /* input file stream */
        ifstream file;
        file.open(p);

        for(int i=0; i<6; i++)
        {
            for(int j=0; j<8; j++)
            {
                file >> noskipws >> data[i][j];
                state[i][j] = data[i][j];
            }
        file >> noskipws >> dummy;
        state[i][8] = dummy; //at the end of the row new line char added
        }
        file.close();


        for(int i=0; i<6; i++)
        {
            for(int j=0; j<9; j++)
            {
                if (state[i][j] == '@')
                {
                    atrow = i;   //in the uploaded file, @ location found
                    atcolumn = j;
                }
            }
        }

    }

    Sokoban(Sokoban &s)   //copy constructor operator
    {
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<9; j++)
            {
                state[i][j] = s.state[i][j];
            }
        }
    }

/*
   Sokoban& operator = (const Sokoban &s)  //copy assignment operator
    {
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<9; j++)
            {
                state[i][j] = s.state[i][j];
            }
        }
        return *this;
    }

*/
    //the following boolean operations are written according to official rules

    //Some examples of the rules are:
    //Character(+ or @) cannot move to respective way when there is a wall or 2 boxes one after another
    //or when there is a box right next to a wall
    //otherwise the character is free to move and push the boxes

    bool move_up()
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<8; j++)
            {
                if ( ( state[i][j] == '#' && (state[i+1][j] == '@' || state[i+1][j] == '+') )
                || ( state[i][j] == '#' && (state[i+1][j] == '$' || state[i+1][j] == '*') && (state[i+2][j] == '@' || state[i+2][j] == '+') )
                || ( (state[i][j] == '$' || state[i][j] == '*') && (state[i+1][j] == '$' || state[i+1][j] == '*') && (state[i+2][j] == '@' || state[i+2][j] == '+') ) )
                    return 0;
            }
        }
        return 1;
    }

    bool move_down()
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<8; j++)
            {
                if ( ( state[i+1][j] == '#' && (state[i][j] == '@' || state[i][j] == '+') )
                || ( state[i+2][j] == '#' && (state[i+1][j] == '$' || state[i+1][j] == '*') && (state[i][j] == '@' || state[i][j] == '+') )
                || ( (state[i+2][j] == '$' || state[i+2][j] == '*') && (state[i+1][j] == '$' || state[i+1][j] == '*') && (state[i][j] == '@' || state[i][j] == '+') ) )
                    return 0;
            }
        }
        return 1;
    }

    bool move_left()
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<8; j++)
            {
                if ( ( state[i][j-1] == '#' && (state[i][j] == '@' || state[i][j] == '+') )
                || ( state[i][j-2] == '#' && (state[i][j-1] == '$' || state[i][j-1] == '*') && (state[i][j] == '@' || state[i][j] == '+') )
                || ( (state[i][j-2] == '$' || state[i][j-2] == '*') && (state[i][j-1] == '$' || state[i][j-1] == '*') && (state[i][j] == '@' || state[i][j] == '+') ) )
                    return 0;
            }
        }
        return 1;
    }

    bool move_right()
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<8; j++)
            {
                if ( ( state[i][j+1] == '#' && (state[i][j] == '@' || state[i][j] == '+') )
                || ( state[i][j+2] == '#' && (state[i][j+1] == '$' || state[i][j+1] == '*') && (state[i][j] == '@' || state[i][j] == '+') )
                || ( (state[i][j+2] == '$' || state[i][j+2] == '*') && (state[i][j+1] == '$' || state[i][j+1] == '*') && (state[i][j] == '@' || state[i][j] == '+') ) )
                    return 0;
            }
        }
        return 1;
    }

    bool is_solved()  //the puzzle is solved when all the boxes are placed
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<9; j++)
            {
                if (state[i][j] == '$')
                    return 0;
            }
        }
        return 1;
    }

    void print_puzzle() //prints the current state of the map
    {
        for (int i=0; i<6; i++)
        {
            for (int j=0; j<9; j++)
            {
                cout << state[i][j];
            }
        }
    }

    void changestate(const int &row,const int &column,const char &moved)
    {
        state[row][column] = moved; //changes the maps corresponding parts after a movement
    }

 //movements
 //my custom function changestate is used in this part
 //the characters moving position in the map and standing position is changed accordingly

    void up()
    {
        if( state[atrow-1][atcolumn] == ' ' ) //up part is empty
                changestate((atrow-1), atcolumn, '@');

            if( state[atrow-1][atcolumn] == '.' ) //up part is an empty box location
                changestate((atrow-1), atcolumn, '+');

            if( ( ( state[atrow-1][atcolumn] == '$' ) ) && state[atrow-2][atcolumn] == '.' ) //there is a box and a box placement place one after another
            {
                changestate((atrow-1), atcolumn, '@');
                changestate((atrow-2), atcolumn, '*');
            }

            if( ( state[atrow-1][atcolumn] == '*' ) && (state[atrow-2][atcolumn] == ' ' )) //there is a placed box and an empty location one after another
            {
                changestate((atrow-1), atcolumn, '+');
                changestate((atrow-2), atcolumn, '$');
            }

            if( ( state[atrow-1][atcolumn] == '$' ) && (state[atrow-2][atcolumn] == ' ' )) //there is a box and an empty location one after another
            {
                changestate((atrow-1), atcolumn, '@');
                changestate((atrow-2), atcolumn, '$');
            }

            if( state[atrow-1][atcolumn] == '$' && state[atrow-2][atcolumn] == '.' ) //there is a box and a box placement place one after another
            {
                changestate((atrow-1), atcolumn, '@');
                changestate((atrow-2), atcolumn, '*');
            }

            if ( state[atrow][atcolumn] == '@' ) //if it was previously empty
                changestate(atrow, atcolumn, ' ');

            if ( state[atrow][atcolumn] == '+' ) //if it was previously .
                changestate(atrow, atcolumn, '.');


            atrow--; //character moved up

    }

//the similar algorithm to up() is applied in other movements
    void left()
    {
        if( state[atrow][atcolumn-1] == ' ' )
                changestate(atrow, (atcolumn-1), '@');

            if( state[atrow][atcolumn-1] == '.' )
                changestate(atrow, (atcolumn-1), '+');

            if( ( state[atrow][atcolumn-1] == '*' ) && (state[atrow][atcolumn-2] == ' ' ))
            {
                changestate((atrow), (atcolumn-1), '+');
                changestate((atrow), (atcolumn-2), '$');
            }

            if( ( state[atrow][atcolumn-1] == '$' ) && (state[atrow][atcolumn-2] == ' ' ))
            {
                changestate((atrow), (atcolumn-1), '@');
                changestate((atrow), (atcolumn-2), '$');
            }

            if( state[atrow][atcolumn-1] == '$' && state[atrow][atcolumn-2] == '.' )
            {
                changestate((atrow), (atcolumn-1), '@');
                changestate(atrow, (atcolumn-2), '*');
            }

            if ( state[atrow][atcolumn] == '@' ) //if it was previously empty
                changestate(atrow, atcolumn, ' ');

            if ( state[atrow][atcolumn] == '+' ) //if it was previously .
                changestate(atrow, atcolumn, '.');


            atcolumn--;
    }

    void right()
    {
        if( state[atrow][atcolumn+1] == ' ' )
                changestate(atrow, (atcolumn+1), '@');

            if( state[atrow][atcolumn+1] == '.' )
                changestate(atrow, (atcolumn+1), '+');

            if( ( ( state[atrow][atcolumn+1] == '$' ) ) && state[atrow][atcolumn+2] == '.' )
            {
                changestate((atrow), (atcolumn+1), '@');
                changestate((atrow), (atcolumn+2), '*');
            }

            if( ( state[atrow][atcolumn+1] == '*' ) && (state[atrow][atcolumn+2] == ' ' ))
            {
                changestate((atrow), (atcolumn+1), '+');
                changestate((atrow), (atcolumn+2), '$');
            }

            if( ( state[atrow][atcolumn+1] == '$' ) && (state[atrow][atcolumn+2] == ' ' ))
            {
                changestate((atrow), (atcolumn+1), '@');
                changestate((atrow), (atcolumn+2), '$');
            }

            if( state[atrow][atcolumn+1] == '$' && state[atrow][atcolumn+2] == '.' )
            {
                changestate((atrow), (atcolumn+1), '@');
                changestate(atrow, (atcolumn+2), '*');
            }

            if ( state[atrow][atcolumn] == '@' ) //if it was previously empty
                changestate(atrow, atcolumn, ' ');

            if ( state[atrow][atcolumn] == '+' ) //if it was previously .
                changestate(atrow, atcolumn, '.');


            atcolumn++;
    }

    void down()
    {
        if( state[atrow+1][atcolumn] == ' ' )
                changestate((atrow+1), atcolumn, '@');

            if( state[atrow+1][atcolumn] == '.' )
                changestate((atrow+1), atcolumn, '+');

            if( ( ( state[atrow+1][atcolumn] == '$' ) ) && state[atrow+2][atcolumn] == '.' )
            {
                changestate((atrow+1), atcolumn, '@');
                changestate((atrow+2), atcolumn, '*');
            }

            if( ( state[atrow+1][atcolumn] == '*' ) && (state[atrow+2][atcolumn] == ' ' ))
            {
                changestate((atrow+1), atcolumn, '+');
                changestate((atrow+2), atcolumn, '$');
            }

            if( ( state[atrow+1][atcolumn] == '$' ) && (state[atrow+2][atcolumn] == ' ' ))
            {
                changestate((atrow+1), atcolumn, '@');
                changestate((atrow+2), atcolumn, '$');
            }
            if( state[atrow+1][atcolumn] == '$' && state[atrow+2][atcolumn] == '.' )
            {
                changestate((atrow+1), atcolumn, '@');
                changestate((atrow+2), atcolumn, '*');
            }

            if ( state[atrow][atcolumn] == '@' ) //if it was previously empty
                changestate(atrow, atcolumn, ' ');

            if ( state[atrow][atcolumn] == '+' ) //if it was previously .
                changestate(atrow, atcolumn, '.');



            atrow++;
    }
};


int main()
{
    //prints the welcome message as raw string literal
    cout << R"(
  _      __ ____ __   _____ ____   __  ___ ____
 | | /| / // __// /  / ___// __ \ /  |/  // __/
 | |/ |/ // _/ / /__/ /__ / /_/ // /|_/ // _/
 |__/|__//___//____/\___/ \____//_/  /_//___/
              ______ ____
             /_  __// __ \
              / /  / /_/ /
             /_/   \____/
   ____ ____   __ __ ____   ___   ___    _  __
  / __// __ \ / //_// __ \ / _ ) / _ |  / |/ /
 _\ \ / /_/ // ,<  / /_/ // _  |/ __ | /    /
/___/ \____//_/|_| \____//____//_/ |_|/_/|_/

    )" << endl << endl;
    string path ("sample_puzzle.txt");
    Sokoban mygame(path);


    StackQueue<Sokoban> mystack;

    mygame.print_puzzle();
    cout << endl << endl;
    mystack.push(mygame); //initial game pushed to stack
    char key;
    char temp;
    int twoz;

    while( mygame.is_solved() == 0 ) //game starts
    {
        cout << "Key:" << endl;

        cin  >> key;

        cout << endl;

        if (key == 'z')
        {
            if ( temp == 'z' )
                twoz = 1; //detects repeated z press
            else          //this is necessary because the first z press pops the current state
                twoz = 0; // so it does not undo the last action
        }// will be used in popping part

//movements
        if ( (key == 'w') && (mygame.move_up()) )
        {
            mygame.up();
            mygame.print_puzzle();
            mystack.push(mygame);
        }

        if ( (key == 'a') && (mygame.move_left()) )
        {
            mygame.left();
            mygame.print_puzzle();
            mystack.push(mygame);
        }

        if ( (key == 'd') && (mygame.move_right()) )
        {
            mygame.right();
            mygame.print_puzzle();
            mystack.push(mygame);
        }

        if ( (key == 's') && (mygame.move_down()) )
        {
            mygame.down();
            mygame.print_puzzle();
            mystack.push(mygame);
        }
//undo the last action 1 times popping is enough when repeatedly undoing
        if ( key == 'z' && twoz == 1 )
        {
            mygame = mystack.pop();
            mygame.print_puzzle();
        }
//for the first z press after an action, 2 times popping is necessary to undo
        if ( (key == 'z') && (twoz != 1) )
        {
            mygame = mystack.pop();
            mygame = mystack.pop();
            mygame.print_puzzle();
        }
//resets the map to the initial state while printing all the previous states and terminates program
        if ( key == 'r' )
        {
            while ( ! (mystack.StackEmpty() ) )
            {
                mygame = mystack.pop();
                mygame.print_puzzle();
            }
            exit(1); //program terminated after r
        }


    temp = key; //stores the last key press, used in detecting repeated z press
    }

    cout << "YOU WIN!!!" << endl; //when the game is won, print this message

}


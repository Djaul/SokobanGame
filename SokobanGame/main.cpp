
//This homework took approximately 12 hours


#include <iostream>
#include <fstream>
#include <cstring> //useful for initialization with char array

using namespace std;

template <class Sokoban>
class StackQueue
    {
        private:
            Sokoban stacklist[100];
            int top;
        public:
            StackQueue()
            {
                top = -1;
            } //constructor

            void push(Sokoban &item)
            {
                //can not push if stack has exceeded its limits
                if (top == 99)
                    {
                        cerr<<"Stack overflow"<<endl;
                        exit(1);
                    }
                // increment top ptr and copy item into list

                top++;
                stacklist[top] =item; //pushed
            }

            Sokoban pop()
            {
                Sokoban temp;
                // if stack empty nothing to pop
                if (top==-1)
                    {
                        cout<<"Stack empty"<<endl;
                        exit(1);
                    }
                //record the top element and remove from stack
                temp=stacklist[top] ;
                //decrement top and return the earlier top element
                top--;
                return temp;
            }

            //returns the earliest pushed element which is the first array element
            Sokoban pop_rear()
            {
                Sokoban temp;
                for(int i=1; i<=top; i++)
                {
                    if(i==1)
                    {
                        temp = stacklist[0];
                    }
                    stacklist[i-1] = stacklist[i];
                }
                top--;
                return temp;
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
   Sokoban& operator = (const Sokoban &s)  //copy assignment operator works fine but after repeated undo operations the program bugs sometimes
    {                                       //hence, I decided to implement the game with the default copy assignment operator you can uncomment to see the bug
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



    //Uncomment for initialization with char array and comment the above object, feel free to load up another 6x8 map
/*
    char game_array[6][9];

    strcpy(game_array[0], "######  \n");
    strcpy(game_array[1], "#.  .###\n");
    strcpy(game_array[2], "#@$#$  #\n");
    strcpy(game_array[3], "#$. .$ #\n");
    strcpy(game_array[4], "#    $.#\n");
    strcpy(game_array[5], "########\n");


    Sokoban mygame(game_array);

*/



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

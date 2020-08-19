// Program to build a simple calculator using switch Statement
#include <iostream>
// Include the string library
#include <string>
using namespace std;

#define SEARCH 0
#define HEAD 1
#define PICK_UP 2
#define HOME 3
#define DROP 4
#define AVOID 5
#define FUN 6

int state = 0;
int prev_state = state;
char sonar;
char can;
char bin;
char close;
char tape;
char fun;

int main()
{
    while (true)
    {
        prev_state = state;

        // cout << "Tape? (Y/N)";
        // cin >> tape;
        // if (tape == 'Y')
        // {
        //     state = AVOID;
        // }

        // cout << "Fun? (Y/N)";
        // cin >> fun;
        // if (fun == 'Y')
        // {
        //     state = SEARCH;
        // }

        switch (state)
        {
        case HEAD:
            cout << "Going to can.... \n";
            cout << "Still seeing can? (Y/N)";
            cin >> can;
            if (can == 'N')
            {
                state = SEARCH;
                break;
            } else {
                cout << "Close to can? (Y/N)";
                cin >> close;
                if (close == 'Y')
                {
                    state = PICK_UP;
                    break;
                }
                else
                {
                    break;
                }
            }
        case PICK_UP:
            cout << "Closing claw....\n";
            cout << "Lifting arm....\n";
            cout << "Still holding can? (Y/N)";
            cin >> can;
            if (can == 'N')
            {
                state = SEARCH;
                break;
            }
            else
            {
                cout << "Rotating....\n";
                cout << "IR Found!\n";
                state = HOME;
                break;
            }
        case HOME:
            cout << "Moving towards IR....\n";
            cout << "Still holding can? (Y/N)";
            cin >> can;
            if (can == 'N')
            {
                state = SEARCH;
                break;
            }

            cout << "Close to bin? (Y/N)";
            cin >> bin;
            if (bin == 'Y')
            {
                state = DROP;
                break;
            }
            else
            {
                break;
            }
        case DROP:
            cout << "Dropping arm....\n";
            cout << "Opening claw....\n";
            cout << "Returning to search...\n";
            state = SEARCH;
            break;
        // case AVOID:
        //     cout << "Avoiding bounds...";
        //     state = prev_state;
        //     break;
        // case FUN:
        //     cout << "FUUUUN....";
        //     break;
        default:
            // operator is doesn't match any case constant (+, -, *, /)
            cout << "Searching for can....\n";
            cout << "Find can? (Y/N)";
            cin >> sonar;
            if (sonar == 'Y')
            {
                state = HEAD;
                break;
            }
            else
            {
                break;
            }
        }
    }

    return 0;
}
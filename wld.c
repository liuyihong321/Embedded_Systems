//Win, Lose or Draw logic module
// Made by: James Shields (jds96 - 94504086) and Yihong Liu (yli227 - 49118489)
//Date: 12/10/16

#include "wld.h"

//This function accepts two characters, either an A B or C. These characters are encoded for the values of paper, scissors or rock respectively.
//The characters are compared to each other using logic within the functions, and a character w d or l is returned indicating a win, draw or loss respectively.
//Some error checking ability is encoded into this function, whereby the char D is returned to indicated that logic did not receive an A B or C value.
//This occasionally can happen due to errors in the IR transmission.
char winlosedraw(char player1choice, char player2choice)
{
    char state;

    if (player1choice == 'A') {
        switch (player2choice) {
        case 'A':
            state = 'd';
            break;

        case 'B':
            state = 'l';
            break;

        case 'C':
            state = 'w';
            break;

        default:
            state = 'D';
            break;

        }
    }

    else if (player1choice == 'B') {
        switch (player2choice) {
        case 'A':
            state = 'w';
            break;

        case 'B':
            state = 'd';
            break;

        case 'C':
            state = 'l';
            break;

        default:
            state = 'D';
            break;

        }
    }

    else if (player1choice == 'C') {
        switch (player2choice) {
        case 'A':
            state = 'l';
            break;

        case 'B':
            state = 'w';
            break;

        case 'C':
            state = 'd';
            break;

        default:
            state = 'D';
            break;

        }
    } else {
        state = 'D';
    }
    return state;
}

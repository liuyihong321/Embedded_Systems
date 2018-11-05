ENCE260 Assignment 2 - Embedded Systems
GAME: PAPER, SCISSORS, ROCK
Made by: James Shields (jds96 - 94504086) and Yihong Liu (yli227 - 49118489)
Date: 12/10/16

This README file outlines how to play our game, Paper, Scissors, Rock (PSR).

Quick Start:

To run the game, plug both UCFK4s into USB ports on the computer. Open a terminal window and navigate to the root folder (final). Run the command MAKE PROGRAM twice.



Instructions:

The basic principle of PSR is that there are two players who both choose either paper, scissors, or rock. Paper will beat rock, rock beats scissors, and scissors beats paper,
giving rise to a triangular system of winning. In this game, each player is presented with an initial screen, where they are able to use the joystick in a up or down fashion
to pick their PSR choice. Once a choice is made, the joystick is clicked in a downwards fashion, whereby the two chosen values are compared for each player.

If the player is the winner, the words "WIN" will scroll across the display, likewise for a draw or lose, the words "DRAW" or "LOSE" scroll across. To re-enforce whether the player has won or
lost, a short set of high beeps is emitted if the player has won, or a set of lower and longer notes are emitted over the speaker for a loss. At this point, both players can click the joystick
button to show their respective scores on the display.

The game is able to be repeated to the heart's content of the players.



Important points:

Make sure the UCFK4 modules are aligned so that the transmitter and receiver components on the board are facing each other. If there is an error with sending information, the value
FUNC will be returned if the IR transmission is compromised.

Be careful not to bump the speaker in the header ports. If the speaker falls out, it should be placed back into the end of the header port closest to the LED screen.

Most of all, enjoy this short game!

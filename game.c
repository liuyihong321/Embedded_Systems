//ENCE260 Assignment 2 - Embedded Systems
//GAME: PAPER, SCISSORS, ROCK
// Made by: James Shields (jds96 - 94504086) and Yihong Liu (yli227 - 49118489)
//Date: 12/10/16

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "beep1.h"
#include "draw.h"
#include "wld.h"



#define MESSAGE_RATE 20         // Text scroll speed
#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)



int main(void)
{
    int PACER_RATE = 500;
    /* Initialize everything */
    system_init();
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    navswitch_init();
    ir_uart_init();
    pacer_init(PACER_RATE);
    /* Initialize char */
    char character = 'A';
    char player1 = '0';
    char player2 = '0';
    char score = '0';
    char sound_check = 'z';
    /* Initialize int */
    int result_check = 0;
    int initialize_check = 0;
    int select = 0;
    int win_lose = 0;
    int sent = 0;
    int received = 0;
    int sound_time = 0;
    int newgame_wait = 0;
    int endsent = 0;
    int endreceived = 0;
    int gap_time = 0;
    int second_sound = 0;
    int wait_time = 0;

    //Displays a single character on the screen
    void display_score(char score) {
        char buffer[2];
        buffer[0] = score;
        buffer[1] = '\0';
        tinygl_text(buffer);
    }
    //main game loop
    while (1) {
        // choose the scissors, paper or rock
        while (select == 0) {

            pacer_wait();
            tinygl_update();
            navswitch_update();

            if (initialize_check == 0) {
                win_lose = 0;
                sent = 0;
                received = 0;
                endsent = 0;
                endreceived = 0;
                result_check = 0;
                sound_time = 0;
                newgame_wait = 0;
                gap_time = 0;
                second_sound = 0;
                initialize_check = 1;
                tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
            }
            if (sound_time < 30)         // start sound
            {
                noise_maker();
                sound_time++;
            }

            if (navswitch_push_event_p(NAVSWITCH_NORTH))         // switch north
            {
                character++;
            }
            if (navswitch_push_event_p(NAVSWITCH_SOUTH))         // switch south
            {
                character--;
            }
            if (character == 'D') {
                character = 'A';
            }
            if (character == '@') {
                character = 'C';
            }
            //draw picture
            switch (character) {
            //case paper
            case 'A':
                tinygl_clear();
                paper_draw();
                break;
            //case scissors
            case 'B':
                tinygl_clear();
                scissors_draw();
                break;
            //case rock
            case 'C':
                tinygl_clear();
                rock_draw();
                break;
            }
            //send your choose
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
                player1 = character;
                tinygl_clear();
                sent = 1;
            }
            //get choice from other FK
            if (ir_uart_read_ready_p()) {
                player2 = ir_uart_getc();
                tinygl_clear();
                received = 1;
            }
            //check both select or not
            if ((sent == 1) && (received == 1)) {
                select = 1;
            }
        }
        //check win or lose
        while (win_lose == 0) {
            tinygl_update();
            pacer_wait();
            navswitch_update();

            if (result_check == 0) {
                //WIN!
                if (winlosedraw(player1, player2) == 'w') {
                    tinygl_text("WIN");
                    sound_check = 'x';
                    score++;
                }
                //DRAW!
                else if (winlosedraw(player1, player2) == 'd') {
                    tinygl_text("DRAW");
                }
                //LOSE!
                else if (winlosedraw(player1, player2) == 'l') {
                    tinygl_text("LOSE");
                    sound_check = 'y';
                }
                //wrong letter tranmit
                else if (winlosedraw(player1, player2) == 'D') {
                    tinygl_text("FUNC");
                }
                //transmit fail
                else {
                    tinygl_text("FAIL");
                }
                result_check = 1;
            }
            //win or lose sound
            if (sound_check == 'y') {          //checks whether player was won or lost, and changes the length (wait_time) and tone (sound_check) of the beep with variable y.
                wait_time = 300;
            }
            else {
                wait_time = 50;
            }
            if (sound_time < wait_time)          // make first beep
            {
                noise_maker();
                if (sound_check == 'y') {
                    pacer_wait();
                }
                sound_time++;
            }
            if (sound_time == wait_time && gap_time < wait_time)        // waiting time
            {
                if (sound_check == 'y') {
                    pacer_wait();
                }
                gap_time++;
            }
            if (gap_time == wait_time && second_sound < wait_time)        // make second beep
            {
                noise_maker();
                if (sound_check == 'y') {
                    pacer_wait();
                }
                second_sound++;
            }
            // end send
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc('n');
                endsent = 1;
            }
            // end received
            if (ir_uart_read_ready_p()) {
                ir_uart_getc();
                endreceived = 1;
            }
            // restart the game
            if ((endsent == 1) && (endreceived == 1)) {
                win_lose = 1;
                select = 0;
                sound_time = 0;
                result_check = 0;
                initialize_check = 0;
                sent = 0;
                received = 0;
            }
        }
        //if score over 9, set back to 0
        if (score == ':') {
            score = '0';
        }

        tinygl_clear();
        tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
        display_score(score);        // display score
        //waiting time to display score and start the next game
        for (newgame_wait = 0; newgame_wait < 1600; newgame_wait++) {
            tinygl_update();
            pacer_wait();
        }
    }
    return 0;
}

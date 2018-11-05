//Draw module
// Made by: James Shields (jds96 - 94504086) and Yihong Liu (yli227 - 49118489)
//Date: 12/10/16

//This function has a bitmap representation of a paper, scissors, or rock symbol using functions such as box, line, and point from the TINYGL graphics library.
#include "tinygl.h"
#include "system.h"
#include "draw.h"

//Draw a scissors icon using TINYGL.
void scissors_draw(void)
{
    static tinygl_point_t pos1;
    static tinygl_point_t pos2;
    static tinygl_point_t tl;
    static tinygl_point_t br;
    tl.y = 4;
    tl.x = 0;
    br.y = 5;
    br.x = 1;
    tinygl_draw_box(tl, br, 1);
    tl.y = 4;
    tl.x = 3;
    br.y = 5;
    br.x = 4;
    tinygl_draw_box(tl, br, 1);
    pos1.y = 3;
    pos1.x = 2;
    pos2.y = 1;
    pos2.x = 0;
    tinygl_draw_line(pos1, pos2, 1);
    pos1.y = 3;
    pos1.x = 2;
    pos2.y = 1;
    pos2.x = 4;
    tinygl_draw_line(pos1, pos2, 1);
}

//Draw a rock icon using TINYGL.
void rock_draw(void)
{
    static tinygl_point_t tl;
    static tinygl_point_t br;
    static tinygl_point_t pop;
    tl.y = 2;
    tl.x = 0;
    br.y = 4;
    br.x = 4;
    tinygl_draw_box(tl, br, 1);
    tl.y = 1;
    tl.x = 1;
    br.y = 5;
    br.x = 3;
    tinygl_draw_box(tl, br, 1);
    pop.y = 3;
    pop.x = 2;
    tinygl_draw_point(pop, 1);
}

//Draw a paper icon using TINYGL.
void paper_draw(void)
{
    static tinygl_point_t tl;
    static tinygl_point_t br;
    tl.y = 1;
    tl.x = 0;
    br.y = 5;
    br.x = 4;
    tinygl_draw_box(tl, br, 1);
}

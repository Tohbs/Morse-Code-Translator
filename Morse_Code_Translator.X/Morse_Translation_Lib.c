#include "xc.h"
#include "string.h"

#define dot 'S'
#define dash 'L'
#define none '0'

volatile char order[38] = {'A', 'B', 'C', 'D', 'E', 'F',
                            'G', 'H', 'I', 'J', 'K', 'L',
                            'M', 'N', 'O', 'P', 'Q', 'R',
                            'S', 'T', 'U', 'V', 'W', 'X',
                            'Y', 'Z', '1', '2', '3', '4',
                            '5', '6', '7', '8', '9', '0','|',';'};

volatile char codes[38][6] = {{dot, dash, none, none, none, none}, {dash, dot, dot, dot, none, none}, {dash, dot, dash, dot, none, none},
                             {dash, dot, dot, none, none, none}, {dot, none, none, none, none, none}, {dot, dot, dash, dot, none, none},
                             {dash, dash, dot, none, none, none}, {dot, dot, dot, dot, none, none}, {dot, dot, none, none, none, none},
                             {dot, dash, dash, dash, none, none}, {dash, dot, dash, none, none, none}, {dot, dash, dot , dot, none, none},
                             {dash, dash, none, none, none, none}, {dash, dot, none, none, none, none}, {dash, dash, dash, none, none, none},
                             {dot, dash, dash, dot, none, none}, {dash, dash, dot, dash, none, none}, {dot, dash, dot, none, none, none},
                             {dot, dot, dot, none, none, none}, {dash, none, none, none, none, none}, {dot, dot, dash, none, none, none},
                             {dot, dot, dot, dash, none, none}, {dot, dash, dash, none, none, none}, {dash, dot, dot, dash, none, none},
                             {dash, dot, dash, dash, none, none}, {dash, dash, dot, dot, none, none}, //done with letters
                             {dot, dash, dash, dash, dash, none}, {dot, dot, dash, dash, dash, none}, {dot, dot, dot, dash, dash, none},
                             {dot, dot, dot, dot, dash, none}, {dot, dot, dot, dot, dot, none}, {dash, dot, dot, dot, dot, none}, {dash, dash, dot, dot, dot, none},
                             {dash, dash, dash, dot, dot, none}, {dash, dash, dash, dash, dot, none}, {dash, dash, dash, dash, dash, none},{dash,dot,dash,dot,dash,none},{dot,dot,dot,dash,dot,dash} };

//Morse is a 5 length array full of chars

char translateMorseCode(char morse[6])
{
    int key;
    int index;
    for(key = 0; key < 38; key++)
    {
        for(index = 0; index<6; index++)
        {
            if(codes[key][index] != morse[index])
            {
                break;
            }
            if(index == 5)
            {
                return order[key];
            }
        }
    }
    return '#';
}
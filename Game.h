//
//  Game.h
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#ifndef __Connect6__Game__
#define __Connect6__Game__

#include <stdio.h>
#include "Tuple.h"
#include "Network.h"
#include <iostream>
#include <string>

const std::string RESET("\033[0m");
const std::string BOLDBLACK("\033[1m\033[30m");
const std::string BOLDWHITE("\033[1m\033[37m");

class Game {

private:
    void init_board();
    void print_input(int input[19][19]);
    int construct_input_array(int (&input)[19][19]);
    void print_board();
    bool game_tied();
    char game_won();
    void turn(char player, int amound);
    Tuple find_r_and_c(int input[19][19], int place);
    bool set(Tuple, char);
    bool board_full();
    bool set_first(char);
    bool game_won_from_stone(Tuple, char);
    
    char board[19][19] = {};
    int total_moves = 0;
public:
    Game();
    int play();
    int play(Network, Network);

};

#endif
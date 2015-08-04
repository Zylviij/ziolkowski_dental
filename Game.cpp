//
//  Game.cpp
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#include "Game.h"

// OPTIMIZE

Game::Game() {
    init_board();
}

void Game::init_board() {
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            board[r][c] = ' ';
        }
    }
    total_moves = 0;
}

bool Game::game_won_from_stone(Tuple loc, char type) {
    int row = loc.getRow();
    int col = loc.getCol();
    int row2 = row;
    int col2 = col;
    int total = 0;
    // | //
    for (int r(0); r < 19; r++) {
        if (board[r][col] == type) total++;
        else total = 0;
        if (total >= 5) {
            //std::cout << "Win cond |" << std::endl;
            return true;
        }
    }
    total = 0;
    // - //
    for (int c(0); c < 19; c++) {
        if (board[row][c] == type) total++;
        else total = 0;
        if (total >= 5) {
            //std::cout << "Win cond -" << std::endl;
            return true;
        }
    }
    total = 0;
    // \ //
    if (row > col) {
        row -= col;
        col = 0;
        while (row < 19) {
            if (board[row][col] == type) total++;
            else total = 0;
            if (total == 5) {
                //std::cout << "Win cond \\ 1" << std::endl;
                return true;
            }
            row++;
            col++;
        }
        total = 0;
    } else if (col > row) {
        col -= row;
        row = 0;
        while (col < 19) {
            if (board[row][col] == type) total++;
            else total = 0;
            if (total == 5) {
                //std::cout << "Win cond \\ 2" << std::endl;
                return true;
            }
            row++;
            col++;
        }
        total = 0;
    } else {
        row = 0;
        col = 0;
        while (row < 19) {
            if (board[row][col] == type) total++;
            else total = 0;
            if (total == 5) {
                //std::cout << "Win cond \\ 3" << std::endl;
                return true;
            }
            row++;
            col++;
        }
        total = 0;
    }
    // / //
    if (18 - col2 > row2) {
        col2 += row2;
        row2 = 0;
        while (18 - col2 < 19) {
            if (board[row2][col2] == type) total++;
            else total = 0;
            if (total == 5)  {
                //std::cout << "Win cond / 1" << std::endl;
                return true;
            }
            row2++;
            col2--;
        }
        total = 0;
    } else if (row2 > 18 - col2) {
        row2 -= 18 - col2;
        col2 = 18;
        while (row2 < 19) {
            if (board[row2][col2] == type) total++;
            else total = 0;
            if (total == 5) {
                //std::cout << "MUCH WOW / 2" << std::endl;
                return true;
            }
            row2++;
            col2--;
        }
        total = 0;
    } else {
        row2 = 0;
        col2 = 18;
        while (row2 < 19) {
            if (board[row2][col2] == type) total++;
            else total = 0;
            if (total == 5) {
                //std::cout << "MUCH WOW / 3" << std::endl;
                return true;
            }
            row2++;
            col2--;
        }
    }
    return false;
}

bool Game::set(Tuple rc, char stone) {
    total_moves++;
    if (board[rc.getRow()][rc.getCol()] != ' ') {
        return set_first(stone);
    } else {
        //std::cout << stone << " played: (" << rc.getRow() << ", " << rc.getCol() << ")" << std::endl;
        board[rc.getRow()][rc.getCol()] = stone;
        return game_won_from_stone(rc, stone);
    }
}

bool Game::set_first(char stone) {
    for (int r(0); r < 19; r++) {
        for (int c(0); c < 19; c++) {
            if (board[r][c] == ' ') {
                //std::cout << stone << " played: (" << r << ", " << c << ") (first)" << std::endl;
                board[r][c] = stone;
                return game_won_from_stone(Tuple(r, c), stone);
            }
        }
    }
    return false;
}

bool Game::board_full() {
    return total_moves >= 361;
}

int Game::play(Network x, Network o) {
    // reset
    init_board();
    
    // play
    while (true) {
        // debug
        //std::cout << "X:" << std::endl;
        if (set(x.calculate(board), 'X')) {
            //std::cout << "Xs Won!" << std::endl;
            //print_board();
            return -1;
        }
        //std::cout << "O:" << std::endl;
        //print_board();
        if (set(o.calculate(board), 'O')) {
            //std::cout << "Os Won!" << std::endl;
            //print_board();
            return 1;
        }
        //print_board();
        if (board_full()) {
            //print_board();
            return 0;
        }
    }
}

// SLOW IS OKAY

void Game::print_board() {
    std::cout << "+-----";
    for (int a = 0; a < 19; a++) {
        std::cout << "+---";
    }
    std::cout << "--+" << std::endl;
    std::cout << "|     ";
    for (int a = 0; a < 19; a++) {
        std::cout << "|   ";
    }
    std::cout << "  |" << std::endl;
    std::cout << "|     ";
    for (int a = 0; a < 19; a++) {
        std::cout << "|   ";
    }
    std::cout << "  |" << std::endl;
    for (int r = 0; r < 19; r++) {
        std::cout << "+----";
        for (int c = 0; c < 19; c++) {
            if (board[r][c] == ' ') {
                std::cout << "----";
            } else {
                if (board[r][c] == 'X') {
                    std::cout << "-" << BOLDBLACK << board[r][c] << RESET << "--";
                } else {
                    std::cout << "-" << BOLDWHITE << board[r][c] << RESET << "--";
                }
            }
        }
        std::cout << "---+" << std::endl;
        std::cout << "|     ";
        for (int a = 0; a < 19; a++) {
            std::cout << "|   ";
        }
        std::cout << "  |" << std::endl;
    }
    std::cout << "|     ";
    for (int a = 0; a < 19; a++) {
        std::cout << "|   ";
    }
    std::cout << "  |" << std::endl;
    std::cout << "+-----";
    for (int a = 0; a < 19; a++) {
        std::cout << "+---";
    }
    std::cout << "--+" << std::endl;
}

int Game::construct_input_array(int (&input)[19][19]) {
    int count = 1;
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            input[r][c] = (board[r][c] == 'X') ? -2 : board[r][c] == 'O' ? -1 : count++;
        }
    }
    return count - 1;
}

void Game::print_input(int input[19][19]) {
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            std::cout << input[r][c] << "\t";
        }
        std::cout << std::endl;
    }
}

Tuple Game::find_r_and_c(int input[19][19], int place) {
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            if (place == input[r][c]) {
                return Tuple(r, c);
            }
        }
    }
    return Tuple(-1,-1);
}

void Game::turn(char player, int amount) {
    int amount_start = amount;
    std::cout << (player == 'X' ? BOLDBLACK + "X" + RESET : BOLDWHITE + "O" + RESET) << "'s turn:" << std::endl;
    while (amount == amount_start) {
        print_board();
        std::cout << "You have " << amount << " remaining stones to place." << std::endl;
        std::cout << "Where do you want to place the stone? ";
        int place;
        std::cin >> place;
        int input[19][19];
        int max = construct_input_array(input);
        if (place <= max) {
            Tuple rc = find_r_and_c(input, place);
            board[rc.getRow()][rc.getCol()] = player;
            amount--;
        } else {
            std::cout << "Please select a valid move!" << std::endl;
        }
    }
}

int Game::play() {
    init_board();
    char next = 'O';
    turn('X', 1);
    print_board();
    int amount = 1;
    while (game_won() == ' ' && !game_tied()) {
        turn(next, amount);
        amount--;
        if (amount == 0) {
            next = next == 'O' ? 'X' : 'O';
            amount = 1;
        }
    }
    print_board();
    char winner = game_won();
    if (winner != ' ') {
        std::cout << game_won() << "'s won!" << std::endl;
        if (winner == 'X') return -1;
        else return 1;
    } else {
        std::cout << "Tie game... Play again?" << std::endl;
        return 0;
    }
}

char Game::game_won() {
    int count = 0;
    char type = ' ';
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            if (type != ' ' && count >= 5) {
                return type;
            }
            if (board[r][c] == type) {
                count++;
            } else {
                type = board[r][c];
                count = 1;
            }
        }
        count = 0;
        type = ' ';
    }
    count = 0;
    type = ' ';
    for (int c = 0; c < 19; c++) {
        for (int r = 0; r < 19; r++) {
            if (type != ' ' && count >= 5) {
                return type;
            }
            if (board[r][c] == type) {
                count++;
            } else {
                type = board[r][c];
                count = 1;
            }
        }
        count = 0;
        type = ' ';
    }
    count = 0;
    type = ' ';
    for (int sum = 4; sum < 32; sum++) {
        for (int r = 0; r < (19 < sum ? 19 : sum); r++) {
            int c = sum - r;
            if (type != ' ' && count >= 5) {
                return type;
            }
            if (board[r][c] == type) {
                count++;
            } else {
                type = board[r][c];
                count = 1;
            }
        }
        count = 0;
        type = ' ';
    }
    count = 0;
    type = ' ';
    for (int sum = 4; sum < 32; sum++) {
        for (int r = 0; r < (19 < sum ? 19 : sum); r++) {
            int c = 18 - (sum - r);
            if (type != ' ' && count >= 5) {
                return type;
            }
            if (board[r][c] == type) {
                count++;
            } else {
                type = board[r][c];
                count = 1;
            }
        }
        count = 0;
        type = ' ';
    }
    return ' ';
}

bool Game::game_tied() {
    bool full = true;
    for (int r = 0; r < 19; r++) {
        for (int c = 0; c < 19; c++) {
            if (board[r][c] == ' ') full = false;
        }
    }
    return full && game_won() == ' ';
} // deprecated
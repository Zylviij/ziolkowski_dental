//
//  main.cpp
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "Game.h"
#include "Network.h"

int main(int argc, const char * argv[]) {
    std::vector<Network> living_pool;
    std::vector<Network> survivors;
    for (int i = 0; i < 100; i++) {
        living_pool.push_back(new Network());
        std::cout << i;
    }
    Game game = *new Game();

    std::cout << std::endl;
    
    for (int generations = 0; generations < 10; generations++) {
        for (int game_num = 0; game_num < 100; game_num +=2) {
            std::cout << "New Game: " << game_num/2 << std::endl;
            int winner = game.play(living_pool.at(game_num), living_pool.at(game_num + 1));
            if (winner == -1) {
                std::cout << "X's won!" << std::endl;
                survivors.push_back(living_pool.at(game_num));
            } else if (winner == 1) {
                std::cout << "O's won!" << std::endl;
                survivors.push_back(living_pool.at(game_num + 1));
            } else {
                std::cout << "Tie..." << std::endl;
                survivors.push_back(living_pool.at(game_num + 1));
            }
        }
        living_pool.clear();
        for (int i = 0; i < 50; i += 2) {
            living_pool.push_back(*new Network(survivors.at(i), survivors.at(i+1)));
            living_pool.push_back(*new Network(survivors.at(i), survivors.at(i+1)));
            living_pool.push_back(*new Network(survivors.at(i+1), survivors.at(i)));
            living_pool.push_back(*new Network(survivors.at(i+1), survivors.at(i)));
        }
        survivors.clear();
        std::cout << "living_pool.size() = " << living_pool.size();
        std::cout << "survivors.size() = " << survivors.size();
    }
    
    return 0;
}

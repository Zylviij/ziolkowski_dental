//
//  Network.cpp
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#include "Network.h"

Network::Network() {
    srand((int) time(NULL));
    for (int i = 0; i < 404681; i++) {
        connection[i] = rand() % 2000 / 1000.0 - 1;
    }
}

Network::Network(Network mother, Network father) {
    srand((int) time(NULL));
    for (int i = 0; i < 404681; i++) {
        connection[i] = rand() % 1000 > 667 ?
            mother.connection[i] + rand() % 20 / 2000.0 - 1 :
            father.connection[i] + rand() % 20 / 2000.0 - 1 ;
    }
}

Tuple Network::calculate_from_output() {
    int col_max_index(0);
    float col_max(FLT_MIN);
    
    int row_max_index(0);
    float row_max(FLT_MIN);
    
    float current;
    
    for (int r = 0; r < 19; r++) {
        current = output[0][r];
        row_max_index = (current > row_max) ? (row_max = current, r) : row_max_index;
    }
    for (int c = 0; c < 19; c++) {
        current = output[1][c];
        col_max_index = (current > col_max) ? (col_max = current, c) : col_max_index;
    }
    //std::cout << row_max_index << ":" << col_max_index << std::endl;
    return Tuple(row_max_index, col_max_index);
}

//Tuple Network::calculate_output_order() {
    
//}

Tuple Network::calculate(char board[19][19]) {
    //std::cout << "Started calculation!" << std::endl;
    int connection_index = 0;
    for (int hidden_row = 0; hidden_row < 19; hidden_row++) {
        for (int hidden_col = 0; hidden_col < 19; hidden_col++) {
            for (int input_row = 0; input_row < 19; input_row++) {
                for (int input_col = 0; input_col < 19; input_col++) {
                    hidden[hidden_row][hidden_col][0] += (board[input_row][input_col] * connection[connection_index++]);
                }
            }
        }
    }
    //std::cout << "Finished the first step!" << std::endl;
    for (int hidden_row = 0; hidden_row < 19; hidden_row++) {
        for (int hidden_col = 0; hidden_col < 19; hidden_col++) {
            for (int input_row = 0; input_row < 19; input_row++) {
                for (int input_col = 0; input_col < 19; input_col++) {
                    hidden[hidden_row][hidden_col][1] += (hidden[input_row][input_col][0] * connection[connection_index++]);
                }
            }
        }
    }
    //std::cout << "Finished the second step!" << std::endl;
    for (int hidden_row = 0; hidden_row < 19; hidden_row++) {
        for (int hidden_col = 0; hidden_col < 19; hidden_col++) {
            for (int input_row = 0; input_row < 19; input_row++) {
                for (int input_col = 0; input_col < 19; input_col++) {
                    hidden[hidden_row][hidden_col][2] += (hidden[input_row][input_col][1] * connection[connection_index++]);
                }
            }
        }
    }
    //std::cout << "Finished the third step!" << std::endl;
    for (int hidden_row = 0; hidden_row < 2; hidden_row++) {
        for (int hidden_col = 0; hidden_col < 19; hidden_col++) {
            for (int input_row = 0; input_row < 19; input_row++) {
                for (int input_col = 0; input_col < 19; input_col++) {
                    output[hidden_row][hidden_col] += (hidden[input_row][input_col][2] * connection[connection_index++]);
                }
            }
        }
    }
    //std::cout << "Finished the fourth step!" << std::endl;
    return calculate_from_output();
}
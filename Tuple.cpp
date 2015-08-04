//
//  Tuple.cpp
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#include "Tuple.h"

int Tuple::getRow() {
    return row;
}
int Tuple::getCol() {
    return col;
}
Tuple::Tuple(int row, int col) {
    this->row = row;
    this->col = col;
}
//
//  Tuple.h
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#ifndef __Connect6__Tuple__
#define __Connect6__Tuple__

#include <stdio.h>

class Tuple {
private:
    int row;
    int col;
public:
    Tuple(int, int);
    int getRow();
    int getCol();
};

#endif /* defined(__Connect6__Tuple__) */

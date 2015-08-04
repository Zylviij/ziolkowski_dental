//
//  Network.h
//  Connect6
//
//  Created by Blake Ziolkowski on 30/07/2015.
//  Copyright (c) 2015 Blake Ziolkowski. All rights reserved.
//

#ifndef __Connect6__Network__
#define __Connect6__Network__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cfloat>
#include <iostream>
#include "Tuple.h"

class Network {
private:
    float hidden[19][19][3];
    float output[2][19];
    float connection[404681];
public:
    Network();
    Network(Network, Network);
    Tuple calculate_from_output();
    Tuple calculate(char board[19][19]);
    
};

#endif /* defined(__Connect6__Network__) */

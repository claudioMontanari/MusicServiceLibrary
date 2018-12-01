//
// Created by Claudio Montanari on 15/11/2018.
//

#ifndef MUSICLIBRARYSERVICE_TESTSUITE_H
#define MUSICLIBRARYSERVICE_TESTSUITE_H

#include <iostream>
#include <vector>
#include "../include/MusicClipPtr.h"

class TestSuite{
public:
    static bool testAll();
    static bool testMusicClipPtr();
};

#endif //MUSICLIBRARYSERVICE_TESTSUITE_H

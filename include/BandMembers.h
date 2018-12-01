//
// Created by Claudio Montanari on 14/11/2018.
//

#ifndef MUSICLIBRARYSERVICE_BANDMEMBERS_H
#define MUSICLIBRARYSERVICE_BANDMEMBERS_H

#include <vector>
#include <string>
#include <iostream>

class BandMembers{
public:
    BandMembers(std::vector<std::string> &band_names): band_names_(band_names){};

    friend std::ostream & operator << (std::ostream &out, const BandMembers &band_members);
    friend std::istream & operator >> (std::istream &in, BandMembers &band_members);

    std::vector<std::string> get_band_names(){return this->band_names_;}

    static bool test_class();
private:
    std::vector<std::string> band_names_;
};

#endif //MUSICLIBRARYSERVICE_BANDMEMBERS_H

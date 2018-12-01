//
// Created by Claudio Montanari on 14/11/2018.
//

#include "../include/BandMembers.h"

std::ostream& operator <<(std::ostream &out, const BandMembers &band_members) {
    out << "Band Members: ";
    auto it = band_members.band_names_.begin();
    out << *it;
    for(++it; it != band_members.band_names_.end(); ++it){
        out << ", " << *it;
    }
    out << std::endl;
    return out;
};

std::istream& operator>>(std::istream &in, BandMembers &band_members) {

};

bool BandMembers::test_class() {
    std::vector<std::string> artist_list(3);
    artist_list[0] = std::string("First Artist");
    artist_list[1] = std::string("Second Artist");
    artist_list[2] = std::string("Third Artist");
    BandMembers class_instance(artist_list);

    std::cout << class_instance;
    return true;
};



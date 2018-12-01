//
// Created by Claudio Montanari on 16/11/2018.
//

#include "../include/MusicClipPtr.h"

/*#####################################################################*/
/*################## Constructor and Destructors ######################*/

MusicClipPtr::MusicClipPtr(long int id) : id_(id) {
    music_clip_ = NULL;
}

MusicClipPtr::MusicClipPtr(std::string& artist, Genre genre, std::vector<std::string>& people,
                                std::string& title, double price) {

    music_clip_ = new MusicClip(artist, genre, people, title, price);
    id_ = music_clip_->ID_;
}

MusicClipPtr::~MusicClipPtr() {
    if(is_in_memory())
        saveToFile();
}

/*#####################################################################*/
/*####################### Memory Management ###########################*/

MusicClipPtr::MusicClip* MusicClipPtr::loadFromFile()  {
    std::ifstream in_file;
    std::string path("../files/");
    path = path + std::to_string(id_) + ".txt";
    in_file.open(path);
    if(is_in_memory())
        return music_clip_;
    if(!in_file)
        std::cerr << "Error while trying to open the file " << path << std::endl;
    else {
        MusicClip* music_clip = new MusicClip(in_file); //TODO  is really okay with const??
        in_file.close();
        return  music_clip;
    }
}

void MusicClipPtr::saveToFile() {
    std::string path("../files/");
    path = path + std::to_string(id_) + ".txt";
    saveToFile(path);
    delete(music_clip_);
    music_clip_ = NULL;
}

void MusicClipPtr::saveToFile(std::string path) {
    std::ofstream out_file;
    out_file.open(path);
    if(!is_in_memory()) {
        std::cerr << "Element not in memory" << std::endl;
        return;
    }
    if(!out_file) {
        std::cerr << "Error while trying to open the file " << path << std::endl;
    }
    else {
        out_file << *this ;
        out_file.close();
    }

}

/*#####################################################################*/
/*###################### Operators Overloading ########################*/

std::ostream& operator <<(std::ostream &out, MusicClipPtr &music_clip_ptr) {

    out << "ID: " << music_clip_ptr->id() << std::endl;
    out << "Index: " << music_clip_ptr->id() << std::endl;
    out << "Title: " << music_clip_ptr->title() << std::endl;
    out << "Artist: " << music_clip_ptr->artist() << std::endl;
    out << "Genre: " << music_clip_ptr->genre() << std::endl;
    out << "Band Members: ";
    if(!music_clip_ptr->people().empty()) {
        out << music_clip_ptr->people()[0];
        for (int i=1; i < music_clip_ptr->people().size(); ++i) {
            out << ", " << music_clip_ptr->people()[i];
        }
    }
    out << std::endl;
    out << "Price: " << music_clip_ptr->price() << std::endl;

    return out;
}

std::ofstream& operator<<(std::ofstream &out, MusicClipPtr &music_clip_ptr) {
    out << std::to_string(music_clip_ptr->id()) << std::endl;
    out << music_clip_ptr->title() << std::endl;
    out << music_clip_ptr->artist() << std::endl;
    out << music_clip_ptr->genre() << std::endl;
    out << std::to_string(music_clip_ptr->people().size()) << std::endl;
    for(int i = 0; i < music_clip_ptr->people().size(); ++i){
        out << music_clip_ptr->people()[i] << std::endl;
    }
    out << std::to_string(music_clip_ptr->price()) << std::endl;
    out << music_clip_ptr->clip() << std::endl;

    return out;
}

inline MusicClipPtr::MusicClip* MusicClipPtr::operator->() {
    if(!is_in_memory())
        music_clip_ = loadFromFile();
    return music_clip_;
}

inline MusicClipPtr::MusicClip& MusicClipPtr::operator*() {
    if(!is_in_memory())
        music_clip_ = loadFromFile();
    return *music_clip_;
}


/*#####################################################################*/
/*##################### MusicClip Nested Class ########################*/

long int MusicClipPtr::MusicClip::instance_count_ = 0;

MusicClipPtr::MusicClip::MusicClip(std::string& artist, Genre genre, std::vector<std::string>& people, std::string& title,
                      double price) {
    this->ID_ = instance_count_;
    MusicClip::instance_count_++;
    this->artist_ = artist;
    this->genre_ = genre;
    this->people_ = people;
    this->title_ = title;
    this->clip_ = std::string("--- Music Clip Section ---");
    this->price_ = price;
};

MusicClipPtr::MusicClip::MusicClip(std::ifstream& in) {
    //File structure:
    //ID
    //Title
    //Artist
    //Genre code
    //#of band members
    //Band member #1
    //...
    //Band member #n
    //Price
    //Clip of the song
    std::string id_str, genre_str, member, people_count_str, price_str;
    int people_count;

    std::getline(in, id_str);
    this->ID_ = std::stol(id_str);

    std::getline(in, this->title_);
    std::getline(in, this->artist_);

    std::getline(in, genre_str);
    this->genre_ = MusicClipPtr::from_string(genre_str);

    std::getline(in, people_count_str);
    people_count = std::stoi(people_count_str);
    for(int i=0; i < people_count; ++i){
        std::getline(in, member);
        this->people_.push_back(member);
    }

    std::getline(in, price_str);
    this->price_ = std::stod(price_str);

    std::getline(in, this->clip_);

}

std::ostream& MusicClipPtr::MusicClip::play(std::ostream &out) {
    return out <<"Playing "<<this->title_<<std::endl;
}

std::ostream& operator <<(std::ostream &out, const MusicClipPtr::Genre &genre){
    switch(genre)
    {
        case MusicClipPtr::Genre::POP_MUSIC :        out << "Pop Music"; break;
        case MusicClipPtr::Genre::FOLK_MUSIC :       out << "Folk Music"; break;
        case MusicClipPtr::Genre::JAZZ :             out << "Jazz"; break;
        case MusicClipPtr::Genre::BLUES :            out << "Blues"; break;
        case MusicClipPtr::Genre::CLASSICAL :        out << "Classical"; break;
        case MusicClipPtr::Genre::COUNTRY_MUSIC :    out << "Country Music" ; break;
        case MusicClipPtr::Genre::REGGAE :           out << "Reggae" ; break;
        case MusicClipPtr::Genre::ROCK :             out << "Rock" ; break;
        case MusicClipPtr::Genre::OPERA:             out << "Opera"; break;

        default: out << "Genre Unknown";
    }
    return out;
}

std::ofstream& operator <<(std::ofstream &out, const MusicClipPtr::Genre &genre) {
    switch(genre){
        case MusicClipPtr::Genre::POP_MUSIC :        out << "1"; break;
        case MusicClipPtr::Genre::FOLK_MUSIC :       out << "2"; break;
        case MusicClipPtr::Genre::JAZZ :             out << "3"; break;
        case MusicClipPtr::Genre::BLUES :            out << "4"; break;
        case MusicClipPtr::Genre::CLASSICAL :        out << "5"; break;
        case MusicClipPtr::Genre::COUNTRY_MUSIC :    out << "6"; break;
        case MusicClipPtr::Genre::REGGAE :           out << "7"; break;
        case MusicClipPtr::Genre::ROCK :             out << "8"; break;
        case MusicClipPtr::Genre::OPERA:             out << "9"; break;

        default: std::cerr << "Error while converting the genre" << genre;
    }
    return out;
}

std::istream& operator>>(std::istream &in, MusicClipPtr::Genre &genre) {
    std::string input;
    in >> input;
    genre = MusicClipPtr::from_string(input);
}

MusicClipPtr::Genre MusicClipPtr::from_string(std::string &genre) {
    int code = stoi(genre);
    switch(code){
        case 1:     return MusicClipPtr::Genre::POP_MUSIC;
        case 2:     return MusicClipPtr::Genre::FOLK_MUSIC;
        case 3:     return MusicClipPtr::Genre::JAZZ;
        case 4:     return MusicClipPtr::Genre::BLUES;
        case 5:     return MusicClipPtr::Genre::CLASSICAL;
        case 6:     return MusicClipPtr::Genre::COUNTRY_MUSIC;
        case 7:     return MusicClipPtr::Genre::REGGAE;
        case 8:     return MusicClipPtr::Genre::ROCK;
        case 9:     return MusicClipPtr::Genre::OPERA;

        default: std::cerr << "Error while parsing from file stream" << std::endl;
    }
}

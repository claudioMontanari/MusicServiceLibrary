//
// Created by Claudio Montanari on 14/11/2018.
//

#ifndef MUSICLIBRARYSERVICE_MUSICCLIPPTR_H
#define MUSICLIBRARYSERVICE_MUSICCLIPPTR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class MusicClipPtr {
    friend class TestSuite;
    enum class Genre { POP_MUSIC, FOLK_MUSIC, JAZZ, BLUES, CLASSICAL, OPERA, COUNTRY_MUSIC, REGGAE, ROCK};

private:
    class MusicClip {
    friend class MusicClipPtr;
    public:
        static const int CLIP_MAX_SIZE = 1000;        //Should be 10MByte

        //Constructor for a newly crated clip
        MusicClip(std::string& artist, Genre genre, std::vector<std::string>& people, std::string& title, double price);
        //Constructor for a memory loaded clip
        MusicClip(std::ifstream& in);

        //Getter
        long int id()                       {return this->ID_; };
        std::string artist()                {return this->artist_; };
        Genre genre()                       {return this->genre_; };
        std::vector<std::string> people()   {return this->people_; };
        std::string title()                 {return this->title_; };
        double price()                      {return this->price_; };
        std::string clip()                  {return this->clip_; }

        //Setter
        void artist(std::string& artist)                 {this->artist_ = artist; };
        void genre(Genre genre)                         {this->genre_ = genre; };
        void people(std::vector<std::string>& people)    {this->people_ = people; };
        void title(std::string& title)                   {this->title_ = title; };
        void price(double price)                        {this->price_ = price; };

        std::ostream& play(std::ostream &out);

    private:
        //Attributes
        static long int instance_count_;
        int long ID_;
        int index_;
        std::string artist_;
        Genre genre_;
        std::vector<std::string> people_;
        std::string title_;
        std::string clip_;
        double price_;
    };

    long int id_;
    MusicClip * music_clip_;

    MusicClipPtr::MusicClip* loadFromFile() ;

public:
    MusicClipPtr() = default;
    MusicClipPtr(long int id);
    MusicClipPtr(std::string& artist, Genre genre, std::vector<std::string>& people,
                 std::string& title, double price);
    MusicClipPtr(MusicClipPtr& copy);

    ~MusicClipPtr();

    void saveToFile() ;
    void saveToFile(std::string path);

    MusicClip& operator*() ;
    MusicClip* operator->() ;

    bool is_in_memory() const {return music_clip_ != NULL;};

    static Genre from_string(std::string& genre);
    friend std::ostream& operator<<(std::ostream &out, const Genre &genre);
    friend std::ofstream& operator<<(std::ofstream &out, const Genre &genre);
    friend std::istream& operator>>(std::istream &in, Genre &genre);

    friend std::ostream& operator<<(std::ostream &out, MusicClipPtr &music_clip_ptr);
    friend std::ofstream& operator<<(std::ofstream &out, MusicClipPtr &music_clip_ptr);

};

#endif //MUSICLIBRARYSERVICE_MUSICCLIPPTR_H

//
// Created by Claudio Montanari on 14/11/2018.
//

#ifndef MUSICLIBRARYSERVICE_CLIPLIST_H
#define MUSICLIBRARYSERVICE_CLIPLIST_H

#include "ClipNode.h"
#include <fstream>

class ClipList{
public:
    ClipList(int size);
    ~ClipList();

    bool search_clip(long int id);

    void print_current(std::ostream& out);
    void current_save(std::string& path);
    void current_new(std::string& artist, std::string genre, std::vector<std::string>& people, std::string& title,
                     double price);
    void current_update_price(double price) { load_node(current_); current_->music_clip()->price(price);};
    bool is_empty() const                   {return this->head_ == NULL;};

    friend std::ostream& operator<<(std::ostream &out, ClipList &clip_list);
    void save_clips();

private:
    static const int MAX_IN_MEMORY = 3;

    ClipNode * head_ = NULL;
    ClipNode * current_ = NULL;
    int in_memory_counter_ = 0;
    int in_memory_index_ = 0;
    ClipNode * in_memory[MAX_IN_MEMORY];

    //Iterator functions
    ClipNode* begin()   {this->current_ = this->head_; return this->current_;};
    ClipNode* next()    {return this->current_;};
    bool end()          {return this->current_->has_next();};
    void load_node(ClipNode* node);
    void update_in_memory();

    void delete_node(ClipNode* node);
};
#endif //MUSICLIBRARYSERVICE_CLIPLIST_H

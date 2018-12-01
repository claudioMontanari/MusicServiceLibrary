//
// Created by Claudio Montanari on 16/11/2018.
//

#include "../include/ClipList.h"


ClipList::ClipList(int size) {
    head_ = new ClipNode(0);

    ClipNode * current = head_;
    for(int i=1; i<size; ++i){
        current->next(new ClipNode(i));
        current = current->next();
    }

    for(int i=0; i<MAX_IN_MEMORY; ++i)
        in_memory[i] = NULL;
    in_memory_counter_ = 0;
    in_memory_index_ = 0;
}

ClipList::~ClipList() {
    if(!this->is_empty()) {
        ClipNode *current = this->begin();
        if (current->has_next()) {
            delete_node(current->next());
        }

        //Search if in memory and then delete it
/*        if(current->music_clip().is_in_memory())
        for(int i=0; i<MAX_IN_MEMORY; ++i){
            if(in_memory[i] != NULL && in_memory[i] == current) {
                in_memory[i] = NULL;
                --in_memory_counter_;
            }
        }
*/
        delete(current);
    }
}

void ClipList::delete_node(ClipNode *node) {
    if(node->has_next())
        delete_node(node->next());

    //Search if in memory and then delete it
/*    for(int i=0; i<MAX_IN_MEMORY; ++i){
        if(in_memory[i] != NULL && in_memory[i] == node) {
            in_memory[i] = NULL;
            --in_memory_counter_;
        }
    }
*/
    delete(node);
}

bool ClipList::search_clip(long int id) {
    bool found = false;
    if(!this->is_empty()){
        current_ = head_;
        do {
            load_node(current_);
            if (current_->music_clip()->id() == id)
                found = true;
            if(!found)
                current_ = current_->next();
        }
        while(current_ != NULL && !found);
    }
    return found;
}

void ClipList::save_clips() {
    if(!is_empty()){
        ClipNode* current = head_;
        while (current != NULL){
            if(current->music_clip().is_in_memory())
                current->music_clip().saveToFile();
            current = current->next();
        }
        update_in_memory();
    }
}

void ClipList::current_save(std::string& path) {
    load_node(current_);
    current_->music_clip().saveToFile(path);
    update_in_memory();
}

void ClipList::current_new(std::string& artist, std::string genre, std::vector<std::string>& people, std::string& title,
                           double price) {
    load_node(current_);
    current_->music_clip()->artist(artist);
    current_->music_clip()->genre(MusicClipPtr::from_string(genre));
    current_->music_clip()->people(people);
    current_->music_clip()->title(title);
    current_->music_clip()->price(price);
}

void ClipList::load_node(ClipNode* node){

    if(!node->music_clip().is_in_memory()) {
        //Restart circular index if necessary
        if (in_memory_index_== ClipList::MAX_IN_MEMORY) {
            in_memory_index_ = 0;
        }
        //If position is occupied, save to file the content before
        if(in_memory[in_memory_index_] != NULL) {
            in_memory[in_memory_index_]->music_clip().saveToFile();
            --in_memory_counter_;
        }
        in_memory[in_memory_index_] = node;
        ++in_memory_index_;
        ++in_memory_counter_;
    }

}

void ClipList::update_in_memory(){
    int updated_in_memory = in_memory_counter_;

    for (int i = 0; i < MAX_IN_MEMORY; ++i) {
        if(in_memory[i] != NULL && !in_memory[i]->music_clip().is_in_memory()){
            --updated_in_memory;
            in_memory[i] = NULL;
        }
    }
    in_memory_counter_ = updated_in_memory;
}

std::ostream& operator<<(std::ostream &out, ClipList &clip_list){
    if(!clip_list.is_empty()){
        ClipNode * current = clip_list.head_;

        while (current != NULL){
            clip_list.load_node(current);
            out << current->music_clip() << std::endl;
            current = current->next();
        }
    }
    return out;
}

void ClipList::print_current(std::ostream &out) {
    load_node(current_);
    out << current_->music_clip() << std::endl;
}

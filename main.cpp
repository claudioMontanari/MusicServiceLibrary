#include <iostream>
#include <string>
#include "include/ClipList.h"

void list_all(ClipList& list, std::ostream& out){
    out << "Here are the Music Clips in the system:" << std::endl;
    out << list << std::endl;
}

void set_current(ClipList& list, std::ostream& out, std::istream& in){
    long int id;
    out << "Insert the id of the file you want to edit (values between 0-9)" << std::endl;
    in >> id;
    if(list.search_clip(id))
        out << "Clip successfully found and set as current" << std::endl;
}

void read_valid_line(std::istream& in, std::string& destination){
    getline(in, destination);
    while (destination.length()==0 )
        getline(in, destination);
}

void create_new(ClipList& list, std::ostream& out, std::istream& in){
    std::string title, artist, people_member, genre_str, id_str, price_str;
    std::vector<std::string> people;
    double price;
    long int id;

    out << "Creation of a new music clip:" << std::endl;

    out << "ID (must be between 0 and 9): ";
    read_valid_line(in, id_str);
    id = std::stol(id_str);

    out << "Title: ";
    read_valid_line(in, title);

    out << "Artist: ";
    read_valid_line(in, artist);

    do {
        out << "People: (write quit to stop with the people list)";
        read_valid_line(in, people_member);
        if( people_member.compare(std::string("quit")) != 0 )
            people.push_back(people_member);
    } while( people_member.compare(std::string("quit")) != 0);

    out << "Genre: ";
    read_valid_line(in, genre_str);

    out << "Price: ";
    read_valid_line(in, price_str);
    price = std::stod(price_str);

    if(list.search_clip(id)){
        list.current_new(artist, genre_str, people, title, price);
    } else
        out << "Insert a valid ID please" << std::endl;

}

void copy_into_file(ClipList& list, std::ostream& out){
    std::string path("../temp.clip");
    list.current_save(path);
    out << "Node correctly saved into the file temp.clip" << std::endl;
}

void change_price(ClipList& list, std::ostream& out, std::istream& in ){
    double new_price;

    out << "Insert new price for current music clip: " << std::endl;
    in >> new_price;
    list.current_update_price(new_price);
    out << "Music Clip updated successfully: " << std::endl;
    list.print_current(out);
}

void save(ClipList& list, std::ostream& out){
    out << "Saving all the updated music clip in memory..." << std::endl;
    list.save_clips();
    out << "Music clip saved successfully" << std::endl;
}

void file_commands(ClipList& list, std::ostream& out, std::istream& in){
    std::string path("../input.inp");
    std::ifstream in_file;
    in_file.open(path);
    if(!in_file){
        out << "Unable to find the input.inp file" << std::endl;
    } else{
        out << "Start parsing of the input commands file" << std::endl;
        char input;
        std::string input_command;
        std::ofstream out_file;
        out_file.open(std::string("../files/output.out"));
        do{
            //read_valid_line(in_file, input_command);
            in_file >> input;

            switch(input){
                case 'l': list_all(list, out_file); break;
                case 'e': set_current(list, out_file, in_file); break;
                case 'c': create_new(list, out_file, in_file); break;
                case 'y': copy_into_file(list, out_file); break;
                case 'p': change_price(list, out_file, in_file); break;
                case 's': save(list, out_file); break;
                case 'q': out << "Exiting from the input file parsing system, goodbye!" << std::endl; break;
                default: out << "Command not valid found in the file, be careful!" << std::endl;
            }
        }
        while(input != 'q');
        in_file.close();
        out_file.close();
    }
}

int main() {

    ClipList list(10);
    char input;

    std::cout << "Welcome to the Music Library Service Command Line Interface!" << std::endl;
    do{
        std::cout << "COMMANDS:" << std::endl;
        std::cout << "- l: list all the music clip" << std::endl;
        std::cout << "- e: to choose a music clip to edit" << std::endl;
        std::cout << "- c: create a new music clip" << std::endl;
        std::cout << "- y: copy the current music clip into a file" << std::endl;
        std::cout << "- i: take commands from a file" << std::endl;
        std::cout << "- p: change price for the current music file" << std::endl;
        std::cout << "- s: save all the music clip in memory" << std::endl;
        std::cout << "- q: quit" << std::endl;
        std::cin >> input;

        switch(input){
            case 'l': list_all(list, std::cout); break;
            case 'e': set_current(list, std::cout, std::cin); break;
            case 'c': create_new(list, std::cout, std::cin); break;
            case 'y': copy_into_file(list, std::cout); break;
            case 'i': file_commands(list, std::cout, std::cin); break;
            case 'p': change_price(list, std::cout, std::cin); break;
            case 's': save(list, std::cout); break;
            case 'q': std::cout << "Exiting from the system, goodbye!" << std::endl; break;
            default: std::cout << "Command not valid, retry please" << std::endl;
        }
    }
    while(input != 'q');

    return 0;
}
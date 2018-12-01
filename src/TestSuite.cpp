//
// Created by Claudio Montanari on 15/11/2018.
//

#include "../include/TestSuite.h"

bool TestSuite::testAll() {
    bool test_passed;
    std::cout<< "Start testing of all the classes in the project..."<<std::endl;
    test_passed = testMusicClipPtr();

    return test_passed;
}

bool TestSuite::testMusicClipPtr() {

    bool test_passed = true;
    std::cout << "Testing class MusicClip Constructors "<< std::endl;
    std::string artist("Artist Name");
    std::string title("Song Title");
    std::vector<std::string> people_vector;
    std::vector<std::string> empty_people_vector;

    people_vector.push_back(std::string("Guitarist"));
    people_vector.push_back(std::string("Guitarist2"));
    people_vector.push_back(std::string("Batterist"));
    people_vector.push_back(std::string("Second Singer"));

    //Build a generic class instance
    MusicClipPtr class_instance(artist, MusicClipPtr::Genre::ROCK, people_vector, title, 19.99);
    std::cout << class_instance << std::endl;
    class_instance->play(std::cout);

    //Build a class instance without band members
    MusicClipPtr class_instance_no_band(artist, MusicClipPtr::Genre::ROCK, empty_people_vector , title, 10.5);
    std::cout << class_instance_no_band << std::endl;
    class_instance_no_band->play(std::cout);

    //Build a class instance from file
    MusicClipPtr class_instance_from_file(1234);
    test_passed = test_passed && !class_instance_from_file.is_in_memory();
    std::cout << class_instance_from_file << std::endl;
    class_instance_from_file->play(std::cout);
    test_passed = test_passed && class_instance_from_file.is_in_memory();

    //Getter and Setter testing


    return test_passed;

}

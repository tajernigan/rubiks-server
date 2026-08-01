#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Cube {
public:
    Cube();

    // moves cube based on space delimited list of valid cube notation THIS ALTERS THE CUBE STATE
    void move_string(const std::string&); 

    // returns string of correct moves to perform the cube to solve in its current state, THIS DOES NOT CHANGE THE CUBE STATE
    std::string solve();

    // getter for cube state
    std::vector<int> get_cube_state();

    bool is_solved(); // returns if cubes current state is solved

private:
    std::vector<int> cube_state; // initialize to size 40, 20 slots for positions of edges and corners and 20 slots for orientation of edges and corners

    void move(int); // moves the cube based on serialized move, should be in set {1, 2, ..., 18}

    // takes cube to next group given a move_set and the hash function for the given group
    template<typename hash_return_value>
    std::string complete_stage(std::vector<int>& move_set, hash_return_value (*hash_function)(std::vector<int>));
};
#include "Cube.h"

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <utility>

const std::unordered_map<char, int> FACE_MAP{
    {'U', 0}, {'D', 1}, {'R', 2}, {'L', 3}, {'F', 4}, {'B', 5}
};

// indexes [][0..3] represent positions of edges such that swapping them would result in the case of a clockwise move
// indexes [][4] and [][9] represent the orientations of the edges and corners respectively, only F and B moves alter the edge orientation and the corner orientation is a little tricky to explain
// indexes [][5..8] repsent the positions of corner in the same style per the edges 
const int MOVE_ARRAY[][10] = {
    {0,1,3,2,0,0,2,3,1}, // U
    {6,7,9,8,0,4,6,7,5}, // D
    {2,5,8,10,0,3,5,7,1}, // R
    {1,11,7,4,0,0,6,4,2}, // L
    {3,4,6,5,1,2,4,5,3}, // F
    {0,10,9,11,1,1,7,6,0} // B
};

const int CORNER_ORIENTATION_SWAPS[][2] = {
    {1, 2}, // U
    {1, 2}, // D
    {0, 1}, // R
    {0, 1}, // L
    {0, 2}, // F
    {0, 2}  // B
};

// helper function to convert a move string ie U' -> 1 or L2 -> 11, if its not a valid move it should return 18
int encode_move(const std::string move){
    const auto face = FACE_MAP.find(move[0]);
    if (face == FACE_MAP.end() || move.size() > 2) return 18; // return invalid int if not a move
    
    int direction = 0;
    if (move.size() == 2) {
        switch (move[1]) {
            case '\'':
                direction = 1;
                break;
            case '2':
                direction = 2;
                break;
            default:
                return 18;
        }
    }

    return 3 * face->second + direction; // this should map to a unique move
}

Cube::Cube(){
    // {0, 1, ..., 11, 0, 1, ..., 7, 0, 0, ..., 0} first 12 indexs are positions of edges, 12-19 are positions of corners, 20-31 are orientation of edges, 32-39 are orientations of corners 
    for (int i = 0; i < 12; i++) this->cube_state.push_back(i);
    for (int i = 12; i < 20; i++) this->cube_state.push_back(i - 12);
    for (int i = 20; i < 40; i++) this->cube_state.push_back(0);
}

bool Cube::is_solved(){
    for (int i = 0; i < 12; i++) if (this->cube_state[i] != i) return false;
    for (int i = 12; i < 20; i++) if (this->cube_state[i] != i - 12) return false;
    for (int i = 20; i < 40; i++) if (this->cube_state[i] != 0) return false;
    return true;
}

std::vector<int> Cube::get_cube_state(){
    return this->cube_state;
}

// iterate through string encode the move then pass through internal "move" method
void Cube::move_string(const std::string& moves){
    std::istringstream move_stream(moves);
    std::string token;

    while (move_stream >> token) {
        if (token.empty()) continue;
        int move = encode_move(token);
        if (move != 18) this->move(move);
    }
}

void Cube::move(int move){
    // deserialize to get move face and direction
    int face = move / 3;
    int direction = move % 3;
    const int* move_instuctions = MOVE_ARRAY[face];

    if (direction == 2){
        // swap edges across from each other
        std::swap(this->cube_state[move_instuctions[0]], this->cube_state[move_instuctions[2]]);
        std::swap(this->cube_state[move_instuctions[1]], this->cube_state[move_instuctions[3]]);

        // swap corners across from each other
        std::swap(this->cube_state[move_instuctions[5] + 12], this->cube_state[move_instuctions[7] + 12]);
        std::swap(this->cube_state[move_instuctions[6] + 12], this->cube_state[move_instuctions[8] + 12]);
    }

    else {
        // orientation of the edges
        for (int i = 0; i < 4; i++){
            int edge_orientation_location = this->cube_state[move_instuctions[i]] + 20;
            this->cube_state[edge_orientation_location] ^= move_instuctions[4];
        }

        // orientation of corners, ik its pretty weird
        for (int i = 5; i < 9; i++){
            int corner_orientation_location = this->cube_state[move_instuctions[i] + 12] + 32;
            int orientation_a = CORNER_ORIENTATION_SWAPS[face][0];
            int orientation_b = CORNER_ORIENTATION_SWAPS[face][1];
            if (this->cube_state[corner_orientation_location] == orientation_a) this->cube_state[corner_orientation_location] = orientation_b;
            else if (this->cube_state[corner_orientation_location] == orientation_b) this->cube_state[corner_orientation_location] = orientation_a;
        }

        if (direction == 0){
            // swap edges
            for (int i = 1; i < 4; i++){
                std::swap(this->cube_state[move_instuctions[i-1]], this->cube_state[move_instuctions[i]]);
            }

            // swap corners
            for (int i = 6; i < 9; i++){
                std::swap(this->cube_state[move_instuctions[i-1] + 12], this->cube_state[move_instuctions[i] + 12]);
            }
        }

        else {
            // swap edges
            for (int i = 3; i > 0; i--){
                std::swap(this->cube_state[move_instuctions[i-1]], this->cube_state[move_instuctions[i]]);
            }

            // swap corners
            for (int i = 8; i > 5; i--){
                std::swap(this->cube_state[move_instuctions[i-1] + 12], this->cube_state[move_instuctions[i] + 12]);
            }
        }
    }
}
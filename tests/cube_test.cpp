#include <gtest/gtest.h>
#include <iostream>
#include "Cube.h"

TEST(MoveTests, InitCube) {
    Cube cube;
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, F) {
    Cube cube;
    cube.move_string("F F'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, B) {
    Cube cube;
    cube.move_string("B B'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, U) {
    Cube cube;
    cube.move_string("U U'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, D) {
    Cube cube;
    cube.move_string("D D'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, R) {
    Cube cube;
    cube.move_string("R R'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, L) {
    Cube cube;
    cube.move_string("L L'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, F2) {
    Cube cube;
    cube.move_string("F2 F2");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, ReverseMoves) {
    Cube cube;
    cube.move_string("R F2 B' R U2 D' R U' L2 D' R2 B2 R2 D2 R2 U' F2 D' R' F'");
    cube.move_string("F R D F2 U R2 D2 R2 B2 R2 D L2 U R' D U2 R' B F2 R'");
    EXPECT_TRUE(cube.is_solved());
}

TEST(MoveTests, Superflip){
    Cube cube;
    cube.move_string("U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2"); // super flip scramble
    auto cube_state = cube.get_cube_state();

    for (size_t i =20; i < 32; i++){ // all edge orientations should be flipped
        EXPECT_EQ(1, cube_state[i]);
    }

    for (size_t i = 32; i < 40; i++){
        EXPECT_EQ(0, cube_state[i]);
    }
}
//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */



int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

   if (board_size != BOARD_SIZE) {

        throw ServerException("the board size is not right");
    }

   else if (p1_setup_board == "" && p2_setup_board == ""){
       throw ServerException("one of the files does NOT exist");
   }
    else{

        this->board_size = board_size;
    }
}


Server::~Server() {
}

/*
1- Get the columns and rows from file
2- Place them in a *pointer as an array of bits
3- Return that array as a BitArray2D

for initializiation */


BitArray2D *Server::scan_setup_board(string setup_board_name){

    vector<string> lines(board_size,"");
    ifstream myfile;
    myfile.open(setup_board_name);

    string each_line;
    int i=0, k = 0, my_rows=0, my_columns=0;

    while(!myfile.eof()) {

            while(getline(myfile,each_line)){
                lines[i] = each_line;
                i++;
            }
        }

    //ASK??
    my_rows = i;
    my_columns = lines[0].size();

    myfile.close();


    //BitArray2D::BitArray2D(unsigned int rows, unsigned int columns)
    BitArray2D *pointer;
    pointer = new BitArray2D(my_rows, my_columns);

    //BitArray2D::set(unsigned int row, unsigned int column)

    for (int j = 0; i < my_rows; i++) {

        for (int k = 0; k < my_columns; k++) {
            if (lines[i].at(k) != '_') {
                pointer->set(j,k);
            }
        }
    }
    BitArray2D *pointer2 = pointer;
    return pointer2;


    //return pointer;


}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    vector<string> lines(board_size,"");

    ifstream myfile;

    // check if the coordinates are within the possible limits
    if (x > board_size-1 || x < 0 || y < 0 || y > board_size-1){
        return OUT_OF_BOUNDS;
    }

    if (player > MAX_PLAYERS || player < 1){
        throw ServerException("invalid player number");
    }

    // compare the player's board against his/her opponent's

    if(player==2){
        player=1;
    }
    else{
        player=2;
    }

    string file_name = "player_"+ to_string(player) +".setup_board.txt";

    myfile.open(file_name);

    string each_line;
    string *pointer;
    int i=0, k = 0;
    char target;

    while(!myfile.eof()) {

        while(getline(myfile,each_line)){
            lines[i] = each_line;

            i++;
        }
    }
    myfile.close();

    target = lines[y].at(x);

    // this target should be

    if (target == 'C' || target == 'B' || target == 'R' || target == 'S' || target == 'D') {
        return HIT;
    }
    else {
        return MISS;
    }

}

int Server::process_shot(unsigned int player) {
    // https://stackoverflow.com/questions/47297648/using-cereal-to-deserialize-a-json-string
    int x;
    int y;
    int shot_result;
    int result;

    std::ifstream myfile;
    //ifstream myfile;
    ofstream outfile;

    if (player > MAX_PLAYERS || player <= 0) {
        throw ServerException("invalid player number");
    }


    string file_nameOut = "player_" + to_string(player) + ".result.json";
    string file_nameIn = "player_" + to_string(player) + ".shot.json";

    myfile.open(file_nameIn);


    if (!myfile) {
        return NO_SHOT_FILE;
    }

    // deserialize; convert JSON string to custom
    //pass the stream sting object into the input archive
    cereal::JSONInputArchive archive_in(myfile);

    // use input archive to extract data to my program
    archive_in(x, y);
    cout << x << endl;
    cout << y << endl;

    remove((file_nameIn).c_str());



    result = evaluate_shot(player, x, y);
    myfile.close();

    outfile.open(file_nameOut);

    cereal::JSONOutputArchive archive_out(outfile);
    archive_out(CEREAL_NVP(result));
          return SHOT_FILE_PROCESSED;

}
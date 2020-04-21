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
#include "Client.hpp"

Client::~Client() {
}

/**
 * Performs the initialization functions that normally would be in a constructor, but needs to be a separate
 * function for googletest so clients may be initialized in the SetUp() function.
 * Creates player_#.action_board.json.
 * @param player - the id of the player
 * @param board_size - the square size of the action board
 */
void Client::initialize(unsigned int player, unsigned int board_size){

    this->player = player;
    this->board_size = board_size;

    if (player <= 0 || player > MAX_PLAYERS){
        throw ClientWrongPlayerNumberException();
    }


    string file_name = "player_"+to_string(player)+".action_board.json";

    // this is considered as a vector of strings "D", "R", "S", "T"
    vector<int> line(board_size);
    // this is considered as a vector of vector of strings
    vector<vector<int>> myBoard(board_size, line);

    ofstream outfile;
    outfile.open(file_name);
    cereal::JSONOutputArchive archive_out(outfile);

    //archive_out(CEREAL_NVP(myBoard));
    archive_out(cereal::make_nvp("board", myBoard));


}

void Client::fire(unsigned int x, unsigned int y) {

    string file_name = "player_"+to_string(player)+".shot.json";

    std::ifstream myfile;
    ofstream outfile;

    outfile.open(file_name);
    // assign the string stream object to the Output Archive
    cereal::JSONOutputArchive archive_out(outfile);
    archive_out(CEREAL_NVP(x),CEREAL_NVP(y));

}

bool Client::result_available() {

    //ifstream ifile("result");
     //if (ifile) {return true;}
     //else {return false;}
    string file_name = "player_"+to_string(player)+".result.json";
    //std::ifstream myfile;
    ifstream myfile;
    myfile.open(file_name);

    if (!myfile){
        //throw ClientException("no available results!");
        return false;
    }
    else{
        return true;
    }

    //myfile.close();
    //return myfile.good();
}


int Client::get_result() {

    //string result;
    int result;
    if (!result_available()) {
        throw ClientException("no available results!");
    }

    else {
        string file_name = "player_" + to_string(player) + ".result.json";
        std::ifstream myfile;
        myfile.open(file_name);

        //convert from JSON
        cereal::JSONInputArchive archive_in(myfile);
        archive_in(result);
        //myfile.close();
        remove((file_name).c_str());

        if (result == 1 || result == -1 || result==0) {
            //return HIT;
            return result;

        }

        throw ClientException("no valid results!");

    }
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {

    string file_nameIn = "player_" + to_string(player) + ".action_board.json";

    // this is considered as a vector of strings "D", "R", "S", "T"
    vector<int> line(board_size);
    // this is considered as a vector of vector of strings
    vector<vector<int>> myBoard(board_size, line);


    myBoard[y][x] = result;
    //cout<< result << endl;
    //cout<< myBoard[y][x] << endl;



    ofstream outfile;
    outfile.open(file_nameIn);

    cereal::JSONOutputArchive archive_out(outfile);
    //archive_out(CEREAL_NVP(myBoard));
    archive_out(cereal::make_nvp("board", myBoard));
    //infile.close();

}

string Client::render_action_board(){


    string file_nameIn = "player_" + to_string(player) + ".action_board.json";

    // this is considered as a vector of strings "D", "R", "S", "T"
    vector<int> line(board_size);
    // this is considered as a vector of vector of strings
    vector<vector<int>> myBoard(board_size, line);
    string myLines;

    ifstream infile;
    infile.open(file_nameIn);
    cereal::JSONInputArchive archive_in(infile);

    archive_in(myBoard);
    int i=0;


    while(i != board_size){

        for (int k = 0; k < board_size; k++) {
            myLines += to_string(myBoard[i][k]);
        }
        i++;


    }

    return myLines;

}
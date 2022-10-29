/*
 * Author: Zharassov Aday   
 * Student_ID: 20182028
 * Email: batthurt2@unist.ac.kr
 */

#include <iostream>

#include "game_spec.h"
#include "game_tree_search.h"


int iterate_func(const GameSpec& spec, std::vector<int> pole, int turn){
    
    std::vector<std::vector<int>> tempWinSeq = spec.getWinSeq();
    int prev = -50;
    for (auto& i : tempWinSeq){

        bool win = true;
        if (pole[i[0]] == 0 || pole[i[0]] == -1){
                continue;
        }
        for (auto& j : i){
            if (pole[j] != pole[i[0]]) {
                win = false;
                break;
            }  
        }
        if (win == true) {
            if (i[0] == 1){
                return 1;
            }
            else if (i[0] == 2){
                return -1;
            }
        }


        
    }

    bool isFull = true;

    for (int i = 0; i < pole.size(); i++){
        if (pole[i] == 0) {
            isFull = false;
            break;
        }
    }

    if (isFull == true){
        return 0;
    }

    turn = turn % 2; 
    int payOff = (turn == 1 ? 1 : -1);
    int newPayOff;
    for (int i = 0; i < pole.size(); i++){
        
        if (pole[i] > 0 || pole[i] < 0) {
            continue;
        }

        pole[i] = (turn == 1 ? 1 : 2);

        newPayOff = iterate_func(spec, pole, turn+1);

        if (turn == 1) {
            if (newPayOff == 1) {
                return 1;
            }
            else{
                payOff = (newPayOff > payOff ? newPayOff : payOff);
            }
        }
        else if (turn == 0) {
            if (newPayOff == -1){
                return -1;
            }
            else{
                payOff = (newPayOff < payOff ? newPayOff : payOff);
            }
        }

        pole[i] = 0;
    }

    return payOff;

}

int GameTree::computeGameTree(const GameSpec& spec) {
    std::vector<int> pole;
    for (int i = 0; i < spec.getSize(); i++){
        if (spec.isBlocked(i)){
            pole[i] = -1;
            continue;
        }
        pole[i] = 0;
    }

    return iterate_func(spec, pole, 1);
}


void GameTree::printGameTree(const GameSpec& spec) {

}


void GameTree::playAsFirstPlayer(const GameSpec& spec) {

}


void GameTree::playAsSecondPlayer(const GameSpec& spec) {

}


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

    std::vector<int> indices;

    for (int i = 0; i < tempWinSeq.size(); i++){

        bool win = true;
        for (int j = 0; j < tempWinSeq[i].size(); j++){

            win = true;

            if (pole[tempWinSeq[i][j]] == 0 || pole[tempWinSeq[i][j]] == -1){
                win = false;
                break;
            }
            
            if (j >= 1) {
                if (tempWinSeq[i][j-1] != tempWinSeq[i][j]){
                    win = false;
                    indices.push_back(i);
                    break;
                }
            }
            
        }
        if (win == true) {
            if (tempWinSeq[i][0] == 1){
                return 1;
            }
            else if (tempWinSeq[i][0] == 2){
                return -1;
            }
        }


        
    }

    int temp = 0;
    if (indices.size() > 0) {
        for (int i = 0; i < indices.size(); i++){
            tempWinSeq.erase(tempWinSeq.begin() + indices[i] - temp);
            temp++;
        }
    }

    bool isFull = true;

    for (int i = 0; i < pole.size(); i++){
        if (pole[i] == 0) {
            isFull = false;
        }
    }

    if (isFull == false){
        return 0;
    }

    turn = turn % 2;
    int payOff = (turn == 1 ? 1 : -1);

    for (int i = 0; i < pole.size(); i++){
        
        if (pole[i] > 0) {
            continue;
        }

        pole[i] = (turn == 1 ? 1 : 2);

        int newPayOff = iterate_func(spec, pole, turn+1);

        if (turn == 1) {
            if (newPayOff == 1) {
                return 1;
            }
            payOff = (newPayOff > payOff ? newPayOff : payOff);
        }
        else if (turn == 0) {
            if (newPayOff == -1){
                return -1;
            }
            payOff = (newPayOff < payOff ? newPayOff : payOff);

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


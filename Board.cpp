#include "Board.h"

Board::Board(Pieces *pPieces, int pScreenHeight) {
    mScreenHeight = pScreenHeight;
    mPieces = pPieces;
    
    InitBoard();
}

void Board::InitBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = POS_FREE;
        }
    }
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation) {
    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            if (mPieces->GetBlockType(pPiece, pRotation, i, j) != 0) {
                mBoard[pX + i][pY + j] = POS_FILLED;
            }
        }
    }
}

bool Board::IsGameOver() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) { //why is is it [i][0] and not [0][i]
            return true;
        }
    }
    
    return false;
}

void Board::DeleteLine (int pY) {
    for (int i = 0; i < pY; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            mBoard[j][pY - i] = mBoard[j][pY - i - 1];
        }
    }
}

void Board::DeletePossibleLines() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        bool filled = true;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (mBoard[i][j] == POS_FREE) {
                filled = false;
            }
        }

        if (filled) {
            DeleteLine(i);
        }
    }
}

bool Board::IsFreeBlock(int pX, int pY) {
    return mBoard[pX][pY] == POS_FILLED;
}

int Board::GetXPosInPixels (int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels (int pPos) {
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation) {
    int xLoc = -1;
    int yLoc = -1;

    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            xLoc = pX + i;
            yLoc = pY + j;

            if (mPieces->GetBlockType(pPiece, pRotation, i, j) != 0 && ((xLoc < 0 || xLoc > BOARD_WIDTH || yLoc < 0 || yLoc > BOARD_HEIGHT) || (!IsFreeBlock(xLoc, yLoc)))) {
                return false;
            }
        }
    }
    
    return true;
}
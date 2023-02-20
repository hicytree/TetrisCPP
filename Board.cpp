#include "Board.h"
#include <iostream>
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
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
            if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) {
//              	std::cout << "pX: " << pX << " i: " << i << " pY: " << pY << " j: " << j << std::endl;
				mBoard[i1][j1] = POS_FILLED;
            }
        }
    }

//	printBoard();
}

bool Board::IsGameOver() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) {
            std::cout << "game over." << std::endl;
//			printBoard();
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
            if (mBoard[j][i] == POS_FREE) {
                filled = false;
            }
        }

        if (filled) {
            DeleteLine(i);
        }
    }
}

bool Board::IsFreeBlock(int pX, int pY) {
    return mBoard[pX][pY] == POS_FREE;
}

int Board::GetXPosInPixels (int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels (int pPos) {
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

void Board::printBoard() {
	for (int a = 0; a < BOARD_HEIGHT; a++) {
		for (int b = 0; b < BOARD_WIDTH; b++) {
			std::cout << mBoard[b][a] << " ";
		}	
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation) {
  //  std::cout << "pX: " << pX << " pY: " << pY << std::endl;
	
	for (int i1 = pX, i2 = 0; i2 < PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j2 < PIECE_BLOCKS; j1++, j2++) {
			if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1)
			{
	//			std::cout << mPieces->GetBlockType (pPiece, pRotation, j2, i2) << std::endl;
	//			std::cout << pPiece << " " << pRotation << " " << i2 << " " << j2 << std::endl;
				if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) {
	//				std::cout << "outta bounds " << i1 << " " << j1 << std::endl;
					return false;
				}
			}	

			if (j1 >= 0)
			{	
				if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) && (!IsFreeBlock (i1, j1))) { 
//					std::cout << "filled" << std::endl;
					return false;
				}
			}
		}
	}
			/*
            if (mPieces->GetBlockType(pPiece, pRotation, i, j) != 0 && (yLoc > BOARD_HEIGHT || !IsFreeBlock(xLoc, yLoc))) {
                std::cout << "piece: " << pPiece << " rotation: " << pRotation << " i: " << i << " j: " << j << " xLoc: " << xLoc << " yLoc: " << yLoc << std::endl << std::endl;
				return false;
            }
			*/
    
//	std::cout << "true" << std::endl;
    return true;
}

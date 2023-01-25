#include "Game.h"
#include "IO.h"
#include <cstdlib>

Game::Game (Board* pBoard, Pieces* pPieces, IO* pIO, int pScreenHeight) {
    mBoard = pBoard;
    mPieces = pPieces;
    mIO = pIO;
    mScreenHeight = pScreenHeight;
}

int Game::getRand(int pA, int pB) {
    return pA + int(rand() % (pB - pA + 1));
}

void Game::initGame() {
    mPiece = getRand(0, 6);
    mRotation = 0;
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition (mPiece, mRotation);

    mNextPiece = getRand(0, 6);
    mNextRotation = 0;
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

void Game::CreateNewPiece() {
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition (mPiece, mRotation);

    mNextPiece = getRand(0, 6);
    mNextRotation = 0;
}

void Game::DrawPiece(int nextX, int nextY, int pPiece, int pRotation) {
    color mColor;

    int mPixelsX = mBoard->GetXPosInPixels (nextX);
    int mPixelsY = mBoard->GetYPosInPixels (nextY);

    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            switch (mPieces->GetBlockType (pPiece, pRotation, j, i))
            {
                case 1: mColor = GREEN; break;
                case 2: mColor = BLUE; break;
            }
            if (mPieces->GetBlockType (pPiece, pRotation, j, i) != 0)
                mIO->DrawRectangle (mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE, (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mColor);
        }
    }
}

void Game::DrawBoard() {
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
    mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE); 
    mX1 += 1;

    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (!mBoard->IsFreeBlock(i, j)) {
                mIO->DrawRectangle ( mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE, (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
            }
        }
    }
}

void Game::DrawScene() {
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}



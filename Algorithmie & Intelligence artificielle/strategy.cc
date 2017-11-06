#include "strategy.h"

#ifdef _OPENMP
   #include <pthread.h>
   #include <omp.h>
#else
   #define omp_get_thread_num() 0
   #define omp_get_num_threads() 0
#endif

void Strategy::applyMove(const move& mv) {
    // Check blob's moves
    // Check if the blob is moved near its current position
    if (((mv.ox - mv.nx)*(mv.ox - mv.nx) <= 1) && 
        ((mv.oy - mv.ny)*(mv.oy - mv.ny) <= 1)) {
        // Duplicate it
        _blobs.set(mv.nx, mv.ny, (int) _current_player);
    } else {
        // Move it and set its origin to "unoccupied"
        _blobs.set(mv.ox, mv.oy, -1);
        _blobs.set(mv.nx, mv.ny, (int) _current_player);
    }

    // If there are some other player's blobs around, make them ours!!
    for (Sint8 i = -1 ; i < 2 ; i++)
        for (Sint8 j = -1 ; j < 2 ; j++) {
            if (mv.nx+i < 0) continue;
            if (mv.nx+i > 7) continue;
            if (mv.ny+j < 0) continue;
            if (mv.ny+j > 7) continue;
            if ((_blobs.get(mv.nx+i, mv.ny+j) != -1) &&
                (_blobs.get(mv.nx+i, mv.ny+j) != (int) _current_player)) {
                _blobs.set(mv.nx+i, mv.ny+j, (int) _current_player);
            }
        }
}

Sint32 Strategy::estimateCurrentScore(int player) const {
    Sint32 score = 0;

    // Find blobs on the board...
    for (int x = 0; x < 8; ++x)
        for (int y = 0; y < 8; ++y)
            if (!_holes.get(x, y)) // Check if the position is not a hole
                if (_blobs.get(x, y) != -1) { // Check if the position has a blob on it
                    if (_blobs.get(x, y) == player) // Is the blob one of the current player's ?
                        score++;
                    else
                        score--;
                }

    return score;    
}

vector<move>& Strategy::computeValidMoves(vector<move>& valid_moves) const {
    move mv(0,0,0,0);

    // for all blobs on the board belonging to the current player...
    for(mv.ox = 0 ; mv.ox < 8 ; mv.ox++) {
        for(mv.oy = 0 ; mv.oy < 8 ; mv.oy++) {
            if (_blobs.get(mv.ox, mv.oy) == (int) _current_player) {
                // iterate on possible destinations
                for(mv.nx = std::max(0,mv.ox-2) ; mv.nx <= std::min(7,mv.ox+2) ; mv.nx++)
                    for(mv.ny = std::max(0,mv.oy-2) ; mv.ny <= std::min(7,mv.oy+2) ; mv.ny++)
                        if (!_holes.get(mv.nx, mv.ny) && _blobs.get(mv.nx, mv.ny) == -1) {
                            valid_moves.push_back(mv);
                        }
            }
        }
    }
    return valid_moves;    
}

move& Strategy::findMoveGreedy(move& mv) {

    #ifdef DEBUG
        cout << "### GREEDY" << endl;
    #endif

    Sint32 best_score = -64;    // In this case, it's the same as -infinity
    vector<move> valid_moves;

    computeValidMoves(valid_moves);

    for (Uint32 i = 0; i < valid_moves.size(); ++i) {
        // For each valid move, create a new Strategy and apply the move, and then estimate the score
        Strategy St(*this);
        move move(valid_moves[i]);        
        St.applyMove(move);
        Sint32 score = St.estimateCurrentScore(_current_player);

        #ifdef DEBUG
            cout << "move : " << (Uint32) valid_moves[i].ox << "," << (Uint32) valid_moves[i].oy;
            cout << " to : " << (Uint32) valid_moves[i].nx << "," << (Uint32) valid_moves[i].ny;
            cout << " --> score : " << score << endl;
        #endif

        // We save the move with the best estimated score
        if (score > best_score) {
            best_score = score;
            mv = move;
        }
    }
    return mv;
}


move& Strategy::findMoveMinMax(move& mv, int profondeur) {

    #ifdef DEBUG
        cout << "### MIN MAX" << endl;
    #endif

    int currentDepth = 0;
    vector<move> valid_moves;

    computeValidMoves(valid_moves);
    _saveBestMove(valid_moves[0]);  // Guaranty that our AI won't be killed if timed out!

    
    vector<Sint32> scores;
    Sint32 maxScore = -64;

    for (Uint32 i = 0; i < valid_moves.size(); ++i) {
        // For each valid move, create a new Strategy and apply the move to the current player
        Strategy St(*this);
        St.applyMove(valid_moves[i]);
        // Change the current player to simulate the ennemy moves
        St._current_player = ((int)_current_player + 1)%2;
        // Call the recursive function
        scores.push_back(St.findMoveMinMaxRec(currentDepth+1, profondeur, (int) _current_player));

        #ifdef DEBUG
            cout << "move : " << (Uint32) valid_moves[i].ox << "," << (Uint32) valid_moves[i].oy;
            cout << " to : " << (Uint32) valid_moves[i].nx << "," << (Uint32) valid_moves[i].ny;
            cout << " --> score : " << scores[i] << endl;
        #endif

        // We save the MAX of the estimated scores
        if (scores[i] > maxScore) {
            mv = valid_moves[i];
            _saveBestMove(mv);
            maxScore = scores[i];
        }
    }
    return mv;
}

Sint32 Strategy::findMoveMinMaxRec(int currentDepth, int maxDepth, int player) {
    Sint32 maxScore = -64;  // Equals -infinity
    Sint32 minScore = 64;   // Equals +infinity
    vector<move> valid_moves;
    Sint32 score = 0;

    computeValidMoves(valid_moves);

    if (currentDepth < maxDepth) {
        
        // If the currentDepth is odd --> MIN node
        if (currentDepth % 2 == 1) {
            // MIN node
            // If there is no valid moves, we return the score of the current board
            if (valid_moves.size() == 0)
                return estimateCurrentScore(player);
            for (Uint32 i = 0; i < valid_moves.size(); ++i) {
                Strategy St(*this);
                St.applyMove(valid_moves[i]);
                St._current_player = ((int)_current_player + 1)%2;
                score = St.findMoveMinMaxRec(currentDepth+1, maxDepth, player);
                
                if (score < minScore)
                    minScore = score;
            }
            return minScore;
        // Else, the currentDepth is even --> MAX node
        } else {
            // MAX node
            if (valid_moves.size() == 0)
                return estimateCurrentScore(player);
            for (Uint32 i = 0; i < valid_moves.size(); ++i) {
                Strategy St(*this);
                St.applyMove(valid_moves[i]);
                St._current_player = ((int)_current_player + 1)%2;
                score = St.findMoveMinMaxRec(currentDepth+1, maxDepth, player);

                if (score > maxScore)
                    maxScore = score;
            }
            return maxScore;
        }
    // If the currentDepth equals the maxDepth --> bottom of the tree
    } else if (currentDepth == maxDepth) {

        if (currentDepth % 2 == 1) {
            // MIN node
            if (valid_moves.size() == 0)
                return estimateCurrentScore(player);
            for (Uint32 i = 0; i < valid_moves.size(); ++i) {
                Strategy St(*this);
                St.applyMove(valid_moves[i]);
                score = St.estimateCurrentScore(player);

                if (score < minScore)
                    minScore = score;
            }
            return minScore;
        } else {
            // MAX node
            if (valid_moves.size() == 0)
                return estimateCurrentScore(player);
            for (Uint32 i = 0; i < valid_moves.size(); ++i) {
                Strategy St(*this);
                St.applyMove(valid_moves[i]);
                score = St.estimateCurrentScore(player);

                if (score > maxScore)
                    maxScore = score;
            }
            return maxScore;
        }
    }
    return 0;
}



void Strategy::computeBestMove() {
    move best_move(0,0,0,0);

    // Greedy
    // if ((int)_current_player == 0)
    //     findMoveGreedy(best_move);

    // Min Max
    // if ((int)_current_player == 1)
    //     findMoveMinMax(best_move, 3);

    // players_names[0] = "red";
    // players_names[1] = "blue";

    findMoveMinMax(best_move, 3);

    _saveBestMove(best_move);
}


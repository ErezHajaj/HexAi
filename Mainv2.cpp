#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

#include "Position.cpp"


using namespace std;



const int MAX = 100000;
const int MIN = -100000;



bool in_red_values(int i, Position& p) {
  if (i < 0 || i > p.size*p.size) return true;
  return p.red_tiles[i];
}

bool in_blue_values(int i, Position& p) {
  if (i < 0 || i > p.size*p.size) return false;
  return p.blue_tiles[i];
}

int evaluate_position1(Position& p, unordered_map< Position, pair <int, int>, PositionHasher >& evaluated_positions) {
  if (evaluated_positions.find(p) != evaluated_positions.end()) {
    return evaluated_positions.at(p).second;
  } else {
    //Evaluate position
    int points = 0;
    for (int i = 0; i < p.size*p.size; ++i) {
      if (p.red_tiles[i]) {
        bool case1 = (i < p.size || in_red_values(i - p.size, p) || ((i + 1)%p.size != 0 && in_red_values(i - p.size + 1, p)));
        bool case2 = (p.size*(p.size - 1) <= i || in_red_values(i + p.size, p) || (i%p.size != 0 && in_red_values(i + p.size - 1, p)));
        if (case1) {
          ++points;
        }
        if (case2) {
          ++points;
        }

      } else if (p.blue_tiles[i]) {
        if (i%p.size == 0 || in_blue_values(i - 1, p) || in_blue_values(i + p.size - 1, p)) --points;
        if ((i+1)%p.size == 0 || in_blue_values(i + 1, p) || in_blue_values(i - p.size + 1, p)) --points;
      }
    }

    evaluated_positions.insert(make_pair(p, make_pair(0, points)));
    return points;
  }
}


int evaluate_position2(Position& p, unordered_map< Position, pair <int, int>, PositionHasher >& evaluated_positions) {
  if (evaluated_positions.find(p) != evaluated_positions.end()) {
    return evaluated_positions.at(p).second;
  } else {
    //Evaluate position
    int points = 0;
    for (int i = 0; i < p.size*p.size; ++i) {
      if (p.red_tiles[i]) {
        bool case1 = (i < p.size || in_red_values(i - p.size, p) || ((i + 1)%p.size != 0 && in_red_values(i - p.size + 1, p)));
        bool case2 = (p.size*(p.size - 1) <= i || in_red_values(i + p.size, p) || (i%p.size != 0 && in_red_values(i + p.size - 1, p)));

        bool case3 = ( i%p.size != 0 && in_red_values(i - 1, p));
        bool case4 = ((i + 1)%p.size != 0 && in_red_values(i + 1, p));
        if (case1) {
          ++points;
        }
        if (case2) {
          ++points;
        }
        if (case1 && case2) {
          points += 3;
        }

        if (case3) {
          points -= 0.5;
        }
        if (case4) {
          points -= 0.5;
        }
        if (case3 && case4) {
          points -= 0.5;
        }

      } else if (p.blue_tiles[i]) {
        bool case1 = (i%p.size == 0 || in_blue_values(i - 1, p) || in_blue_values(i + p.size - 1, p));
        bool case2 = ((i+1)%p.size == 0 || in_blue_values(i + 1, p) || in_blue_values(i - p.size + 1, p));

        bool case3 = in_blue_values(i - p.size, p);
        bool case4 = in_blue_values(i + p.size, p);
        if (case1) --points;
        if (case2) --points;
        if (case1 && case2) points -= 3;
        if (case3) points += 0.5;
        if (case4) points += 0.5;
        if (case3 && case4) points += 0.5;
      }
    }

    evaluated_positions.insert(make_pair(p, make_pair(0, points)));
    return points;
  }
}



bool compareMax(Eval_Move* a, Eval_Move* b) {
    return (*b < *a);
}
bool compareMin(Eval_Move* a, Eval_Move* b) {
    return (*a < *b);
}

Eval_Move* minimax(int depth, int target_depth, bool maximizingPlayer, Position& p, int alpha,  int beta, unordered_map< Position, pair <int, int>, PositionHasher >& evaluated_positions) {
  if (p.num_empty == 0) {
    return new Eval_Move(0, evaluate_position2(p, evaluated_positions));
  }
  //cout << "A" << endl;
	Eval_Move* candidate_moves[p.num_empty];
	p.get_moves(candidate_moves);
	//cout << "B" << endl;
	for (int i = 0; i < p.num_empty; ++i) {
		p.do_move(candidate_moves[i]->pos, maximizingPlayer);
		candidate_moves[i]->evaluation = evaluate_position2(p, evaluated_positions);
		p.undo_move(candidate_moves[i]->pos, maximizingPlayer);
	}
	//cout << "C" << endl;
	if (maximizingPlayer) {
			sort(candidate_moves, candidate_moves + p.num_empty, compareMax);
	} else {
			sort(candidate_moves, candidate_moves + p.num_empty, compareMin);
	}

	//cout << "D" << endl;
	//for(int i = 0; i < p.num_empty; ++i) {
	//		cout << candidate_moves[i]->pos << " " << candidate_moves[i]->evaluation << endl;
	//}
	if (depth == target_depth) {
		//cout << "D1" << endl;
		//cout << "Maximizing: " << maximizingPlayer << " depth: " << depth << endl;
		//cout <<  candidate_moves[0]->pos << " " << candidate_moves[0]->evaluation << endl;
		return candidate_moves[0];
	}
	//cout << "E" << endl;
	if (maximizingPlayer) {
		int best = MIN;

		int best_pos = 0;;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0]->pos;
    }
		// Recur for left and
		// right children
		//cout << "E1" << endl;
		for (int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i]->pos, maximizingPlayer);
			Eval_Move* opponent_eval_move = minimax(depth + 1, target_depth, false, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i]->pos, maximizingPlayer);
			if (opponent_eval_move->evaluation > best) {
				best = opponent_eval_move->evaluation;
				best_pos = candidate_moves[i]->pos;
			}
			alpha = max(alpha, best);
      delete candidate_moves[i];
      delete opponent_eval_move;
			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
    //TO DO: Add to evaluated positions
		return new Eval_Move(best_pos, best);
	} else {
		//cout << "E2" << endl;
		int best = MAX;
    int best_pos = 0;;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0]->pos;
    }

		// Recur for left and
		// right children
		for (int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i]->pos, maximizingPlayer);
			Eval_Move* opponent_eval_move = minimax(depth + 1, target_depth, true, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i]->pos, maximizingPlayer);
			if (opponent_eval_move->evaluation < best) {
				best = opponent_eval_move->evaluation;
				best_pos = candidate_moves[i]->pos;
			}
			beta = min(alpha, best);
      delete candidate_moves[i];
      delete opponent_eval_move;
			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}

		return new Eval_Move(best_pos, best);

	}

}






// Driver Code
int main(int argc, char *argv[])  {
  string ai_color = "RED";
  int board_size = 7;
  bool debug = false;

  int c ;
  while( ( c = getopt (argc, argv, "p:s:d") ) != -1 ) {
      switch(c) {
          case 'p':
              if(optarg) ai_color = optarg;
              break;
          case 's':
              if(optarg) board_size = std::atoi(optarg) ;
              break;
          case 'd':
            debug = true;
            break;
      }
  }

bool ai_red = true;
if (ai_color == "BLUE") {
  ai_red = false;
}

Position p(board_size, ai_red);


unordered_map< Position, pair <int, int>, PositionHasher > evaluated_positions;


Eval_Move* val;
auto t1 = chrono::high_resolution_clock::now();
auto t2 = chrono::high_resolution_clock::now();
if (ai_red) {
    int i = 1;
    while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 400 && i < 10) {
      t1 = chrono::high_resolution_clock::now();
      delete val;
      val = minimax(0, i, false, p, MIN, MAX, evaluated_positions);
      t2 = chrono::high_resolution_clock::now();
      ++i;
    }
    cout << p.move_to_output(val->pos) << endl;
    if (debug) {
      cout << val->evaluation << endl;
    }
    p.do_move(val->pos, true);
}


while(p.num_empty > 0) {
  string player_move;
  cin >> player_move;
  //cout << "Played: " << player_move << " = " << p.input_to_move(player_move) << endl;
  p.do_move(p.input_to_move(player_move), !ai_red);
  int i = 1;
  t1 = chrono::high_resolution_clock::now();
  t2 = chrono::high_resolution_clock::now();
  while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 400 && i < 10) {
    t1 = chrono::high_resolution_clock::now();
    delete val;
    val = minimax(0, i, !ai_red, p, MIN, MAX, evaluated_positions);
    t2 = chrono::high_resolution_clock::now();
    chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    ++i;
  }
  //cout <<  val->pos << " " << p.move_to_output(val->pos) << " " << val->evaluation << endl;
  cout << p.move_to_output(val->pos) << endl;
  if (debug) {
    cout << val->evaluation << endl;
  }
  p.do_move(val->pos, ai_red);
}




}

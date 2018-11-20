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

//quque
//remove from queue. add to end to queue.
//look for neighbors if not added
//if 0 add to front of queue if 1 add to end of queue
//check if ad

bool in_red_values(int i, const Position& p) { //improve
  return (i < 0 || i > p.size*p.size || p.red_tiles[i]);
}

bool in_blue_values(int i, const Position& p) { //improve
  return ((0 <= i && i <= p.size*p.size) && p.blue_tiles[i]);
}

int evaluate_position(const Position& p, unordered_map< Position, int, PositionHasher >& evaluated_positions) {
  const auto& iter = evaluated_positions.find(p);
  if (iter != evaluated_positions.end()) {
      return iter->second;
  } else {
    //Evaluate position
    float points = 0;
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

    evaluated_positions.insert(make_pair(p, points));
    return points;
  }
}


Eval_Move minimax(int depth, int target_depth, bool maximizingPlayer, Position& p, int alpha, int beta, unordered_map< Position, int, PositionHasher >& evaluated_positions) {
  if (p.num_empty == 0) {
    return Eval_Move(0, evaluate_position(p, evaluated_positions));
  }
	vector<Eval_Move> candidate_moves(p.num_empty);
  p.get_moves(candidate_moves);;
	for (int i = 0; i < p.num_empty; ++i) {
		p.do_move(candidate_moves[i].pos, maximizingPlayer);
		candidate_moves[i].evaluation = evaluate_position(p, evaluated_positions);
		p.undo_move(candidate_moves[i].pos, maximizingPlayer);
	}
	if (maximizingPlayer) {
			sort(candidate_moves.begin(), candidate_moves.end(), greater<Eval_Move>());
	} else {
			sort(candidate_moves.begin(), candidate_moves.end());
	}

	if (depth == target_depth) {
		return candidate_moves[0];
	}
	if (maximizingPlayer) {
		int best = MIN;

		int best_pos = 0;;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }

		for (int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i].pos, maximizingPlayer);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, false, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i].pos, maximizingPlayer);
			if (opponent_eval_move.evaluation > best) {
				best = opponent_eval_move.evaluation;
				best_pos = candidate_moves[i].pos;
			}
			alpha = max(alpha, best);
			if (beta <= alpha)
				break;
		}
    //TO DO: Add to evaluated positions
		return Eval_Move(best_pos, best);
	} else {
		//cout << "E2" << endl;
		int best = MAX;
    int best_pos = 0;;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }

		// Recur for left and
		// right children
		for (int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i].pos, maximizingPlayer);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, true, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i].pos, maximizingPlayer);
			if (opponent_eval_move.evaluation < best) {
				best = opponent_eval_move.evaluation;
				best_pos = candidate_moves[i].pos;
			}
			beta = min(alpha, best);
			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return Eval_Move(best_pos, best);

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

Position p(board_size);


unordered_map< Position, int, PositionHasher > evaluated_positions;


Eval_Move val;
auto t1 = chrono::high_resolution_clock::now();
auto t2 = chrono::high_resolution_clock::now();
if (ai_red) {
    int i = 1;
    while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 400 && i < 10) {
      t1 = chrono::high_resolution_clock::now();
      val = minimax(0, i, false, p, MIN, MAX, evaluated_positions);
      t2 = chrono::high_resolution_clock::now();
      ++i;
    }
    cout << p.move_to_output(val.pos) << endl;
    if (debug) {
    cout << val.evaluation << " Depth: " << i << endl;
    }
    p.do_move(val.pos, true);
}


while(p.num_empty > 0) {
  string player_move;
  cin >> player_move;
  //cout << "Played: " << player_move << " = " << p.input_to_move(player_move) << endl;
  p.do_move(p.input_to_move(player_move), !ai_red);
  int i = 1;
  t1 = chrono::high_resolution_clock::now();
  t2 = chrono::high_resolution_clock::now();
  while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 500 && i < 10) {
    t1 = chrono::high_resolution_clock::now();
    val = minimax(0, i, !ai_red, p, MIN, MAX, evaluated_positions);
    t2 = chrono::high_resolution_clock::now();
    chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    ++i;
  }
  //cout <<  val.pos << " " << p.move_to_output(val.pos) << " " << val.evaluation << endl;
  cout << p.move_to_output(val.pos) << endl;
  if (debug) {
    cout << val.evaluation << " Depth: " << i << endl;
  }
  p.do_move(val.pos, ai_red);
}




}

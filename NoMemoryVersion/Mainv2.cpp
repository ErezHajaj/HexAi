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
#include <deque>
#include <chrono>
#include <bitset>
#include "Position.cpp"


using namespace std;



const int MAX = 100;
const int MIN = -100;

const bool DEBUG = false;

bool in_first_col(int i, const Position&p) {
  return (i < p.size);
}

bool in_first_2_col(int i, const Position&p) {
  return (i < 2*p.size);
}

bool in_last_col(int i, const Position&p) {
  return (p.size*(p.size - 1) <= i);
}

bool in_last_2_col(int i, const Position&p) {
  return ((p.size*(p.size - 2)) <= i);
}


bool in_first_row(int i, const Position&p) {
  return !(i%p.size);
}

bool in_first_2_row(int i, const Position&p) {
  short int a = i%p.size;
  return (a <= 1);
}

bool in_last_row(int i, const Position&p) {
  return !((i+1)%p.size);
}

bool in_last_2_row(int i, const Position&p) {
  short int a = ((i+2)%p.size);
  return (a <= 1);
}


short int evaluate_shortestpath(const Position& p) {

  short int red_shortest_path = MAX;
  short int blue_shortest_path = MAX;
  unordered_set<short int> reached;
  deque < pair<short int, short int> > to_check;


  for (short int i = 0; i < p.size; ++i) {
    if (p.red_tiles[i]) {
      reached.insert(i);
      to_check.push_front( make_pair(i, 0) );
    } else if (!p.blue_tiles[i]) {
      reached.insert(i);
      to_check.push_back( make_pair(i, 1) );
    }
  }
  //if (DEBUG) cout << "eval shortest path3 " << points << endl;
  while(!to_check.empty()) {
    pair<short int, short int> c = to_check.front();
    //if (DEBUG) cout << c.first << " " << c.second << endl;
    to_check.pop_front();
    //if (DEBUG) cout << "eval shortest path31 " << c.second << endl;
    if (in_last_col(c.first, p)) {
      red_shortest_path = c.second;
      break;
    }
    //if (DEBUG) cout << "eval shortest path32 " << c.second << endl;
    bitset<6> dirs(0b111111);
    if (in_first_col(c.first, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_first_2_col(c.first, p)) {
      dirs &= bitset<6>(0b001111);
    }
    //if (DEBUG) cout << "eval shortest path33 " << c.second << endl;
    if(in_first_row(c.first, p)) {
      dirs &= bitset<6>(0b001100);
    } else if (in_first_2_row(c.first, p)) {
      dirs &= bitset<6>(0b011110);
    } else if (in_last_row(c.first, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_last_2_row(c.first, p)) {
      dirs &= bitset<6>(0b001111);
    }
    //if (DEBUG) cout << "eval shortest path34 " << c.second << endl;

    if (dirs[0]) {
      int i = c.first - 1;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
    //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
    if (dirs[1]) {
      short int i = c.first + p.size -1;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
    if (dirs[2]) {
      short int i = c.first + p.size;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
    if (dirs[3]) {
      short int i = c.first + 1;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
    if (dirs[4]) {
      short int i = c.first - p.size + 1;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
      //if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
    if (dirs[5]) { //always true
      short int i = c.first - p.size;
      if (!p.blue_tiles[i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.red_tiles[i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    } //always true
    //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
  }
///BLUE

reached.clear();
to_check.clear();
short int coord = 0;
for (short int i = 0; i < p.size; ++i) {
  if (p.blue_tiles[coord]) {
    reached.insert(coord);
    to_check.push_front( make_pair(coord, 0) );
  } else if (!p.red_tiles[coord]) {
    reached.insert(coord);
    to_check.push_back( make_pair(coord, 1) );
  }
  coord += p.size;
}
//if (DEBUG) cout << "eval shortest path3 " << points << endl;
while(!to_check.empty()) {
  pair<short int, short int> c = to_check.front();
  //if (DEBUG) cout << c.first << " " << c.second << endl;
  to_check.pop_front();
  //if (DEBUG) cout << "eval shortest path31 " << c.second << endl;
  if (in_last_row(c.first, p)) {
    blue_shortest_path = c.second;
    //cout << c.first << " " << points << endl;
    break;
  }
  //if (DEBUG) cout << "eval shortest path32 " << c.second << endl;
  bitset<6> dirs(0b111111);
  if (in_first_row(c.first, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_first_2_row(c.first, p)) {
    dirs &= bitset<6>(0b111100);
  }
  //if (DEBUG) cout << "eval shortest path33 " << c.second << endl;
  if(in_first_col(c.first, p)) {
    dirs &= bitset<6>(0b001100);
  } else if (in_first_2_col(c.first, p)) {
    dirs &= bitset<6>(0b011110);
  } else if (in_last_col(c.first, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_last_2_col(c.first, p)) {
    dirs &= bitset<6>(0b111100);
  }
  //if (DEBUG) cout << "eval shortest path34 " << c.second << endl;

  if (dirs[0]) {
    int i = c.first - 1;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
  //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
  if (dirs[1]) {
    short int i = c.first + p.size -1;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
  if (dirs[2]) {
    short int i = c.first + p.size;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
  if (dirs[3]) {
    short int i = c.first + 1;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
  if (dirs[4]) {
    short int i = c.first - p.size + 1;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
    //if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
  if (dirs[5]) { //always true
    short int i = c.first - p.size;
    if (!p.red_tiles[i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.blue_tiles[i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  } //always true
  //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
}



//target_depth - depth
//
//if (DEBUG) cout << "eval shortest path4" << points << endl;
int points = blue_shortest_path - red_shortest_path;
return points;
}




Eval_Move minimax(short int depth, short int target_depth, bool maximizingPlayer, Position& p, short int alpha, short int beta) {
  if (p.num_empty == 0) {
    return Eval_Move(0, evaluate_shortestpath(p));
  }
	vector<Eval_Move> candidate_moves(p.num_empty);
  p.get_moves(candidate_moves);
	for (short int i = 0; i < p.num_empty; ++i) { //possibly better for loop
		p.do_move(candidate_moves[i].pos, maximizingPlayer);
		candidate_moves[i].evaluation = evaluate_shortestpath(p);
		p.undo_move(candidate_moves[i].pos);
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
		short int best = MIN;

		short int best_pos = 0;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }

		for (short int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i].pos, maximizingPlayer);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, false, p, alpha, beta);
			p.undo_move(candidate_moves[i].pos);
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
		short int best = MAX;
    short int best_pos = -1;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }


		for (short int i = 0; i < p.num_empty; ++i) {
			p.do_move(candidate_moves[i].pos, maximizingPlayer);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, true, p, alpha, beta);
			p.undo_move(candidate_moves[i].pos);
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
  short int board_size = 7;
  short int max_depth = 12;

  int c ;
  while( ( c = getopt (argc, argv, "p:s:") ) != -1 ) {
      switch(c) {
          case 'p':
              if(optarg) ai_color = optarg;
              break;
          case 's':
              if(optarg) board_size = std::atoi(optarg) ;
              break;
      }
  }

bool ai_red = true;
if (ai_color == "BLUE") {
  ai_red = false;
}

if (board_size >= 7) {
  max_depth = 7;
} else if(board_size >= 9) {
  max_depth = 6;
} else if(board_size >= 11) {
  max_depth = 5;
} else if(board_size >= 13) {
  max_depth = 4;
}

Position p(board_size);

Eval_Move val;




auto t1 = chrono::high_resolution_clock::now();
auto t2 = chrono::high_resolution_clock::now();
if (ai_red) {
    int i = 1;
    while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 200 && i < max_depth) {
      t1 = chrono::high_resolution_clock::now();
      val = minimax(0, i, false, p, MIN, MAX);
      t2 = chrono::high_resolution_clock::now();
      ++i;
    }
    cout << p.move_to_output(val.pos) << endl;
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
  while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 200 && i < max_depth) {
    t1 = chrono::high_resolution_clock::now();
    val = minimax(0, i, !ai_red, p, MIN, MAX);
    t2 = chrono::high_resolution_clock::now();
    chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    ++i;
  }
  //cout <<  val.pos << " " << p.move_to_output(val.pos) << " " << val.evaluation << endl;
  cout << p.move_to_output(val.pos) << endl;
  p.do_move(val.pos, ai_red);

}

}

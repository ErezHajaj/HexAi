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

const unordered_set<Neighbor_State, NeighborHasher> pruned_neighbor_states( {Neighbor_State(bitset<6>(0b111000), bitset<6>(0b000010)), Neighbor_State(bitset<6>(0b011100), bitset<6>(0b000001)), Neighbor_State(bitset<6>(0b001110), bitset<6>(0b100000)),
Neighbor_State(bitset<6>(0b000111), bitset<6>(0b010000)), Neighbor_State(bitset<6>(0b100011), bitset<6>(0b001000)), Neighbor_State(bitset<6>(0b110001), bitset<6>(0b000100)),
Neighbor_State(bitset<6>(0b111000), bitset<6>(0b000110)), Neighbor_State(bitset<6>(0b011100), bitset<6>(0b000011)), Neighbor_State(bitset<6>(0b001110), bitset<6>(0b100001)),
Neighbor_State(bitset<6>(0b000111), bitset<6>(0b110000)), Neighbor_State(bitset<6>(0b100011), bitset<6>(0b011000)), Neighbor_State(bitset<6>(0b110001), bitset<6>(0b001100)),
Neighbor_State(bitset<6>(0b111000), bitset<6>(0b000011)), Neighbor_State(bitset<6>(0b011100), bitset<6>(0b100001)), Neighbor_State(bitset<6>(0b001110), bitset<6>(0b110000)),
Neighbor_State(bitset<6>(0b000111), bitset<6>(0b011000)), Neighbor_State(bitset<6>(0b100011), bitset<6>(0b001100)), Neighbor_State(bitset<6>(0b110001), bitset<6>(0b000110)),
Neighbor_State(bitset<6>(0b111000), bitset<6>(0b000111)), Neighbor_State(bitset<6>(0b011100), bitset<6>(0b100011)), Neighbor_State(bitset<6>(0b001110), bitset<6>(0b110001)),
Neighbor_State(bitset<6>(0b000111), bitset<6>(0b111000)), Neighbor_State(bitset<6>(0b100011), bitset<6>(0b011100)), Neighbor_State(bitset<6>(0b110001), bitset<6>(0b001110)),

Neighbor_State(bitset<6>(0b110000), bitset<6>(0b000110)), Neighbor_State(bitset<6>(0b011000), bitset<6>(0b000011)), Neighbor_State(bitset<6>(0b001100), bitset<6>(0b100001)),
Neighbor_State(bitset<6>(0b000110), bitset<6>(0b110000)), Neighbor_State(bitset<6>(0b000011), bitset<6>(0b011000)), Neighbor_State(bitset<6>(0b100001), bitset<6>(0b001100))
});
const unordered_set<bitset<6>> pruned_single_color( {bitset<6>(0b111100), bitset<6>(0b011110), bitset<6>(0b001111), bitset<6>(0b100111), bitset<6>(0b110011),bitset<6>(0b111001),
                                              bitset<6>(0b111110), bitset<6>(0b011111), bitset<6>(0b101111), bitset<6>(0b110111), bitset<6>(0b111011),bitset<6>(0b111101), bitset<6>(0b111111)});


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
    if (p.tiles[0][i]) {
      reached.insert(i);
      to_check.push_front( make_pair(i, 0) );
    } else if (!p.tiles[1][i]) {
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
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
    //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
    if (dirs[1]) {
      short int i = c.first + p.size -1;
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
    if (dirs[2]) {
      short int i = c.first + p.size;
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
    if (dirs[3]) {
      short int i = c.first + 1;
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
        //if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
    if (dirs[4]) {
      short int i = c.first - p.size + 1;
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
        }
      }
    }
      //if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
    if (dirs[5]) { //always true
      short int i = c.first - p.size;
      if (!p.tiles[1][i] && reached.find(i) == reached.end()) {
        reached.insert(i);
        if (p.tiles[0][i]) {
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
  if (p.tiles[1][coord]) {
    reached.insert(coord);
    to_check.push_front( make_pair(coord, 0) );
  } else if (!p.tiles[0][coord]) {
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
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
  //if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
  if (dirs[1]) {
    short int i = c.first + p.size -1;
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
  if (dirs[2]) {
    short int i = c.first + p.size;
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
  if (dirs[3]) {
    short int i = c.first + 1;
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
      //if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
  if (dirs[4]) {
    short int i = c.first - p.size + 1;
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
      }
    }
  }
    //if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
  if (dirs[5]) { //always true
    short int i = c.first - p.size;
    if (!p.tiles[0][i] && reached.find(i) == reached.end()) {
      reached.insert(i);
      if (p.tiles[1][i]) {
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

bitset<6> getNeighbors(bool is_red, int pos, const Position& p) {
  bitset<6> neighbors = bitset<6>();
  bool first_row = in_first_row(pos, p);
  bool first_col = in_first_col(pos, p);
  bool last_row = in_last_row(pos, p);
  bool last_col = in_last_row(pos, p);

  int max_size = p.size*p.size - 1;
  neighbors[0] = p.tiles[!is_red][max(0, pos - 1)];
  neighbors[1] = p.tiles[!is_red][min(max_size, pos + p.size - 1)];
  neighbors[2] = p.tiles[!is_red][min(max_size, pos + p.size)];
  neighbors[3] = p.tiles[!is_red][min(max_size, pos + 1)];
  neighbors[4] = p.tiles[!is_red][max(0, pos - p.size + 1)];
  neighbors[5] = p.tiles[!is_red][max(0, pos - p.size)];

  if(first_row) {
    neighbors[0] = !is_red;
    neighbors[1] = !is_red;
  } else if(last_row) {
    neighbors[3] = !is_red;
    neighbors[4] = !is_red;
  }
  if(first_col) {
    neighbors[4] = is_red;
    neighbors[5] = is_red;
  } else if(last_col) {
    neighbors[1] = is_red;
    neighbors[2] = is_red;
  }
}



bool in_pruned_states(int pos, const Position& p) {
    bitset<6> red_state = getNeighbors(true, pos, p);
    bitset<6> blue_state = getNeighbors(false, pos, p);
    Neighbor_State ns(red_state, blue_state);

    //For Now, replace with unordered_set
    return ( pruned_single_color.find(red_state) != pruned_single_color.end() || pruned_single_color.find(blue_state) != pruned_single_color.end() || pruned_neighbor_states.find(ns) != pruned_neighbor_states.end());
}


Eval_Move minimax(short int depth, short int target_depth, bool maximizingPlayer, Position& p, short int alpha, short int beta) {
  if (p.num_empty == 0) {
    return Eval_Move(0, evaluate_shortestpath(p));
  }
	vector<Eval_Move> candidate_moves(p.num_empty);
  p.get_moves(candidate_moves);
	for (short int i = 0; i < p.num_empty; ++i) { //possibly better for loop
    if (in_pruned_states(candidate_moves[i].pos, p)) {
      candidate_moves[i].evaluation = (2*maximizingPlayer - 1)*MIN;
    } else {
      p.do_move(candidate_moves[i].pos, maximizingPlayer);
      candidate_moves[i].evaluation = evaluate_shortestpath(p);
      p.undo_move(candidate_moves[i].pos);
    }

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
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        continue;
      }
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
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        continue;
      }
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
    // int i = 1;
    // while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 230 && i < max_depth) {
    //   t1 = chrono::high_resolution_clock::now();
    //   val = minimax(0, i, false, p, MIN, MAX);
    //   t2 = chrono::high_resolution_clock::now();
    //   ++i;
    // }
    // cout << p.move_to_output(val.pos) << endl;
    // if (debug) {
    //   cout << val.evaluation << " Depth: " << i << endl;
    // }
    // p.do_move(val.pos, true);
    int move = p.size*p.size/2; //For some reason doesn't help
    cout << p.move_to_output(move) << endl;
    p.do_move(move, true);
}


while(p.num_empty > 0) {
  string player_move;
  cin >> player_move;
  //cout << "Played: " << player_move << " = " << p.input_to_move(player_move) << endl;
  p.do_move(p.input_to_move(player_move), !ai_red);
  int i = 1;
  t1 = chrono::high_resolution_clock::now();
  t2 = chrono::high_resolution_clock::now();
  while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 230 && i < max_depth) {
    //cout << i << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
    t1 = chrono::high_resolution_clock::now();
    val = minimax(0, i, !ai_red, p, MIN, MAX);
    t2 = chrono::high_resolution_clock::now();
    chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    ++i;
  }
  //cout << i << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
  //cout <<  val.pos << " " << p.move_to_output(val.pos) << " " << val.evaluation << endl;
  cout << p.move_to_output(val.pos) << endl;
  // if (debug) {
  //   cout << val.evaluation << " Depth: " << i << endl;
  // }
  p.do_move(val.pos, ai_red);

}

}

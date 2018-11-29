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
#include <math.h>
#include <bitset>
#include <algorithm>
#include "Position.cpp"


using namespace std;



const int MAX = 100;
const int MIN = -100;

const bool DEBUG = true;

const float MULTI_PATH_WEIGHT = 0.5;

const unordered_set<Neighbor_State, NeighborHasher> pruned_dead( {Neighbor_State(bitset<6>(0b111000), bitset<6>(0b000010)), Neighbor_State(bitset<6>(0b011100), bitset<6>(0b000001)), Neighbor_State(bitset<6>(0b001110), bitset<6>(0b100000)),
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

const unordered_set<bitset<6>> pruned_single_color_dead( {bitset<6>(0b111100), bitset<6>(0b011110), bitset<6>(0b001111), bitset<6>(0b100111), bitset<6>(0b110011),bitset<6>(0b111001),
                                              bitset<6>(0b111110), bitset<6>(0b011111), bitset<6>(0b101111), bitset<6>(0b110111), bitset<6>(0b111011),bitset<6>(0b111101), bitset<6>(0b111111)});


const unordered_set<bitset<6>> pruned_single_color_vulnerable( {bitset<6>(0b111000), bitset<6>(0b011100), bitset<6>(0b001110), bitset<6>(0b000111), bitset<6>(0b100011),bitset<6>(0b110001)});

const unordered_set<Neighbor_State, NeighborHasher> pruned_vulnerable( {
Neighbor_State(bitset<6>(0b110000), bitset<6>(0b000100)), Neighbor_State(bitset<6>(0b110000), bitset<6>(0b000010)),
Neighbor_State(bitset<6>(0b100000), bitset<6>(0b001010)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b111000)),
Neighbor_State(bitset<6>(0b000100), bitset<6>(0b111000)), Neighbor_State(bitset<6>(0b000001), bitset<6>(0b111000)),
Neighbor_State(bitset<6>(0b000101), bitset<6>(0b111000)),

Neighbor_State(bitset<6>(0b011000), bitset<6>(0b000010)), Neighbor_State(bitset<6>(0b011000), bitset<6>(0b000001)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b000101)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b011100)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b011100)), Neighbor_State(bitset<6>(0b100000), bitset<6>(0b011100)),
Neighbor_State(bitset<6>(0b100010), bitset<6>(0b011100)),

Neighbor_State(bitset<6>(0b001100), bitset<6>(0b000001)), Neighbor_State(bitset<6>(0b001100), bitset<6>(0b100000)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b100010)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b001110)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b001110)), Neighbor_State(bitset<6>(0b010000), bitset<6>(0b001110)),
Neighbor_State(bitset<6>(0b010001), bitset<6>(0b001110)),

Neighbor_State(bitset<6>(0b000110), bitset<6>(0b100000)), Neighbor_State(bitset<6>(0b000110), bitset<6>(0b010000)),
Neighbor_State(bitset<6>(0b000100), bitset<6>(0b010001)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b000111)),
Neighbor_State(bitset<6>(0b100000), bitset<6>(0b000111)), Neighbor_State(bitset<6>(0b001000), bitset<6>(0b000111)),
Neighbor_State(bitset<6>(0b101000), bitset<6>(0b000111)),

Neighbor_State(bitset<6>(0b000011), bitset<6>(0b010000)), Neighbor_State(bitset<6>(0b000011), bitset<6>(0b001000)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b101000)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b100011)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b100011)), Neighbor_State(bitset<6>(0b000100), bitset<6>(0b100011)),
Neighbor_State(bitset<6>(0b010100), bitset<6>(0b100011)),

Neighbor_State(bitset<6>(0b100001), bitset<6>(0b001000)), Neighbor_State(bitset<6>(0b100001), bitset<6>(0b000100)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b010100)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b110001)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b110001)), Neighbor_State(bitset<6>(0b000010), bitset<6>(0b110001)),
Neighbor_State(bitset<6>(0b001010), bitset<6>(0b110001))

});

float sigmoidP(float x) {
    return 1 / (1 + exp(-x)) - 0.5;
}


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

//NUMBER OF SHORTEST PATHS ALGORITHM IS SLIGHTLY BROKEN. Since there are cost edges of 0. It propogates a number of shortest paths that undervalues central tiles.


float evaluate_shortestpath(const Position& p, unordered_map< Position, pair<short int, float>, PositionHasher >& evaluated_positions) {

  const auto& iter = evaluated_positions.find(p); //should be
  if (iter != evaluated_positions.end()) {
      return iter->second.second;

  }

  short int red_shortest_path = MAX;
  short int blue_shortest_path = MAX;
  int num_red_shortest_paths = 0;
  int num_blue_shortest_paths = 0;
  unordered_map<short int, pair<short int, short int> > reached; //Reached position, shortest path, number of paths
  deque < pair<short int, short int> > to_check;


  for (short int i = 0; i < p.size; ++i) {
    if (p.tiles[0][i]) {
      reached.insert(make_pair(i, make_pair(0, 1)));
      to_check.push_front( make_pair(i, 0) );
    } else if (!p.tiles[1][i]) {
      reached.insert(make_pair(i, make_pair(1, 1)));
      to_check.push_back( make_pair(i, 1) );
    }
  }
  // if (DEBUG) cout << "eval shortest path3 "  << endl;
  bool end_found_flag = false;
  vector<short int> shortest_nodes;

  while(!to_check.empty()) {
    pair<short int, short int> c = to_check.front();
    to_check.pop_front();
    if(end_found_flag && red_shortest_path != c.second) {
      for (short int s : shortest_nodes) {
        num_red_shortest_paths += reached.at(s).second;
      }
      break;
    }
    if (in_last_col(c.first, p)) {
      shortest_nodes.push_back(c.first);
      //num_red_shortest_paths += reached.at(c.first).second;
      if (!end_found_flag) {
        red_shortest_path = c.second;
        end_found_flag = true;
      }
    }
    // if (DEBUG) cout << "eval shortest path32 " << c.second << endl;
    bitset<6> dirs(0b111111);
    if (in_first_col(c.first, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_first_2_col(c.first, p)) {
      dirs &= bitset<6>(0b001111);
    }
    // if (DEBUG) cout << "eval shortest path33 " << c.second << endl;
    if(in_first_row(c.first, p)) {
      dirs &= bitset<6>(0b001100);
    } else if (in_first_2_row(c.first, p)) {
      dirs &= bitset<6>(0b011110);
    } else if (in_last_row(c.first, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_last_2_row(c.first, p)) {
      dirs &= bitset<6>(0b001111);
    }
    // if (DEBUG) cout << "eval shortest path34 " << c.second << endl;

    if (dirs[0]) {
      int i = c.first - 1;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
    // if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
    if (dirs[1]) {
      short int i = c.first + p.size -1;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
        // if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
    if (dirs[2]) {
      short int i = c.first + p.size;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
        // if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
    if (dirs[3]) {
      short int i = c.first + 1;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
        //// if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
    if (dirs[4]) {
      short int i = c.first - p.size + 1;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
      //// if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
    if (dirs[5]) { //always true
      short int i = c.first - p.size;
      const auto& iter = reached.find(i);
      const auto current = reached.at(c.first);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check.push_front( make_pair(i, c.second));
          reached.insert(make_pair(i, make_pair(c.second, current.second)));
        } else {
          to_check.push_back( make_pair(i, c.second + 1));
          reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
        }
      } else if (iter != reached.end() && !p.tiles[1][i]) {
        if (p.tiles[0][i]) {
          if (iter->second.first >= current.first) {
              iter->second.second += current.second;
          }
        } else if (iter->second.first > current.first) {
            iter->second.second += current.second;
        }
      }
    }
}
///BLUE

//cout << "Red Reached: " << endl;
// for (auto p : reached) {
//   cout << p.first << " : " << p.second.first << " "  << p.second.second << endl;
// }

reached.clear();
to_check.clear();
shortest_nodes.clear();
short int coord = 0;
for (short int i = 0; i < p.size; ++i) {
  if (p.tiles[1][coord]) {
    reached.insert(make_pair(coord, make_pair(0, 1)));
    to_check.push_front( make_pair(coord, 0));
  } else if (!p.tiles[0][coord]) {
    reached.insert(make_pair(coord, make_pair(1, 1)));
    to_check.push_back( make_pair(coord, 1) );
  }
  coord += p.size;
}
// if (DEBUG) cout << "eval shortest path3 "  << endl;
end_found_flag = false;
while(!to_check.empty()) {
  pair<short int, short int> c = to_check.front();
  to_check.pop_front();
  if(end_found_flag && blue_shortest_path != c.second) {
    for (short int s : shortest_nodes) {
      num_blue_shortest_paths += reached.at(s).second;
    }
    break;
  }
  if (in_last_row(c.first, p)) {
    shortest_nodes.push_back(c.first);
    //num_red_shortest_paths += reached.at(c.first).second;
    if (!end_found_flag) {
      blue_shortest_path = c.second;
      end_found_flag = true;
    }
  }
  bitset<6> dirs(0b111111);
  if (in_first_row(c.first, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_first_2_row(c.first, p)) {
    dirs &= bitset<6>(0b111100);
  }
  // if (DEBUG) cout << "eval shortest path33 " << c.second << endl;
  if(in_first_col(c.first, p)) {
    dirs &= bitset<6>(0b001100);
  } else if (in_first_2_col(c.first, p)) {
    dirs &= bitset<6>(0b011110);
  } else if (in_last_col(c.first, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_last_2_col(c.first, p)) {
    dirs &= bitset<6>(0b111100);
  }
  // if (DEBUG) cout << "eval shortest path34 " << c.second << endl;

  if (dirs[0]) {
    int i = c.first - 1;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
  // if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
  if (dirs[1]) {
    short int i = c.first + p.size -1;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
      //// if (DEBUG) cout << "eval shortest path36 " << c.second << endl;
  if (dirs[2]) {
    short int i = c.first + p.size;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
      //// if (DEBUG) cout << "eval shortest path37 " << c.second << endl;
  if (dirs[3]) {
    short int i = c.first + 1;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
      //// if (DEBUG) cout << "eval shortest path38 " << c.second << endl;
  if (dirs[4]) {
    short int i = c.first - p.size + 1;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
    //// if (DEBUG) cout << "eval shortest path39 " << c.second << endl;
  if (dirs[5]) { //always true
    short int i = c.first - p.size;
    const auto& iter = reached.find(i);
    const auto current = reached.at(c.first);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check.push_front( make_pair(i, c.second));
        reached.insert(make_pair(i, make_pair(c.second, current.second)));
      } else {
        to_check.push_back( make_pair(i, c.second + 1));
        reached.insert(make_pair(i, make_pair(c.second + 1, current.second)));
      }
    } else if (iter != reached.end() && !p.tiles[0][i]) {
      if (p.tiles[1][i]) {
        if (iter->second.first >= current.first) {
            iter->second.second += current.second;
        }
      } else if (iter->second.first > current.first) {
          iter->second.second += current.second;
      }
    }
  }
  //// if (DEBUG) cout << "eval shortest path35 " << c.second << endl;
}



//target_depth - depth
//
//// if (DEBUG) cout << "eval shortest path4"  << endl;
//cout << "Getting output" << endl;
float shortest_path_value = (log(num_red_shortest_paths) - log(num_blue_shortest_paths));
float points = blue_shortest_path - red_shortest_path + sigmoidP(shortest_path_value);
//if (DEBUG) cout << points << endl;
//cout << "Got output" << endl;
evaluated_positions.insert(make_pair(p, make_pair(0, points)));
// cout << "Blue reached" << endl;
// for (auto p : reached) {
//   cout << p.first << " : " << p.second.first << " "  << p.second.second << endl;
// }
// cout << "Red Shortest:" << red_shortest_path << " Red num: " << num_red_shortest_paths << " Blue Shortest:" << blue_shortest_path << " Blue num: " << num_blue_shortest_paths << endl;

return points;
}


bitset<6> getNeighbors(bool is_red, int pos, const Position& p) {
  bitset<6> neighbors = bitset<6>();
  bool first_row = in_first_row(pos, p);
  bool first_col = in_first_col(pos, p);
  bool last_row = in_last_row(pos, p);
  bool last_col = in_last_col(pos, p);

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
  return neighbors;
}



bool in_pruned_states(int pos, const Position& p) {
    bitset<6> red_state = getNeighbors(true, pos, p);
    bitset<6> blue_state = getNeighbors(false, pos, p);
    Neighbor_State ns(red_state, blue_state);

    Neighbor_State ns_reversed(blue_state, red_state);
    //For Now, replace with unordered_sets
    //cout << red_state << " " << blue_state << endl;

    return (((p.is_red && pruned_vulnerable.find(ns) != pruned_vulnerable.end()) || (!p.is_red && pruned_vulnerable.find(ns_reversed) != pruned_vulnerable.end()))
    || ((p.is_red && pruned_single_color_vulnerable.find(red_state) != pruned_single_color_vulnerable.end()) || (!p.is_red && pruned_single_color_vulnerable.find(blue_state) != pruned_single_color_vulnerable.end()))
    || pruned_single_color_dead.find(red_state) != pruned_single_color_dead.end() || pruned_single_color_dead.find(blue_state) != pruned_single_color_dead.end() || pruned_dead.find(ns) != pruned_dead.end());
}


Eval_Move minimax(short int depth, short int target_depth, Position& p, float alpha, float beta,unordered_map< Position, pair<short int, float>, PositionHasher >& evaluated_positions) {
  if (p.num_empty == 0) {
    //cout << "Empty" << endl;
    return Eval_Move(0, evaluate_shortestpath(p, evaluated_positions));
  }
	vector<Eval_Move> candidate_moves(p.num_empty);
  p.get_moves(candidate_moves);
	for (short int i = 0; i < p.num_empty; ++i) { //possibly better for loop
    if (in_pruned_states(candidate_moves[i].pos, p)) {
      candidate_moves[i].evaluation = (2*p.is_red - 1)*MIN;
      //cout << "PRUNED" << endl;
    } else {
      p.do_move(candidate_moves[i].pos, p.is_red);
      //cout << "pre calculating" << endl;
      //Eval_Move e = evaluate_shortestpath(p, evaluated_positions);
      //cout << e.pos << " " << e.evaluation << endl;
      candidate_moves[i].evaluation = evaluate_shortestpath(p, evaluated_positions);
      //cout << "pre undid" << endl;
      p.undo_move(candidate_moves[i].pos, p.is_red);
      //cout << "pre calculated" << endl;
    }

	}


	if (p.is_red) {
    if (depth == target_depth) {

      return *max_element(begin(candidate_moves), end(candidate_moves));
    }
    sort(candidate_moves.begin(), candidate_moves.end(), greater<Eval_Move>());
		float best = MIN;

		short int best_pos = -1;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }

		for (short int i = 0; i < p.num_empty; ++i) {
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        //cout << "PRUNED" << endl;
        continue;
      }
			p.do_move(candidate_moves[i].pos, p.is_red);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i].pos, p.is_red);
			if (opponent_eval_move.evaluation > best) {
				best = opponent_eval_move.evaluation;
				best_pos = candidate_moves[i].pos;
			}
			alpha = max(alpha, best);
			if (beta <= alpha)
				break;
		}
    //TO DO: Add to evaluated positions
    const auto& iter = evaluated_positions.find(p); //should be
    if (iter != evaluated_positions.end() && iter->second.first < target_depth - depth) {
        iter->second.first = target_depth - depth;
        iter->second.second = best;
        //cout << "Test1: " << target_depth - depth << endl;
    }
		return Eval_Move(best_pos, best);
	} else {
    if (depth == target_depth) {
      return *min_element(begin(candidate_moves), end(candidate_moves));
    }
    sort(candidate_moves.begin(), candidate_moves.end());
		float best = MAX;
    short int best_pos = -1;
    if (p.num_empty > 0) {
      best_pos = candidate_moves[0].pos;
    }


		for (short int i = 0; i < p.num_empty; ++i) {
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        //cout << "PRUNED" << endl;
        continue;
      }
			p.do_move(candidate_moves[i].pos, p.is_red);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, p, alpha, beta, evaluated_positions);
			p.undo_move(candidate_moves[i].pos, p.is_red);
			if (opponent_eval_move.evaluation < best) {
				best = opponent_eval_move.evaluation;
				best_pos = candidate_moves[i].pos;
			}
			beta = min(alpha, best);
			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
    const auto& iter = evaluated_positions.find(p); //should be
    if (iter != evaluated_positions.end() && iter->second.first < target_depth - depth) {
        iter->second.first = target_depth - depth;
        iter->second.second = best;
        //cout << "Test2: " << target_depth - depth << endl;
    }
		return Eval_Move(best_pos, best);

	}

}


//Test main
int main2(int argc, char *argv[]) {

  Position p(15, true);
  // unordered_map< Position, pair<short int, float> , PositionHasher > evaluated_positions;
  // float f = evaluate_shortestpath(p, evaluated_positions);
  // cout << f << endl;
  // bool red = true;
  // for (int i = 1; i < argc; ++i) {
  //       if (strcmp(argv[i],"S") == 0) {
  //         red = false;
  //         continue;
  //       }
  //       p.do_move(atoi(argv[i]), red);
  // }
  // cout << p << endl;
  //
  //
  // f = evaluate_shortestpath(p, evaluated_positions);
  // cout << f << endl;

  p.do_move(p.input_to_move("L11"), true);
  p.do_move(p.input_to_move("M12"), true);
  p.do_move(p.input_to_move("L12"), false);
  cout << p << endl;
  string move;
  while(true) {
    cin >> move;
    int m = p.input_to_move(move);
    cout << m << endl;
    string red_n = getNeighbors(true, m, p).to_string<char,std::string::traits_type,std::string::allocator_type>();
    string blue_n = getNeighbors(false, m, p).to_string<char,std::string::traits_type,std::string::allocator_type>();
    bool first_row = in_first_row(m, p);
    bool first_col = in_first_col(m, p);
    bool last_row = in_last_row(m, p);
    bool last_col = in_last_col(m, p);
    cout << "first_row: " << first_row << " first_col: " << first_col << " last row: " << last_row << " last_col " << last_col << endl;
    cout << red_n << endl;
    cout << blue_n << endl;
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
  max_depth = 9;
} else if(board_size >= 9) {
  max_depth = 8;
} else if(board_size >= 11) {
  max_depth = 7;
} else if(board_size >= 13) {
  max_depth = 6;
}

Position p(board_size, true);

unordered_map< Position, pair<short int, float> , PositionHasher > evaluated_positions; //Position to quality, evaluation

Eval_Move val;




auto t1 = chrono::high_resolution_clock::now();
auto t2 = chrono::high_resolution_clock::now();
if (ai_red) {
    int i = 1;
    while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 300 && i < max_depth) {
      t1 = chrono::high_resolution_clock::now();
      val = minimax(0, i, p, MIN, MAX, evaluated_positions);
      t2 = chrono::high_resolution_clock::now();
      i += 2;
    }
    // cout << p.move_to_output(val.pos) << endl;
    // // if (DEBUG) {
    //   cout << val.evaluation << " Depth: " << i << endl;
    // }
    // p.do_move(val.pos, true);
    int move = p.size/2 + p.size*(p.size/2) - (p.size+1)%2; //For some reason doesn't help
    cout << p.move_to_output(move) << endl;
    p.do_move(move, true);
    if (debug) cout << p;
}


while(p.num_empty > 0) {
  string player_move;
  cin >> player_move;
  //cout << "Played: " << player_move << " = " << p.input_to_move(player_move) << endl;
  p.do_move(p.input_to_move(player_move), !ai_red);
  // if (DEBUG) cout << p;
  int i = ai_red;
  t1 = chrono::high_resolution_clock::now();
  t2 = chrono::high_resolution_clock::now();
  while (chrono::duration_cast<chrono::milliseconds>(t2-t1).count() < 300 && i < max_depth) {
    //cout << i << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
    t1 = chrono::high_resolution_clock::now();
    val = minimax(0, i, p, MIN, MAX, evaluated_positions);
    t2 = chrono::high_resolution_clock::now();
    chrono::duration_cast<chrono::milliseconds>(t2-t1).count();
    i += 2;
  }
  //cout << i << " " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << endl;
  //cout <<  val.pos << " " << p.move_to_output(val.pos) << " " << val.evaluation << endl;



  cout << p.move_to_output(val.pos) << endl;
  p.do_move(val.pos, ai_red);
   if (debug) {
     cout << val.evaluation << " Depth: " << i << endl;
     cout << p;
  }
}

}

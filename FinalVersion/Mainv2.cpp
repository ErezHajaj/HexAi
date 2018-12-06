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

const int time_cap = 29855;

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

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b101100)), Neighbor_State(bitset<6>(0b000010), bitset<6>(0b101100)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b101100)), Neighbor_State(bitset<6>(0b000011), bitset<6>(0b101100)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b110100)), Neighbor_State(bitset<6>(0b000010), bitset<6>(0b110100)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b110100)), Neighbor_State(bitset<6>(0b000011), bitset<6>(0b110100)),

Neighbor_State(bitset<6>(0b011000), bitset<6>(0b000010)), Neighbor_State(bitset<6>(0b011000), bitset<6>(0b000001)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b000101)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b011100)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b011100)), Neighbor_State(bitset<6>(0b100000), bitset<6>(0b011100)),
Neighbor_State(bitset<6>(0b100010), bitset<6>(0b011100)),

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b010110)), Neighbor_State(bitset<6>(0b000001), bitset<6>(0b010110)),
Neighbor_State(bitset<6>(0b100000), bitset<6>(0b010110)), Neighbor_State(bitset<6>(0b100001), bitset<6>(0b010110)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b011010)), Neighbor_State(bitset<6>(0b000001), bitset<6>(0b011010)),
Neighbor_State(bitset<6>(0b100000), bitset<6>(0b011010)), Neighbor_State(bitset<6>(0b100001), bitset<6>(0b011010)),

Neighbor_State(bitset<6>(0b001100), bitset<6>(0b000001)), Neighbor_State(bitset<6>(0b001100), bitset<6>(0b100000)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b100010)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b001110)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b001110)), Neighbor_State(bitset<6>(0b010000), bitset<6>(0b001110)),
Neighbor_State(bitset<6>(0b010001), bitset<6>(0b001110)),

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b001011)), Neighbor_State(bitset<6>(0b100000), bitset<6>(0b001011)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b001011)), Neighbor_State(bitset<6>(0b110000), bitset<6>(0b001011)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b001101)), Neighbor_State(bitset<6>(0b100000), bitset<6>(0b001101)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b001101)), Neighbor_State(bitset<6>(0b110000), bitset<6>(0b001101)),

Neighbor_State(bitset<6>(0b000110), bitset<6>(0b100000)), Neighbor_State(bitset<6>(0b000110), bitset<6>(0b010000)),
Neighbor_State(bitset<6>(0b000100), bitset<6>(0b010001)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b000111)),
Neighbor_State(bitset<6>(0b100000), bitset<6>(0b000111)), Neighbor_State(bitset<6>(0b001000), bitset<6>(0b000111)),
Neighbor_State(bitset<6>(0b101000), bitset<6>(0b000111)),

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b100101)), Neighbor_State(bitset<6>(0b010000), bitset<6>(0b100101)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b100101)), Neighbor_State(bitset<6>(0b011000), bitset<6>(0b100101)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b100110)), Neighbor_State(bitset<6>(0b010000), bitset<6>(0b100110)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b100110)), Neighbor_State(bitset<6>(0b011000), bitset<6>(0b100110)),

Neighbor_State(bitset<6>(0b000011), bitset<6>(0b010000)), Neighbor_State(bitset<6>(0b000011), bitset<6>(0b001000)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b101000)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b100011)),
Neighbor_State(bitset<6>(0b010000), bitset<6>(0b100011)), Neighbor_State(bitset<6>(0b000100), bitset<6>(0b100011)),
Neighbor_State(bitset<6>(0b010100), bitset<6>(0b100011)),

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b110010)), Neighbor_State(bitset<6>(0b001000), bitset<6>(0b110010)),
Neighbor_State(bitset<6>(0b000100), bitset<6>(0b110010)), Neighbor_State(bitset<6>(0b001100), bitset<6>(0b110010)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b010011)), Neighbor_State(bitset<6>(0b001000), bitset<6>(0b010011)),
Neighbor_State(bitset<6>(0b000100), bitset<6>(0b010011)), Neighbor_State(bitset<6>(0b001100), bitset<6>(0b010011)),

Neighbor_State(bitset<6>(0b100001), bitset<6>(0b001000)), Neighbor_State(bitset<6>(0b100001), bitset<6>(0b000100)),
Neighbor_State(bitset<6>(0b000001), bitset<6>(0b010100)), Neighbor_State(bitset<6>(0b000000), bitset<6>(0b110001)),
Neighbor_State(bitset<6>(0b001000), bitset<6>(0b110001)), Neighbor_State(bitset<6>(0b000010), bitset<6>(0b110001)),
Neighbor_State(bitset<6>(0b001010), bitset<6>(0b110001)),

Neighbor_State(bitset<6>(0b000000), bitset<6>(0b011001)), Neighbor_State(bitset<6>(0b000100), bitset<6>(0b011001)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b011001)), Neighbor_State(bitset<6>(0b000110), bitset<6>(0b011001)),
Neighbor_State(bitset<6>(0b000000), bitset<6>(0b101001)), Neighbor_State(bitset<6>(0b000100), bitset<6>(0b101001)),
Neighbor_State(bitset<6>(0b000010), bitset<6>(0b101001)), Neighbor_State(bitset<6>(0b000110), bitset<6>(0b101001))

});




inline float sigmoidP(float x) {
    return x/(1 +abs(x));
}


inline bool in_first_col(int i, const Position&p) {
  return (i < p.size);
}

inline bool in_first_2_col(int i, const Position&p) {
  return (i < 2*p.size);
}

inline bool in_last_col(int i, const Position&p) {
  return (p.size*(p.size - 1) <= i);
}

inline bool in_last_2_col(int i, const Position&p) {
  return ((p.size*(p.size - 2)) <= i);
}


inline bool in_first_row(int i, const Position&p) {
  return !(i%p.size);
}

inline bool in_first_2_row(int i, const Position&p) {
  return (i%p.size <= 1);
}

inline bool in_last_row(int i, const Position&p) {
  return !((i+1)%p.size);
}

inline bool in_last_2_row(int i, const Position&p) {
  return (((i+2)%p.size) <= 1);
}

float evaluate_shortestpath(const Position& p, unordered_map< Position, pair<short int, float>, PositionHasher >& evaluated_positions) {

  const auto& iter = evaluated_positions.find(p); //should be
  if (iter != evaluated_positions.end()) {
      return iter->second.second;

  }

  short int red_shortest_path = MAX;
  short int blue_shortest_path = MAX;
  int num_red_shortest_paths = 0;
  int num_blue_shortest_paths = 0;
  unordered_map<short int, pair<short int, int> > reached; //Reached position, shortest path, number of paths

  deque < pair<short int, short int> > to_check_uncolored;
  deque < pair<short int, short int> > to_check_colored;


  for (short int i = 0; i < p.size; ++i) {
    if (p.tiles[0][i]) {
      reached.insert(make_pair(i, make_pair(0, 1)));
      to_check_colored.push_front( make_pair(0, i) );
    } else if (!p.tiles[1][i]) {
      reached.insert(make_pair(i, make_pair(1, 1)));
      to_check_uncolored.push_back( make_pair(1, i) );
    }
  }
  bool end_found_flag = false;
  vector<short int> shortest_nodes;

  while(!to_check_uncolored.empty() || !to_check_colored.empty()) {
    pair<short int, short int> c;
    if (to_check_colored.empty()) {
      c = to_check_uncolored.front();
      to_check_uncolored.pop_front();
    } else if (to_check_uncolored.empty()) {
      c = to_check_colored.front();
      to_check_colored.pop_front();
    } else if (to_check_colored.front().first < to_check_uncolored.front().first) {
      c = to_check_colored.front();
      to_check_colored.pop_front();
    } else {
      c = to_check_uncolored.front();
      to_check_uncolored.pop_front();
    }

    const auto current = reached.at(c.second);
    //cout << "test " << red_shortest_path << " " << c.first << " " << c.second << endl;
    if(end_found_flag && red_shortest_path < c.first) {
      for (short int s : shortest_nodes) {
        num_red_shortest_paths += reached.at(s).second;
      }
      break;
    }
    if (in_last_col(c.second, p)) {
      shortest_nodes.push_back(c.second);
      if (!end_found_flag) {
        red_shortest_path = c.first;
        end_found_flag = true;
      }
    }
    bitset<6> dirs(0b111111);
    if (in_first_col(c.second, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_first_2_col(c.second, p)) {
      dirs &= bitset<6>(0b001111);
    }
    if(in_first_row(c.second, p)) {
      dirs &= bitset<6>(0b001100);
    } else if (in_first_2_row(c.second, p)) {
      dirs &= bitset<6>(0b011110);
    } else if (in_last_row(c.second, p)) {
      dirs &= bitset<6>(0b000110);
    } else if (in_last_2_row(c.second, p)) {
      dirs &= bitset<6>(0b001111);
    }

    short int i;
    if (dirs[0]) {
      i = c.second - 1;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
    if (dirs[1]) {
      i = c.second + p.size -1;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
    //if (dirs[2]) { //ALWAYS HAPPENS
      i = c.second + p.size;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
    //}
    if (dirs[3]) {
      i = c.second + 1;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
    if (dirs[4]) {
      i = c.second - p.size + 1;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
    if (dirs[5]) { //always true
      i = c.second - p.size;
      const auto& iter = reached.find(i);
      if (!p.tiles[1][i] && iter == reached.end()) {
        if (p.tiles[0][i]) {
          to_check_colored.push_front( make_pair(c.first, i));
          reached.insert(make_pair(i, make_pair(c.first, current.second)));
        } else {
          to_check_uncolored.push_back( make_pair(c.first + 1, i));
          reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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

reached.clear();
to_check_colored.clear();
to_check_uncolored.clear();
shortest_nodes.clear();
short int coord = 0;
for (short int i = 0; i < p.size; ++i) {
  if (p.tiles[1][coord]) {
    reached.insert(make_pair(coord, make_pair(0, 1)));
    to_check_colored.push_front( make_pair(0, coord));
  } else if (!p.tiles[0][coord]) {
    reached.insert(make_pair(coord, make_pair(1, 1)));
    to_check_uncolored.push_back( make_pair(1, coord) );
  }
  coord += p.size;
}
end_found_flag = false;
while(!to_check_uncolored.empty() || !to_check_colored.empty()) {
  pair<short int, short int> c;
  if (to_check_colored.empty()) {
    c = to_check_uncolored.front();
    to_check_uncolored.pop_front();
  } else if (to_check_uncolored.empty()) {
    c = to_check_colored.front();
    to_check_colored.pop_front();
  } else if (to_check_colored.front().first < to_check_uncolored.front().first) {
    c = to_check_colored.front();
    to_check_colored.pop_front();
  } else {
    c = to_check_uncolored.front();
    to_check_uncolored.pop_front();
  }


  const auto current = reached.at(c.second);
  if(end_found_flag && blue_shortest_path != c.first) {
    for (short int s : shortest_nodes) {
      num_blue_shortest_paths += reached.at(s).second;
    }
    break;
  }
  if (in_last_row(c.second, p)) {
    shortest_nodes.push_back(c.second);
    if (!end_found_flag) {
      blue_shortest_path = c.first;
      end_found_flag = true;
    }
  }
  bitset<6> dirs(0b111111);
  if (in_first_row(c.second, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_first_2_row(c.second, p)) {
    dirs &= bitset<6>(0b111100);
  }
  if(in_first_col(c.second, p)) {
    dirs &= bitset<6>(0b001100);
  } else if (in_first_2_col(c.second, p)) {
    dirs &= bitset<6>(0b011110);
  } else if (in_last_col(c.second, p)) {
    dirs &= bitset<6>(0b011000);
  } else if (in_last_2_col(c.second, p)) {
    dirs &= bitset<6>(0b111100);
  }
  short int i;
  if (dirs[0]) {
     i = c.second - 1;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
  if (dirs[1]) {
    i = c.second + p.size -1;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
  if (dirs[2]) {
    i = c.second + p.size;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
  //if (dirs[3]) { //Always happens
    i = c.second + 1;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
  //}
  if (dirs[4]) {
    i = c.second - p.size + 1;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
  if (dirs[5]) { //always true
    i = c.second - p.size;
    const auto& iter = reached.find(i);
    if (!p.tiles[0][i] && iter == reached.end()) {
      if (p.tiles[1][i]) {
        to_check_colored.push_front( make_pair(c.first, i));
        reached.insert(make_pair(i, make_pair(c.first, current.second)));
      } else {
        to_check_uncolored.push_back( make_pair(c.first + 1, i));
        reached.insert(make_pair(i, make_pair(c.first + 1, current.second)));
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
}

float points = blue_shortest_path - red_shortest_path + sigmoidP(num_red_shortest_paths - num_blue_shortest_paths);
evaluated_positions.insert(make_pair(p, make_pair(0, points)));
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



bool in_pruned_states(short int pos, const Position& p) {
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


Eval_Move minimax(short int depth, short int target_depth, Position& p, float alpha, float beta,unordered_map< Position, pair<short int, float>, PositionHasher >& evaluated_positions, chrono::time_point<std::chrono::high_resolution_clock>& t1, bool& time_remaining) {
  if (p.num_empty == 0) {
    //cout << "Empty" << endl;
    return Eval_Move(0, evaluate_shortestpath(p, evaluated_positions));
  }
	vector<Eval_Move> candidate_moves(p.num_empty);
  p.get_moves(candidate_moves);
	for (short int i = 0; i < p.num_empty; ++i) { //possibly better for loop
    if (in_pruned_states(candidate_moves[i].pos, p)) {
      candidate_moves[i].evaluation = (2*p.is_red - 1)*MIN;
    } else {
      p.do_move(candidate_moves[i].pos, p.is_red);

      candidate_moves[i].evaluation = evaluate_shortestpath(p, evaluated_positions);
      p.undo_move(candidate_moves[i].pos, p.is_red);
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
      //cout << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count() << endl;
      if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count() > time_cap) {
        time_remaining = false;
        break;
      }
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        //cout << "PRUNED" << endl;
        continue;
      }
			p.do_move(candidate_moves[i].pos, p.is_red);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, p, alpha, beta, evaluated_positions, t1, time_remaining);
			p.undo_move(candidate_moves[i].pos, p.is_red);
			if (opponent_eval_move.evaluation > best) {
				best = opponent_eval_move.evaluation;
				best_pos = candidate_moves[i].pos;
			}
			alpha = max(alpha, best);
			if (beta <= alpha)
				break;
		}
    const auto& iter = evaluated_positions.find(p); //should be
    if (iter != evaluated_positions.end() && iter->second.first < target_depth - depth) {
        iter->second.first = target_depth - depth;
        iter->second.second = best;
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
      //cout << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count() << endl;
      if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1).count() > time_cap) {
        time_remaining = false;
        break;
      }
      if (in_pruned_states(candidate_moves[i].pos, p)) {
        continue;
      }
			p.do_move(candidate_moves[i].pos, p.is_red);
			Eval_Move opponent_eval_move = minimax(depth + 1, target_depth, p, alpha, beta, evaluated_positions, t1, time_remaining);
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


int main(int argc, char *argv[])  {
  string ai_color = "RED";
  short int board_size = 7;
  short int max_depth = 15;
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

Position p(board_size, true);

unordered_map< Position, pair<short int, float> , PositionHasher > evaluated_positions; //Position to quality, evaluation

Eval_Move val;


auto t1 = chrono::high_resolution_clock::now();
bool time_remaining = true;
if (ai_red) {
    int i = 1;

    while (time_remaining && i < max_depth) {
      val = minimax(0, i, p, MIN, MAX, evaluated_positions, t1, time_remaining);
      i += 2;
    }
    int move = p.size/2 + p.size*(p.size/2) - (p.size+1)%2; //For some reason doesn't help
    cout << p.move_to_output(move) << endl;
    p.do_move(move, true);
}


while(p.num_empty > 0) {
  string player_move;
  cin >> player_move;
  p.do_move(p.input_to_move(player_move), !ai_red);
  int i = ai_red;

  t1 = chrono::high_resolution_clock::now();
  time_remaining = true;
  while (time_remaining && i < max_depth) {
    val = minimax(0, i, p, MIN, MAX, evaluated_positions, t1, time_remaining);
    i += 2;
  }

  cout << p.move_to_output(val.pos) << endl;
  p.do_move(val.pos, ai_red);
}

}

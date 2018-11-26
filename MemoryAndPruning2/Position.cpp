#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <stdlib.h>
#include <string>

#include "Move.cpp"

using namespace std;


template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


class Position {
  public:
    Position(short int s, bool red):tiles(2, vector<bool>(s*s)), is_red(red), size(s), num_empty(s*s) {
    }


    void do_move(short int pos, bool red) {
        tiles[0][pos] = red;
        tiles[1][pos] = !red;

      is_red = !red;
      --num_empty;
    }

    void undo_move(short int pos, bool red) {
      //if (red) {
        tiles[0][pos] = false;
      //} else {
        tiles[1][pos] = false;
      //}
      is_red = !red;
      ++num_empty;
    }



    void get_moves(vector<Eval_Move>& candidate_moves) {
      short int counter = 0;
      for (short int i = 0; i < size*size; ++i) {
          if (!tiles[0][i] && !tiles[1][i]) {
            candidate_moves[counter] = Eval_Move(i);
            ++counter;
          }
      }
    }

    int input_to_move(string s) {
      return ((int)s[0] - (int)'A') + (stoi(s.substr(1)))*size;
    }
    string move_to_output(int n) {
      char aChar = 'A' + n%size;
      string output = "";
      output += aChar;
      return output + to_string(n/size);
    }

    bool operator==(const Position &other) const {
      if (num_empty != other.num_empty || size != other.size || is_red != other.is_red) {
        return false;
      }
      return (tiles == other.tiles);
    }


    short int num_empty;
    short int size;
    vector< vector<bool> > tiles;
    bool is_red;
};

inline std::ostream & operator<<(std::ostream & Str, Position const & p) {
  for (int i = 0; i < p.size; ++i) {
    for (int j = 0; j < p.size; ++j) {
      int pos = i+j*p.size;
      if (p.tiles[0][pos]) Str << "R";
      else if (p.tiles[1][pos]) Str << "B";
      else Str << "O";
    }
    Str << endl;
  }
return Str;
}

struct PositionHasher {
  size_t operator()(const Position & obj) const {
    size_t seed = 0;
    hash_combine(seed, obj.tiles[0]);
    hash_combine(seed, obj.tiles[1]);
    hash_combine(seed, obj.is_red);
    return seed;
  }
};

struct Neighbor_State {

  Neighbor_State(bitset<6> rs, bitset<6> bs): red_state(rs), blue_state(bs){
  }

  bool operator==(const Neighbor_State &other) const {
    return(red_state == other.red_state && blue_state == other.blue_state);
  }
  bitset<6> red_state;
  bitset<6> blue_state;
};

struct NeighborHasher {
  size_t operator()(const Neighbor_State& obj) const {
    size_t seed = 0;
    hash_combine(seed, obj.red_state);
    hash_combine(seed, obj.blue_state);
    return seed;
  }
};

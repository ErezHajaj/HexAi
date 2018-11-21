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
    Position(short int s):red_tiles((s*s), false), blue_tiles((s*s), false), size(s), num_empty(s*s) {
    }


    void do_move(short int pos, bool red) {
      if (red) {
        red_tiles[pos] = true;
      } else {
        blue_tiles[pos] = true;
      }
      //is_red = !red;
      --num_empty;
    }

    void undo_move(short int pos, bool red) {
      //if (red) {
        red_tiles[pos] = false;
      //} else {
        blue_tiles[pos] = false;
      //}
      //is_red = !red;
      ++num_empty;
    }

    void get_moves(vector<Eval_Move>& candidate_moves) {
      short int counter = 0;
      for (short int i = 0; i < size*size; ++i) {
        //if (is_red) {
          if (!red_tiles[i] && !blue_tiles[i]) {
            candidate_moves[counter] = Eval_Move(i);
            ++counter;
          }
      }
    }

    int input_to_move(string s) {
      return ((int)s[0] - (int)'A') + ((int)s[1] - (int)'0')*size;
    }
    string move_to_output(int n) {
      char aChar = 'A' + n%size;
      string output = "";
      output += aChar;
      return output + to_string(n/size);
    }

    bool operator==(const Position &other) const {
      if (num_empty != other.num_empty || size != other.size) {
        return false;
      }
      return (red_tiles == other.red_tiles && blue_tiles == other.blue_tiles);
    }


    short int num_empty;
    short int size;
    vector<bool> red_tiles;
    vector<bool> blue_tiles;
    //bool is_red;
};

struct PositionHasher {
  size_t operator()(const Position & obj) const {
    size_t seed = 0;
    hash_combine(seed, obj.red_tiles);
    hash_combine(seed, obj.blue_tiles);
    return seed;
  }
};

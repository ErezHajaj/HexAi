#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <utility>

using namespace std;


struct Eval_Move {
  Eval_Move(int p, int eval): pos(p), evaluation(eval){
  }
  Eval_Move(int p): pos(p){
  }
  Eval_Move(){
  }


  bool operator < (const Eval_Move& m) const {
   return (evaluation < m.evaluation);

  }
  bool operator > (const Eval_Move& m) const {
   return (evaluation > m.evaluation);
  }

  bool operator == (const Eval_Move& m) const {
   return (evaluation == m.evaluation);
  }

  int pos;
  int evaluation;
};

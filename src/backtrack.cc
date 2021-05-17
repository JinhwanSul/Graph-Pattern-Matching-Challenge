/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

Backtrack::Backtrack() {
  // TODO: state space initiailize
  // initialize v-stacks
}
Backtrack::~Backtrack() {}

size_t Backtrack::GoBack(size_t current_state) {
  while (state_space[current_state].second->empty()) {
    current_state--;
    state_space[current_state].second->pop();
  }
}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query, const CandidateSet &cs) {
  size_t root = SelectRoot(query, cs); 
  PushU(root);
  size_t current_state = 0;
  size_t next_u, next_state;
  
  while (state_space[0].second->size() == 0) {
    
    if (current_state == query.GetNumVertices()) {
      PrintnClear();
      current_state = GoBack(current_state);
    }

    next_state = state_space[current_state + 1].first;
    
    if (next_state == -1){
      next_u = NextU(state_space[current_state].first);
      current_state++;
      if (!PushU(next_u)){
        current_state = GoBack(current_state);
      }
    } else {
      next_u = next_state;
      current_state++;
      if (!PushU(next_u)){
        current_state = GoBack(current_state);
      }
    }    
  } 
}

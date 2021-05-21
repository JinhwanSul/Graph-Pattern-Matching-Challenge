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
  size_t current_state = 0;
  PushU(root, current_state, cs, data, query);
  size_t next_u, next_state;
  
  while (state_space[0].second->size() == 0) {
    
    if (current_state == query.GetNumVertices()) {
      PrintnClear(current_state);
      current_state = GoBack(current_state);
    }

    next_state = state_space[current_state + 1].first;
    
    if (next_state == -1){
      next_u = NextU(state_space[current_state].first);
      current_state++;
      if (!PushU(next_u, current_state, cs, data, query)){
        current_state = GoBack(current_state);
      }
    } else {
      next_u = next_state;
      current_state++;
      if (!PushU(next_u, current_state, cs, data, query)){
        current_state = GoBack(current_state);
      }
    }    
  } 
}


size_t Backtrack::SelectRoot(const Graph &query, const CandidateSet &cs) {
  //cs 에서 한 u당 v 갯수 / query에서 한 vertex에서 뻗어나가는 가짓수 최소
  size_t cs_size = query.GetNumVertices();
  size_t tmp, root_number;
  size_t min = 100;
  for(size_t i=0; i<cs_size; i++)
  {
    if(query.GetDegree(i)==0) break;
    tmp = cs.GetCandidateSize(i)/query.GetDegree(i);
    if(tmp < min)
    {
      min = tmp;
      root_number = i;
    }
  }
  return root_number;
}

bool Backtrack::PushU(size_t &u, size_t &current_state, const CandidateSet &cs, const Graph &data, const Graph &query) {
  //input으로 current_state, cs도 필요해서 추가하였음
  //next u 정해주고서 embedding condition 따져서 가능한 v들 찾기
  //가능한 v 없으면 return false
  //next 위치에 u 삽입, 그 해당 -> 포인터에 v stack 삽입 
  this->state_space[current_state].first = u;
  size_t v_size = cs.GetCandidateSize(u);
  size_t i,j = 0;
  for(size_t i=0; i<v_size; i++)
  {
    size_t v = cs.GetCandidate(u,i);
    std::pair<size_t, size_t> p1;
    p1 = {u, v};
    if(EmbeddingCondition(data, query, p1))
    {
      this->state_space[current_state].second.push(v);
      j++;
    }
  }
  return j!=0;
}

void Backtrack::PrintnClear(size_t current_state) {
  //
  size_t n = this->state_space.size();
  size_t *printarray = new size_t[n];
  
  //u[current_state]의 에 해당되는 원소만 빼고 나머지 원소 다 채워넣음
  for(size_t i=0; i<n; i++)
  {
    if(i!=current_state)
    {
      printarray[state_space[i].first]=this->state_space[i].second.top;
    }
  }

  //u[current_state] 의 v가 empty 될때까지 v들을 하나씩 pop해서 넣어서 출력함
  while(!this->state_space[current_state].second.empty())
  {
    printarray[state_space[current_state].first] = this->state_space[current_state].second.pop;
    for(size_t i=0; i<n; i++)
    {
      std::cout << printarray[i];
    }
  }
}
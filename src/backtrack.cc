/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

// #define DEBUG

void print_vector(std::set<size_t> question);


Backtrack::Backtrack(const Graph &query) {

  size_t i, query_vertices = query.GetNumVertices();
  this->count = 0;
  // std::vector<std::pair<size_t, std::stack<size_t>*>> state_space_;
  for (i = 0; i < query_vertices; i++) {
    std::stack<size_t> v_stack;
    std::pair<size_t, std::stack<size_t>> p;
    p.first = SIZE_MAX;
    p.second = v_stack;
    this->state_space.push_back(p);
  }
  // this->state_space = state_space_;

  // Maybe redundant
  // std::map<size_t, size_t> partial_embedding_;
  // this->partial_embedding = partial_embedding_;
  // std::vector<size_t> extendable_vertex_;
  // this->extendable_vertex = extendable_vertex_;
  
}

Backtrack::~Backtrack() {}


void Backtrack::PrintAllMatches(const Graph &data, const Graph &query, const CandidateSet &cs) {
  clock_t start_time, end_time;
  start_time = clock();
  size_t root = SelectRoot(query, cs);
  size_t current_state = 0;
  size_t next_u = 0, next_state;
  
  PushU(root, current_state, cs, data, query);

#ifdef DEBUG
  size_t first_u = this->state_space[0].first;
  size_t size = this->state_space[0].second.size();
#endif

  while (state_space[0].second.size() != 0) {
    end_time = clock();
    if (end_time - start_time > 60*1000) {
      printf("Time out\n");
      printf("Total embedding %d found\n", this->count);
      break;
    }
    if (current_state == query.GetNumVertices()-1) {
      PrintnClear(current_state);
      current_state = GoBack(current_state);
    }

    next_state = state_space[current_state + 1].first;
    if (next_state == SIZE_MAX){
      // next_u = NextU(state_space[current_state].first);
      //printf("[DEBUG11] before nextU\n");
      //print_vector(this->extendable_vertex);
      next_u = NextU(data, query, cs);
      DeleteExtendableVertex(next_u, query);
      //printf("[DEBUG11] after DeleteExtenableVertex\n");
      //print_vector(this->extendable_vertex);
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
  printf("Search Done!\n"); 
}

size_t Backtrack::GoBack(size_t current_state) {
  
  while (state_space[current_state].second.empty()) {
    this->partial_embedding.erase(this->state_space[current_state].first);
    if (current_state == 0) {
      break;
    }
    current_state--; 
    state_space[current_state].second.pop();
  }
  return current_state;
}

bool Backtrack::EmbeddingCondition(const Graph &data, const Graph &query, std::pair<size_t, size_t> u_v) {
  
  size_t v_p;
  size_t u = u_v.first, v = u_v.second;
  std::vector<size_t> parent_of_u;
  std::vector<size_t>::iterator u_p;
  std::map<size_t, size_t>::iterator iter;
  
  // Case 1: check if v is already in partial_embedding or not & find parent of u
  for (iter = this->partial_embedding.begin(); iter != this->partial_embedding.end(); iter++) {
    if (iter->second == v) {
      return false;
    }
    if (query.IsNeighbor(u, iter->first)) {
      parent_of_u.push_back(iter->first);
    }
  }

  // Case 2: check if u_v connection state is same
  for (u_p = parent_of_u.begin(); u_p != parent_of_u.end(); u_p++) {
    v_p = this->partial_embedding.find(*u_p)->second;
    if (!data.IsNeighbor(v, v_p)) {
      return false;
    }
  }

  return true;
}

void Backtrack::DeleteExtendableVertex(size_t u, const Graph &query) {
  size_t i, start_offset, end_offset;
  size_t child_candidate;
  std::set<size_t>::iterator iter;

  start_offset = query.GetNeighborStartOffset(u);
  end_offset = query.GetNeighborEndOffset(u);
  for (i = start_offset; i < end_offset; i++) {
    child_candidate = query.GetNeighbor(i);
    // If child_candidate is not in partial_embedding, it is child of u.
    if (this->partial_embedding.find(child_candidate) == this->partial_embedding.end()) {
      this->extendable_vertex.insert(child_candidate);
    }
  }

  for (iter = this->extendable_vertex.begin(); iter != this->extendable_vertex.end(); iter++) {
    if (*iter == u) {
      this->extendable_vertex.erase(iter);
      break;
    }
  }
}

size_t Backtrack::NextU(const Graph &data, const Graph &query, const CandidateSet &cs) {
  std::set<size_t>::iterator iter;
  std::pair<size_t, size_t> u_v;
  int i, v_size, cmu_size, min_cmu_size = INT32_MAX;
  size_t u, v, next_u = 0;

  for (iter = this->extendable_vertex.begin(); iter != this->extendable_vertex.end(); iter++) {
    u = *iter;
    v_size = cs.GetCandidateSize(u);
    cmu_size = 0;
    for (i = 0; i < v_size; i++) {
      v = cs.GetCandidate(u, i);
      u_v = std::make_pair(u, v);
      if (EmbeddingCondition(data, query, u_v)) {
        cmu_size++;
      }
    }
    
    if (cmu_size < min_cmu_size) {
      min_cmu_size = cmu_size;
      next_u = u;
    }
  }

  return next_u;
}

size_t Backtrack::SelectRoot(const Graph &query, const CandidateSet &cs) {
  //cs 에서 한 u당 v 갯수 / query에서 한 vertex에서 뻗어나가는 가짓수 최소
  size_t cs_size = query.GetNumVertices();
  size_t tmp, root_number = 0, min = 100;
  size_t i, start_offset, end_offset;

  for (i = 0; i < cs_size; i++) {
    
    if (query.GetDegree(i) == 0) { break; }
    
    tmp = cs.GetCandidateSize(i) / query.GetDegree(i);
    if (tmp < min) {
      min = tmp;
      root_number = i;
    }
  }

  // Initialize extendable_vertex with child of root
  start_offset = query.GetNeighborStartOffset(root_number);
  end_offset = query.GetNeighborEndOffset(root_number);
  for (i = start_offset; i < end_offset; i++) {
    this->extendable_vertex.insert(query.GetNeighbor(i));
  }

  return root_number;
}

bool Backtrack::PushU(size_t u, size_t current_state, const CandidateSet &cs, const Graph &data, const Graph &query) {
  //next u 정해주고서 embedding condition 따져서 가능한 v들 찾기
  //가능한 v 없으면 return false
  //next 위치에 u 삽입, 그 해당 -> 포인터에 v stack 삽입 
  size_t i, v_size;
  std::pair<size_t, size_t> p1;
  size_t v, j = 0;
  
  v_size = cs.GetCandidateSize(u);
  
  this->state_space[current_state].first = u;
  
  for (i = 0; i < v_size; i++) {
    
    v = cs.GetCandidate(u, i);
    p1 = std::make_pair(u, v);
    
    if (EmbeddingCondition(data, query, p1)) {
      this->state_space[current_state].second.push(v);
      j++;
    }
  }

  this->partial_embedding.insert({u, this->state_space[current_state].second.top()});

  return j != 0; // j == 0 means v-stack is empty, 
}

void Backtrack::PrintnClear(size_t current_state) {
  
  size_t n = this->state_space.size();
  size_t *print_array = new size_t[n];
  
  //u[current_state]의 에 해당되는 원소만 빼고 나머지 원소 다 채워넣음
  for (size_t i = 0; i < n; i++) {
    if(i != current_state) {
      print_array[state_space[i].first] = this->state_space[i].second.top();
    }
  }

  //u[current_state] 의 v가 empty 될때까지 v들을 하나씩 pop해서 넣어서 출력함
  while (!this->state_space[current_state].second.empty()) {
    
    print_array[state_space[current_state].first] = this->state_space[current_state].second.top();
    
    this->state_space[current_state].second.pop();
    this->count++;
    std::cout << "\nresult " << this->count << std::endl;
    for (size_t i = 0; i < n; i++) {
      std::cout << print_array[i] << " ";
    }
  }
  std::cout << std::endl;
  delete[] print_array;
}

void print_vector(std::set<size_t> question) {
  std::set<size_t>::iterator iter;
  printf("---[VECTOR] print vector----\n");
  for (iter = question.begin(); iter != question.end(); iter++) {
    printf("%ld ", *iter);
  }
  printf("\n---------------------------\n");
}
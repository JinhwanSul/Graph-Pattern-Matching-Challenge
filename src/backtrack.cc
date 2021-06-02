/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <assert.h>

#define JUMP_TIME 30

void print_set(std::set<size_t> question, const char *msg);
void print_vector(std::vector<size_t> question, const char *msg);
void print_partial_embedding(std::map<size_t, size_t> partial_embedding, const char *msg);
void print_state_space(std::vector<std::pair<size_t, std::stack<size_t>>> question);
void check_synchronization(std::vector<std::pair<size_t, std::stack<size_t>>> state_space,
                          std::map<size_t, size_t> partial_embedding);
void StackClear(std::stack<size_t> v_stack);      

void print_u_info(const Graph &query, const CandidateSet &cs, size_t u, size_t cmu);

Backtrack::Backtrack(const Graph &query) {

  size_t i, query_vertices = query.GetNumVertices();
  this->count = 0;
  for (i = 0; i < query_vertices; i++) {
    std::stack<size_t> v_stack;
    std::pair<size_t, std::stack<size_t>> p;
    p.first = SIZE_MAX;
    p.second = v_stack;
    this->state_space.push_back(p);
  }  
}

Backtrack::~Backtrack() {}


void Backtrack::PrintAllMatches(const Graph &data, const Graph &query, const CandidateSet &cs) {
  time_t max_curr_time_check, max_curr_time_last, start_time, end_time, print_time_check, print_time_last;
  start_time = time(NULL);
  max_curr_time_last = time(NULL);
  print_time_last = time(NULL);
  size_t root = SelectRoot(query, cs);
  // printf("[DEBUG] root is %ld\n", root);
  size_t current_state = 0;
  size_t next_u = 0, next_state;
  size_t max_current_state = 0;


  PushU(root, current_state, cs, data, query);

  while (state_space[0].second.size() != 0) {
    time(&end_time);
    time(&max_curr_time_check);
    time(&print_time_check);
    

    if (max_current_state < query.GetNumVertices()-1) {
      if(max_curr_time_check - max_curr_time_last > JUMP_TIME)
      {
        current_state = Jump(current_state);
        print_time_last = time(NULL);
        max_curr_time_last = time(NULL);
      }
    }
    else 
    {
      if (print_time_check - print_time_last > JUMP_TIME) {
        current_state = Jump(current_state);
        print_time_last = time(NULL);
        max_curr_time_last = time(NULL);
      }
    }
    // printf("\n\n===============[DEBUG](end_time - start_time) = %ld==============\n", (end_time - start_time));
    if ((end_time - start_time) >= 60) {
      printf("Time out\n");
      printf("Total embedding %d found\n", this->count);
      break;
    }
    // printf("[DEBUG] current_state = %ld\n", current_state);
    if (current_state == query.GetNumVertices()-1) {
      PrintnClear(current_state);
      print_time_last = time(NULL);
      current_state = GoBack(current_state);
    }

    next_state = state_space[current_state + 1].first;
    if (next_state == SIZE_MAX) {
      // printf("[DEBUG] before nextU\n");
      // print_set(this->extendable_vertex, "extendable vertex");
      // print_partial_embedding(this->partial_embedding, "partial_embedding");
      // printf("[DEBUG] current state_space (%ld %ld)\n", state_space[current_state].first, state_space[current_state].second.top());
      next_u = NextU(data, query, cs);
      // printf("[DEBUG] next_u = %ld\n", next_u);
      DeleteExtendableVertex(next_u, query);
      // printf("[DEBUG] after DeleteExtenableVertex\n");
      // print_set(this->extendable_vertex, "extendable vertex");
      current_state++;
      if (!PushU(next_u, current_state, cs, data, query)){
        current_state = GoBack(current_state);
      }

      max_curr_time_last = time(NULL);
      max_current_state = current_state;

    } else {
      next_u = next_state;
      // printf("[DEBUG] (not calling NextU) next_u = %ld\n", next_u);
      current_state++;
      if (!PushU(next_u, current_state, cs, data, query)) {
        // print_partial_embedding(this->partial_embedding, "before GoBack");
        current_state = GoBack(current_state);
      }
    }
    // print_partial_embedding(this->partial_embedding, "partial_embedding");
    // print_state_space(this->state_space);
    // check_synchronization(this->state_space, this->partial_embedding);
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
    this->partial_embedding.erase(this->state_space[current_state].first);
    state_space[current_state].second.pop();
  }
  // print_state_space(state_space);
  // print_partial_embedding(partial_embedding, "[DEBUG]");
  // if (current_state != 0) {
  //   this->partial_embedding.insert({this->state_space[current_state].first, 
  //                                   this->state_space[current_state].second.top()});
  // }

  if(current_state==0 && this->state_space[0].second.empty()) {
    return 0;
  } else {
    this->partial_embedding.insert({this->state_space[current_state].first, 
                                    this->state_space[current_state].second.top()});
  }

  return current_state;
}

size_t Backtrack::Jump(size_t current_state) {
  printf("[DEBUG] current_state = %ld\n", current_state);
  if (current_state == 1) { return current_state; }
  
  print_partial_embedding(partial_embedding, "[DEBUG] before jump");
  print_state_space(this->state_space);  
  
  size_t new_state = current_state;
  size_t jump_ratio = 2;
  size_t target_state = (current_state > jump_ratio) ? (current_state - current_state / jump_ratio) : (current_state - 1);
  // size_t target_state = current_state - 3;
  
  while(!this->state_space[new_state].second.empty()) {
    this->state_space[new_state].second.pop();
  }
  while (new_state > target_state) {
    // clear stack
    this->partial_embedding.erase(this->state_space[new_state].first);
    new_state--;
    this->partial_embedding.erase(this->state_space[new_state].first);
    while(!this->state_space[new_state].second.empty()) {
      this->state_space[new_state].second.pop();
    }
  }
  print_partial_embedding(partial_embedding, "[DEBUG] after jump"); 
  printf("[DEBUG] after jump new_state = %ld\n", new_state);
  new_state = this->GoBack(new_state);

  print_partial_embedding(partial_embedding, "[DEBUG] after jumpnGoback"); 
  print_state_space(this->state_space);  

  printf("[DEBUG] after jumpGoback new_state = %ld\n", new_state);
  return new_state;
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
    
    //if (cmu_size < min_cmu_size && cmu_size != 0) {
    if (cmu_size <= min_cmu_size) {
      min_cmu_size = cmu_size;
      next_u = u;
    }
     
    
  }

  if (min_cmu_size == INT32_MAX) {
    next_u = u;
  }

  print_u_info(query, cs, next_u, min_cmu_size);

  return next_u;
}

// Select root vertex with miminum critera value
// criteria = (# of v corresponding to u in cs) / (Degree of vertex)
size_t Backtrack::SelectRoot(const Graph &query, const CandidateSet &cs) {
  size_t cs_size = query.GetNumVertices();
  size_t criteria, root_number = 0, min = 100;
  size_t i, start_offset, end_offset;

  for (i = 0; i < cs_size; i++) {
    
    if (query.GetDegree(i) == 0) { break; }
    
    criteria = cs.GetCandidateSize(i) / query.GetDegree(i);
    if (criteria < min) {
      min = criteria;
      root_number = i;
    }
  }

  // Initialize extendable_vertex with child of root
  start_offset = query.GetNeighborStartOffset(root_number);
  end_offset = query.GetNeighborEndOffset(root_number);
  for (i = start_offset; i < end_offset; i++) {
    this->extendable_vertex.insert(query.GetNeighbor(i));
  }

  printf("===========[INSIGHT PLEASE] total vertices %d =========\n", query.GetNumVertices());
  print_u_info(query, cs, root_number, -1);
  return root_number;
}

bool Backtrack::PushU(size_t u, size_t current_state, const CandidateSet &cs, const Graph &data, const Graph &query) {

  size_t i, v_size;
  std::pair<size_t, size_t> p1;
  size_t v, num_v_in_stack = 0;

  std::stack <size_t> new_stack;
  
  v_size = cs.GetCandidateSize(u);
  
  this->state_space[current_state].first = u;
  
  // Find possible v-s in candidate set by checking embedding condition
  // Push it to state space

  for (i = 0; i < v_size; i++) {
    
    v = cs.GetCandidate(u, i);
    p1 = std::make_pair(u, v);
    
    if (EmbeddingCondition(data, query, p1)) {
      // this->state_space[current_state].second.push(v);
      new_stack.push(v);
      num_v_in_stack++;
    }
  }

  

  while(!new_stack.empty()){
    size_t stack_value = new_stack.top();
    new_stack.pop();

    if(!this->state_space[current_state].second.empty() && data.GetDegree(stack_value) >= data.GetDegree(this->state_space[current_state].second.top()))
    {
      this->state_space[current_state].second.push(stack_value);
    }
    else 
    {
      while(!this->state_space[current_state].second.empty() && data.GetDegree(this->state_space[current_state].second.top()) < data.GetDegree(stack_value))
      {
        size_t tmp = this->state_space[current_state].second.top();
        new_stack.push(tmp);
        this->state_space[current_state].second.pop();
      }
      this->state_space[current_state].second.push(stack_value);
    }
  }

  if (num_v_in_stack != 0) {
    this->partial_embedding.insert({u, this->state_space[current_state].second.top()});
  }

  return num_v_in_stack != 0;
}

void Backtrack::PrintnClear(size_t current_state) {
  
  size_t i, n = this->state_space.size();
  size_t *print_array = new size_t[n];
  
  // Fill print_array with top element of v-stacks from state_space (= Embedding)
  for (i = 0; i < n; i++) {
    if (i != current_state) {
      print_array[state_space[i].first] = this->state_space[i].second.top();
    }
  }

  while (!this->state_space[current_state].second.empty()) {
    
    print_array[state_space[current_state].first] = this->state_space[current_state].second.top();
    
    this->state_space[current_state].second.pop();
    this->count++;
    std::cout << "\nresult " << this->count << std::endl;
    for (i = 0; i < n; i++) {
      std::cout << print_array[i] << " ";
    }
  }
  std::cout << std::endl;
  delete[] print_array;
}




// Helper functions for Debugging
void print_set(std::set<size_t> question, const char* msg) {
  std::set<size_t>::iterator iter;
  printf("---[SET] print %s----\n", msg);
  for (iter = question.begin(); iter != question.end(); iter++) {
    printf("%ld ", *iter);
  }
  printf("\n---------------------------\n");
}

void print_partial_embedding(std::map<size_t, size_t> partial_embedding, const char* msg) {
  std::map<size_t,size_t>::iterator iter;
  printf("-------[PARTIAL_EMBED] %s--------\n", msg);
  printf("(u, v) = ");
  for (iter = partial_embedding.begin(); iter != partial_embedding.end(); iter++) {
    printf("(%ld, %ld) ", iter->first, iter->second);
  }
  printf("\n-------------------------------------\n");
}

void print_vector(std::vector<size_t> question, const char* msg) {
  std::vector<size_t>::iterator iter;
  printf("---[VECTOR] print %s----\n", msg);
  for (iter = question.begin(); iter != question.end(); iter++) {
    printf("%ld ", *iter);
  }
  printf("\n---------------------------\n");
}

void print_state_space(std::vector<std::pair<size_t, std::stack<size_t>>> question) {
  std::vector<std::pair<size_t, std::stack<size_t>>>::iterator iter;
  printf("----[STATE_SPACE]----------\n");
  int i = 0;
  for (iter = question.begin(); iter != question.end(); iter++, i++) {
    if (iter->second.empty()) {
      printf("([%d], %ld)->E  ", i, iter->first);
    } else {
      printf("([%d], %ld)->%ld  ", i, iter->first, iter->second.top());
    }
  }
  printf("\n-----------------------\n");
}

void check_synchronization(std::vector<std::pair<size_t, std::stack<size_t>>> state_space, 
                          std::map<size_t, size_t> partial_embedding) {
  std::vector<std::pair<size_t, std::stack<size_t>>>::iterator iter;
  size_t v_from_stack, u_from_stack, v_from_pe;
  for (iter = state_space.begin(); iter != state_space.end(); iter++) {
    if (!iter->second.empty()) {
      v_from_stack = iter->second.top();
      u_from_stack = iter->first;
      v_from_pe = partial_embedding.find(u_from_stack)->second;
      if(v_from_pe != v_from_stack) {
        printf("[ERROR] u(%ld) -> v_from_pe(%ld), v_from_stack(%ld)\n", u_from_stack, v_from_pe, v_from_stack);
        exit(0);
      }
    }  
  }
}

void print_u_info(const Graph &query, const CandidateSet &cs, size_t u, size_t cmu) {
  printf("u = %ld |  Deg = %ld | CandidateSize = %ld | CMU = %ld\n", u, query.GetDegree(u), cs.GetCandidateSize(u), cmu);
}
/**
 * @file backtrack.h
 *
 */

#ifndef BACKTRACK_H_
#define BACKTRACK_H_

#include "candidate_set.h"
#include "common.h"
#include "graph.h"

class Backtrack {
 public:
  Backtrack();
  ~Backtrack();

  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);

 private:
	//TODO: JinHwan
	size_t NextU(size_t current_u);
	bool EmbeddingCondition(const Graph &data, const Graph &query, std::pair<size_t, size_t> u_v);
	//TODO: JaeHyung
	size_t SelectRoot(const Graph &query, const CandidateSet &cs);
	bool PushU(size_t u); // true: v-stack is not empty
	void PrintnClear();

	size_t GoBack(size_t current_state);
	std::vector<std::pair<size_t, std::stack<size_t>*>> state_space;
	std::vector<std::pair<size_t, size_t> > partial_embedding;
   
};

#endif  // BACKTRACK_H_

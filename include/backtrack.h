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
  Backtrack(const Graph &query);
  ~Backtrack();

  void PrintAllMatches(const Graph &data, const Graph &query,
                       const CandidateSet &cs);

 private:
	size_t GoBack(size_t current_state);
	//TODO: JinHwan
	bool EmbeddingCondition(const Graph &data, const Graph &query, std::pair<size_t, size_t> u_v);
	// size_t NextU(size_t current_u);
	size_t NextU(const Graph &data, const Graph &query, const CandidateSet &cs); // Why need current_u??
	void DeleteExtendableVertex(size_t u, const Graph &query);
	//TODO: JaeHyung
	size_t SelectRoot(const Graph &query, const CandidateSet &cs);
	bool PushU(size_t u, size_t current_state, const CandidateSet &cs, const Graph &data, const Graph &query); // true: v-stack is not empty
	void PrintnClear(size_t current_state);

	std::vector<std::pair<size_t, std::stack<size_t>*> > state_space;
	std::map<size_t, size_t> partial_embedding;
  std::vector<size_t> extendable_vertex;

};

#endif  // BACKTRACK_H_

#include "backtrack.h"
#include "candidate_set.h"
#include "common.h"
#include "graph.h"
#include <sstream>

int main(int argc, char* argv[]) {
	
	if (argc < 5) {
    std::cout << "Usage: ./program <data graph file> <query graph file> <candidate set file>\n" << std::endl;
    return EXIT_FAILURE;
  }

  std::string data_file_name = argv[1];
  std::string query_file_name = argv[2];
  std::string candidate_set_file_name = argv[3];
  std::string result_file_name = argv[4];

  Graph data(data_file_name);
  Graph query(query_file_name, true);
  CandidateSet candidate_set(candidate_set_file_name);
	
	std::ifstream fin_lines(result_file_name);
	if (!fin_lines.is_open()) {
    std::cout << "Result file " << result_file_name << " not found!\n";
    exit(EXIT_FAILURE);
  }

	size_t num_lines = 0, tmp, i, j, array_size = query.GetNumVertices();;
	std::string one_line;
	std::stringstream line_stream;
	size_t *array = new size_t[array_size];
	char identifier;

	std::cout << "\n" << result_file_name << " Sanity check!\n";
	
	while (std::getline(fin_lines, one_line)) {
		// printf("%s", one_line.c_str());
		if (num_lines == 0) {
			line_stream.str(one_line);
			line_stream >> identifier;
			num_lines++;
			continue;
		}

		num_lines++;
		line_stream.str(one_line);
		line_stream >> identifier;
		// printf("%c, %d\n", identifier, num_lines);
		for (i = 0; i < array_size; i++) {
			line_stream >> tmp;
			array[i] = tmp;
		}
	}
	
	if (num_lines == 1) {
		printf("Fail to find embeddings\n");
		exit(0);
	} else if (num_lines == 100001) {
    printf("100000 Embeddings found!\n");
	} else {
		printf("%zu Embeddings found!\n", num_lines-1);
	}

	// std::ifstream fin(result_file_name);
	// if (!fin.is_open()) {
  //   std::cout << "Result file " << result_file_name << " not found!\n";
  //   exit(EXIT_FAILURE);
  // }

	// for(i = 0; i<array_size; i++) {
	// 	fin >> tmp;
	// 	array[i] = tmp;
	// }
	// fin.close();
 
	//조건 1 : injective
	//입력받은 v들끼리 중복 확인
	for (i = 0; i < array_size; i++) {
		for (j = 0; j < i; j++) {
			if (array[i] == array[j]) {
				printf("Not injective\n");
				printf("u1 : %zu, v1 : %zu, u2 : %zu, v2 : %zu\n", i, array[i], j, array[j]);
				printf("Not Valid\n");
				return 0;
			}
		}
	}

	//조건 2. Label 일치
	//입력 받은 v들이 순서대로 u0 u1 u2 에 대응되는 것들
	//따라서 i번째 v의 label == ui의 label 확인
	for (i = 0; i < array_size; i++) {
		if (query.GetLabel(i) != data.GetLabel(array[i])) {
			printf("Label not match\n");
			printf("u1 : %zu, v1 : %zu\n", i, array[i]);
			printf("Not Valid\n");
			return 0;
		}
	}    
    
	//조건 3. query의 모든 edge가 data에 mapping 된 채로 연결.
	for (i = 0; i < query.GetNumVertices(); i++){
		for(j = 0; j < i; j++) {
			if (query.IsNeighbor(i, j)) {
				if (!data.IsNeighbor(array[i], array[j])) {
					printf("Edge not match\n");
					printf("u1 : %zu, v1 : %zu, u2 : %zu, v2 : %zu\n", i, array[i], j, array[j]);
					printf("Not Valid\n");
					return 0;
				}
			}
		}
	}
	printf("Success!\n");

	delete[] array;
	return 0;
}
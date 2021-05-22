#include "backtrack.h"
#include "candidate_set.h"
#include "common.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    if (argc < 5) {
    std::cerr << "Usage: ./program <data graph file> <query graph file> "
                 "<candidate set file>\n";
    return EXIT_FAILURE;
  }
  std::string data_file_name = argv[1];
  std::string query_file_name = argv[2];
  std::string candidate_set_file_name = argv[3];
  std::string result_file_name = argv[4];


  Graph data(data_file_name);
  Graph query(query_file_name, true);
  CandidateSet candidate_set(candidate_set_file_name);
	std::ifstream fin(result_file_name);
	if (!fin.is_open()) {
    std::cout << "Result file " << result_file_name << " not found!\n";
    exit(EXIT_FAILURE);
  }


	size_t array_size = query.GetNumVertices();
	size_t tmp;
	size_t *array = new size_t[array_size];

	for(size_t i = 0; i<array_size; i++)
	{
		fin >> tmp;
		array[i] = tmp;
	}
	fin.close();
 
    //조건 1 : injective
    //입력받은 v들끼리 중복 확인
	for(size_t i = 0; i<array_size; i++)
	{
		for(size_t j = 0; j<i; j++)
			{
				if(array[i]==array[j]) 
				{
					printf("Not injective\n");
					printf("Not Valid\n");
					return 0;
				}
			}
	}

    //조건 2. Label 일치
    //입력 받은 v들이 순서대로 u0 u1 u2 에 대응되는 것들
    //따라서 i번째 v의 label == ui의 label 확인
	for(size_t i = 0; i<array_size; i++)
	{
		if(data.GetLabel(i)!=query.GetLabel(array[i]))
		{
			printf("Label not match\n");
			printf("Not Valid\n");
			return 0;
		}
	}    
    
    //조건 3. query의 모든 edge가 data에 mapping 된 채로 연결.
	for(size_t i = 0; i<query.GetNumVertices(); i++){
		for(size_t j = 0; j<i; j++)
		{
			if(query.IsNeighbor(i, j))
			{
				if(!data.IsNeighbor(array[i], array[j]))
				{
					printf("Edge not match\n");
					printf("Not Valid\n");
					return 0;
				}
			}
		}
	}
	printf("Success!\n");
}
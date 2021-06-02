mkdir build/result

# Execute hprd n1~n8
timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_n1.igraph ./candidate_set/lcc_hprd_n1.cs > ./build/result/lcc_hprd_n1_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_n1.igraph ./candidate_set/lcc_hprd_n1.cs ./build/result/lcc_hprd_n1_result.txt
rm ./build/result/lcc_hprd_n1_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_n3.igraph ./candidate_set/lcc_hprd_n3.cs > ./build/result/lcc_hprd_n3_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_n3.igraph ./candidate_set/lcc_hprd_n3.cs ./build/result/lcc_hprd_n3_result.txt
rm ./build/result/lcc_hprd_n3_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_n5.igraph ./candidate_set/lcc_hprd_n5.cs > ./build/result/lcc_hprd_n5_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_n5.igraph ./candidate_set/lcc_hprd_n5.cs ./build/result/lcc_hprd_n5_result.txt
rm ./build/result/lcc_hprd_n5_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_n8.igraph ./candidate_set/lcc_hprd_n8.cs > ./build/result/lcc_hprd_n8_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_n8.igraph ./candidate_set/lcc_hprd_n8.cs ./build/result/lcc_hprd_n8_result.txt
rm ./build/result/lcc_hprd_n8_result.txt


# Execute hprd s1~s8
timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_s1.igraph ./candidate_set/lcc_hprd_s1.cs > ./build/result/lcc_hprd_s1_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_s1.igraph ./candidate_set/lcc_hprd_s1.cs ./build/result/lcc_hprd_s1_result.txt
rm ./build/result/lcc_hprd_s1_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_s3.igraph ./candidate_set/lcc_hprd_s3.cs > ./build/result/lcc_hprd_s3_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_s3.igraph ./candidate_set/lcc_hprd_s3.cs ./build/result/lcc_hprd_s3_result.txt
rm ./build/result/lcc_hprd_s3_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_s5.igraph ./candidate_set/lcc_hprd_s5.cs > ./build/result/lcc_hprd_s5_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_s5.igraph ./candidate_set/lcc_hprd_s5.cs ./build/result/lcc_hprd_s5_result.txt
rm ./build/result/lcc_hprd_s5_result.txt

timeout 60 ./build/main/program ./data/lcc_hprd.igraph ./query/lcc_hprd_s8.igraph ./candidate_set/lcc_hprd_s8.cs > ./build/result/lcc_hprd_s8_result.txt
./build/sanitycheck/sanity ./data/lcc_hprd.igraph ./query/lcc_hprd_s8.igraph ./candidate_set/lcc_hprd_s8.cs ./build/result/lcc_hprd_s8_result.txt
rm ./build/result/lcc_hprd_s8_result.txt


# Execute human n1~n8
timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_n1.igraph ./candidate_set/lcc_human_n1.cs > ./build/result/lcc_human_n1_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_n1.igraph ./candidate_set/lcc_human_n1.cs ./build/result/lcc_human_n1_result.txt
rm ./build/result/lcc_human_n1_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_n3.igraph ./candidate_set/lcc_human_n3.cs > ./build/result/lcc_human_n3_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_n3.igraph ./candidate_set/lcc_human_n3.cs ./build/result/lcc_human_n3_result.txt
rm ./build/result/lcc_human_n3_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_n5.igraph ./candidate_set/lcc_human_n5.cs > ./build/result/lcc_human_n5_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_n5.igraph ./candidate_set/lcc_human_n5.cs ./build/result/lcc_human_n5_result.txt
rm ./build/result/lcc_human_n5_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_n8.igraph ./candidate_set/lcc_human_n8.cs > ./build/result/lcc_human_n8_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_n8.igraph ./candidate_set/lcc_human_n8.cs ./build/result/lcc_human_n8_result.txt
rm ./build/result/lcc_human_n8_result.txt


# Execute human s1~s8
timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_s1.igraph ./candidate_set/lcc_human_s1.cs > ./build/result/lcc_human_s1_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_s1.igraph ./candidate_set/lcc_human_s1.cs ./build/result/lcc_human_s1_result.txt
rm ./build/result/lcc_human_s1_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_s3.igraph ./candidate_set/lcc_human_s3.cs > ./build/result/lcc_human_s3_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_s3.igraph ./candidate_set/lcc_human_s3.cs ./build/result/lcc_human_s3_result.txt
rm ./build/result/lcc_human_s3_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_s5.igraph ./candidate_set/lcc_human_s5.cs > ./build/result/lcc_human_s5_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_s5.igraph ./candidate_set/lcc_human_s5.cs ./build/result/lcc_human_s5_result.txt
rm ./build/result/lcc_human_s5_result.txt

timeout 60 ./build/main/program ./data/lcc_human.igraph ./query/lcc_human_s8.igraph ./candidate_set/lcc_human_s8.cs > ./build/result/lcc_human_s8_result.txt
./build/sanitycheck/sanity ./data/lcc_human.igraph ./query/lcc_human_s8.igraph ./candidate_set/lcc_human_s8.cs ./build/result/lcc_human_s8_result.txt
rm ./build/result/lcc_human_s8_result.txt


# Execute yeast n1~n8
timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_n1.igraph ./candidate_set/lcc_yeast_n1.cs > ./build/result/lcc_yeast_n1_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_n1.igraph ./candidate_set/lcc_yeast_n1.cs ./build/result/lcc_yeast_n1_result.txt
rm ./build/result/lcc_yeast_n1_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_n3.igraph ./candidate_set/lcc_yeast_n3.cs > ./build/result/lcc_yeast_n3_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_n3.igraph ./candidate_set/lcc_yeast_n3.cs ./build/result/lcc_yeast_n3_result.txt
rm ./build/result/lcc_yeast_n3_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_n5.igraph ./candidate_set/lcc_yeast_n5.cs > ./build/result/lcc_yeast_n5_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_n5.igraph ./candidate_set/lcc_yeast_n5.cs ./build/result/lcc_yeast_n5_result.txt
rm ./build/result/lcc_yeast_n5_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_n8.igraph ./candidate_set/lcc_yeast_n8.cs > ./build/result/lcc_yeast_n8_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_n8.igraph ./candidate_set/lcc_yeast_n8.cs ./build/result/lcc_yeast_n8_result.txt
rm ./build/result/lcc_yeast_n8_result.txt


# Execute yeast s1~s8
timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_s1.igraph ./candidate_set/lcc_yeast_s1.cs > ./build/result/lcc_yeast_s1_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_s1.igraph ./candidate_set/lcc_yeast_s1.cs ./build/result/lcc_yeast_s1_result.txt
rm ./build/result/lcc_yeast_s1_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_s3.igraph ./candidate_set/lcc_yeast_s3.cs > ./build/result/lcc_yeast_s3_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_s3.igraph ./candidate_set/lcc_yeast_s3.cs ./build/result/lcc_yeast_s3_result.txt
rm ./build/result/lcc_yeast_s3_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_s5.igraph ./candidate_set/lcc_yeast_s5.cs > ./build/result/lcc_yeast_s5_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_s5.igraph ./candidate_set/lcc_yeast_s5.cs ./build/result/lcc_yeast_s5_result.txt
rm ./build/result/lcc_yeast_s5_result.txt

timeout 60 ./build/main/program ./data/lcc_yeast.igraph ./query/lcc_yeast_s8.igraph ./candidate_set/lcc_yeast_s8.cs > ./build/result/lcc_yeast_s8_result.txt
./build/sanitycheck/sanity ./data/lcc_yeast.igraph ./query/lcc_yeast_s8.igraph ./candidate_set/lcc_yeast_s8.cs ./build/result/lcc_yeast_s8_result.txt
rm ./build/result/lcc_yeast_s8_result.txt
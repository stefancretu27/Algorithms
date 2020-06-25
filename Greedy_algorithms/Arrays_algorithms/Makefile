CFLAGS = -std=c++17 -Wall -g
CC = g++
ARRAY_GREEDY_SOURCES = min_product_subset.cpp max_product_subset.cpp max_sum_k_negations.cpp max_sum_elementMultipliedWithIndex.cpp maxSum_increasingOrderElementsFromNArrays.cpp maxHeightPyramid.cpp 
ARRAY_GREEDY_SOURCES2 = maxSum_absoluteDifferencesOfConsecutiveElements.cpp maxDiff_sumsOfTwoArrayPartitions.cpp minSum_prodsElementsTwoArrays.cpp minSumFromMinValueOfPairs.cpp minChangesNonIncreasingArray.cpp

all:
	$(CC) $(CFLAGS) main.cpp $(ARRAY_GREEDY_SOURCES) $(ARRAY_GREEDY_SOURCES2) -o array_greedy.bin
	
clean:
	rm *.bin

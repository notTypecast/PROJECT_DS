cmake_minimum_required (VERSION 3.17)
project (ProjectDS)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/agn.us.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/agn.us.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/ainv.us.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/ainv.us.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/ale.us.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/ale.us.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/gumbel.rnd.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/gumbel.rnd.txt COPYONLY)
add_executable (ProjectDS src/main.cpp include/algo.h src/algo/mergeSort.cpp src/algo/quickSort.cpp include/utils.h include/algo.h src/utils/CSVReader.cpp include/exercises.h src/exercises.cpp src/utils/stock.cpp src/utils/timer.tpp include/ds.h src/ds/StockHeap.cpp src/algo/heapSort.cpp src/algo/countingSort.cpp src/algo/binarySearch.cpp src/algo/interpolationSearch.cpp src/utils/date.cpp src/algo/binaryInterpolationSearch.cpp src/algo/improvedBIS.cpp src/utils/string.cpp src/ds/HashTable.tpp)
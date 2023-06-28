cmake_minimum_required(VERSION 3.13)

project(codestuff_cplpusplus)

#get googletest
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0)
#googletest_POPULATED
#googletest_SOURCE_DIR
#googletest_BUILD_DIR
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

FetchContent_GetProperties(googletest)

include_directories("${CMAKE_SOURCE_DIR}/BinarySearch"
                    "${CMAKE_SOURCE_DIR}/NextGreat"
                    "${CMAKE_SOURCE_DIR}/StringsFun"
                    "${CMAKE_SOURCE_DIR}/HashTable"
                    "${CMAKE_SOURCE_DIR}/SingleLinkedList")

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/BinarySearch/binary_search.cpp"
                  "${CMAKE_SOURCE_DIR}/NextGreat/next_great.cpp"
                  "${CMAKE_SOURCE_DIR}/StringsFun/strings_fun.cpp"
                  "${CMAKE_SOURCE_DIR}/HashTable/hash_table.cpp"
                  "${CMAKE_SOURCE_DIR}/SingleLinkedList/single_linked_list.cpp")

file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/BinarySearch/test/binary_search_test.cpp"
                       "${CMAKE_SOURCE_DIR}/NextGreat/test/next_great_test.cpp"
                       "${CMAKE_SOURCE_DIR}/StringsFun/test/strings_fun_test.cpp"
                       "${CMAKE_SOURCE_DIR}/HashTable/test/hash_table_test.cpp"
                       "${CMAKE_SOURCE_DIR}/SingleLinkedList/test/single_linked_list_test.cpp")


add_library(main_lib STATIC ${SOURCES})

add_executable(mainApp main.cpp)
target_link_libraries(mainApp main_lib)

add_executable(testRunner ${TEST_SOURCES})
target_link_libraries(testRunner main_lib gtest_main gmock_main)
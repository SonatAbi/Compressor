cmake_minimum_required(VERSION 3.2)
project(P5 CXX)
  
enable_testing()
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/deps/cxxtest)

find_package(CxxTest REQUIRED)

include_directories(${CXXTEST_INCLUDE_DIR})	
CXXTEST_ADD_TEST(test_treap_bst test_instructor_treap.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/test_instructor_treap.h abstract_bst.h treap_bst.h treap_bst.txx)
set_property(TARGET test_treap_bst PROPERTY CXX_STANDARD 11)

add_executable(compress compress.cpp abstract_bst.h treap_bst.h treap_bst.txx)
set_property(TARGET compress PROPERTY CXX_STANDARD 11)

add_test(compress1 compress ${CMAKE_CURRENT_SOURCE_DIR}/input.txt compressed.bin)
add_test(decompress1 compress "-d" compressed.bin output.txt)

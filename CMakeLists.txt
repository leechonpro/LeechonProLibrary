cmake_minimum_required(VERSION 3.10)

project(LPL CXX)
# 헤더 경로 설정
message(${PROJECT_SOURCE_DIR})
set( LPLCODE 
source/utility/LUtil.cpp 
source/utility/CLFile.cpp 
source/multiThreading/ILThread.cpp 
source/dataStructure/CLBuffer.cpp
)
# Protobuf 및 gRPC 라이브러리 찾기

add_library( LPL ${LPLCODE} )

target_include_directories(LPL PRIVATE
  ./header
)
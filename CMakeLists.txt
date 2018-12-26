PROJECT(CPPJIEBA LANGUAGES C CXX)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps
  ${PROJECT_SOURCE_DIR}/include)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "/usr/local/cppjieba" CACHE PATH "default install path" FORCE )
endif()

ADD_DEFINITIONS(-O3 -Wall -g)
IF(APPLE) # mac os
    ADD_DEFINITIONS(-std=c++0x)
endif()

# cmake .. -DENC=GBK
# IF (DEFINED ENC)
#     ADD_DEFINITIONS(-DCPPJIEBA_${ENC})
# ENDIF()

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 \
    -Wall -Wno-sign-compare -Wno-unused-local-typedefs \
    -Wno-deprecated-declarations -Winit-self -Wno-deprecated-register \
    -Wno-uninitialized \
    -msse -msse2 -pthread \
    -DHAVE_EXECINFO_H=1 -DHAVE_CXXABI_H \
    -g")

    ADD_LIBRARY(jieba_pinyin SHARED ${PROJECT_SOURCE_DIR}/include/cppjieba/Jieba.cpp)
target_link_libraries(jieba_pinyin m pthread dl)
ADD_SUBDIRECTORY(deps)
ADD_SUBDIRECTORY(test)

ENABLE_TESTING()
ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
ADD_TEST(NAME ./load_test COMMAND ./load_test)
ADD_TEST(NAME ./demo COMMAND ./demo)

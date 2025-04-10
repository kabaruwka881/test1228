cmake_minimum_required(VERSION 3.16)
project(t LANGUAGES CXX) 

set(SOURCES t.cpp)
set(INC_PATH /usr/local/include)
set(LIB_PATH /usr/local/lib)

add_library(MyList SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(MyList PROPERTIES
  IMPORTED_LOCATION "${LIB_PATH}/MyList/libMyList.dylib"
  INTERFACE_INCLUDE_DIRECTORIES "${INC_PATH}/MyList"
)

add_executable(app ${SOURCES})
target_link_libraries(app MyList) # also adds the required include path
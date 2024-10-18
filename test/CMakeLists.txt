cmake_minimum_required(VERSION 3.5.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS ON)  

set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Building in Debug mode")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Building in Release mode")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")
endif()

# set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SPDLOG_INCLUDE "D:/00.Lib/spdlog/include")
# set(HDF5_INCLUDE "D:\\ProgramLib\\HDF5-1.14.3-win64\\include")
# set(HDF5_LIB "D:/ProgramLib/HDF5-1.14.3-win64/lib")

# test 
set(QUEUE ${CMAKE_CURRENT_SOURCE_DIR}/../queue)
set(SMARTPTR ${CMAKE_CURRENT_SOURCE_DIR}/../smart_ptr)
set(CONTAINER ${CMAKE_CURRENT_SOURCE_DIR}/../container)
set(THREAD ${CMAKE_CURRENT_SOURCE_DIR}/../thread)
set(DATASTRUCTURE ${CMAKE_CURRENT_SOURCE_DIR}/../dataStructure)
set(ALGRITHM ${CMAKE_CURRENT_SOURCE_DIR}/../algrithm)


include_directories(${QUEUE})
include_directories(${SMARTPTR}
                    ${CONTAINER}
                    ${THREAD}
                    ${DATASTRUCTURE}
                    ${ALGRITHM}
)

# test end

set(SOURCE main.cpp
          ../container/unorder.cpp
          ../dataStructure/myHashTable.cpp
          ../algrithm/tSort.cpp
          ../algrithm/tHeapSort.cpp
)
add_executable(test ${SOURCE})

include_directories(${SPDLOG_INCLUDE})
# include_directories(${HDF5_INCLUDE})

# target_link_libraries(test ${HDF5_LIB}/hdf5.lib
#                           ${HDF5_LIB}/hdf5_tools.lib
#                           ${HDF5_LIB}/hdf5_cpp.lib
#                           ${HDF5_LIB}/hdf5_hl.lib
#                           ${HDF5_LIB}/hdf5_hl_cpp.lib)

# target_compile_options(test PRIVATE
    # $<$<CONFIG:Release>:--DNDEBUG>
    # $<$<CONFIG:Debug>:-DDEBUG>
    # $<$<CONFIG:Release>:-DNDEBUG>
    # if (MSVC)
    #   add_compile_options(/std:c++17 /MP)
    # elseif(CMAKE_COMPILER_IS_GNUCXX)
    #   add_compile_options(-std=c++17)
    # endif()
    # $<$<CXX_COMPILER_ID:MSVC>:/O2>  # MSVC 编译器下启用优化
    # $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2>  # 其他编译器下启用优化
# )
if (MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od")
endif()
  

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test PROPERTY CXX_STANDARD 17)
endif()


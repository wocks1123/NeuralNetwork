# Target name
set(target CudaTest)

option(USE_CUDA "Use CUDA" OFF)


if (USE_CUDA)
    message("User CUDA!")
	find_package(CUDA)
	set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)
	message(STATUS "Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")
    set(CDUA_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cu)
	set(CUDA_NVCC_FLAGS
        ${CUDA_NVCC_FLAGS}
        # -std=c++11
        # -O3 -gencode arch=compute_52,code=sm_52
        )
else()
    message("No CUDA... in CudaTest")
endif()

# Define
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)




#set(CMAKE_C_FLAGS -m32)
#set(CMAKE_CXX_FLAGS -m32)

# Includes
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries
)

# Sources
file(GLOB header_dir
        ${root_dir}/Includes)

file(GLOB_RECURSE headers
        ${header_dir}/*.cuh
        ${header_dir}/*.hpp
        )

file(GLOB_RECURSE sources
        # ${CMAKE_CURRENT_SOURCE_DIR}/*.cu
        ${CDUA_SRCS}
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        )

# Build library
if (USE_CUDA)
	cuda_add_library(${target}
		${sources})
else()
	add_library(${target}
		${sources})
endif()
#cuda_add_executable(${target}
#                ${sources})

# Project options
set_target_properties(${target}
        PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
        CUDA_SEPERABLE_COMPILATION ON
        )

# Compile options
target_compile_options(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_COMPILE_OPTIONS}
        INTERFACE
        )

target_link_libraries(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_LINKER_OPTIONS}
        ${DEFAULT_LIBRARIES}
        ${CUDA_LIBRARIES}

        INTERFACE
        )

# Install
# install(TARGETS ${target} DESTINATION lib)
install(TARGETS ${target} DESTINATION exe)
install(DIRECTORY ${header_dir} DESTINATION include)
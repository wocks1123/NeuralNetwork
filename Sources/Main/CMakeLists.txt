# Target name
set(target Main)

option(USE_CUDA "Use CUDA" OFF)

if (USE_CUDA)
	message("use cuda ON")
	find_package(CUDA)
	set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)
	set(CUDA_NVCC_FLAGS
			${CUDA_NVCC_FLAGS}
			)
else()
	message("use cuda OFF")
endif()

# Define
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)




# Includes
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries
)

# set(CMAKE_C_FLAGS -m64)
# set(CMAKE_CXX_FLAGS -m64)

# Sources
file(GLOB header_dir
        ${root_dir}/Includes)

file(GLOB_RECURSE headers
        ${header_dir}/*.hpp
		${header_dir}/*.h
		)

file(GLOB_RECURSE sources
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} )

# Build Executable
if (USE_CUDA)
	cuda_add_executable(${target}
			${sources}
			)
else()
	message("use cuda OFF")
	add_executable(${target}
			${sources}
			)
endif()


# Project options
set_target_properties(${target}
		PROPERTIES
		${DEFAULT_PROJECT_OPTIONS}
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
		Exclam
		CudaTest
        ${DEFAULT_LINKER_OPTIONS}
        ${DEFAULT_LIBRARIES}

        INTERFACE
        )

# Install
install(TARGETS ${target} DESTINATION exe)
install(DIRECTORY ${header_dir} DESTINATION include)
add_library(data_structures
	vector.cpp
	oa_hashmap.cpp
)

target_include_directories(data_structures
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

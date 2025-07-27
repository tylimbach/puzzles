cmake_minimum_required(VERSION 3.14)

add_library(data_structures INTERFACE)

target_sources(data_structures
	INTERFACE
        vector.h
        oa_hashmap.h
)

target_include_directories(data_structures
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(data_structures
	INTERFACE
        ${Boost_LIBRARIES}
)

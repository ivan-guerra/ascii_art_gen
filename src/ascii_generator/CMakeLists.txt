cmake_minimum_required(VERSION 3.25)

find_package(Boost REQUIRED)

project(ascii_generator DESCRIPTION "ASCII Art Generation Utility"
                        LANGUAGES   CXX
)

add_library(${PROJECT_NAME} STATIC ascii_generator.cc)

target_include_directories(${PROJECT_NAME} SYSTEM
    INTERFACE Boost::boost
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC -ljpeg
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${AAG_INCLUDE_DIR}/ascii_generator
)

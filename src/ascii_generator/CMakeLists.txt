cmake_minimum_required(VERSION 3.25)

find_package(X11 REQUIRED)

project(ascii_generator DESCRIPTION "ASCII Art Generation Utility"
                        LANGUAGES   CXX
)

add_library(${PROJECT_NAME} STATIC ascii_generator.cc)

target_include_directories(${PROJECT_NAME} SYSTEM
    PRIVATE ${X11_INCLUDE_DIR}
    PUBLIC ${AAG_INCLUDE_DIR}/CImg
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${AAG_INCLUDE_DIR}/ascii_generator
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${X11_LIBRARIES}
)

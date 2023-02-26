cmake_minimum_required(VERSION 3.11...3.25)

find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(Boost REQUIRED)

project(ascii_generator DESCRIPTION "ASCII Art Generation Utility"
                        LANGUAGES   CXX
)

add_library(${PROJECT_NAME} STATIC ascii_generator.cc)

target_link_libraries(${PROJECT_NAME}
    PRIVATE JPEG::JPEG
            PNG::PNG
            Boost::boost
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${AAG_INCLUDE_DIR}/ascii_generator
)

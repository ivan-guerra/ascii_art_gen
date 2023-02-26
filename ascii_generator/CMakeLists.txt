cmake_minimum_required(VERSION 3.25)

project(asciigen DESCRIPTION "Image to ASCII Art Generator"
                 LANGUAGES   CXX
)

add_executable(${PROJECT_NAME} generator.cc)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ascii_generator
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${AAG_BIN_DIR}
)

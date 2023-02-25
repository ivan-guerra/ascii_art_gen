cmake_minimum_required(VERSION 3.25)

project(asciigen DESCRIPTION "ASCII Art Generator"
                 LANGUAGES   CXX
)

add_executable(${PROJECT_NAME} generator.cc)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${AAG_BIN_DIR}
)

find_package(re2c REQUIRED)

add_re2c_target(xylo_lexer lexer.in.cpp)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

target_sources(xylo PRIVATE ${HEADERS} ${SRC})
target_link_libraries(xylo PRIVATE xylo_lexer)
target_sources(xylod PRIVATE ${HEADERS} ${SRC})
target_link_libraries(xylod PRIVATE xylo_lexer)

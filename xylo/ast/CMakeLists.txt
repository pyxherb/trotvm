find_package(re2c REQUIRED)

add_re2c_target(xyloLexer lexer.in.cpp ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

target_sources(xylo PRIVATE ${HEADERS} ${SRC})
target_link_libraries(xylo PRIVATE xyloLexer)
target_sources(xylod PRIVATE ${HEADERS} ${SRC})
target_link_libraries(xylod PRIVATE xyloLexer)

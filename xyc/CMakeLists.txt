file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

add_executable(xyc)
target_sources(xyc PRIVATE ${HEADERS} ${SRC})
target_link_libraries(xyc PRIVATE xylo)

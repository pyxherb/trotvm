find_package(re2c REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

target_sources(xylo PRIVATE ${HEADERS} ${SRC})
target_sources(xylod PRIVATE ${HEADERS} ${SRC})

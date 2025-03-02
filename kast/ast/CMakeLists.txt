find_package(re2c REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

target_sources(kast PRIVATE ${HEADERS} ${SRC})
target_sources(kastd PRIVATE ${HEADERS} ${SRC})

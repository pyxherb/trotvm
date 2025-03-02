find_package(peff REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

add_library(kast STATIC)
target_compile_definitions(kast PRIVATE TROTVM_IS_BUILDING=1)
set_property(TARGET kast PROPERTY CXX_STANDARD 17)
target_include_directories(kast PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(kast PUBLIC peff_containers_static)
set_target_properties(kast PROPERTIES
    VERSION ${PROJECT_VERSION}
)

add_library(kastd SHARED)
target_compile_definitions(kastd PRIVATE TROTVM_IS_BUILDING=1)
target_compile_definitions(kastd PUBLIC TROTVM_BUILD_SHARED=1)
set_property(TARGET kastd PROPERTY CXX_STANDARD 17)
set_property(TARGET kastd PROPERTY PUBLIC_HEADER "")
target_include_directories(kastd PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(kast PUBLIC peff_containers)
set_target_properties(kastd PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    ARCHIVE FALSE
)

target_sources(kast PRIVATE ${HEADERS} ${SRC})
target_sources(kastd PRIVATE ${HEADERS} ${SRC})

configure_file(
    config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kast/generated)

if(${TROTVM_ENABLE_DEBUGGER})
endif()

install(TARGETS kast kastd
    EXPORT kastTargets
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    RUNTIME DESTINATION bin
)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kast)

add_subdirectory("ast")

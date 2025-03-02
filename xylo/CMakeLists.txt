find_package(peff REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

add_library(xylo STATIC)
target_compile_definitions(xylo PRIVATE TROTVM_IS_BUILDING=1)
set_property(TARGET xylo PROPERTY CXX_STANDARD 17)
target_include_directories(xylo PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(xylo PUBLIC peff_containers_static)
set_target_properties(xylo PROPERTIES
    VERSION ${PROJECT_VERSION}
)

add_library(xylod SHARED)
target_compile_definitions(xylod PRIVATE TROTVM_IS_BUILDING=1)
target_compile_definitions(xylod PUBLIC TROTVM_BUILD_SHARED=1)
set_property(TARGET xylod PROPERTY CXX_STANDARD 17)
set_property(TARGET xylod PROPERTY PUBLIC_HEADER "")
target_include_directories(xylod PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(xylo PUBLIC peff_containers)
set_target_properties(xylod PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    ARCHIVE FALSE
)

target_sources(xylo PRIVATE ${HEADERS} ${SRC})
target_sources(xylod PRIVATE ${HEADERS} ${SRC})

configure_file(
    config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/xylo/generated)

if(${TROTVM_ENABLE_DEBUGGER})
endif()

install(TARGETS xylo xylod
    EXPORT xyloTargets
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    RUNTIME DESTINATION bin
)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/xylo)

add_subdirectory("ast")

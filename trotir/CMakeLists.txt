find_package(peff REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

add_library(trotir STATIC)
target_compile_definitions(trotir PRIVATE TROTIR_IS_BUILDING=1)
set_property(TARGET trotir PROPERTY CXX_STANDARD 17)
target_include_directories(trotir PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(trotir PUBLIC peff_containers_static)
set_target_properties(trotir PROPERTIES
    VERSION ${PROJECT_VERSION}
)

add_library(trotird SHARED)
target_compile_definitions(trotird PRIVATE TROTIR_IS_BUILDING=1)
target_compile_definitions(trotird PUBLIC TROTIR_BUILD_SHARED=1)
set_property(TARGET trotird PROPERTY CXX_STANDARD 17)
set_property(TARGET trotird PROPERTY PUBLIC_HEADER "")
target_include_directories(trotird PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(trotird PUBLIC peff_containers)
set_target_properties(trotird PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    ARCHIVE FALSE
)

target_sources(trotir PRIVATE ${HEADERS} ${SRC})
target_sources(trotird PRIVATE ${HEADERS} ${SRC})

set(TROTIR_STACK_MAX 1048576 CACHE STRING "Maximum stack size for trotir runtime")
set(TROTIR_NATIVE_STACK_MAX 1048576 CACHE STRING "Maximum native stack size for trotir runtime")
set(TROTIR_WITH_STDLIB TRUE CACHE BOOL "With trotir standard library")
set(TROTIR_WITH_AOT TRUE CACHE BOOL "With AOT execution support")
set(TROTIR_ENABLE_DEBUGGER TRUE CACHE BOOL "Enable runtime debugger")

configure_file(
    config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/trotir/generated)

if(${TROTIR_ENABLE_DEBUGGER})
endif()

install(TARGETS trotir trotird
    EXPORT trotirTargets
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    RUNTIME DESTINATION bin
)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/trotir)

find_package(peff REQUIRED)

file(GLOB HEADERS *.h *.hh)
file(GLOB SRC *.c *.cc)

add_library(trotvm STATIC)
target_compile_definitions(trotvm PRIVATE TROTVM_IS_BUILDING=1)
set_property(TARGET trotvm PROPERTY CXX_STANDARD 17)
target_include_directories(trotvm PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(trotvm PUBLIC peff_containers_static)
set_target_properties(trotvm PROPERTIES
    VERSION ${PROJECT_VERSION}
)

add_library(trotvmd SHARED)
target_compile_definitions(trotvmd PRIVATE TROTVM_IS_BUILDING=1)
target_compile_definitions(trotvmd PUBLIC TROTVM_BUILD_SHARED=1)
set_property(TARGET trotvmd PROPERTY CXX_STANDARD 17)
set_property(TARGET trotvmd PROPERTY PUBLIC_HEADER "")
target_include_directories(trotvmd PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> $<INSTALL_INTERFACE:include/>)
target_link_libraries(trotvm PUBLIC peff_containers)
set_target_properties(trotvmd PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    ARCHIVE FALSE
)

target_sources(trotvm PRIVATE ${HEADERS} ${SRC})
target_sources(trotvmd PRIVATE ${HEADERS} ${SRC})

set(TROTVM_STACK_MAX 1048576 CACHE STRING "Maximum stack size for trotvm runtime")
set(TROTVM_NATIVE_STACK_MAX 1048576 CACHE STRING "Maximum native stack size for trotvm runtime")
set(TROTVM_WITH_STDLIB TRUE CACHE BOOL "With trotvm standard library")
set(TROTVM_WITH_AOT TRUE CACHE BOOL "With AOT execution support")
set(TROTVM_ENABLE_DEBUGGER TRUE CACHE BOOL "Enable runtime debugger")

configure_file(
    config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/generated/config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/trotvm/generated)

if(${TROTVM_ENABLE_DEBUGGER})
endif()

install(TARGETS trotvm trotvmd
    EXPORT trotvmTargets
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    RUNTIME DESTINATION bin
)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/trotvm)

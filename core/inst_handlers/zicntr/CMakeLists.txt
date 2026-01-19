project(Pegasus)

file(GLOB SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_library(rvzicntr
    OBJECT
    ${SOURCES}
)
add_dependencies(rvzicntr AutogenArchFiles)
target_link_libraries(rvzicntr PUBLIC pegasuslibs)

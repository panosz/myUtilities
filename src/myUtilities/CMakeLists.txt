

add_library(${PROJECT_NAME} SHARED src/myUtilities.cpp include/myUtilities.hpp include/linspace.hpp src/linspace.cpp include/interval.hpp src/interval.cpp include/wrap.hpp src/wrap.cpp include/zero_crossing.hpp include/data_reading.hpp src/data_reading.cpp)



target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
        -Wconversion -Wsign-conversion -Wmisleading-indentation
        -Wduplicated-cond -Wduplicated-branches -Wlogical-op
        -Wnull-dereference -Wuseless-cast -Wdouble-promotion
        -Wformat=2
        $<$<CONFIG:Debug>:
        -g
        >
        $<$<CONFIG:Release>:
        -O2
        -frounding-math
        -march=native>

        )




set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};$ENV{HOME}")


find_package(Boost REQUIRED Regex)

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost Boost::Regex)



target_include_directories(
        ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

install (
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

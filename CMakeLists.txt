cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(result LANGUAGES CXX)

add_library(result INTERFACE)

target_include_directories(result INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(DIRECTORY include/result DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/result)

install(TARGETS result EXPORT resultTargets)

install(EXPORT resultTargets
    FILE resultTargets.cmake
    NAMESPACE result::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/result
)

# Enable / Disable tests
option(RESULT_BUILD_TESTS "Enable result tests." ON)

if(RESULT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
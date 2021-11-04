cmake_minimum_required(VERSION 3.7)
project(dde-calendar-test)

set(ASAN_CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

ADD_SUBDIRECTORY(dde-calendar-client-test)

ADD_SUBDIRECTORY(dde-calendar-service-test)

ADD_SUBDIRECTORY(dde-online-accounts-test)

include_directories(third-party_stub)

add_custom_target(test)
add_custom_command(TARGET test
    COMMAND echo " =================== CREAT LCOV REPROT BEGIN ==================== "
    COMMAND ${CMAKE_BINARY_DIR}/tests/dde-calendar-client-test/dde-calendar-test
    COMMAND ${CMAKE_BINARY_DIR}/tests/dde-calendar-service-test/dde-calendar-service-test
    COMMAND ${CMAKE_BINARY_DIR}/tests/dde-online-accounts-test/dde-online-accounts-daemon-test/dde-online-accounts-daemon-test
    COMMAND ${CMAKE_BINARY_DIR}/tests/dde-online-accounts-test/dde-online-accounts-plugin-test/dde-online-accounts-plugin-test
    COMMAND ${CMAKE_BINARY_DIR}/tests/dde-online-accounts-test/dde-online-accounts-lib-test/dde-online-accounts-lib-test
    COMMAND echo " =================== TEST END ==================== "
    )

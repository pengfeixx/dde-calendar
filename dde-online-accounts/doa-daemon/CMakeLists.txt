cmake_minimum_required(VERSION 3.7)

if (NOT DEFINED VERSION)
     message(WARNING "Not defined version ,about dialog version set 1.2.2")
    set(VERSION 1.2.2)
endif ()

project(dde-online-accounts-daemon)

set(CMAKE_INSTALL_PREFIX /usr)
set(APP_SERVICE "assets/dde-online-accounts-daemon.service")
set(APP_DBUS_SERVICE "assets/com.dde.onlineaccount.service")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--as-needed -fPIE")
set(CMAKE_EXE_LINKER_FLAGS "-pie")


if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "sw_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mieee")
elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ftree-vectorize -march=loongson3a -mhard-float -mno-micromips -mno-mips16 -flax-vector-conversions -mloongson-ext2 -mloongson-mmi -Wl,--as-needed")
endif ()

#compile flags
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

  # Enable Qt builtin debug mode
  add_definitions("-DQT_MESSAGELOGCONTEXT")
else()
  # -Wl, -O2 Enable linker optimizations
  # -Wl, --gc-sections Remove unused code resulting from -fdsta-sections and
  # -ffunction-sections
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections")
endif()

#安全编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-strong -D_FORTITY_SOURCE=1 -z noexecstack -pie -fPIC -z lazy")

find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5DBus REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5LinguistTools)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)
find_package(Qt5Network REQUIRED)

pkg_search_module(DtkGui REQUIRED dtkgui)
pkg_search_module(DtkCore REQUIRED dtkcore)

include_directories(${DtkWidget_INCLUDE_DIRS})
include_directories(${DtkGui_INCLUDE_DIRS})
include_directories(${DtkCore_INCLUDE_DIRS})
include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

set(LINK_LIBS
    Qt5::Core
    Qt5::DBus
    Qt5::Sql
    Qt5::Widgets
    Qt5::Network
    ${DtkGui_LDFLAGS}
    ${DtkCore_LDFLAGS}
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(../doa-lib/src)


set(CONTROLLER_FILES
src/controller/doaqqprovider.cpp
src/controller/doaqqprovider.h
    )

set(DBUS_FILES
src/dbus/dbus_consts.cpp
src/dbus/dbus_consts.h
src/dbus/doaaccountmanager.cpp
src/dbus/doaaccountmanager.h
src/dbus/doaaccounts_adapter.h
src/dbus/doaaccounts_adapter.cpp
src/dbus/doaaccountscalendar_adapter.cpp
src/dbus/doaaccountscalendar_adapter.h
src/dbus/doaaccountspasswordadapter.cpp
src/dbus/doaaccountspasswordadapter.h
    )
set(DB_FILES
src/db/accountdb.cpp
src/db/accountdb.h
src/db/account_result.h
    )

# Main executable
add_executable(${PROJECT_NAME}
               src/app/doa_daemon.cpp
               ${CONTROLLER_FILES}
               ${DBUS_FILES}
               ${DB_FILES}
               )

target_link_libraries(${PROJECT_NAME}
    ${LINK_LIBS}
    doa-lib)

## Installation
install(TARGETS ${PROJECT_NAME}  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES ${APP_SERVICE} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/user)
install(FILES ${APP_DBUS_SERVICE} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/dbus-1/services/)

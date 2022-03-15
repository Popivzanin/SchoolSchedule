cmake_minimum_required(VERSION 3.1)
project(crud)

set(CMAKE_CXX_STANDARD 11)

add_library(crud-lib
        src/controller/StaticController.hpp
        src/controller/UserController.hpp

        src/controller/ScheduleController.hpp

        src/db/UserDb.hpp
        src/dto/PageDto.hpp
        src/dto/StatusDto.hpp
        src/dto/UserDto.hpp

        src/dto/ScheduleDto.hpp

        src/service/UserService.cpp
        src/service/UserService.hpp

        src/service/ScheduleService.hpp
        src/service/ScheduleService.cpp

        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.cpp
        src/ErrorHandler.hpp)

## include directories
set(project_name crud)
target_include_directories(crud-lib PUBLIC src)
#--------------------------------------------------------------------------------------------------
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
#conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ..
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
target_link_libraries(${project_name}-lib ${CONAN_LIBS})

#--------------------------------------------------------------------------------------------------

add_definitions(
        ## define path to swagger-ui static resources folder
#        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
        -DOATPP_SWAGGER_RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/swagger"

        ## SQLite database file
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        ## SQLite database test file
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(crud-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## add executables

add_executable(crud-exe src/App.cpp)
target_link_libraries(crud-exe crud-lib)

#add_executable(crud-test
#        test/tests.cpp
#        test/app/TestClient.hpp
#        test/app/TestDatabaseComponent.hpp
#        test/app/TestComponent.hpp
#        test/UserControllerTest.hpp
#        test/UserControllerTest.cpp)
#target_link_libraries(crud-test crud-lib)
#
#enable_testing()
#add_test(project-tests crud-test)

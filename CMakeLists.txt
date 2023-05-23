cmake_minimum_required( VERSION 3.0.2 )

project( Dissertation )

set( CLIENT_SRC_DIR ${CMAKE_SOURCE_DIR}/src/client)
set( CLIENT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/client)
set( SERVER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/server)
set( SERVER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/server)

set( CLIENT_HEADERS ${CLIENT_INCLUDE_DIR}/client_hello.hpp )
set( CLIENT_SRCS ${CLIENT_SRC_DIR}/main.cpp )

set( SERVER_HEADERS 
    ${SERVER_INCLUDE_DIR}/server_hello.hpp
    ${SERVER_INCLUDE_DIR}/socket/SocketServer.hpp )
set( SERVER_SRCS 
    ${SERVER_SRC_DIR}/main.cpp
    ${SERVER_SRC_DIR}/socket/SocketServer.cpp )

add_executable( client ${CLIENT_SRCS} ${CLIENT_HEADERS} )
target_include_directories(client PRIVATE ${CLIENT_INCLUDE_DIR})

add_executable( server ${SERVER_SRCS} ${SERVER_HEADERS} )
target_include_directories(server PRIVATE ${SERVER_INCLUDE_DIR})
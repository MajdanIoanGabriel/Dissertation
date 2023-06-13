cmake_minimum_required( VERSION 3.0.2 )

project( Dissertation )

set( CLIENT_SRC_DIR ${CMAKE_SOURCE_DIR}/src/client)
set( CLIENT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/client)
set( SERVER_SRC_DIR ${CMAKE_SOURCE_DIR}/src/server)
set( SERVER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/server)
set( UTILS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/utils)

set( CLIENT_HEADERS 
    ${CLIENT_INCLUDE_DIR}/clients/MsgQueueClient.hpp
    ${CLIENT_INCLUDE_DIR}/clients/PipeClient.hpp
    ${CLIENT_INCLUDE_DIR}/clients/ShmClient.hpp
    ${CLIENT_INCLUDE_DIR}/clients/SocketClient.hpp
    ${UTILS_INCLUDE_DIR}/Defines.hpp
    ${UTILS_INCLUDE_DIR}/Timer.hpp )
set( CLIENT_SRCS 
    ${CLIENT_SRC_DIR}/main.cpp
    ${CLIENT_SRC_DIR}/clients/MsgQueueClient.cpp
    ${CLIENT_SRC_DIR}/clients/PipeClient.cpp
    ${CLIENT_SRC_DIR}/clients/ShmClient.cpp
    ${CLIENT_SRC_DIR}/clients/SocketClient.cpp )

set( SERVER_HEADERS 
    ${SERVER_INCLUDE_DIR}/servers/MsgQueueServer.hpp
    ${SERVER_INCLUDE_DIR}/servers/PipeServer.hpp
    ${SERVER_INCLUDE_DIR}/servers/ShmServer.hpp
    ${SERVER_INCLUDE_DIR}/servers/SocketServer.hpp
    ${UTILS_INCLUDE_DIR}/Defines.hpp )
set( SERVER_SRCS 
    ${SERVER_SRC_DIR}/main.cpp
    ${SERVER_SRC_DIR}/servers/MsgQueueServer.cpp
    ${SERVER_SRC_DIR}/servers/PipeServer.cpp
    ${SERVER_SRC_DIR}/servers/ShmServer.cpp
    ${SERVER_SRC_DIR}/servers/SocketServer.cpp )

add_executable( client ${CLIENT_SRCS} ${CLIENT_HEADERS} )
target_include_directories(client PRIVATE ${CLIENT_INCLUDE_DIR} ${UTILS_INCLUDE_DIR})

add_executable( server ${SERVER_SRCS} ${SERVER_HEADERS} )
target_include_directories(server PRIVATE ${SERVER_INCLUDE_DIR} ${UTILS_INCLUDE_DIR})
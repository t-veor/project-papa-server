set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INCLUDE_DIRECTORIES
    ${LIB_DIR}/Simple-Websocket-Server
    ${LIB_DIR}/rapidjson/include
    ${LIB_DIR}/server_shm
    ${LIB_DIR}/oscpkt
    PARENT_SCOPE)

set(INCLUDE_CATCH_DIRECTORY
    ${LIB_DIR}/catch
    PARENT_SCOPE)

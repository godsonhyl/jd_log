SET(SOURCE
        BaseLoggerSpdImpl.cpp
        LogManager.cpp
        )

SET(HEADERS
        nsdef.h
        IBaseLogger.h
        IBaseLoggerImpl.h
        LogManager.h
        BaseLoggerSpdImpl.h
        )

add_library(jd_log SHARED ${SOURCE} ${HEADERS})
target_compile_definitions(jd_log PRIVATE JD_LOG_EXPORT=1)

if (UNIX)
   target_link_libraries(jd_log stdc++fs)
endif ()


#install
if (MSVC)
    set(SDK_INSTALL_HEAD_DIR ${SDK_DIR}/jd_log/win32/include)
    install(FILES ${CMAKE_BINARY_DIR}/jd_log/${CMAKE_BUILD_TYPE_LOWER}/jd_log.dll
                  ${CMAKE_BINARY_DIR}/jd_log/${CMAKE_BUILD_TYPE_LOWER}/jd_log.lib
            DESTINATION ${SDK_DIR}/jd_log/win32/lib)
else()
    set(SDK_INSTALL_HEAD_DIR ${SDK_DIR}/jd_log/linux/include)
    install(TARGETS jd_log LIBRARY 
            DESTINATION  ${SDK_DIR}/jd_log/linux/lib)
endif ()

install(FILES ${CMAKE_SOURCE_DIR}/jd_log/nsdef.h
                  ${CMAKE_SOURCE_DIR}/jd_log/IBaseLogger.h
                  ${CMAKE_SOURCE_DIR}/jd_log/IBaseLoggerImpl.h
                  ${CMAKE_SOURCE_DIR}/jd_log/LogManager.h
                  ${CMAKE_SOURCE_DIR}/jd_log/LogManager.h
            DESTINATION ${SDK_INSTALL_HEAD_DIR} )

add_custom_command(TARGET jd_log POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy_directory 
                   ${CMAKE_SOURCE_DIR}/jd_log/include/spdlog 
                   ${SDK_INSTALL_HEAD_DIR}/spdlog)

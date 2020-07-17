
SET(SOURCE demo.cpp)
add_executable(log_demo ${SOURCE})

if (MSVC)
    set(LIBS_JD_LOG "${CMAKE_BINARY_DIR}/jd_log/${CMAKE_BUILD_TYPE_LOWER}/jd_log.lib")
    target_link_libraries(log_demo ${LIBS_JD_LOG})
elseif(UNIX) 
    #link_directories(${CMAKE_BINARY_DIR}jd_log)
    target_link_libraries(log_demo jd_log pthread)
endif()


#install
if (MSVC)
    install(FILES ${SDK_DIR}/jd_log/win32/lib/jd_log.dll
                  ${CMAKE_BINARY_DIR}/demo/${CMAKE_BUILD_TYPE_LOWER}/log_demo.exe
            DESTINATION ${INSTALL_DIR})

elseif (UNIX)
    install(PROGRAMS ${CMAKE_BINARY_DIR}/demo/log_demo DESTINATION ${INSTALL_DIR})

    install(DIRECTORY ${SDK_DIR}/jd_log/linux/lib/
        DESTINATION ${INSTALL_DIR}
        FILES_MATCHING PATTERN "*.so")
endif ()

cmake_minimum_required(VERSION 3.18)   

project(cpp2023_test)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "..." FORCE)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
find_package(doctest REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Doxygen REQUIRED)

add_subdirectory(prj.lab)
add_subdirectory(prj.test)
add_subdirectory(prj.cw)

install(TARGETS trirastr_test trirastr_testVu trirastr_demo trirastr_demoVu arrayt_test matrixs_test arrayd_test rational_test RUNTIME
  DESTINATION bin
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
  DESTINATION data
)

if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()

install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*zlib*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*tiff*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_videoio*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_imgproc*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_imgcodecs*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_highgui*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*opencv_core*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libwebpdecoder*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libsharpyuv*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libpng*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*liblzma*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*jpeg*"
)
install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
  DESTINATION bin
  FILES_MATCHING PATTERN "*libwebp*"
)

if(DOXYGEN_FOUND)
       set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/prj.cw/trirastr/Doxyfile)
       set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

       add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
       )

endif()

if(DOXYGEN_FOUND)
       install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen_docs/latex
               DESTINATION docs)
   endif()

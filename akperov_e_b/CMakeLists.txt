cmake_minimum_required(VERSION 3.18)   

project(cpp2023_test)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

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

install(TARGETS trirastr_test trirastr_testVu trirastr_demo trirastr_demoVu arrayt_test matrixs_test arrayd_test rational_test
  DESTINATION bin
)

if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    install(FILES "${VCPKG_INSTALLED_DIR}/x64-windows/bin/zlib1.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/tiff.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/opencv_videoio4.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/opencv_imgproc4.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/opencv_imgcodecs4.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/opencv_highgui4.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/opencv_core4.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/libwebp.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/libwebpdecoder.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/libsharpyuv.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/libpng16.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/liblzma.dll"
                "${VCPKG_INSTALLED_DIR}/x64-windows/bin/jpeg62.dll"
          DESTINATION bin)
  else()
   install(FILES "${VCPKG_INSTALLED_DIR}/x32-windows/bin/zlib1.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/tiff.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/opencv_videoio4.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/opencv_imgproc4.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/opencv_imgcodecs4.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/opencv_highgui4.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/opencv_core4.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/libwebp.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/libwebpdecoder.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/libsharpyuv.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/libpng16.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/liblzma.dll"
                "${VCPKG_INSTALLED_DIR}/x32-windows/bin/jpeg62.dll"
          DESTINATION bin)
  endif()
  else()
   install(FILES "${VCPKG_INSTALLED_DIR}/lib/libz.so.1"
                "${VCPKG_INSTALLED_DIR}/lib/libtiff.so.5"
                "${VCPKG_INSTALLED_DIR}/lib/libopencv_videoio.so.4.1"
                "${VCPKG_INSTALLED_DIR}/lib/libopencv_imgproc.so.4.1"
                "${VCPKG_INSTALLED_DIR}/lib/libopencv_imgcodecs.so.4.1"
                "${VCPKG_INSTALLED_DIR}/lib/libopencv_highgui.so.4.1"
                "${VCPKG_INSTALLED_DIR}/lib/libopencv_core.so.4.1"
                "${VCPKG_INSTALLED_DIR}/lib/libwebp.so.7"
                "${VCPKG_INSTALLED_DIR}/lib/libwebpdecoder.so.3"
                "${VCPKG_INSTALLED_DIR}/lib/libsharpyuv.so.3"
                "${VCPKG_INSTALLED_DIR}/lib/libpng16.so.16"
                "${VCPKG_INSTALLED_DIR}/lib/liblzma.so.5"
                "${VCPKG_INSTALLED_DIR}/lib/libjpeg.so.62"
          DESTINATION /usr/local/lib)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
  DESTINATION data
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
       install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen_docs
               DESTINATION ${CMAKE_INSTALL_PREFIX})
   endif()

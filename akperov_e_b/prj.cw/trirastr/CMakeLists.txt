add_library(trirastr trirastr.cpp include/trirastr/trirastr.hpp)
set_property(TARGET trirastr PROPERTY CXX_STANDARD 20)
target_include_directories(trirastr PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(trirastr PRIVATE opencv_core opencv_highgui opencv_imgproc)
install(TARGETS trirastr)
project(BinPicking)

set(B2BTL_MEAM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "")

find_package( OpenCV REQUIRED )

add_library(B2BTL_MEAM SHARED STATIC B2BTL_MEAM.cpp B2BTL_MEAM.h)
target_link_libraries(B2BTL_MEAM ${OpenCV_LIBS} pclFunction meshSampling HPR)
target_include_directories(B2BTL_MEAM PUBLIC ${PCLFUNCTION_INCLUDE_DIR} ${MESHSAMPLING_INCLUDE_DIR} ${HPR_INCLUDE_DIR})




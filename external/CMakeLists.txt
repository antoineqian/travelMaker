
add_library(external STATIC airfrance.cpp airjapan.cpp cosmosants.cpp naebaprince.cpp)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp)

target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

FILE(GLOB app_headers lab3/*.h)
FILE(GLOB app_sources lab3/*.cc)

SET(files_example ${app_headers} ${app_sources})
SOURCE_GROUP("app" FILES ${files_app})

ADD_EXECUTABLE(app ${files_app})
TARGET_LINK_LIBRARIES(app core render)
ADD_DEPENDENCIES(app core render)
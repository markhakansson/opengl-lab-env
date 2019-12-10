#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

FILE(GLOB example_headers lab3/*.h)
FILE(GLOB example_sources lab3/*.cc)

SET(files_example ${example_headers} ${example_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(example ${files_example})
TARGET_LINK_LIBRARIES(example core render)
ADD_DEPENDENCIES(example core render)
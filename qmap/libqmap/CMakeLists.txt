set (libq65_FSRCS)

set (libq65_CXXSRCS
  QmapCompat.cpp
  )

set (libq65_C_and_CXXSRCS
  ${libq65_CSRCS}
  ${libq65_CXXSRCS}
  )
set_property (SOURCE ${libq65_C_and_CXXSRCS} APPEND_STRING PROPERTY COMPILE_FLAGS " -include wsjtx_config.h")
set_property (SOURCE ${libq65_C_and_CXXSRCS} APPEND PROPERTY OBJECT_DEPENDS ${CMAKE_BINARY_DIR}/wsjtx_config.h)


#
# build our targets
#
add_library (qmap_impl STATIC ${libq65_FSRCS} ${libq65_CSRCS} ${libq65_CXXSRCS})
target_include_directories (qmap_impl PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries (qmap_impl wsjt_cxx Qt5::Core)

#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyList" for configuration ""
set_property(TARGET MyList APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MyList PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/usr/local/lib/MyList/libMyList.so"
  IMPORTED_SONAME_NOCONFIG "@rpath/libMyList.so"
  )

list(APPEND _cmake_import_check_targets MyList )
list(APPEND _cmake_import_check_files_for_MyList "/usr/local/lib/MyList/libMyList.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

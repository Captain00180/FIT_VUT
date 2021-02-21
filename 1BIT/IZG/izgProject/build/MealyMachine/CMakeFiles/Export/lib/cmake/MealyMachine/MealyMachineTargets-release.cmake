#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MealyMachine::MealyMachine" for configuration "RELEASE"
set_property(TARGET MealyMachine::MealyMachine APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MealyMachine::MealyMachine PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib64/libMealyMachine.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS MealyMachine::MealyMachine )
list(APPEND _IMPORT_CHECK_FILES_FOR_MealyMachine::MealyMachine "${_IMPORT_PREFIX}/lib64/libMealyMachine.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

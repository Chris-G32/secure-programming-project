# Find the native libsodium includes and library
#
#  sodium_INCLUDE_DIR - where to find sodium.h, etc.
#  sodium_LIBRARIES   - List of libraries when using libsodium.
#  sodium_FOUND       - True if libsodium found.

if (sodium_INCLUDE_DIR)
  # Already in cache, be silent
  set(sodium_FIND_QUIETLY TRUE)
endif ()

find_path(sodium_INCLUDE_DIR sodium.h
  PATHS
  /usr/local/include
  /opt/local/include
  /usr/include
)

find_library(sodium_LIBRARY NAMES sodium libsodium
  PATHS
  /usr/local/lib
  /opt/local/lib
  /usr/lib
)

# handle the QUIETLY and REQUIRED arguments and set sodium_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sodium DEFAULT_MSG sodium_LIBRARY sodium_INCLUDE_DIR)

if (sodium_FOUND)
  set(sodium_LIBRARIES ${sodium_LIBRARY})
else ()
  set(sodium_LIBRARIES)
endif ()

mark_as_advanced(sodium_INCLUDE_DIR sodium_LIBRARY)
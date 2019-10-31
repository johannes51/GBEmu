
function(set_std_properties TARGET STANDARD)
  set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD ${STANDARD})
  set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)
  set_property(TARGET ${TARGET} PROPERTY CXX_EXTENSIONS OFF)
endfunction()

function(msvc_option TARGET STANDARD)
  if(MSVC_VERSION GREATER_EQUAL "1900" AND CMAKE_VERSION LESS 3.10)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("/std:c++${STANDARD}" _cpp_latest_flag_supported)
    if(_cpp_latest_flag_supported)
      target_compile_options(${TARGET} PRIVATE "/std:c++${STANDARD}")
    endif()
  endif()
endfunction()

# Set the compiler standard to C++11
function(cxx_11 TARGET)
  set_std_properties(${TARGET} 11)
  msvc_option(${TARGET} 11)
endfunction()

# Set the compiler standard to C++14
function(cxx_14 TARGET)
  set_std_properties(${TARGET} 14)
  msvc_option(${TARGET} 14)
endfunction()

# Set the compiler standard to C++17
function(cxx_17 TARGET)
  set_std_properties(${TARGET} 17)
  msvc_option(${TARGET} 17)
endfunction()

# Set the compiler standard to C++20
function(cxx_20 TARGET)
  set_std_properties(${TARGET} 20)
endfunction()

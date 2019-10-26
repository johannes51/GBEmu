
function(sanitize TARGET_NAME SANITIZER)
  target_compile_options("${TARGET_NAME}" PRIVATE "-fno-omit-frame-pointer")

  if(UNIX)

    if(uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG")
      append("-O1" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    endif()

    if(SANITIZER MATCHES "([Aa]ddress);([Uu]ndefined)"
       OR SANITIZER MATCHES "([Uu]ndefined);([Aa]ddress)")
      message(STATUS "Building with Address, Undefined sanitizers")
      append("-fsanitize=address,undefined" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    elseif("${SANITIZER}" MATCHES "([Aa]ddress)")
      # Optional: -fno-optimize-sibling-calls -fsanitize-address-use-after-scope
      message(STATUS "Building with Address sanitizer")
      target_compile_options("${TARGET_NAME}" PRIVATE "-fsanitize=address")
    elseif(SANITIZER MATCHES "([Mm]emory([Ww]ith[Oo]rigins)?)")
      # Optional: -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2
      append("-fsanitize=memory" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
      if(SANITIZER MATCHES "([Mm]emory[Ww]ith[Oo]rigins)")
        message(STATUS "Building with MemoryWithOrigins sanitizer")
        append("-fsanitize-memory-track-origins" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
      else()
        message(STATUS "Building with Memory sanitizer")
      endif()
    elseif(SANITIZER MATCHES "([Uu]ndefined)")
      message(STATUS "Building with Undefined sanitizer")
      append("-fsanitize=undefined" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
      if(EXISTS "${BLACKLIST_FILE}")
        append("-fsanitize-blacklist=${BLACKLIST_FILE}" CMAKE_C_FLAGS
               CMAKE_CXX_FLAGS)
      endif()
    elseif(SANITIZER MATCHES "([Tt]hread)")
      message(STATUS "Building with Thread sanitizer")
      append("-fsanitize=thread" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    elseif(SANITIZER MATCHES "([Ll]eak)")
      message(STATUS "Building with Leak sanitizer")
      append("-fsanitize=leak" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    else()
      message(
        FATAL_ERROR "Unsupported value of SANITIZER: ${SANITIZER}")
    endif()
  elseif(MSVC)
    if(SANITIZER MATCHES "([Aa]ddress)")
      message(STATUS "Building with Address sanitizer")
      append("-fsanitize=address" CMAKE_C_FLAGS CMAKE_CXX_FLAGS)
    else()
      message(
        FATAL_ERROR
          "This sanitizer not yet supported in the MSVC environment: ${SANITIZER}"
        )
    endif()
  else()
    message(FATAL_ERROR "SANITIZER is not supported on this platform.")
  endif()

endfunction()


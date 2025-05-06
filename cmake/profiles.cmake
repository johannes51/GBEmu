get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
    if(NOT "Sanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Sanitizer)
    endif()
else()
    set(allowedBuildTypes Sanitizer Debug Release RelWithDebInfo MinSizeRel)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

    if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
        message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_C_FLAGS_SANITIZER
    "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -O1" CACHE STRING
    "Flags used by the C compiler for Sanitizer build type or configuration." FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER
    "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -O1" CACHE STRING
    "Flags used by the C++ compiler for Sanitizer build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_SANITIZER "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Linker flags to be used to create executables for Sanitizer build type." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_SANITIZER "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Linker flags to be used to create shared libraries for Sanitizer build type." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_SANITIZER "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Linker flags to be used to create static libraries for Sanitizer build type." FORCE)

mark_as_advanced(CMAKE_C_FLAGS_SANITIZER
                 CMAKE_CXX_FLAGS_SANITIZER
                 CMAKE_EXE_LINKER_FLAGS_SANITIZER
                 CMAKE_SHARED_LINKER_FLAGS_SANITIZER
                 CMAKE_STATIC_LINKER_FLAGS_SANITIZER)

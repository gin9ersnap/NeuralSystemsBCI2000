###########################################################################
## $Id$
## Authors: griffin.milsap@gmail.com
## Description: Sets a number of default build options for makefile
## generators.

#
# Runs compiler with "-dumpversion" (taken from FindBoost.cmake, jm)
#
FUNCTION(COMPILER_DUMPVERSION _OUTPUT_VERSION)

  EXEC_PROGRAM(${CMAKE_CXX_COMPILER}
    ARGS ${CMAKE_CXX_COMPILER_ARG1} -dumpversion
    OUTPUT_VARIABLE _bci_COMPILER_VERSION
  )

  SET(${_OUTPUT_VERSION} ${_bci_COMPILER_VERSION} PARENT_SCOPE)
ENDFUNCTION()

IF( MINGW )
  COMPILER_DUMPVERSION( GCC_VERSION )
  IF( NOT USE_STD_QT AND GCC_VERSION VERSION_LESS 4.0 )
    MESSAGE( FATAL_ERROR
      "When building against the Qt libraries in the BCI2000 source tree, "
      "a 4.x version of gcc is required. --- Your gcc version is " ${GCC_VERSION}
      " --- More information may be found at "
      "http://doc.bci2000.org/index.php/Programming_Reference:Build_System"
    )
  ELSE( NOT USE_STD_QT AND GCC_VERSION VERSION_LESS 4.0 )
    MESSAGE( "Your gcc version is " ${GCC_VERSION} )
  ENDIF( NOT USE_STD_QT AND GCC_VERSION VERSION_LESS 4.0 )
ENDIF( MINGW )

IF( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES Clang )
  SET( COMPILER_IS_GCC_COMPATIBLE 1 )
ENDIF()
  
IF( COMPILER_IS_GCC_COMPATIBLE )
  # Set a default build type for single-configuration
  # CMake generators if no build type is set.
  IF( NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE RELEASE )
  ENDIF( NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE )

  # Select flags.
  SET( cflags_
      "-include \"${PROJECT_SRC_DIR}/shared/config/gccprefix.h\""
  )
  IF( USE_SSE2 )
    LIST( APPEND cflags_ -msse2 )
  ENDIF()

  IF( NOT WIN32 )
    SET( cflags_
      ${cflags_}
      -fPIC
      -fvisibility=hidden
    )
  ENDIF()
  
  SET( cflags_
    ${cflags_}
    -Wstrict-aliasing
    -Wno-endif-labels
    -Wno-multichar
  )

  FOREACH( flag_ ${cflags_} )
    SET( CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} ${flag_}"
    )
    SET( CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} ${flag_}"
    )
  ENDFOREACH()

  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
  SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

  SET( lflags_ )
  IF( WIN32 )
    SET( lflags_
      ${lflags_}
      -static-libgcc
      -Wl,--enable-stdcall-fixup
    )
  ELSEIF( APPLE )
    SET( lflags
      ${lflags_}
      -dead_strip
    )
  ENDIF()

  FOREACH( var_ EXE;SHARED;MODULE )
    FOREACH( flag_ ${lflags_} )
      SET( CMAKE_${var_}_LINKER_FLAGS
        "${CMAKE_${var_}_LINKER_FLAGS} ${flag_}"
      )
    ENDFOREACH()
  ENDFOREACH()

  # Build the compiler description string.
  COMPILER_DUMPVERSION( GCC_VERSION )
  IF( APPLE )
    SET( COMPILER_SUB "apple" )
  ELSEIF( MINGW )
    SET( COMPILER_SUB "mingw" )
  ELSEIF( CYGWIN )
    SET( COMPILER_SUB "cygwin" )
  ELSE()
    SET( COMPILER_SUB "unknown" )
  ENDIF()

  SET( COMPILER_NAME_ "gcc-${COMPILER_SUB}-${GCC_VERSION}" )
ELSE()

  SET( COMPILER_NAME_ "${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}" )

ENDIF( COMPILER_IS_GCC_COMPATIBLE )

# MSVC specific flags
IF( MSVC )

  SET_PROPERTY( GLOBAL PROPERTY USE_FOLDERS ${BUILD_USE_SOLUTION_FOLDERS} )
  
  SET( CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} /EHsc"
  )
  IF( USE_SSE2 )
    SET( CMAKE_C_FLAGS
      "${CMAKE_C_FLAGS} /arch:SSE2"
    )
    SET( CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} /arch:SSE2"
    )
  ENDIF()

  SET( CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} /D_SECURE_SCL=0"
  )
  ADD_DEFINITIONS(
    /DNOMINMAX
    /D_CRT_SECURE_NO_WARNINGS
    /D_CRT_SECURE_NO_DEPRECATE
    /D_CRT_NONSTDC_NO_WARNINGS
    /D_SCL_SECURE_NO_WARNINGS
    /J # use unsigned chars by default
    /W3
    /wd4355
    /wd4800
  )
  INCLUDE_DIRECTORIES(
    ${PROJECT_SRC_DIR}/shared/compat
  )
  # Adjust flags such that by default programs are built statically against the MSVC runtime;
  # save defaults as "_DYNAMIC" for use with MFC-based projects.
  # Support for statically linking MFC appears to be broken in CMake, see
  # http://www.cmake.org/Wiki/CMake_FAQ#How_to_use_MFC_with_CMake, so
  # we need to go back to dynamic linking for MFC.
  SET( COMP_FLAG_VARS
         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
         CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
         CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
  )
  FOREACH( flag_var ${COMP_FLAG_VARS} )
    SET( ${flag_var}_DYNAMIC "${${flag_var}}" )
    IF( ${flag_var} MATCHES "/MD" )
      STRING( REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}" )
    ENDIF( ${flag_var} MATCHES "/MD" )
    SET( ${flag_var}_STATIC "${${flag_var}}" )
  ENDFOREACH( flag_var )

  SET( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL:NO" )
  SET( CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /INCREMENTAL:NO" )

  SET( LINKER_FLAG_VARS
        CMAKE_EXE_LINKER_FLAGS
        CMAKE_SHARED_LINKER_FLAGS
        CMAKE_MODULE_LINKER_FLAGS
  )
  FOREACH( flag_var ${LINKER_FLAG_VARS} )
  
     FOREACH( type_ ${CMAKE_CONFIGURATION_TYPES} )
       STRING( TOUPPER "${type_}" type_ )
       SET( name_ ${flag_var}_${type_} )
       STRING( REGEX REPLACE "/INCREMENTAL[:YESNO]*" "" ${name_} "${${name_}}" )
       SET( ${name_} "${${name_}} /INCREMENTAL:NO" )
     ENDFOREACH()

     SET( ${flag_var}_DYNAMIC "${${flag_var}}" )
     SET( ${flag_var} "${${flag_var}} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:msvcrtd /NODEFAULTLIB:msvcprt /NODEFAULTLIB:msvcprtd" )
     SET( ${flag_var}_STATIC "${${flag_var}}" )
     
  ENDFOREACH()

  SET( FLAG_VARS ${COMP_FLAG_VARS} ${LINKER_FLAG_VARS} )

ENDIF( MSVC )

IF( COMPILER_NAME_ )
  ADD_DEFINITIONS(
    -DCOMPILER_NAME="${COMPILER_NAME_}-${CMAKE_SYSTEM_PROCESSOR}"
  )
ENDIF()

# Add global definitions.
ADD_DEFINITIONS( -D_USE_MATH_DEFINES )

# Control behavior of bciassert() macro
SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBCIDEBUG=1 -DDEBUG_BUILD=1" )



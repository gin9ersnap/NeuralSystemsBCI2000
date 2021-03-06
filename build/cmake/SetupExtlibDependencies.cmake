###########################################################################
## $Id$
## Authors: griffin.milsap@gmail.com
## Description: Modifies the framework and sets up libraries to be linked

# Sets up the extlib dependencies by looping through the BCI2000_INCLUDING var
MACRO( BCI2000_SETUP_EXTLIB_DEPENDENCIES SRC_FRAMEWORK HDR_FRAMEWORK LIBS FAILED )

# Make sure the input is treated as variables
SET( SOURCES_ "${SRC_FRAMEWORK}" )
SET( HEADERS_ "${HDR_FRAMEWORK}" )
SET( LIBRARIES "${LIBS}" )
SET( ${FAILED} "" )

# We'll loop through the using statements
FOREACH( INC ${BCI2000_INCLUDING} )
  
  IF( NOT EXISTS ${PROJECT_UTILS_DIR}/extlib/${INC}.cmake )
    MESSAGE( FATAL_ERROR
      "Unknown extlib dependency: ${INC}."
      "Make sure all BCI2000_INCLUDE statements have a corresponding .cmake file in src/extlib."
    )
  ELSE()
    SET( EXTLIB_OK FALSE )
    UNSET( INC_EXTLIB )
    UNSET( HDR_EXTLIB )
    UNSET( SRC_EXTLIB )
    UNSET( LIBDIR_EXTLIB )
    UNSET( LIBS_EXTLIB )
    INCLUDE( ${PROJECT_UTILS_DIR}/extlib/${INC}.cmake )
    IF( EXTLIB_OK )
      SET( ${SOURCES_}
        ${${SOURCES_}}
        ${SRC_EXTLIB}
      )
      SET( ${HEADERS_}
        ${${HEADERS_}}
        ${HDR_EXTLIB}
      )
      INCLUDE_DIRECTORIES( ${INC_EXTLIB} )
      LINK_DIRECTORIES( ${LIBDIR_EXTLIB} )
      SET( ${LIBRARIES}
        ${${LIBRARIES}}
        ${LIBS_EXTLIB}
      )
    ELSE( EXTLIB_OK )
      MESSAGE( " - WARNING: Could not satisfy dependency on ${INC} extlib." )
      SET( ${FAILED}
        ${${FAILED}}
        ${INC}
      )
    ENDIF( EXTLIB_OK )
  ENDIF()

ENDFOREACH( INC )

# Clear out all dependencies for next project
UNSET( BCI2000_INCLUDING )

ENDMACRO( BCI2000_SETUP_EXTLIB_DEPENDENCIES SRC_FRAMEWORK HDR_FRAMEWORK LIBS )

# Add an EXTLIB dependency to ${BCI2000_INCLUDING}
FUNCTION( BCI2000_INCLUDE LIB_LC )
  STRING( TOUPPER ${LIB_LC} LIB )
  SET( BCI2000_INCLUDING 
    ${BCI2000_INCLUDING}
    ${LIB}
    PARENT_SCOPE
  )
ENDFUNCTION() 

# Use an EXTLIB that is contained in a library
FUNCTION( BCI2000_USE LIB_LC )
  STRING( TOUPPER ${LIB_LC} LIB  )
  IF( NOT EXISTS ${PROJECT_UTILS_DIR}/extlib/${LIB}.cmake )
    MESSAGE( FATAL_ERROR
      "Unknown extlib dependency: ${LIB}."
      "Make sure all BCI2000_USE statements have a corresponding .cmake file in src/extlib."
    )
  ELSE()
    SET( EXTLIB_OK FALSE )
    INCLUDE( ${PROJECT_UTILS_DIR}/extlib/${LIB}.cmake )
    IF( EXTLIB_OK )
      INCLUDE_DIRECTORIES( ${INC_EXTLIB} )
      LINK_DIRECTORIES( ${LIBDIR_EXTLIB} )
    ENDIF()
  ENDIF()
ENDFUNCTION()


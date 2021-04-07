# If additional ACE libraries are required for testing purposes add them to the
# LIBRARY_NAMES list
IF("${XSDIR}" STREQUAL "")
  SET(XSDIR "xsdir")
ENDIF()

FIND_ACE_LIBRARIES(${XSDIR}
  LIBRARY_NAMES
  1000.12p 1000.14p 5000.12p 6000.12p 8000.12p 79000.14p 82000.12p 82000.14p 92000.12p
  82000.04p
  5000.03e 82000.03e
  1002.24u 6012.24u
  1001.70c 8016.70c 82208.70c 92238.70c
  grph.10t lwtr.10t poly.10t)

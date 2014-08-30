# Find the BLAS and LAPACK libraries that were used
  # FOREACH(I ${Trilinos_TPL_LIBRARIES})
  #   STRING(REGEX MATCH [libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.][libapck.] FOUND_LAPACK_STRING ${I})
  #   STRING(REGEX MATCH [libas.][libas.][libas.][libas.][libas.][libas.][libas.][libas.][libas.] FOUND_BLAS_STRING ${I})
  #   IF(FOUND_LAPACK_STRING)
  #     SET(BLAS ${I})
  #   ELSEIF(FOUND_BLAS_STRING)
  #     SET(LAPACK ${I})
  #   ENDIF()
  #   UNSET(FOUND_LAPACK_STRING)
  #   UNSET(FOUND_BLAS_STRING)
  # ENDFOREACH(I)
  
  # IF(NOT BLAS)
  #   MESSAGE(FATAL_ERROR "Could not find the BLAS library used by Trilinos.")
  # ENDIF()

  
  # IF(NOT LAPACK)
  #   MESSAGE(FATAL_ERROR "Could not find the LAPACK library used by Trilinos.")
  # ENDIF()
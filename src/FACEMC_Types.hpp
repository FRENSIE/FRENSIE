//---------------------------------------------------------------------------//
// \file   FACEMC_Types.hpp
// \author Alex Robinson
// \brief  Centrally located FACEMC typedefs to accommodate the single 
// point-of-control paradigm.
//---------------------------------------------------------------------------//


#ifndef FACEMC_TYPES_HPP
#define FACEMC_TYPES_HPP

// Trilinos Includes
#include <Teuchos_Array>
#include <Teuchos_ArrayRCP>
#include <Teuchos_TwoDArray>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{
//@{
//! FACEMC Typedefs.
// \brief These are the typedefs used withing the FACEMC namespace
  typedef Teuchos::Array<double> FACEMC

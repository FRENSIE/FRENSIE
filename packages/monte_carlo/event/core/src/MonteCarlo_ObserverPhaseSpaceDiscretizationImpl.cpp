//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.cpp
//! \author Alex Robinson
//! \brief  Observer phase space discretization impl. class template
//!         instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace MonteCarlo{

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ObserverPhaseSpaceDiscretizationImpl );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDiscretizationImpl.cpp
//---------------------------------------------------------------------------//

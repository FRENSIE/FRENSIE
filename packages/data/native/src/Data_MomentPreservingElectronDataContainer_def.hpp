//---------------------------------------------------------------------------//
//!
//! \file   Data_MomentPreservingElectronDataContainer_def.hpp
//! \author Luke Kersting
//! \brief  The native moment preserving electron data container template defs.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_DEF_HPP
#define DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

// FRENSIE Includes
#include "Data_DataContainerHelpers.hpp"

namespace Data{

// Save the data to an archive
template<typename Archive>
void MomentPreservingElectronDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_weights );
}

// Load the data from an archive
template<typename Archive>
void MomentPreservingElectronDataContainer::load( Archive& ar,
						  const unsigned version )
{
  DATA_MAKE_NVP_DEFAULT( ar, atomic_number );
  DATA_MAKE_NVP_DEFAULT( ar, cutoff_angle_cosine );
  DATA_MAKE_NVP_DEFAULT( ar, angular_energy_grid );
  DATA_MAKE_NVP_DEFAULT( ar, number_of_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_discrete_angles );
  DATA_MAKE_NVP_DEFAULT( ar, moment_preserving_elastic_weights );
}

} // end Data namespace

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronDataContainer_def.hpp
//---------------------------------------------------------------------------//

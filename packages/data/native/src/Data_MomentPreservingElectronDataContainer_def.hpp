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

namespace Data{

// Save the data to an archive
template<typename Archive>
void MomentPreservingElectronDataContainer::save( Archive& ar,
						  const unsigned version) const
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "cutoff_angle_cosine",
                                        d_cutoff_angle_cosine );
  ar & boost::serialization::make_nvp( "angular_energy_grid",
				                        d_angular_energy_grid );
  ar & boost::serialization::make_nvp( "number_of_discrete_angles",
                                        d_number_of_discrete_angles );
  ar & boost::serialization::make_nvp( "moment_preserving_elastic_discrete_angles",
                                        d_moment_preserving_elastic_discrete_angles );
  ar & boost::serialization::make_nvp( "moment_preserving_elastic_weights",
                                        d_moment_preserving_elastic_weights );
/*  ar & boost::serialization::make_nvp( "electron_energy_grid",
				                        d_electron_energy_grid );
  ar & boost::serialization::make_nvp(
            "moment_preserving_moment_preserving_elastic_cross_section",
            d_moment_preserving_moment_preserving_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "moment_preserving_moment_preserving_elastic_cross_section_threshold_index",
            d_moment_preserving_moment_preserving_elastic_cross_section_threshold_index );*/
}

// Load the data from an archive
template<typename Archive>
void MomentPreservingElectronDataContainer::load( Archive& ar,
						  const unsigned version )
{
  ar & boost::serialization::make_nvp( "atomic_number", d_atomic_number );
  ar & boost::serialization::make_nvp( "cutoff_angle_cosine",
                                        d_cutoff_angle_cosine );
  ar & boost::serialization::make_nvp( "angular_energy_grid",
				                        d_angular_energy_grid );
  ar & boost::serialization::make_nvp( "number_of_discrete_angles",
                                        d_number_of_discrete_angles );
  ar & boost::serialization::make_nvp( "moment_preserving_elastic_discrete_angles",
                                        d_moment_preserving_elastic_discrete_angles );
  ar & boost::serialization::make_nvp( "moment_preserving_elastic_weights",
                                        d_moment_preserving_elastic_weights );
/*  ar & boost::serialization::make_nvp( "electron_energy_grid",
				                        d_electron_energy_grid );
  ar & boost::serialization::make_nvp(
            "moment_preserving_moment_preserving_elastic_cross_section",
            d_moment_preserving_moment_preserving_elastic_cross_section );
  ar & boost::serialization::make_nvp(
            "moment_preserving_moment_preserving_elastic_cross_section_threshold_index",
            d_moment_preserving_moment_preserving_elastic_cross_section_threshold_index );*/
}

} // end Data namespace

#endif // end DATA_MOMENT_PRESERVING_ELECTRON_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronDataContainer_def.hpp
//---------------------------------------------------------------------------//

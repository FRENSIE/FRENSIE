//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayNuclide_def.hpp
//! \author Alex Robinson
//! \brief  The decay nuclide class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_NUCLIDE_DEF_HPP
#define DATA_DECAY_NUCLIDE_DEF_HPP

// Boost Includes
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>

namespace Data{

// Serialize the data
template<typename Archive>
void DecayNuclide::serialize( Archive &ar, const unsigned int version )
{
  ar & boost::serialization::make_nvp( "z", d_atomic_number );
  ar & boost::serialization::make_nvp( "a", d_atomic_mass_number );
  ar & boost::serialization::make_nvp( "s", d_isomer_number );
  ar & boost::serialization::make_nvp( "half_life", d_half_life );
  ar & boost::serialization::make_nvp( "half_life_err", d_half_life_error );
  ar & boost::serialization::make_nvp( "decay_const", d_decay_constant );
  ar & boost::serialization::make_nvp( "decay_const_err", d_decay_constant_error );
  ar & boost::serialization::make_nvp( "decay_data", d_decay_branches );
}

// Serialize the struct data
template<typename Archive>
void DecayNuclide::DecayBranch::serialize( Archive &ar, 
					   const unsigned int version )
{
  ar & boost::serialization::make_nvp( "branching_ratio", branching_ratio );
  ar & boost::serialization::make_nvp( "branching_ratio_err", 
				     branching_ratio_error );
  ar & boost::serialization::make_nvp( "daughter", daughter);
  ar & boost::serialization::make_nvp( "decay_type", 
				     decay_type );
}

} // end Data namespace

#endif // end DATA_DECAY_NUCLIDE_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_DecayNuclide_def.hpp
//---------------------------------------------------------------------------//

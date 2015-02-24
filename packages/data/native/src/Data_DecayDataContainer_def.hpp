//---------------------------------------------------------------------------//
//! 
//! \file   Data_DecayDataContainer_def.hpp
//! \author Alex Robinson
//! \brief  The decay data container class template definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_DATA_CONTAINER_DEF_HPP
#define DATA_DECAY_DATA_CONTAINER_DEF_HPP

// Boost Includes
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>

namespace Data{

// Serialize the data
template<typename Archive>
void DecayDataContainer::serialize( Archive& ar, const unsigned int version )
{
  ar & boost::serialization::make_nvp( "decay_data", d_decay_nuclides );
}

} // end Data namespace

#endif // end DATA_DECAY_DATA_CONTAINER_DEF_HPP

//---------------------------------------------------------------------------//
// end Data_DecayDataContainer_def.hpp
//---------------------------------------------------------------------------//

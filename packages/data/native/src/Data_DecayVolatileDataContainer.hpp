//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayVolatileDataContainer.hpp
//! \author Alex Robinson
//! \brief  The native decay volatile data container class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_DECAY_DATA_VOLATILE_CONTAINER_HPP
#define DATA_DECAY_DATA_VOLATILE_CONTAINER_HPP

// FRENSIE Includes
#include "Data_DecayDataContainer.hpp"

namespace Data{

//! The decay volatile data container
class DecayVolatileDataContainer : public DecayDataContainer
{

public:

  //! Default Constructor
  DecayVolatileDataContainer();

  //! Constructor (from saved archive)
  DecayVolatileDataContainer(
		   const std::string& archive_name,
		   const Utility::ArchivableObject::ArchiveType archive_type );

  
  // Add the setter member functions to the public interface
  using DecayDataContainer::addDecayNuclide;

  // Add the exportData member function to the public interface
  using DecayDataContainer::exportData;

  // Add the packDataInString member function to the public interface
  using DecayDataContainer::packDataInString;
};

} // end Data namespace

#endif // end DATA_DECAY_DATA_VOLATILE_CONTAINER_HPP

//---------------------------------------------------------------------------//
// end Data_DecayVolatileDataContainer.hpp
//---------------------------------------------------------------------------//

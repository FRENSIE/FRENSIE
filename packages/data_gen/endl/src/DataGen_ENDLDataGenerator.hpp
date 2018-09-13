//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ENDLDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The ENDL data generator base class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ENDL_DATA_GENERATOR_HPP
#define DATA_GEN_ENDL_DATA_GENERATOR_HPP

// FRENSIE Includes
#include "Data_ENDLVolatileDataContainer.hpp"

namespace DataGen{

//! The electron-photon-relaxation data generator base class
class ENDLDataGenerator
{

public:

  //! Constructor
  ENDLDataGenerator();

  //! Destructor
  virtual ~ENDLDataGenerator()
  { /* ... */ }

  //! Populate the ENDL data container
  virtual void populateENDLDataContainer() = 0;

  //! Populate the EADL data container
  virtual void populateEADLDataContainer() = 0;

  //! Populate the EPDL data container
  virtual void populateEPDLDataContainer() = 0;

  //! Populate the EEDL data container
  virtual void populateEEDLDataContainer() = 0;

  //! Get the data container
  const Data::ENDLDataContainer& getDataContainer() const;

protected:

  //! Get the volatile data container
  Data::ENDLVolatileDataContainer& getVolatileDataContainer();

private:

  // The ENDL volatile data container
  Data::ENDLVolatileDataContainer d_data_container;
};

} // end DataGen namespace

#endif // end DATA_GEN_ENDL_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ENDLDataGenerator.hpp
//---------------------------------------------------------------------------//

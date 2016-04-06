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
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"

namespace DataGen{

//! The electron-photon-relaxation data generator base class
class ENDLDataGenerator
{
  
public:

  //! Constructor
  ENDLDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~ENDLDataGenerator()
  { /* ... */ }

  //! Populate the ENDL data container
  virtual void populateENDLDataContainer( 
        Data::EvaluatedElectronVolatileDataContainer&
        data_container ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::EvaluatedElectronVolatileDataContainer&
			data_container ) const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

private:

  // The atomic number for data being generated
  unsigned d_atomic_number;
};

} // end DataGen namespace

#endif // end DATA_GEN_ENDL_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ENDLDataGenerator.hpp
//---------------------------------------------------------------------------//

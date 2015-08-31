//---------------------------------------------------------------------------//
//!
//! \file   DataGen_EvaluatedElectronDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The soft elastic electron scattering data generator bazse decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_EVALUATED_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_EVALUATED_ELECTRON_DATA_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"

namespace DataGen{

//! The soft elastic electron scattering data generator
class EvaluatedElectronDataGenerator
{

public:

  //! Constructor
  EvaluatedElectronDataGenerator( const unsigned atomic_number );

  //! Destructor
  virtual ~EvaluatedElectronDataGenerator()
  { /* ... */ }

  //! Populate the soft elastic electron data container
  virtual void populateEvaluatedDataContainer( 
                        Data::EvaluatedElectronVolatileDataContainer&
                        data_container ) const = 0;

protected:

  //! Set the atomic number
  void setAtomicNumber( Data::EvaluatedElectronVolatileDataContainer&
                        data_container ) const;

  //! Get the atomic number
  unsigned getAtomicNumber() const;

private:

  // The atomic number for which soft elastic data can be generated
  unsigned d_atomic_number;
};

} // end DataGen namespace

#endif // end DATA_GEN_EVALUATED_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_EvaluatedElectronDataGenerator.hpp
//---------------------------------------------------------------------------//

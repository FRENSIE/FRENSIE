//---------------------------------------------------------------------------//
//!
//! \file    SprngFactory.hpp
//! \author  Alex Robinson
//! \brief   Declaration of a Simple struct to aid the Sprng class 
//!
//---------------------------------------------------------------------------//

#ifndef SPRNG_FACTORY_HPP
#define SPRNG_FACTORY_HPP

// SPRNG Includes
#include "Sprng.hpp"
#include "GeneratorType.hpp"

namespace sprng{

//! Main Sprng factory class
class SprngFactory
{

public:

  //! Typedef for generator pointer
  typedef Sprng* SprngPtr;

  //! Constructor
  SprngFactory( const GeneratorType gtype );

  //! Destructor
  ~SprngFactory()
  { /* ... */ }

  //! Generator creation method
  SprngPtr create() const;

private:
  
  // Generator type
  GeneratorType d_gen_type;
};

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "SprngFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SPRNG_FACTORY_HPP

//---------------------------------------------------------------------------//
// end SprngFactory.hpp
//---------------------------------------------------------------------------//

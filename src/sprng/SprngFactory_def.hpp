//---------------------------------------------------------------------------//
//!
//! \file    SprngFactory_def.hpp
//! \author  Alex Robinson
//! \brief   Definition of a Simple struct to aid the Sprng class 
//!
//---------------------------------------------------------------------------//

#ifndef SPRNG_FACTORY_DEF_HPP
#define SPRNG_FACTORY_DEF_HPP

// SPRNG Includes
#include "LFG.hpp"
#include "LCG.hpp"
#include "LCG64.hpp"
#include "CMRG.hpp"
#include "MLFG.hpp"
#include "PMLCG.hpp"

namespace sprng{

// Constructor
SprngFactory::SprngFactory( const GeneratorType gtype )
  : d_gen_type( gtype )
{ /* ... */ }

// Generator creation method
SprngFactory::SprngPtr SprngFactory::create() const
{
  switch( d_gen_type )
  {
  case LFG: return new LFG;
  case LCG: return new LCG;
  case LCG64: return new LCG64;
  case CMRG: return new CMRG;
  case MLFG: return new MLFG;
  case PMLCG: return new PMLCG;
  }
}

} // end namespace sprng

#endif // end SPRNG_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end SprngFactory_def.hpp
//---------------------------------------------------------------------------//

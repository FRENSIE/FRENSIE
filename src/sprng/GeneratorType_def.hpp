//---------------------------------------------------------------------------//
//!
//! \file   GeneratorType_def.hpp
//! \author Alex Robinson
//! \brief  Enumeration for the different types of generators
//!
//---------------------------------------------------------------------------//

#ifndef GENERATOR_TYPE_DEF_HPP
#define GENERATOR_TYPE_DEF_HPP

// Std Lib Includes
#include <assert.h>

namespace sprng{

// Convert a GeneratorType to an int
int generatorTypeToInt( const GeneratorType gtype )
{
  switch( gtype )
  {
  case LFG: return 0;
  case LCG: return 1;
  case LCG64: return 2;
  case CMRG: return 3;
  case MLFG: return 4;
  case PMLCG: return 5;
  }
}

// Convert an int to a GeneratorType
GeneratorType intToGeneratorType( const int gtype )
{
  assert( gtype >= 0 && gtype <= 5 );

  switch( gtype )
  {
  case 0: return LFG;
  case 1: return LCG;
  case 2: return LCG64;
  case 3: return CMRG;
  case 4: return MLFG;
  case 5: return PMLCG;
  }
}


} // end namespace sprng

#endif // end GENERATOR_TYPE_DEF_HPP

//---------------------------------------------------------------------------//
// end GeneratorType_def.hpp
//---------------------------------------------------------------------------//

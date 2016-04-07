//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfileSubshellConverterFactory_def.hpp
//! \author Alex Robinson
//! \brief  Compton profile subshell-to-index converter factory definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_DEF_HPP
#define MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_StandardComptonProfileSubshellConverter.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Create the converter
template<template<typename> class SmartPointer>
void ComptonProfileSubshellConverterFactory::createConverter( 
		      SmartPointer<ComptonProfileSubshellConverter>& converter,
		      const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0u );
  testPrecondition( atomic_number <= 100u );
  
  switch( atomic_number )
  {
  case 1u: 
    converter.reset( new StandardComptonProfileSubshellConverter<1u> );
    break;
  case 2u:
    converter.reset( new StandardComptonProfileSubshellConverter<2u> );
    break;
  case 3u:
    converter.reset( new StandardComptonProfileSubshellConverter<3u> );
    break;
  case 4u:
    converter.reset( new StandardComptonProfileSubshellConverter<4u> );
    break;
  case 5u:
    converter.reset( new StandardComptonProfileSubshellConverter<5u> );
    break;
  case 6u:
    converter.reset( new StandardComptonProfileSubshellConverter<6u> );
    break;
  case 7u:
    converter.reset( new StandardComptonProfileSubshellConverter<7u> );
    break;
  case 8u:
    converter.reset( new StandardComptonProfileSubshellConverter<8u> );
    break;
  case 9u:
    converter.reset( new StandardComptonProfileSubshellConverter<9u> );
    break;
  case 10u:
    converter.reset( new StandardComptonProfileSubshellConverter<10u> );
    break;
  case 11u:
    converter.reset( new StandardComptonProfileSubshellConverter<11u> );
    break;
  case 12u:
    converter.reset( new StandardComptonProfileSubshellConverter<12u> );
    break;
  case 13u:
    converter.reset( new StandardComptonProfileSubshellConverter<13u> );
    break;
  case 14u:
    converter.reset( new StandardComptonProfileSubshellConverter<14u> );
    break;
  case 15u:
    converter.reset( new StandardComptonProfileSubshellConverter<15u> );
    break;
  case 16u:
    converter.reset( new StandardComptonProfileSubshellConverter<16u> );
    break;
  case 17u:
    converter.reset( new StandardComptonProfileSubshellConverter<17u> );
    break;
  case 18u:
    converter.reset( new StandardComptonProfileSubshellConverter<18u> );
    break;
  case 19u:
    converter.reset( new StandardComptonProfileSubshellConverter<19u> );
    break;
  case 20u:
    converter.reset( new StandardComptonProfileSubshellConverter<20u> );
    break;
  case 21u:
    converter.reset( new StandardComptonProfileSubshellConverter<21u> );
    break;
  case 22u:
    converter.reset( new StandardComptonProfileSubshellConverter<22u> );
    break;
  case 23u:
    converter.reset( new StandardComptonProfileSubshellConverter<23u> );
    break;
  case 24u:
    converter.reset( new StandardComptonProfileSubshellConverter<24u> );
    break;
  case 25u:
    converter.reset( new StandardComptonProfileSubshellConverter<25u> );
    break;
  case 26u:
    converter.reset( new StandardComptonProfileSubshellConverter<26u> );
    break;
  case 27u:
    converter.reset( new StandardComptonProfileSubshellConverter<27u> );
    break;
  case 28u:
    converter.reset( new StandardComptonProfileSubshellConverter<28u> );
    break;
  case 29u:
    converter.reset( new StandardComptonProfileSubshellConverter<29u> );
    break;
  case 30u:
    converter.reset( new StandardComptonProfileSubshellConverter<30u> );
    break;
  case 31u:
    converter.reset( new StandardComptonProfileSubshellConverter<31u> );
    break;
  case 32u:
    converter.reset( new StandardComptonProfileSubshellConverter<32u> );
    break;
  case 33u:
    converter.reset( new StandardComptonProfileSubshellConverter<33u> );
    break;
  case 34u:
    converter.reset( new StandardComptonProfileSubshellConverter<34u> );
    break;
  case 35u:
    converter.reset( new StandardComptonProfileSubshellConverter<35u> );
    break;
  case 36u:
    converter.reset( new StandardComptonProfileSubshellConverter<36u> );
    break;
  case 37u:
    converter.reset( new StandardComptonProfileSubshellConverter<37u> );
    break;
  case 38u:
    converter.reset( new StandardComptonProfileSubshellConverter<38u> );
    break;
  case 39u:
    converter.reset( new StandardComptonProfileSubshellConverter<39u> );
    break;
  case 40u:
    converter.reset( new StandardComptonProfileSubshellConverter<40u> );
    break;
  case 41u:
    converter.reset( new StandardComptonProfileSubshellConverter<41u> );
    break;
  case 42u:
    converter.reset( new StandardComptonProfileSubshellConverter<42u> );
    break;
  case 43u:
    converter.reset( new StandardComptonProfileSubshellConverter<43u> );
    break;
  case 44u:
    converter.reset( new StandardComptonProfileSubshellConverter<44u> );
    break;
  case 45u:
    converter.reset( new StandardComptonProfileSubshellConverter<45u> );
    break;
  case 46u:
    converter.reset( new StandardComptonProfileSubshellConverter<46u> );
    break;
  case 47u:
    converter.reset( new StandardComptonProfileSubshellConverter<47u> );
    break;
  case 48u:
    converter.reset( new StandardComptonProfileSubshellConverter<48u> );
    break;
  case 49u:
    converter.reset( new StandardComptonProfileSubshellConverter<49u> );
    break;
  case 50u:
    converter.reset( new StandardComptonProfileSubshellConverter<50u> );
    break;
  case 51u:
    converter.reset( new StandardComptonProfileSubshellConverter<51u> );
    break;
  case 52u:
    converter.reset( new StandardComptonProfileSubshellConverter<52u> );
    break;
  case 53u:
    converter.reset( new StandardComptonProfileSubshellConverter<53u> );
    break;
  case 54u:
    converter.reset( new StandardComptonProfileSubshellConverter<54u> );
    break;
  case 55u:
    converter.reset( new StandardComptonProfileSubshellConverter<55u> );
    break;
  case 56u:
    converter.reset( new StandardComptonProfileSubshellConverter<56u> );
    break;
  case 57u:
    converter.reset( new StandardComptonProfileSubshellConverter<57u> );
    break;
  case 58u:
    converter.reset( new StandardComptonProfileSubshellConverter<58u> );
    break;
  case 59u:
    converter.reset( new StandardComptonProfileSubshellConverter<59u> );
    break;
  case 60u:
    converter.reset( new StandardComptonProfileSubshellConverter<60u> );
    break;
  case 61u:
    converter.reset( new StandardComptonProfileSubshellConverter<61u> );
    break;
  case 62u:
    converter.reset( new StandardComptonProfileSubshellConverter<62u> );
    break;
  case 63u:
    converter.reset( new StandardComptonProfileSubshellConverter<63u> );
    break;
  case 64u:
    converter.reset( new StandardComptonProfileSubshellConverter<64u> );
    break;
  case 65u:
    converter.reset( new StandardComptonProfileSubshellConverter<65u> );
    break;
  case 66u:
    converter.reset( new StandardComptonProfileSubshellConverter<66u> );
    break;
  case 67u:
    converter.reset( new StandardComptonProfileSubshellConverter<67u> );
    break;
  case 68u:
    converter.reset( new StandardComptonProfileSubshellConverter<68u> );
    break;
  case 69u:
    converter.reset( new StandardComptonProfileSubshellConverter<69u> );
    break;
  case 70u:
    converter.reset( new StandardComptonProfileSubshellConverter<70u> );
    break;
  case 71u:
    converter.reset( new StandardComptonProfileSubshellConverter<71u> );
    break;
  case 72u:
    converter.reset( new StandardComptonProfileSubshellConverter<72u> );
    break;
  case 73u:
    converter.reset( new StandardComptonProfileSubshellConverter<73u> );
    break;
  case 74u:
    converter.reset( new StandardComptonProfileSubshellConverter<74u> );
    break;
  case 75u:
    converter.reset( new StandardComptonProfileSubshellConverter<75u> );
    break;
  case 76u:
    converter.reset( new StandardComptonProfileSubshellConverter<76u> );
    break;
  case 77u:
    converter.reset( new StandardComptonProfileSubshellConverter<77u> );
    break;
  case 78u:
    converter.reset( new StandardComptonProfileSubshellConverter<78u> );
    break;
  case 79u:
    converter.reset( new StandardComptonProfileSubshellConverter<79u> );
    break;
  case 80u:
    converter.reset( new StandardComptonProfileSubshellConverter<80u> );
    break;
  case 81u:
    converter.reset( new StandardComptonProfileSubshellConverter<81u> );
    break;
  case 82u:
    converter.reset( new StandardComptonProfileSubshellConverter<82u> );
    break;
  case 83u:
    converter.reset( new StandardComptonProfileSubshellConverter<83u> );
    break;
  case 84u:
    converter.reset( new StandardComptonProfileSubshellConverter<84u> );
    break;
  case 85u:
    converter.reset( new StandardComptonProfileSubshellConverter<85u> );
    break;
  case 86u:
    converter.reset( new StandardComptonProfileSubshellConverter<86u> );
    break;
  case 87u:
    converter.reset( new StandardComptonProfileSubshellConverter<87u> );
    break;
  case 88u:
    converter.reset( new StandardComptonProfileSubshellConverter<88u> );
    break;
  case 89u:
    converter.reset( new StandardComptonProfileSubshellConverter<89u> );
    break;
  case 90u:
    converter.reset( new StandardComptonProfileSubshellConverter<90u> );
    break;
  case 91u:
    converter.reset( new StandardComptonProfileSubshellConverter<91u> );
    break;
  case 92u:
    converter.reset( new StandardComptonProfileSubshellConverter<92u> );
    break;
  case 93u:
    converter.reset( new StandardComptonProfileSubshellConverter<93u> );
    break;
  case 94u:
    converter.reset( new StandardComptonProfileSubshellConverter<94u> );
    break;
  case 95u:
    converter.reset( new StandardComptonProfileSubshellConverter<95u> );
    break;
  case 96u:
    converter.reset( new StandardComptonProfileSubshellConverter<96u> );
    break;
  case 97u:
    converter.reset( new StandardComptonProfileSubshellConverter<97u> );
    break;
  case 98u:
    converter.reset( new StandardComptonProfileSubshellConverter<98u> );
    break;
  case 99u:
    converter.reset( new StandardComptonProfileSubshellConverter<99u> );
    break;
  case 100u:
    converter.reset( new StandardComptonProfileSubshellConverter<100u> );
    break;
  default:
    THROW_EXCEPTION( std::logic_error, 
		     "Error: Z " << atomic_number << " is invalid!" );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_SUBSHELL_CONVERTER_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfileSubshellConverterFactory_def.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MaterialHelpers.hpp
//! \author Alex Robinson
//! \brief  Material helper functions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_HELPERS_HPP
#define MONTE_CARLO_MATERIAL_HELPERS_HPP

// Std Lib Includes
#include <iterator>

// FRENSIE Includes
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! Test if a set of fractional values are valid
template<size_t member, typename Iterator>
bool areFractionValuesValid( Iterator start, Iterator end );

//! Test if a set of fractional values are valid
template<typename Iterator>
bool areFractionValuesValid( Iterator start, Iterator end );

//! Test if a set of fractional values are normalized
template<size_t member, typename Iterator>
bool areFractionValuesNormalized( Iterator start, Iterator end );

//! Test if a set of fractional values are normalized
template<typename Iterator>
bool areFractionValuesNormalized( Iterator start, Iterator end );

//! Normalize a set of fractions
template<size_t member, typename Iterator>
void normalizeFractionValues( Iterator start, Iterator end );

//! Normalize a set of fractions
template<typename Iterator>
void normalizeFractionValues( Iterator start, Iterator end );

//! Convert a set of weight fractions to atom fractions
template<size_t fracMember,
	 size_t atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator,
         typename Extractor>
void convertWeightFractionsToAtomFractions(
 FracIterator frac_start,
 FracIterator frac_end,
 AtomicWgtIterator atomic_wgt_start,
 AtomicWgtIterator atomic_wgt_end,
 Extractor atomic_wgt_extractor );

//! Convert a set of weight fractions to atom fractions
template<size_t fracMember,
	 size_t atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator>
void convertWeightFractionsToAtomFractions(
 FracIterator frac_start,
 FracIterator frac_end,
 AtomicWgtIterator atomic_wgt_start,
 AtomicWgtIterator atomic_wgt_end );

//! Convert a set of weight fractions to atom fractions
template<typename FracIterator, typename AtomicWgtIterator>
void convertWeightFractionsToAtomFractions( FracIterator frac_start,
					    FracIterator frac_end,
					    AtomicWgtIterator atomic_wgt_start,
					    AtomicWgtIterator atomic_wgt_end );

//! Convert a mass density (g/cm^3) to a number density (atom/b-cm)
template<size_t fracMember,
	 size_t atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator,
         typename Extractor>
double convertMassDensityToNumberDensity( const double mass_density,
                                          FracIterator frac_start,
                                          FracIterator frac_end,
                                          AtomicWgtIterator atomic_wgt_start,
                                          AtomicWgtIterator atomic_wgt_end,
                                          Extractor atomic_wgt_extractor );

//! Convert a mass density (g/cm^3) to a number density (atom/b-cm)
template<size_t fracMember,
	 size_t atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator>
double convertMassDensityToNumberDensity( const double mass_density,
                                          FracIterator frac_start,
                                          FracIterator frac_end,
                                          AtomicWgtIterator atomic_wgt_start,
                                          AtomicWgtIterator atomic_wgt_end );

//! Convert a mass density (g/cm^3) to a number density (atom/b-cm)
template<typename FracIterator, typename AtomicWgtIterator>
double convertMassDensityToNumberDensity( const double mass_density,
					  FracIterator frac_start,
					  FracIterator frac_end,
					  AtomicWgtIterator atomic_wgt_start,
					  AtomicWgtIterator atomic_wgt_end );

//! Scale atom fractions by a number density (atom/b-cm)
template<size_t member, typename Iterator>
void scaleAtomFractionsByNumberDensity( const double number_density,
					Iterator start,
					Iterator end );

//! Scale atom fractions by a number density (atom/b-cm)
template<typename Iterator>
void scaleAtomFractionsByNumberDensity( const double number_density,
					Iterator start,
					Iterator end );


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_MaterialHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MonteCarlo_MATERIAL_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MaterialHelpers.hpp
//---------------------------------------------------------------------------//

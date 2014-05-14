//---------------------------------------------------------------------------//
//!
//! \file   MaterialHelpers.hpp
//! \author Alex Robinson
//! \brief  Material helper functions
//!
//---------------------------------------------------------------------------//

#ifndef MATERIAL_HELPERS_HPP
#define MATERIAL_HELPERS_HPP

// Std Lib Includes
#include <iterator>

// FACEMC Includes
#include "TupleMemberTraits.hpp"

namespace FACEMC{

//! Test if a set of fractional values are valid
template<TupleMember member, typename Iterator>
bool areFractionValuesValid( Iterator start, Iterator end );

//! Test if a set of fractional values are valid
template<typename Iterator>
bool areFractionValuesValid( Iterator start, Iterator end );

//! Test if a set of fractional values are normalized
template<TupleMember member, typename Iterator>
bool areFractionValuesNormalized( Iterator start, Iterator end );

//! Test if a set of fractional values are normalized
template<typename Iterator>
bool areFractionValuesNormalized( Iterator start, Iterator end );

//! Normalize a set of fractions
template<TupleMember member, typename Iterator>
void normalizeFractionValues( Iterator start, Iterator end );

//! Normalize a set of fractions
template<typename Iterator>
void normalizeFractionValues( Iterator start, Iterator end );

//! Convert a set of weight fractions to atom fractions
template<TupleMember fracMember, 
	 TupleMember atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator>
void convertWeightFractionsToAtomFractions( 
 FracIterator frac_start, 
 FracIterator frac_end,
 AtomicWgtIterator atomic_wgt_start,
 AtomicWgtIterator atomic_wgt_end,
 double (*extractor)( const typename std::iterator_traits<AtomicWgtIterator>::value_type& )
 = &get<atomicWgtMember,typename std::iterator_traits<AtomicWgtIterator>::value_type> );

//! Convert a set of weight fractions to atom fractions
template<typename FracIterator, typename AtomicWgtIterator>
void convertWeightFractionsToAtomFractions( FracIterator frac_start, 
					    FracIterator frac_end,
					    AtomicWgtIterator atomic_wgt_start,
					    AtomicWgtIterator atomic_wgt_end );

//! Convert a mass density (g/cm^3) to a number density (atom/b-cm)
template<TupleMember fracMember, 
	 TupleMember atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator>
double convertMassDensityToNumberDensity( 
 const double mass_density,
 FracIterator frac_start, 
 FracIterator frac_end,
 AtomicWgtIterator atomic_wgt_start,
 AtomicWgtIterator atomic_wgt_end,
 double (*extractor)( const typename std::iterator_traits<AtomicWgtIterator>::value_type& )
 = &get<atomicWgtMember,typename std::iterator_traits<AtomicWgtIterator>::value_type> );

//! Convert a mass density (g/cm^3) to a number density (atom/b-cm)
template<typename FracIterator, typename AtomicWgtIterator>
double convertMassDensityToNumberDensity( const double mass_density,
					  FracIterator frac_start, 
					  FracIterator frac_end,
					  AtomicWgtIterator atomic_wgt_start,
					  AtomicWgtIterator atomic_wgt_end );

//! Scale atom fractions by a number density (atom/b-cm)
template<TupleMember member, typename Iterator>
void scaleAtomFractionsByNumberDensity( const double number_density,
					Iterator start,
					Iterator end );

//! Scale atom fractions by a number density (atom/b-cm)
template<typename Iterator>
void scaleAtomFractionsByNumberDensity( const double number_density,
					Iterator start,
					Iterator end );


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MaterialHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MATERIAL_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MaterialHelpers.hpp
//---------------------------------------------------------------------------//

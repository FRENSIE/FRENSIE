//---------------------------------------------------------------------------//
//!
//! \file   MaterialHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Material helper functions
//!
//---------------------------------------------------------------------------//

#ifndef MATERIAL_HELPERS_DEF_HPP
#define MATERIAL_HELPERS_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Test if a set of fractional values are valid
/*! \details Fractional values for a set of nuclides can be weight fractions or
 * atom fractions but not both. Weight fractions will be given as negative 
 * numbers while atom fractions will be given as positive numbers. This 
 * function will check that all values are non-zero have a consistent sign.
 */
template<TupleMember member, typename Iterator>
bool areFractionValuesValid( Iterator start, Iterator end )
{
  // Make sure the container is not empty
  testPrecondition( start != end );
  
  if( get<member>( *start ) == 0.0 )
    return false;

  bool sign = get<member>( *start ) > 0.0;

  ++start;

  bool valid = true;
  
  while( start != end )
  {
    if( get<member>( *start ) == 0.0 )
    {
      valid = false;
      break;
    }
    
    if( (get<member>( *start ) > 0.0) != sign )
    {
      valid = false;
      break;
    }

    ++start;
  }

  return valid;
}

// Test if a set of fractional values are valid
/*! \details This function allows simple arrays (non-tuple) to be checked for
 * valid fractions.
 */
template<typename Iterator>
inline bool areFractionValuesValid( Iterator start, Iterator end )
{
  return areFractionValuesValid<FIRST>( start, end );
}

// Test if a set of fractional values are normalized
template<TupleMember member, typename Iterator>
bool areFractionValuesNormalized( Iterator start, Iterator end )
{
  double sum = 0.0;

  while( start != end )
  {
    sum += get<member>( *start );

    ++start;
  }

  sum = Teuchos::ScalarTraits<double>::magnitude( sum );
  
  if( Teuchos::ScalarTraits<double>::magnitude( sum - 1.0 ) <
      Teuchos::ScalarTraits<double>::eps() )
    return true;
  else
    return false;
}

// Normalize a set of fractions
/*! \details This function allows simple arrays (non-tuple) to be checked if
 * normalized.
 */
template<typename Iterator>
inline bool areFractionValuesNormalized( Iterator start, Iterator end )
{
  return areFractionValuesNormalized<FIRST>( start, end );
}

// Normalize a set of fractions
template<TupleMember member, typename Iterator>
void normalizeFractionValues( Iterator start, Iterator end )
{
  Iterator start_copy = start;
  
  double sum = 0.0;

  while( start != end )
  {
    sum += get<member>( *start );

    ++start;
  }

  sum = Teuchos::ScalarTraits<double>::magnitude( sum );
  
  start = start_copy;

  while( start != end )
  {
    set<member>( *start, get<member>( *start )/sum );

    ++start;
  }

  // Make sure the fraction values were successfully normalized.
  remember( start = start_copy );
  testPostcondition( areFractionValuesNormalized<member>( start, end ) );
}

// Normalize a set of fractions
/*! \details This function allows simple arrays (non-tuple) to be normalized.
 */
template<typename Iterator>
inline void normalizeFractionValues( Iterator start, Iterator end )
{
  return normalizeFractionValues<FIRST>( start, end );
}

// Convert a set of weight fractions to atom fractions
template<TupleMember fracMember, 
	 TupleMember atomicWgtMember,
	 typename FracIterator,
	 typename AtomicWgtIterator>
void convertWeightFractionsToAtomFractions( 
  FracIterator frac_start, 
  FracIterator frac_end,
  AtomicWgtIterator atomic_wgt_start,
  AtomicWgtIterator atomic_wgt_end,
  double (*extractor)( const typename std::iterator_traits<AtomicWgtIterator>::value_type& ) )
{
  // Make sure the containers have the same size
  testPrecondition( std::distance( frac_start, frac_end ) ==
		    std::distance( atomic_wgt_start, atomic_wgt_end ) );
  // Make sure the fractions are valid
  testPrecondition( areFractionValuesValid<fracMember>(frac_start, frac_end) );

  // Only conduct the conversion if the fractions are weight fractions
  if( get<fracMember>( *frac_start ) < 0.0 )
  {
    FracIterator frac_start_copy = frac_start;
    AtomicWgtIterator atomic_wgt_start_copy = atomic_wgt_start;

    // Divide each weight fraction by its corresponding atomic weight
    while( frac_start != frac_end )
    {
      set<fracMember>( *frac_start, 
		   -1.0*get<fracMember>( *frac_start )/
		   extractor( *atomic_wgt_start ) );

      ++frac_start;
      ++atomic_wgt_start;
    }

    frac_start = frac_start_copy;
    atomic_wgt_start = atomic_wgt_start_copy;

    // Sum all of the ratios
    double sum = 0.0;
    
    while( frac_start != frac_end )
    {
      sum += get<fracMember>( *frac_start );

      ++frac_start;
    }

    frac_start = frac_start_copy;

    // Divide all of the ratios by the sum
    while( frac_start != frac_end )
    {
      set<fracMember>( *frac_start, get<fracMember>( *frac_start )/sum );

      ++frac_start;
    }
  }
}

// Convert a set of weight fractions to atom fractions
/*! \details This function allows simple arrays (non-tuple) of weight
 * fractions to be converted to atom fractions.
 */
template<typename FracIterator, typename AtomicWgtIterator>
inline void convertWeightFractionsToAtomFractions( 
					    FracIterator frac_start, 
					    FracIterator frac_end,
					    AtomicWgtIterator atomic_wgt_start,
					    AtomicWgtIterator atomic_wgt_end )
{
  convertWeightFractionsToAtomFractions<FIRST,FIRST>( frac_start, 
						      frac_end,
						      atomic_wgt_start,
						      atomic_wgt_end );
}

// Convert a mass density (g/cm^3) to a number density (atom/b-cm)
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
  double (*extractor)( const typename std::iterator_traits<AtomicWgtIterator>::value_type& ) )
{
  // Make sure the mass density is valid
  testPrecondition( mass_density > 0.0 );
  // Make sure the containers have the same size
  testPrecondition( std::distance( frac_start, frac_end ) ==
		    std::distance( atomic_wgt_start, atomic_wgt_end ) );
  // Make sure the fractions are valid
  testPrecondition( areFractionValuesValid<fracMember>(frac_start, frac_end) );
  testPrecondition( get<fracMember>( *frac_start ) > 0.0 );
  // Make sure the fractions are normalized
  testPrecondition( areFractionValuesNormalized<fracMember>( frac_start,
							     frac_end ) );
  
  double effective_atomic_weight = 0.0;

  // Calculate the effective atomic weight
  while( frac_start != frac_end )
  {
    effective_atomic_weight += get<fracMember>( *frac_start )*
      extractor( *atomic_wgt_start );

    ++frac_start;
    ++atomic_wgt_start;
  }
  
  // Calculate the number density
  return mass_density/effective_atomic_weight*
    PhysicalConstants::avogadro_constant*1e-24;
}

// Convert a mass density (g/cm^3) to a number density (atom/b-cm)
/*! \details This function allows the mass density to be converted to a
 * number density using simple arrays (non-tuple) of atom fractions
 */
template<typename FracIterator, typename AtomicWgtIterator>
inline double convertMassDensityToNumberDensity( 
					    const double mass_density,
					    FracIterator frac_start, 
					    FracIterator frac_end,
					    AtomicWgtIterator atomic_wgt_start,
					    AtomicWgtIterator atomic_wgt_end )
{
  return convertMassDensityToNumberDensity<FIRST,FIRST>( mass_density,
							 frac_start,
							 frac_end,
							 atomic_wgt_start,
							 atomic_wgt_end );
}

// Scale atom fractions by a number density (atom/b-cm)
template<TupleMember member, typename Iterator>
void scaleAtomFractionsByNumberDensity( const double number_density,
					Iterator start,
					Iterator end )
{
  // Make sure the number density is valid
  testPrecondition( number_density > 0.0 );
  // Make sure the container is not empty
  testPrecondition( start != end );
  // Make sure the fractions are valid
  testPrecondition( areFractionValuesValid<member>( start, end ) );
  testPrecondition( get<member>( *start ) > 0.0 );
  // Make sure the fractions are normalized
  testPrecondition( areFractionValuesNormalized<member>( start, end ) );

  while( start != end )
  {
    set<member>( *start, get<member>( *start )*number_density );

    ++start;
  }
}

// Scale atom fractions by a number density (atom/b-cm)
/*! \details This function allows a simple arrays (non-tuple) of atom fractions
 * to be scaled by a number density.
 */
template<typename Iterator>
inline void scaleAtomFractionsByNumberDensity( const double number_density,
					       Iterator start,
					       Iterator end )
{
  scaleAtomFractionsByNumberDensity<FIRST>( number_density, start, end );
}

} // end FACEMC namespace

#endif // end MATERIAL_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MaterialHelpers_def.hpp
//---------------------------------------------------------------------------//

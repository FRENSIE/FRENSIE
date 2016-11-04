//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularOneDDistribution.hpp
//! \author Alex Robinson
//! \brief  Tabular one-dimensional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP
#define UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace Utility{

/*! The unit-aware tabular one-dimensional distribution declaration
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareTabularOneDDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>
{

public:

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Constructor
  UnitAwareTabularOneDDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~UnitAwareTabularOneDDistribution()
  { /* ... */ }

  //! Evaluate the CDF
  virtual double evaluateCDF( const IndepQuantity indep_var_value ) const = 0;

  //! Return a random sample from the distribution and the sampled index
  virtual IndepQuantity sampleAndRecordBinIndex(
				       unsigned& sampled_bin_index ) const = 0;

  //! Return a random sample from the distribution at the given CDF value
  virtual IndepQuantity sampleWithRandomNumber( const double random_number ) const = 0;

  //! Return a random sample from the distribution in a subrange
  virtual IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const = 0;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  virtual IndepQuantity sampleWithRandomNumberInSubrange(
				 const double random_number,
				 const IndepQuantity max_indep_var ) const = 0;

  //! Test if the distribution is tabular
  bool isTabular() const;
};

// Test if the distribution is tabular
template<typename IndependentUnit, typename DependentUnit>
inline bool UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::isTabular() const
{
  return true;
}

/*! The tabular one-dimensional distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareTabularOneDDistribution<void,void> TabularOneDDistribution;

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularOneDDistribution<void,void> );

} // end Utility namespace

#endif // end UTILITY_TABULAR_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularOneDDistribution.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramPartiallyTabularBasicBivariateDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The histogram partially tabular two-dimensional dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP
#define UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

BOOST_SERIALIZATION_DISTRIBUTION3_EXPORT_IMPLEMENT( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution );

namespace Utility{

// Constructor
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareHistogramPartiallyTabularBasicBivariateDistribution(
       const std::vector<PrimaryIndepQuantity>& primary_indep_grid,
       const std::vector<std::shared_ptr<const BaseUnivariateDistributionType>&
       secondary_distributions )
  : BaseType( primary_indep_grid, secondary_distributions )
{ /* ... */ }

// Method for placing the object in an output stream
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
void UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamTabularDistImpl( os, "HistogramPartiallyTabularBasicBivariateDistribution" );
}
  
// Save the distribution to an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}

// Load the distribution from an archive
template<typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename Archive>
void UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );
}
  
} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareHistogramPartiallyTabularBasicBivariateDistribution<void,void,void> );

#endif // end UTILITY_HISTOGRAM_PARTIALLY_TABULAR_BASIC_BIVARIATE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramPartiallyTabularBasicBivariateDistribution_def.hpp
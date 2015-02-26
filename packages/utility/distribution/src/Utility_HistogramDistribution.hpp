//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution.hpp
//! \author Alex Robinson
//! \brief  Histogram distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_DISTRIBUTION_HPP
#define UTILITY_HISTOGRAM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_XMLCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Histogram distribution class
class HistogramDistribution : public OneDDistribution,
			      public XMLCompatibleObject<HistogramDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  HistogramDistribution();

  //! Constructor (data owning)
  HistogramDistribution( const Teuchos::Array<double>& bin_boundaries,
			             const Teuchos::Array<double>& bin_values,
                         const bool interpret_dependent_values_as_cdf = false );

  //! Copy constructor
  HistogramDistribution( const HistogramDistribution& dist_instance );

  //! Assignment operator
  HistogramDistribution& operator=( 
				  const HistogramDistribution& dist_instance );

  //! Destructor
  ~HistogramDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return a random sample and bin index from the distribution
  double sample( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the corresponding CDF in a subrange
  double sample( const double max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value
  double sampleCDFValue( const double CDF_value ) const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const HistogramDistribution& other ) const;
  
private:

  // Initialize the distribution
  void initializeDistribution( const Teuchos::Array<double>& bin_boundaries,
			                   const Teuchos::Array<double>& bin_values );

  // The distribution type
  static const OneDDistributionType distribution_type = HISTOGRAM_DISTRIBUTION;

  // The distribution (first = bin_min, second = bin_PDF, third = bin_CDF)
  // Note: The bin_CDF value is the value of the CDF at the lower bin boundary
  Teuchos::Array<Trip<double,double,double> > d_distribution;
  
  // The normalization constant
  double d_norm_constant;
};

// Return a random sample from the distribution
inline double HistogramDistribution::sample() 
{
  return (const_cast<const HistogramDistribution*>(this))->sample();
}

// Return a random sample from the distribution
inline double HistogramDistribution::sample() const
{
  unsigned bin_index;
  
  return this->sample( bin_index );
}

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::HistogramDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::HistogramDistribution>
{
public:
  static std::string name()
  {
    return "Histogram Distribution";
  }
  static std::string concreteName( 
			       const Utility::HistogramDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.hpp
//---------------------------------------------------------------------------//

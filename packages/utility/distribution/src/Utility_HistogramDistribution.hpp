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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Histogram distribution class
class HistogramDistribution : public TabularOneDDistribution,
			      public ParameterListCompatibleObject<HistogramDistribution>
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
  double sample() const;

  //! Return a random sample and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample and bin index from the distribution
  double sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  double sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the corresponding CDF in a subrange
  double sampleInSubrange( const double max_indep_var ) const;

  //! Return a sample from the distribution at the given CDF value in a subrange
  double sampleWithRandomNumberInSubrange( const double random_number,
					   const double max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

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

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // The distribution type
  static const OneDDistributionType distribution_type = HISTOGRAM_DISTRIBUTION;

  // The distribution (first = bin_min, second = bin_PDF, third = bin_CDF)
  // Note: The bin_CDF value is the value of the CDF at the lower bin boundary
  Teuchos::Array<Trip<double,double,double> > d_distribution;
  
  // The normalization constant
  double d_norm_constant;
};

// Return a random sample using the random number and record the bin index
inline double HistogramDistribution::sampleImplementation( 
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  Teuchos::Array<Trip<double,double,double> >::const_iterator bin = 
    Search::binaryLowerBound<THIRD>( d_distribution.begin(),
                                     d_distribution.end(),
                                     random_number );

  sampled_bin_index = std::distance( d_distribution.begin(), bin );

  return bin->first + (random_number - bin->third)/bin->second;
}

// Return a sample from the distribution at the given CDF value in a subrange
double HistogramDistribution::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
  
  // Compute the scaled random number
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;
    
  return this->sampleImplementation( scaled_random_number, dummy_index );
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

//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISCRETE_DISTRIBUTION_HPP
#define UTILITY_DISCRETE_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Discrete distribution class
class DiscreteDistribution : public TabularOneDDistribution,
			     public ParameterListCompatibleObject<DiscreteDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default Constructor
  DiscreteDistribution();

  //! Constructor 
  DiscreteDistribution( const Teuchos::Array<double>& independent_values,
			const Teuchos::Array<double>& dependent_values,
			const bool interpret_dependent_values_as_cdf = false );
  
  //! Copy constructor
  DiscreteDistribution( const DiscreteDistribution& dist_instance );

  //! Assignment operator
  DiscreteDistribution& operator=( const DiscreteDistribution& dist_instance );

  //! Destructor
  ~DiscreteDistribution()
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

  //! Return a random sample and sampled index from the distribution
  double sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  double sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the distribution in a subrange
  double sampleInSubrange( const double max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  double sampleWithRandomNumberInSubrange( const double random_number,
					   const double max_indep_var ) const;
  

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the independent variable
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
  bool isEqual( const DiscreteDistribution& other ) const;

private:

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values );

  // The distribution type
  static const OneDDistributionType distribution_type = DISCRETE_DISTRIBUTION;

  // The distribution (first = independent value, second = CDF)
  Teuchos::Array<Pair<double,double> > d_distribution;

  // The distribution normalization constant
  double d_norm_constant;
};

// Return a random sample using the random number and record the bin index
inline double DiscreteDistribution::sampleImplementation( 
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  Teuchos::Array<Pair<double,double> >::const_iterator sample = 
    Search::binaryUpperBound<SECOND>( d_distribution.begin(),
				      d_distribution.end(),
				      random_number );

  // Get the bin index sampled
  sampled_bin_index = std::distance( d_distribution.begin(), sample );

  return sample->first;
}

// Return a random sample from the distribution at the given CDF value in a subrange
inline double DiscreteDistribution::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_distribution.front().first );

  // Scale the random number to the cdf at the max indep var
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;
  
  return this->sampleImplementation( scaled_random_number, dummy_index );
}

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::DiscreteDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::DiscreteDistribution>
{
public:
  static std::string name()
  {
    return "Discrete Distribution";
  }
  static std::string concreteName( 
				const Utility::DiscreteDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_DISCRETE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution.hpp
//---------------------------------------------------------------------------//

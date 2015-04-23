//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The equiprobable bin distribution class
  class EquiprobableBinDistribution : public TabularOneDDistribution,
	       public ParameterListCompatibleObject<EquiprobableBinDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  EquiprobableBinDistribution();

  //! Constructor
  EquiprobableBinDistribution( const Teuchos::Array<double>& bin_boundaries);

  //! Copy constructor
  EquiprobableBinDistribution(
			    const EquiprobableBinDistribution& dist_instance );

  //! Assignment operator
  EquiprobableBinDistribution& operator=(
		            const EquiprobableBinDistribution& dist_instance );

  //! Destructor
  ~EquiprobableBinDistribution()
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

  //! Return a random sample from the distribution and the sampled index 
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
  bool isEqual( const EquiprobableBinDistribution& other ) const;

private:

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // The disribution type
  static const OneDDistributionType distribution_type = 
    EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  Teuchos::Array<double> d_bin_boundaries;
};

// Return a random sample using the random number and record the bin index
inline double EquiprobableBinDistribution::sampleImplementation( 
				            double random_number,
				            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  double bin_location = random_number*(d_bin_boundaries.size()-1);
  
  sampled_bin_index = (unsigned)floor(bin_location);
  
  return d_bin_boundaries[sampled_bin_index] + 
    (bin_location - sampled_bin_index)*(d_bin_boundaries[sampled_bin_index+1]-
					d_bin_boundaries[sampled_bin_index]);
}

// Return a random sample from the distribution at the given CDF value in a subrange
inline double EquiprobableBinDistribution::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  // Compute the scaled random number
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}
  
} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the 
 * Utility::EquiprobableBinDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::EquiprobableBinDistribution>
{
public:
  static std::string name()
  {
    return "Equiprobable Bin Distribution";
  }
  static std::string concreteName( 
		const Utility::EquiprobableBinDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//

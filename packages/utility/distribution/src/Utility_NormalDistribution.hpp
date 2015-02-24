//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_HPP
#define UTILITY_NORMAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Normal distribution class
class NormalDistribution : public OneDDistribution,
			   public ParameterListCompatibleObject<NormalDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  NormalDistribution( const double mean = 0.0,
		      const double standard_deviation = 1.0,
		      const double min_independent_value = 
		      -std::numeric_limits<double>::infinity(),
		      const double max_independent_value = 
		      std::numeric_limits<double>::infinity() );

  //! Copy constructor
  NormalDistribution( const NormalDistribution& dist_instance );

  //! Assignment operator
  NormalDistribution& operator=( const NormalDistribution& dist_instance );

  //! Destructor
  ~NormalDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

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
  bool isEqual( const NormalDistribution& other ) const;

private:

  // Sample a value from the distribution, count the number of trials
  double sample( unsigned& number_of_trials ) const;

  // The distribution type
  static const OneDDistributionType distribution_type = NORMAL_DISTRIBUTION;

  // Constant multiplier (1/sqrt(2*pi))
  static const double constant_multiplier;

  // The mean of the distribution
  double d_mean;

  // The standard deviation of the distribution
  double d_standard_deviation;

  // The min independent value
  double d_min_independent_value;

  // The max independent value
  double d_max_independent_value;

  // The number of trials
  unsigned d_trials;

  // The number of random samples returned
  unsigned d_samples;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::NormalDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::NormalDistribution>
{
public:
  static std::string name()
  {
    return "Normal Distribution";
  }
  static std::string concreteName( 
				const Utility::NormalDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_NORMAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.hpp
//---------------------------------------------------------------------------//

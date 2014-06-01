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
#include "Utility_OneDDistribution.hpp"
#include "Utility_XMLCompatibleObject.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Discrete distribution class
class DiscreteDistribution : public OneDDistribution,
			     public XMLCompatibleObject<DiscreteDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default Constructor
  DiscreteDistribution();

  //! Constructor
  DiscreteDistribution( const Teuchos::Array<double>& independent_values,
			const Teuchos::Array<double>& dependent_values );
  
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

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const DiscreteDistribution& other ) const;

private:

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

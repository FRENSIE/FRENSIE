//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution.hpp
//! \author Alex Robinon
//! \brief  Power distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_HPP
#define UTILITY_POWER_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_XMLCompatibleObject.hpp"

namespace Utility{

//! Power distribution class (N > 2)
template<unsigned N>
class PowerDistribution : public OneDDistribution,
			  public XMLCompatibleObject<PowerDistribution<N> >
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  PowerDistribution();

  //! Constructor ( A*x^N : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );

  //! Copy constructor
  PowerDistribution( const PowerDistribution<N>& dist_instance );

  //! Assignment operator
  PowerDistribution<N>& operator=( const PowerDistribution<N>& dist_instance );

  //! Destructor
  ~PowerDistribution()
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
  bool isEqual( const PowerDistribution<N>& other ) const;

private:

  // Initialize the distribution
  void initializeDistribution();

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_N_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power N+1
  double d_min_indep_limit_to_power_Np1;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power N+1
  double d_max_indep_limit_to_power_Np1;
};

//! Power distribution class (N = 2)
template<>
class PowerDistribution<2u> : public OneDDistribution,
			     public XMLCompatibleObject<PowerDistribution<2u> >
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  PowerDistribution();

  //! Constructor ( A*x^2 : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );

  //! Copy constructor
  PowerDistribution( const PowerDistribution<2u>& dist_instance );

  //! Assignment operator
  PowerDistribution<2u>& operator=( 
				  const PowerDistribution<2u>& dist_instance );

  //! Destructor
  ~PowerDistribution()
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
  bool isEqual( const PowerDistribution<2u>& other ) const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_2_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power 3
  double d_min_indep_limit_cubed;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power 3
  double d_max_indep_limit_cubed;
};

//! Power distribution class (N = 1)
template<>
class PowerDistribution<1u> : public OneDDistribution,
			     public XMLCompatibleObject<PowerDistribution<1u> >
{

private:

  // Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Default constructor
  PowerDistribution();

  //! Constructor ( A*x : x in (a,b) )
  PowerDistribution( const double constant_multiplier,
		     const double min_indep_limit,
		     const double max_indep_limit );
  
  //! Copy constructor
  PowerDistribution( const PowerDistribution<1u>& dist_instance );

  //! Assignment operator
  PowerDistribution<1u>& operator=( 
				  const PowerDistribution<1u>& dist_instance );

  //! Destructor
  ~PowerDistribution()
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
  bool isEqual( const PowerDistribution<1u>& other ) const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = POWER_1_DISTRIBUTION;

  // The constant multiplier
  double d_constant_multiplier;

  // The min independent variable limit
  double d_min_indep_limit;

  //! The min independent variable limit to the power 2
  double d_min_indep_limit_squared;

  //! The max independent variable limit
  double d_max_indep_limit;
  
  //! The max independent variable limit to the power 2
  double d_max_indep_limit_squared;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::PowerDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<unsigned N>
class TypeNameTraits<Utility::PowerDistribution<N> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Power " << N << " Distribution";
    
    return iss.str();
  }
  static std::string concreteName( 
				const Utility::PowerDistribution<N>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//
 
#include "Utility_PowerDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POWER_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.hpp
//---------------------------------------------------------------------------//

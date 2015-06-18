//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WATT_DISTRIBUTION_HPP
#define UTILITY_WATT_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Watt distribution class
class WattDistribution : public OneDDistribution,
			   public ParameterListCompatibleObject<WattDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
 
  //! Default Constructor
  WattDistribution( const double incident_energy = 1.0,
		      const double a_parameter = 1.0,
                      const double b_parameter = 1.0,
		      const double restriction_energy = 0.0 );

  //! Copy constructor
  WattDistribution( const WattDistribution& dist_instance );

  //! Assignment operator
  WattDistribution& operator=( const WattDistribution& dist_instance );

  //! Destructor
  ~WattDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a sample from the distribution
  double sample() const;

  //! Return a random sample from the distribution and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Returna a random sample from the corresponding CDF and record the number of trials
  static double sampleAndRecordTrials(
    const double incident_energy,
    const double a_parameter,
    const double b_parameter,
    const double restriction_energy,
    unsigned& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const;

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
  bool isEqual( const WattDistribution& other ) const;

private:

  // Return the normalization constant of the distribution, pass in parameters
  double getNormalizationConstant(
    const double incident_energy,
    const double a_parameter,
    const double b_parameter,
    const double restriction_energy ) const;
 
  // The distribution type
  static const OneDDistributionType distribution_type = WATT_DISTRIBUTION;

  // The incident neutron energy of the distribution
  double d_incident_energy;

  // The a_parameter of the distribution
  double d_a_parameter;

  // The b_parameter of the distribution
  double d_b_parameter;
  
  // The restriction energy of the distribution
  double d_restriction_energy;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::WattDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::WattDistribution>
{
public:
  static std::string name()
  {
    return "Watt Distribution";
  }
  static std::string concreteName( 
				const Utility::WattDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_WATT_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.hpp
//---------------------------------------------------------------------------//

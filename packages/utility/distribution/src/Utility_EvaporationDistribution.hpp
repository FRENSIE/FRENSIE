//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EVAPORATION_DISTRIBUTION_HPP
#define UTILITY_EVAPORATION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Evaporation distribution class
class EvaporationDistribution : public OneDDistribution,
			   public ParameterListCompatibleObject<EvaporationDistribution>
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:
 
  //! Default Constructor
  EvaporationDistribution( const double incident_energy = 1.0,
		      const double nuclear_temperature = 1.0,
		      const double restriction_energy = 0.0 );

  //! Copy constructor
  EvaporationDistribution( const EvaporationDistribution& dist_instance );

  //! Assignment operator
  EvaporationDistribution& operator=( const EvaporationDistribution& dist_instance );

  //! Destructor
  ~EvaporationDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a sample from the distribution
  double sample() const;

  //! Return a random sample from the distribution, and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static double sampleAndRecordTrials(
    const double incident_energy,
    const double nuclear_temperature,
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
  bool isEqual( const EvaporationDistribution& other ) const;

private:

  // Return the normalization constant of the distribution, pass in parameters
  double getNormalizationConstant(
    const double incident_energy,
    const double nuclear_temperature,
    const double restriction_energy ) const;
 
  // The distribution type
  static const OneDDistributionType distribution_type = EVAPORATION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  double d_incident_energy;

  // The nuclear temperature of the distribution
  double d_nuclear_temperature;
  
  // The restriction energy of the distribution
  double d_restriction_energy;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::EvaporationDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::EvaporationDistribution>
{
public:
  static std::string name()
  {
    return "Evaporation Distribution";
  }
  static std::string concreteName( 
				const Utility::EvaporationDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution.hpp
//---------------------------------------------------------------------------//

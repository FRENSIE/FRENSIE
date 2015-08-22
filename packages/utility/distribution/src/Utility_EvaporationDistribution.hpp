//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution class declaration. Modified by Alex
//!         Robinson to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EVAPORATION_DISTRIBUTION_HPP
#define UTILITY_EVAPORATION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

/*! The unit-aware evaporation distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareEvaporationDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					 public ParameterListCompatibleObject<UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

  // The inverse squared independent unit traits typedef
  typedef UnitTraits<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<-2>::value> InverseSquaredIndepUnitTraits;

  // The inverse squared independent quantity type
  typedef typename InverseSquaredIndepUnitTraits::template GetQuantityType<double>::value InverseSquaredIndepQuantity;

public:

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;
 
  //! Default constructor
  UnitAwareEvaporationDistribution( 
	            const IndepQuantity incident_energy = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 ),
		    const IndepQuantity nuclear_temperature = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 1.0 ),
		    const IndepQuantity restriction_energy = 
		    QuantityTraits<IndepQuantity>::initializeQuantity( 0.0 ) );

  //! Constructor
  template<typename InputIndepQuantityA,
	   typename InputIndepQuantityB,
	   typename InputIndepQuantityC>
  UnitAwareEvaporationDistribution( 
				const InputIndepQuantityA incident_energy,
				const InputIndepQuantityB nuclear_temperature,
				const InputIndepQuantityC restriction_energy );

  //! Copy constructor
  UnitAwareEvaporationDistribution( const UnitAwareEvaporationDistribution& dist_instance );

  //! Copy constructor (copying from unitless distribution only)
  UNITLESS_COPY_CONSTRUCTOR_DEFAULT( UnitAwareEvaporationDistribution );

  //! Assignment operator
  UnitAwareEvaporationDistribution& operator=( const UnitAwareEvaporationDistribution& dist_instance );

  //! Destructor
  ~UnitAwareEvaporationDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the distribution, and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
    const IndepQuantity incident_energy,
    const IndepQuantity nuclear_temperature,
    const IndepQuantity restriction_energy,
    unsigned& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareEvaporationDistribution& other ) const;

protected:

  //! Return the normalization constant of the distribution, pass in parameters
  static InverseSquaredIndepQuantity getNormalizationConstant(
				      const IndepQuantity incident_energy,
				      const IndepQuantity nuclear_temperature,
				      const IndepQuantity restriction_energy );

private:
 
  // The distribution type
  static const OneDDistributionType distribution_type = EVAPORATION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The nuclear temperature of the distribution
  IndepQuantity d_nuclear_temperature;
  
  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;
};

/*! The evaporation distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareEvaporationDistribution<void,void> EvaporationDistribution;

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

/*! \brief Type name traits partial specialization for the 
 * Utility::UnitAwareEvaporationDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareEvaporationDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Evaporation Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	       const Utility::UnitAwareEvaporationDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EvaporationDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution.hpp
//---------------------------------------------------------------------------//

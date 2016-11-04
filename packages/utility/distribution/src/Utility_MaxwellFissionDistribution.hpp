//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class declaration. Modified by Alex
//!         Robison to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP
#define UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/dimensionless_type.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

/*! The unit-aware Maxwell fission distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareMaxwellFissionDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					    public ParameterListCompatibleObject<UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

private:

  // The distribution multiplier unit traits typedef
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::template GetUnitToPowerType<1,-2>::type>::type> DistMultiplierUnitTraits;

  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;

  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! This distribution type
  typedef UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareMaxwellFissionDistribution(
				const InputIndepQuantityA incident_energy =
                                QuantityTraits<InputIndepQuantityA>::one(),
				const InputIndepQuantityB nuclear_temperature =
                                QuantityTraits<InputIndepQuantityB>::one(),
				const InputIndepQuantityC restriction_energy =
                                QuantityTraits<InputIndepQuantityC>::zero(),
				const double constant_multiplier = 1.0 );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareMaxwellFissionDistribution fromUnitlessDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareMaxwellFissionDistribution& operator=( const UnitAwareMaxwellFissionDistribution& dist_instance );

  //! Destructor
  ~UnitAwareMaxwellFissionDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity nuclear_temperature,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution and record the number of trials
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
  bool isEqual( const UnitAwareMaxwellFissionDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareMaxwellFissionDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = MAXWELLFISSION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The nuclear temperature of the distribution
  IndepQuantity d_nuclear_temperature;

  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The Maxwell fission distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareMaxwellFissionDistribution<void,void> MaxwellFissionDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::MaxwellFissionDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::MaxwellFissionDistribution>
{
public:
  static std::string name()
  {
    return "Maxwell Fission Distribution";
  }
  static std::string concreteName(
				const Utility::MaxwellFissionDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareMaxwellFissionDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareMaxwellFissionDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Maxwell Fission Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	    const Utility::UnitAwareMaxwellFissionDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_MaxwellFissionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MAXWELLFISSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.hpp
//---------------------------------------------------------------------------//

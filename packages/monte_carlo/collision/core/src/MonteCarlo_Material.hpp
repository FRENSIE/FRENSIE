//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Material.hpp
//! \author Alex Robinson
//! \brief  Material base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_HPP
#define MONTE_CARLO_MATERIAL_HPP

// Std Lib Includes
#include <unordered_map>
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The material base class
template<typename ScatteringCenter>
class Material
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for this type
  typedef Material<ScatteringCenter> ThisType;

public:

  //! The material handle type
  typedef size_t InternalMaterialHandle;

  //! The scattering center name map
  typedef std::unordered_map<std::string,std::shared_ptr<const ScatteringCenter> > ScatteringCenterNameMap;

  //! Destructor
  virtual ~Material()
  { /* ... */ }

  //! Check if an id is valid
  static bool isIdValid( const InternalMaterialHandle id );

  //! Return the material id
  InternalMaterialHandle getId() const;

  //! Return the number density (atom/b-cm)
  double getNumberDensity() const;

  //! Return the macroscopic total cross section (1/cm)
  double getMacroscopicTotalCrossSection( const double energy ) const;

  //! Return the macroscopic absorption cross section (1/cm)
  double getMacroscopicAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability
  double getSurvivalProbability( const double energy ) const;

  //! Return the macroscopic cross section (1/cm) for a specific reaction
  double getMacroscopicReactionCrossSection(
          const double energy,
	  const typename ScatteringCenter::ReactionEnumType reaction ) const;

  //! Collide with a photon
  void collideAnalogue( typename ScatteringCenter::ParticleStateType& photon,
                        ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  void collideSurvivalBias( typename ScatteringCenter::ParticleStateType& photon,
                            ParticleBank& bank ) const;

protected:

  //! The macroscopic cross section evaluation functor type
  typedef std::function<double(const double)> MacroscopicCrossSectionEvaluationFunctor;

  //! The microscopic cross section evaluation functor type
  typedef std::function<double(const ScatteringCenter&, const double)> MicroscopicCrossSectionEvaluationFunctor;

  //! Constructor
  Material( const InternalMaterialHandle id,
            const double density,
            const ScatteringCenterNameMap& scattering_center_name_map,
            const std::vector<double>& scattering_center_fractions,
            const std::vector<std::string>& scattering_center_names );

  //! Return the macroscopic cross section
  double getMacroscopicCrossSection(
                                const double energy,
                                const MicroscopicCrossSectionEvaluationFunctor&
                                cs_evaluation_functor ) const;
  
  //! Sample the collision atom
  size_t sampleCollisionScatteringCenterImpl(
                           const double energy,
                           const MacroscopicCrossSectionEvaluationFunctor&
                           macroscopic_total_cs_evaluation_functor,
                           const MicroscopicCrossSectionEvaluationFunctor&
                           total_cs_evaluation_functor ) const;

  //! Return the number of scattering centers
  size_t getNumberOfScatteringCenters() const;

  //! Return the scattering center at the desired index
  ScatteringCenter& getScatteringCenter( const size_t index ) const;
  
private:

  // Get the atomic weight from an atom pointer
  static double getAtomicWeightFromPair(
      const std::pair<double,std::shared_ptr<const ScatteringCenter> >& pair );

  // Sample the atom that is collided with
  size_t sampleCollisionScatteringCenter( const double energy ) const;

  // The ScatteringCenter::getTotalCrossSection function wrapper
  static MicroscopicCrossSectionEvaluationFunctor s_total_cs_evaluation_functor;
  // The ScatteringCenter::getAbsorptionCrossSection function wrapper
  static MicroscopicCrossSectionEvaluationFunctor s_absorption_cs_evaluation_functor;

  // The material id
  InternalMaterialHandle d_id;

  // The number density of the atoms of the material
  double d_number_density;

  // The atoms that make up the material
  std::vector<std::pair<double,std::shared_ptr<const ScatteringCenter> > > d_scattering_centers;

  // The getMacroscopicTotalCrossSection function wrapper
  MacroscopicCrossSectionEvaluationFunctor
  d_macroscopic_total_cs_evaluation_functor;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Material_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Material.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled geometry model class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_GEOMETRY_MODEL_DEF_HPP
#define MONTE_CARLO_FILLED_GEOMETRY_MODEL_DEF_HPP

// FRENSIE Includes

namespace MonteCarlo{

namespace Details{

//! The filled geometry model upcast helper
template<typename ParticleStateType>
struct FilledGeometryModelUpcastHelper;

//! Specialization of the filled geometry model upcast helper for neutrons
template<>
struct FilledGeometryModelUpcastHelper<NeutronState>
{
  //! The desired base type for the upcast
  typedef FilledNeutronGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a NeutronFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a NeutronFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the filled geometry model upcast helper for photons
template<>
struct FilledGeometryModelUpcastHelper<PhotonState>
{
  //! The desired base type for the upcast
  typedef FilledPhotonGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a PhotonFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a PhotonFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the filled geometry model upcast helper for adjoint photons
template<>
struct FilledGeometryModelUpcastHelper<AdjointPhotonState>
{
  //! The desired base type for the upcast
  typedef FilledAdjointPhotonGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a AdjointPhotonFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a AdjointPhotonFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the filled geometry model upcast helper for electrons
template<>
struct FilledGeometryModelUpcastHelper<ElectronState>
{
  //! The desired base type for the upcast
  typedef FilledElectronGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a ElectronFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a ElectronFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the filled geometry model upcast helper for adjoint electrons
template<>
struct FilledGeometryModelUpcastHelper<AdjointElectronState>
{
  //! The desired base type for the upcast
  typedef FilledAdjointElectronGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a AdjointElectronFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a AdjointElectronFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the filled geometry model upcast helper for positrons
template<>
struct FilledGeometryModelUpcastHelper<PositronState>
{
  //! The desired base type for the upcast
  typedef FilledPositronGeometryModel UpcastType;
  
  //! Upcast the filled geometry model to a PositronFilledGeometryModel
  static inline UpcastType* upcast( FilledGeometryModel* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the filled geometry model to a PositronFilledGeometryModel
  static inline const UpcastType* upcast( const FilledGeometryModel* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};
  
} // end Details namespace

// Check if a cell is void (as experienced by the given particle type)
/*! \details This method overload can be used to avoid the extra switch 
 * statement overhead.
 */
template<typename ParticleStateType>
bool FilledGeometryModel::isCellVoid(
                         const Geometry::Model::InternalCellHandle cell ) const
{
  Details::FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType::isCellVoid( cell );
}

// Get the total macroscopic cross section of a material for the given particle type
template<typename ParticleStateType>
double FilledGeometryModel::getMacroscopicTotalCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  Details::FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType::getMacroscopicTotalCrossSection( cell, energy );
}

// Get the total macroscopic cross section of a material for the given particle type
template<typename ParticleStateType>
double FilledGeometryModel::getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  Details::FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType::getMacroscopicTotalCrossSectionQuick( cell, energy );
}

// Get the total forward macroscopic cross section of a material for the given particle type
template<typename ParticleStateType>
double FilledGeometryModel::getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  Details::FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType::getMacroscopicTotalForwardCrossSection( cell, energy );
}

// Get the total macroscopic cross section of a material for the given particle type
template<typename ParticleStateType>
double FilledGeometryModel::getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  Details::FilledGeometryModelUpcastHelper<ParticleStateType>::UpcastType::getMacroscopicTotalForwardCrossSectionQuick( cell, energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_FILLED_GEOMETRY_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledGeometryModel_def.hpp
//---------------------------------------------------------------------------//

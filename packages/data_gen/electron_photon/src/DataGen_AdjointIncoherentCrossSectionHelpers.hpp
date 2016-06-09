//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentCrossSectionHelpers.hpp
//! \author Alex Robinson
//! \brief  The adjoint incoherent cross section helper function declarations
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_HELPERS_HPP
#define DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_HELPERS_HPP

namespace DataGen{

//! Return the energy of the max cross section value
double getEnergyOfMaxCrossSection( const double max_energy );

/*! Check if the energy corresponds to the max cross section value at any
 * max energy
 */
double doesEnergyCorrespondToAMaxCrossSectionValue( const double energy );

//! Return the max energy that results in a max cross section value at energy
double getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
						         const double energy );

} // end DataGen

#endif // end DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentCrossSectionHelpers.hpp
//---------------------------------------------------------------------------//


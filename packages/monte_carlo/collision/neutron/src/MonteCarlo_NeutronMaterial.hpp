//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronMaterial.hpp
//! \author Alex Robinson
//! \brief  Neutron material class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_MATERIAL_HPP
#define MONTE_CARLO_NEUTRON_MATERIAL_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_Material.hpp"
#include "MonteCarlo_Nuclide.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The neutron material class
class NeutronMaterial : public Material<Nuclide>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<Nuclide> BaseType;

public:

  //! The material handle type
  typedef typename BaseType::InternalMaterialHandle InternalMaterialHandle;

  //! The nuclide name map type
  typedef typename BaseType::ScatteringCenterNameMap NuclideNameMap;

  //! Constructor
  NeutronMaterial( const InternalMaterialHandle id,
                   const double density,
                   const NuclideNameMap& nuclide_name_map,
                   const std::vector<double>& nuclide_fractions,
                   const std::vector<std::string>& nuclide_names );

  //! Destructor
  ~NeutronMaterial()
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronMaterial.hpp
//---------------------------------------------------------------------------//

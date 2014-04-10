//---------------------------------------------------------------------------//
//!
//! \file   GeneralizedNuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The generalized nuclear reaction class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GENERALIZED_NUCLEAR_REACTION_HPP
#define GENERALIZED_NUCLEAR_REACTION_HPP

// FACEMC Includes
#include "NuclearReaction.hpp"

namespace FACEMC{

/*! The generalized nuclear reaction class
 * \details The behavior of this class is determined from the ENDFLawPolicy
 * and the ReferenceFramePolicy classes
 */
template<typename ENDFLawPolicy, typename ReferenceFramePolicy>
class GeneralizedNuclearReaction : public NuclearReaction
{
  
};

} // end FACEMC namespace

#endif // end GENERALIZED_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end GeneralizedNuclearReaction.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   Utility_OArchivableObject_def.hpp
//! \author Alex Robinson
//! \brief  OArchivable object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OARCHIVABLE_OBJECT_DEF_HPP
#define UTILITY_OARCHIVABLE_OBJECT_DEF_HPP

// Boost Includes
#include <boost/serialization/nvp.hpp>

namespace Utility{

namespace Details{

/*! The output archive creator
 *
 * This class should never be used directly
 */
class OArchiveCreator
{
  
public:

  //! Constructor
  OArchiveCreator()
  { /* ... */ }

  //! Destructor
  virtual ~OArchiveCreator()
  { /* ... */ }

  //! Create an output archive
  static void create(
             const boost::filesystem::path& archive_name_with_path,
             std::unique_ptr<std::ostream>& oarchive_stream,
             std::unique_ptr<boost::archive::polymorphic_oarchive>& oarchive );
};

} // end Details namespace

// Archive the object
/*! \details The file extension will be used to determine the archive type
 * (e.g. .xml, .txt, .bin, .h5fa)
 */
template<typename DerivedType>
void OArchivableObject<DerivedType>::saveToFile( const boost::filesystem::path& archive_name_with_path ) const
{
  // Create the output archive
  std::unique_ptr<std::ostream> oarchive_stream;
  std::unique_ptr<boost::archive::polymorphic_oarchive> oarchive;

  Details::OArchiveCreator::create( archive_name_with_path, oarchive_stream, oarchive );

  // Save the derived type to the archive
  (*oarchive) << boost::serialization::make_nvp( this->getOArchiveName(), *dynamic_cast<const DerivedType*>(this) );

  // Ensure that the archive destructor is called before the stream destructor
  oarchive.reset();
}
  
} // end Utility namespace

#endif // end UTILITY_OARCHIVABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OArchivableObject_def.hpp
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirConverter.hpp
//! \author Alex Robinson
//! \brief  The xsdir converter class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_CONVERTER_HPP
#define DATA_GEN_XSDIR_CONVERTER_HPP

namespace DataGen{

//! The xsdir converter
class XsdirConverter
{

public:

  //! Constructor
  XsdirConverter( const std::string& xsdir_file,
		  const bool overwrite = false );

  //! Destructor
  ~XsdirConverter()
  { /* ... */ }
};

} // end DataGen namespace

#endif // end DATA_GEN_XSDIR_CONVERTER_HPP

//---------------------------------------------------------------------------//
// end DataGen_XsdirConverter.hpp
//---------------------------------------------------------------------------//

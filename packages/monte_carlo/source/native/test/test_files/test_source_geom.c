//---------------------------------------------------------------------------//
//!
//! \file   test_source_geom.c
//! \author Alex Robinson
//! \brief  Geometry for unit testing sources with rejection on ROOT geoms.
//!
//---------------------------------------------------------------------------//

/* Definition of geometry consisting of two volumes. The innermost volume is
 * a cube of half side length 2/sqrt(3)cm centered at (0,0,0) filled with void
 * material. The surrounding volume is a cube of half side length 5cm filled 
 * with the terminal material. 
 */
void test_source_geom()
{
  // Set up manager of geometry world
  gSystem->Load( "libGeom" );
  new TGeoManager( "Test_Source_Geometry",
                   "Geometry for testing source cell rejection" );

  // Define the materials and media (space filling materials)
  TGeoMaterial* void_mat = new TGeoMaterial( "void", 0, 0, 0 );
  TGeoMedium* void_med = new TGeoMedium( "void_med", 1, void_mat );

  TGeoMaterial* terminal_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
  TGeoMedium* terminal_med = new TGeoMedium( "graveyard", 2, terminal_mat );

  // Define the graveyard volume and set it to the highest node
  TGeoVolume* terminal_cube = gGeoManager->MakeBox( "TERMINAL",
                                                    terminal_med,
                                                    5.0, 
                                                    5.0, 
                                                    5.0 );
  
  gGeoManager->SetTopVolume( terminal_cube );
  terminal_cube->SetUniqueID( 1 );

  // Define the inner cube
  TGeoVolume* cube = 
    gGeoManager->MakeBox( "CUBE", 
                          void_med, 
                          1.1547005383792517,
                          1.1547005383792517,
                          1.1547005383792517 );
  cube->SetUniqueID( 2 );
  cube->SetVisibility( kTRUE );
  
  // Add the inner cube as a daughter of the graveyard
  terminal_cube->AddNode( cube, 1 );
  
  // Close the geometry
  gGeoManager->CloseGeometry();

  // Export the geometry
  gGeoManager->Export( "test_source_geom.root" );
  exit( 0 );
}

//---------------------------------------------------------------------------//
// end test_source_geom.c
//---------------------------------------------------------------------------//

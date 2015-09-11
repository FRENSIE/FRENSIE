//---------------------------------------------------------------------------//
//!
//! \file   Verification_Test.C
//! \author Eli Moll
//! \brief  Geometry for verification testing on ROOT implementation
//!
//---------------------------------------------------------------------------//

/* Description: A verification study geometry file for comparison between
 * ROOT and DagMC using FRENSIE. Hydrogen at 2500k in a 1cm sphere is
 * surrounded by void. A surface current tally and cell track-length flux
 * tally are placed on the sphere.
 */
void Verification_Test()
{
  // Set up manager of geometry world
  gSystem->Load( "libGeom" );
  new TGeoManager( "Test_Geometry",
                   "Geometry for testing root implementation" );

//---------------------------------------------------------------------------//
// Material Definitions
//---------------------------------------------------------------------------//

  // Hydrogen
  TGeoMaterial *mat_1 = new TGeoMaterial( "mat_1",1,1,1 );
  TGeoMedium   *med_1 = new TGeoMedium( "med_1",2,mat_1 );

  // Void
  TGeoMaterial *void_mat = new TGeoMaterial( "void",0,0,0 );
  TGeoMedium   *void_med = new TGeoMedium( "void_med",1,void_mat );

  // Graveyard (terminal)
  TGeoMaterial *terminal_mat = new TGeoMaterial( "graveyard",0,0,0 );
  TGeoMedium   *terminal_med = new TGeoMedium( "graveyard",3,terminal_mat );

//---------------------------------------------------------------------------//
// Volume Definitions
//---------------------------------------------------------------------------//

  // Graveyard Volume
  TGeoVolume *terminal_cube = gGeoManager->MakeBox( "TERMINAL",
                                                     terminal_med,
                                                     2.0, 2.0, 2.0 );
  terminal_cube->SetUniqueID(3);   
                                                     
  // Set the graveyard to be the top volume (rest-of-universe)
  gGeoManager->SetTopVolume( terminal_cube );

  // Void Volume (cube)
  TGeoVolume *cube = gGeoManager->MakeBox( "CUBE",
                                           void_med, 
                                           1.5, 1.5, 1.5 );
  cube->SetUniqueID(2);

  // Hydrogen Volume (sphere)
  TGeoVolume *sphere = gGeoManager->MakeSphere( "SPHERE",
                                                med_1,
                                                0.0,1.0 );
  sphere->SetUniqueID(1);

//---------------------------------------------------------------------------//
// Heirarchy (Volume) Definitions
//---------------------------------------------------------------------------//

  // Add SPHERE as a daughter of CUBE
  terminal_cube->AddNode( cube, 1 );
  
  // Add CUBE as a daughter of TERMINAL
  cube->AddNode( sphere, 1 );

//---------------------------------------------------------------------------//
// Export and Drawing Capabilities
//---------------------------------------------------------------------------//

  // Close the geometry
  gGeoManager->CloseGeometry();
  gGeoManager->SetTopVisible();
  
  // Uncomment to draw the geometry in an X-Window
  // terminal_cube->Draw();

  gGeoManager->Export("verification_test.root");
  exit(1);

}  // end Test_Root_Geometry

//---------------------------------------------------------------------------//
// end Test_Root_Geometry.C
//---------------------------------------------------------------------------//

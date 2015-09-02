//---------------------------------------------------------------------------//
//! 
//! \file   Test_Root_Geometry.C
//! \author Eli Moll
//! \brief  Geometry for unit testing on ROOT implementation
//!
//---------------------------------------------------------------------------//

/* Definition of geometry consisting of two volumes. The innermost volume is
 * sphere of radius 2.5cm, centered at (0,0,0) and filled with hydrogen. The
 * surrounding volume is a cube of side length 10cm centered at (0,0,0) filled
 * with the terminal material. 
 */ 
void Test_Root_Geometry()
{
  // Set up manager of geometry world
  gSystem->Load( "libGeom" );
  new TGeoManager( "Test_Geometry",
                   "Geometry for testing root implementation" );
   
  // Define materials and media (space filling materials)
  TGeoMaterial *void_mat = new TGeoMaterial( "void",0,0,0 );
  TGeoMedium   *void_med = new TGeoMedium( "void_med",1,void_mat );
   
  TGeoMaterial *mat_1 = new TGeoMaterial( "mat_1",1,1,1 );
  TGeoMedium   *med_1 = new TGeoMedium( "med_1",2,mat_1 );
  
  TGeoMaterial *terminal_mat = new TGeoMaterial( "graveyard",0,0,0 );
  TGeoMedium   *terminal_med = new TGeoMedium( "graveyard",3,terminal_mat );

  // Define the graveyard volume and set it to be the highest node
  TGeoVolume *terminal_cube = gGeoManager->MakeBox( "TERMINAL",
                                                     terminal_med,
                                                     7., 7., 7. );
  gGeoManager->SetTopVolume( terminal_cube );
  terminal_cube->SetUniqueID(3);
  
  TGeoVolume *cube = gGeoManager->MakeBox( "CUBE",void_med,5.,5.,5. );
  cube->SetUniqueID(1);
  cube->SetVisibility(kTRUE);

  // Define the spherical volume
  TGeoVolume *sphere = gGeoManager->MakeSphere( "SPHERE",med_1,0.,2.5 );
  sphere->SetUniqueID(2);

  // Add the sphere as a daughter of the cube
  terminal_cube->AddNode( cube, 1 );
  cube->AddNode( sphere, 1 );
  
  // Close the geometry and draw it for visualization
  gGeoManager->CloseGeometry();
  // gGeoManager->SetTopVisible();
  // terminal_cube->Draw();

  gGeoManager->Export("Test_Root_Geometry.root");
  exit(1);

}  // end Test_Root_Geometry


//---------------------------------------------------------------------------//
// end Test_Root_Geometry.C
//---------------------------------------------------------------------------//

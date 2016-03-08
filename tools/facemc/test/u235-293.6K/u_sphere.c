//---------------------------------------------------------------------------//
//!
//! \file   u_sphere.c
//! \author Alex Robinson
//! \brief  Geometry for Nuetron U-235 sphere at 293.6K verification problem
//!
//---------------------------------------------------------------------------//

void u_sphere()
{
  // Set up manager of the geometry world
  gSystem->Load( "libGeom" );
  
  TGeoManager* geom = new TGeoManager( 
                 "u_sphere",
                 "Geometry for the neutron U-235 sphere at 293.6K test prob.");
  
  // Create the Uranium material
  TGeoMaterial* uranium = new TGeoMaterial( "mat_1", 235, 92, -19.1 );
  TGeoMedium* med_1 = new TGeoMedium( "uranium", 1, uranium );

  // Create the void material
  TGeoMaterial* void_mat = new TGeoMaterial( "void", 0, 0, 0 );
  TGeoMedium* void_med = new TGeoMedium( "void", 2, void_mat );

  // Create the graveyard 
  TGeoMaterial* graveyard_mat = new TGeoMaterial( "graveyard", 0, 0, 0 );
  TGeoMedium* graveyard_med = new TGeoMedium( "graveyard", 3, graveyard_mat );

  // Create the Uranium volume
  TGeoVolume* u_sphere_volume = 
    geom->MakeSphere( "SPHERE", med_1, 0.0, 1.0 );
  
  u_sphere_volume->SetUniqueID( 1 );

  // Create the void volume
  TGeoVolume* void_cube_volume = geom->MakeBox( 
                                             "CUBE", void_med, 2.5, 2.5, 2.5 );
  
  void_cube_volume->SetUniqueID( 2 );

  // Create the graveyard volume
  TGeoVolume* graveyard_volume = geom->MakeBox( 
                                   "GRAVEYARD", graveyard_med, 3.0, 3.0, 3.0 );

  graveyard_volume->SetUniqueID( 3 );

  // Place the Uranium sphere inside of the void cube
  void_cube_volume->AddNode( u_sphere_volume, 1 );

  // Place the void cube inside of the graveyard
  graveyard_volume->AddNode( void_cube_volume, 1 );
  geom->SetTopVolume( graveyard_volume );

  // Close the geometry
  geom->SetTopVisible();
  geom->CloseGeometry();

  // Draw the geometry
  // graveyard_volume->Draw();

  // Export the geometry
  geom->Export( "u_sphere.root" );
  
  // Finished
  exit(0);
}

//---------------------------------------------------------------------------//
// end u_sphere.c
//---------------------------------------------------------------------------//

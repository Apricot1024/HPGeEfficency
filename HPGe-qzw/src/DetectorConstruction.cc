//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"

#include <CLHEP/Units/PhysicalConstants.h>

#include "lala.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/* DetectorConstruction::DetectorConstruction()
{} */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/* DetectorConstruction::~DetectorConstruction()
{} */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  // 
  //
  G4Material* Ge_mat = nist->FindOrBuildMaterial("G4_Ge");
  G4Material* Be_mat = nist->FindOrBuildMaterial("G4_Be");
  G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al");
  // G4Material* Cu_mat = nist->FindOrBuildMaterial("G4_Cu");

  G4VisAttributes* visHPGe        = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.5));
  G4VisAttributes* visAl          = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.4));
  G4VisAttributes* visair         = new G4VisAttributes(G4Colour(0.0,0.0,0.5,0.5));
  G4VisAttributes* visBe          = new G4VisAttributes(G4Colour(1.0,1.0,0.3,0.5));



  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // Paramaters 
  //

    // a little calculation
  G4double primary_Al_R = 20/2 *cm,primary_Al_x = 10 *cm,primary_Al_H = 10 *um;
  G4double primary_Al_V = CLHEP::pi*2*primary_Al_R * primary_Al_x * primary_Al_H;
  G4double Al_R = lala_R*mm;
  G4double Al_H = primary_Al_V/(CLHEP::pi * Al_R * Al_R);
   //target
  G4double D_bottom = 41*mm; // 距离井底的长度


  G4double Ge_Rin = 16.5/2*mm,Ge_Rout = 79.3/2*mm,Ge_Hin = 40.5*mm,Ge_Hout = 77*mm;
  //well
  G4double well_D = 0.5*mm;
  G4double well_R = 16.5/2*mm ,well_H = Ge_Hin;

  
  //
  // World
  //
  G4double world_sizeXY = 2*Ge_Rout, world_sizeZ = 2*Ge_Hout;
  G4Material* Air_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       world_sizeXY, world_sizeXY, world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        Air_mat,           //its material
                        "World");

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  
  //
  // Ge_Crystal
  //
  G4Tubs* Ge_solid =
    new G4Tubs("Ge_solid", 0, Ge_Rout, Ge_Hout/2, 0*deg, 360*deg);
  G4LogicalVolume* Ge_logic =
    new G4LogicalVolume(Ge_solid,   
                        Ge_mat,      
                        "Ge_logic"); 
  //well
  G4Tubs* well_solid =
    new G4Tubs("well_solid", 0, well_R, well_H/2, 0*deg, 360*deg);
  G4LogicalVolume* well_logic =
    new G4LogicalVolume(well_solid,   
                        Al_mat,      
                        "well_logic");
   
  //air
  G4double Air_R = well_R - well_D;
  G4double Air_H = well_H - well_D;
  G4Tubs* Air_solid_inner =
    new G4Tubs("Air_solid_inner", 0, Air_R, Air_H/2, 0*deg, 360*deg);
  G4LogicalVolume* Air_logic_inner =
    new G4LogicalVolume(Air_solid_inner,
                        Air_mat,
                        "Air_logic_inner");

  G4VPhysicalVolume* physGe =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,-Ge_Hout/2),       //at (0,0,0)
                      Ge_logic,              //its logical volume
                      "Ge_Crystal",          //its name
                      logicWorld,            //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  G4double h_well = Ge_Hout/2 - Ge_Hin/2;
  G4VPhysicalVolume* physwell = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,h_well),       //at (0,0,0)
                      well_logic,            //its logical volume
                      "well",        //its name
                      Ge_logic,            //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  G4double h_Air = well_H/2 - Air_H/2;
  G4VPhysicalVolume* physAir =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,h_Air),       //at (0,0,0)
                      Air_logic_inner,       //its logical volume
                      "Air_inner",   //its name
                      well_logic,               //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);
  
  //
  //  target
  //
  
  #if 0
  G4Tubs* Al_solid = 
    new G4Tubs("Al_solid", 0, Al_R, Al_H/2, 0*deg, 360*deg);

  G4LogicalVolume* Al_logic =
    new G4LogicalVolume(Al_solid,   
                        Al_mat,      
                        "Al_logic"); 
  
  G4double D_center = D_bottom + Al_H/2 -Ge_Hin + well_D ; 
  G4VPhysicalVolume* physAl =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,D_center),       //
                      Al_logic,              //its logical volume
                      "Al_Crystal",          //its name
                      logicWorld,               //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);
  #endif


  fScoringVolume = Ge_logic;

  //
  //always return the physical World
  //

  //设置可视化


#if 0 
// 设置Air_mat的可视化属性为透明
G4VisAttributes* airVis = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0, 0.5)); // 白色，透明度为0.5
airVis->SetVisibility(true);
airVis->SetForceSolid(true); // 设置为非实心，以便看到透明效果
// Air_logic_inner->SetVisAttributes(airVis);

// 设置Ge_mat的可视化属性为灰色
G4VisAttributes* geVis = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5)); // 灰色
geVis->SetVisibility(true);
geVis->SetForceSolid(true); // 设置为实心
Ge_logic->SetVisAttributes(geVis);
#endif 

#if 1
Ge_logic         -> SetVisAttributes(visHPGe);
well_logic       -> SetVisAttributes(visAl);
Air_logic_inner  -> SetVisAttributes(visair);
// Al_logic         -> SetVisAttributes(visAl);
// Be_logic         -> SetVisAttributes(visBe);
#endif

  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

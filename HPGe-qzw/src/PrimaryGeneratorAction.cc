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
/// \file B1/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

#include "lala.hh"

namespace B1
{
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  PrimaryGeneratorAction::PrimaryGeneratorAction()
  {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    // default particle kinematic

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("chargedgeantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    fParticleGun->SetParticleEnergy(0 * eV);
    fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  PrimaryGeneratorAction::~PrimaryGeneratorAction()
  {
    delete fParticleGun;
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
  {
    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
    if (particle == G4ChargedGeantino::ChargedGeantino())
    {
      // fluorine
      G4int Z = 27, A = 55;
      G4double ionCharge = 0. * eplus;
      G4double excitEnergy = 0. * keV;

      G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
      fParticleGun->SetParticleDefinition(ion);
      fParticleGun->SetParticleCharge(ionCharge);
    }

#if 0
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(477.6*keV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

#if 0
  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }
#endif

#if 0
    if (!ftargetTubs)
  {
    G4LogicalVolume* Be_LV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Be_logic");
    if ( Be_LV ) ftargetTubs = dynamic_cast<G4Tubs*>(Be_LV->GetSolid());
  }

  if ( ftargetTubs ) {
     G4ThreeVector position = physVolume->GetObjectTranslation();
     G4double Hz0 = position.z();
  }
#endif
#endif

    // a little calculation
    G4double primary_Al_R = 20 / 2 * cm, primary_Al_x = 10 * cm, primary_Al_H = 10 * um;
    G4double primary_Al_V = CLHEP::pi * 2 * primary_Al_R * primary_Al_x * primary_Al_H;
    G4double Al_R = lala_R * mm;
    G4double Al_H = primary_Al_V / (CLHEP::pi * Al_R * Al_R);

    G4double Ge_Hin = 40.5 * mm;
    // G4double D_bottom = 40.5*mm;
    G4double D_bottom = 10 * mm;
    G4double well_D = 0.5 * mm;
    G4double D_center = D_bottom + Al_H / 2 - Ge_Hin + well_D;

    G4double H = D_center;
    G4double R0 = Al_R;
    G4double z0 = Al_H;
    G4double sita0 = 360. * deg;
    G4double R = R0 * G4UniformRand();

    G4double z = H + z0 * (G4UniformRand() - 0.5);
    G4double sita = sita0 * G4UniformRand();

    G4double x = R * cos(sita);
    G4double y = R * sin(sita);

    fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));

    fParticleGun->GeneratePrimaryVertex(anEvent);
  }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}

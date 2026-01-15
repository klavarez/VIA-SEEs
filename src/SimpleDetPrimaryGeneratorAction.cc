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
// $Id: SimpleDetPrimaryGeneratorAction.cc,v 1.7 2006-06-29 17:48:13 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SimpleDetPrimaryGeneratorAction.hh"
#include "SimpleDetDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "TRandom.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetPrimaryGeneratorAction::SimpleDetPrimaryGeneratorAction(
SimpleDetDetectorConstruction* myDC)
:myDetector(myDC)
{
G4int n_particle = 1;
particleGun = new G4ParticleGun(n_particle);

// default particle

G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
G4ParticleDefinition* particle = particleTable->FindParticle("proton");

particleGun->SetParticleDefinition(particle);
particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
particleGun->SetParticleEnergy(3.0*GeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetPrimaryGeneratorAction::~SimpleDetPrimaryGeneratorAction()
{
delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimpleDetPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{  
//particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
/*
TF1 *Power = new TF1("Power", "x^[0]", 1,100000);
Power->SetParameter(0,Index);
Power->SetNpx(10000);

for(double i = 0; i < 1000000; i++)
	{
	double Ekin = Power->GetRandom();
	
	double m = 938;
	double Beta = sqrt(1-pow(m/(Ekin+m),2));

	double SigmaBeta = pow(Beta,2)*299792458/Distance*TRes;*/

//particleGun->SetParticleEnergy(gRandom->Uniform(5,100)*GeV);

//double Temp = particleGun->GetParticleEnergy();

//------------------------

// double rigidity = gRandom->Uniform(100,10000);
// double kinetic_energy = sqrt(rigidity*rigidity+pow(particleGun->GetParticleDefinition()->GetPDGMass(),2))-particleGun->GetParticleDefinition()->GetPDGMass();
// particleGun->SetParticleEnergy(kinetic_energy);

//------------------------

//double beta = gRandom->Uniform(0.42,0.62);
// double beta = gRandom->Uniform(0.42,0.9999);
// double kinetic_energy = particleGun->GetParticleDefinition()->GetPDGMass()*(sqrt(1/(1-beta*beta))-1);
// particleGun->SetParticleEnergy(kinetic_energy);

//------------------------

particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//----------------------------------------------------------------------

G4ParticleGun* SimpleDetPrimaryGeneratorAction::GetParticleGun()
{
return particleGun;
}

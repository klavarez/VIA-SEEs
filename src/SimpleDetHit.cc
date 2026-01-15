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
// $Id: SimpleDetHit.cc,v 1.10 2006-06-29 17:48:24 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SimpleDetHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "TROOT.h"

G4Allocator<SimpleDetHit> SimpleDetHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetHit::SimpleDetHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetHit::~SimpleDetHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetHit::SimpleDetHit(const SimpleDetHit& right)
: G4VHit()
{
parentID   = right.parentID;
trackID   = right.trackID;
volumeID = right.volumeID;
edep      = right.edep;
pos       = right.pos;
pdg       = right.pdg;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const SimpleDetHit& SimpleDetHit::operator=(const SimpleDetHit& right)
{
parentID   = right.parentID;
trackID   = right.trackID;
volumeID = right.volumeID;
edep      = right.edep;
pos       = right.pos;
pdg       = right.pdg;
return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int SimpleDetHit::operator==(const SimpleDetHit& right) const
{
return (this==&right) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimpleDetHit::Draw()
{
G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
if(pVVisManager)
{
G4Circle circle(pos);
circle.SetScreenSize(2.);
circle.SetFillStyle(G4Circle::filled);
G4Colour colour(1.,0.,0.);
G4VisAttributes attribs(colour);
circle.SetVisAttributes(attribs);
pVVisManager->Draw(circle);
}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimpleDetHit::Print()
{
G4cout.precision(5);
G4cout<<"parent: "<<parentID<<G4endl<<
"track: "<<trackID<<G4endl<<
"volume: "<<volumeID<<G4endl<<
"pdg: "<<pdg<<G4endl<<
"Edep: "<<G4BestUnit(edep,"Energy")<<G4endl<<
"pos: "<<G4BestUnit(pos,"Length")<<G4endl<<
"direction: "<<MomentumDirection<<G4endl<<
"Ekin: "<<G4BestUnit(KineticEnergy,"Energy")<<G4endl<<
"time: "<<G4BestUnit(GlobalTime,"Time")<<G4endl<<
"vertex direction: "<<VertexMomentumDirection<<G4endl<<
"vertex pos: "<<G4BestUnit(VertexPosition,"Length")<<G4endl<<
"vertex Ekin: "<<G4BestUnit(VertexKineticEnergy,"Energy")<<G4endl<<G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


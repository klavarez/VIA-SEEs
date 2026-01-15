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
// $Id: SimpleDetHit.hh,v 1.8 2006-06-29 17:47:53 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SimpleDetHit_h
#define SimpleDetHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimpleDetHit : public G4VHit
{
public:

SimpleDetHit();
~SimpleDetHit();
SimpleDetHit(const SimpleDetHit&);
const SimpleDetHit& operator=(const SimpleDetHit&);
G4int operator==(const SimpleDetHit&) const;

inline void* operator new(size_t);
inline void  operator delete(void*);

void Draw();
void Print();

public:

void SetParentID (G4int parent) { parentID = parent; };
void SetTrackID (G4int track) { trackID = track; };
void SetVolumeId(G4int vol) { volumeID = vol; };
void SetPdg(G4int p) { pdg = p; };
void SetEdep(G4double de) { edep = de; };
void SetPos(G4ThreeVector xyz) { pos = xyz; };

void SetMomentumDirection(G4ThreeVector MD) { MomentumDirection = MD; };
void SetKineticEnergy(G4double KE) { KineticEnergy = KE; };
void SetGlobalTime(G4double GT) { GlobalTime = GT; };
void SetVertexMomentumDirection(G4ThreeVector  VMD) { VertexMomentumDirection = VMD; };
void SetVertexPosition(G4ThreeVector  VP) { VertexPosition = VP; };
void SetVertexKineticEnergy(G4double VKE) { VertexKineticEnergy = VKE; };

G4int GetParentID() { return parentID; };
G4int GetTrackID() { return trackID; };
G4int GetVolumeId() { return volumeID; };
G4int GetPdg() { return pdg; };
G4double GetEdep() { return edep; };      
G4ThreeVector GetPos() { return pos; };

G4ThreeVector GetMomentumDirection() { return MomentumDirection; };
G4double GetKineticEnergy() { return KineticEnergy; };
G4double GetGlobalTime() { return GlobalTime; };
G4ThreeVector GetVertexMomentumDirection() { return VertexMomentumDirection; };
G4ThreeVector GetVertexPosition() { return VertexPosition; };
G4double GetVertexKineticEnergy() { return VertexKineticEnergy; };

private:

G4int parentID;	
G4int trackID;
G4int volumeID;
G4double edep;
G4ThreeVector pos;
G4int pdg;

G4ThreeVector MomentumDirection;
G4double KineticEnergy;
G4double GlobalTime;
G4ThreeVector VertexMomentumDirection;
G4ThreeVector VertexPosition;
G4double VertexKineticEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<SimpleDetHit> SimpleDetHitsCollection;

extern G4Allocator<SimpleDetHit> SimpleDetHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* SimpleDetHit::operator new(size_t)
{
void *aHit;
aHit = (void *) SimpleDetHitAllocator.MallocSingle();
return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void SimpleDetHit::operator delete(void *aHit)
{
SimpleDetHitAllocator.FreeSingle((SimpleDetHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

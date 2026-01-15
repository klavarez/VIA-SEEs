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
// $Id: SimpleDetDetectorConstruction.hh,v 1.10 2008-09-22 16:41:20 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SimpleDetDetectorConstruction_h
#define SimpleDetDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "SimpleDetMagneticField.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PhysicalConstants.hh"
#include "G4GenericMessenger.hh"
#include <vector>
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include <vector>

using namespace std;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class SimpleDetDetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimpleDetDetectorConstruction : public G4VUserDetectorConstruction
{
public:

SimpleDetDetectorConstruction();
~SimpleDetDetectorConstruction();

public:

G4VPhysicalVolume* Construct();

void DefineMaterials();
void InitializeGeometry();

void SetPassive(G4String MaterialName, double DimX, double DimY, double DimZ, double PosX, double PosY, double PosZ);
void SetActive(G4String MaterialName, double DimX, double DimY, double DimZ, double PosX, double PosY, double PosZ);

void SetMagField(G4double);
void SetMaxStep(G4double);    

vector<G4Material*> GetMaterialPassive();
vector<G4ThreeVector> GetPositionPassive();
vector<G4ThreeVector> GetDimensionPassive();
vector<int> GetVolumeIdPassive();

vector<G4Material*> GetMaterialActive();
vector<G4ThreeVector> GetPositionActive();
vector<G4ThreeVector> GetDimensionActive();
vector<int> GetVolumeIdActive();

private:

G4Box*             MySolidWorld;    // pointer to the MySolid envelope 
G4LogicalVolume*   MyLogicWorld;    // pointer to the MyLogical envelope
G4VPhysicalVolume* MyPhysicalWorld;    // pointer to the MyPhysicalcal envelope

vector <G4Box*>             MySolidPassive;  // pointer to the MySolid Passive
vector <G4LogicalVolume*>   MyLogicPassive;  // pointer to the MyLogical Passive
vector <G4VPhysicalVolume*> MyPhysicalPassive;  // pointer to the MyPhysicalcal Passive

vector <G4Box*>             MySolidActive;  // pointer to the MySolid Active
vector <G4LogicalVolume*>   MyLogicActive;  // pointer to the MyLogical Active
vector <G4VPhysicalVolume*> MyPhysicalActive;  // pointer to the MyPhysicalcal Active

G4Material* MyAir;
G4Material* MyAverageAntarcticAir;
G4Material* MyPb;
G4Material* MyGe;
G4Material* MySi;
G4Material* MyAl;
G4Material* MyC;
G4Material* MyH;
G4Material* MyD;
G4Material* MyHe;
G4Material* MyPvt;
G4Material* MyVacuum;
G4Material* MyNa61Tpc;
G4Material* MyNa61LH;
G4Material* AlTight;
G4Material* Cu;
G4Material* Be;
G4Material* Pvt;
G4Material* BGO;
G4Material* multiAl;
G4Material* mptPvt;
G4Material* Mylar;


G4VisAttributes* MyPassiveVisAtt;
vector<G4Material*> MyMaterialPassive;
vector<G4ThreeVector> MyPositionPassive;
vector<G4ThreeVector> MyDimensionPassive;
vector<int> MyVolumeIdPassive;

G4VisAttributes* MyActiveVisAtt;
vector<G4Material*> MyMaterialActive;
vector<G4ThreeVector> MyPositionActive;
vector<G4ThreeVector> MyDimensionActive;
vector<int> MyVolumeIdActive;

int MyVolumeId;

G4UserLimits* MyStepLimit;             // pointer to user step limits
SimpleDetMagneticField* MyMagField;   // pointer to the magnetic field 
SimpleDetDetectorMessenger* MyDetectorMessenger;  // pointer to the Messenger
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

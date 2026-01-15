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
// $Id: SimpleDetRunAction.hh,v 1.8 2006-06-29 17:47:45 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef SimpleDetRunAction_h
#define SimpleDetRunAction_h 1

#include "SimpleDetEventAction.hh"
#include "SimpleDetDetectorConstruction.hh"
#include "G4UserRunAction.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"
#include <string.h>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class SimpleDetEventAction;

class SimpleDetRunAction : public G4UserRunAction
{
public:
SimpleDetRunAction();
~SimpleDetRunAction();

void Clear();

void BeginOfRunAction(const G4Run*);
void EndOfRunAction(const G4Run*);
	
//void SetRoot(G4String filename);
void SaveRootBegin();
void SaveRootEnd();
void NewOutputFile(G4String filename);
void SetFileName(G4String filename);
void SetPhysicsListName(G4String PhysicsListName);
SimpleDetEventAction * GetCurrentEvent();
SimpleDetDetectorConstruction * GetCurrentDetectorConstruction();

void SetSeed(unsigned int seed = 0);
void SetRunNumber(unsigned int n = 0);

void SetPrimaryParticlePdg(int PrimaryParticlePdg);
void SetPrimaryParticleEnergy(double PrimaryParticleEnergy);
void SetPrimaryParticlePosition(G4ThreeVector PrimaryParticlePosition);
void SetPrimaryParticleTime(double PrimaryParticleTime);
void SetPrimaryParticleMomentumDirection(G4ThreeVector PrimaryParticleMomentumDirection);

void SetParentID(int ParentID);
void SetTrackID(int TrackID);
void SetVolumeID(int VolumeID);
void SetEdep(double Edep);
void SetPos(G4ThreeVector Pos);
void SetPdg(int Pdg);
void SetMomentumDirection(G4ThreeVector MomentumDirection);
void SetKineticEnergy(double KineticEnergy);
void SetGlobalTime(double GlobalTime);

void SetVertexTrackID(int TrackID);
void SetVertexMomentumDirection(G4ThreeVector VertexMomentumDirection);
void SetVertexPosition(G4ThreeVector VertexPosition);
void SetVertexKineticEnergy(double VertexKineticEnergy);

private:

G4bool runSaveRoot;
bool runMachineTime;
string baseRootFilename;
string runPhysicsListName;
TFile * runRootFile;
TTree * runRootTreeEvent;
TTree * runRootTreeGeometryActive;
TTree * runRootTreeGeometryPassive;

unsigned int * runRandSeed;
unsigned int * runNumber;

int * runPrimaryParticlePdg;
double * runPrimaryParticleEnergy;
vector<double> * runPrimaryParticlePosition;
double * runPrimaryParticleTime;
vector<double> * runPrimaryParticleMomentumDirection;

vector<int> * runParentID;
vector<int> * runTrackID;
vector<int> * runVolumeID;
vector<double> * runEdep;
vector<vector<double> > * runPos;
vector<int> * runPdg;
vector<vector<double> > * runMomentumDirection;
vector<double> * runKineticEnergy;
vector<double> * runGlobalTime;

vector<int> * runVertexTrackID;
vector<vector<double> > * runVertexMomentumDirection;
vector<vector<double> > * runVertexPosition;
vector<double> * runVertexKineticEnergy;

vector<string> * runMaterialPassive;
vector<vector<double> > * runPositionPassive;
vector<vector<double> > * runDimensionPassive;
vector<int> * runVolumeIdPassive;

vector<string> * runMaterialActive;
vector<vector<double> > * runPositionActive;
vector<vector<double> > * runDimensionActive;
vector<int> * runVolumeIdActive;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif






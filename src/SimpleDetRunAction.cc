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
// $Id: SimpleDetRunAction.cc,v 1.9 2006-06-29 17:48:16 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------

#include "SimpleDetRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

#include "TRandom3.h"

//----------------------------------------------------------------------

SimpleDetRunAction::SimpleDetRunAction()
{
runRandSeed = new unsigned int;
*runRandSeed = time(0); //can be changed by messenger
gRandom->SetSeed(*runRandSeed);
runNumber = new unsigned int;
*runNumber = time(0); //can be changed by messenger
runSaveRoot = false;
runMachineTime = true;
runPhysicsListName = "undefined";

runPrimaryParticlePdg = new int;
runPrimaryParticleEnergy = new double;
runPrimaryParticlePosition = new vector<double>;
runPrimaryParticleTime = new double;

runParentID = new vector<int>;
runTrackID = new vector<int>;
runVolumeID = new vector<int>;
runPrimaryParticleMomentumDirection = new vector<double>;
runEdep = new vector<double>;
runPos = new vector<vector<double> >;
runPdg = new vector<int>;
runMomentumDirection = new vector<vector<double> >;
runKineticEnergy = new vector<double>;
runGlobalTime = new vector<double>;

runVertexTrackID = new vector<int>;
runVertexMomentumDirection = new vector<vector<double> >;
runVertexPosition = new vector<vector<double> >;
runVertexKineticEnergy = new vector< double>;

runMaterialPassive = new vector<string>;
runPositionPassive = new vector<vector<double> >;
runDimensionPassive = new vector<vector<double> >;
runVolumeIdPassive = new vector<int>;

runMaterialActive = new vector<string>;
runPositionActive = new vector<vector<double> >;
runDimensionActive = new vector<vector<double> >;
runVolumeIdActive = new vector<int>;

Clear();
}

//----------------------------------------------------------------------

SimpleDetRunAction::~SimpleDetRunAction()
{}

//----------------------------------------------------------------------

void SimpleDetRunAction::Clear()
{
*runPrimaryParticlePdg = 0;
*runPrimaryParticleEnergy = 0;
*runPrimaryParticleTime = 0;
vector <double> Temp(3);
*runPrimaryParticlePosition = Temp;
*runPrimaryParticleMomentumDirection = Temp;

runParentID->clear();
runTrackID->clear();
runVolumeID->clear();
runEdep->clear();
runPos->clear();
runPdg->clear();
runMomentumDirection->clear();
runKineticEnergy->clear();
runGlobalTime->clear();

runVertexTrackID->clear();
runVertexMomentumDirection->clear();
runVertexPosition->clear();
runVertexKineticEnergy->clear();

runMaterialPassive->clear();
runPositionPassive->clear();
runDimensionPassive->clear();
runVolumeIdPassive->clear();

runMaterialActive->clear();
runPositionActive->clear();
runDimensionActive->clear();
runVolumeIdActive->clear();
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetSeed(unsigned int seed) 
{
if(seed == 0) *runRandSeed = time(0);
else *runRandSeed = seed;
gRandom->SetSeed(*runRandSeed);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetRunNumber(unsigned int n) 
{
if(n == 0) 
	{
	*runNumber = time(0);
	runMachineTime = true;
	}
else 
	{
	*runNumber = n;
	runMachineTime = false;
	}
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPrimaryParticlePdg(int PrimaryParticlePdg) 
{ 
*runPrimaryParticlePdg = PrimaryParticlePdg; 
}


void SimpleDetRunAction::SetPrimaryParticleEnergy(double PrimaryParticleEnergy) 
{ 
*runPrimaryParticleEnergy = PrimaryParticleEnergy;
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPrimaryParticlePosition(G4ThreeVector PrimaryParticlePosition) 
{
runPrimaryParticlePosition->clear();
runPrimaryParticlePosition->push_back(PrimaryParticlePosition.getX());
runPrimaryParticlePosition->push_back(PrimaryParticlePosition.getY());
runPrimaryParticlePosition->push_back(PrimaryParticlePosition.getZ());
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPrimaryParticleTime(double PrimaryParticleTime)
{
*runPrimaryParticleTime = PrimaryParticleTime;
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPrimaryParticleMomentumDirection(G4ThreeVector PrimaryParticleMomentumDirection) 
{
runPrimaryParticleMomentumDirection->clear();
runPrimaryParticleMomentumDirection->push_back(PrimaryParticleMomentumDirection.getX());
runPrimaryParticleMomentumDirection->push_back(PrimaryParticleMomentumDirection.getY());
runPrimaryParticleMomentumDirection->push_back(PrimaryParticleMomentumDirection.getZ());
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetParentID(int ParentID)
{
runParentID->push_back(ParentID);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetTrackID(int TrackID)
{
runTrackID->push_back(TrackID);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetVolumeID(int VolumeID)
{
runVolumeID->push_back(VolumeID);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetEdep(double Edep)
{
runEdep->push_back(Edep);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPos(G4ThreeVector Pos)
{
vector<double> Temp;
Temp.push_back(Pos.getX());
Temp.push_back(Pos.getY());
Temp.push_back(Pos.getZ());
runPos->push_back(Temp);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPdg(int Pdg)
{
runPdg->push_back(Pdg);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetMomentumDirection(G4ThreeVector MomentumDirection)
{
vector<double> Temp;
Temp.push_back(MomentumDirection.getX());
Temp.push_back(MomentumDirection.getY());
Temp.push_back(MomentumDirection.getZ());
runMomentumDirection->push_back(Temp);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetKineticEnergy(double KineticEnergy) 
{
runKineticEnergy->push_back(KineticEnergy);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetGlobalTime(double GlobalTime) 
{
runGlobalTime->push_back(GlobalTime); 
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetVertexTrackID(int TrackID)
{
runVertexTrackID->push_back(TrackID);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetVertexMomentumDirection(G4ThreeVector VertexMomentumDirection)
{
vector<double> Temp;
Temp.push_back(VertexMomentumDirection.getX());
Temp.push_back(VertexMomentumDirection.getY());
Temp.push_back(VertexMomentumDirection.getZ());
runVertexMomentumDirection->push_back(Temp);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetVertexPosition(G4ThreeVector VertexPosition)
{
vector<double> Temp;
Temp.push_back(VertexPosition.getX());
Temp.push_back(VertexPosition.getY());
Temp.push_back(VertexPosition.getZ());
runVertexPosition->push_back(Temp);
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetVertexKineticEnergy(double VertexKineticEnergy) 
{ 
runVertexKineticEnergy->push_back(VertexKineticEnergy); 
}

//----------------------------------------------------------------------

void SimpleDetRunAction::BeginOfRunAction(const G4Run*)
{
CLHEP::HepRandom::setTheSeed(*runRandSeed);

if(baseRootFilename.size() == 0) NewOutputFile("SimpleDet");
else NewOutputFile(baseRootFilename);


//cout<<"Seed: "<<CLHEP::HepRandom::getTheSeed()<<endl;
}

//----------------------------------------------------------------------

void SimpleDetRunAction::EndOfRunAction(const G4Run*)
{ 
SaveRootEnd();
*runRandSeed = gRandom->Integer(0xFFFFFFFF);
}

//----------------------------------------------------------------------

SimpleDetDetectorConstruction * SimpleDetRunAction::GetCurrentDetectorConstruction()
{
return dynamic_cast<SimpleDetDetectorConstruction*> (const_cast<G4VUserDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction()));
}

//----------------------------------------------------------------------

SimpleDetEventAction * SimpleDetRunAction::GetCurrentEvent()
{
//when converting to MT mode this is causing the problem
return dynamic_cast<SimpleDetEventAction*> (const_cast<G4UserEventAction*> (G4RunManager::GetRunManager()->GetUserEventAction()));
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetFileName(G4String filename)
{
baseRootFilename = filename;
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SetPhysicsListName(G4String PhysicsListName)
{
runPhysicsListName = PhysicsListName;
}

//----------------------------------------------------------------------

void SimpleDetRunAction::NewOutputFile(G4String filename)
{
baseRootFilename = filename;

if(runMachineTime) *runNumber = time(0);
else (*runNumber)++;
std::stringstream s_runNumber;
s_runNumber << *runNumber;

G4cout<<"run: " <<*runNumber<<G4endl;

//create new file
if(runSaveRoot)
	{
	runRootFile->Write();
	runRootFile->Close();
	GetCurrentEvent()->CloseRoot();
	runSaveRoot = false;
	}
	
G4String RootFilename = baseRootFilename + "_" + runPhysicsListName + "_" + s_runNumber.str() + ".root";
runSaveRoot = true;
runRootFile = new TFile(RootFilename, "RECREATE");

SaveRootBegin();
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SaveRootBegin()
{
if(runSaveRoot) 
	{
	runRootTreeEvent = new TTree("Event","");

	runRootTreeEvent->Branch("RandSeed", runRandSeed);
	runRootTreeEvent->Branch("Number", runNumber);
	
	runRootTreeEvent->Branch("PrimaryParticlePdg", runPrimaryParticlePdg);
	runRootTreeEvent->Branch("PrimaryParticleEnergy", runPrimaryParticleEnergy);
	runRootTreeEvent->Branch("PrimaryParticlePosition", runPrimaryParticlePosition);
	runRootTreeEvent->Branch("PrimaryParticleTime", runPrimaryParticleTime);
	runRootTreeEvent->Branch("PrimaryParticleMomentumDirection", runPrimaryParticleMomentumDirection);
	
	runRootTreeEvent->Branch("ParentID", runParentID);
	runRootTreeEvent->Branch("TrackID", runTrackID);
	runRootTreeEvent->Branch("VolumeID", runVolumeID);
	runRootTreeEvent->Branch("EnergyDeposition", runEdep);
	runRootTreeEvent->Branch("Position", runPos);
	runRootTreeEvent->Branch("Pdg", runPdg);
	runRootTreeEvent->Branch("MomentumDirection", runMomentumDirection);
	runRootTreeEvent->Branch("KineticEnergy", runKineticEnergy);
	runRootTreeEvent->Branch("GlobalTime", runGlobalTime);
	
	runRootTreeEvent->Branch("VertexTrackID", runVertexTrackID);
	runRootTreeEvent->Branch("VertexMomentumDirection", runVertexMomentumDirection);
	runRootTreeEvent->Branch("VertexPosition", runVertexPosition);	
	runRootTreeEvent->Branch("VertexKineticEnergy", runVertexKineticEnergy);

	GetCurrentEvent()->SetRoot(runRootTreeEvent);

	//save geometry
	
	runRootTreeGeometryActive = new TTree("GeometryActive","");

	runRootTreeGeometryActive->Branch("MaterialActive", runMaterialActive);
	runRootTreeGeometryActive->Branch("PositionActive", runPositionActive);
	runRootTreeGeometryActive->Branch("DimensionActive", runDimensionActive);
	runRootTreeGeometryActive->Branch("VolumeIdActive", runVolumeIdActive);

	for(unsigned int i = 0; i < GetCurrentDetectorConstruction()->GetMaterialActive().size(); i++)
		{
		runMaterialActive->push_back(GetCurrentDetectorConstruction()->GetMaterialActive().at(i)->GetName());
	
		vector<double> TempPositionActive;
		TempPositionActive.push_back(GetCurrentDetectorConstruction()->GetPositionActive().at(i).getX());
		TempPositionActive.push_back(GetCurrentDetectorConstruction()->GetPositionActive().at(i).getY());
		TempPositionActive.push_back(GetCurrentDetectorConstruction()->GetPositionActive().at(i).getZ());
		runPositionActive->push_back(TempPositionActive);
	
		vector<double> TempDimensionActive;
		TempDimensionActive.push_back(GetCurrentDetectorConstruction()->GetDimensionActive().at(i).getX());
		TempDimensionActive.push_back(GetCurrentDetectorConstruction()->GetDimensionActive().at(i).getY());
		TempDimensionActive.push_back(GetCurrentDetectorConstruction()->GetDimensionActive().at(i).getZ());
		runDimensionActive->push_back(TempDimensionActive);
		
		runVolumeIdActive->push_back(GetCurrentDetectorConstruction()->GetVolumeIdActive().at(i));
		}
	
	runRootTreeGeometryActive->Fill();
	
	runRootTreeGeometryPassive = new TTree("GeometryPassive","");

	runRootTreeGeometryPassive->Branch("MaterialPassive", runMaterialPassive);
	runRootTreeGeometryPassive->Branch("PositionPassive", runPositionPassive);
	runRootTreeGeometryPassive->Branch("DimensionPassive", runDimensionPassive);
	runRootTreeGeometryPassive->Branch("VolumeIdPassive", runVolumeIdPassive);
	
	for(unsigned int i = 0; i < GetCurrentDetectorConstruction()->GetMaterialPassive().size(); i++)
		{
		runMaterialPassive->push_back(GetCurrentDetectorConstruction()->GetMaterialPassive().at(i)->GetName());
	
		vector<double> TempPositionPassive;
		TempPositionPassive.push_back(GetCurrentDetectorConstruction()->GetPositionPassive().at(i).getX());
		TempPositionPassive.push_back(GetCurrentDetectorConstruction()->GetPositionPassive().at(i).getY());
		TempPositionPassive.push_back(GetCurrentDetectorConstruction()->GetPositionPassive().at(i).getZ());
		runPositionPassive->push_back(TempPositionPassive);
	
		vector<double> TempDimensionPassive;
		TempDimensionPassive.push_back(GetCurrentDetectorConstruction()->GetDimensionPassive().at(i).getX());
		TempDimensionPassive.push_back(GetCurrentDetectorConstruction()->GetDimensionPassive().at(i).getY());
		TempDimensionPassive.push_back(GetCurrentDetectorConstruction()->GetDimensionPassive().at(i).getZ());
		runDimensionPassive->push_back(TempDimensionPassive);
		
		runVolumeIdPassive->push_back(GetCurrentDetectorConstruction()->GetVolumeIdPassive().at(i));
		}
		
	runRootTreeGeometryPassive->Fill();	
	}
}

//----------------------------------------------------------------------

void SimpleDetRunAction::SaveRootEnd()
{
if(runSaveRoot) 
	{
	runRootFile->Write();
	runRootFile->Close();
	runSaveRoot = false;
	GetCurrentEvent()->CloseRoot();
	}
}


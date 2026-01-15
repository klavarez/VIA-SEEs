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
// $Id: SimpleDetDetectorMessenger.cc,v 1.12 2008-09-22 16:41:20 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4SystemOfUnits.hh"

#include "SimpleDetDetectorMessenger.hh"
#include "SimpleDetDetectorConstruction.hh"
#include "G4RunManager.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetDetectorMessenger::SimpleDetDetectorMessenger(SimpleDetDetectorConstruction* myDet)
:myDetector(myDet)
{ 
SimpleDetDir = new G4UIdirectory("/SimpleDet/");
SimpleDetDir->SetGuidance("UI commands specific to this example.");

detDir = new G4UIdirectory("/SimpleDet/det/");
detDir->SetGuidance("detector control.");

FieldCmd = new G4UIcmdWithADoubleAndUnit("/SimpleDet/det/setField",this);  
FieldCmd->SetGuidance("Define magnetic field.");
FieldCmd->SetGuidance("Magnetic field will be in X direction.");
FieldCmd->SetParameterName("Bx",false);
FieldCmd->SetUnitCategory("Magnetic flux density");
FieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/SimpleDet/det/stepMax",this);  
StepMaxCmd->SetGuidance("Define a step max");
StepMaxCmd->SetParameterName("stepMax",false);
StepMaxCmd->SetUnitCategory("Length");
StepMaxCmd->AvailableForStates(G4State_Idle);  

InitializeCmd = new G4UIcmdWithoutParameter("/SimpleDet/det/initialize",this);
InitializeCmd->SetGuidance("Initialize geometry.");
InitializeCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
InitializeCmd->SetGuidance("if you changed geometrical value(s).");
InitializeCmd->AvailableForStates(G4State_Idle);  

PassiveCmd = new G4UIcommand("/SimpleDet/det/passive",this);
PassiveCmd->AvailableForStates(G4State_Idle);
G4UIparameter* Parameter = new G4UIparameter("material",'s',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionX",'d',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionY",'d',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionZ",'d',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionX",'d',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionY",'d',false);
PassiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionZ",'d',false);
PassiveCmd->SetParameter(Parameter);

ActiveCmd = new G4UIcommand("/SimpleDet/det/active",this);
ActiveCmd->AvailableForStates(G4State_Idle);
Parameter = new G4UIparameter("material",'s',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionX",'d',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionY",'d',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("DimensionZ",'d',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionX",'d',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionY",'d',false);
ActiveCmd->SetParameter(Parameter);
Parameter = new G4UIparameter("PositionZ",'d',false);
ActiveCmd->SetParameter(Parameter);  

runDir = new G4UIdirectory("/SimpleDet/run/");
runDir->SetGuidance("run control.");

FilenameCmd = new G4UIcmdWithAString("/SimpleDet/run/setFileName",this);
FilenameCmd->SetGuidance("Set filename prefix.");
FilenameCmd->SetParameterName("choice",false);
FilenameCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimpleDetDetectorMessenger::~SimpleDetDetectorMessenger()
{
delete FieldCmd;
delete StepMaxCmd;  
delete detDir;
delete runDir;
delete SimpleDetDir;
delete FilenameCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimpleDetDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
if( command == FieldCmd )
	{ 
	myDetector->SetMagField(FieldCmd->GetNewDoubleValue(newValue));
	}

if( command == StepMaxCmd )
	{ 
	myDetector->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));
	}

if( command == InitializeCmd )
	{
	myDetector->InitializeGeometry();		
	}

if( command == PassiveCmd )
	{
	const char* ParamString = newValue;

	G4String Material;	
	G4double DimX, DimY, DimZ, PosX, PosY, PosZ;

	std::istringstream is((char*)ParamString);
	is >> Material >> DimX >> DimY >> DimZ >> PosX >> PosY >> PosZ;

	myDetector->SetPassive(Material, DimX*cm, DimY*cm, DimZ*cm, PosX*cm, PosY*cm, PosZ*cm);
	}

if( command == ActiveCmd )
	{
	const char* ParamString = newValue;

	G4String Material;	
	G4double DimX, DimY, DimZ, PosX, PosY, PosZ;

	std::istringstream is((char*)ParamString);
	is >> Material >> DimX >> DimY >> DimZ >> PosX >> PosY >> PosZ;

	myDetector->SetActive(Material, DimX*cm, DimY*cm, DimZ*cm, PosX*cm, PosY*cm, PosZ*cm);
	}

if( command == FilenameCmd )
	{ 
	dynamic_cast<SimpleDetRunAction*> (const_cast<G4UserRunAction*> (G4RunManager::GetRunManager()->GetUserRunAction()))->SetFileName(newValue);
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

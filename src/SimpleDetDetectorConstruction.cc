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
// $Id: SimpleDetDetectorConstruction.cc,v 1.22 2010-01-22 11:57:03 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//============================================================================== 
//==============================================================================
 
#include "SimpleDetDetectorConstruction.hh"
#include "SimpleDetDetectorMessenger.hh"
#include "SimpleDetMagneticField.hh"
#include "SimpleDetSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4Colour.hh"

#include "G4ios.hh"

//==============================================================================
 
SimpleDetDetectorConstruction::SimpleDetDetectorConstruction()
{
MyMagField = new SimpleDetMagneticField();
MyDetectorMessenger = new SimpleDetDetectorMessenger(this);

DefineMaterials();

MyPassiveVisAtt = new G4VisAttributes(G4Colour(1,1,1));
MyActiveVisAtt = new G4VisAttributes(G4Colour(1,0,0));

MyStepLimit = new G4UserLimits();

MyVolumeId = 0;
}

//==============================================================================

SimpleDetDetectorConstruction::~SimpleDetDetectorConstruction()
{
delete MyMagField;
delete MyStepLimit;
delete MyDetectorMessenger;   

}

void SimpleDetDetectorConstruction::DefineMaterials()
{
G4NistManager *nist = G4NistManager::Instance();

G4Element* N = new G4Element("Nitrogen", "N", 7., 14.01*g/mole);
G4Element* O = new G4Element("Oxygen"  , "O", 8., 16.00*g/mole);
// G4Element* Be = new G4Element("Beryllium", "Be", 4., 9.1218*g/mole);
G4Element* Ar = new G4Element("Argon"  , "Ar", 18., 39.948*g/mole);
G4Element* He = new G4Element("Helium"  , "He", 2., 4.002*g/mole);
G4Element* H = new G4Element("Hydrogen"  , "H", 1., 1.008*g/mole);
G4Element* C = new G4Element("Carbon"  , "C", 6., 12.001*g/mole);
G4Element* Bi = new G4Element("Bismuth", "Bi", 83., 208.98*g/mole);
G4Element* Ge = new G4Element("Germanium", "Ge", 32., 72.63*g/mole);

//Air
MyAir = new G4Material("Air", 0.0057*mg/cm3, 5);
MyAir->AddElement(N, 75.5569*perCent);
MyAir->AddElement(O, 23.1542*perCent);
MyAir->AddElement(Ar, 1.28881*perCent);
MyAir->AddElement(He, 7.24467e-05*perCent);
MyAir->AddElement(H, 0*perCent);

//Average air in front of 37km altitude at Antarctia during December
MyAverageAntarcticAir = new G4Material("AverageAntarcticAir", 5.6023e-2*g/cm3, 5);
MyAverageAntarcticAir->AddElement(N, 59.7417986*perCent);
MyAverageAntarcticAir->AddElement(O, 39.9032668*perCent);
MyAverageAntarcticAir->AddElement(Ar, 0.31098995*perCent);
MyAverageAntarcticAir->AddElement(He, 0.04317824*perCent);
MyAverageAntarcticAir->AddElement(H, 0.00076565*perCent);

//Lead
MyPb = new G4Material("Lead", 82., 207.19*g/mole, 11.35*g/cm3);

//Germanium
MyGe = new G4Material("Germanium", 32., 72.63*g/mole, 5.323*g/cm3);

//Silicon
MySi = new G4Material("Silicon", 14., 28.10*g/mole, 2.336*g/cm3);

//Aluminum
MyAl = new G4Material("Aluminum"  ,13, 26.98*g/mole, 2.70*g/cm3);

//Carbon
MyC = new G4Material("Carbon"  ,6, 12.011*g/mole, 1.6*g/cm3);

//Hydrogen
MyH = new G4Material("Hydrogen"  ,1, 1.008*g/mole, 1*g/cm3);

//Deuterium
MyD = new G4Material("Deuterium"  ,1, 2.01410178*g/mole, 1*g/cm3);

//Helium
MyHe = new G4Material("Helium" ,2, 4.002602*g/mole, 1*g/cm3);//0.1785*kg/m3);

// Mylar Foil
Mylar = nist->FindOrBuildMaterial("G4_MYLAR");

// Copper shielding
Cu = nist->FindOrBuildMaterial("G4_Cu");

// Beryllium
Be = nist->FindOrBuildMaterial("G4_Be");
// MyBe = new G4Material("Beryllium", 9.1218*g/mole, 1.85*g/cm3, 1);

// BGO
BGO = new G4Material("BGO", 7.13*g/cm3, 3);
BGO->AddElement(Bi, 4);
BGO->AddElement(Ge, 3);
BGO->AddElement(O, 12);

//PVT
Pvt = new G4Material("PVT", 1.032*g/cm3, 2);
Pvt->AddElement(C, 9);
Pvt->AddElement(H, 10);

// 99.0% light tight aluminum
AlTight = new G4Material("AlTight", 2.700*g/cm3, 6);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 90.2*perCent);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Fe"), 4.7*perCent);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Zn"), 1*perCent);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Cu"), 1*perCent);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Si"), 3*perCent);
AlTight->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 1*perCent);

// 6061 aluminum foil
multiAl = new G4Material("multiAl", 2.700*g/cm3, 9);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 98.6*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Cr"), 0.04*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Cu"), 0.14*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Fe"), 0.7*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Mg"), 0.8*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Mn"), 0.15*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Si"), 0.4*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Ti"), 0.1376*perCent);
multiAl->AddMaterial(nist->FindOrBuildMaterial("G4_Zn"), 0.25*perCent);

// //PVT EJ-212
// std::vector<G4double> rindexPvt = {1.58, 1.58};
// std::vector<G4double> abslenPvt = {250.*cm, 250.*cm};
// mptPvt = new G4MaterialPropertiesTable();
// mptPvt->AddProperty("RINDEX", energy, rindexPvt);
// mptPvt->AddProperty("ABSLENGTH", energy, abslenPvt);
// mptPvt->AddConstProperty("SCINTILLATIONYIELD", 10000./MeV);
// mptPvt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.4*ns);
// Pvt->SetMaterialPropertiesTable(mptPvt);

//scintillator
MyPvt = new G4Material("PVT", 1.032*g/cm3, 2); //the organic material //made of two types of atoms
MyPvt->AddElement(C, 9); //9 carbons and 10 hydrogens in the chemical formula
MyPvt->AddElement(H, 10);

//Vacuum
MyVacuum = new G4Material("Vacuum", 1, 1.008*g/mole, 1.e-25*g/cm3, kStateGas, 2.73*kelvin, 3.e-18*pascal); 

//Na61Tpc
MyNa61Tpc = new G4Material("Na61Tpc", 1.61*kg/m3, 3);
MyNa61Tpc->AddElement(C, 5/3.0*perCent);
MyNa61Tpc->AddElement(O, 10/3.0*perCent);
MyNa61Tpc->AddElement(Ar, 95*perCent);

//Na61LH
MyNa61LH = new G4Material("Na61LH", 1, 1.008*g/mole, 0.0707*g/cm3);

G4cout<<G4endl<<"The materials defined are : "<<G4endl<<G4endl;
G4cout<<*(G4Material::GetMaterialTable())<<G4endl;
}

//==============================================================================

vector<G4Material*> SimpleDetDetectorConstruction::GetMaterialPassive()
{
return MyMaterialPassive;
}

//==============================================================================

vector<G4ThreeVector> SimpleDetDetectorConstruction::GetPositionPassive()
{
return MyPositionPassive;
}

//==============================================================================

vector<G4ThreeVector> SimpleDetDetectorConstruction::GetDimensionPassive()
{
return MyDimensionPassive;
}

//==============================================================================

vector<int> SimpleDetDetectorConstruction::GetVolumeIdPassive()
{
return MyVolumeIdPassive;
}

//==============================================================================

vector<G4Material*> SimpleDetDetectorConstruction::GetMaterialActive()
{
return MyMaterialActive;
}

//==============================================================================

vector<G4ThreeVector> SimpleDetDetectorConstruction::GetPositionActive()
{
return MyPositionActive;
}

//==============================================================================

vector<G4ThreeVector> SimpleDetDetectorConstruction::GetDimensionActive()
{
return MyDimensionActive;
}

//==============================================================================

vector<int> SimpleDetDetectorConstruction::GetVolumeIdActive()
{
return MyVolumeIdActive;
}

//==============================================================================

G4VPhysicalVolume* SimpleDetDetectorConstruction::Construct()
{
G4GeometryManager::GetInstance()->SetWorldMaximumExtent(400*cm);
G4cout<<"Computed tolerance = "<<G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm<<" mm"<<G4endl;

MySolidWorld = new G4Box("world",40*cm,40*cm,40*cm);
//MyLogicWorld= new G4LogicalVolume(MySolidWorld, MyAir, "World", 0, 0, 0);
MyLogicWorld= new G4LogicalVolume(MySolidWorld, MyVacuum, "World", 0, 0, 0);

//  Must place the World Physical volume unrotated at (0,0,0).
// 
MyPhysicalWorld = new G4PVPlacement(0,          // no rotation
				G4ThreeVector(), // at (0,0,0)
				MyLogicWorld,    // its MyLogical volume
				"World",         // its name
				0,               // its mother  volume
				false,           // no boolean operations
				MyVolumeId);     // copy number
MyVolumeId++;

MyLogicWorld->SetVisAttributes(MyPassiveVisAtt);

return MyPhysicalWorld;
}

//==============================================================================

void SimpleDetDetectorConstruction::SetPassive(G4String MaterialName, double DimX, double DimY, double DimZ, double PosX, double PosY, double PosZ)
{
G4Material* Material = G4Material::GetMaterial(MaterialName);  
if(Material)
	{
	MyMaterialPassive.push_back(Material);
	MyDimensionPassive.push_back(G4ThreeVector(DimX,DimY,DimZ));
	MyPositionPassive.push_back(G4ThreeVector(PosX,PosY,PosZ));
	MyVolumeIdPassive.push_back(MyVolumeId);
	MyVolumeId++;
	}
else cout<<MaterialName<<" does not exist."<<endl;
}

//==============================================================================

void SimpleDetDetectorConstruction::SetActive(G4String MaterialName, double DimX, double DimY, double DimZ, double PosX, double PosY, double PosZ)
{
G4Material* Material = G4Material::GetMaterial(MaterialName);  
if(Material)
	{
	MyMaterialActive.push_back(Material);
	MyDimensionActive.push_back(G4ThreeVector(DimX,DimY,DimZ));
	MyPositionActive.push_back(G4ThreeVector(PosX,PosY,PosZ));
	MyVolumeIdActive.push_back(MyVolumeId);
	MyVolumeId++;
	}
else cout<<MaterialName<<" does not exist."<<endl;
}
//==============================================================================

void SimpleDetDetectorConstruction::InitializeGeometry()
{
for(unsigned int i = 0; i < MyVolumeIdPassive.size(); i++)
	{
	MySolidPassive.push_back(new G4Box("Passive",MyDimensionPassive.at(i).x()*0.5, MyDimensionPassive.at(i).y()*0.5, MyDimensionPassive.at(i).z()*0.5));

	MyLogicPassive.push_back(new G4LogicalVolume(MySolidPassive.at(i), MyMaterialPassive.at(i), "Passive", 0, 0, 0));

	MyPhysicalPassive.push_back(new G4PVPlacement(0, MyPositionPassive.at(i), MyLogicPassive.at(i), "Passive", MyLogicWorld, false, MyVolumeIdPassive.at(i)));

	cout<<"passive box of "<<MyMaterialPassive.at(i)->GetName()<<" dimension ("<<MyDimensionPassive.at(i).x()/cm<<","<<MyDimensionPassive.at(i).y()/cm<<","<<MyDimensionPassive.at(i).z()/cm<<") position ("<<MyPositionPassive.at(i).x()/cm<<","<<MyPositionPassive.at(i).y()/cm<<","<<MyPositionPassive.at(i).z()/cm<<")"<<endl;

	MyLogicPassive.at(i)->SetUserLimits(MyStepLimit);

	MyLogicPassive.at(i)->SetVisAttributes(MyPassiveVisAtt);
	}

G4SDManager* SDman = G4SDManager::GetSDMpointer();
SimpleDetSD* SD = new SimpleDetSD("SimpleDet/ActiveDetectorSD");
SDman->AddNewDetector(SD);

for(unsigned int i = 0; i < MyVolumeIdActive.size(); i++)
	{
	MySolidActive.push_back(new G4Box("Active",MyDimensionActive.at(i).x()*0.5, MyDimensionActive.at(i).y()*0.5, MyDimensionActive.at(i).z()*0.5));

	MyLogicActive.push_back(new G4LogicalVolume(MySolidActive.at(i), MyMaterialActive.at(i), "Active", 0, 0, 0));

	MyPhysicalActive.push_back(new G4PVPlacement(0, MyPositionActive.at(i), MyLogicActive.at(i), "Active", MyLogicWorld, false, MyVolumeIdActive.at(i)));

	cout<<"active box of "<<MyMaterialActive.at(i)->GetName()<<" dimension ("<<MyDimensionActive.at(i).x()/cm<<","<<MyDimensionActive.at(i).y()/cm<<","<<MyDimensionActive.at(i).z()/cm<<") position ("<<MyPositionActive.at(i).x()/cm<<","<<MyPositionActive.at(i).y()/cm<<","<<MyPositionActive.at(i).z()/cm<<")"<<endl;

	MyLogicActive.at(i)->SetUserLimits(MyStepLimit);

	MyLogicActive.at(i)->SetVisAttributes(MyActiveVisAtt);

	MyLogicActive.at(i)->SetSensitiveDetector(SD);
	
	// Set additional contraints on the track, with G4UserSpecialCuts
	//
	// G4double maxLength = 2*fActiveLength, maxTime = 0.1*ns, minEkin = 10*MeV;
	//MyLogicActive->SetUserLimits(new G4UserLimits(100*cm, maxLength,0.1*ns, 10*KeV));
	}
}

//==============================================================================

void SimpleDetDetectorConstruction::SetMagField(G4double fieldValue)
{
MyMagField->SetMagFieldValue(fieldValue);  
}

//==============================================================================

void SimpleDetDetectorConstruction::SetMaxStep(G4double maxStep)
{
if((MyStepLimit) && (maxStep>0.)) MyStepLimit->SetMaxAllowedStep(maxStep);
}

//==============================================================================

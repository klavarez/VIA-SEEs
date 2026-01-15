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
// $Id: SimpleDetEventAction.hh,v 1.8 2006-06-29 17:47:35 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef SimpleDetEventAction_h
#define SimpleDetEventAction_h 1

#include "G4UserEventAction.hh"
#include "SimpleDetRunAction.hh"
#include "SimpleDetPrimaryGeneratorAction.hh"

#include "globals.hh"

#include "TTree.h"

class G4Event;
class SimpleDetRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimpleDetEventAction : public G4UserEventAction
{
public:
SimpleDetEventAction();
~SimpleDetEventAction();

void BeginOfEventAction(const G4Event*);
void EndOfEventAction(const G4Event*);

void SetRoot(TTree * RootTree);
void CloseRoot();
void SaveRoot(const G4Event* evt);
SimpleDetRunAction * GetCurrentRun();
SimpleDetPrimaryGeneratorAction * GetCurrentPrimaryGeneratorAction();

private:
G4bool evtSaveRoot;
TTree * evtRootTree;
//SimpleDetEventActionMessenger* evtMessenger;	
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    

#include<TApplication.h>
#include<TCanvas.h>
#include<TH1D.h>
#include<TH2D.h>
#include<TF1.h>
#include<TStyle.h>
#include<TFile.h>
#include<TTree.h>
#include<TROOT.h>
#include<TLegend.h>
#include<TColor.h>
#include<TGraph.h>
#include<TMath.h>
#include<TProfile.h>
#include<THistPainter.h>

#include<vector>
#include<string>
#include<stdlib.h>

// imports
#include<fstream>

using namespace std;

int Colors[] = {kBlack, kRed, kBlue, kOrange, kGreen, kGray-1, kRed-1, kBlue-1, kOrange-1, kGreen-1, kGray+1, kRed+1, kBlue+1, kOrange+1, kGreen+1, kGray-2, kRed-2, kBlue-2, kOrange-2, kGreen-2, kGray-2, kRed+2, kBlue+2, kOrange+2, kGreen+2};

TProfile* SimpleDetAnalysis(string Filename) {
gROOT->Reset();

//open simulation file
TFile * File = new TFile(Filename.c_str());

//------------------------------------

//load geometry of active components
TTree * TreeGeometryActive = (TTree*)File->Get("GeometryActive");

vector<string> * MaterialActive = new vector<string>;
vector<vector<double> > * PositionActive = new vector<vector<double> >;
vector<vector<double> > * DimensionActive = new vector<vector<double> >;
vector<int> * VolumeIdActive = new vector<int>;

TreeGeometryActive->SetBranchAddress("MaterialActive", &MaterialActive);
TreeGeometryActive->SetBranchAddress("PositionActive", &PositionActive);
TreeGeometryActive->SetBranchAddress("DimensionActive", &DimensionActive);
TreeGeometryActive->SetBranchAddress("VolumeIdActive", &VolumeIdActive);

//load entries

TreeGeometryActive->GetEntry(0);

//------------------------------------

//load geometry of passive components

TTree * TreeGeometryPassive = (TTree*)File->Get("GeometryPassive");

vector<string> * MaterialPassive = new vector<string>;
vector<vector<double> > * PositionPassive = new vector<vector<double> >;
vector<vector<double> > * DimensionPassive = new vector<vector<double> >;
vector<int> * VolumeIdPassive = new vector<int>;

TreeGeometryPassive->SetBranchAddress("MaterialPassive", &MaterialPassive);
TreeGeometryPassive->SetBranchAddress("PositionPassive", &PositionPassive);
TreeGeometryPassive->SetBranchAddress("DimensionPassive", &DimensionPassive);
TreeGeometryPassive->SetBranchAddress("VolumeIdPassive", &VolumeIdPassive);

//load entries

TreeGeometryPassive->GetEntry(0);

//------------------------------------

//load geometry of passive components

TTree * TreeEvent = (TTree*)File->Get("Event");

unsigned int RandSeed = 0;
unsigned int Number = 0;

int PrimaryParticlePdg = 0;
double PrimaryParticleEnergy = 0;
vector<double> * PrimaryParticlePosition = new vector<double>;
double * PrimaryParticleTime = new double;
vector<double> * PrimaryParticleMomentumDirection = new vector<double>;

vector<int> * ParentID = new vector<int>;
vector<int> * TrackID = new vector<int>;
vector<int> * VolumeID = new vector<int>;
vector<double> * EnergyDeposition = new vector<double>;
vector<vector<double> > * Position = new vector<vector<double> >;
vector<int> * Pdg = new vector<int>;
vector<vector<double> > * MomentumDirection = new vector<vector<double> >;
vector<double> * KineticEnergy = new vector<double>;
vector<double> * GlobalTime = new vector<double>;

vector<int> * VertexTrackID = new vector<int>;
vector<vector<double> > * VertexMomentumDirection = new vector<vector<double> >;
vector<vector<double> > * VertexPosition = new vector<vector<double> >;
vector<double> * VertexKineticEnergy = new vector< double>;

TreeEvent->SetBranchAddress("RandSeed", &RandSeed);
TreeEvent->SetBranchAddress("Number", &Number);

TreeEvent->SetBranchAddress("PrimaryParticlePdg", &PrimaryParticlePdg);
TreeEvent->SetBranchAddress("PrimaryParticleEnergy", &PrimaryParticleEnergy);
TreeEvent->SetBranchAddress("PrimaryParticlePosition", &PrimaryParticlePosition);
TreeEvent->SetBranchAddress("PrimaryParticleTime", &PrimaryParticleTime);
TreeEvent->SetBranchAddress("PrimaryParticleMomentumDirection", &PrimaryParticleMomentumDirection);

TreeEvent->SetBranchAddress("ParentID", &ParentID);
TreeEvent->SetBranchAddress("TrackID", &TrackID);
TreeEvent->SetBranchAddress("VolumeID", &VolumeID);
TreeEvent->SetBranchAddress("EnergyDeposition", &EnergyDeposition);
TreeEvent->SetBranchAddress("Position", &Position);
TreeEvent->SetBranchAddress("Pdg", &Pdg);
TreeEvent->SetBranchAddress("MomentumDirection", &MomentumDirection);
TreeEvent->SetBranchAddress("KineticEnergy", &KineticEnergy);
TreeEvent->SetBranchAddress("GlobalTime", &GlobalTime);

TreeEvent->SetBranchAddress("VertexTrackID", &VertexTrackID);
TreeEvent->SetBranchAddress("VertexMomentumDirection", &VertexMomentumDirection);
TreeEvent->SetBranchAddress("VertexPosition", &VertexPosition);	
TreeEvent->SetBranchAddress("VertexKineticEnergy", &VertexKineticEnergy);

//------------------------------------

//print active components

cout<<"active materials:"<<endl;

int HighestActiveIndex = -1;
for(unsigned int i = 0; i < VolumeIdActive->size(); i++)
	{
	if(VolumeIdActive->at(i) > HighestActiveIndex)  HighestActiveIndex = VolumeIdActive->at(i);
	}

vector<int> MapVolumeIdIndex(HighestActiveIndex+1,-1);

// mapping
for(unsigned int i = 0; i < VolumeIdActive->size(); i++)
	{
	cout<<"id: "<<VolumeIdActive->at(i)<<" material: "<<MaterialActive->at(i)<<" position: "<<PositionActive->at(i).at(0)<<" "<<PositionActive->at(i).at(1)<<" "<<PositionActive->at(i).at(2)<<" position: "<<DimensionActive->at(i).at(0)<<" "<<DimensionActive->at(i).at(1)<<" "<<DimensionActive->at(i).at(2)<<endl;

	MapVolumeIdIndex.at(VolumeIdActive->at(i)) = i;
	}
	
//print passive components

cout<<"passive materials:"<<endl;

for(unsigned int i = 0; i < VolumeIdPassive->size(); i++)
	{
	cout<<"id: "<<VolumeIdPassive->at(i)<<" material: "<<MaterialPassive->at(i)<<" position: "<<PositionPassive->at(i).at(0)<<" "<<PositionPassive->at(i).at(1)<<" "<<PositionPassive->at(i).at(2)<<" position: "<<DimensionPassive->at(i).at(0)<<" "<<DimensionPassive->at(i).at(1)<<" "<<DimensionPassive->at(i).at(2)<<endl;
	}

//------------------------------------

//creat histograms

char text[400];

// Initialize 1D histogram for energy deposition by Z position
TH1D* HEnergyDepositionZ = new TH1D("EnergyDepositionZ", "Energy Deposition by Z;Z position [mm];Energy deposition [MeV]", 5000, -28, -10);
HEnergyDepositionZ->SetLineWidth(2);
HEnergyDepositionZ->GetYaxis()->SetTitleOffset(1.6);
// HEnergyDepositionZ->SetStats(false);

// Initialize vector of 1D histograms for energy deposition by volume ID
vector<TH1D*> HEnergyDepositionVolumeID;
for (unsigned int i = 0; i < VolumeIdActive->size(); i++) {
    sprintf(text, "EnergyDepositionVolumeID%d", VolumeIdActive->at(i));
    HEnergyDepositionVolumeID.push_back(new TH1D(text, Form("Energy Deposition Volume ID %d;Energy deposition [MeV];Entries", VolumeIdActive->at(i)), 6000, 0, 10));
}

// Initialize vector of 2D histograms for energy deposition by Z position
TH2D* hTotalEnergyDeposition = new TH2D("hTotalEnergyDeposition", 
    "Total Energy Deposition by Volume;Scintillator Number;Total Energy Deposition [MeV]", 
    VolumeIdActive->size(), 0.5, 6.5, 6000, 0, 10);

TProfile* hprof = new TProfile("hprof","Total Energy Deposition by Volume;Scintillator Number;Total Energy Deposition [MeV]", 30, 0.5, 6.5);
hprof->SetStats(false);
	
//------------------------------------

// event loop
double NoEntries = TreeEvent->GetEntriesFast();

// Correction: Ensure you declare and initialize all needed variables before the loop
vector<double> EnergyDepositionPerVolume(VolumeIdActive->size(), 0); // Initialize with 0

for (unsigned int i = 0; i < NoEntries; i++) {
    TreeEvent->GetEntry(i);

    for (unsigned int j = 0; j < EnergyDeposition->size(); j++) {
    	
	double zPos = Position->at(j).at(2); // Example for getting Z position
	double edep = EnergyDeposition->at(j); // Energy deposition value
	
	// Fill HEnergyDepositionZ without normalization by NoEntries (assuming one entry per event)
	HEnergyDepositionZ->Fill(zPos, edep);
	int volumeIndex = MapVolumeIdIndex.at(VolumeID->at(j));
		
	// No normalization here as well; assuming you want to fill with the raw edep values
	HEnergyDepositionVolumeID[volumeIndex]->Fill(edep);

	// Accumulate energy deposition per volume
	EnergyDepositionPerVolume[volumeIndex] += edep;
	hTotalEnergyDeposition->Fill(VolumeID->at(j), edep);
		
	hprof->Fill(VolumeID->at(j),edep);
    }
}

//---------------------------------------

// Draws the 1D histogram for the edep at one layer and saves it in different output formats

// refers to canvas coordinates
TCanvas * CEnergyDepositionZ = new TCanvas("CEnergyDepositionZ","CEnergyDepositionZ", 200,10,1200,1200);

CEnergyDepositionZ->SetLeftMargin(0.15);
CEnergyDepositionZ->SetRightMargin(0.04);
CEnergyDepositionZ->SetTopMargin(0.04);

HEnergyDepositionZ->Draw("hist");

gPad->SetLogy(1);
gPad->SetGridx(1);
gPad->SetGridy(1);

// sprintf(text,"%s_EnergyDepositionZ.root", Filename.c_str());
// CEnergyDepositionZ->SaveAs(text);
// // sprintf(text,"%s_EnergyDepositionZ.pdf", Filename.c_str());
// // CEnergyDepositionZ->SaveAs(text);
// sprintf(text,"%s_EnergyDepositionZ.png", Filename.c_str());
// CEnergyDepositionZ->SaveAs(text);

//---------------------------------------

// Draws the 2D histogram for the edep according to each volume ID

TCanvas *cTotalEnergyDeposition = new TCanvas("cTotalEnergyDeposition", "Total Energy Deposition", 200, 20, 1200, 1200);
hTotalEnergyDeposition->Draw("COLZ");

// Configure canvas as needed, e.g., set log scale, grid
gPad->SetGridx(1);
gPad->SetGridy(1);

// // Assuming 'Filename' is a std::string or char[] that is properly defined
// sprintf(text, "%s_TotalEnergyDeposition.root", Filename.c_str());
// cTotalEnergyDeposition->SaveAs(text);
// sprintf(text, "%s_TotalEnergyDeposition.png", Filename.c_str());
// cTotalEnergyDeposition->SaveAs(text);
// // Optionally save as PNG or any other format

//---------------------------------------

// Draws the 1D histogram for the TProfile
TCanvas *cTProfileEdep = new TCanvas("cTProfileEdep", "TESTING TProfile Total Energy Deposition", 200, 10, 1200, 1200);

// This sets how the tProfile will Draw()
// any subsequent calls of Draw() will inherit the options gotten from SetOption
hprof->SetOption("HIST L SAME X0 E0");
// hprof->Draw("E0")
hprof->Draw("HIST L SAME X0 E0");
hprof->SetMarkerStyle(20);
hprof->SetMarkerSize(1.5);
// hprof->Draw();
// TGraph *g = new TGraph();
// for(int i=1; i<=hprof->GetNbinsX(); i++){
// 	if(hprof->GetBinContent(i) != 0.0){
// 		g->SetPoint(g->GetN(), hprof->GetBinCenter(i), hprof->GetBinContent(i));
// 	}
// }
// g->SetLineColor(kBlue);
// if(g->GetN() > 1) g->Draw("L");

// Configure canvas as needed, e.g., set log scale, grid
// gPad->SetGridx(1);
// gPad->SetGridy(1);
gPad->SetLogy();

//---------------------------------------

//another canvas for the edep across all volumes
TCanvas * CEnergyDepositionVolumeID = new TCanvas("CEnergyDepositionVolumeID","CEnergyDepositionVolumeID", 400,1,1200,1200);

CEnergyDepositionVolumeID->SetLeftMargin(0.15);
CEnergyDepositionVolumeID->SetRightMargin(0.04);
CEnergyDepositionVolumeID->SetTopMargin(0.04);

double MaxEnergyDepositionVolumeID = 0;
double MinEnergyDepositionVolumeID = 1e100;
for(unsigned int i = 0; i < VolumeIdActive->size(); i++) {
	if(HEnergyDepositionVolumeID.at(i)->GetMaximum() > MaxEnergyDepositionVolumeID) 
		MaxEnergyDepositionVolumeID = HEnergyDepositionVolumeID.at(i)->GetMaximum();
	
	for(int k = 1; k <= HEnergyDepositionVolumeID.at(i)->GetNbinsX(); k++) 	 
		if(HEnergyDepositionVolumeID.at(i)->GetBinContent(k) > 0 && HEnergyDepositionVolumeID.at(i)->GetBinContent(k) < MinEnergyDepositionVolumeID) 
			MinEnergyDepositionVolumeID = HEnergyDepositionVolumeID.at(i)->GetBinContent(k);
	}

//Draws a frame for the histogram with specified minimum and maximum values on the y-axis
TH1F * FEnergyDepositionVolumeID = CEnergyDepositionVolumeID->DrawFrame(0, MinEnergyDepositionVolumeID, 1, MaxEnergyDepositionVolumeID);
FEnergyDepositionVolumeID->GetYaxis()->SetTitleOffset(1.6);
FEnergyDepositionVolumeID->GetYaxis()->SetTitle("normalized entries");
FEnergyDepositionVolumeID->GetXaxis()->SetNdivisions(510);
FEnergyDepositionVolumeID->GetXaxis()->SetTitle("energy deposition [MeV]");

TLegend* LEnergyDepositionVolumeID = new TLegend(0.8,0.6,0.99,0.99);
LEnergyDepositionVolumeID->SetFillColor(0);

//Loops through the VolumeIdActive vector to draw histograms on the canvas
for(unsigned int i = 0; i < VolumeIdActive->size(); i++) {
	HEnergyDepositionVolumeID.at(i)->SetLineColor(Colors[i]);
	HEnergyDepositionVolumeID.at(i)->SetLineWidth(2);
	HEnergyDepositionVolumeID.at(i)->Draw("histsame");

	sprintf(text, "Volume ID %d", VolumeIdActive->at(i));
	LEnergyDepositionVolumeID->AddEntry(HEnergyDepositionVolumeID.at(i),text,"l");
	}
	
LEnergyDepositionVolumeID->Draw();

gPad->SetLogy(1);

// sprintf(text,"%s_EnergyDepositionVolumeID.root", Filename.c_str());
// CEnergyDepositionVolumeID->SaveAs(text);
// // sprintf(text,"%s_EnergyDepositionVolumeID.pdf", Filename.c_str());
// // CEnergyDepositionVolumeID->SaveAs(text);
// sprintf(text,"%s_EnergyDepositionVolumeID.png", Filename.c_str());
// CEnergyDepositionVolumeID->SaveAs(text);

//-----------------------------------------

// returning the TProfile
return hprof;
}


/*
 Given 2 vectors protons and electrons, print them on the same graph.
 UNSAFE IF PROTONS IS EMPTY

 To see what tprofile "histogram graphics attributes" can be changed see
 classTH1 on Root Docs
 OR
 TAttLine, TAttFill, TAttMarker on Root Docs
*/
void PlotProtonsAndElectrons(const vector<TProfile*>& protons, const vector<TProfile*>& electrons){

	// MARKER STYLES:
	// https://root.cern.ch/doc/master/classTAttMarker.html

	// Proton Style Options
	int protonColor = kPink;
	int protonMarkerStyle = 22;

	//Electron Style Options
	int electronColor = kAzure;
	int electronMarkerStyle = 21;
	
	// Shared Option Styles 
	// int sharedMarkerStyle = 20; // unused but still available if needed
	double sharedMarkerSize = 1.5;
	// Option_t* sharedErrorOption = "s";

    // Create a new canvas for plotting
    TCanvas *canvas = new TCanvas("canvas", "Multiple TProfiles", 20, 10, 1200, 1200);
	TLegend *legend = new TLegend(0.8,0.6,0.99,0.99); // Adjust position as needed

    // Loop over all profiles and draw them on the same graph
	
	// DRAW PROTONS
	std::vector<int> protonEnergies = {2, 10, 20, 30, 40, 50, 60, 70, 80};
	std::vector<int> protonColors = {kRed, kOrange+8, kOrange-3, kRed-3, kOrange+6, kOrange, kPink-9, kPink+9, kPink+1};

    for (int i = 0; i < protons.size(); i++){
		// profiles[i]->SetLineColor(color);
		// Protons are red == 1
		protons[i]->SetMarkerColor(protonColors[i]);
        protons[i]->SetMarkerStyle(protonMarkerStyle);
        protons[i]->SetMarkerSize(sharedMarkerSize);
		protons[i]->SetLineColor(protonColors[i]);
        // protons[i]->SetErrorOption(sharedErrorOption);

        if (i == 0){
            // If it's the first profile, draw with option "P" to draw points with errors
            protons[i]->Draw("L P E X0");
        }
        else{
            // For subsequent profiles, draw with option "same" to overlay on the existing plot
            protons[i]->Draw("L P E X0 same");
        }

		legend->AddEntry(protons[i], Form("Proton %dMeV", protonEnergies[i]), "1p");
    }
	canvas->Update();

	//DRAW ELECTRONS
	std::vector<int> electronEnergies = {250, 500, 750, 1000, 1250, 1500, 1750, 2000};
	std::vector<int> electronColors = {kBlue, kBlue-9, kAzure+10, kAzure+1, kAzure+6, kCyan, kCyan-3, kCyan-10};

    for (int i = 0; i < electrons.size(); i++){
		// profiles[i]->SetLineColor(color);
		//Electrons are blue == 2

		electrons[i]->SetMarkerColor(electronColors[i]);
        electrons[i]->SetMarkerStyle(electronMarkerStyle);
        electrons[i]->SetMarkerSize(sharedMarkerSize);
		electrons[i]->SetLineColor(electronColors[i]);
        // electrons[i]->SetErrorOption(sharedErrorOption);
        
		//removed the ->Draw("P") check here, as it caused only Electrons to be displayed.. It is unsafe if the list of Protons was empty
        electrons[i]->Draw("L P E X0 same");

		legend->AddEntry(electrons[i], Form("Electron %dkeV", electronEnergies[i]), "1p");
    }
	// legend attributes
	legend->SetFillColor(0);
	legend->Draw();

	// log axes
	// gPad->SetLogy(1);

	// Update the canvas to show the plot
    canvas->Update();
}


// trying something out
void PlotProtonsAndElectrons2(const vector<TProfile*>& protons, const vector<TProfile*>& electrons){

	// MARKER STYLES:
	// https://root.cern.ch/doc/master/classTAttMarker.html
	
	// Option_t* sharedErrorOption = "s";
	// Proton Style Options
    std::vector<int> protonColors = {kRed, kOrange+8, kOrange-3, kRed-3, kOrange+6, kPink-9, kPink+9, kPink+1};
	std::vector<int> protonEnergies = {10, 20, 30, 40, 50, 60, 70, 80};

    // Electron Style Options
    std::vector<int> electronColors = {kBlue, kBlue-9, kAzure+10, kAzure+1, kAzure-6, kCyan, kCyan-3, kCyan-10};
	std::vector<int> electronEnergies = {250, 500, 750, 1000, 1250, 1500, 1750, 2000};

    // Shared Option Styles
    double sharedMarkerSize = 1.5;

    // Create a new canvas for plotting
    TCanvas *canvas = new TCanvas("canvas", "Multiple TProfiles", 20, 10, 1200, 1200);
	TLegend *legend = new TLegend(0.8,0.6,0.99,0.99); // Adjust position as needed

    // Loop over all profiles and draw them on the same graph
	std::vector<TGraph*> graphs; // Store graphs for later adjustments
	
    // DRAW PROTONS
    for (int i = 0; i < protons.size(); i++){
        TGraph *g = new TGraph();
		// titles and stuff
		g->SetTitle("Electron and Proton Energy Deposition");
		g->GetYaxis()->SetTitle("Total Energy Deposition [MeV]");
		g->GetXaxis()->SetTitle("Scintillator Number");

        for(int j = 1; j <= protons[i]->GetNbinsX(); j++){
            if(protons[i]->GetBinContent(j) != 0.0){
                g->SetPoint(g->GetN(), protons[i]->GetBinCenter(j), protons[i]->GetBinContent(j));
            }
        }
        g->SetLineColor(protonColors[i]);
        g->SetMarkerColor(protonColors[i]);
        g->SetMarkerStyle(22);
        g->SetMarkerSize(sharedMarkerSize);
        std::string drawOptions = (i == 0 ? "APL" : "PL") + std::string(" SAME");
        g->Draw(drawOptions.c_str());
		graphs.push_back(g);

        legend->AddEntry(g, Form("Proton %dMeV", protonEnergies[i]), "lp");
    }

    // DRAW ELECTRONS
    for (int i = 0; i < electrons.size(); i++){
        TGraph *g = new TGraph();
        for(int j = 1; j <= electrons[i]->GetNbinsX(); j++){
            if(electrons[i]->GetBinContent(j) != 0.0){
                g->SetPoint(g->GetN(), electrons[i]->GetBinCenter(j), electrons[i]->GetBinContent(j));
            }
        }
        g->SetLineColor(electronColors[i]);
        g->SetMarkerColor(electronColors[i]);
        g->SetMarkerStyle(21);
        g->SetMarkerSize(sharedMarkerSize);
    	g->Draw("PL SAME");
		graphs.push_back(g);

        legend->AddEntry(g, Form("Electron %dkeV", electronEnergies[i]), "lp");
    }

	// Set axis limits
	double xMin = 0.5; // Adjust as needed
	double xMax = 6.5; // Adjust as needed
	double yMin = -1.0; // Adjust as needed
	double yMax = 4; // Adjust as needed

	for (TGraph* g : graphs) {
		g->GetXaxis()->SetLimits(xMin, xMax);
		g->GetYaxis()->SetRangeUser(yMin, yMax);
	}

    // legend attributes
    legend->SetFillColor(0);
    legend->Draw();

	// log scale
	gPad->SetLogy();

    // Update the canvas to show the plot
    canvas->Update();
}


/**
  hard coded plotter. change the files you want to load inside of the vector `files`, file reading doesn't work so we gotta go with hardcoding for now
 */
void hardCodePlotAll(){
    // PUT THE FILES YOU NEED HERE
    vector<string> protonFiles = {"/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps10MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps20MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps30MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps40MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps50MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps60MeV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/proton_gaps80MeV_FTFP_BERT.root"};

	vector<string> electronFiles = {"/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps250keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps500keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps750keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps1000keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps1250keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps1500keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps1750keV_FTFP_BERT.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/build/electron_gaps2MeV_FTFP_BERT.root"};

    vector<TProfile*> protonProfiles;
	vector<TProfile*> electronProfiles;
    
    cout << "Loading HARDCODED files for SimpleDetAnalysis at \n";

    for(string file : protonFiles){
		// TProfile* tProf
        protonProfiles.push_back(SimpleDetAnalysis(file));
        cout << "--pProf " + file + "\n";
    }
    cout << "...Done!\n";
    
	for(string file : electronFiles){
		electronProfiles.push_back(SimpleDetAnalysis(file));
        cout << "--eProf " + file + "\n";
    }
    cout << "...Done!\n";

	PlotProtonsAndElectrons2(protonProfiles, electronProfiles);
}
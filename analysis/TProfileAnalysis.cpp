#include<TFile.h>
#include<TTree.h>
#include<TROOT.h>
#include <TCanvas.h>
#include<TLegend.h>
#include<TColor.h>
#include<TMath.h>
#include<TProfile.h>

#include<vector>
#include<string>
#include<stdlib.h>

using namespace std;

void PlotProfiles(const std::vector<std::string>& protonFileNames, const std::vector<std::string>& electronFileNames) {
    // Create canvas
    TCanvas* canvas = new TCanvas("canvas", "Energy Deposition Profiles", 800, 600);

    // Create legend
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);

    // initializing variables
    const int numProtonEnergies = 9;
    const int numElectronEnergies = 8;
    int protonFileIndex = 0;
    int electronFileIndex = 0;
    const int numBins = 5000;
    const double minX = 0.0; // Minimum value on the x-axis
    const double maxX = 100.0; // Maximum value on the x-axis

    // Loop over proton files
    for (const auto& protonFileName : protonFileNames) {
        TFile* protonFile = TFile::Open(protonFileName.c_str());
        
        // Loop over proton energies
        for (int protonEnergy = 0; protonEnergy < numProtonEnergies; ++protonEnergy) {
            TTree* protonTree = (TTree*)protonFile->Get(Form("protonTree_%d", protonEnergy));

            TProfile* protonProfile = new TProfile(Form("protonProfile_%d_%d", protonEnergy, protonFileIndex), Form("Proton Energy Deposition Profile (%d MeV)", protonEnergy), numBins, minX, maxX);
            protonTree->Draw("energyDeposition >>+ protonProfile", "", "goff");
            protonProfile->SetMarkerColor(kRed);
            protonProfile->SetLineColor(kRed);
            if (protonEnergy == 0 && protonFileIndex == 0) {
                protonProfile->Draw();
            } else {
                protonProfile->Draw("same");
            }
            legend->AddEntry(protonProfile, Form("Protons (%d MeV)", protonEnergy), "l");
        }
    }

    // for electrons
        for (const auto& electronFileName : electronFileNames) {
        TFile* electronFile = TFile::Open(electronFileName.c_str());

        // Loop over electron energies
        for (int electronEnergy = 0; electronEnergy < numElectronEnergies; ++electronEnergy) {
            TTree* electronTree = (TTree*)electronFile->Get(Form("electronTree_%d", electronEnergy));

            TProfile* electronProfile = new TProfile(Form("electronProfile_%d_%d", electronEnergy, electronFileIndex), Form("Electron Energy Deposition Profile (%d MeV)", electronEnergy), numBins, minX, maxX);
            electronTree->Draw("energyDeposition >>+ electronProfile", "", "goff");
            electronProfile->SetMarkerColor(kGreen);
            electronProfile->SetLineColor(kGreen);
            if (electronEnergy == 0 && electronFileIndex == 0) {
                electronProfile->Draw();
            } else {
                electronProfile->Draw("same");
            }
            legend->AddEntry(electronProfile, Form("Electrons (%d MeV)", electronEnergy), "l");
        }
    }

    // Add legend to canvas
    legend->Draw();

    // Draw canvas
    canvas->Draw();

    // Save canvas to file
    const char* outputFileName = "TProfile.png"; // Output file name
    canvas->SaveAs(outputFileName);
}

int main() {
    std::vector<std::string> protonFileNames = {"/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_2MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_10MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_20MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_30MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_40MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_50MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_60MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_70MeV.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/proton_gaps_FTFP_BERT_80MeV.root"};

    std::vector<std::string> electronFileNames = {"/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_250keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_500keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_750keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_1000keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_1250keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_1500keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_1750keV2.root", "/Users/neptoon/Desktop/VIA-SEES/SimpleDet2/ROOTfiles/electron_gaps_FTFP_BERT_2000keV2.root"};

    PlotProfiles(protonFileNames, electronFileNames);
    
    return 0;
}
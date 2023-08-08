#include <iostream>
#include<string>
#include<sstream>
#include <fstream>
#include <stdlib.h>
#include<algorithm>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TF1.h>
#include <TROOT.h>
#include <TChain.h>

using namespace std;

// void efficency()
int main()
{

    TFile *ipf = new TFile("AnaEx01.root");
    if (ipf->IsZombie()) {
    cout << "Error opening file!" << endl;
    exit(-1);
    }
    // ipf->cd();
    TTree *ipt=(TTree*)ipf->Get("Ntuple");

    double fEdep;

    ipt->SetBranchAddress("fEdep", &fEdep);

    Double_t peak = 0.;

    // cout << peak << endl;

    Double_t ratio = 0.;

    Long64_t nentries = ipt->GetEntries();
    cout << nentries << endl;
    for(Long64_t jentry = 0; jentry < nentries; jentry++) {
    
        ipt->GetEntry(jentry);
        
        if (fEdep >= 0.015 - 0.001)
        {
            /* code */
            peak += 1;
        }
    }

    cout << peak << endl;

    ratio = peak / 100000;


    cout << "ratio = " << ratio << endl;

    ipf->Close();

    return 0;
}
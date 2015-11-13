#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */


void MakeRocCurves(){

gROOT->ProcessLine(".L ./tdrstyle.C");
setTDRStyle();

TFile *fsig = TFile::Open("./fEff_OldDeltaBeta.root");  
TFile *fbkg = TFile::Open("./fFakeRate_OldDeltaBeta.root");  

TH1F* hsig_pu40 = (TH1F*)fsig->Get("EffLooseIso3Hits_Pt_Pu40"); 
TH1F* hsig_pu20 = (TH1F*)fsig->Get("EffLooseIso3Hits_Pt_Pu20"); 
TH1F* hsig_8tev = (TH1F*)fsig->Get("EffLooseIso3Hits_Pt_8Tev"); 	
	
TH1F* hbkg_pu40 = (TH1F*)fbkg->Get("FRLooseIso3Hits_Pt_Pu40"); 
TH1F* hbkg_pu20 = (TH1F*)fbkg->Get("FRLooseIso3Hits_Pt_Pu20");
TH1F* hbkg_8tev = (TH1F*)fbkg->Get("FRLooseIso3Hits_Pt_8Tev"); 	
	
assert(hsig_pu40->GetNbinsX() == hbkg_pu40->GetNbinsX());	
int numBins = hsig_pu40->GetNbinsX();   
	int numBins_bkg = hbkg_pu40->GetNbinsX();   
	
    std::vector<double> graphPointsX,graphPointsX_pu20 ;
    std::vector<double> graphPointsY, graphPointsY_pu20;
	
    double mean_signal = hsig_pu40->GetMean();
    double mean_background = hbkg_pu40->GetMean();
    std::cout << "NbinSig: signal = " << numBins << ", background = " << numBins_bkg << std::endl;
    std::cout << "mean: signal = " << mean_signal << ", background = " << mean_background << std::endl;
    int increment;
    increment = +1;
    double initialBin = 0;
    double runningSum_signal = 0.;
    double normalization_signal = hsig_8tev->Integral();
    double runningSum_background = 0.;
    double normalization_background = hbkg_8tev->Integral();
    
    double runningSum_signal20 = 0.;
    double normalization_signal20 = hsig_pu40->Integral();
    double runningSum_background20 = 0.;
    double normalization_background20 = hbkg_pu40->Integral();
	
	
    for ( int iBin = initialBin; iBin >= 0 && iBin <= (numBins + 1); iBin += increment ) {
      //	assert( hbkg_pu40->GetBinCenter(iBin) ==  hsig_pu40->GetBinCenter(iBin));
      runningSum_signal += hsig_8tev->GetBinContent(iBin);
      runningSum_background += hbkg_8tev->GetBinContent(iBin);
      
      runningSum_signal20 += hsig_pu40->GetBinContent(iBin);
      runningSum_background20 += hbkg_pu40->GetBinContent(iBin);
		      
		
      //	std::cout << "running sum(bin #" << iBin << "): signal = " << runningSum_signal20 << ", background = " << runningSum_background20 << std::endl;
      
      if ( (runningSum_signal >= 1.e-6 || runningSum_background >= 1.e-6) &&
	   ((normalization_signal - runningSum_signal) >= 1.e-6 || (normalization_background - runningSum_background) >= 1.e-6) ) {
	//double x = 1. - (runningSum_signal/normalization_signal);
	double x = 1-(runningSum_signal/normalization_signal);
	graphPointsX.push_back(x);
	double y = runningSum_background/normalization_background;
	graphPointsY.push_back(y);
			
	
	
      }
      
		if ( (runningSum_signal20 >= 1.e-6 || runningSum_background20 >= 1.e-6) &&
			((normalization_signal20 - runningSum_signal20) >= 1.e-6 || (normalization_background20 - runningSum_background20) >= 1.e-6) ) {

			double x20 = (runningSum_signal20/normalization_signal20);
			graphPointsX_pu20.push_back(x20);
			double y20 = runningSum_background20/normalization_background20;
			graphPointsY_pu20.push_back(y20);
			
			std::cout << "x(bin #" << iBin << "): signal = " << x20 << ", y = " << y20 << std::endl;
		}		
		
		
    }
    assert(graphPointsX.size() == graphPointsY.size());
	
	int numPoints = graphPointsX.size();
	int numPoints_pu20 = graphPointsX_pu20.size();
	cout<<" pu20 num punti "<<numPoints_pu20<<endl;
	
	TGraph* graph = 0; 
	TGraph* graph_pu20 = 0; 
	
	//TGraph* graphPU20 = new TGraph(numPoints_pu20);

	
    if ( numPoints >= 1 ) {
		graph = new TGraph(numPoints);
		for ( int iPoint = 0; iPoint < numPoints; ++iPoint ) {
			graph->SetPoint(iPoint, graphPointsX[iPoint], graphPointsY[iPoint]);
		}
    } else {
		std::cerr << "Warning: failed to compute efficiency and fake-rate for graph = " << graphName << " !!" << std::endl;
		graph = new TGraph(1);
		graph->SetPoint(0, 0.5, 0.5);
    
	}

	
	
    if ( numPoints_pu20 >= 1 ) {
		graph_pu20 = new TGraph(numPoints_pu20);
		for ( int iPoint = 0; iPoint < numPoints_pu20; ++iPoint ) {
			graph_pu20->SetPoint(iPoint, graphPointsX_pu20[iPoint], graphPointsY_pu20[iPoint]);
		}
    } else {
		std::cerr << "Warning: failed to compute efficiency and fake-rate for graph = " << graphName_<< " !!" << std::endl;
		graph_pu20 = new TGraph(1);
		graph_pu20->SetPoint(0, 0.5, 0.5);
		
	}
	
	
    TCanvas *IsoRoc = new TCanvas("IsoRoc","IsoRoc",800,700);
	graph_pu20->SetLineColor(kMagenta);
	graph_pu20->Draw("ACP");
	graph->Draw("CP");

	


}

#include <TH1>
#include <TString.h>
#include <vector>

void PlotPerformance_Pt(){
	
  gROOT->ProcessLine(".L ./tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptStat(0000000);	
	
     
  TFile *f1 = TFile::Open("histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");  

	 
	 std::vector<TString> NumIsoNamesLooseFakeTau;
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterLooseIso3H");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterLooseIso3HRho");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterChIsoPtSum");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso_05");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso_1");
	NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso_15");
	NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso_Rho_Off");
	NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterNewIso_RhoNe_Off");
	 NumIsoNamesLooseFakeTau.push_back("hTauGenMatchPt_AfterIsoPU");
	
	
		
	TH1F* histoNum[10];
	TH1F* histoDen[10];
	TH1F* hFakeRate[10];
	
	TH1F* histoNumReal[10];
	TH1F* histoDenReal[10];
	TH1F* hEff[10];
	
	TH1F* histoNumTight[10];
	TH1F* histoDenTight[10];
	TH1F* hFakeRateTight[10];
	
	TH1F* histoNumRealTight[10];
	TH1F* histoDenRealTight[10];
	TH1F* hEffTight[10];
	
	
	
	TH1F* histoNumLoose[10];
	TH1F* histoDenLoose[10];
	TH1F* hFakeRateLoose[10];
	
	TH1F* histoNumRealLoose[10];
	TH1F* histoDenRealLoose[10];
	TH1F* hEffLoose[10];
	
	
	
	double  sumFakeMedium[10] ;
	double  sumEffMedium[10] ;
	
	double  sumFakeTight[10] ;
	double  sumEffTight[10] ;
	
	double  sumFakeLoose[10] ;
	double  sumEffLoose[10] ;

	
	std::vector<double> MeanFake, MeanEff;
	std::vector<double> MeanFakeTight, MeanEffTight;
	std::vector<double> MeanFakeLoose, MeanEffLoose;
	std::vector<TString> DenNames;
	int fileNumMed = NumIsoNamesLooseFakeTau.size();
	
	int binMin=0;
	int binMax=200;
	int NumTotBin =50;
	
	for(int i=0;i<10; i++){
		
	TString idLooseFake ("FakeRateLoose");
	idLooseFake +=(i+1);		
		
				
	
	histoNumLoose[i] = (TH1F*)f1->Get(NumIsoNamesLooseFakeTau[i]);
	cout<<i<<" bin size num "<<histoNumLoose[i]->GetNbinsX()<<endl;
	histoNumLoose[i]->Rebin(4);
	
		
	f1->cd();
	histoDenLoose[i] = (TH1F*)hTauGenMatchPt->Clone();
	cout<<i<<" bin size  den "<<histoDenLoose[i]->GetNbinsX()<<endl;
	histoDenLoose[i]->Rebin(4);	
	hFakeRateLoose[i] = new TH1F(idLooseFake,idLooseFake ,NumTotBin,binMin,binMax);
	hFakeRateLoose[i]->Divide(histoNumLoose[i] ,histoDenLoose[i], 1. ,  1. , "B");		
	}
	//histoNumLoose[0]->Draw();
	//histoDenLoose[0]->Draw();
	
	TCanvas *FakeRateCanvas = new TCanvas("FakeRateCanvas ","FakeRateCanvas ",1000,700);		
	FakeRateCanvas->cd();
	 //gPad->SetLogy();
	 gPad->SetGridy();
	for(int i=0;i<10; i++){
	hFakeRateLoose[i]->SetMarkerStyle(20+i);
	hFakeRateLoose[i]->SetMarkerSize(1.2);
 
	}
	
	hFakeRateLoose[0]->SetMarkerColor(kRed);
	hFakeRateLoose[1]->SetMarkerColor(kBlue);
	hFakeRateLoose[2]->SetMarkerColor(kViolet);
	hFakeRateLoose[3]->SetMarkerColor(kGreen);
	hFakeRateLoose[7]->SetMarkerColor(1);
	hFakeRateLoose[8]->SetMarkerColor(kTeal+1);
	hFakeRateLoose[9]->SetMarkerColor(kOrange+1);
	
	hFakeRateLoose[0]->SetLineColor(kRed);
	hFakeRateLoose[1]->SetLineColor(kBlue);
	hFakeRateLoose[2]->SetLineColor(kViolet);
	hFakeRateLoose[3]->SetLineColor(kGreen);
	//hFakeRateLoose[4]->Draw("SAME");
	//hFakeRateLoose[5]->Draw("SAME");
	//hFakeRateLoose[6]->Draw("SAME");
	hFakeRateLoose[7]->SetLineColor(1);
	hFakeRateLoose[8]->SetLineColor(kTeal+1);
	hFakeRateLoose[9]->SetLineColor(kOrange+1);

	
	hFakeRateLoose[0]->Draw();
	hFakeRateLoose[1]->Draw("SAME");
	hFakeRateLoose[2]->Draw("SAME");
	hFakeRateLoose[3]->Draw("SAME");
	//hFakeRateLoose[4]->Draw("SAME");
	//hFakeRateLoose[5]->Draw("SAME");
	//hFakeRateLoose[6]->Draw("SAME");
	hFakeRateLoose[7]->Draw("SAME");
	hFakeRateLoose[8]->Draw("SAME");
	hFakeRateLoose[9]->Draw("SAME");
	hFakeRateLoose[0]->SetMinimum(0.3);
    hFakeRateLoose[0]->SetMaximum(0.9);
	hFakeRateLoose[0]->GetXaxis()->SetTitle("gen. P_{T}^{#tau} [GeV]");
	hFakeRateLoose[0]->GetYaxis()->SetTitle("Efficiency");

	FakeRateCanvas->cd();
	TLegend* legend = new TLegend( 0.35, 0.18, 0.7, 0.4);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	
		
	legend->AddEntry(hFakeRateLoose[0], "Old #Delta#beta", "p");
	legend->AddEntry(hFakeRateLoose[1], "New #Delta#beta (2.0*RMS)", "p");
	legend->AddEntry(hFakeRateLoose[2], "Old #rho Correction", "p");
	legend->AddEntry(hFakeRateLoose[7], "New #rho Correction (2.0*RMS)", "p");
	legend->AddEntry(hFakeRateLoose[8], "New #rho^{neutral} Correction (2.0*RMS)", "p");
	legend->AddEntry(hFakeRateLoose[9], "Charged Particle Isolation |dz|>2mm (2*RMS)", "p");
	legend->AddEntry(hFakeRateLoose[3], "Charged Particle Isolation", "p");
	//legend->Draw("same");
	FakeRateCanvas->SaveAs("./PU40/EffPt.pdf"); 
	

}

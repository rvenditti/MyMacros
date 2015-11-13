#include <TH1>
#include <sstream>
#include <string>
#include <iostream>

void FitAndOverlap(){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();


  ////////////////////////////////////////////////////////////////////////////
  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
  TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");

  gStyle->SetOptStat(0000000);
 
 	
	TCanvas* canvas = new TCanvas("canvas", "PU ISO VS NVTX", 800, 900);
	
	TH2F* hTau_NVtxVSpuCorrPtSum_PU20 = (TH2F*)f1->Get("hTau_NVtxVSpuCorrPtSum");
	TH2F* hTau_NVtxVSpuCorrPtSum_PU40 = (TH2F*)f2->Get("hTau_NVtxVSpuCorrPtSum");
	TH2F* hTau_NVtxVSpuCorrPtSum_8TeV = (TH2F*)f3->Get("hTau_NVtxVSpuCorrPtSum");

	TH2F*	hTau_NVtxVSChIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSChIso");
	TH2F*	hTau_NVtxVSChIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSChIso");
	TH2F*	hTau_NVtxVSChIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSChIso");

	
	TH2F*    hTau_NVtxVSNeIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNeIso");
	TH2F*    hTau_NVtxVSNeIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNeIso");
	TH2F*    hTau_NVtxVSNeIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSNeIso");

	TH2F*    hTau_NVtxVSRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSRawIso");
	TH2F*    hTau_NVtxVSRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSRawIso");
	TH2F*    hTau_NVtxVSRawIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSRawIso");
	
	TH2F*    hTau_NVtxVSNewRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNewRawIso");
	TH2F*    hTau_NVtxVSNewRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNewRawIso");

	int	NBins =60;
	
	TH1D *ProjYChIso40; 
	TH1D *ProjYChIso20;
	TH1D *ProjYChIso8; 
	ProjYChIso40 = (TH1D) malloc(80 * sizeof(TH1D));
	ProjYChIso20 = (TH1D) malloc(60 * sizeof(TH1D));
	ProjYChIso8 = (TH1D) malloc(60 * sizeof(TH1D));
	
	TH1F *prof1 = new TH1F("prof1","prof1",NBins,0,NBins);
	TH1F *prof2 = new TH1F("prof2","prof2",NBins,0,NBins);
	TH1F *prof3 = new TH1F("prof3","prof3",NBins,0,NBins);
	
	
	TH1D *ProjYNeIso40; 
	TH1D *ProjYNeIso20;
	TH1D *ProjYNeIso8; 
	ProjYNeIso40 = (TH1D) malloc(80 * sizeof(TH1D));
	ProjYNeIso20 = (TH1D) malloc(60 * sizeof(TH1D));
	ProjYNeIso8 = (TH1D) malloc(60 * sizeof(TH1D));
	
	
	TH1F *prof_ne20 = new TH1F("prof_ne20","prof_ne20",NBins,0,NBins);
	TH1F *prof_ne40 = new TH1F("prof_ne40","prof_ne40",NBins,0,NBins);
	TH1F *prof_ne8tev = new TH1F("prof_ne8tev","prof_ne8tev",NBins,0,NBins);
	

	
	
	for(int i=0;i<80;++i){
		ProjYChIso40[i]= hTau_NVtxVSpuCorrPtSum_PU40->ProjectionY("ProjYChIso40", i, i+1); 
		ProjYNeIso40[i]= hTau_NVtxVSNeIso_PU40->ProjectionY("ProjYNeIso40", i, i+1); 
		if( ProjYChIso40[i].GetEntries() > 100) {	
		prof2->SetBinContent(i,ProjYChIso40[i].GetMean());
		prof2->SetBinError(i,ProjYChIso40[i].GetMeanError() );}
		
		if( ProjYNeIso40[i].GetEntries() > 100) {	
		prof_ne40->SetBinContent(i,ProjYNeIso40[i].GetMean());
		prof_ne40->SetBinError(i,ProjYNeIso40[i].GetMeanError() );}
	}
	
	for(int i=0;i<NBins;++i){
		ProjYChIso20[i]= hTau_NVtxVSpuCorrPtSum_PU20->ProjectionY("ProjYChIso20", i, i+1); 
		ProjYNeIso20[i]= hTau_NVtxVSNeIso_PU20->ProjectionY("ProjYNeIso20", i, i+1); 
		if( ProjYChIso20[i].GetEntries() > 150) {
		prof1->SetBinContent(i,ProjYChIso20[i].GetMean());
		prof1->SetBinError(i,ProjYChIso20[i].GetMeanError() );
		}
		if( ProjYNeIso20[i].GetEntries() > 150) {	
		prof_ne20->SetBinContent(i,ProjYNeIso20[i].GetMean());
		prof_ne20->SetBinError(i,ProjYNeIso20[i].GetMeanError() );}
		
	}
	
	for(int i=0;i<NBins;++i){
		ProjYChIso8[i]= hTau_NVtxVSpuCorrPtSum_8TeV->ProjectionY("ProjYChIso8", i, i+1); 
		ProjYNeIso8[i]= hTau_NVtxVSNeIso_8TeV->ProjectionY("ProjYNeIso8", i, i+1); 
		if( ProjYChIso8[i].GetEntries() > 150) {
			prof3->SetBinContent(i,ProjYChIso8[i].GetMean());
		prof3->SetBinError(i,ProjYChIso8[i].GetMeanError() );}
		if( ProjYNeIso8[i].GetEntries() > 150) {	
		prof_ne8tev->SetBinContent(i,ProjYNeIso8[i].GetMean());
		prof_ne8tev->SetBinError(i,ProjYNeIso8[i].GetMeanError() );}
	}
			//cout<<i<<" Mean "<<ProjYNeIso40[i].GetMean()<<" ± "<<ProjYNeIso40[i].GetMeanError()<<endl;
			//cout<<"	RMS= "<< ProjYNeIso40[i].GetRMS()<<" ± "<<ProjYNeIso40[i].GetRMSError()<< endl;	
			
			

		
	canvas->cd();
		
	prof1->SetMarkerStyle(20);
	prof2->SetMarkerStyle(20);
	prof3->SetMarkerStyle(20);
	
	prof1->SetMarkerColor(kMagenta);
	prof2->SetMarkerColor(kBlue);
	
	prof2->Draw();
	prof1->Draw("SAME"); 
	prof3->Draw("SAME");   
	prof2->GetXaxis()->SetTitle("N_{vtx}");
	prof2->GetYaxis()->SetTitle("<P_{T}^{PU}> [GeV]");
	prof2->SetMinimum(0);
	


	
	TF1  *funPU40 = new TF1("funPU40"," [0]*x + [1] ",0,60) ; 
	TF1  *funPU20 = new TF1("funPU20"," [0]*x + [1]",0,60) ; 
	TF1  *fun8TEV = new TF1("fun8TEV"," [0]*x + [1] ",0,50) ; 
	
	cout<<" ************************************************************ fit PUCorr pu40  ************************************************************"<<endl;
	prof2->Fit("funPU40","N0Q","E",20,NBins);
	cout<<" ************************************************************ fit PUCorr pu20  ************************************************************"<<endl;
	prof1->Fit("funPU20","N0Q","E",0,NBins);
	cout<<" ************************************************************ fit PUCorr 8tev  ************************************************************"<<endl;
	prof3->Fit("fun8TEV","N0Q","E",0,NBins);	
	
	fun8TEV->SetParameter(0,fun8TEV->GetParameter(0));
	fun8TEV->SetParameter(1,fun8TEV->GetParameter(1));
	
	funPU40->SetParameter(0,funPU40->GetParameter(0));
	funPU40->SetParameter(1,funPU40->GetParameter(1));
	
	funPU20->SetParameter(0,funPU20->GetParameter(0));
	funPU20->SetParameter(1,funPU20->GetParameter(1));
	
	fun8TEV ->SetLineColor(kBlack); fun8TEV->Draw("same");
	funPU20 ->SetLineColor(kMagenta); funPU20->Draw("same");
	funPU40->SetLineColor(kBlue); funPU40->Draw("same");
	
	cout<<" chi2 40="<<funPU40->GetChisquare()<<endl;
	cout<<" chi2 20="<<funPU20->GetChisquare()<<endl;
	cout<<" chi2 8tev="<<fun8TEV->GetChisquare()<<endl;
	
	TLegend* legend = new TLegend( 0.25, 0.75, 0.45, 0.9);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(fun8TEV, "Summer12, 8 TeV", "l");
	legend->AddEntry(funPU20, "Fall13, 13 TeV, PU20, bx25", "l");
	legend->AddEntry(funPU40, "Fall13, 13 TeV, PU40, bx25", "l");
	//canvas->cd();
	//legend->Draw("same");
	
	
	TCanvas* canvas1 = new TCanvas("canvas1", "canvas1", 800, 900);
	canvas1->cd();

	prof_ne20->SetLineColor(kMagenta);
	prof_ne40->SetLineColor(kBlue);
	prof_ne40->SetMarkerStyle(20);
	prof_ne20->SetMarkerStyle(20);
	prof_ne8tev->SetMarkerStyle(20);
	
	prof_ne40->SetMarkerColor(kBlue);
	prof_ne20->SetMarkerColor(kMagenta);
	
	
	prof_ne40->Draw();
	prof_ne20->Draw("SAME");
	prof_ne8tev->Draw("SAME");
	prof_ne40->SetMinimum(0);
	//prof_ne40->Fit("pol1");
	prof_ne40->GetXaxis()->SetTitle("N_{vtx}");
	prof_ne40->GetYaxis()->SetTitle("<P_{T}^{#gamma}> [GeV]");
	
	TF1  *fun_NE_PU40 = new TF1("fun_NE_PU40"," [0]*x + [1]",0,60) ; 
	TF1  *fun_NE_PU20 = new TF1("fun_NE_PU20"," [0]*x + [1]",0,60) ; 
	TF1  *fun_NE_8TEV = new TF1("fun_NE_8TEV"," [0]*x + [1]",0,60) ; 
	
	cout<<" ************************************************************ fit ne iso pu40 ************************************************************"<<endl;
	prof_ne40->Fit("fun_NE_PU40","N0Q");
	cout<<" ************************************************************ fit ne iso pu20 ************************************************************"<<endl;
	prof_ne20->Fit("fun_NE_PU20","N0Q");
	cout<<" ************************************************************ fit ne iso 8tev ************************************************************"<<endl;
	prof_ne8tev->Fit("fun_NE_8TEV","N0Q");	
	
	fun_NE_8TEV->SetParameter(0,fun_NE_8TEV->GetParameter(0));
	fun_NE_8TEV->SetParameter(1,fun_NE_8TEV->GetParameter(1));
	
	fun_NE_PU40->SetParameter(0,fun_NE_PU40->GetParameter(0));
	fun_NE_PU40->SetParameter(1,fun_NE_PU40->GetParameter(1));
	
	fun_NE_PU20->SetParameter(0,fun_NE_PU20->GetParameter(0));
	fun_NE_PU20->SetParameter(1,fun_NE_PU20->GetParameter(1));
	
	fun_NE_8TEV ->SetLineColor(kBlack); fun_NE_8TEV->Draw("same");
	fun_NE_PU20 ->SetLineColor(kMagenta); fun_NE_PU20->Draw("same");
	fun_NE_PU40 ->SetLineColor(kBlue); fun_NE_PU40->Draw("same");
	
	
	canvas1->cd();
	legend->Draw("same");
	
	


	cout<<"  pu40 slope;"<<fun_NE_PU40->GetParameter(0)<<" ±  "<<fun_NE_PU40->GetParError(0)<<"; offset;"<<fun_NE_PU40->GetParameter(1)<<" ± "<<fun_NE_PU40->GetParError(1)<<endl;
	cout<<"  pu20 slope;"<<fun_NE_PU20->GetParameter(0)<<" ±  "<<fun_NE_PU20->GetParError(0)<<"; offset;"<<fun_NE_PU20->GetParameter(1)<<" ± "<<fun_NE_PU20->GetParError(1)<<endl;
	cout<<"  8tev slope;"<<fun_NE_8TEV->GetParameter(0)<<" ±  "<<fun_NE_8TEV->GetParError(0)<<"; offset;"<<fun_NE_8TEV->GetParameter(1)<<" ± "<<fun_NE_8TEV->GetParError(1)<<endl;
	
	cout<<"  pu contribution slope;  offset"<<endl;
	cout<<" pu40 slope;"<<funPU40->GetParameter(0)<<" ± "<<funPU40->GetParError(0)<<"; offset;"<<funPU40->GetParameter(1)<<" ± "<<funPU40->GetParError(1)<<endl;
	cout<<" pu20 slope;"<<funPU20->GetParameter(0)<<" ± "<<funPU20->GetParError(0)<<"; offset;"<<funPU20->GetParameter(1)<<" ±"<<funPU20->GetParError(1)<<endl;
	cout<<" 8tev slope;"<<fun8TEV->GetParameter(0)<<" ± "<<fun8TEV->GetParError(0)<<"; offset;"<<fun8TEV->GetParameter(1)<<" ±"<<fun8TEV->GetParError(1)<<endl;
	
	cout<<"  RATIO NE/PU"<<endl;
	cout << "  pu40;"<<fun_NE_PU40->GetParameter(0)/funPU40->GetParameter(0)<<" ± "<<(fun_NE_PU40->GetParameter(0)/funPU40->GetParameter(0)) * TMath::Sqrt( (funPU40->GetParError(0)/funPU40->GetParameter(0))*(funPU40->GetParError(0)/funPU40->GetParameter(0)) + (fun_NE_PU40->GetParError(0)/fun_NE_PU40->GetParameter(0))*(fun_NE_PU40->GetParError(0)/fun_NE_PU40->GetParameter(0)) ) <<endl;
	cout << "  pu20;"<<fun_NE_PU20->GetParameter(0)/funPU20->GetParameter(0)<<" ± "<<(fun_NE_PU20->GetParameter(0)/funPU20->GetParameter(0)) * TMath::Sqrt( (funPU20->GetParError(0)/funPU20->GetParameter(0))*(funPU20->GetParError(0)/funPU20->GetParameter(0)) + (fun_NE_PU40->GetParError(0)/fun_NE_PU20->GetParameter(0))*(fun_NE_PU20->GetParError(0)/fun_NE_PU20->GetParameter(0)) ) <<endl;
	cout << "  8tev;"<<fun_NE_8TEV->GetParameter(0)/fun8TEV->GetParameter(0)<<" ± "<<(fun_NE_8TEV->GetParameter(0)/fun8TEV->GetParameter(0)) * TMath::Sqrt( (fun8TEV->GetParError(0)/fun8TEV->GetParameter(0))*(fun8TEV->GetParError(0)/fun8TEV->GetParameter(0)) + (fun_NE_8TEV->GetParError(0)/fun_NE_8TEV->GetParameter(0))*(fun_NE_8TEV->GetParError(0)/fun_NE_8TEV->GetParameter(0)) ) <<endl;
	
	
	
	
	canvas->SaveAs("ChIsoVsNVTX.pdf");
	canvas1->SaveAs("NeIsoVsNVTX.pdf");
	
	
	
}

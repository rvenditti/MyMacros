#include <TH1>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

//hTau_RhoVsNeutralIso
//hTau_RhoNeutralVsNeutralIso
//hTau_NeIsoVSpuCorrIso
//hTau_NVtxVSNeIso
//hTau_NVtxVSpuCorrPtSum
//hTau_NVtxVSNeIso
//hTau_NVtxVSpuCorrPtSum
//hTau_puCorrPtSumVSNeIso
//hTau_NeIsoVSpuCorrIso

void FitAndGiveCorr(string inputfile="histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root", TString histoName = "hTau_NeIsoVSpuCorrIso" ){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();
	gStyle->SetOptStat(00000000);

	TFile* f = new TFile(inputfile.c_str());	
	TH2F*  h2  = (TH2F*)f->Get(histoName);
		
	//////////////////////////////////////////////////////////////////canvas scatter rho vs iso neutral///////////////////////////////////////////////////////////////////////////////////////////////////	
	TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 700, 700);
	h2->GetYaxis()->SetTitle("Iso^{Neutral} [GeV]");
	h2->GetXaxis()->SetTitle("PuIso [GeV]");
	h2->Draw("COLZ");
	cout<<"XY correlation factor "<<h2->GetCorrelationFactor()<<endl;
	canvas2->SaveAs( "DirPlotsPU/"+histoName+".png" );
	const int NBins = h2->GetNbinsX();
	cout<<" NBins "<<NBins<<endl;
	TH1D *ProjY; 
	ProjY = (TH1D) malloc(NBins * sizeof(TH1D));
	
	TH1F *hMean = new TH1F("hMean","hMean",NBins,0,NBins);
	TH1F *hRMS = new TH1F("hRMS","hRMS",NBins,0,NBins);
	
	double meanRMS =0;
	double den =0;
	double num =0;

	double weight[500];
	
	for(int i=0;i<NBins;++i){
		TString id =  "ProjY";
		id  ++;
		ProjY[i]= h2->ProjectionY("ProjY", i, i+1); 

		if( ProjY[i].GetEntries() > 100) {
			

		hMean->SetBinContent(i,ProjY[i].GetMean());
		hMean->SetBinError(i,ProjY[i].GetMeanError() );
	    hRMS->SetBinContent(i, ProjY[i].GetRMS());
		hRMS->SetBinError(i,ProjY[i].GetRMSError());

			//cout<<i<<" Mean "<<ProjY[i].GetMean()<<" ± "<<ProjY[i].GetMeanError()<<endl;
			//cout<<"	RMS= "<< ProjY[i].GetRMS()<<" ± "<<ProjY[i].GetRMSError()<< endl;	
			
			weight[i] = 1/ (ProjY[i].GetRMSError()*ProjY[i].GetRMSError())    ;
			//std::cout<<"weight="<<weight[i]<<endl;
			
			num +=  ((ProjY[i].GetRMS()) * weight[i] ) ;	
			den += weight[i];
			
			meanRMS +=  ProjY[i].GetRMS();
		}
		
	}
	
	cout<<" num  "<<meanRMS<<endl;
	cout<<" den  "<<den<<endl;
	double RMS = num/den ;
	
	TCanvas* canvas3 = new TCanvas("canvas3", "MEAN", 500, 500);
	canvas3->cd();
	hMean->SetMarkerColor(kBlue);
	//TF1  *fun1 = new TF1("fun1","(1-exp((-1/x)*[0]))",0,NBins) ; 
	TF1  *fun1 = new TF1("fun1"," [0]*x + [1]",0,NBins) ; 
	
	TF1  *fun1 = new TF1("fun1","[0]*(1-exp(x/[1]))",0,NBins) ; 
/*	fun1->SetParameter(0,2);
	fun1->SetParameter(1,1);
    fun1->SetParameter(2,-2);*/

	hMean->Fit("fun1","N0","E",0,NBins);
	cout<<" chi1 "<<fun1->GetChisquare()<<endl;
	hMean->Draw("pe");
	fun1->SetParameter(0,fun1->GetParameter(0));
	fun1->SetParameter(1,fun1->GetParameter(1));
	//fun1->SetParameter(2,fun1->GetParameter(2));
	
	fun1->SetLineColor(kBlue); 
	fun1->Draw("same");
	hMean->GetYaxis()->SetTitle("<Tau Neutral Isolation>");

	TCanvas* canvas4 = new TCanvas("canvas4", "RMS", 500, 500);
	canvas4->cd();
	hRMS->SetMarkerColor(kMagenta);
	hRMS->Draw("pe");
	hRMS->GetXaxis()->SetRangeUser(0,70);
	TF1  *fun2 = new TF1("fun2"," [0]*x + [1]",0,NBins) ; 
	hRMS->Fit("fun2","RN0","E",0,NBins);
	hRMS->Draw("pe");
	fun2->SetParameter(0,fun2->GetParameter(0));
	fun2->SetParameter(1,fun2->GetParameter(1));
	
	fun2->SetLineColor(kMagenta); 
	fun2->Draw("same");

	hRMS->GetYaxis()->SetTitle("RMS(P_{T}^{#gamma}) [GeV]");
	hRMS->GetXaxis()->SetTitle("N_{vtx}");
	
		
	std::cout<<"  Slope  "<<fun1->GetParameter(0)<<endl;
	std::cout<<"  Offset "<<fun1->GetParameter(1)<<endl;
	std::cout<<"  RMS    "<<RMS<<endl;

	canvas3->SaveAs("PlotNota/Mean20.pdf");
	canvas4->SaveAs("PlotNota/RMS20.pdf");
	
	
	
	TFile fout("fPU40.root","recreate"); 
	hMean->Write("MeanNeIso");
	hRMS->Write("RMS");
		
	fout.Close();
	
}

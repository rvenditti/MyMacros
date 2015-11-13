#include <TH1>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <TMath>

//hTau_RhoVsNeutralIso
//hTau_RhoNeutralVsNeutralIso
//hTau_NeIsoVSpuCorrIso
//hTau_NVtxVSNeIso
//hTau_NVtxVSpuCorrPtSum
//hTau_NVtxVSNeIso
//hTau_NVtxVSpuCorrPtSum
//hTau_puCorrPtSumVSNeIso

Double_t fitf(Double_t *x, Double_t *par)
{
	Double_t fitval =0;
	//if(x<25){
	Double_t arg = 0;
	if (par[2] != 0) arg = -x[0]/par[2];
	fitval = par[0]*(par[1]-TMath::Exp(arg));
	//}
	//else fitval =  par[0]*(par[1]-TMath::Exp(-25/par[2]));
	return fitval;
}


Double_t prova(Double_t *x, Double_t *par)
{
	Double_t fitval =0;
	Double_t arg = 0;
	if(x[0]<25){
	if (par[2] != 0) arg = -x[0]/par[2];
	fitval = par[0]*(par[1]-TMath::Exp(arg));
	}
	else fitval =  par[0]*(par[1]-TMath::Exp(-25/par[2]));
	return fitval;
	


}




void FitExp(string inputfile="histo_file_HToTauTau_13TeV_Fall13dr_PU40bx250.root", TString histoName = "hTau_NeIsoVSpuCorrIso_HE" ){
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

	double weight[50];
	
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

	hMean->GetYaxis()->Set(10,0,50);
	//hMean->Rebin(10);
	//hMean->GetXaxis()->SetLimits(0,50);
	
	TF1  *fun1 = new TF1("fun1"," [0]*x + [1]",0,50) ; 
	hMean->Fit("fun1","N0","E",0,50);
	
	fun1->SetParameter(0,fun1->GetParameter(0));
	fun1->SetParameter(1,fun1->GetParameter(1));
	
	

	
//	TF1 *fun1 = new TF1("fitf",fitf,0,25,3);
//	fun1->SetParameters(10,3,8);
//	hMean->Fit(fun1,"N0R","E",0,25);
	
	cout<<" ************chi2******************* "<<fun1->GetChisquare()<<endl;
	hMean->Draw("pe");
	
	//TF1 *fun3 = new TF1("fitf",fitf,0,50,3);
	
	
//	fun3->SetParameter(2,fun1->GetParameter(2));
	
	fun1->SetLineColor(kBlue); 
	fun1->Draw("same");
	
	TF1 *fun4 = new TF1("prova",prova,0,50,3);
	
	
	fun4->SetParameter(0,fun1->GetParameter(0));
	fun4->SetParameter(1,fun1->GetParameter(1));
	fun4->SetParameter(2,fun1->GetParameter(2));
  //  fun4->Draw("same");
	
	hMean->GetYaxis()->SetTitle("<P_{T}^{#gamma}> [GeV]");
	hMean->GetXaxis()->SetTitle("P_{T}^{charged} (d_{z} > 0.2 cm) [GeV]");

	TCanvas* canvas4 = new TCanvas("canvas4", "RMS", 500, 500);
	canvas4->cd();
	hRMS->SetMarkerColor(kMagenta);
	hRMS->Draw("pe");
	//hRMS->Rebin(10);
	//hRMS->GetXaxis()->SetLimits(0,50);
	TF1  *fun2 = new TF1("fun2"," [0]*x + [1]",0,NBins) ; 
	hRMS->Fit("fun2","RN0","E",0,NBins);
	hRMS->Draw("pe");
	fun2->SetParameter(0,fun2->GetParameter(0));
	fun2->SetParameter(1,fun2->GetParameter(1));
	
	fun2->SetLineColor(kMagenta); 
	fun2->Draw("same");

	hRMS->GetYaxis()->SetTitle("RMS(P_{T}^{#gamma}) [GeV]");
	hRMS->GetXaxis()->SetTitle("P_{T}^{charged} (d_{z} > 0.2 cm) [GeV]");
	
		
	std::cout<<" const  "<<fun1->GetParameter(0)<<endl;
	std::cout<<" coeff  "<<fun1->GetParameter(1)<<endl;
	std::cout<<" exp  "<<fun1->GetParameter(2)<<endl;
	std::cout<<" RMS    "<<RMS<<endl;

	canvas3->SaveAs("NeIsoVSPuIso_Mean40_Endcap.pdf");
	canvas4->SaveAs("NeIsoVSPuIso_RMS40_Endcap.pdf");
	
	
	
	TFile fout("fPU40.root","recreate"); 
	hMean->Write("MeanNeIso");
	hRMS->Write("RMS");
		
	fout.Close();
	
}

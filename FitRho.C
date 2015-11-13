#include <TH1>
#include <sstream>
#include <string>
#include <iostream>

void FitRho(){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();


  ////////////////////////////////////////////////////////////////////////////
  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
  TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");

  gStyle->SetOptStat(0000000);
 
	/////////////////////////////////////////////////////////////////////////Rho e rho neutral th1//////////////////////////////////////////////////////////////////////////////////////////////////////
	TCanvas* canvas1 = new TCanvas("canvas1", "canvas1", 1400, 700);
	canvas1->Divide(2,1);
	TH1F* hTau_Rho_PU20 = (TH1F*)f1->Get("hTau_Rho");
	TH1F* hTau_Rho_PU40 = (TH1F*)f2->Get("hTau_Rho");
	
	TH1F* hTau_RhoNeutral_PU20 = (TH1F*)f1->Get("hTau_RhoNeutral");
	TH1F* hTau_RhoNeutral_PU40 = (TH1F*)f2->Get("hTau_RhoNeutral");
	canvas1->cd(1);
	hTau_Rho_PU20->SetLineColor(kMagenta);
	hTau_Rho_PU40->SetLineColor(kBlue);
	hTau_Rho_PU20->Draw("HISTES");
	hTau_Rho_PU40->Draw("HISTESAMES");
	hTau_Rho_PU20->GetXaxis()->SetTitle("#rho [GeV]");
	canvas1->cd(2);
	hTau_RhoNeutral_PU20->SetLineColor(kMagenta);
	hTau_RhoNeutral_PU40->SetLineColor(kBlue);
	hTau_RhoNeutral_PU20->Draw("HISTES");
	hTau_RhoNeutral_PU40->Draw("HISTESAMES");
	hTau_RhoNeutral_PU20->GetXaxis()->SetTitle("#rho^{Neutral} [GeV]");
	
	TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(hTau_RhoNeutral_PU20, "Fall13, 13 TeV, PU20, bx25");
	legend->AddEntry(hTau_RhoNeutral_PU40, "Fall13, 13 TeV, PU40, bx25");
	canvas1->cd(2);
	legend->Draw("same");
	
///////////////////////////////////////////////prendo th2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TH2F* hTau_RhoVSNeIso_PU20 = (TH2F*)f1->Get("hTau_RhoVsNeutralIso");
	TH2F* hTau_RhoVSNeIso_PU40 = (TH2F*)f2->Get("hTau_RhoVsNeutralIso");

	TH2F* hTau_RhoNeVSNeIso_PU20 = (TH2F*)f1->Get("hTau_RhoNeutralVsNeutralIso");
	TH2F* hTau_RhoNeVSNeIso_PU40 = (TH2F*)f2->Get("hTau_RhoNeutralVsNeutralIso");

	
//////////////////////////////////////////////////////////////////canvas scatter rho vs iso neutral///////////////////////////////////////////////////////////////////////////////////////////////////	
	TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 1400, 700);
	canvas2->Divide(2,2);
	canvas2->cd(1);
	hTau_RhoVSNeIso_PU20->GetYaxis()->SetTitle("Iso^{Neutral} [GeV]");
	hTau_RhoVSNeIso_PU20->GetXaxis()->SetTitle("#rho [GeV]");
	hTau_RhoVSNeIso_PU20->Draw("COLZ");
	cout<<"PU20: correlation factor RhoVSNeIso "<<hTau_RhoVSNeIso_PU20->GetCorrelationFactor()<<endl;
	canvas2->cd(2);
	hTau_RhoVSNeIso_PU40->GetYaxis()->SetTitle("Iso^{Neutral} [GeV]");
	hTau_RhoVSNeIso_PU40->GetXaxis()->SetTitle("#rho [GeV]");
	hTau_RhoVSNeIso_PU40->Draw("COLZ");
	cout<<"PU40: correlation factor RhoVSNeIso "<<hTau_RhoVSNeIso_PU40->GetCorrelationFactor()<<endl;
	canvas2->cd(3);
	hTau_RhoNeVSNeIso_PU20->GetYaxis()->SetTitle("Iso^{Neutral} [GeV]");
	hTau_RhoNeVSNeIso_PU20->GetXaxis()->SetTitle("#rho^{Neutral} [GeV]");
	hTau_RhoNeVSNeIso_PU20->Draw("COLZ");
	cout<<"PU20: correlation factor RhoNeVSNeIso "<<hTau_RhoNeVSNeIso_PU20->GetCorrelationFactor()<<endl;
	canvas2->cd(4);
	hTau_RhoNeVSNeIso_PU40->GetYaxis()->SetTitle("Iso^{Neutral} [GeV]");
	hTau_RhoNeVSNeIso_PU40->GetXaxis()->SetTitle("#rho^{Neutral} [GeV]");
	hTau_RhoNeVSNeIso_PU40->Draw("COLZ");
	cout<<"PU40: correlation factor RhoNeVSNeIso "<<hTau_RhoNeVSNeIso_PU40->GetCorrelationFactor()<<endl;
	canvas2->SaveAs("ScatterRho.png");

///////////////////////////////////////////////////////////////////////////////Fit//////////////////////////////////////////////////////////////////////////////////////
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 1400, 700);
	canvas->Divide(2,1);
	canvas->cd(1);
	hTau_RhoVSNeIso_PU20->ProfileX("prof_Rho20",0,80);
	hTau_RhoVSNeIso_PU40->ProfileX("prof_Rho40",0,80);

	
	
	prof_Rho40->SetMarkerStyle(20);
	prof_Rho20->SetMarkerStyle(20);

	prof_Rho40->SetMarkerColor(kBlue);
	prof_Rho20->SetMarkerColor(kMagenta);	

	
	prof_Rho40->GetXaxis()->SetTitle("#rho [GeV]");
	prof_Rho40->GetYaxis()->SetTitle("Iso Neutral [GeV]");
	prof_Rho40->GetYaxis()->SetTitleSize(0.05);
	prof_Rho40->Draw();
	prof_Rho20->Draw("SAME");
	

	
	TF1  *fun_RHO_PU40 = new TF1("fun_RHO_PU40"," [0]*x + [1]",0,80) ; 
	TF1  *fun_RHO_PU20 = new TF1("fun_RHO_PU20"," [0]*x + [1]",0,80) ; 

	cout<<" ************************************************************ fit ch iso pu40  ************************************************************"<<endl;
	prof_Rho40->Fit("fun_RHO_PU40","N0");
	//cout<<" charged, pu40 slope="<<fun_CH_PU40->GetParameter(0)<<" err="<<fun_CH_PU40->GetParError(0)<<" offset="<<fun_CH_PU40->GetParameter(1)<<" err="<<fun_CH_PU40->GetParError(1)<<endl;
	cout<<"************************************************************  fit ch iso pu20  ************************************************************"<<endl;
	prof_Rho20->Fit("fun_RHO_PU20","N0");
	//cout<<" charged, pu40 slope="<<fun_CH_PU20->GetParameter(0)<<" err="<<fun_CH_PU20->GetParError(0)<<" offset="<<fun_CH_PU20->GetParameter(1)<<" err="<<fun_CH_PU20->GetParError(1)<<endl;
	cout<<"************************************************************  fit ch iso 8tev  ************************************************************"<<endl;
		
	fun_RHO_PU40->SetParameter(0,fun_RHO_PU40->GetParameter(0));
	fun_RHO_PU40->SetParameter(1,fun_RHO_PU40->GetParameter(1));
	
	fun_RHO_PU20->SetParameter(0,fun_RHO_PU20->GetParameter(0));
	fun_RHO_PU20->SetParameter(1,fun_RHO_PU20->GetParameter(1));
	
	fun_RHO_PU20 ->SetLineColor(kMagenta); fun_RHO_PU20->Draw("same");
	fun_RHO_PU40 ->SetLineColor(kBlue); fun_RHO_PU40->Draw("same");
	
	
	
	canvas->cd(2);
	hTau_RhoNeVSNeIso_PU20->ProfileX("prof1", 0,50);
	hTau_RhoNeVSNeIso_PU40->ProfileX("prof2", 0,50);

	
	prof1->SetMarkerStyle(20);
	prof2->SetMarkerStyle(20);
		
	prof1->SetMarkerColor(kMagenta);
	prof2->SetMarkerColor(kBlue);
	
	prof2->GetXaxis()->SetTitle("#rho^{Neutral} [GeV]");
	prof2->GetYaxis()->SetTitle("Iso Neutral [GeV]");
	prof2->GetYaxis()->SetTitleSize(0.05);
	
	prof2->Draw();
	prof1->Draw("SAME"); 
	
	
	TF1  *funPU40 = new TF1("funPU40"," [0]*x + [1]",0,50) ; 
	TF1  *funPU20 = new TF1("funPU20"," [0]*x + [1]",0,50) ; 
	
	cout<<" ************************************************************ fit RhoNeutral pu40  ************************************************************"<<endl;
	prof2->Fit("funPU40","N0");
	cout<<" ************************************************************ fit RhoNeutral pu20  ************************************************************"<<endl;
	prof1->Fit("funPU20","N0");
	
	funPU40->SetParameter(0,funPU40->GetParameter(0));
	funPU40->SetParameter(1,funPU40->GetParameter(1));
	
	funPU20->SetParameter(0,funPU20->GetParameter(0));
	funPU20->SetParameter(1,funPU20->GetParameter(1));
	
	funPU20 ->SetLineColor(kMagenta); funPU20->Draw("same");
	funPU40 ->SetLineColor(kBlue); funPU40->Draw("same");

	TLegend* legend = new TLegend( 0.4, 0.15, 0.88, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(funPU20, "Fall13, 13 TeV, PU20, bx25","l");
	legend->AddEntry(funPU40, "Fall13, 13 TeV, PU40, bx25","l");
	canvas->cd(2);
	legend->Draw("same");
	
	double k=3.14*(0.5)*(0.5);
	cout<<"  rho slope;  offset"<<endl;
	cout<<setprecision(3)<<"  pu40;"<<fun_RHO_PU40->GetParameter(0)<<" ± "<<fun_RHO_PU40->GetParError(0)<<"; offset;"<<fun_RHO_PU40->GetParameter(1)<<"  ± "<<fun_RHO_PU40->GetParError(1)<<endl;
	cout<<"  pu20;"<<fun_RHO_PU20->GetParameter(0)<<" ± "<<fun_RHO_PU20->GetParError(0)<<"; offset;"<<fun_RHO_PU20->GetParameter(1)<<"  ± "<<fun_RHO_PU20->GetParError(1)<<endl;

	cout<<" effective area rho pu40 "<<(fun_RHO_PU40->GetParameter(0))/k<<endl;
	cout<<" effective area rho pu20 "<<(fun_RHO_PU20->GetParameter(0))/k<<endl;
	
	cout<<" rho neutral slope;  offset"<<endl;
	cout<<" pu40 slope;"<<funPU40->GetParameter(0)<<" ± "<<funPU40->GetParError(0)<<"; offset;"<<funPU40->GetParameter(1)<<" ± "<<funPU40->GetParError(1)<<endl;
	cout<<" pu20 slope;"<<funPU20->GetParameter(0)<<" ± "<<funPU20->GetParError(0)<<"; offset;"<<funPU20->GetParameter(1)<<" ±"<<funPU20->GetParError(1)<<endl;
	
	cout<<" effective area rhoNeutral pu40 "<<(funPU40->GetParameter(0))/k<<endl;
	cout<<" effective area rhoNeutral pu20 "<<(funPU20->GetParameter(0))/k<<endl;
	
		////////////////////NEW ISO/////////////////////////////////////////////        
	
	
    TH1D *ProjYNeIso20[80]; TH1D *ProjYNeIso40[80];
	TH1D *ProjYNeIsoRhoNe20[80]; TH1D *ProjYNeIsoRhoNe40[80];
	float media =0; float media20 =0;
	float pesi =0; float pesi20	=0; 
	TH1F *hMeanNeIsoPU20 = new TH1F("hMeanNeIsoPU20","hMeanNeIsoPU20",80,0,80);
	TH1F *hMeanNeIsoPU40 = new TH1F("hMeanNeIsoPU40","hMeanNeIsoPU40",80,0,80);
	
	TH1F *hRMSNeIsoPU20 = new TH1F("hRMSNeIsoPU20","hRMSNeIsoPU20",80,0,80);
	TH1F *hRMSNeIsoPU40 = new TH1F("hRMSNeIsoPU40","hRMSNeIsoPU40",80,0,80);
	
	TH1F *hMeanRhoNeIsoPU20 = new TH1F("hMeanRhoNeIsoPU20","hMeanRhoNeIsoPU20",80,0,80);
	TH1F *hMeanRhoNeIsoPU40 = new TH1F("hMeanRhoNeIsoPU40","hMeanRhoNeIsoPU40",80,0,80);

	
	TH1F *hRMSRhoNeIsoPU20 = new TH1F("hRMSRhoNeIsoPU20","hRMSRhoNeIsoPU20",80,0,80);
	TH1F *hRMSRhoNeIsoPU40 = new TH1F("hRMSRhoNeIsoPU40","hRMSRhoNeIsoPU40",80,0,80);
	std::vector<double> RMSPU20;
	double meanRMSRhopu20 =0;
	double meanRMSRhoNepu20 =0;
	double meanRMSRhopu40 =0;
	double meanRMSRhoNepu40 =0;
	for(int i=0;i<80;++i){
	
	    ProjYNeIso20[i] = hTau_RhoVSNeIso_PU20->ProjectionY("ProjYNeIso", i, i+1); 
		ProjYNeIsoRhoNe20[i] = hTau_RhoNeVSNeIso_PU20->ProjectionY("ProjYRhoNeIso", i, i+1); 
		if(  (ProjYNeIso20[i]->GetEntries() > 100)) {
		cout<<"PU 20: rho="<<i<<" media  "<<ProjYNeIso20[i]->GetMean()<<" RMS  "<<ProjYNeIso20[i]->GetRMS()<<" entries "<<ProjYNeIso20[i]->GetEntries()<<endl;
		media20 += (ProjYNeIso20[i]->GetRMS())/(1/(ProjYNeIso20[i]->GetEntries())*(ProjYNeIso20[i]->GetEntries()));
	    pesi20 += 1/(ProjYNeIso20[i]->GetEntries())*(ProjYNeIso20[i]->GetEntries()) ;
		hMeanNeIsoPU20->SetBinContent(i,ProjYNeIso20[i]->GetMean());
		hMeanNeIsoPU20->SetBinError(i,ProjYNeIso20[i]->GetMeanError());
		
		hRMSNeIsoPU20->SetBinContent(i,ProjYNeIso20[i]->GetRMS());
		hRMSNeIsoPU20->SetBinError(i, ProjYNeIso20[i]->GetRMSError());
			
		meanRMSRhopu20 +=	ProjYNeIso20[i]->GetRMS();	
		double rmspu20 = ProjYNeIsoRhoNe20[i]->GetRMS();
		RMSPU20.push_back(rmspu20);
		}
		
		if(ProjYNeIsoRhoNe20[i]->GetEntries() > 100)) {
			hRMSRhoNeIsoPU20->SetBinContent(i,ProjYNeIsoRhoNe20[i]->GetRMS());
			hRMSRhoNeIsoPU20->SetBinError(i, ProjYNeIsoRhoNe20[i]->GetRMSError() ) ;
			//hRMSRhoNeIsoPU20->SetBinError(i,1/TMath::Sqrt(ProjYNeIsoRhoNe20[i]->GetEntries()) );
			
			
			meanRMSRhoNepu20 +=	ProjYNeIsoRhoNe20[i] ->GetRMS();
			
			hMeanRhoNeIsoPU20->SetBinContent(i,ProjYNeIsoRhoNe20[i]->GetMean());
			hMeanRhoNeIsoPU20->SetBinError(i,ProjYNeIsoRhoNe20[i]->GetMeanError());
		}
		//cout<<" size  "<<RMSPU20.size()<<endl ;
	
	}
	std::cout<<" mean RMS Rho Neutral pu20  "<<meanRMSRhoNepu20/21<<endl;
	std::cout<<" mean RMS Rho pu20  "<<meanRMSRhopu20/37<<endl;
	
	std::vector<double> RMSPU40;
	std::vector<double> RMSPU40RhoNe;
	
	for(int i=0;i<80;++i){
        ProjYNeIsoRhoNe40[i]= hTau_RhoNeVSNeIso_PU40->ProjectionY("ProjYNeIso40", i, i+1); 
		ProjYNeIso40[i] = hTau_RhoVSNeIso_PU40->ProjectionY("ProjYRhoNeIso40", i, i+1); 
		if( ProjYNeIso40[i]->GetEntries() > 100) {
	
		//cout<<" PU 40: NVTX="<<i<<" media  "<<ProjYNeIso40[i]->GetMean()<<" RMS  "<<ProjYNeIso40[i]->GetRMS()<<" entries "<<ProjYNeIso40[i]->GetEntries()<<endl;
		media += (ProjYNeIso40[i]->GetRMS())/(1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries()));
		//pesi +=  (1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries())) ;
		hMeanNeIsoPU40->SetBinContent(i,ProjYNeIso40[i]->GetMean());
		hMeanNeIsoPU40->SetBinError(i, ProjYNeIso40[i]->GetMeanError());
	    hRMSNeIsoPU40->SetBinContent(i, ProjYNeIso40[i]->GetRMS());
		hRMSNeIsoPU40->SetBinError(i, ProjYNeIso40[i]->GetRMSError());
		   
		meanRMSRhopu40 +=	ProjYNeIso40[i]->GetRMS();	
		RMSPU40.push_back(ProjYNeIso40[i]->GetRMS());
		
		   }
		
		//   cout<<" size  "<<RMSPU40.size()<<endl ;
		   
		if(ProjYNeIsoRhoNe40[i]->GetEntries() > 100)) {
			hRMSRhoNeIsoPU40->SetBinContent(i,ProjYNeIsoRhoNe40[i]->GetRMS());
			hRMSRhoNeIsoPU40->SetBinError(i, ProjYNeIsoRhoNe40[i]->GetRMSError());
			
			hMeanRhoNeIsoPU40->SetBinContent(i,ProjYNeIsoRhoNe40[i]->GetMean());
			hMeanRhoNeIsoPU40->SetBinError(i, ProjYNeIsoRhoNe40[i]->GetMeanError());
			
			
			meanRMSRhoNepu40 +=	hRMSRhoNeIsoPU40->GetRMS();	
			RMSPU40RhoNe.push_back(hRMSRhoNeIsoPU40->GetRMS());
		}
		
	}
	//cout<<" size  "<<RMSPU40RhoNe.size()<<endl ;
	std::cout<<" mean RMS Rho pu40  "<<meanRMSRhopu40/54<<endl;
	std::cout<<" mean RMS Rho Neutral pu40  "<<meanRMSRhopu20/29<<endl;
	
	TCanvas* canvas3 = new TCanvas("canvas3", "canvas3", 1600, 900);
	canvas3->Divide(2,2);
	canvas3->cd(1);
	hMeanNeIsoPU20->SetMarkerColor(kMagenta);
//	hMeanNeIsoPU20->Fit("pol1");
	hMeanNeIsoPU40->SetMarkerColor(kBlue);
	//hMeanNeIsoPU40->Fit("pol1");
	hMeanNeIsoPU40->Draw("pe");
	hMeanNeIsoPU20->Draw("pesame");

	TF1  *fun1 = new TF1("fun1"," [0]*x + [1]",0,80) ; 
	hMeanNeIsoPU40->Fit("fun1","N0Q","E",0,80);
	fun1->SetParameter(0,fun1->GetParameter(0));
	fun1->SetParameter(1,fun1->GetParameter(1));
	fun1->SetLineColor(kBlue); 
	fun1->Draw("same");
	
	TF1  *fun2 = new TF1("fun2"," [0]*x + [1]",0,80) ; 
	hMeanNeIsoPU20->Fit("fun2","N0Q","E",0,80);
	fun2->SetParameter(0,fun2->GetParameter(0));
	fun2->SetParameter(1,fun2->GetParameter(1));
	fun2->SetLineColor(kMagenta); 
	fun2->Draw("same");


	hMeanNeIsoPU40->GetXaxis()->SetTitle("#rho [GeV]");
	hMeanNeIsoPU40->GetYaxis()->SetTitle("<P_{T}^{#gamma}> [GeV]");
	canvas3->cd(2);
	hRMSNeIsoPU20->SetMarkerColor(kMagenta);
	hRMSNeIsoPU40->SetMarkerColor(kBlue);
	
	TF1  *fun3 = new TF1("fun3"," [0]*x + [1]",0,80) ; 
	hRMSNeIsoPU40->Fit("fun3","N0Q","E",0,80);
	fun3->SetParameter(0,fun3->GetParameter(0));
	fun3->SetParameter(1,fun3->GetParameter(1));
	fun3->SetLineColor(kBlue); 

	
	TF1  *fun4 = new TF1("fun4"," [0]*x + [1]",0,80) ; 
	hRMSNeIsoPU20->Fit("fun4","N0Q","E",0,80);
	fun4->SetParameter(0,fun4->GetParameter(0));
	fun4->SetParameter(1,fun4->GetParameter(1));
	fun4->SetLineColor(kMagenta); 
	hRMSNeIsoPU40->Draw("pe");
	hRMSNeIsoPU20->Draw("peSAME");
	fun3->Draw("same");
	fun4->Draw("same");
	hRMSNeIsoPU40->GetXaxis()->SetTitle("#rho [GeV]");
	hRMSNeIsoPU40->GetYaxis()->SetTitle("RMS(P_{T}^{#gamma}) [GeV]");
	
	canvas3->cd(3);
	hMeanRhoNeIsoPU20->SetMarkerColor(kMagenta);
	hMeanRhoNeIsoPU40->SetMarkerColor(kBlue);
	hMeanRhoNeIsoPU40->Draw("pe");
	hMeanRhoNeIsoPU20->Draw("pesame");
	
	TF1  *fun5 = new TF1("fun5"," [0]*x + [1]",0,80) ; 
	hMeanRhoNeIsoPU40->Fit("fun5","N0Q","E",0,80);
	fun5->SetParameter(0,fun5->GetParameter(0));
	fun5->SetParameter(1,fun5->GetParameter(1));
	fun5->SetLineColor(kBlue); 
	fun5->Draw("same");
	
	TF1  *fun6 = new TF1("fun6"," [0]*x + [1]",0,80) ; 
	hMeanRhoNeIsoPU20->Fit("fun6","N0Q","E",0,80);
	fun6->SetParameter(0,fun6->GetParameter(0));
	fun6->SetParameter(1,fun6->GetParameter(1));
	fun6->SetLineColor(kMagenta); 
	fun6->Draw("same");
	
	hMeanRhoNeIsoPU40->GetXaxis()->SetTitle("#rho^{neutral} [GeV]");
	hMeanRhoNeIsoPU40->GetYaxis()->SetTitle("<P_{T}^{#gamma}> [GeV]");
	
	canvas3->cd(4);
	hRMSRhoNeIsoPU20->SetMarkerColor(kMagenta);
	hRMSRhoNeIsoPU40->SetMarkerColor(kBlue);
	hRMSRhoNeIsoPU40->Draw("pe");
	hRMSRhoNeIsoPU20->Draw("peSAME");
	
	
	TF1  *fun7 = new TF1("fun7"," [0]*x + [1]",0,80) ; 
	hRMSRhoNeIsoPU40->Fit("fun7","N0Q","E",0,80);
	fun7->SetParameter(0,fun7->GetParameter(0));
	fun7->SetParameter(1,fun7->GetParameter(1));
	fun7->SetLineColor(kBlue); 
	fun7->Draw("same");
	
	TF1  *fun8 = new TF1("fun8"," [0]*x + [1]",0,80) ; 
	hRMSRhoNeIsoPU20->Fit("fun8","N0Q","E",0,80);
	fun8->SetParameter(0,fun8->GetParameter(0));
	fun8->SetParameter(1,fun8->GetParameter(1));
	fun8->SetLineColor(kMagenta); 
	fun8->Draw("same");
	
	
	hRMSRhoNeIsoPU40->GetXaxis()->SetTitle("#rho^{neutral} [GeV]");
	hRMSRhoNeIsoPU40->GetYaxis()->SetTitle("RMS(P_{T}^{#gamma}) [GeV]");
	
	
	
	TLegend* legend = new TLegend( 0.3, 0.15, 0.8, 0.35);
	legend->SetTextSize(0.05);
	legend->SetFillColor(0);
	legend->AddEntry(funPU20, "Fall13, 13 TeV, PU20, bx25","l");
	legend->AddEntry(funPU40, "Fall13, 13 TeV, PU40, bx25","l");
	canvas3->cd(4);
	legend->Draw("same");
	
	
	TCanvas* canvas4 = new TCanvas("canvas4", "canvas4", 1400, 700);
	canvas4->Divide(2,1);
	canvas4->cd(1);
	TH3F* hTau_rhoPUVSNeIso_PU20 = (TH3F*)f1->Get("hTau_rhoPUVSNeIso");
	hTau_rhoPUVSNeIso_PU20 ->Draw("COLZ");
	canvas4->cd(2);
	TH3F* hTau_rhoPUVSNeIso_PU40 = (TH3F*)f2->Get("hTau_rhoPUVSNeIso");
	hTau_rhoPUVSNeIso_PU40 ->Draw("LEGO");
	
	
	
	//cout<<" rms medio  pu 40 ="<<media/pesi<<endl;
//	cout<<" RMS medio  pu 20 ="<<media20/pesi20<<endl;
	
	
	
	
	
	
	
}

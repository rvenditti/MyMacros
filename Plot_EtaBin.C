#include <TH1>
#include <sstream>
#include <string>
#include <iostream>
#include< vector >   
using namespace std;

void Plot_EtaBin(){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();


  ////////////////////////////////////////////////////////////////////////////
	
  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
  TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");


	TH2F* hIsoChVSPV_PU20[12]; TH2F* hIsoNeVSPV_PU20[12]; TH2F* hIsoPUVSPV_PU20[12]; TH2F* hNVtx_PU20[12];
	TH2F* hIsoChVSPV_PU40[12]; TH2F* hIsoNeVSPV_PU40[12]; TH2F* hIsoPUVSPV_PU40[12]; TH2F* hNVtx_PU40[12];

	TH1D* PProfIsoCh_PU20[12]; TH1D* ProfIsoNe_PU20[12]; TH1D* ProfIsoPU_PU20[12]; TH1D* ProfNvtx_PU20[12];
	TH1D* PProfIsoCh_PU40[12]; TH1D* ProfIsoNe_PU40[12]; TH1D* ProfIsoPU_PU40[12]; TH1D* ProfNvtx_PU40[12];
	TH1D* ProjectionYNeutral20[12];
	
	TCanvas* CanvVector[12]; TCanvas* CanvNeVector[12]; TCanvas* CanvPUVector[12]; TCanvas* CanvVtxVector[12];
	TCanvas* CanvVector40[12]; TCanvas* CanvNeVector40[12]; TCanvas* CanvPUVector40[12]; TCanvas* CanvVtxVector40[12];
	
	TF1* fun_Ch20[12];  TF1* fun_Ne20[12];  TF1* fun_PU20[12]; 
	TF1* fun_Ch40[12];  TF1* fun_Ne40[12];  TF1* fun_PU40[12]; 
	float Ne_slope[12], Ne_slopeX[12], ex[12], ey[12], Ne_offset[12], Ne_offsetErr[12], PU_slopeErr[12], PU_slope[12];
	float Ne_slope40[12], Ne_slopeErr40[12], Ne_offset40[12], Ne_offsetErr40[12], PU_slopeErr40[12], PU_slope40[12];

	float DeltaBetaPU20[12], DeltaBetaPU20[40] ;
	float	RMS_PU20[12], sum20[12] , pesi20[12] ; 
	float	RMS_PU40[12], sum40[12] , pesi40[12] , RMS_PU40_err[12], error_sum40[12] ;
	
	TH1F* hDeltaBetaPU20 = new TH1F("hDeltaBetaPU20","hDeltaBetaPU20", 12,0.1,2.4);
	TH1F* hDeltaBetaPU40 = new TH1F("hDeltaBetaPU40","hDeltaBetaPU40", 12,0.1,2.4);
	TH1F* hOffsetPU20 = new TH1F("hOffsetPU20","hOffsetPU20", 12,0.1,2.4);
	TH1F* hOffsetPU40 = new TH1F("hOffsetPU40","hOffsetPU40", 12,0.1,2.4);
	TH1F* hRMS20 =  new TH1F("hRMS20","hRMS20", 12,0.1,2.4);
	TH1F* hRMS40 =  new TH1F("hRMS40","hRMS40", 12,0.1,2.4);
	
	TFitResultPtr ptr[12];

	for (int i = 0; i < 12; i++) {
		TString idch ("hIsoChVSPV");
		idch +=(i+1);
		TString idne ("hIsoNeVSPV");
		idne +=(i+1);
		TString idpu ("hIsoPUVSPV");
		idpu +=(i+1);
		TString idpv ("hNVtx");
		idpv +=(i+1);
		cout<<"********************************* histoname "<<idch<<"  "<<idne<<"*********************************"<< endl;
		hIsoChVSPV_PU20[i] = (TH2F*)f1->Get(idch);
		hIsoNeVSPV_PU20[i] = (TH2F*)f1->Get(idne);
		hIsoPUVSPV_PU20[i] = (TH2F*)f1->Get(idpu);
		hNVTX_PU20[i] = (TH1F*)f1->Get(idpv);
		
		hIsoChVSPV_PU40[i] = (TH2F*)f2->Get(idch);
		hIsoNeVSPV_PU40[i] = (TH2F*)f2->Get(idne);
		hIsoPUVSPV_PU40[i] = (TH2F*)f2->Get(idpu);
		hNVTX_PU40[i] = (TH1F*)f2->Get(idpv);
		
		PProfIsoCh_PU20[i]= hIsoChVSPV_PU20[i]->ProfileX(idch,0,40);
		ProfIsoNe_PU20[i] = hIsoNeVSPV_PU20[i]->ProfileX(idne,0,40);
		ProfIsoPU_PU20[i] = hIsoPUVSPV_PU20[i]->ProfileX(idpu,0,50);
		
	//	ProjectionYNeutral20[1]=hIsoNeVSPV_PU20[1]->ProjectionY("proj1",10,21);
		
		for(int m=0;m<50;++m){
			
			TH1D *ProjYNeIso20[70]; 
	
			ProjYNeIso20[m] = hIsoNeVSPV_PU20[i]->ProjectionY("ProjYNeIso", m, m+1); 
			if( (ProjYNeIso20[m]->GetEntries()) > 100){
				//cout<<"PU 20: NVTX="<<m<<" media  "<<ProjYNeIso20[m]->GetMean()<<" RMS  "<<ProjYNeIso20[m]->GetRMS()<<" entries "<<ProjYNeIso20[m]->GetEntries()<<endl;
				sum20[i] += (ProjYNeIso20[m]->GetRMS())/(1/(ProjYNeIso20[m]->GetEntries())*(ProjYNeIso20[m]->GetEntries()));
				pesi20[i] += 1/(ProjYNeIso20[m]->GetEntries())*(ProjYNeIso20[m]->GetEntries()) ;
				
			}
		}
		RMS_PU20[i]=sum20[i]/pesi20[i] ;

		
		//PProfIsoCh_PU20[i]->SetMarkerStyle(20);
		PProfIsoCh_PU20[i]->SetLineColor(kMagenta);
		ProfIsoNe_PU20[i]->SetLineColor(kGreen);
		ProfIsoPU_PU20[i]->SetLineColor(kBlue);	
				
		CanvVector[i] = new TCanvas("CanvVector ", "CanvVector", 500, 500);
		CanvNeVector[i] =new TCanvas("CanvNeVector ", "CanvNeVector", 500, 500);
		CanvPUVector[i] =new TCanvas("CanvPUVector ", "CanvPUVector", 500, 500);
		CanvVtxVector[i] =new TCanvas("CanvVtxVector", "CanvVtxVector", 500, 500);
		
		CanvVector[i]->cd();
		TString title_ch ("fun_Ch20"); title_ch+=(i+1);
		fun_Ch20[i]= new TF1( title_ch,"[0]*x + [1]",10,50) ;
		PProfIsoCh_PU20[i]->Fit( title_ch,"0R+");
		//ptr[i] =PProfIsoCh_PU20[i] ->Fit(title_ch,"","",10,50);
		//TMatrixDSym mat[2][2];
		//mat =ptr[0]->GetCorrelationMatrix();
		
		//TString title ("|#eta|< "); title +=(i+1)/10;
		fun_Ch20[i]->SetParameter(0,fun_Ch20[i]->GetParameter(0));
		fun_Ch20[i]->SetParameter(1,fun_Ch20[i]->GetParameter(1));
		fun_Ch20[i]->SetLineColor(kMagenta);
		PProfIsoCh_PU20[i]->Draw();
		//PProfIsoCh_PU20[i]->SetTitle(title);
		fun_Ch20[i]->Draw("same");
		CanvVector[i]->SaveAs("./PU20Plot/ChIso/"+idch+".pdf");
		
		/*fitter = TVirtualFitter::GetFitter();
		int nPars = fitter->GetNumberFreeParameters();
		for (int i=0;i<1;i++){
			for (int k=0;k<2;k++){
				
				cout<<i<<" "<<k<<" "<<(fitter->GetCovarianceMatrixElement(i,k)/TMath::Sqrt( (fitter->GetCovarianceMatrixElement(i,i))* (fitter->GetCovarianceMatrixElement(k,k))))<<endl;
			}}	*/
		
		
		
		CanvNeVector[i]->cd();
		TString title_ne ("fun_Ne20"); title_ne+=(i+1);
		fun_Ne20[i]= new TF1( title_ne,"[0]*x + [1]",10,50) ;
		ProfIsoNe_PU20[i]->Fit( title_ne,"0R+");
		ProfIsoNe_PU20[i]->SetTitle(idne);
		fun_Ne20[i]->SetParameter(0,fun_Ne20[i]->GetParameter(0));
		fun_Ne20[i]->SetParameter(1,fun_Ne20[i]->GetParameter(1));
		fun_Ne20[i]->SetLineColor(kGreen);
		ProfIsoNe_PU20[i]->Draw();
		fun_Ne20[i]->Draw("same");
		CanvNeVector[i]->SaveAs("./PU20Plot/NeIso/"+idne+".pdf");
		Ne_slope[i] = fun_Ne20[i]->GetParameter(0);
		Ne_slopeX[i]=2*(i)/10.;
		ex[i]=0.;
		ey[i]= fun_Ne20[i]->GetParError(0);
		
		Ne_offset[i] = fun_Ne20[i]->GetParameter(1);
		Ne_offsetErr[i]= fun_Ne20[i]->GetParError(1);
		
		cout<<" slope ne "<<	Ne_slope[i] << " x "<< Ne_slopeX[i]<<"  error "<<ey[i]<<endl;
		
		CanvPUVector[i]->cd();
		TString title_pu ("fun_PU20"); title_pu+=(i+1);
		fun_PU20[i]= new TF1( title_pu,"[0]*x ",10,50) ;
		ProfIsoPU_PU20[i]->Fit( title_pu,"0R+");
		ProfIsoPU_PU20[i]->SetTitle(idpu);
		fun_PU20[i]->SetParameter(0,fun_PU20[i]->GetParameter(0));
		fun_PU20[i]->SetParameter(1,fun_PU20[i]->GetParameter(1));
		fun_PU20[i]->SetLineColor(kBlue);
		ProfIsoPU_PU20[i]->Draw();
		fun_PU20[i]->Draw("same");
	    CanvPUVector[i]->SaveAs("./PU20Plot/PUIso/"+idpu+".pdf");
		PU_slope[i] = fun_PU20[i]->GetParameter(0);
		PU_slopeErr[i]= fun_PU20[i]->GetParError(0);
		
		DeltaBetaPU20[i]=Ne_slope[i]/PU_slope[i];
		hDeltaBetaPU20->SetBinContent(i, Ne_slope[i]/PU_slope[i] );
		hOffsetPU20->SetBinContent(i,Ne_offset[i]);
		hRMS20->SetBinContent(i,RMS_PU20[i]);
		/////////////////////////////pu40////////////////////////////////////
		
		PProfIsoCh_PU40[i]= hIsoChVSPV_PU40[i]->ProfileX(idch,0,70);
		ProfIsoNe_PU40[i] = hIsoNeVSPV_PU40[i]->ProfileX(idne,0,70);
		ProfIsoPU_PU40[i] = hIsoPUVSPV_PU40[i]->ProfileX(idpu,0,70);
		
		//PProfIsoCh_PU40[i]->SetMarkerStyle(20);
		PProfIsoCh_PU40[i]->SetLineColor(kMagenta);
		ProfIsoNe_PU40[i]->SetLineColor(kGreen);
		ProfIsoPU_PU40[i]->SetLineColor(kBlue);	
		
	   for(int m=0;m<60;++m){
			
			TH1D *ProjYNeIso40[70]; 
			
			ProjYNeIso40[m] =hIsoNeVSPV_PU40[i]->ProjectionY("ProjYNeIso40", m, m+1); 
			if( (ProjYNeIso40[m]->GetEntries()) > 100){
				//cout<<"PU 20: NVTX="<<m<<" media  "<<ProjYNeIso20[m]->GetMean()<<" RMS  "<<ProjYNeIso20[m]->GetRMS()<<" entries "<<ProjYNeIso20[m]->GetEntries()<<endl;
				sum40[i] += (ProjYNeIso40[m]->GetRMS())/(1/(ProjYNeIso40[m]->GetEntries())*(ProjYNeIso40[m]->GetEntries()));
				pesi40[i] += 1/(ProjYNeIso40[m]->GetEntries())*(ProjYNeIso40[m]->GetEntries()) ;
				//error_sum40[i] += (ProjYNeIso40[m]->GetRMSErorr())/(1/(ProjYNeIso40[m]->GetEntries())*(ProjYNeIso40[m]->GetEntries()));
			}
		}
		RMS_PU40[i]=sum40[i]/pesi40[i] ;
		//RMS_PU40_err[i]=error_sum40[i]/pesi40[i] ;
		
		
		CanvVector40[i] = new TCanvas("CanvVector40", "CanvVector40", 500, 500);
		CanvNeVector40[i] =new TCanvas("CanvNeVector40", "CanvNeVector40", 500, 500);
		CanvPUVector40[i] =new TCanvas("CanvPUVector40 ", "CanvPUVector40", 500, 500);
		CanvVtxVector40[i] = new TCanvas("CanvVtxVector40", "CanvVtxVector40", 500, 500);
		
		CanvVector40[i]->cd();
		TString title_ch40 ("fun_Ch40"); title_ch40+=(i+1);
		fun_Ch40[i]= new TF1( title_ch40,"[0]*x + [1]",10,60) ;
		PProfIsoCh_PU40[i]->Fit( title_ch40,"0R+");
		fun_Ch40[i]->SetParameter(0,fun_Ch40[i]->GetParameter(0));
		fun_Ch40[i]->SetParameter(1,fun_Ch40[i]->GetParameter(1));
		fun_Ch40[i]->SetLineColor(kMagenta);
		PProfIsoCh_PU40[i]->Draw();
		fun_Ch40[i]->Draw("same");
		CanvVector40[i]->SaveAs("./PU40Plot/ChIso/"+idch+".pdf");
	
		
		
		CanvNeVector40[i]->cd();
		TString title_ne40 ("fun_Ne40"); title_ne40+=(i+1);
		fun_Ne40[i]= new TF1( title_ne40,"[0]*x + [1]",10,60) ;
		ProfIsoNe_PU40[i]->Fit( title_ne40,"0R+");
		fun_Ne40[i]->SetParameter(0,fun_Ne40[i]->GetParameter(0));
		fun_Ne40[i]->SetParameter(1,fun_Ne40[i]->GetParameter(1));
		fun_Ne40[i]->SetLineColor(kGreen);
		ProfIsoNe_PU40[i]->Draw();
		fun_Ne40[i]->Draw("same");
		Ne_slope40[i] = fun_Ne40[i]->GetParameter(0);
		Ne_slopeErr40[i] = fun_Ne40[i]->GetParError(0);
		Ne_offset40[i] = fun_Ne40[i]->GetParameter(1);
		Ne_offsetErr40[i] = fun_Ne40[i]->GetParError(1);
		CanvNeVector40[i]->SaveAs("./PU40Plot/NeIso/"+idne+".pdf");
		

		
		
		CanvPUVector40[i]->cd();
		TString title_pu40 ("fun_PU40"); title_pu40 +=(i+1);
		fun_PU40[i]= new TF1( title_pu40,"[0]*x ",10,60) ;
		ProfIsoPU_PU40[i]->Fit( title_pu40,"0R+");
		fun_PU40[i]->SetParameter(0,fun_PU40[i]->GetParameter(0));
		fun_PU40[i]->SetParameter(1,fun_PU40[i]->GetParameter(1));
		fun_PU40[i]->SetLineColor(kBlue);
		ProfIsoPU_PU40[i]->Draw();
		fun_PU40[i]->Draw("same");
		PU_slope40[i] = fun_PU40[i]->GetParameter(0);
		PU_slopeErr40[i] = fun_PU40[i]->GetParError(0);

		CanvPUVector40[i]->SaveAs("./PU40Plot/PUIso/"+idpu+".pdf");
		
		gStyle->SetOptStat(1111111);
		CanvVtxVector[i]->cd();
		hNVTX_PU20[i]->Draw();
		CanvVtxVector[i]->SaveAs("./PU20Plot/Vertex/"+idpv+".pdf");
		
		CanvVtxVector40[i]->cd();
		hNVTX_PU40[i]->Draw();
		CanvVtxVector40[i]->SaveAs("./PU40Plot/Vertex/"+idpv+".pdf");
		
		DeltaBetaPU40[i]=Ne_slope40[i]/PU_slope40[i];
		hDeltaBetaPU40->SetBinContent(i,DeltaBetaPU40[i] );
		hOffsetPU40->SetBinContent(i,Ne_offset40[i]);
		hRMS40->SetBinContent(i,RMS_PU40[i]);
		
	}
	
	
	TCanvas *Canv3 = new TCanvas("Canv3","Neutral slope vs eta",900,600);
	gPad->SetGridy(); gPad->SetGridx();
	TGraphErrors* gr_PU20_slope = new TGraphErrors(12,Ne_slopeX, Ne_slope,ex,ey);
	TGraphErrors* gr_PU40_slope = new TGraphErrors(12,Ne_slopeX, Ne_slope40,ex,Ne_slopeErr40);
	gr_PU20_slope->SetLineColor(kMagenta); 
	gr_PU40_slope->SetLineColor(kBlue); 
	gr_PU40_slope->SetTitle(" Neutral Slope ");
	gr_PU40_slope->Draw("ACP");  
	gr_PU20_slope->Draw("CP");  
	gr_PU40_slope->SetMinimum(0);
	gr_PU40_slope->SetMaximum(0.5);
	gr_PU40_slope->GetXaxis()->SetTitle("|#eta|");
	gr_PU40_slope->GetYaxis()->SetTitle("Neutral Iso Slope");
	TLegend* legend = new TLegend( 0.45, 0.55, 0.99, 0.75);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(gr_PU20_slope, "Fall13, 13 TeV, PU20, bx25", "f");
	legend->AddEntry(gr_PU40_slope, "Fall13, 13 TeV, PU40, bx25", "f");
	Canv3->cd();
	legend->Draw("same");
	
	Canv3->SaveAs("NeIsoSlope.pdf");
	
	TCanvas *Canv4 = new TCanvas("Canv4","Neutral offset vs eta",900,600);
	gPad->SetGridy(); gPad->SetGridx();
	TGraphErrors* gr_PU20_offset= new TGraphErrors(12,Ne_slopeX, Ne_offset,ex,Ne_offsetErr);
	TGraphErrors* gr_PU40_offset= new TGraphErrors(12,Ne_slopeX, Ne_offset40,ex,Ne_offsetErr40);
	gr_PU20_offset->SetLineColor(kMagenta); 
	gr_PU40_offset->SetLineColor(kBlue); 
	gr_PU40_offset->SetTitle(" Neutral Offset ");
	gr_PU40_offset->Draw("ACP"); 
	gr_PU20_offset->Draw("CP"); 
	gr_PU40_offset->SetMinimum(0);
	gr_PU40_offset->SetMaximum(8);
	gr_PU40_offset->GetXaxis()->SetTitle("|#eta|");
	gr_PU40_offset->GetYaxis()->SetTitle("Neutral Iso Offset");
	TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(gr_PU20_offset, "Fall13, 13 TeV, PU20, bx25", "f");
	legend->AddEntry(gr_PU40_offset, "Fall13, 13 TeV, PU40, bx25", "f");
	Canv4->cd();
	legend->Draw("same");
	
	Canv4->SaveAs("NeIsoOffset.pdf");
	
	TCanvas *Canv5 = new TCanvas("Canv5","PU SLOPE vs eta",900,600);
	gPad->SetGridy(); gPad->SetGridx();
	TGraphErrors* gr_PU20_puslope= new TGraphErrors(12,Ne_slopeX, PU_slope,ex, PU_slopeErr);
	TGraphErrors* gr_PU40_puslope= new TGraphErrors(12,Ne_slopeX, PU_slope40,ex, PU_slopeErr40);
	gr_PU40_puslope->SetTitle(" PU Slope ");
	gr_PU20_puslope->SetLineColor(kMagenta); 
	gr_PU40_puslope->SetLineColor(kBlue); 
	gr_PU40_puslope->Draw("ACP"); 
	gr_PU20_puslope->Draw("CP"); 
	gr_PU40_puslope->SetMinimum(0.5);
	gr_PU40_puslope->SetMaximum(1);
	gr_PU40_puslope->GetXaxis()->SetTitle("|#eta|");
	gr_PU40_slope->GetYaxis()->SetTitle("PU Iso Slope");
	Canv5->SaveAs("PUIsoSlope.pdf");
	
	
	TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(gr_PU20_puslope, "Fall13, 13 TeV, PU20, bx25", "f");
	legend->AddEntry(gr_PU40_puslope, "Fall13, 13 TeV, PU40, bx25", "f");
	Canv5->cd();
	legend->Draw("same");
	
	TCanvas *Canv6 = new TCanvas("Canv6","rms vs eta",900,600);
	gPad->SetGridy(); gPad->SetGridx();
	TGraphErrors* gr_PU20_rms= new TGraphErrors(12,Ne_slopeX, RMS_PU20,ex, PU_slopeErr);
	TGraphErrors* gr_PU40_rms= new TGraphErrors(12,Ne_slopeX, RMS_PU40,ex, PU_slopeErr40);
	gr_PU40_rms->SetTitle(" RMS Neutral distribution ");
	gr_PU20_rms->SetLineColor(kMagenta); 
	gr_PU40_rms->SetLineColor(kBlue); 
	gr_PU40_rms->Draw("ACP"); 
	gr_PU20_rms->Draw("CP"); 
	gr_PU40_rms->SetMinimum(1);
	gr_PU40_rms->SetMaximum(10);
	gr_PU40_rms->GetXaxis()->SetTitle("|#eta|");
	gr_PU40_rms->GetYaxis()->SetTitle("RMS Neutral distribution");
	Canv6->SaveAs("RMS.pdf");
	
	
	
	   
	TFile f_par("IsoParameters.root","recreate"); 
	
	hDeltaBetaPU20->Write();
	hDeltaBetaPU40->Write();
	
	hOffsetPU20->Write();
	hOffsetPU40->Write();
	hRMS20->Write();
	hRMS40->Write();
	f_par.Close();

	
	
	
	
	
	
	
	
	
	
	
	
	
}

#include <TH1>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

void Fit3D(){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();


  ////////////////////////////////////////////////////////////////////////////
  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
  gStyle->SetOptStat(0000000);
	gStyle->SetOptFit(00111);

	////////////////////////////////////////////////////////////////////////prendo th3//////////////////////////////////////////////////////////////////////////////////////////////////////
	TH3F* hTau_rhoPUVSNeIso_PU20 = (TH3F*)f1->Get("hTau_rhoPUVSNeIso");
	TH3F* hTau_rhoPUVSNeIso_PU40 = (TH3F*)f2->Get("hTau_rhoPUVSNeIso");
	
	TH3F* hTau_rhoNePUVSNeIso_PU20 = (TH3F*)f1->Get("hTau_rhoNePUVSNeIso");
	TH3F* hTau_rhoNePUVSNeIso_PU40 = (TH3F*)f2->Get("hTau_rhoNePUVSNeIso");
	
	TCanvas* canvas5 = new TCanvas("canvas5", "canvas5", 1400, 700);
	canvas5->Divide(2,1);
	canvas5->cd(1);
	TH3F* hTau_rhoPUVSNeIso_PU20 = (TH3F*)f1->Get("hTau_rhoPUVSNeIso");
	hTau_rhoPUVSNeIso_PU20 ->Draw();
	canvas5->cd(2);
	TH3F* hTau_rhoPUVSNeIso_PU40 = (TH3F*)f2->Get("hTau_rhoPUVSNeIso");
	hTau_rhoPUVSNeIso_PU40 ->Draw();
	
	

   ///////////////////////////////////////////////////////////////////////////////Fit//////////////////////////////////////////////////////////////////////////////////////
	
	TH1 *h2;
	hTau_rhoPUVSNeIso_PU20->GetYaxis()->SetRange(0,10);
	hTau_rhoPUVSNeIso_PU20->GetXaxis()->SetRange(0,10);
	h2= hTau_rhoPUVSNeIso_PU20->Project3D("z"); 
	cout<<"mean h2 "<<h2->GetMean()<<endl;
	
		
	TH1 *hIsoNePu20[25]; 
	std::vector<double> MeanPU20;
	std::vector<double> RMSPU20;
	
	TH1 *hIsoNePu40[25]; 
	std::vector<double> MeanPU40;
	std::vector<double> RMSPU40;
	
	
	TH1 *hIsoNePu20_RhoNe[25]; 
	std::vector<double> MeanPU20_RhoNe;
	std::vector<double> RMSPU20_RhoNe;
	
	TH1 *hIsoNePu40_RhoNe[25]; 
	std::vector<double> MeanPU40_RhoNe;
	std::vector<double> RMSPU40_RhoNe;
	
	TH1 *hprova[50]; 
	
    for(int i=0;i<25;++i){
		TString id= "hIsoNePu20_";
		id +=i;
		TString id40= "hIsoNePu40_";
		id40 +=i;
		
		TString idne= "hIsoNePu20RhoNe_";
		idne +=i;
		TString idne40= "hIsoNePu40RhoNe_";
		idne40 +=i;
		
		TString idp= "prova_";
		idp +=i;
		
		hIsoNePu20[i] = new TH1F(id,id ,50,0,50);
		hIsoNePu40[i] = new TH1F(id40,id40 ,50,0,50);
		hIsoNePu20_RhoNe[i] = new TH1F(idne,idne ,50,0,50);
		hIsoNePu40_RhoNe[i] = new TH1F(idne40,idne40 ,50,0,50);
		hprova[i]= new TH1F(idp,idp ,50,0,50);;
	}
	TH2F *hMeanPU20 = new TH2F ("hMeanPU20","hMeanPU20",5,0,50,5,0,50);
	TH2F *hRMSPU20 = new TH2F ("hRMSPU20","hRMSPU20",5,0,50,5,0,50);
	TH2F *hEntriesPU20 = new TH2F ("hEntriesPU20","hEntriesPU20",5,0,50,5,0,50);
	
	TH2F *hMeanPU40 = new TH2F ("hMeanPU40","hMeanPU40",7,0,70,5,0,50);
	TH2F *hRMSPU40 = new TH2F ("hRMSPU40","hRMSPU40",7,0,70,5,0,50);
    TH2F *hEntriesPU40 = new TH2F ("hEntriesPU40","hEntriesPU40",7,0,70,5,0,50);
	
	
	TH2F *hMeanPU20_RhoNe = new TH2F ("hMeanPU20_RhoNe","hMeanPU20_RhoNe",5,0,50,5,0,50);
	TH2F *hRMSPU20_RhoNe = new TH2F ("hRMSPU20_RhoNe","hRMSPU20_RhoNe",5,0,50,5,0,50);
	TH2F *hEntriesPU20_RhoNe = new TH2F ("hEntriesPU20_RhoNe","hEntriesPU20_RhoNe",5,0,50,5,0,50);
	
	TH2F *hMeanPU40_RhoNe = new TH2F ("hMeanPU40_RhoNe","hMeanPU40_RhoNe",7,0,70,5,0,50);
	TH2F *hRMSPU40_RhoNe = new TH2F ("hRMSPU40_RhoNe","hRMSPU40_RhoNe",7,0,70,5,0,50);
    TH2F *hEntriesPU40_RhoNe = new TH2F ("hEntriesPU40_RhoNe","hEntriesPU40_RhoNe",7,0,70,5,0,50);
	
	
	int k=0; 
	for(int i=0;i<5;++i){

		hTau_rhoPUVSNeIso_PU20->GetXaxis()->SetRange(i*10,(i+1)*10);
		hTau_rhoNePUVSNeIso_PU20->GetXaxis()->SetRange(i*10,(i+1)*10);
	
				for(int j=0; j<5;++j){	
					hTau_rhoPUVSNeIso_PU20->GetYaxis()->SetRange(j*10,(j+1)*10);
					hTau_rhoNePUVSNeIso_PU20->GetYaxis()->SetRange(j*10,(j+1)*10);
					k += 1;
					cout<<i<<"  "<<j<<" n "<<k<<endl;
					cout<<"********************X:("<<i*10<<", "<<(i+1)*10<<")"<<"Y:("<<j*10<<", "<<(j+1)*10<<")"<<"mean "<<(hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetMean()<<"  RMS "<<(hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetRMS()<<" Entries "<<(hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetEntries()<<endl;
					double meanpu20 = (hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetMean();
					double rmspu20 = (hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetRMS();
					hMeanPU20->Fill(i*10,j*10,meanpu20);
					hRMSPU20->Fill(i*10,j*10,rmspu20);
					hEntriesPU20->Fill(i*10,j*10, (hTau_rhoPUVSNeIso_PU20->Project3D("z"))->GetEntries())	;
					double meanPU20_RhoNe = (hTau_rhoNePUVSNeIso_PU20->Project3D("z"))->GetMean();
					double rmsPU20_RhoNe = (hTau_rhoNePUVSNeIso_PU20->Project3D("z"))->GetMean();
					hMeanPU20_RhoNe->Fill(i*10,j*10, meanPU20_RhoNe  );
					hRMSPU20_RhoNe->Fill(i*10,j*10, rmsPU20_RhoNe);
					hEntriesPU20_RhoNe->Fill(i*10,j*10, (hTau_rhoNePUVSNeIso_PU20->Project3D("z"))->GetEntries())	;
				//	double x = ( (hTau_rhoNePUVSNeIso_PU20->Project3D("z"))->ProjectionX(""))->GetMean();
					
					}	
	
			}	
	
	
	
	for(int i=0;i<5;++i){
		hTau_rhoPUVSNeIso_PU40->GetXaxis()->SetRange(i*10,(i+1)*10);
		hTau_rhoNePUVSNeIso_PU40->GetXaxis()->SetRange(i*10,(i+1)*10);
		for(int j=0; j<7;++j){	
			hTau_rhoPUVSNeIso_PU40->GetYaxis()->SetRange(j*10,(j+1)*10);
			hTau_rhoNePUVSNeIso_PU40->GetYaxis()->SetRange(j*10,(j+1)*10);
			double meanpu40 = (hTau_rhoPUVSNeIso_PU40->Project3D("z"))->GetMean();
			double rmspu40 = (hTau_rhoPUVSNeIso_PU40->Project3D("z"))->GetRMS();
			hMeanPU40->Fill(i*10,j*10,meanpu40);
			hRMSPU40->Fill(i*10,j*10,rmspu40);
			hEntriesPU40->Fill(i*10,j*10, (hTau_rhoPUVSNeIso_PU40->Project3D("z"))->GetEntries())	;
			
			double meanPU40_RhoNe = (hTau_rhoNePUVSNeIso_PU40->Project3D("z"))->GetMean();
			double rmsPU40_RhoNe = (hTau_rhoNePUVSNeIso_PU40->Project3D("z"))->GetMean();
			
			hMeanPU40_RhoNe->Fill(i*10,j*10, meanPU40_RhoNe);
			hRMSPU40_RhoNe->Fill(i*10,j*10, rmsPU40_RhoNe);
			hEntriesPU40_RhoNe->Fill(i*10,j*10, (hTau_rhoNePUVSNeIso_PU40->Project3D("z"))->GetEntries())	;
			
		}
	}
	
	
	TCanvas* canvas = new TCanvas("canvas", "PU20", 1400, 700);
	canvas->Divide(3,1);
	canvas->cd(1);
	hMeanPU20->Draw("LEGO2");
	hMeanPU20->GetXaxis()->SetTitle("Rho");
	hMeanPU20->GetYaxis()->SetTitle("PU Iso");
	hMeanPU20->SetTitle("Mean Neutral Iso");
	canvas->cd(2);
	//hRMSPU20->SetMarkerStyle(20);
	hRMSPU20->Draw("LEGO2");
	hRMSPU20->GetXaxis()->SetTitle("Rho");
	hRMSPU20->GetYaxis()->SetTitle("PU Iso");
	hRMSPU20->SetTitle("RMS Neutral Iso");
	
	canvas->cd(3);
	hEntriesPU20->Draw("LEGO2");
	hEntriesPU20->GetXaxis()->SetTitle("Rho");
	hEntriesPU20->GetYaxis()->SetTitle("PU Iso");
	hEntriesPU20->SetTitle("Num Entries");
	canvas->SaveAs("./IsoCorr2D/NeIsoVSRhoVSPU_Pu20.pdf");

	
	///////////////////////////////////////RhoPU40/////////////////////////////////////////////////
	TCanvas* canvas2 = new TCanvas("canvas2", "PU40", 1400, 700);
	canvas2->Divide(3,1);
	canvas2->cd(1);
	hMeanPU40->Draw("LEGO2");
	hMeanPU40->GetXaxis()->SetTitle("Rho");
	hMeanPU40->GetYaxis()->SetTitle("PU Iso");
	hMeanPU40->SetTitle("Mean Neutral Iso");
	
	canvas2->cd(2);
	hRMSPU40->Draw("LEGO2");
	hRMSPU40->Draw("LEGO2");
	hRMSPU40->GetXaxis()->SetTitle("Rho");
	hRMSPU40->GetYaxis()->SetTitle("PU Iso");
	hRMSPU40->SetTitle("RMS Neutral Iso");
	
	canvas2->cd(3);
	hEntriesPU40->Draw("LEGO2");
	hEntriesPU40->GetXaxis()->SetTitle("Rho");
	hEntriesPU40->GetYaxis()->SetTitle("PU Iso");
	hEntriesPU40->SetTitle("Num Entries");
	canvas2->SaveAs("./IsoCorr2D/NeIsoVSRhoVSPU_Pu40.pdf");
	///////////////////////////////////////RhoNePU20/////////////////////////////////////////////////
	TCanvas* canvas3 = new TCanvas("canvas3", "RhoNePU20", 1400, 700);
	canvas3->Divide(3,1);
	canvas3->cd(1);
	hMeanPU20_RhoNe->Draw("LEGO2");
	hMeanPU20_RhoNe->GetXaxis()->SetTitle("Rho");
	hMeanPU20_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hMeanPU20_RhoNe->SetTitle("Mean Neutral Iso");
	canvas3->cd(2);
	hRMSPU20_RhoNe->Draw("LEGO2");
	hRMSPU20_RhoNe->GetXaxis()->SetTitle("Rho");
	hRMSPU20_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hRMSPU20_RhoNe->SetTitle("RMS Neutral Iso");
	canvas3->cd(3);
	hEntriesPU20_RhoNe->Draw("LEGO2");
	hEntriesPU20_RhoNe->GetXaxis()->SetTitle("Rho");
	hEntriesPU20_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hEntriesPU20_RhoNe->SetTitle("Num Entries");
	canvas3->SaveAs("./IsoCorr2D/NeIsoVSRhoNeVSPU_Pu20.pdf");
	
	///////////////////////////////////////RhoNePU40/////////////////////////////////////////////////
	TCanvas* canvas4 = new TCanvas("canvas4", "RhoNePU40", 1400, 700);
	canvas4->Divide(3,1);
	canvas4->cd(1);
	hMeanPU40_RhoNe->Draw("LEGO2");
	hMeanPU40_RhoNe->GetXaxis()->SetTitle("RhoNe");
	hMeanPU40_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hMeanPU40_RhoNe->SetTitle("Mean Neutral Iso");
	canvas4->cd(2);
	hRMSPU40_RhoNe->Draw("LEGO2");
	hRMSPU40_RhoNe->GetXaxis()->SetTitle("RhoNe");
	hRMSPU40_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hRMSPU40_RhoNe->SetTitle("RMS Neutral Iso");
	canvas4->cd(3);
	hEntriesPU40_RhoNe->Draw("LEGO2");
	hEntriesPU40_RhoNe->GetXaxis()->SetTitle("Rho");
	hEntriesPU40_RhoNe->GetYaxis()->SetTitle("PU Iso");
	hEntriesPU40_RhoNe->SetTitle("Num Entries");
	canvas4->SaveAs("./IsoCorr2D/NeIsoVSRhoNeVSPU_Pu40.pdf");
	
	
	
		////////////////////NEW ISO/////////////////////////////////////////////        
	TH2F* hTau_puCorrPtSumVSNeIso_PU40 = (TH2F*)f2->Get("hTau_puCorrPtSumVSNeIso");
	TH2F* hTau_RhoVSNeIso_PU40= (TH2F*)f2->Get("hTau_RhoVsNeutralIso");
	TH2F* hTau_RhoNeVsNeIso_PU40= (TH2F*)f2->Get("hTau_RhoNeutralVsNeutralIso");
	
					
    TH1D *ProjYNeIso20[80]; TH1D *ProjYNeIso40[80];
	TH1D *ProjYNeIsoRhoNe20[80]; TH1D *ProjYNeIsoRhoNe40[80];  TH1D *ProjYNeIsoPU40[80];
	
	float media =0; float media20 =0;
	float pesi =0; float pesi20     =0; 
	TH1F *hMeanNeIsoPU20 = new TH1F("hMeanNeIsoPU20","hMeanNeIsoPU20",80,0,80);
	TH1F *hMeanNeIsoPU40 = new TH1F("hMeanNeIsoPU40","hMeanNeIsoPU40",80,0,80);
					
	TH1F *hRMSNeIsoPU20 = new TH1F("hRMSNeIsoPU20","hRMSNeIsoPU20",80,0,80);
	TH1F *hRMSNeIsoPU40 = new TH1F("hRMSNeIsoPU40","hRMSNeIsoPU40",80,0,80);
					
	TH1F *hMeanRhoNeIsoPU20 = new TH1F("hMeanRhoNeIsoPU20","hMeanRhoNeIsoPU20",80,0,80);
	TH1F *hMeanRhoNeIsoPU40 = new TH1F("hMeanRhoNeIsoPU40","hMeanRhoNeIsoPU40",80,0,80);
					
					
	TH1F *hRMSRhoNeIsoPU20 = new TH1F("hRMSRhoNeIsoPU20","hRMSRhoNeIsoPU20",80,0,80);
	TH1F *hRMSRhoNeIsoPU40 = new TH1F("hRMSRhoNeIsoPU40","hRMSRhoNeIsoPU40",80,0,80);
					
	TH1F *hMean_PUIsoPU40 = new TH1F("hMean_PUIsoPU40","hMean_PUIsoPU40v",80,0,80);
	TH1F *hRMS_PUIsoPU40 = new TH1F("hRMS_PUIsoPU40","hRMS_PUIsoPU40",80,0,80);
					
	std::vector<double> RMSPU20;
	double meanRMSRhopu20 =0;
	double meanRMSRhoNepu20 =0;
	double meanRMSRhopu40 =0;
	double meanRMSRhoNepu40 =0;
				    
					std::vector<double> RMSPU40;
					std::vector<double> RMSPU40RhoNe;
					
					for(int i=0;i<80;++i){
						ProjYNeIsoRhoNe40[i]= hTau_RhoNeVsNeIso_PU40->ProjectionY("ProjYNeIso40", i, i+1); 
						ProjYNeIso40[i] = hTau_RhoVSNeIso_PU40->ProjectionY("ProjYRhoNeIso40", i, i+1); 
						ProjYNeIsoPU40[i] =hTau_puCorrPtSumVSNeIso_PU40->ProjectionY("ProjYPUNeIso40", i, i+1); 
						if( ProjYNeIso40[i]->GetEntries() > 100) {
							
							//cout<<" PU 40: NVTX="<<i<<" media  "<<ProjYNeIso40[i]->GetMean()<<" RMS  "<<ProjYNeIso40[i]->GetRMS()<<" entries "<<ProjYNeIso40[i]->GetEntries()<<endl;
							//media += (ProjYNeIso40[i]->GetRMS())/(1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries()));
							//pesi +=  (1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries())) ;
							hMeanNeIsoPU40->SetBinContent(i,ProjYNeIso40[i]->GetMean());
							hMeanNeIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIso40[i]->GetEntries()) );
							hRMSNeIsoPU40->SetBinContent(i, ProjYNeIso40[i]->GetRMS());
							hRMSNeIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIso40[i]->GetEntries()) );
							
							//meanRMSRhopu40 +=       ProjYNeIso40[i]->GetRMS();      
							RMSPU40.push_back(ProjYNeIso40[i]->GetRMS());
							
						}
						
						//   cout<<" size  "<<RMSPU40.size()<<endl ;
						
						if(ProjYNeIsoRhoNe40[i]->GetEntries() > 100)) {
							hRMSRhoNeIsoPU40->SetBinContent(i,ProjYNeIsoRhoNe40[i] ->GetRMS());
							hRMSRhoNeIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIsoRhoNe40[i]->GetEntries()) );
							
							hMeanRhoNeIsoPU40->SetBinContent(i,ProjYNeIsoRhoNe40[i] ->GetMean());
							hMeanRhoNeIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIsoRhoNe40[i]->GetEntries()) );
							
							
							meanRMSRhoNepu40 +=     hRMSRhoNeIsoPU40->GetRMS();     
							RMSPU40RhoNe.push_back(hRMSRhoNeIsoPU40->GetRMS());
						}
						
						if(ProjYNeIsoPU40[i]->GetEntries() > 100)) {
							hMean_PUIsoPU40->SetBinContent(i,ProjYNeIsoPU40[i] ->GetMean());
							hMean_PUIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIsoPU40[i]->GetEntries()) );
							
							hRMS_PUIsoPU40->SetBinContent(i,ProjYNeIsoPU40[i]->GetRMS());
							hRMS_PUIsoPU40->SetBinError(i,1/TMath::Sqrt(ProjYNeIsoPU40[i]->GetEntries()) );

						}
					}
						
						
						
					
				    TCanvas* canvas3 = new TCanvas("canvas3", "canvas3", 900, 1300);
					canvas3->Divide(2,3);
					canvas3->cd(1);
					hMeanNeIsoPU40->SetMarkerColor(kBlue);
					hMeanNeIsoPU40->Fit("pol1");
					hMeanNeIsoPU40->SetTitle("Mean Neutral Iso VS Rho");
					hMeanNeIsoPU40->GetXaxis()->SetTitle("#rho");
	                hMeanNeIsoPU40->GetYaxis()->SetTitle("Mean Neutral particles Isolation");
					hMeanNeIsoPU40->Draw("esame");
					canvas3->cd(2);
					hRMSNeIsoPU40->SetMarkerColor(kBlue);
					hRMSNeIsoPU40->Fit("pol1");
					hRMSNeIsoPU40->Draw("peSAME");
	                hRMSNeIsoPU40->GetXaxis()->SetTitle("#rho");
	                hRMSNeIsoPU40->GetYaxis()->SetTitle("RMS Neutral particles Isolation");
					hRMSNeIsoPU40->SetTitle("RMS Neutral Iso VS Rho");	
					canvas3->cd(3);
					hMeanRhoNeIsoPU40->SetMarkerColor(kBlue);
					hMeanRhoNeIsoPU40->Fit("pol1");
					hMeanRhoNeIsoPU40->Draw("pesame");
	                hMeanRhoNeIsoPU40->SetTitle("Mean Neutral Iso VS Rho Neutral");	
	                hMeanRhoNeIsoPU40->GetXaxis()->SetTitle("#rho_{Neutral}");
	                hMeanRhoNeIsoPU40->GetYaxis()->SetTitle("Mean Neutral particles Isolation");
					canvas3->cd(4);
					hRMSRhoNeIsoPU40->SetMarkerColor(kBlue);
					hRMSRhoNeIsoPU40->Fit("pol1");
					hRMSRhoNeIsoPU40->Draw("peSAME");
					hRMSRhoNeIsoPU40->SetTitle("RMS Neutral Iso VS Rho Neutral");	
	hRMSRhoNeIsoPU40->GetXaxis()->SetTitle("#rho_{Neutral}");
	hRMSRhoNeIsoPU40->GetYaxis()->SetTitle("RMS Neutral particles Isolation");
	
	canvas3->cd(5);
	hMean_PUIsoPU40->SetMarkerColor(kBlue);
	hMean_PUIsoPU40->Fit("pol1");
	hMean_PUIsoPU40->Draw("esame");
	//hMean_PUIsoPU40->SetTitle("Mean Neutral Iso VS PU Iso");	
	hMean_PUIsoPU40->GetXaxis()->SetTitle("PU isolation");
	hMean_PUIsoPU40->GetYaxis()->SetTitle("Mean Neutral particles Isolation");
	
	canvas3->cd(6);
	hRMS_PUIsoPU40->SetMarkerColor(kBlue);
	hRMS_PUIsoPU40->Fit("pol0");
	hRMS_PUIsoPU40->Draw("peSAME");
	//hRMS_PUIsoPU40->SetTitle("RMS Neutral Iso VS PU Iso");
	hRMS_PUIsoPU40->GetXaxis()->SetTitle("PU isolation");
	hRMS_PUIsoPU40->GetYaxis()->SetTitle("RMS Neutral particles Isolation");
									
					
					
					TCanvas* canvas4 = new TCanvas("canvas4", "canvas4", 1400, 700);
					canvas4->Divide(2,1);
					canvas4->cd(1);
					TH3F* hTau_rhoPUVSNeIso_PU20 = (TH3F*)f1->Get("hTau_rhoPUVSNeIso");
					hTau_rhoPUVSNeIso_PU20 ->Draw("COLZ");
					canvas4->cd(2);
					TH3F* hTau_rhoPUVSNeIso_PU40 = (TH3F*)f2->Get("hTau_rhoPUVSNeIso");
					hTau_rhoPUVSNeIso_PU40 ->Draw("LEGO");
					
					
					
					
					//cout<<" rms medio  pu 40 ="<<media/pesi<<endl;
					//      cout<<" RMS medio  pu 20 ="<<media20/pesi20<<endl;
					
					
					
					
			
	
/*	TH2D *h2prova[80];
	TH1 *h1prova[80];

	for(int i=0;i<80;++i){
		
		hTau_rhoPUVSNeIso_PU40->GetXaxis()->SetRange(i,(i+1));
		hTau_rhoNePUVSNeIso_PU40->GetXaxis()->SetRange(i,(i+1));
		
		for(int j=0; j<50;++j){
			hTau_rhoPUVSNeIso_PU40->GetYaxis()->SetRange(j,(j+1));
			hTau_rhoNePUVSNeIso_PU40->GetYaxis()->SetRange(j,(j+1));	
			
			h2prova[i] = hTau_rhoPUVSNeIso_PU40->Project3DProfile("xz");
			//cout<<"  mean palle  "<<(h2prova[40]->ProjectionY("prova",i,i+1))->GetMean()<<endl;
						
		}
	}
						

	for (int k=30;k<33;k++){
		cout<<"*********************"<<k<<"*********************"<<endl;
		for(int i=0;i<80;i++){
				h1prova[i] = 	h2prova[k]->ProjectionY("prova",i,i+1) ;
				cout<<i<<"  mean palle "<< h1prova[i]->GetMean()<<endl;
	}	
}
	*/		


}	
			
			
			
			
			
			
			
			
			
			
			
			
			

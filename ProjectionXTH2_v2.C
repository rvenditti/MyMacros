#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TString.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TLatex.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>


void ProjectionXTH2(string inputfile, TString path, TString histoName, TString time, TString folderName, TString label, double binMax, TString process, int rebin){

	gROOT->SetBatch(true);
	//gStyle->SetOptStat(00000000);
	gStyle->SetOptStat(111111111);

	TFile * f = TFile::Open(inputfile.c_str());
	
	TH2F*  h2  = (TH2F*)f->Get(path + histoName);
	
//	TH1F*   = (TH1F*)f->Get(path+"hNzmm");
//	std::cout<<inputfile.c_str()<<"-------------------------------------------------------------------------------------------- Nevents="<<hEvents->Integral()<<std::endl;

	TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 700, 700);
	
	h2->RebinX(2);
	//h2->RebinY(4);
	h2->GetYaxis()->SetTitle("p_{T}^{sim} [GeV]");
	h2->GetXaxis()->SetTitle(label);
	h2->SetStats(0);
	h2->SetTitle(time);
	//h2->GetXaxis()->SetRangeUser(0, binMax);
	h2->Draw("COLZ");
	cout<<"XY correlation factor "<<h2->GetCorrelationFactor()<<" Entris "<<h2->GetEntries()<<endl;
	canvas2->SaveAs( path +histoName+time+".png" );
	
	
	

	const int NBinsX = h2->GetNbinsX();
	const int NBinsY = h2->GetNbinsY();
	cout<<" NBins X"<<NBinsX<<endl;
	cout<<" NBins Y"<<NBinsY<<endl;

	//TH1D *ProjX; 
	//ProjX = (TH1D) malloc(NBinsY * sizeof(TH1D));
	TH1D* ProjX[200];
		
	TH1F *hMean = new TH1F("hMean","hMean",NBinsY,0,200);
	TH1F *hRMS = new TH1F("hRMS","hRMS",NBinsY,0,200);
	
		
	TAxis* xAxis = h2->GetXaxis();
	TAxis* yAxis = h2->GetYaxis();
	

	
	for(int i=0;i<NBinsY;++i){
		//TString id =  "ProjX";
		//id  ++;
		ProjX[i]= h2->ProjectionX("ProjX", i, i+1); 


		double binCenterX = xAxis->GetBinCenter(i);
		double binCenterY = yAxis->GetBinCenter(i);

	   // if(ProjX[i]->GetEntries() > 10) {
	   // cout<<i<<" sim pt= "<<yAxis->GetBinCenter(i)<<" mean phi "<<ProjX[i]->GetMean()<<" entries "<<ProjX[i]->GetEntries() <<endl;
		
		// cout<<i<<" histo estratto mean="<<ProjX[i]->GetMean()<<"  rms="<<ProjX[i]->GetRMS()<<"  entries="<<ProjX[i]->GetEntries()<<endl;
		ProjX[i]->SetLineWidth(2);
		ProjX[i]->SetLineColor(i+1);
		
		hMean->SetBinContent(i,ProjX[i]->GetMean());
		//hMean->SetBinError(i,ProjX[i]->GetMeanError() );
		hMean->SetBinError(i,ProjX[i]->GetRMS() );
	    //hRMS->SetBinContent(i, ProjX[i]->GetRMS());
		hRMS->SetBinError(i,ProjX[i]->GetRMSError());
		//}
		}
	
	
	
	
	TCanvas* canvas3 = new TCanvas("canvas3", "MEAN", 700, 500);
	canvas3->cd();
	hMean->SetMarkerColor(kBlue);
//	hMean->GetXaxis()->SetRangeUser(0,40);
	hMean->SetLineWidth(2);
	hMean->SetStats(0);
	hMean->SetTitle(0);
	hMean->Draw("poe");
		
	hMean->GetXaxis()->SetTitle("p_{T}^{sim} [GeV]");
	
	hMean->GetYaxis()->SetTitle(label);
	hMean->GetXaxis()->SetRangeUser(0,100);
	hMean->GetYaxis()->SetTitleOffset(1.2);	
	//hMean->Rebin(4);
	
	
	TLatex *   tex = new TLatex(0.8731544,0.9115385, process);
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	tex->SetTextSize(0.035);
	tex->SetLineWidth(1);
	tex->Draw();
	tex = new TLatex(0.1097315,0.9668531,"CMS Simulation");
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(61);
	tex->SetTextSize(0.0472028);
	tex->SetLineWidth(1);
	tex->Draw();
	canvas3->Modified();
	canvas3->cd();
	canvas3->SetSelected(canvas3);
	
	
	canvas3->SaveAs(path+histoName+"_projX"+time+".png");	
	canvas3->SaveAs(path+histoName+"_projX"+time+".pdf");
	//canvas3->Delete();
	
	TFile* fout = new TFile(path+histoName+ time+ ".root", "recreate");
	fout->cd();
	hMean->Write();
	//fout->Close();
	
	TCanvas* CanvVector[200];
		
	
	TH1D* ProjX2[200];
	
	
	
	//h2->RebinY(4);
	int nbinpT = h2->GetNbinsY();
	cout<<"-------------------------------------------------------------#plots  "<<nbinpT-1<<endl;
	for(int i=0;i<(nbinpT);++i){
		ProjX2[i]= h2->ProjectionX("ProjX2", i, i+1); 
		//cout<<i<<" mean pT="<<yAxis->GetBinCenter(i)<<"  mean phi="<<ProjX2[i]->GetMean()<<"  rms="<<ProjX2[i]->GetRMS()<<"  entries="<<ProjX2[i]->GetEntries()<<" binWidth="<<ProjX2[i]->GetBinWidth(2)<<endl;
		ProjX2[i]->SetLineWidth(2);
		ProjX2[i]->SetLineColor(i+1);
		
		TString nameforwriting ("DeltaPhi_pT"); nameforwriting+=(i*4);	
		ProjX2[i]->Write(nameforwriting);
		
		TString titleCanv ("CanvVector"); titleCanv+=(i+1);	
		CanvVector[i] = new TCanvas("titleCanv", "titleCanv", 700, 500);
		CanvVector[i]->cd();
		//ProjX2[i]->Rebin();
		ProjX2[i]->Draw("hist");
		//ProjX2[i]->RedrawAxis(); 
		CanvVector[i]->SaveAs(folderName+"/"+time+"/"+titleCanv+".pdf");
		}	
	
	
	fout->Close();	
	
	
	
	TFile* fnew = new TFile(path + histoName+ time+ ".root", "READ");
	
	TH1F* histopT[10];  TH1F* histopT_norm[10];  

	std::vector<TString> dphiName;
	dphiName.push_back("DeltaPhi_pT4");
	dphiName.push_back("DeltaPhi_pT12");
	dphiName.push_back("DeltaPhi_pT20");
	dphiName.push_back("DeltaPhi_pT28");
	//dphiName.push_back("DeltaPhi_pT48");
	
	TCanvas * cAll = new TCanvas("cAll", "DPhi in pT range", 600, 600);
	for(int i=0;i< dphiName.size() ;++i){
		fnew->cd();
		histopT[i] = (TH1F*)fnew->Get(dphiName[i]);
		//		histopT[i] = (TH1F*)f->Get("DeltaPhi_pT28");
		
		histopT[i]->Rebin(rebin);
		cout<<" DPhi range: entries "<<histopT[i]->GetEntries()<<" mean "<<histopT[i]->GetMean()<<" binWidth="<<histopT[i]->GetBinWidth(2)<<endl;
	//	histopT[i]->SetLineColor(i+7);
		histopT[i]->SetStats(0);
		histopT[i]->SetTitle(0);
		//histopT[i]->SetTitle(time);
		histopT[i]->GetXaxis()->SetTitle(label);
		histopT[i]->GetYaxis()->SetTitle("fraction of Muons");
		histopT[i]->GetYaxis()->SetTitleOffset(1.5);
		
	     TH1F htmp (dphiName[i], dphiName[i], histopT[i]->GetNbinsX()  , 0 , binMax);
		//histopT_norm[i] = dynamic_cast<TObject*>(histopT[i]->Clone());
		//histopT_norm[i]->Reset();
		
		double nEntries = histopT[i]->GetEntries() ;

		std::cout<<"---------------"<<dphiName[i]<<"---------------"<<std::endl;
		for(int k =0; k<histopT[i]->GetNbinsX(); k++){

			histopT[i]->SetBinContent(k, histopT[i]->GetBinContent(k)/nEntries) ;			
		}
		
		histopT[i]->GetXaxis()->SetRangeUser(0.,binMax);	
	}
	
	histopT[0]->SetLineColor(1);
	histopT[1]->SetLineColor(2);
	histopT[2]->SetLineColor(kGreen+2);
	histopT[3]->SetLineColor(kMagenta+2);
	/*histopT[4]->SetLineColor(kBlue);
	*/
	cAll->cd();
	histopT[0]->SetMaximum( (6) * (histopT[0]->GetMaximum()));
	
	histopT[0]->Draw("hist");
	histopT[1]->Draw("histsame");
	histopT[2]->Draw("histsame");
	histopT[3]->Draw("histsame");
/*	histopT[4]->Draw("histsame");
	histopT[6]->Draw("histsame")
	histopT[7]->Draw("histsame");*/
	cAll->SetLogy();
	cAll->RedrawAxis(); 
	
	TLegend* legend1 = new TLegend(0.51, 0.6, 0.89, 0.89);
	legend1->SetHeader(time);
	legend1->AddEntry(histopT[0], "0<Muon p_{T}<5"   ,"l");
	legend1->AddEntry(histopT[3], "25<Muon p_{T}<35"   ,"l");
	legend1->SetFillColor(0);
	legend1->SetTextSize(0.034);	
	
	/*
	for(int m=1;m<dphiName.size() ;m++) {
		TString labelpTmax ("<Muon p_{T}<");  labelpTmax +=(5+m*10);
		TString labelpTmin (" ");  labelpTmin +=((m-1)*10+5  );	
		legend1->AddEntry(histopT[m], labelpTmin + labelpTmax  ,"l");
	}*/
	cAll->cd();
	legend1->Draw("same");
	tex->Draw();
	
	
	TLatex *   tex1 = new TLatex(0.87,0.91,process);
	tex1->SetNDC();
	tex1->SetTextAlign(31);
	tex1->SetTextFont(42);
	tex1->SetTextSize(0.027);
	tex1->SetLineWidth(1);
	tex1->Draw();
	
	cAll->Modified();
	cAll->cd();
	cAll->SetSelected(cAll);
	cAll->SaveAs(folderName+"/"+time+"/"+histoName+time+".png");
	cAll->SaveAs(folderName+"/"+time+"/"+histoName+time+".pdf");
	
	
	
	}



void GetPlot(){

//	ProjectionXTH2("histoME0Seg_500micron_7marzo.root","me0SegAna/","hMuonDigiDPhiVsPT" , "DigiPU0_promptOnly_500um_Reco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);
	//ProjectionXTH2("histoME0Seg_500micron_7marzo.root","me0SegAna/","hMuonDigiDXVsPT" ,   "DigiPU0_promptOnly_500um_Reco","DXPlots",   "#DeltaX(first hit, last hit) [cm]", 20, "Z/#gamma*#rightarrow #mu#mu 14 TeV",100);
	/*ProjectionXTH2("histoME0Seg_500um_PU0.root", "me0SegAna/","hMuonDigiDPhiVsPT" ,   "DigiPU0_promptOnly_500um_Reco","DPhiPlots",   "#DeltaPhi(first hit, last hit) [cm]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV",50);
	ProjectionXTH2("histoME0Seg_100um_PU0.root", "me0SegAna/","hMuonDigiDPhiVsPT" ,   "DigiPU0_promptOnly_100um_Reco","DPhiPlots",   "#DeltaPhi(first hit, last hit) [cm]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV",50);
	ProjectionXTH2("histoME0Seg_100um_PU0.root", "me0SegAna/","hSimPtVSDphi" ,        "DigiPU0_promptOnly_100um_Sim","DPhiPlots",   "#DeltaPhi(first hit, last hit) [cm]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV",50);
	*/
	
	ProjectionXTH2("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root","me0SegAna/","hMuonDigiDPhiVsPT" , "DigiPU0_promptOnly_500um_Reco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.1, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);

	
/*	ProjectionXTH2("histoME0Seg_500micron_7marzo.root","me0SegAna/","hMuonDigiLocalDPhiVsPT" , "DigiPU0_promptOnly_500um_LocalReco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.1, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);
	ProjectionXTH2("histoME0Seg_500micron_7marzo.root","me0SegAna/","hMuonDigiLocalDXVsPT" ,   "DigiPU0_promptOnly_500um_LocalReco","DXPlots",   "#DeltaX(first hit, last hit) [cm]", 20, "Z/#gamma*#rightarrow #mu#mu 14 TeV",100);
	
	ProjectionXTH2("histoME0Seg_100micron_7marzo.root","me0SegAna/","hMuonDigiLocalDPhiVsPT" , "DigiPU0_promptOnly_100um_LocalReco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.1, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);
	ProjectionXTH2("histoME0Seg_100micron_7marzo.root","me0SegAna/","hMuonDigiLocalDXVsPT" ,   "DigiPU0_promptOnly_100um_LocalReco","DXPlots",   "#DeltaX(first hit, last hit) [cm]", 20, "Z/#gamma*#rightarrow #mu#mu 14 TeV",100);
	
	ProjectionXTH2("histoME0Seg_1micron_7marzo.root","me0SegAna/","hMuonDigiLocalDPhiVsPT" , "DigiPU0_promptOnly_1um_LocalReco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.1, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);
	ProjectionXTH2("histoME0Seg_1micron_7marzo.root","me0SegAna/","hMuonDigiLocalDXVsPT" ,   "DigiPU0_promptOnly_1um_LocalReco","DXPlots",   "#DeltaX(first hit, last hit) [cm]", 20, "Z/#gamma*#rightarrow #mu#mu 14 TeV",100);


	ProjectionXTH2("histoME0Seg_100micron_7marzo.root","me0SegAna/","hMuonDigiDPhiVsPT" , "DigiPU0_promptOnly_100um_Reco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);
	ProjectionXTH2("histoME0Seg_1micron_7marzo.root","me0SegAna/","hMuonDigiDPhiVsPT" , "DigiPU0_promptOnly_1um_Reco","DPhiPlots", "#Delta#Phi(first hit, last hit) [rad]", 0.01, "Z/#gamma*#rightarrow #mu#mu 14 TeV", 50);

	*/
	}

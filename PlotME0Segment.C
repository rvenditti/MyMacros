#include <TH1.h>
#include <TH2.h>
#include <TH1D.h>
#include <string>
#include <vector>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <iostream>
#include <TFile.h>
#include <algorithm>    


void GiveRate(TString Filename, TString histoNameNum,TString histoNameDen){
	TH1::SetDefaultSumw2();
	TFile * file = TFile::Open(Filename);
	TH1F * 	histoNum = (TH1F*)file->Get("me0SegAna/"+histoNameNum );
	TH1F*   histoDen = (TH1F*)file->Get("me0SegAna/"+histoNameDen);
	cout<<" rate="<<histoNum->Integral()/histoDen->Integral()<<endl;

}

TH1F * Divide(TString Filename, TString histoNameNum,TString histoNameDen ){
	
	TH1::SetDefaultSumw2();
	TFile * file = TFile::Open(Filename);
	TH1F * 	histoNum = (TH1F*)file->Get("me0SegAna/"+histoNameNum );
	TH1F*   histoDen = (TH1F*)file->Get("me0SegAna/"+histoNameDen);
	
	histoNum->Rebin(2);
	histoDen->Rebin(2);
	cout<<" Num="<<histoNum->Integral()<<" Den="<<histoDen->Integral()<<endl;
	
	TH1F* hEff =new TH1F("hEff","hEff",histoNum->GetNbinsX(), 0, 200);
	hEff->Divide(histoNum,histoDen, 1. ,  1. , "B");
	
//	for(int k=0; k<histoNum->GetNbinsX(); k++ ){
//		double binerr= TMath::Sqrt();}
	
	//TEfficiency* pEff = 0;
	//TEfficiency* pEff = new TEfficiency("eff","my efficiency;x;#epsilon",histoNum->GetNbinsX(), 0, 200);
	//pEff = new TEfficiency(histoNum,histoDen);
	
	TCanvas * canvEffCut = new TCanvas("canvEffCut","canvEffCut",700, 600);
	if(Filename.Contains("100ps")){
	histoNum->SetLineColor(1);
	histoDen->SetLineColor(2);
	//histoNum->Scale(1/histoNum->Integral());
	//histoDen->Scale(1/histoDen->Integral());
	histoNum->GetXaxis()->SetTitle("Muon p_{T}^{sim}");
	histoDen->GetXaxis()->SetTitle("Muon p_{T}^{sim}");
	histoNum->GetXaxis()->SetRangeUser(0,100);
	histoDen->GetXaxis()->SetRangeUser(0,100);
	histoDen->SetLineColor(2);
	histoDen->Draw();	
	histoNum->Draw("same");

	
	TLegend* legend = new TLegend(0.6, 0.85, 0.9, 0.75);
	legend->AddEntry(histoNum,histoNameNum, "l");
	legend->AddEntry(histoDen,histoNameDen, "l");
	legend->Draw("same");
	canvEffCut->SaveAs("MuonpTSim"+histoNameNum+".pdf");
	}
	
//	hEff->Draw("p0");
	return hEff;
//	return pEff;

}


std::vector<TGraph *> PlotEff(TString histoName, std::vector<TString> fName, std::vector<TString> label){
	//gStyle->SetOptStat(00000001111);	
	//gStyle->SetOptStat("nemr");
	TFile* f[100];
	TH1F* histo[100];
	std::vector<TGraph *> gr; 
	TCanvas * canv = new TCanvas("canv","canv",700, 600);
	//TLegend* legend = new TLegend(0.6, 0.45, 0.9, 0.15);
	//  legend->SetHeader((categories.at(j)).c_str());
	//legend->SetFillColor(0);
	//legend->SetTextSize(0.025);
	
	for(int i=0;i<fName.size(); i++ ){
		f[i] = TFile::Open(fName[i]);
		histo[i] = (TH1F*)f[i]->Get("me0SegAna/"+histoName );
		cout<<i<<"  Filename: "<<fName[i]<<endl;	
		//	cout<<" lastBin="<<histo[i]->GetXaxis()->FindBin(0.05)<<endl;
		TH1F * h1 = new TH1F("h1","eff vs cut", (histo[i]->GetNbinsX())/2, 0., 0.05);
		
		int n=histo[i]->GetNbinsX()-2;
		double x[1000]= {0}; double y[1000]= {0};
		
		for(int k=histo[i]->GetXaxis()->FindBin(0.); k<histo[i]->GetNbinsX()-1; k++){
			double eff= histo[i]->Integral(histo[i]->GetXaxis()->FindBin(0.), k)/histo[i]->Integral(histo[i]->GetXaxis()->FindBin(0.), histo[i]->GetNbinsX()-1);
			//cout<<" k= "<<k<<" bin="<<histo[i]->GetBinCenter(k)<<" eff="<<eff<<endl;
			h1->SetBinContent(k, eff);
			x[k]=histo[i]->GetBinCenter(k);
			y[k]=eff;
		}
		
		TCanvas * cEff = new TCanvas("cEff","cEff",500, 500);
		h1->SetMarkerStyle(20);
		//h1->Draw("p0e");
		
//		gr[i]= new TGraph(n,x,y);
		gr.push_back( new TGraph (n, x, y) );
		cout<<" sto qua"<<	endl;	
		//gr[i]->Draw("AC*");
		//cEff->SaveAs("eff"+histoName+"_"+label[i]+".pdf");
		
	}

return gr;
}

void PlotAnalisi(TString histoName, std::vector<TString> fName, std::vector<TString> label){
	
//	gROOT->ProcessLine(".L ./tdrstyle.C");
	//setTDRStyle();
	//gStyle->SetOptStat(00000001111);	
	gStyle->SetOptStat("nemr");
	TFile* f[100];
	TH1F* histo[100];
	TCanvas * canv = new TCanvas("canv","canv",700, 600);
	TLegend* legend = new TLegend(0.6, 0.45, 0.9, 0.15);
	//  legend->SetHeader((categories.at(j)).c_str());
	legend->SetFillColor(0);
	legend->SetTextSize(0.025);
	
	std::vector<double> maximum;


	
	for(int i=0;i<fName.size(); i++ ){
		f[i] = TFile::Open(fName[i]);
		histo[i] = (TH1F*)f[i]->Get("me0SegAna/"+histoName );
		cout<<i<<"  Filename: "<<fName[i]<<endl;	
		
		if(histoName.Contains("hNME0SegmentSignal")  || histoName.Contains("hNME0SegmentSignal_timeCut")  ){
			histo[i]->GetXaxis()->SetRangeUser(0,10);
			cout<<histoName<<"/////////////////////////////////////\\\\\\\\\//////////////////////////////////////// "<<histo[i]->Integral()<<endl;
			histo[i]->SetMaximum(1.2);
		}
		
		
		histo[i]->Scale(1/histo[i]->Integral());
		histo[i]->SetLineColor(i+1);	
		histo[i]->SetLineWidth(2);	
		histo[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo[i]->GetYaxis()->SetTitleOffset(1.4);
	
		maximum.push_back(histo[i]->GetMaximum());
		
		if(histoName.Contains("hDPhi")){
		//	histo[i]->Rebin(5); 
			histo[i]->GetXaxis()->SetRangeUser(-0.04,0.04); 
			histo[i]->GetXaxis()->SetTitle("#Delta#Phi(L1, L6) [rad]");
		//	canv->SetLogy();

		}
			
	
		if(histoName.Contains("hSimDPhi")){
			histo[i]->Rebin(5);		
			histo[i]->GetXaxis()->SetRangeUser(-0.02,0.02); 
			histo[i]->GetXaxis()->SetTitle("#Delta#Phi(L1, L6) [rad]");

		}
		
	/*
		
		if(histoName.Contains("hDX")){
			histo[i]->Rebin(10);  histo[i]->GetXaxis()->SetTitle("#DeltaX(L1, L6) [cm]");
		}
		
		if(histoName.Contains("hNME0RecHits")){
			histo[i]->GetXaxis()->SetTitle("#Rechits");
			histo[i]->GetXaxis()->SetRangeUser(0,25);
		}
		
		if(histoName.Contains("hDeltaPhiSimReco")){
			histo[i]->Rebin(1); 
			histo[i]->GetXaxis()->SetTitle("#Delta#Phi(SimHit, RecHit) [rad]");
			histo[i]->GetXaxis()->SetRangeUser(-0.005,0.005);

		}
		
		
		if(histoName.Contains("hDeltaEtaSimReco")){
			histo[i]->Rebin(2); 
			histo[i]->GetXaxis()->SetTitle("#Delta#eta(SimHit, RecHit)"); 
			histo[i]->GetXaxis()->SetRangeUser(-0.2,0.2); 
		}
		
		if(histoName.Contains("hDeltaXSimReco")){
			histo[i]->Rebin(10); 
			histo[i]->GetXaxis()->SetTitle("#DeltaX(SimHit, RecHit) [cm]");}
		
		if(histoName.Contains("hDeltaYSimReco")){
			histo[i]->GetXaxis()->SetRangeUser(-2,2); 
			histo[i]->GetXaxis()->SetTitle("#DeltaY(SimHit, RecHit) [cm]");}
		
		if(histoName.Contains("hDeltaXSimRecoLocal")){
		histo[i]->Rebin(2); 
		histo[i]->GetXaxis()->SetTitle("#DeltaX(SimHit, RecHit) [cm]");
		}
		
		if(histoName.Contains("hDeltaYSimRecoLocal")){
			histo[i]->GetXaxis()->SetRangeUser(-2,2); 
			histo[i]->GetXaxis()->SetTitle("#DeltaY(SimHit, RecHit) [cm]");
		}
		
		
		if(histoName.Contains("hme0machtMuonEta")){
			histo[i]->Rebin(5); 
			histo[i]->GetXaxis()->SetTitle("Muon #eta");
		}
		
		if(histoName.Contains("hme0machtMuonPt")){
			histo[i]->Rebin(5); 
			histo[i]->GetXaxis()->SetTitle("Muon p_{T}");
			histo[i]->GetXaxis()->SetRangeUser(0,80); 
		}
		
		if( (histoName.Contains("LocalDXNeg")) || (histoName.Contains("LocalDXPos") )){
			histo[i]->GetXaxis()->SetTitle("#DeltaX^{loc}(L1,L6) [cm]");
			histo[i]->GetXaxis()->SetRangeUser(-2,2); 
		}
		
			
		if(histoName.Contains("hNME0Time")) {
			histo[i]->GetXaxis()->SetTitle("Time (ns)"); 			
			histo[i]->GetXaxis()->SetRangeUser(-100,100); 
			
		}*/
	 

		/*
		if(histoName.Contains("hDPhiMatchByHitsME0Seg_Signal")){
			histo[i]->Rebin(2); 
			//histo[i]->GetXaxis()->SetRangeUser(-0.04,0.04); 
			histo[i]->GetXaxis()->SetTitle("ME0Segment #Delta#Phi(L1, L6) [rad]");
			//canv->SetLogy();
			
		}
		
		if(histoName.Contains("DPhiMatchByHitsME0Seg_Bkg")){
			histo[i]->Rebin(10); 
			//histo[i]->GetXaxis()->SetRangeUser(-0.04,0.04); 
			histo[i]->GetXaxis()->SetTitle("ME0Segment #Delta#Phi(L1, L6) [rad]");
			//canv->SetLogy();
		}*/
		
		if(histoName.Contains("hTimeDiffSigvsBkg")){
				histo[i]->GetXaxis()->SetTitle("SigTime-BkgTime [ns]");
				if(fName[i].Contains("1ns")){cout<<fName[i]<<" ---------------------------------------------- signal/bkg="<< histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-3),histo[i]->GetXaxis()->FindBin(3))/
					(histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-10),histo[i]->GetXaxis()->FindBin(-4))+histo[i]->Integral(histo[i]->GetXaxis()->FindBin(4),histo[i]->GetXaxis()->FindBin(10)) ) <<endl; }
		
		if(fName[i].Contains("5ns")){cout<<fName[i]<<" ---------------------------------------------- signal/bkg="<< histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-15),histo[i]->GetXaxis()->FindBin(15))/
		(histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-100),histo[i]->GetXaxis()->FindBin(-16))+histo[i]->Integral(histo[i]->GetXaxis()->FindBin(16),histo[i]->GetXaxis()->FindBin(100)) ) <<endl; }
	
	
			if(fName[i].Contains("100ps")){cout<<fName[i]<<" ---------------------------------------------- signal/bkg="<< 
			histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-1.5),histo[i]->GetXaxis()->FindBin(1.5))/	(histo[i]->Integral(histo[i]->GetXaxis()->FindBin(-10),histo[i]->GetXaxis()->FindBin(-1.5))+histo[i]->Integral(histo[i]->GetXaxis()->FindBin(1.5),histo[i]->GetXaxis()->FindBin(10)) ) <<endl; }
			}
		
		/*
		if(histoName.Contains("hDPhiNoMatchME0Seg")){
				histo[i]->Rebin(2); 
				//histo[i]->GetXaxis()->SetRangeUser(-0.04,0.04); 
				histo[i]->GetXaxis()->SetTitle("ME0Segment #Delta#Phi(L1, L6) [rad]");
				
			}*/
		
				
	legend->AddEntry( histo[i] , label[i] , "l");

}
	
	int	numHisto = fName.size();
	canv->cd();
	histo[0]->Draw();
	gPad->Update();
	TPaveStats* st = (TPaveStats*) histo[0]->FindObject("stats");
	st->SetX1NDC(0.85);
	st->SetX2NDC(0.99);
	st->SetY1NDC(0.95);
	st->SetY2NDC(0.80);
	st->SetTextColor(1);
	st->Draw();
	gPad->Update();
	
	TPaveStats * statbox[100];
	double boxdim=0.15;
	
	for(int m=0; m<numHisto; m++) {
		histo[m]->Draw("histsames");
		gPad->Update();	
		statbox[m] = (TPaveStats*) histo[m]->FindObject("stats");
		statbox[m]->SetX1NDC(0.85);
        statbox[m]->SetX2NDC(0.99);
        statbox[m]->SetY1NDC(0.95-m*boxdim);
        statbox[m]->SetY2NDC(0.80-m*boxdim);
        statbox[m]->SetTextColor(m+1);
        statbox[m]->Draw();
		gPad->Update();	
	//	std::cout<<"maximum="<<maximum[m]<<endl;
	}

	double maxY= (*std::max_element(maximum.begin(),maximum.end()));
	std::cout<<"max="<< maxY<<endl;
	//histo[2]->GetYaxis()->SetRangeUser(0, 2*maxY);
	//histo[1]->SetMaximum(2*maxY);
	gPad->Update();
	
	legend->Draw();
	canv->RedrawAxis();
	canv->SaveAs("PlotME02/"+ histoName +".pdf");
}

void Overlay(TString Filename, std::vector<TString> histoName, TString labelX, float binMin, float binMax, TString titlePlot){
	gStyle->SetOptStat("nemr");
	cout<<"********************************************************************Overlay signal and bkg*****************************************************************"<<endl;
	cout<<Filename<<endl;
	//gStyle->SetOptStat(0);
	TH1F * histo[10];
	TFile * f = TFile::Open(Filename);
	TLegend* legend = new TLegend(0.82, 0.35, 0.95, 0.15);
	double boxdim=0.2;
	for(int i=0;i<histoName.size(); i++){
		histo[i] = (TH1F*)f->Get("me0SegAna/"+histoName[i]);
		histo[i]->SetLineColor(i+1);	
		histo[i]->SetLineWidth(2);	
		histo[i]->Rebin(5);	
		histo[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo[i]->GetXaxis()->SetTitle(labelX);
		histo[i]->GetYaxis()->SetTitleOffset(1.4);
		histo[i]->GetXaxis()->SetRangeUser(binMin, binMax);
		std::cout<<" Mean="<<histo[i]->GetMean()<<" RMS="<<histo[i]->GetRMS()<<std::endl;
	}
	

	std::cout<<"S/N Before Timing Cut: "<<histo[0]->Integral()/histo[1]->Integral()<<" s="<<histo[0]->Integral()<<" b="<<histo[1]->Integral()<<std::endl;
//	if(Filename.Contains("Pt5")) std::cout<<"S/N Before Timing Cut in signal region: "<<histo[0]->Integral(histo[0]->GetXaxis()->FindBin(-0.01),histo[0]->GetXaxis()->FindBin(0.01))/histo[1]->Integral(histo[1]->GetXaxis()->FindBin(-0.01),histo[1]->GetXaxis()->FindBin(0.01))<<std::endl;
//	if(Filename.Contains("Pt30")) std::cout<<"S/N Before Timing Cut in signal region: "<<histo[0]->Integral(histo[0]->GetXaxis()->FindBin(-0.003),histo[0]->GetXaxis()->FindBin(0.003))/histo[1]->Integral(histo[1]->GetXaxis()->FindBin(-0.003),histo[1]->GetXaxis()->FindBin(0.003))<<std::endl;
	

	histo[0]->Scale(1/(histo[0]->Integral()+histo[1]->Integral()));
	histo[1]->Scale(1/(histo[0]->Integral()+histo[1]->Integral()));
	
	


	TCanvas * Canvas = new TCanvas("Canvas","Canvas",500, 600);
	histo[0]->Draw();
	gPad->Update();
	TPaveStats* st = (TPaveStats*) histo[0]->FindObject("stats");
	st->SetX1NDC(0.7);
	st->SetX2NDC(0.9);
	st->SetY1NDC(0.9-0*boxdim);
	st->SetY2NDC(0.70-0*boxdim);
	st->SetTextColor(1);
	st->Draw();
	gPad->Update();
	
	histo[1]->Draw("histsames");
	gPad->Update();	

	histo[1]->Draw("histsames");
	TPaveStats * statbox2 = (TPaveStats*) histo[1]->FindObject("stats");
	statbox2->SetX1NDC(0.7);
	statbox2->SetX2NDC(0.9);
	statbox2->SetY1NDC(0.9-1*boxdim);
	statbox2->SetY2NDC(0.7-1*boxdim);
	statbox2->SetTextColor(2);
	statbox2->Draw();
	gPad->Update();	
	
	if(histo[0]->GetMaximum()>histo[1]->GetMaximum()) histo[0]->SetMaximum(histo[0]->GetMaximum());
	if(histo[0]->GetMaximum()<histo[1]->GetMaximum()) histo[0]->SetMaximum(histo[1]->GetMaximum());

	legend->AddEntry(histo[0],"Signal","l");	
	legend->AddEntry(histo[1],"Bkg","l");	
	legend->Draw("same");
	
	
	Canvas->SaveAs("PlotME02/"+ titlePlot+".pdf");

}



	TH1D * GiveProjection(TString fName, TString histoName2D, float timeRes){
	TFile *f = TFile::Open(fName);
	TH2F  *h2 = (TH2F*)f->Get("me0SegAna/"+histoName2D);
	cout<<"**************************************************************TH2 PLOTS AND OPTIMIZATION***********************************************************************"<<endl;
	cout<<fName<<endl;
	TString process;
	if(histoName2D.Contains("Signal")) process = "signal";
	if(histoName2D.Contains("Bkg")) process = "bkg";

	cout<<process<<" ME0Segments before the cut ="<< h2->Integral(h2->GetXaxis()->FindBin(-0.05),h2->GetXaxis()->FindBin(0.05), h2->GetYaxis()->FindBin(18.3-12.5),h2->GetYaxis()->FindBin(18.3+12.5))<<std::endl;	
	cout<<process<<" ME0Segments passing the cut ="<< h2->Integral(h2->GetXaxis()->FindBin(-0.01),h2->GetXaxis()->FindBin(0.01), h2->GetYaxis()->FindBin(17),h2->GetYaxis()->FindBin(19))<<std::endl;
	cout<<process<<"Cut Eff="<< h2->Integral(h2->GetXaxis()->FindBin(-0.01),h2->GetXaxis()->FindBin(0.01), h2->GetYaxis()->FindBin(17),h2->GetYaxis()->FindBin(19))/h2->Integral(h2->GetXaxis()->FindBin(-0.05),h2->GetXaxis()->FindBin(0.05), h2->GetYaxis()->FindBin(18.3-12.5),h2->GetYaxis()->FindBin(18.3+12.5))<<endl;
//	double cutPhiMin=h2->GetXaxis()->FindBin(-0.02);
//	double cutPhiMax=h2->GetXaxis()->FindBin(0.02);
	
	//double cutTMin=h2->GetYaxis()->FindBin(18.3-3*timeRes);
	//double cutTMax=h2->GetYaxis()->FindBin(18.3+3*timeRes);
		double cutTMin=h2->GetYaxis()->FindBin(17);
		double cutTMax=h2->GetYaxis()->FindBin(19);
		cout<<" timeRes="<<	timeRes<<" cut in ["<< 18.3-3*timeRes<<", "<<18.3+3*timeRes<<"]"<<endl;
	TH1D *py = h2->ProjectionX("py",cutTMin ,cutTMax);
//	TH1D *px = h2->ProjectionY("py",cutTMin ,cutTMax);	
//	TCanvas * c2 = new TCanvas("c2","h",700, 600);
//	py->Draw();
//	c2->SaveAs("PlotME02/"+titleforSave+"_py.png");	
		
	return py;
		
	
}

void PlotTH2(TString fName, TString histoName2D, TString labelX, TString labelY, TString titleforSave, float timeRes){
	
	TFile *f = TFile::Open(fName);
	TH2F  *h2 = (TH2F*)f->Get("me0SegAna/"+histoName2D);
	TCanvas * c = new TCanvas("c","histo",700, 600);
	h2->RebinX(10);
	h2->GetYaxis()->SetRangeUser(10,40);
	h2->GetXaxis()->SetTitle(labelX);
	h2->GetYaxis()->SetTitle(labelY);
	h2->Draw("colz");
   // cout<<" bin = "<<h2->GetXaxis()->FindBin(0.01)<<" center="<<h2->GetXaxis()->GetBinCenter(h2->GetXaxis()->FindBin(0.01))<<" binc="<<h2->GetBinContent(h2->GetXaxis()->FindBin(0.01),h2->GetYaxis()->FindBin(18.1))<<std::endl;

	
/*
	double cutPhiMin=h2->GetXaxis()->FindBin(-0.02);
	double cutPhiMax=h2->GetXaxis()->FindBin(0.02);
	
	double cutTMin=h2->GetYaxis()->FindBin(18.3-3*timeRes);
	double cutTMax=h2->GetYaxis()->FindBin(18.3+3*timeRes);	
	
	TH1D *py = h2->ProjectionX("py",cutTMin ,cutTMax);
	TCanvas * c2 = new TCanvas("c2","h",700, 600);
	py->Draw();
 	c2->SaveAs("PlotME02/"+titleforSave+"_py.png");
 */
	

	c->SaveAs("PlotME02/"+titleforSave+".png");

	
}


void GetOverlayPlot(){
/*
	
	std::vector<TString> histoNameForOverlay;
	histoNameForOverlay.push_back("hTimeMatchByHitsME0Seg_Signal");
	histoNameForOverlay.push_back("hTimeMatchByHitsME0Seg_Bkg");
	Overlay( "histoME0SegMuGun_AllPt_PU200Bkg_14June_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,"ME0SegmentTime_SignalVSBkg_pt5_100ps");
	
	
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,"ME0SegmentTime_SignalVSBkg_pt5_100ps");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,   "ME0SegmentTime_SignalVSBkg_pt5_1ns");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,   "ME0SegmentTime_SignalVSBkg_pt5_5ns");
	
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,"ME0SegmentTime_SignalVSBkg_pt30_100ps");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,   "ME0SegmentTime_SignalVSBkg_pt30_1ns");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay, "ME0Segment time [ns]", 5., 40.,   "ME0SegmentTime_SignalVSBkg_pt30_5ns");
	

	std::vector<TString> histoNameForOverlay2;
	histoNameForOverlay2.push_back("hDPhiMatchByHitsME0Seg_Signal");
	histoNameForOverlay2.push_back("DPhiMatchByHitsME0Seg_Bkg");
	
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay2, "#Delta#Phi[L1,L6]", -0.05, 0.05,   "ME0SegmentDPhi_SignalVSBkg_pt5_100ps");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay2, "ME0Segment time [ns]",  -0.05, 0.05,  "ME0SegmentDPhi_SignalVSBkg_pt5_1ns");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay2, "ME0Segment time [ns]",  -0.05, 0.05,   "ME0SegmentDPhi_SignalVSBkg_pt5_5ns");
	
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay2, "ME0Segment time [ns]",  -0.05, 0.05,"ME0SegmentDPhi_SignalVSBkg_pt30_100ps");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay2, "ME0Segment time [ns]",  -0.05, 0.05,   "ME0SegmentDPhi_SignalVSBkg_pt30_1ns");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay2, "ME0Segment time [ns]",  -0.05, 0.05,  "ME0SegmentDPhi_SignalVSBkg_pt30_5ns");
	
	std::vector<TString> histoNameForOverlay3;
	histoNameForOverlay3.push_back("hDPhiMatchByHitsME0Seg_Signal_timeCut");
	histoNameForOverlay3.push_back("DPhiMatchByHitsME0Seg_Bkg_timeCut");
	
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay3, "#Delta#Phi[L1,L6]",   -0.05, 0.05,   "ME0SegmentDPhi_TimeCut_SignalVSBkg_pt5_100ps");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay3, "ME0Segment time [ns]",  -0.05, 0.05,  "ME0SegmentDPhi_TimeCut_SignalVSBkg_pt5_1ns");
	Overlay( "histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay3, "ME0Segment time [ns]",  -0.05, 0.05,   "ME0SegmentDPhi_TimeCut_SignalVSBkg_pt5_5ns");
	
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root",histoNameForOverlay3, "ME0Segment time [ns]",  -0.05, 0.05,"ME0SegmentDPhi_TimeCut_SignalVSBkg_pt30_100ps");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root",histoNameForOverlay3, "ME0Segment time [ns]",  -0.05, 0.05,   "ME0SegmentDPhi_TimeCut_SignalVSBkg_pt30_1ns");
	Overlay( "histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root",histoNameForOverlay3, "ME0Segment time [ns]",  -0.05, 0.05,  "ME0SegmentDPhi_TimeCut_SignalVSBkg_pt30_5ns");
	*/
	
	
	
}




////////////////
void GetEffDPhiCut(){
	std::vector<TString> FilenameVec, label, histoNameVec;
	TString Title="Bkg_5ns";
	
	//FilenameVec.push_back("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root");    label.push_back("100ps_30GeV");
	//FilenameVec.push_back("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root");     label.push_back("#sigmaT=1ns, 30GeV");	
	FilenameVec.push_back("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root");      label.push_back("#sigmaT=5ns, 30GeV");
	//FilenameVec.push_back("histoME0SegMuGunPt30_AllEtaPhi_500um500um.root");      label.push_back("#sigmaT=1ns, 30GeV, PU=0, noBkg");
	
	//FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root");    label.push_back("100ps_5GeV");
	//FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root");     label.push_back("#sigmaT=1ns,5GeV");	
	FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root");      label.push_back("#sigmaT=5ns,5GeV");
	//FilenameVec.push_back("histoME0SegMuGunPt5_AllEtaPhi_500um500um.root");      label.push_back("#sigmaT=1ns,5GeV, PU=0, noBkg");	
	
	
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal_timeCut");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg_timeCut");
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg");
	TCanvas * CanvEff = new TCanvas("CanvEff","CEff",800,600);
	std::vector<TGraph *> graphEff;
	//for(int i=0; i<histoNameVec.size(); i++){
		graphEff = PlotEff("DPhiMatchByHitsME0Seg_Bkg", FilenameVec, label);
	//	graphEff[i]->SetLineColor(i);
		
//	}
	CanvEff->SetGridx();
	CanvEff->SetGridy();
	CanvEff->cd();
	//graphEff[0]->SetLineColor(1);
	//graphEff[0]->SetLineColor(2);
	
	graphEff[0]->SetMarkerColor(3);
	graphEff[0]->SetMarkerStyle(8);
	graphEff[0]->SetMarkerSize(0.5);
	
	graphEff[1]->SetMarkerColor(4);
	graphEff[1]->SetMarkerStyle(8);
	graphEff[1]->SetMarkerSize(0.5);
	
	graphEff[0]->Draw("ACP*");
	graphEff[1]->Draw("P");
//	graphEff[2]->Draw("PSAME");
//	graphEff[3]->Draw("SpAME");
	graphEff[0]->GetXaxis()->SetTitle("#Delta #Phi(L1,L6)^{cut}");
	graphEff[0]->GetYaxis()->SetTitle("#epsilon (#Delta#Phi > #Delta#Phi(L1,L6)^{cut})");
	graphEff[0]->SetTitle(Title);
	
	TLegend* legend = new TLegend(0.6, 0.45, 0.9, 0.15);
//	legend->SetHeader("Sign");
	legend->SetFillColor(0);
	legend->SetTextSize(0.025);
	legend->AddEntry(graphEff[0], label[0], "p");
	legend->AddEntry(graphEff[1], label[1], "p");
	legend->Draw("same");
	CanvEff->SaveAs("PlotEff/"+Title+".pdf");
	
}	

///////////////
void GetPlotAnalisi(){
	std::vector<TString> FilenameVec, label, histoNameVec;
	FilenameVec.push_back("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root");    label.push_back("#sigmaT=100ps, 30GeV,  PU200");
	//FilenameVec.push_back("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root");     label.push_back("#sigmaT=1ns, 30GeV");	
	//FilenameVec.push_back("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root");      label.push_back("#sigmaT=5ns, 30GeV");
	//FilenameVec.push_back("histoME0SegMuGunPt30_AllEtaPhi_500um500um.root");      label.push_back("#sigmaT=1ns, 30GeV, PU=0, noBkg");
	
	FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root");    label.push_back("#sigmaT=100ps,5GeV, PU200");
	//FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root");     label.push_back("#sigmaT=1ns,5GeV");	
	//FilenameVec.push_back("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root");      label.push_back("#sigmaT=5ns,5GeV");
	//FilenameVec.push_back("histoME0SegMuGunPt5_AllEtaPhi_500um500um.root");      label.push_back("#sigmaT=1ns,5GeV, PU=0, noBkg");	
	
	
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal_timeCut");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg_timeCut");
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg");
		
	
	/*histoNameVec.push_back("hDPhi");
	histoNameVec.push_back("hDPhiPos");
	histoNameVec.push_back("hDPhiNeg");*/
	/*
	histoNameVec.push_back("hSimDPhi");
	histoNameVec.push_back("hSimDPhiPos");
	histoNameVec.push_back("hSimDPhiNeg");
	histoNameVec.push_back("hDX");
	histoNameVec.push_back("hme0machtMuonPt");
	histoNameVec.push_back("hme0machtMuonEta");
	histoNameVec.push_back("hme0machtMuonPhi");
	histoNameVec.push_back("hme0machtMuonCharge");
	histoNameVec.push_back("hNME0Time");
	histoNameVec.push_back("hNME0RecHits");
	histoNameVec.push_back("hMuonRecHitTime");

	
	histoNameVec.push_back("hDPhiNoMatch");
	histoNameVec.push_back("hTimeDiffSigvsBkg");
	histoNameVec.push_back("hDPhiNoMatch_TimeWindow");
	histoNameVec.push_back("hDPhiNoMatch_TimeWindowTightID");
	histoNameVec.push_back("hDPhiNoMatchME0Seg");	histoNameVec.push_back("hNPU");
	histoNameVec.push_back("hNME0Segment");
	histoNameVec.push_back("hTightME0SegmDigiHitTOF_prompt");
	histoNameVec.push_back("hTightME0SegmDigiHitPdgID_prompt");*/
	
	/*histoNameVec.push_back("hAllME0SegmentTime");
	histoNameVec.push_back("hAllME0SegmentTimeErr");
	histoNameVec.push_back("hME0SegmentCollectionTime");
	histoNameVec.push_back("hDigiHitType");
	histoNameVec.push_back("hDigiHitPdgID");
	histoNameVec.push_back("hDigiHitToF_prompt");
	histoNameVec.push_back("hDigiHitToF_noprompt");
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg");
	histoNameVec.push_back("hDPhiMatchByHitsME0Seg_Signal_timeCut");
	histoNameVec.push_back("DPhiMatchByHitsME0Seg_Bkg_timeCut");
	histoNameVec.push_back("hTimeMatchByHitsME0Seg_Signal");	
	histoNameVec.push_back("hTimeMatchByHitsME0Seg_Bkg");
	histoNameVec.push_back("hNME0SegmentSignal");
	histoNameVec.push_back("hNME0SegmentBkg");
	histoNameVec.push_back("hNME0SegmentSignal_timeCut");
	histoNameVec.push_back("hNME0SegmentBkg_timeCut");
*/
	/*
	
	histoNameVec.push_back("hDeltaPhiSimReco");
	histoNameVec.push_back("hDeltaEtaSimReco");
	histoNameVec.push_back("hDeltaXSimReco");
	histoNameVec.push_back("hDeltaYSimReco");
	histoNameVec.push_back("hDeltaXSimRecoLocal");
	histoNameVec.push_back("hDeltaYSimRecoLocal");
	*/
	
	//	histoNameVec.push_back("hRecDPhiOverSimDphi");
	
	
	for(int i=0; i<histoNameVec.size(); i++){
	PlotAnalisi(histoNameVec[i], FilenameVec, label);
	}
	
}

void MakeTH2Plot(){
	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt5_5ns", 5.);
	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt5_5ns",5.);

	
	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt5_1ns", 1.);
	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt5_1ns",1.);
	

	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt5_100ps", 0.1);
	PlotTH2("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Signal","#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt5_100ps",0.1);
	
	///////////
	
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt30_5ns", 5.);
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt30_5ns",5.);
	
	
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt30_1ns", 1.);
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt30_1ns",1.);
	
	
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", "#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Bkg_pt30_100ps", 0.1);
	PlotTH2("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Signal","#Delta#Phi(L1,L6) [rad]", "ME0Segment time[ns]", "ME0SegmentTimevsDPhiL1L6_Signal_pt30_100ps",0.1);
	
	
}

void GetSigVSBkg(){
	
	TH1D * hSignal_Pt5_100ps = GiveProjection("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 0.1); 
	TH1D * hBkg_Pt5_100ps    = GiveProjection("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 0.1); 
	
	TH1D * hSignal_Pt5_1ns = GiveProjection("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 1); 
	TH1D * hBkg_Pt5_1ns    = GiveProjection("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 1); 
	
	TH1D * hSignal_Pt5_5ns = GiveProjection("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 5); 
	TH1D * hBkg_Pt5_5ns    = GiveProjection("histoME0SegMuGun_Pt5_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 5); 
	
	TH1D * hSignal_Pt30_100ps = GiveProjection("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 0.1); 
	TH1D * hBkg_Pt30_100ps    = GiveProjection("histoME0SegMuGun_AllPtAllEtaPhi_500um500um_100ps.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 0.1); 
	
	TH1D * hSignal_Pt30_1ns = GiveProjection("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 1); 
	TH1D * hBkg_Pt30_1ns    = GiveProjection("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_1ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 1); 
	
	TH1D * hSignal_Pt30_5ns = GiveProjection("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Signal", 5); 
	TH1D * hBkg_Pt30_5ns    = GiveProjection("histoME0SegMuGun_Pt30_PU200Bkg_30May_AllEtaPhi_500um500um_5ns.root", "hDPhivsTOFMatchByHitsME0Seg_Bkg", 5); 

	
	std::vector<TH1D*> histoSig;
	histoSig.push_back(hSignal_Pt5_100ps); histoSig.push_back(hSignal_Pt5_1ns); histoSig.push_back(hSignal_Pt5_5ns);
	histoSig.push_back(hSignal_Pt30_100ps); histoSig.push_back(hSignal_Pt30_1ns); histoSig.push_back(hSignal_Pt30_5ns);
	
	std::vector<TH1D*> histoBkg;
	histoBkg.push_back(hBkg_Pt5_100ps); histoBkg.push_back(hBkg_Pt5_1ns); histoBkg.push_back(hBkg_Pt5_5ns); 
	histoBkg.push_back(hBkg_Pt30_100ps); histoBkg.push_back(hBkg_Pt30_1ns); histoBkg.push_back(hBkg_Pt30_5ns);
	
	TCanvas * cc = new TCanvas("cc","cc", 500, 500);
	TCanvas * cc1 = new TCanvas("cc1","cc1", 500, 500);
	cc1->Divide(1,3);
	cc->Divide(1,3);
	
	
	for(int i=0; i<histoBkg.size(); i++){
		cout<<" after time cut: S/N="<<histoSig[i]->Integral()/histoBkg[i]->Integral()<<" s="<<histoSig[i]->Integral()<<"  b="<<histoBkg[i]->Integral()<<endl;
		histoSig[i]->SetLineColor(2);
		histoBkg[i]->SetLineColor(1);
		histoSig[i]->Scale(1/(histoSig[i]->Integral()+histoBkg[i]->Integral()));
		histoBkg[i]->Scale(1/(histoSig[i]->Integral()+histoBkg[i]->Integral()));
		histoSig[i]->Rebin(2);
		histoBkg[i]->Rebin(2);
		histoSig[i]->GetXaxis()->SetRangeUser(-0.01, 0.01);
		histoBkg[i]->GetXaxis()->SetRangeUser(-0.01, 0.01);
		histoSig[i]->GetXaxis()->SetTitle("#Delta#Phi(L1,L6)");
		histoBkg[i]->GetXaxis()->SetTitle("#Delta#Phi(L1,L6)");
//		histoSig[i]->GetYaxis()->SetTitle("");
//		histoBkg[i]->GetYaxis()->SetTitle("");
	}

	
	/*cout<<"pt=5GeV-- sigmaT=100ps after time cut: S/N="<<hSignal_Pt5_100ps->Integral()/hBkg_Pt5_100ps->Integral()<<" s="<<hSignal_Pt5_100ps->Integral()<<"  b="<<hBkg_Pt5_100ps->Integral()<<endl;
	cout<<"pt=5GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt5_1ns->Integral()/hBkg_Pt5_1ns->Integral()<<" s="<<hSignal_Pt5_1ns->Integral()<<"  b="<<hBkg_Pt5_1ns->Integral()<<endl;
	cout<<"pt=5GeV-- sigmaT=5ns after time cut: S/N="<<hSignal_Pt5_5ns->Integral()/hBkg_Pt5_5ns->Integral()<<" s="<<hSignal_Pt5_5ns->Integral()<<"  b="<<hBkg_Pt5_5ns->Integral()<<endl;
	
	cout<<"pt=30GeV-- sigmaT=100ps after time cut: S/N="<<hSignal_Pt30_100ps->Integral()/hBkg_Pt30_100ps->Integral()<<" s="<<hSignal_Pt30_100ps->Integral()<<"  b="<<hBkg_Pt30_100ps->Integral()<<endl;
	cout<<"pt=30GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt30_1ns->Integral()/hBkg_Pt30_1ns->Integral()<<" s="<<hSignal_Pt30_1ns->Integral()<<"  b="<<hBkg_Pt30_1ns->Integral()<<endl;
	cout<<"pt=30GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt30_5ns->Integral()/hBkg_Pt30_5ns->Integral()<<" s="<<hSignal_Pt30_5ns->Integral()<<"  b="<<hBkg_Pt30_5ns->Integral()<<endl;*/
	
	

	
	cout<<"pt=5GeV-- sigmaT=100ps after time cut: S/N="<<hSignal_Pt5_100ps->Integral()/hBkg_Pt5_100ps->Integral()<<" s="<<hSignal_Pt5_100ps->Integral()<<"  b="<<hBkg_Pt5_100ps->Integral()<<endl;
	cout<<"pt=5GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt5_1ns->Integral()/hBkg_Pt5_1ns->Integral()<<" s="<<hSignal_Pt5_1ns->Integral()<<"  b="<<hBkg_Pt5_1ns->Integral()<<endl;
	cout<<"pt=5GeV-- sigmaT=5ns after time cut: S/N="<<hSignal_Pt5_5ns->Integral()/hBkg_Pt5_5ns->Integral()<<" s="<<hSignal_Pt5_5ns->Integral()<<"  b="<<hBkg_Pt5_5ns->Integral()<<endl;
	
	cout<<"pt=30GeV-- sigmaT=100ps after time cut: S/N="<<hSignal_Pt30_100ps->Integral()/hBkg_Pt30_100ps->Integral()<<" s="<<hSignal_Pt30_100ps->Integral()<<"  b="<<hBkg_Pt30_100ps->Integral()<<endl;
	cout<<"pt=30GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt30_1ns->Integral()/hBkg_Pt30_1ns->Integral()<<" s="<<hSignal_Pt30_1ns->Integral()<<"  b="<<hBkg_Pt30_1ns->Integral()<<endl;
	cout<<"pt=30GeV-- sigmaT=1ns after time cut: S/N="<<hSignal_Pt30_5ns->Integral()/hBkg_Pt30_5ns->Integral()<<" s="<<hSignal_Pt30_5ns->Integral()<<"  b="<<hBkg_Pt30_5ns->Integral()<<endl;
	
							
	
	cc->cd(1);
	histoSig[0]->Draw();
	histoBkg[0]->Draw("same");
	cc->cd(2);
	//if(hBkg_Pt5_1ns->GetMaximum() > hSignal_Pt5_1ns->GetMaximum()){
	histoBkg[1]->Draw();
	histoSig[1]->Draw("same");
	histoBkg[1]->SetMinimum(0.);
	//}
	//if(hBkg_Pt5_1ns->GetMaximum() < hSignal_Pt5_1ns->GetMaximum()){
	//	hSignal_Pt5_1ns->Draw();
	//	hBkg_Pt5_1ns->Draw("same");
	//}
	cc->cd(3);
//	if(hBkg_Pt5_5ns->GetMaximum() > hSignal_Pt5_5ns->GetMaximum()){
	histoBkg[2]->Draw();
	histoSig[2]->Draw("same");
	histoBkg[2]->SetMinimum(0.);
//	}
//	if(hBkg_Pt5_5ns->GetMaximum() < hSignal_Pt5_5ns->GetMaximum()){
	//	hSignal_Pt5_5ns->Draw();
	//	hBkg_Pt5_5ns->Draw("same");
		
	//}
	

	cc->SaveAs("PlotME02/palle.pdf");
	
	//////////

		
	
	cc1->cd(1);
	histoSig[3]->Draw();
	histoBkg[3]->Draw("same");
	cc1->cd(2);
	//if(hBkg_Pt5_1ns->GetMaximum() > hSignal_Pt5_1ns->GetMaximum()){
	histoSig[4]->Draw();
	histoBkg[4]->Draw("same");

	//}
	//if(hBkg_Pt5_1ns->GetMaximum() < hSignal_Pt5_1ns->GetMaximum()){
	//	hSignal_Pt5_1ns->Draw();
	//	hBkg_Pt5_1ns->Draw("same");
	//}
	cc1->cd(3);
	//	if(hBkg_Pt5_5ns->GetMaximum() > hSignal_Pt5_5ns->GetMaximum()){
	histoSig[5]->Draw();
	histoBkg[5]->Draw("same");
	
	//	}
	//	if(hBkg_Pt5_5ns->GetMaximum() < hSignal_Pt5_5ns->GetMaximum()){
	//	hSignal_Pt5_5ns->Draw();
	//	hBkg_Pt5_5ns->Draw("same");
	
	//}
	
	
	
	cc1->SaveAs("PlotME02/palle2.png");
	cc1->SaveAs("PlotME02/palle2.pdf");
	
	


}

void GetTriggerEff(){

	std::vector<TString> fName, label;
//	fName.push_back("histoME0SegDY_3June_PU200_100ps.root");  label.push_back("PU200_100ps");
	fName.push_back("histoME0SegDY_prova100ps.root");  label.push_back("PU200_100ps");
	 
	fName.push_back("histoME0SegDY_3June_PU200_1ns.root");    label.push_back("PU200_1ns");
	fName.push_back("histoME0SegDY_3June_PU200_5ns.root");     label.push_back("PU200_5ns"); 
	fName.push_back("histoME0SegDY_3June_PU140_1ns.root");      label.push_back("PU140_1ns");
	
	gStyle->SetOptStat(0);
	std::vector<TH1F*> histoEff_30GeV;
	std::vector<TH1F*> histoEff_5GeV;
//	std::vector<TCanvas*> cTr;
	TLegend* legend = new TLegend(0.55, 0.35, 0.9, 0.15);
	legend->SetFillColor(0);
	
/*	std::vector<TCanvas*> cTr;
	cTr[i] = new TCanvas("cTr","cTr",600, 600);
	cTr[i]->SetGridx();
	cTr[i]->SetGridy();*/
	
	TCanvas * cTr1 = new TCanvas("cTr1","cTr",800, 600);
	TCanvas * cTr2 = new TCanvas("cTr2","cTr",800, 600);
	TCanvas * cTr3 = new TCanvas("cTr3","cTr",800, 600);
	TCanvas * cTr4 = new TCanvas("cTr4","cTr",800, 600);
	
	for(int i=0; i < fName.size(); i++ ){
		//histoEff_5GeV.clear();
		//histoEff_30GeV.clear();
		
		histoEff_5GeV.push_back(	Divide(fName[i], "hSimMuonPt_DPhiCut5GeV", "hSimPt"));
		histoEff_30GeV.push_back(	Divide(fName[i], "hSimMuonPt_DPhiCut30GeV", "hSimPt"));
	
		histoEff_5GeV[i]->SetMarkerStyle(20);
		histoEff_30GeV[i]->SetMarkerStyle(20);
		histoEff_5GeV[i]->SetMarkerColor(2);
		histoEff_30GeV[i]->SetMarkerColor(3);
		histoEff_5GeV[i]->GetXaxis()->SetRangeUser(0, 50);
		histoEff_30GeV[i]->GetXaxis()->SetRangeUser(0, 50);
		
		histoEff_5GeV[i]->SetTitle(label[i]);
		histoEff_30GeV[i]->SetTitle(label[i]);
		
		histoEff_5GeV[i]->GetXaxis()->SetTitle("p_{T}^{sim}");
		histoEff_5GeV[i]->GetYaxis()->SetTitle("|#Delta#Phi(L1,L6)|< |#Delta#Phi_{0}^{p_{T}>p_{T}^{min}}| Cut Efficiency");
		histoEff_5GeV[i]->GetYaxis()->SetTitleOffset(1.4);
		
	}
	
	cTr1->cd();
	cTr1->SetGridx();
	cTr1->SetGridy();
	histoEff_5GeV[0]->Draw("p1");
	histoEff_30GeV[0]->Draw("p1same");
	legend->AddEntry(histoEff_5GeV[0], "#Delta#Phi_{0}^{p_{T}>5 GeV}=0.01 rad", "p"); 
	legend->AddEntry(histoEff_30GeV[0], "#Delta#Phi_{0}^{p_{T}>30 GeV}=0.004 rad", "p");
	legend->Draw("same");
	cTr1->SaveAs(label[0]+".pdf");

	cTr2->cd();
	cTr2->SetGridx();
	cTr2->SetGridy();
	histoEff_5GeV[1]->Draw("p1");
	histoEff_30GeV[1]->Draw("p1same");
	//legend->AddEntry(histoEff_5GeV[1], "#Delta#Phi_{0}^{p_{T}>5 GeV}=0.01 rad", "p"); 
	//legend->AddEntry(histoEff_30GeV[1], "#Delta#Phi_{0}^{p_{T}>30 GeV}=0.004 rad", "p");
	legend->Draw("same");
	cTr1->SaveAs(label[1]+".pdf");
	
	cTr3->cd();
	cTr3->SetGridx();
	cTr3->SetGridy();
	histoEff_5GeV[2]->Draw("p1");
	histoEff_30GeV[2]->Draw("p1same");
	//legend->AddEntry(histoEff_5GeV[2], "#Delta#Phi_{0}^{p_{T}>5 GeV}=0.01 rad", "p"); 
	//legend->AddEntry(histoEff_30GeV[2], "#Delta#Phi_{0}^{p_{T}>30 GeV}=0.004 rad", "p");
	legend->Draw("same");
	cTr1->SaveAs(label[2]+".pdf");
	
	cTr4->cd();
	cTr4->SetGridx();
	cTr4->SetGridy();
	histoEff_5GeV[3]->Draw("p1");
	histoEff_30GeV[3]->Draw("p1same");
	//legend->AddEntry(histoEff_5GeV[3], "#Delta#Phi_{0}^{p_{T}>5 GeV}=0.01 rad", "p"); 
	//legend->AddEntry(histoEff_30GeV[3], "#Delta#Phi_{0}^{p_{T}>30 GeV}=0.004 rad", "p");
	legend->Draw("same");
	cTr1->SaveAs(label[3]+".pdf");
	
	//Divide(fName[i], "hSimMuonPt_DPhiCut5GeV", "hSimPt")
	
	}

void  GetRate(){
	std::vector<TString> fName, label;
	fName.push_back("histoME0SegDY_3June_PU200_100ps.root");  label.push_back("PU200_100ps");
	//fName.push_back("histoME0SegDY_prova100ps.root");  label.push_back("PU200_100ps");
	cout<<"***************30GeV cut*****************"<<endl;
	GiveRate(fName[0], "hEventPass30GeVCut", "hNEv");
	cout<<"***************5GeV cut*****************"<<endl;
	GiveRate(fName[0], "hEventPass5GeVCut", "hNEv");

}


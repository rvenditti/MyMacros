#include <TH1.h>
#include <string>
#include <vector>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TFile.h>

void PlotValidation(TString fName1, TString fName2,  TString fName3, TString fName4, TString fName5, TString fName6,
					
					TString label1, TString label2, TString label3, TString label4, TString label5, TString label6){
	
	//	gROOT->ProcessLine(".L ./tdrstyle.C");
	//setTDRStyle();
	//gStyle->SetOptStat(00000001111);	
	gStyle->SetOptStat("nemr");
	

	TFile *f1 = TFile::Open(fName1);
	TFile *f2 = TFile::Open(fName2);  
	TFile *f3 = TFile::Open(fName3);
	
	TFile *f4 = TFile::Open(fName4);
	TFile *f5 = TFile::Open(fName5);
	TFile *f6 = TFile::Open(fName6);
	
	std::vector<TString> histoName;
	
	
	histoName.push_back("digiDPhi");
	histoName.push_back("digiDPhi_pos");
	histoName.push_back("digiDPhi_neg");

	histoName.push_back("digiDX");
	histoName.push_back("digiDY");


	int numHisto = histoName.size();
	TH1F* histo1[100];
	TH1F* histo2[100];
	TH1F* histo3[100];
	TH1F* histo4[100];
	TH1F* histo5[100];
	TH1F* histo6[100];
	
	
	TCanvas* CanvVector[100];
	TCanvas * cDphi = new TCanvas("cDphi","cDphi",700, 600);
	
	
	
	for(int i=0;i<numHisto; i++){
		
		histo1[i] = (TH1F*)f1->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		histo2[i] = (TH1F*)f2->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		histo3[i] = (TH1F*)f3->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		histo4[i] = (TH1F*)f4->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		histo5[i] = (TH1F*)f5->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		histo6[i] = (TH1F*)f6->Get("DQMData/MuonME0DigisV/ME0DigiTask/"+histoName[i]);
		cout<<i<<" histo name "<<histoName[i]<<endl;	
		
		histo1[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo2[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo3[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo4[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo5[i]->GetYaxis()->SetTitle("Fraction of muons");
		histo6[i]->GetYaxis()->SetTitle("Fraction of muons");
		
		
		histo1[i]->Scale(1/histo1[i]->Integral());
		histo2[i]->Scale(1/histo2[i]->Integral());
		histo3[i]->Scale(1/histo3[i]->Integral());
		histo4[i]->Scale(1/histo4[i]->Integral());
		histo5[i]->Scale(1/histo5[i]->Integral());
		histo6[i]->Scale(1/histo6[i]->Integral());
		
		
		histo1[i]->SetLineColor(kBlue);			histo1[i]->SetLineWidth(2);	
		
		histo2[i]->SetLineColor(kRed);			histo2[i]->SetLineWidth(2);	
		
		histo3[i]->SetLineColor(kGreen);	   histo3[i]->SetLineWidth(2);	
		
		histo4[i]->SetLineColor(1);	   histo4[i]->SetLineWidth(2);	
		histo5[i]->SetLineColor(kViolet);	   histo5[i]->SetLineWidth(2);	
		histo6[i]->SetLineColor(kOrange);	   histo6[i]->SetLineWidth(2);	
		
		
		
		TLegend* legend = new TLegend(0.10, 0.60, 0.38, 0.30);
		//  legend->SetHeader((categories.at(j)).c_str());
		legend->SetFillColor(0);
		legend->SetTextSize(0.036);
		legend->AddEntry( histo1[i] , label1 , "l");
		legend->AddEntry( histo2[i] , label2 , "l");
		legend->AddEntry( histo3[i] , label3 , "l");
		legend->AddEntry( histo4[i] , label4 , "l");
		legend->AddEntry( histo5[i] , label5 , "l");
		legend->AddEntry( histo6[i] , label6 , "l");
		
		TString titleCanv ("CanvVector"); titleCanv+=(i+1);	
		CanvVector[i] = new TCanvas("titleCanv", "titleCanv", 700, 500);
		
		
//		if(histo1[i]->GetMaximum() > histo2[i]->GetMaximum())  histo1[i]->SetMaximum(1.5*histo1[i]->GetMaximum());
//		if(histo2[i]->GetMaximum() < histo1[i]->GetMaximum())  histo2[i]->SetMaximum(1.5*histo2[i]->GetMaximum());
		
		CanvVector[i]->cd();		

		
		if(histo1[i]->GetMaximum() > histo2[i]->GetMaximum()) {
			histo1[i]->Draw("hists");
			histo2[i]->Draw("histsames");
			histo3[i]->Draw("histsames");
			histo4[i]->Draw("histsames");
			histo5[i]->Draw("histsames");
			histo6[i]->Draw("histsames");
			
			histo1[i]->SetMaximum(1.15*histo1[i]->GetMaximum());
		}
		
		
		if(histo1[i]->GetMaximum() < histo2[i]->GetMaximum()) {
			histo2[i]->Draw("hists");
			histo1[i]->Draw("histsames");
			histo3[i]->Draw("histsames");
			histo4[i]->Draw("histsames");
			histo5[i]->Draw("histsames");
			histo6[i]->Draw("histsames");
			
			histo2[i]->SetMaximum(1.15*histo2[i]->GetMaximum());
		}
		

		if(histoName[i].Contains("DPhi")){
			
			histo1[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			histo2[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			histo3[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			histo4[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			histo5[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			histo6[i]->GetXaxis()->SetRangeUser(-0.01,0.01);
			
		
		}
		
		if(histoName[i].Contains("DX")  ){
			
			histo1[i]->GetXaxis()->SetRangeUser(-2,2);
			histo2[i]->GetXaxis()->SetRangeUser(-2,2);
			histo3[i]->GetXaxis()->SetRangeUser(-2,2);
			histo4[i]->GetXaxis()->SetRangeUser(-2,2);
			histo5[i]->GetXaxis()->SetRangeUser(-2,2);
			histo6[i]->GetXaxis()->SetRangeUser(-2,2);
			
			
		}
		
		if(histoName[i].Contains("DY")  ){
			
			histo1[i]->GetXaxis()->SetRangeUser(-10,10);
			histo2[i]->GetXaxis()->SetRangeUser(-10,10);
			histo3[i]->GetXaxis()->SetRangeUser(-10,10);
			histo4[i]->GetXaxis()->SetRangeUser(-10,10);
			histo5[i]->GetXaxis()->SetRangeUser(-10,10);
			histo6[i]->GetXaxis()->SetRangeUser(-10,10);
			
			
		}
		
		
		gPad->Update();
        
		if((histo1[i]->Integral()) >0  && (histo2[i]->Integral() >0 )){
			TPaveStats* st20 = (TPaveStats*) histo1[i]->FindObject("stats");
			st20->SetX1NDC(0.80);
			st20->SetX2NDC(0.99);
			st20->SetY1NDC(0.95);
			st20->SetY2NDC(0.80);
			st20->SetTextColor(kBlue);
			st20->Draw();
			gPad->Update();
			
			
			TPaveStats* st21 = (TPaveStats*) histo2[i]->FindObject("stats");
			st21->SetX1NDC(0.80);
			st21->SetX2NDC(0.99);
			st21->SetY1NDC(0.80);
			st21->SetY2NDC(0.65);
			st21->SetTextColor(1);
			st21->SetTextColor(kRed);
			
			st21->Draw();
			gPad->Update();
			
			TPaveStats* st22 = (TPaveStats*) histo3[i]->FindObject("stats");
			st22->SetX1NDC(0.80);
			st22->SetX2NDC(0.99);
			st22->SetY1NDC(0.20);
			st22->SetY2NDC(0.05);
			st22->SetTextColor(1);
			st22->SetTextColor(kGreen);
			
			st22->Draw();
			gPad->Update();
			
			TPaveStats* st23 = (TPaveStats*) histo4[i]->FindObject("stats");
			st23->SetX1NDC(0.80);
			st23->SetX2NDC(0.99);
			st23->SetY1NDC(0.65);
			st23->SetY2NDC(0.50);
			st23->SetTextColor(1);
			st23->SetTextColor(1);
			
			st23->Draw();
			gPad->Update();
			
			TPaveStats* st24 = (TPaveStats*) histo5[i]->FindObject("stats");
			st24->SetX1NDC(0.80);
			st24->SetX2NDC(0.99);
			st24->SetY1NDC(0.50);
			st24->SetY2NDC(0.35);
			st24->SetTextColor(1);
			st24->SetTextColor(kViolet);
			
			st24->Draw();
			gPad->Update();
			
			TPaveStats* st25 = (TPaveStats*) histo6[i]->FindObject("stats");
			st25->SetX1NDC(0.80);
			st25->SetX2NDC(0.99);
			st25->SetY1NDC(0.35);
			st25->SetY2NDC(0.20);
			st25->SetTextColor(1);
			st25->SetTextColor(kOrange);
			
			st25->Draw();
			gPad->Update();
			
		}
		legend->Draw("same");
		
		CanvVector[i]->SaveAs("ValidationPlots/"+ histoName[i]+".pdf");
		

		
		
	}		
	
	
}

void PlotTH2(TString fName){
	TFile *f = TFile::Open(fName);
	TH2F  *h2 = (TH2F*)f->Get("DQMData/MuonME0DigisV/ME0DigiTask/DPhiSimRecovsPhi");
	TCanvas * c = new TCanvas("c","DPhiSimVsReco",700, 600);
	//h2->RebinX(2);
	h2->GetYaxis()->SetRangeUser(-0.01,0.01);
	h2->GetXaxis()->SetTitle("#Phi^{sim} [rad]");
	h2->GetYaxis()->SetTitle("#Phi^{sim}-#Phi^{digi} [rad]");
	h2->Draw("colz");
	c->SaveAs("ValidationPlots/DPhiSimRecovsPhi_"+fName+".pdf");
	
}




void GetPlotValidation(){

	
	
	PlotValidation("ME0Digis_SigmaX500um_SigmaY500um.root", "ME0Digis_SigmaX500um_SigmaY1cm.root", "ME0Digis_SigmaX500um_SigmaY05cm.root", "ME0Digis_SigmaX1cm_SigmaY1cm.root", "ME0Digis_SigmaX01cm_SigmaY1cm.root", "ME0Digis_SigmaX02cm_SigmaY2cm.root", 
				   "#sigma_{x}=500um,#sigma_{y}=500um", "#sigma_{x}=500um,#sigma_{y}=1cm", "#sigma_{x}=500um,#sigma_{y}=0.5cm", "#sigma_{x}=1cm,#sigma_{y}=1cm", "#sigma_{x}=0.1cm,#sigma_{y}=1cm", "#sigma_{x}=0.2cm,#sigma_{y}=2cm");

	PlotTH2("ME0Digis_SigmaX500um_SigmaY500um.root");
	PlotTH2("ME0Digis_SigmaX500um_SigmaY1cm.root");
	
	PlotTH2("ME0Digis_SigmaX1cm_SigmaY1cm.root");
	PlotTH2("ME0Digis_SigmaX2cm_SigmaY2cm.root");

	PlotTH2("ME0Digis_SigmaX02cm_SigmaY2cm.root");
	PlotTH2("ME0Digis_SigmaX01cm_SigmaY1cm.root");
	
	PlotTH2("ME0Digis_SigmaX500um_SigmaY05cm.root");

	
}
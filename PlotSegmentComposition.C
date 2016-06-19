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

void PlotSegmentComposition(TString nomeFile, TString NameforSave){
	
// gROOT->ProcessLine(".L ./tdrstyle.C");
// setTDRStyle();
	gStyle->SetOptStat(0000000000);	
//	gStyle->SetOptStat("nemr");
	
	std::vector<TString> fileName;
	fileName.push_back(nomeFile);
		
	std::vector<TString> histoName;

	histoName.push_back("hNME0SegmentAfterDigiMatch");
	histoName.push_back("hMuOnlyinME0Segm");
	histoName.push_back("hMuEleinME0Segm");
	histoName.push_back("hMuEleOthersinME0Seg");
	
	 
	histoName.push_back("hNEleBrem");
	histoName.push_back("hNEleDeltaRays");
	histoName.push_back("hNEle");
//histoName.push_back(hMatchedSimEleTrack);
	
	TH1F * h1= new TH1F("h1","ME0Segment Composition",3,0,3);
	
	TH1F* histo[18]; TH1F* histo_ev[18];
	
	cout<<" fileName="<<fileName[0]<<std::endl;
	for( int k=1; k<4;k++){
		TFile *f = TFile::Open(fileName[0]);
		f->cd("me0SegAna");
		histo[k] = (TH1F*)f->Get("me0SegAna/"+histoName[k]); 
		histo_ev[k] = (TH1F*)f->Get("me0SegAna/hNME0SegmentAfterDigiMatch");
		//histo_ev[k] = (TH1F*)f->Get("me0SegAna/hNEvZmm");
		cout<<k<<" histoName ="<<histoName[k]<<" Integral="<<histo[k]->Integral()<<" NTotSeg= "<<histo_ev[k]->Integral()<<" ratio="<<histo[k]->Integral()/histo_ev[k]->Integral()<<endl;	
		
		double area=histo_ev[k]->Integral();
		h1->SetBinContent(k,(histo[k]->Integral()/histo_ev[k]->Integral()));
		
		
	}
		
		h1->SetLineColor(k+2);
		h1->SetLineWidth(2);
		//histo[k]->GetXaxis()->SetRangeUser(binMin, binMax);
		h1->GetXaxis()->SetTitle("SegmentComposition");
		h1->GetYaxis()->SetTitle("Fraction of ME0Segments");
		h1->GetYaxis()->SetTitleOffset(1.4);
//		h1->Scale(1/area);
		h1->SetTitle(0);
		
		h1->GetXaxis()->SetBinLabel(1,"Muon Only");
		h1->GetXaxis()->SetBinLabel(2,"Muon+Electrons");
		h1->GetXaxis()->SetBinLabel(3,"Muon+Electrons+pdgID>200");
		
		
		
		
	TCanvas * c1 = new TCanvas("c1","c1",600, 500);
	
	h1->Draw("hist");
	
	TFile* fout = new TFile(NameforSave+".root", "recreate");
	fout->cd();
	h1->Write("h1");
	//fout->Close();
	
	
	//histo[3]->Draw("histsame");	

	/*	
	histo[0]->SetMaximum((histo[2]->GetMaximum())*maxH);
	
	TLegend* legend = new TLegend(0.45, 0.7, 0.9, 0.9);
	legend->SetHeader(descriptionString);
	legend->SetFillColor(0);
	legend->SetTextSize(0.04);
	legend->AddEntry( histo[0] ,"#sigma_{t}=5ns", "l");
	legend->AddEntry( histo[1] ,"#sigma_{t}=1ns", "l");
	legend->AddEntry( histo[2] ,"#sigma_{t}=100ps", "l");
	//legend->AddEntry( histo[3] ,"#sigma_{t}=25ns", "l");
	legend->Draw("same");
	c1->RedrawAxis();
	c1->SaveAs("PlotHits/"+histoNameString+".png");
	c1->SaveAs("PlotHits/"+histoNameString+".pdf");
	*/
	 
	TLatex *   tex = new TLatex(0.89,0.92,"Z #rightarrow #mu#mu, 14 TeV, PU=140, neutron bkg");
	tex->SetNDC();
	tex->SetTextAlign(31);
	tex->SetTextFont(42);
	tex->SetTextSize(0.032);
	tex->SetLineWidth(1);
	tex->Draw();
	tex = new TLatex(0.1,0.96,"CMS Simulation");
	tex->SetNDC();
	tex->SetTextAlign(13);
	tex->SetTextFont(61);
	tex->SetTextSize(0.0472028);
	tex->SetLineWidth(1);
	tex->Draw();
	c1->Modified();
	c1->cd();
	c1->SetSelected(c1);
	c1->RedrawAxis();
	//c2->SaveAs("PlotHits/"+histoNameString+".pdf");
	//c2->SaveAs("PlotHits/"+histoNameString+".png");
	c1->SaveAs(NameforSave+".pdf");
	c1->SaveAs(NameforSave+".png");
	
	
	
	
	TH1F * h2= new TH1F("h2","ME0Segment EleComposition",2,0,2);

	for( int k=4; k<6;k++){
		TFile *f = TFile::Open(fileName[0]);
		f->cd("me0SegAna");
		histo[k] = (TH1F*)f->Get("me0SegAna/"+histoName[k]);
		histo_ev[k] = (TH1F*)f->Get("me0SegAna/hNEle");
		cout<<k<<" elettroni: "<<histoName[k]<<"  int="<< histo[k]->Integral()<<" NTotELE= "<<histo_ev[k]->Integral()<<endl;	
		
		double area=histo_ev[k]->Integral();
				
		
	}
	
	h2->SetBinContent(1,(histo[4]->Integral()/histo_ev[4]->Integral()));
	h2->SetBinContent(2,(histo[5]->Integral()/histo_ev[5]->Integral()));

	
	h2->SetLineColor(k+2);
	h2->SetLineWidth(2);
	//histo[k]->GetXaxis()->SetRangeUser(binMin, binMax);
	//h2->GetXaxis()->SetTitle("Electron");
	h2->GetYaxis()->SetTitle("Fraction of ME0Segments");
	h2->GetYaxis()->SetTitleOffset(1.4);
	h2->SetTitle(0);
	
	h2->GetXaxis()->SetBinLabel(2,"DeltaRays");
	h2->GetXaxis()->SetBinLabel(1,"Bremsstrahlung");

	
	
	
	
	TCanvas * c2 = new TCanvas("c2","c2",600, 500);	
	c2->cd();
	h2->Draw("hist");	
	fout->cd();
	h2->Write("h2");
	
	
	
	TFile *f = TFile::Open(fileName[0]);
	histo[10] = (TH1F*)f->Get("me0SegAna/hMatchedSimEleTrack");
	histo_ev[10] = (TH1F*)f->Get("me0SegAna/hNEle");
	
	histo[10]->SetLineColor(1);
	histo[10]->SetLineWidth(2);
	histo[10]->SetTitle(0);
	histo[10]->GetXaxis()->SetTitle("p_{T}[GeV]");
	histo[10]->GetXaxis()->SetRangeUser(0,1);
	
	TCanvas * c3 = new TCanvas("c3","c3",600, 500);	
	c3->cd();
	histo[10]->Draw();
 

	
}

		
void GetPlotSegm(){
	
	PlotSegmentComposition("histoME0Seg_OldGeo1ns.root", "PlotHits/ME0Segm_SP4");
	PlotSegmentComposition("histoME0Seg_PU140_1ns_newGeo.root", "PlotHits/ME0Segm_SP5");
	//PlotSegmentComposition("histoME0Seg_100ps_Dphi0p02_FullSegAna_500um.root", "PlotHits/ME0Segm_100ps");
	//PlotSegmentComposition("histoME0Seg_25ns_Dphi0p02_FullSegAna_500um.root", "PlotHits/ME0Segm_25ns");

			
	}
	
	
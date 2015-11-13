#include <TH1>
void PlotEff(){
	
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();
	
	TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");  
	TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");  
	TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");
	
	gStyle->SetOptStat(0000000);
	TH1F* hTauGenMatchPt_AfterLooseIso3H = (TH1F*)f1->Get("hTauGenMatchPt_AfterLooseIso3H");
	hTauGenMatchPt_AfterLooseIso3H->Rebin(4);
	TH1F* hGenTauPt = (TH1F*)f1->Get("hTauGenMatchPt"); 
	hGenTauPt->Rebin(4);
	TH1F* EffLooseIso3Hits_Pt =new TH1F("EffLooseIso3Hits_Pt","EffLooseIso3Hits_Pt",50,0,200);
	EffLooseIso3Hits_Pt->Divide(hTauGenMatchPt_AfterLooseIso3H,hGenTauPt, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchEta_AfterLooseIso3H = (TH1F*)f1->Get("hTauGenMatchEta_AfterLooseIso3H");
	hTauGenMatchEta_AfterLooseIso3H->Rebin(2);
	TH1F* hGenTauEta = (TH1F*)f1->Get("hTauGenMatchEta");
	hGenTauEta->Rebin(2);
	TH1F* EffLooseIso3Hits_Eta =new TH1F("EffLooseIso3Hits_Eta","EffLooseIso3Hits_Eta",50,-3,3);
	EffLooseIso3Hits_Eta->Divide(hTauGenMatchEta_AfterLooseIso3H,hGenTauEta, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchPhi_AfterLooseIso3H = (TH1F*)f1->Get("hTauGenMatchPhi_AfterLooseIso3H");
	TH1F* hGenTauPhi = (TH1F*)f1->Get("hTauGenMatchPhi");
	TH1F* EffLooseIso3Hits_Phi =new TH1F("EffLooseIso3Hits_Phi","EffLooseIso3Hits_Phi",100,-3,3);
	EffLooseIso3Hits_Phi->Divide(hTauGenMatchPhi_AfterLooseIso3H,hGenTauPhi, 1. ,  1. , "B");
	
	TH1F* hOfflinePV_AfterLooseIso3H = (TH1F*)f1->Get("hOfflinePV_AfterLooseIso3H");
	TH1F* hOfflinePV = (TH1F*)f1->Get("hOfflinePV");
	f1->cd();
	TH1F* hOfflinePV = (TH1F*)hOfflinePV->Clone();
	//hOfflinePV_AfterLooseIso3H->SetRange(0,70);
	//hOfflinePV->SetRangeUser(0,70);
	
	TH1F* EffLooseIso3Hits_NPV =new TH1F("EffLooseIso3Hits_NPV","EffLooseIso3Hits_NPV",100,0,100);
	EffLooseIso3Hits_NPV->Divide(hOfflinePV_AfterLooseIso3H, hOfflinePV, 1. ,  1. , "B");
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	TH1F* hTauGenMatchPt_AfterLooseIso3H_40 = (TH1F*)f2->Get("hTauGenMatchPt_AfterLooseIso3H");
	hTauGenMatchPt_AfterLooseIso3H_40->Rebin(4);
	TH1F* hGenTauPt_40 = (TH1F*)f2->Get("hTauGenMatchPt");
	hGenTauPt_40->Rebin(4);
	TH1F* EffLooseIso3Hits_Pt_40 =new TH1F("EffLooseIso3Hits_Pt_40","EffLooseIso3Hits_Pt_40",50,0,200);
	EffLooseIso3Hits_Pt_40->Divide(hTauGenMatchPt_AfterLooseIso3H_40,hGenTauPt_40, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchEta_AfterLooseIso3H_40 = (TH1F*)f2->Get("hTauGenMatchEta_AfterLooseIso3H"); 
	hTauGenMatchEta_AfterLooseIso3H_40->Rebin(2);
	TH1F* hGenTauEta_40 = (TH1F*)f2->Get("hTauGenMatchEta");
	hGenTauEta_40->Rebin(2);
	TH1F* EffLooseIso3Hits_Eta_40 =new TH1F("EffLooseIso3Hits_Eta_40","EffLooseIso3Hits_Eta_40",50,-3,3);
	EffLooseIso3Hits_Eta_40->Divide(hTauGenMatchEta_AfterLooseIso3H_40,hGenTauEta_40, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchPhi_AfterLooseIso3H_40 = (TH1F*)f2->Get("hTauGenMatchPhi_AfterLooseIso3H");
	TH1F* hGenTauPhi_40  = (TH1F*)f2->Get("hTauGenMatchPhi");
	TH1F* EffLooseIso3Hits_Phi_40 =new TH1F("EffLooseIso3Hits_Phi_40","EffLooseIso3Hits_Phi_40",100,-3,3);
	EffLooseIso3Hits_Phi_40->Divide(hTauGenMatchPhi_AfterLooseIso3H_40,hGenTauPhi_40, 1. ,  1. , "B");
	
	TH1F* hOfflinePV_AfterLooseIso3H_40 = (TH1F*)f2->Get("hOfflinePV_AfterLooseIso3H");
	TH1F* hOfflinePV_40 = (TH1F*)f2->Get("hOfflinePV");
	TH1F* EffLooseIso3Hits_NPV_40 =new TH1F("EffLooseIso3Hits_NPV","EffLooseIso3Hits_NPV",100,0,100);
	EffLooseIso3Hits_NPV_40->Divide(hOfflinePV_AfterLooseIso3H_40, hOfflinePV_40, 1. ,  1. , "B");
	
	/////////////////////////////8tev//////////////////////////////
	TH1F* hTauGenMatchPt_AfterLooseIso3H_8Tev = (TH1F*)f3->Get("hTauGenMatchPt_AfterLooseIso3H");
	hTauGenMatchPt_AfterLooseIso3H_8Tev->Rebin(4);
	TH1F* hGenTauPt_8Tev = (TH1F*)f3->Get("hTauGenMatchPt");
	hGenTauPt_8Tev->Rebin(4);
	TH1F* EffLooseIso3Hits_Pt_8Tev =new TH1F("EffLooseIso3Hits_Pt_8Tev","EffLooseIso3Hits_Pt_8Tev",50,0,200);
	EffLooseIso3Hits_Pt_8Tev->Divide(hTauGenMatchPt_AfterLooseIso3H_8Tev,hGenTauPt_8Tev, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchEta_AfterLooseIso3H_8Tev = (TH1F*)f3->Get("hTauGenMatchEta_AfterLooseIso3H"); 
	hTauGenMatchEta_AfterLooseIso3H_8Tev->Rebin(2);
	TH1F* hGenTauEta_8Tev = (TH1F*)f3->Get("hTauGenMatchEta");
	hGenTauEta_8Tev->Rebin(2);
	TH1F* EffLooseIso3Hits_Eta_8Tev =new TH1F("EffLooseIso3Hits_Eta_8Tev","EffLooseIso3Hits_Eta_8Tev",50,-3,3);
	EffLooseIso3Hits_Eta_8Tev->Divide(hTauGenMatchEta_AfterLooseIso3H_8Tev,hGenTauEta_8Tev, 1. ,  1. , "B");
	
	TH1F* hTauGenMatchPhi_AfterLooseIso3H_8Tev = (TH1F*)f3->Get("hTauGenMatchPhi_AfterLooseIso3H");
	TH1F* hGenTauPhi_8Tev  = (TH1F*)f3->Get("hTauGenMatchPhi");
	TH1F* EffLooseIso3Hits_Phi_8Tev =new TH1F("EffLooseIso3Hits_Phi_8Tev","EffLooseIso3Hits_Phi_8Tev",100,-3,3);
	EffLooseIso3Hits_Phi_8Tev->Divide(hTauGenMatchPhi_AfterLooseIso3H_8Tev,hGenTauPhi_8Tev, 1. ,  1. , "B");
	
	TH1F* hOfflinePV_AfterLooseIso3H_8Tev = (TH1F*)f3->Get("hOfflinePV_AfterLooseIso3H");
	TH1F* hOfflinePV_8Tev = (TH1F*)f3->Get("hOfflinePV");
	TH1F* EffLooseIso3Hits_NPV_8Tev =new TH1F("EffLooseIso3Hits_NPV_8Tev","EffLooseIso3Hits_NPV_8Tev",100,0,100);
	EffLooseIso3Hits_NPV_8Tev->Divide(hOfflinePV_AfterLooseIso3H_8Tev, hOfflinePV_8Tev, 1. ,  1. , "B");
	
	//////////////////////Draw Eff///////////////////////////////////
	TCanvas *Eff_LooseIso3Hits = new TCanvas("Eff_LooseIso3Hits","Eff Loose Isolation 3Hits",1600,900);
	Eff_LooseIso3Hits->Divide(2,2);
	
	Eff_LooseIso3Hits->cd(1);
	gPad->SetGridy();
	EffLooseIso3Hits_Pt_8Tev->GetXaxis()->SetTitle("gen. P_{T}^{#tau} [GeV]");
	EffLooseIso3Hits_Pt_8Tev->GetYaxis()->SetTitle("Efficiency");
	
	EffLooseIso3Hits_Pt_40->SetMarkerColor(kBlue); 
	EffLooseIso3Hits_Pt->SetMarkerColor(kMagenta);
	EffLooseIso3Hits_Pt_40->SetLineColor(kBlue); 
	EffLooseIso3Hits_Pt->SetLineColor(kMagenta);
	
	EffLooseIso3Hits_Pt_8Tev->Draw("HISTE");
	EffLooseIso3Hits_Pt->Draw("HISTESAME");
	EffLooseIso3Hits_Pt_40->Draw("HISTESAME");
	EffLooseIso3Hits_Pt_8Tev->SetMinimum(0.3);
	EffLooseIso3Hits_Pt_8Tev->SetMaximum(0.9);
	
	
	Eff_LooseIso3Hits->cd(2);
	gPad->SetGridy();
	EffLooseIso3Hits_Eta_40->SetMarkerColor(kBlue);
	EffLooseIso3Hits_Eta_40->SetLineColor(kBlue);
	EffLooseIso3Hits_Eta->SetMarkerColor(kMagenta);  
	EffLooseIso3Hits_Eta->SetLineColor(kMagenta);
	EffLooseIso3Hits_Eta_8Tev->Draw("HISTE");
	EffLooseIso3Hits_Eta_40->Draw("HISTESAME"); 
	EffLooseIso3Hits_Eta->Draw("HISTESAME"); 
	EffLooseIso3Hits_Eta_8Tev->GetXaxis()->SetTitle("gen. #eta_{#tau}");
	EffLooseIso3Hits_Eta_8Tev->GetYaxis()->SetTitle("Efficiency");
	EffLooseIso3Hits_Eta_8Tev->SetMinimum(0.3);
	EffLooseIso3Hits_Eta_8Tev->SetMaximum(0.9);
	
	Eff_LooseIso3Hits->cd(3);
	gPad->SetGridy();
	EffLooseIso3Hits_Phi_40->SetMarkerColor(kBlue);  
	EffLooseIso3Hits_Phi->SetMarkerColor(kMagenta);
	EffLooseIso3Hits_Phi_40->SetLineColor(kBlue);  
	EffLooseIso3Hits_Phi->SetLineColor(kMagenta);
	EffLooseIso3Hits_Phi_8Tev->Draw("HISTE");
	EffLooseIso3Hits_Phi_40->Draw("SAMEHISTE");
	EffLooseIso3Hits_Phi->Draw("SAMEHISTE");  
	EffLooseIso3Hits_Phi_8Tev->GetXaxis()->SetTitle("gen. #phi_{#tau}");
	EffLooseIso3Hits_Phi_8Tev->GetYaxis()->SetTitle("Efficiency");
	EffLooseIso3Hits_Phi_8Tev->SetMinimum(0.3);
	EffLooseIso3Hits_Phi_8Tev->SetMaximum(0.9);
	
	Eff_LooseIso3Hits->cd(4);
	gPad->SetGridy();
	EffLooseIso3Hits_NPV_40->SetMarkerColor(kBlue);  
	EffLooseIso3Hits_NPV->SetMarkerColor(kMagenta);
    EffLooseIso3Hits_NPV_40->SetLineColor(kBlue);  
	EffLooseIso3Hits_NPV->SetLineColor(kMagenta);
	EffLooseIso3Hits_NPV_8Tev->GetXaxis()->SetRange(0, 70);

	EffLooseIso3Hits_NPV_40->GetXaxis()->SetRange(0, 70);
	EffLooseIso3Hits_NPV->GetXaxis()->SetRange(0, 70);
	
	EffLooseIso3Hits_NPV_8Tev->Draw();
	EffLooseIso3Hits_NPV_40->Draw("HISTESAME");
	EffLooseIso3Hits_NPV->Draw("HISTESAME");  
	EffLooseIso3Hits_NPV_8Tev->GetXaxis()->SetTitle("N_{vtx}");
	EffLooseIso3Hits_NPV_8Tev->GetYaxis()->SetTitle("Efficiency");
	EffLooseIso3Hits_NPV_8Tev->SetMinimum(0.);
	EffLooseIso3Hits_NPV_8Tev->SetMaximum(0.9);
	
	TLegend* legend = new TLegend( 0.2, 0.75, 0.65, 0.9);
	legend->SetTextSize(0.047);
	legend->SetFillColor(0);
	legend->AddEntry(EffLooseIso3Hits_Phi_8Tev, "Summer12, 8 TeV");
	legend->AddEntry(EffLooseIso3Hits_Phi, "Fall13, 13 TeV, PU20, bx25");
	legend->AddEntry(EffLooseIso3Hits_Phi_40, "Fall13, 13 TeV, PU40, bx25");
	Eff_LooseIso3Hits->cd(3);
	legend->Draw("same");
	
	Eff_LooseIso3Hits->SaveAs("LooseIsoEff.pdf");
	
	
}

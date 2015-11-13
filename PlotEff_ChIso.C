#include <TH1>
void PlotEff_ChIso(){
 	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();
	
	TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
	TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
	TFile *f3 = TFile::Open(".//histo_file_HToTauTau_8TeV_HighPt.root");
	

///////////////////////////////////////charged iso///////////////////////////////////
 gStyle->SetOptStat(00000000);
 TH1F* hTauGenMatchPt_AfterChIsoPtSum = (TH1F*)f1->Get("hTauGenMatchPt_AfterChIsoPtSum");
 hTauGenMatchPt_AfterChIsoPtSum->Rebin(4);
 TH1F* hGenTauPt = (TH1F*)f1->Get("hTauGenMatchPt"); 
 hGenTauPt->Rebin(4);
 TH1F* Eff_AfterChIsoPtSum_Pt =new TH1F("Eff_AfterChIsoPtSum_Pt","Eff_AfterChIsoPtSum_Pt",50,0,200);
  Eff_AfterChIsoPtSum_Pt->Divide(hTauGenMatchPt_AfterChIsoPtSum,hGenTauPt, 1. ,  1. , "B");

 TH1F* hTauGenMatchEta_AfterChIsoPtSum = (TH1F*)f1->Get("hTauGenMatchEta_AfterChIsoPtSum");
 hTauGenMatchEta_AfterChIsoPtSum->Rebin(2);
 TH1F* hGenTauEta = (TH1F*)f1->Get("hTauGenMatchEta");
 hGenTauEta->Rebin(2);
 TH1F* Eff_AfterChIsoPtSum_Eta =new TH1F("AfterChIsoPtSum_Eta","AfterChIsoPtSum_Eta",50,-3,3);
 Eff_AfterChIsoPtSum_Eta->Divide(hTauGenMatchEta_AfterChIsoPtSum,hGenTauEta, 1. ,  1. , "B");

 TH1F* hTauGenMatchPhi_AfterChIsoPtSum = (TH1F*)f1->Get("hTauGenMatchPhi_AfterChIsoPtSum");
 TH1F* hGenTauPhi = (TH1F*)f1->Get("hTauGenMatchPhi");
 TH1F* Eff_AfterChIsoPtSum_Phi =new TH1F("Eff_AfterChIsoPtSum_Phi","Eff_AfterChIsoPtSum_Phi",100,-3,3);
 Eff_AfterChIsoPtSum_Phi->Divide(hTauGenMatchPhi_AfterChIsoPtSum,hGenTauPhi, 1. ,  1. , "B");
	
TH1F* hOfflinePV_AfterChIsoPtSum = (TH1F*)f1->Get("hOfflinePV_AfterChIsoPtSum");
TH1F* hOfflinePV = (TH1F*)f1->Get("hOfflinePV");
TH1F* Eff_AfterChIsoPtSum_NPV =new TH1F("AfterChIsoPtSum","AfterChIsoPtSum",100,0,100);
Eff_AfterChIsoPtSum_NPV->Divide(hOfflinePV_AfterChIsoPtSum, hOfflinePV, 1. ,  1. , "B");

///////////////////////////////////////////////////////////////////////////////////////////////////////
 TH1F* hTauGenMatchPt_AfterChIsoPtSum_40 = (TH1F*)f2->Get("hTauGenMatchPt_AfterChIsoPtSum");
 hTauGenMatchPt_AfterChIsoPtSum_40->Rebin(4);
 TH1F* hGenTauPt_40 = (TH1F*)f2->Get("hTauGenMatchPt");
 hGenTauPt_40->Rebin(4);
 TH1F* Eff_AfterChIsoPtSum_Pt_40 =new TH1F("Eff_AfterChIsoPtSum_Pt_40","Eff_AfterChIsoPtSum_Pt_40",50,0,200);
 Eff_AfterChIsoPtSum_Pt_40->Divide(hTauGenMatchPt_AfterChIsoPtSum_40,hGenTauPt_40, 1. ,  1. , "B");


 TH1F* hTauGenMatchEta_AfterChIsoPtSum_40 = (TH1F*)f2->Get("hTauGenMatchEta_AfterChIsoPtSum"); 
 hTauGenMatchEta_AfterChIsoPtSum_40->Rebin(2);
 TH1F* hGenTauEta_40 = (TH1F*)f2->Get("hTauGenMatchEta");
 hGenTauEta_40->Rebin(2);
 TH1F* Eff_AfterChIsoPtSum_Eta_40 =new TH1F("Eff_AfterChIsoPtSum_Eta_40","Eff_AfterChIsoPtSum_Eta_40",50,-3,3);
 Eff_AfterChIsoPtSum_Eta_40->Divide(hTauGenMatchEta_AfterChIsoPtSum_40,hGenTauEta_40, 1. ,  1. , "B");
 
 TH1F* hTauGenMatchPhi_AfterChIsoPtSum_40 = (TH1F*)f2->Get("hTauGenMatchPhi_AfterChIsoPtSum");
 TH1F* hGenTauPhi_40  = (TH1F*)f2->Get("hTauGenMatchPhi");
 TH1F* AfterChIsoPtSum_Phi_40 =new TH1F("Eff_AfterChIsoPtSum_Phi_40","Eff_AfterChIsoPtSum_Phi_40",100,-3,3);
 Eff_AfterChIsoPtSum_Phi_40->Divide(hTauGenMatchPhi_AfterChIsoPtSum_40,hGenTauPhi_40, 1. ,  1. , "B");
	
TH1F* hOfflinePV_AfterChIso_40 = (TH1F*)f2->Get("hOfflinePV_AfterChIsoPtSum");
TH1F* hOfflinePV_40 = (TH1F*)f2->Get("hOfflinePV");
TH1F* Eff_AfterChIsoPtSum_NPV_40 =new TH1F("Eff_AfterChIsoPtSum_NPV_40","Eff_AfterChIsoPtSum_NPV_40",100,0,100);
Eff_AfterChIsoPtSum_NPV_40->Divide(hOfflinePV_AfterChIso_40, hOfflinePV_40, 1. ,  1. , "B");

   /////////////////////////////8tev//////////////////////////////
 TH1F* hTauGenMatchPt_AfterChIsoPtSum_8Tev = (TH1F*)f3->Get("hTauGenMatchPt_AfterChIsoPtSum");
 hTauGenMatchPt_AfterChIsoPtSum_8Tev->Rebin(4);
 TH1F* hGenTauPt_8Tev = (TH1F*)f3->Get("hTauGenMatchPt");
 hGenTauPt_8Tev->Rebin(4);
 TH1F* Eff_AfterChIsoPtSum_Pt_8Tev =new TH1F("Eff_AfterChIsoPtSum_Pt_8Tev","Eff_AfterChIsoPtSum_Pt_8Tev",50,0,200);
 Eff_AfterChIsoPtSum_Pt_8Tev->Divide(hTauGenMatchPt_AfterChIsoPtSum_8Tev,hGenTauPt_8Tev, 1. ,  1. , "B");
 
 TH1F* hTauGenMatchEta_AfterChIsoPtSum_8Tev = (TH1F*)f3->Get("hTauGenMatchEta_AfterChIsoPtSum"); 
 hTauGenMatchEta_AfterChIsoPtSum_8Tev->Rebin(2);
 TH1F* hGenTauEta_8Tev = (TH1F*)f3->Get("hTauGenMatchEta");
 hGenTauEta_8Tev->Rebin(2);
 TH1F* Eff_AfterChIsoPtSum_Eta_8Tev =new TH1F("Eff_AfterChIsoPtSum_Eta_8Tev","Eff_AfterChIsoPtSum_Eta_8Tev",50,-3,3);
 Eff_AfterChIsoPtSum_Eta_8Tev->Divide(hTauGenMatchEta_AfterChIsoPtSum_8Tev,hGenTauEta_8Tev, 1. ,  1. , "B");

TH1F* hTauGenMatchPhi_AfterChIsoPtSum_8Tev = (TH1F*)f3->Get("hTauGenMatchPhi_AfterChIsoPtSum");
TH1F* hGenTauPhi_8Tev  = (TH1F*)f3->Get("hTauGenMatchPhi");
TH1F* Eff_AfterChIsoPtSum_Phi_8Tev =new TH1F("Eff_AfterChIsoPtSum_Phi_8Tev","Eff_AfterChIsoPtSum_Phi_8Tev",100,-3,3);
Eff_AfterChIsoPtSum_Phi_8Tev->Divide(hTauGenMatchPhi_AfterChIsoPtSum_8Tev,hGenTauPhi_8Tev, 1. ,  1. , "B");

TH1F* hOfflinePV_AfterChIsoPtSum_8Tev  = (TH1F*)f3->Get("hOfflinePV_AfterChIsoPtSum");
TH1F* hOfflinePV_8Tev  = (TH1F*)f3->Get("hOfflinePV");
TH1F* Eff_AfterChIsoPtSum_NPV_8Tev  =new TH1F("Eff_AfterChIso_NPV_8Tev ","Eff_AfterChIsoPtSum_NPV_8Tev",100,0,100);
Eff_AfterChIsoPtSum_NPV_8Tev->Divide(hOfflinePV_AfterChIsoPtSum_8Tev , hOfflinePV_8Tev , 1. ,  1. , "B");
	

//////////////////////Draw E////////////////////
  TCanvas *Eff_AfterChIsoPtSum = new TCanvas("Eff_AfterChIsoPtSum","Eff Charged Hadron IsoPtSum",700,800);
  Eff_AfterChIsoPtSum->Divide(1,2);
  
/*  Eff_AfterChIsoPtSum->cd(1);
	 gPad->SetGridy();
  Eff_AfterChIsoPtSum_Pt_40->SetMarkerColor(kBlue); 
  Eff_AfterChIsoPtSum_Pt->SetMarkerColor(kMagenta);
  Eff_AfterChIsoPtSum_Pt_8Tev->Draw("HISTE");
  Eff_AfterChIsoPtSum_Pt->Draw("SAME");
  Eff_AfterChIsoPtSum_Pt_40->Draw("SAME");
  Eff_AfterChIsoPtSum_Pt_8Tev->SetMinimum(0.3);
  Eff_AfterChIsoPtSum_Pt_8Tev->SetMaximum(0.9);
  Eff_AfterChIsoPtSum_Pt_8Tev->GetXaxis()->SetTitle("Pt^{gen}");
*/
  Eff_AfterChIsoPtSum->cd(1);
	 gPad->SetGridy();
  Eff_AfterChIsoPtSum_Eta_40->SetMarkerColor(kBlue);
  Eff_AfterChIsoPtSum_Eta->SetMarkerColor(kMagenta);
  Eff_AfterChIsoPtSum_Eta_8Tev->Draw("HISTE");
  Eff_AfterChIsoPtSum_Eta_8Tev->SetMinimum(0.3);
	Eff_AfterChIsoPtSum_Eta_8Tev->SetMaximum(0.9);
  Eff_AfterChIsoPtSum_Eta_40->Draw("SAME"); 
  Eff_AfterChIsoPtSum_Eta->Draw("SAME"); 
  Eff_AfterChIsoPtSum_Eta_8Tev->GetXaxis()->SetTitle("Eta^{gen}");
 // Eff_AfterChIsoPtSum_Eta_8Tev->GetYaxis()->SetTitle("eff");


/*  Eff_AfterChIsoPtSum->cd(3);
	 gPad->SetGridy();
  Eff_AfterChIsoPtSum_Phi_40->SetMarkerColor(kBlue);  
  Eff_AfterChIsoPtSum_Phi->SetMarkerColor(kMagenta);
  Eff_AfterChIsoPtSum_Phi_8Tev->Draw("HISTE");
  Eff_AfterChIsoPtSum_Phi_8Tev->SetMinimum(0.3);
	 Eff_AfterChIsoPtSum_Phi_8Tev->SetMaximum(0.9);
  Eff_AfterChIsoPtSum_Phi_40->Draw("SAME");
  Eff_AfterChIsoPtSum_Phi->Draw("SAME");  
  Eff_AfterChIsoPtSum_Phi_8Tev->GetXaxis()->SetTitle("Phi^{gen}");
  Eff_AfterChIsoPtSum_Phi_8Tev->GetYaxis()->SetRange(0.1, 1.);
	*/
	
Eff_AfterChIsoPtSum->cd(2);
	 gPad->SetGridy();
Eff_AfterChIsoPtSum_NPV_40->SetMarkerColor(kBlue);  
Eff_AfterChIsoPtSum_NPV->SetMarkerColor(kMagenta);
Eff_AfterChIsoPtSum_NPV_8Tev->Draw();
Eff_AfterChIsoPtSum_NPV_8Tev->SetMinimum(0.3);
	Eff_AfterChIsoPtSum_NPV_8Tev->SetMaximum(0.9);
	Eff_AfterChIsoPtSum_NPV_40->Draw("SAME");
	Eff_AfterChIsoPtSum_NPV->Draw("SAME");  
	Eff_AfterChIsoPtSum_NPV_8Tev->GetXaxis()->SetTitle("# PV");
	Eff_AfterChIsoPtSum_NPV_8Tev->GetYaxis()->SetRange(0.1, 1.);


 TLegend* legend = new TLegend( 0.45, 0.3, 0.99, 0.5);
 legend->SetTextSize(0.035);
 legend->SetFillColor(0);
 legend->AddEntry(Eff_AfterChIsoPtSum_Phi_8Tev, "Summer12, 8 TeV");
 legend->AddEntry(Eff_AfterChIsoPtSum_Phi, "Fall13, 13 TeV, PU20, bx25");
 legend->AddEntry(Eff_AfterChIsoPtSum_Phi_40, "Fall13, 13 TeV, PU40, bx25");
 Eff_AfterChIsoPtSum->cd(3);
// legend->Draw("same");
 
 Eff_AfterChIsoPtSum->SaveAs("EffChargedIso.pdf");
	
	TFile fEff_ChIso("fEff_ChIso.root","recreate"); 
	Eff_AfterChIsoPtSum_Pt_40->Write("EffLooseIso3Hits_Pt_Pu40");
	Eff_AfterChIsoPtSum_Pt->Write("EffLooseIso3Hits_Pt_Pu20"); 
	Eff_AfterChIsoPtSum_Pt_8Tev->Write("EffLooseIso3Hits_Pt_8Tev");
	
	
	fEff_ChIso.Close();
	

}

#include <TH1>
void PlotEff_DM(){
  gROOT->ProcessLine(".L ./tdrstyle.C");
  setTDRStyle();
	TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
	TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25_OLD.root");
	TFile *f3 = TFile::Open(".//histo_file_HToTauTau_8TeV_HighPt.root");


///////////////////////////////////////charged iso///////////////////////////////////
 gStyle->SetOptStat(00000000);
 TH1F* hTauGenMatchPt_AfterDM = (TH1F*)f1->Get("hTauGenMatchPt_AfterDM");
 hTauGenMatchPt_AfterDM->Rebin(4);
 TH1F* hGenTauPt = (TH1F*)f1->Get("hTauGenMatchPt"); 
 hGenTauPt->Rebin(4);
 TH1F* Eff_AfterDM_Pt =new TH1F("Eff_AfterDM_Pt","Eff_AfterDM_Pt",50,0,200);
  Eff_AfterDM_Pt->Divide(hTauGenMatchPt_AfterDM,hGenTauPt, 1. ,  1. , "B");

 TH1F* hTauGenMatchEta_AfterDM = (TH1F*)f1->Get("hTauGenMatchEta_AfterDM");
 hTauGenMatchEta_AfterDM->Rebin(2);
 TH1F* hGenTauEta = (TH1F*)f1->Get("hTauGenMatchEta");
 hGenTauEta->Rebin(2);
 TH1F* Eff_AfterDM_Eta =new TH1F("AfterDM_Eta","AfterDM_Eta",50,-3,3);
 Eff_AfterDM_Eta->Divide(hTauGenMatchEta_AfterDM,hGenTauEta, 1. ,  1. , "B");

 TH1F* hTauGenMatchPhi_AfterDM = (TH1F*)f1->Get("hTauGenMatchPhi_AfterDM");
 TH1F* hGenTauPhi = (TH1F*)f1->Get("hTauGenMatchPhi");
 TH1F* Eff_AfterDM_Phi =new TH1F("Eff_AfterDM_Phi","Eff_AfterDM_Phi",100,-3,3);
 Eff_AfterDM_Phi->Divide(hTauGenMatchPhi_AfterDM,hGenTauPhi, 1. ,  1. , "B");
	
TH1F* hOfflinePV_AfterDM = (TH1F*)f1->Get("hOfflinePV_AfterDM");
TH1F* hOfflinePV = (TH1F*)f1->Get("hOfflinePV");
TH1F* Eff_AfterDM_NPV =new TH1F("AfterDM","AfterDM",100,0,100);
Eff_AfterDM_NPV->Divide(hOfflinePV_AfterDM, hOfflinePV, 1. ,  1. , "B");
	


 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 TH1F* hTauGenMatchPt_AfterDM_40 = (TH1F*)f2->Get("hTauGenMatchPt_AfterDM");
 hTauGenMatchPt_AfterDM_40->Rebin(4);
 TH1F* hGenTauPt_40 = (TH1F*)f2->Get("hTauGenMatchPt");
 hGenTauPt_40->Rebin(4);
 TH1F* Eff_AfterDM_Pt_40 =new TH1F("Eff_AfterDM_Pt_40","Eff_AfterDM_Pt_40",50,0,200);
 Eff_AfterDM_Pt_40->Divide(hTauGenMatchPt_AfterDM_40,hGenTauPt_40, 1. ,  1. , "B");


 TH1F* hTauGenMatchEta_AfterDM_40 = (TH1F*)f2->Get("hTauGenMatchEta_AfterDM"); 
 hTauGenMatchEta_AfterDM_40->Rebin(2);
 TH1F* hGenTauEta_40 = (TH1F*)f2->Get("hTauGenMatchEta");
 hGenTauEta_40->Rebin(2);
 TH1F* Eff_AfterDM_Eta_40 =new TH1F("Eff_AfterDM_Eta_40","Eff_AfterDM_Eta_40",50,-3,3);
 Eff_AfterDM_Eta_40->Divide(hTauGenMatchEta_AfterDM_40,hGenTauEta_40, 1. ,  1. , "B");
 
 TH1F* hTauGenMatchPhi_AfterDM_40 = (TH1F*)f2->Get("hTauGenMatchPhi_AfterDM");
 TH1F* hGenTauPhi_40  = (TH1F*)f2->Get("hTauGenMatchPhi");
 TH1F* AfterDM_Phi_40 =new TH1F("Eff_AfterDM_Phi_40","Eff_AfterDM_Phi_40",100,-3,3);
 Eff_AfterDM_Phi_40->Divide(hTauGenMatchPhi_AfterDM_40,hGenTauPhi_40, 1. ,  1. , "B");
	
TH1F* hOfflinePV_AfterDM_40 = (TH1F*)f2->Get("hOfflinePV_AfterDM");
TH1F* hOfflinePV_40 = (TH1F*)f2->Get("hOfflinePV");
TH1F* Eff_AfterDM_NPV_40 =new TH1F("AfterDM_40","AfterDM_40",100,0,100);
Eff_AfterDM_NPV_40->Divide(hOfflinePV_AfterDM_40, hOfflinePV_40, 1. ,  1. , "B");
	

   /////////////////////////////8tev//////////////////////////////
 TH1F* hTauGenMatchPt_AfterDM_8Tev = (TH1F*)f3->Get("hTauGenMatchPt_AfterDM");
 hTauGenMatchPt_AfterDM_8Tev->Rebin(4);
 TH1F* hGenTauPt_8Tev = (TH1F*)f3->Get("hTauGenMatchPt");
 hGenTauPt_8Tev->Rebin(4);
 TH1F* Eff_AfterDM_Pt_8Tev =new TH1F("Eff_AfterDM_Pt_8Tev","Eff_AfterDM_Pt_8Tev",50,0,200);
 Eff_AfterDM_Pt_8Tev->Divide(hTauGenMatchPt_AfterDM_8Tev,hGenTauPt_8Tev, 1. ,  1. , "B");

 
 TH1F* hTauGenMatchEta_AfterDM_8Tev = (TH1F*)f3->Get("hTauGenMatchEta_AfterDM"); 
 hTauGenMatchEta_AfterDM_8Tev->Rebin(2);
 TH1F* hGenTauEta_8Tev = (TH1F*)f3->Get("hTauGenMatchEta");
 hGenTauEta_8Tev->Rebin(2);
 TH1F* Eff_AfterDM_Eta_8Tev =new TH1F("Eff_AfterDM_Eta_8Tev","Eff_AfterDM_Eta_8Tev",50,-3,3);
 Eff_AfterDM_Eta_8Tev->Divide(hTauGenMatchEta_AfterDM_8Tev,hGenTauEta_8Tev, 1. ,  1. , "B");

TH1F* hTauGenMatchPhi_AfterDM_8Tev = (TH1F*)f3->Get("hTauGenMatchPhi_AfterDM");
TH1F* hGenTauPhi_8Tev  = (TH1F*)f3->Get("hTauGenMatchPhi");
TH1F* Eff_AfterDM_Phi_8Tev =new TH1F("Eff_AfterDM_Phi_8Tev","Eff_AfterDM_Phi_8Tev",100,-3,3);
Eff_AfterDM_Phi_8Tev->Divide(hTauGenMatchPhi_AfterDM_8Tev,hGenTauPhi_8Tev, 1. ,  1. , "B");

TH1F* hOfflinePV_AfterDM_8Tev = (TH1F*)f3->Get("hOfflinePV_AfterDM");
TH1F* hOfflinePV_8Tev = (TH1F*)f3->Get("hOfflinePV");
TH1F* Eff_AfterDM_NPV_8Tev =new TH1F("AfterDM_8Tev","AfterDM_8Tev",100,0,100);
Eff_AfterDM_NPV_8Tev->Divide(hOfflinePV_AfterDM_8Tev, hOfflinePV_8Tev, 1. ,  1. , "B");

//////////////////////Draw E////////////////////
  TCanvas *Eff_AfterDM = new TCanvas("Eff_AfterDM","Eff DecayMode",1300,800);
  Eff_AfterDM->Divide(2,2);
  
  Eff_AfterDM->cd(1);
	gPad->SetGridy();
  Eff_AfterDM_Pt_40->SetMarkerColor(kBlue); 
  Eff_AfterDM_Pt->SetMarkerColor(kMagenta);
  Eff_AfterDM_Pt_8Tev->Draw("HISTE");
  Eff_AfterDM_Pt->Draw("SAME");
  Eff_AfterDM_Pt_40->Draw("SAME");
 // Eff_AfterDM_Pt_8Tev->SetMinimum(0.95);
  Eff_AfterDM_Pt_8Tev->GetXaxis()->SetTitle("Pt^{gen}");

  Eff_AfterDM->cd(2);
	gPad->SetGridy();
  Eff_AfterDM_Eta_40->SetMarkerColor(kBlue);
  Eff_AfterDM_Eta->SetMarkerColor(kMagenta);
  Eff_AfterDM_Eta_8Tev->Draw("HISTE");
  //Eff_AfterDM_Eta_8Tev->SetMinimum(0.95);
  Eff_AfterDM_Eta_40->Draw("SAME"); 
  Eff_AfterDM_Eta->Draw("SAME"); 
  Eff_AfterDM_Eta_8Tev->GetXaxis()->SetTitle("Eta^{gen}");
//  Eff_AfterDM_Eta_8Tev->GetYaxis()->SetTitle("eff");

  Eff_AfterDM->cd(3);
	gPad->SetGridy();
  Eff_AfterDM_Phi_40->SetMarkerColor(kBlue);  
  Eff_AfterDM_Phi->SetMarkerColor(kMagenta);
  Eff_AfterDM_Phi_8Tev->Draw("HISTE");
 // Eff_AfterDM_Phi_8Tev->SetMinimum(0.95);
  Eff_AfterDM_Phi_40->Draw("SAME");
 // Eff_AfterDM_Phi->Draw("SAME");  
  Eff_AfterDM_Phi_8Tev->GetXaxis()->SetTitle("Phi^{gen}");
 // Eff_AfterDM_Phi_8Tev->GetYaxis()->SetRange(0.1, 1.);
	
  Eff_AfterDM->cd(4);
	gPad->SetGridy();
  Eff_AfterDM_NPV_40->SetMarkerColor(kBlue);  
  Eff_AfterDM_NPV->SetMarkerColor(kMagenta);
  Eff_AfterDM_NPV_8Tev->Draw();
//  Eff_AfterDM_NPV_8Tev->SetMinimum(0.95);
  Eff_AfterDM_NPV_40->Draw("SAME");
  Eff_AfterDM_NPV->Draw("SAME");  
  Eff_AfterDM_NPV_8Tev->GetXaxis()->SetTitle("#PV");
  Eff_AfterDM_NPV_8Tev->GetYaxis()->SetRange(0.1, 1.);


 TLegend* legend = new TLegend( 0.45, 0.3, 0.99, 0.5);
 legend->SetTextSize(0.035);
 legend->SetFillColor(0);
 legend->AddEntry(Eff_AfterDM_Phi_8Tev, "Summer12, 8 TeV");
 legend->AddEntry(Eff_AfterDM_Phi, "Fall13, 13 TeV, PU20, bx25");
 legend->AddEntry(Eff_AfterDM_Phi_40, "Fall13, 13 TeV, PU40, bx25");
 Eff_AfterDM->cd(3);
 legend->Draw("same");
 
 Eff_AfterDM->SaveAs("DecayModeEff.pdf");

}

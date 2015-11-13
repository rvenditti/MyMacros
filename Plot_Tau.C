#include <TH1>
#include <sstream>
#include <string>
#include <iostream>

void Plot_Tau(){
	gROOT->ProcessLine(".L ./tdrstyle.C");
	setTDRStyle();


  ////////////////////////////////////////////////////////////////////////////
  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25_OLD.root");
  TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");

  gStyle->SetOptStat(0000000);
 
  TH1F* hTau_chargedIsoPtSum_PU20 = (TH1F*)f1->Get("hTau_chargedIsoPtSum");
  TH1F* hTau_neutralIsoPtSum_PU20 = (TH1F*)f1->Get("hTau_neutralIsoPtSum");
  TH1F* hTau_puCorrPtSum_PU20 = (TH1F*)f1->Get("hTau_puCorrPtSum");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20 = (TH1F*)f1->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits");
  TH1F* hTau_NewRawIsoCE_PU20 = (TH1F*)f1->Get("hTau_NewRawIso"); 
  TH1F* hTau_NewRawIsoEtaCorr_PU20 = (TH1F*)f1->Get("hTau_NewRawIso_EtaCorr"); 
	//hTau_NewRawIsoEtaCorr_PU20->Draw();
  TH1F* hTau_chargedIsoPtSum_PU40 = (TH1F*)f2->Get("hTau_chargedIsoPtSum");
  TH1F* hTau_neutralIsoPtSum_PU40 = (TH1F*)f2->Get("hTau_neutralIsoPtSum");
  TH1F* hTau_puCorrPtSum_PU40 = (TH1F*)f2->Get("hTau_puCorrPtSum");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40 = (TH1F*)f2->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits");
	TH1F* hTau_NewRawIsoCE_PU40 = (TH1F*)f2->Get("hTau_NewRawIso");

  TH1F* hTau_chargedIsoPtSum_8TeV = (TH1F*)f3->Get("hTau_chargedIsoPtSum");
  TH1F* hTau_neutralIsoPtSum_8TeV = (TH1F*)f3->Get("hTau_neutralIsoPtSum");
  TH1F* hTau_puCorrPtSum_8TeV = (TH1F*)f3->Get("hTau_puCorrPtSum");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV = (TH1F*)f3->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits");

  TCanvas *IsolationVar = new TCanvas("IsolationVar","Isolation Contribution",1200,800);
  IsolationVar->Divide(2,2);
  
  IsolationVar->cd(1);
  gPad->SetLogy();
  hTau_chargedIsoPtSum_PU20->SetLineColor(kMagenta);
  hTau_chargedIsoPtSum_PU40->SetLineColor(kBlue);
 

  hTau_chargedIsoPtSum_PU20->Scale(1/hTau_chargedIsoPtSum_PU20->Integral());
  hTau_chargedIsoPtSum_PU40->Scale(1/hTau_chargedIsoPtSum_PU40->Integral());
  hTau_chargedIsoPtSum_8TeV->Scale(1/hTau_chargedIsoPtSum_8TeV->Integral());

  hTau_chargedIsoPtSum_8TeV->Draw("HISTE");
  hTau_chargedIsoPtSum_PU20->Draw("SAMEHISTE");
  hTau_chargedIsoPtSum_PU40->Draw("SAMEHISTE");
  hTau_chargedIsoPtSum_8TeV->GetXaxis()->SetTitle("I_{Ch} [GeV]");
  hTau_chargedIsoPtSum_8TeV->SetTitle("Charged Isolation");

  IsolationVar->cd(2);

  hTau_neutralIsoPtSum_PU20->SetLineColor(kMagenta);
  hTau_neutralIsoPtSum_PU40->SetLineColor(kBlue);
//  hTau_neutralIsoPtSum_8TeV->SetLineColor(kMagenta);

  hTau_neutralIsoPtSum_PU20->Scale(1/hTau_neutralIsoPtSum_PU20->Integral());
  hTau_neutralIsoPtSum_PU40->Scale(1/hTau_neutralIsoPtSum_PU40->Integral());
  hTau_neutralIsoPtSum_8TeV->Scale(1/hTau_neutralIsoPtSum_8TeV->Integral());

  hTau_neutralIsoPtSum_8TeV->Draw("HISTE"); 
  hTau_neutralIsoPtSum_PU20->Draw("SAMEHISTE");
  hTau_neutralIsoPtSum_PU40->Draw("SAMEHISTE");
	
	hTau_neutralIsoPtSum_8TeV->GetXaxis()->SetTitle("I_{Ne} [GeV]");
	hTau_neutralIsoPtSum_8TeV->SetTitle("Neutral Isolation");

  IsolationVar->cd(3);

  hTau_puCorrPtSum_PU20->SetLineColor(kMagenta);
  hTau_puCorrPtSum_PU40->SetLineColor(kBlue);

	hTau_puCorrPtSum_PU20->Scale(1/hTau_puCorrPtSum_PU20->Integral());
  hTau_puCorrPtSum_PU40->Scale(1/hTau_puCorrPtSum_PU40->Integral());
  hTau_puCorrPtSum_8TeV->Scale(1/hTau_puCorrPtSum_8TeV->Integral());
hTau_puCorrPtSum_8TeV->SetMaximum(0.035);
  hTau_puCorrPtSum_8TeV->Draw("HISTE");
  hTau_puCorrPtSum_PU20->Draw("SAMEHISTE");
  hTau_puCorrPtSum_PU40->Draw("SAMEHISTE");
	
	hTau_puCorrPtSum_8TeV->GetXaxis()->SetTitle("I_{PU} [GeV]");
	hTau_puCorrPtSum_8TeV->SetTitle("Pile-Up Isolation");
 
  IsolationVar->cd(4);
  gPad->SetLogy();
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->SetLineColor(kMagenta);
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->SetLineColor(kBlue);


  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral());
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral());
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral());

  std::cout<<" iso>2 8 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral(4,100)<<endl;
  std::cout<<" iso>2 pu20 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral(4,100)<<endl;
 std::cout<<" iso>2 pu40 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral(4,100)<<endl;
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Draw("HISTE");
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Draw("SAMEHISTE");
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Draw("SAMEHISTE");
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->GetXaxis()->SetTitle("I_{Raw} [GeV]");
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->SetTitle("Combined Isolation DeltaBeta Corrected Raw 3Hits");

 
  TLegend* legend = new TLegend( 0.45, 0.60, 0.99, 0.9);
 legend->SetTextSize(0.035);
 legend->SetFillColor(0);
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV, "Summer12, 8 TeV");
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20, "Fall13, 13 TeV, PU20, bx25");
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40, "Fall13, 13 TeV, PU40, bx25");
 IsolationVar->cd(2);
 legend->Draw("same");

 IsolationVar->SaveAs("IsolationVar.pdf");

/* TH2F* hPUCorrVSEta_PU20 = (TH2F*)f1->Get("hTau_EtaVSPuCorr");
 TH2F* hIsoRawVSEta_PU20  = (TH2F*)f1->Get("hTau_EtaVSIsoRaw");

 TH2F* hPUCorrVSEta_PU40  = (TH2F*)f2->Get("hTau_EtaVSPuCorr");
 TH2F* hIsoRawVSEta_PU40  = (TH2F*)f2->Get("hTau_EtaVSIsoRaw");

 TH2F* hPUCorrVSEta_8TeV  = (TH2F*)f3->Get("hTau_EtaVSPuCorr");
 TH2F* hIsoRawVSEta_8TeV  = (TH2F*)f3->Get("hTau_EtaVSIsoRaw");


 TCanvas* PUCorr_cavas = new TCanvas("PUCorr_cavas", "PUCorr_cavas", 600, 800);
 PUCorr_cavas->Divide(1,3);
 PUCorr_cavas->cd(1);
 hPUCorrVSEta_PU20->SetTitle("Eta VS PU Correction, 13 TeV, pu20");
 hPUCorrVSEta_PU20->Draw("COLZ");
 PUCorr_cavas->cd(2);
 hPUCorrVSEta_PU40->SetTitle("Eta VS PU Correction, 13 TeV, pu40");
 hPUCorrVSEta_PU40->Draw("COLZ");
 PUCorr_cavas->cd(3);
 hPUCorrVSEta_8TeV->SetTitle("Eta VS PU Correction, 8 TeV");
 //hPUCorrVSEta_8TeV->Draw("COLZ");
 PUCorr_cavas->SaveAs("EtaVsPUCorr.pdf");
*/

 /*TCanvas* IsoRaw_cavas = new TCanvas("IsoRaw_cavas", "IsoRaw_cavas", 600, 800);
 IsoRaw_cavas->Divide(1,3);
 IsoRaw_cavas->cd(1);
 hIsoRawVSEta_PU20->SetTitle("Eta vs RawIso, 13 TeV, pu20");
		hIsoRawVSEta_PU20->GetYaxis()->SetRange(0,10);
 hIsoRawVSEta_PU20->Draw("COLZ");
 IsoRaw_cavas->cd(2);
	hIsoRawVSEta_PU40->GetYaxis()->SetRange(0,10);
 hIsoRawVSEta_PU40->SetTitle("Eta vs RawIso, 13 TeV, pu40");
// hIsoRawVSEta_PU40->Draw("COLZ");

IsoRaw_cavas->cd(3);
hIsoRawVSEta_8TeV->GetYaxis()->SetRange(0,10);
hIsoRawVSEta_8TeV->SetTitle("Eta vs RawIso, 8 TeV");
hIsoRawVSEta_8TeV->Draw("COLZ");
IsoRaw_cavas->SaveAs("EtaVSIso.pdf");
*/
	/////////////////////////////////////////////////////////////////
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 1200, 800);
	canvas->Divide(2,2);
	
	TH2F* hTau_NVtxVSpuCorrPtSum_PU20 = (TH2F*)f1->Get("hTau_NVtxVSpuCorrPtSum");
	TH2F* hTau_NVtxVSpuCorrPtSum_PU40 = (TH2F*)f2->Get("hTau_NVtxVSpuCorrPtSum");
	TH2F* hTau_NVtxVSpuCorrPtSum_8TeV = (TH2F*)f3->Get("hTau_NVtxVSpuCorrPtSum");

	TH2F*	hTau_NVtxVSChIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSChIso");
	TH2F*	hTau_NVtxVSChIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSChIso");
	TH2F*	hTau_NVtxVSChIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSChIso");

	
	TH2F*    hTau_NVtxVSNeIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNeIso");
	TH2F*    hTau_NVtxVSNeIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNeIso");
	TH2F*    hTau_NVtxVSNeIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSNeIso");

	TH2F*    hTau_NVtxVSRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSRawIso");
	TH2F*    hTau_NVtxVSRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSRawIso");
	TH2F*    hTau_NVtxVSRawIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSRawIso");
	
	TH2F*    hTau_NVtxVSNewRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNewRawIso");
	TH2F*    hTau_NVtxVSNewRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNewRawIso");

	
	canvas->cd(1);
	hTau_NVtxVSChIso_PU20->ProfileX("prof_ch20",0,70);
	hTau_NVtxVSChIso_PU40->ProfileX("prof_ch40",0,70);
	hTau_NVtxVSChIso_8TeV->ProfileX("prof_ch8tev",0,70);
	
	prof_ch40->SetMarkerStyle(20);
	prof_ch20->SetMarkerStyle(20);
	prof_ch8tev->SetMarkerStyle(20);
	
	//prof_ch40->SetMarkerSize(0.8);
//	prof_ch20->SetMarkerSize(0.8);
//	prof_ch8tev->SetMarkerSize(0.8);
	prof_ch40->SetMarkerColor(kBlue);
	prof_ch20->SetMarkerColor(kMagenta);	

	prof_ch40->Draw();
	prof_ch20->Draw("SAME");
	prof_ch8tev->Draw("SAME");
	
	TF1  *fun_CH_PU40 = new TF1("fun_CH_PU40"," [0]*x + [1]",0,70) ; 
	TF1  *fun_CH_PU20 = new TF1("fun_CH_PU20"," [0]*x + [1]",0,70) ; 
	TF1  *fun_CH_8TEV = new TF1("fun_CH_8TEV"," [0]*x + [1]",0,70) ; 
	cout<<" ************************************************************ fit ch iso pu40  ************************************************************"<<endl;
	prof_ch40->Fit("fun_CH_PU40","N0");
	//cout<<" charged, pu40 slope="<<fun_CH_PU40->GetParameter(0)<<" err="<<fun_CH_PU40->GetParError(0)<<" offset="<<fun_CH_PU40->GetParameter(1)<<" err="<<fun_CH_PU40->GetParError(1)<<endl;
	cout<<"************************************************************  fit ch iso pu20  ************************************************************"<<endl;
	prof_ch20->Fit("fun_CH_PU20","N0");
	//cout<<" charged, pu40 slope="<<fun_CH_PU20->GetParameter(0)<<" err="<<fun_CH_PU20->GetParError(0)<<" offset="<<fun_CH_PU20->GetParameter(1)<<" err="<<fun_CH_PU20->GetParError(1)<<endl;
	cout<<"************************************************************  fit ch iso 8tev  ************************************************************"<<endl;
	prof_ch8tev->Fit("fun_CH_8TEV","N0");	
	
	fun_CH_8TEV->SetParameter(0,fun_CH_8TEV->GetParameter(0));
	fun_CH_8TEV->SetParameter(1,fun_CH_8TEV->GetParameter(1));
	
	fun_CH_PU40->SetParameter(0,fun_CH_PU40->GetParameter(0));
	fun_CH_PU40->SetParameter(1,fun_CH_PU40->GetParameter(1));
	
	fun_CH_PU20->SetParameter(0,fun_CH_PU20->GetParameter(0));
	fun_CH_PU20->SetParameter(1,fun_CH_PU20->GetParameter(1));
	
	fun_CH_8TEV ->SetLineColor(kBlack); fun_CH_8TEV->Draw("same");
	fun_CH_PU20 ->SetLineColor(kMagenta); fun_CH_PU20->Draw("same");
	fun_CH_PU40 ->SetLineColor(kBlue); fun_CH_PU40->Draw("same");
	
	
	
	canvas->cd(2);
	hTau_NVtxVSpuCorrPtSum_PU20->ProfileX("prof1", 0,60);
	hTau_NVtxVSpuCorrPtSum_PU40->ProfileX("prof2", 0,60);
	hTau_NVtxVSpuCorrPtSum_8TeV->ProfileX("prof3", 0,50);

	
	prof1->SetMarkerStyle(20);
	prof2->SetMarkerStyle(20);
	prof3->SetMarkerStyle(20);
	
	prof1->SetMarkerColor(kMagenta);
	prof2->SetMarkerColor(kBlue);
	
	prof2->Draw();
	prof1->Draw("SAME"); 
	prof3->Draw("SAME");   
	prof2->SetMinimum(0);
	
	TF1  *funPU40 = new TF1("funPU40"," [0]*x + [1]",0,60) ; 
	TF1  *funPU20 = new TF1("funPU20"," [0]*x + [1]",0,60) ; 
	TF1  *fun8TEV = new TF1("fun8TEV"," [0]*x + [1] ",0,50) ; 
	
	cout<<" ************************************************************ fit PUCorr pu40  ************************************************************"<<endl;
	prof2->Fit("funPU40","N0");
	cout<<" ************************************************************ fit PUCorr pu20  ************************************************************"<<endl;
	prof1->Fit("funPU20","N0");
	cout<<" ************************************************************ fit PUCorr 8tev  ************************************************************"<<endl;
	prof3->Fit("fun8TEV","N0");	
	
	fun8TEV->SetParameter(0,fun8TEV->GetParameter(0));
	fun8TEV->SetParameter(1,fun8TEV->GetParameter(1));
	
	funPU40->SetParameter(0,funPU40->GetParameter(0));
	funPU40->SetParameter(1,funPU40->GetParameter(1));
	
	funPU20->SetParameter(0,funPU20->GetParameter(0));
	funPU20->SetParameter(1,funPU20->GetParameter(1));
	
	fun8TEV ->SetLineColor(kBlack); fun8TEV->Draw("same");
	funPU20 ->SetLineColor(kMagenta); funPU20->Draw("same");
	funPU40 ->SetLineColor(kBlue); funPU40->Draw("same");

	TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(fun8TEV, "Summer12, 8 TeV");
	legend->AddEntry(funPU20, "Fall13, 13 TeV, PU20, bx25");
	legend->AddEntry(funPU40, "Fall13, 13 TeV, PU40, bx25");
	canvas->cd(2);
	legend->Draw("same");
	
	canvas->cd(3);
	hTau_NVtxVSNeIso_PU20->ProfileX("prof_ne20", 0,70);
	hTau_NVtxVSNeIso_PU40->ProfileX("prof_ne40", 0,70);
	hTau_NVtxVSNeIso_8TeV->ProfileX("prof_ne8tev", 0,70);
	prof_ne20->SetLineColor(kMagenta);
	prof_ne40->SetLineColor(kBlue);
	
	
	prof_ne40->SetMarkerStyle(20);
	prof_ne20->SetMarkerStyle(20);
	prof_ne8tev->SetMarkerStyle(20);
	
	prof_ne40->SetMarkerColor(kBlue);
	prof_ne20->SetMarkerColor(kMagenta);
	
	
	prof_ne40->Draw();
	prof_ne20->Draw("SAME");
	prof_ne8tev->Draw("SAME");
	prof_ne40->SetMinimum(0);
	//prof_ne40->Fit("pol1");
	
	TF1  *fun_NE_PU40 = new TF1("fun_NE_PU40"," [0]*x + [1]",0,70) ; 
	TF1  *fun_NE_PU20 = new TF1("fun_NE_PU20"," [0]*x + [1]",0,70) ; 
	TF1  *fun_NE_8TEV = new TF1("fun_NE_8TEV"," [0]*x + [1]",0,70) ; 
	
	cout<<" ************************************************************ fit ne iso pu40 ************************************************************"<<endl;
	prof_ne40->Fit("fun_NE_PU40","N0");
	cout<<" ************************************************************ fit ne iso pu20 ************************************************************"<<endl;
	prof_ne20->Fit("fun_NE_PU20","N0");
	cout<<" ************************************************************ fit ne iso 8tev ************************************************************"<<endl;
	prof_ne8tev->Fit("fun_NE_8TEV","N0");	
	
	fun_NE_8TEV->SetParameter(0,fun_NE_8TEV->GetParameter(0));
	fun_NE_8TEV->SetParameter(1,fun_NE_8TEV->GetParameter(1));
	
	fun_NE_PU40->SetParameter(0,fun_NE_PU40->GetParameter(0));
	fun_NE_PU40->SetParameter(1,fun_NE_PU40->GetParameter(1));
	
	fun_NE_PU20->SetParameter(0,fun_NE_PU20->GetParameter(0));
	fun_NE_PU20->SetParameter(1,fun_NE_PU20->GetParameter(1));
	
	fun_NE_8TEV ->SetLineColor(kBlack); fun_NE_8TEV->Draw("same");
	fun_NE_PU20 ->SetLineColor(kMagenta); fun_NE_PU20->Draw("same");
	fun_NE_PU40 ->SetLineColor(kBlue); fun_NE_PU40->Draw("same");
	
	canvas->cd(4);
	hTau_NVtxVSRawIso_PU20->ProfileX("prof_iso20", 0,70);
	hTau_NVtxVSRawIso_PU40->ProfileX("prof_iso40", 0,70);
	hTau_NVtxVSRawIso_8TeV->ProfileX("prof_iso8tev", 0,70);
	prof_iso8tev->SetMarkerStyle(20);
	prof_iso20->SetMarkerStyle(20);
	prof_iso40->SetMarkerStyle(20);
	prof_iso20->SetMarkerColor(kMagenta);
	prof_iso40->SetMarkerColor(kBlue);
	prof_iso40->Draw();
	prof_iso20->Draw("SAME");
	prof_iso8tev->Draw("SAME");
	prof_iso40->SetMinimum(0);
	canvas->SaveAs("IsoVSNVtx.pdf");

	cout<<"  charged slope;  offeset"<<endl;
	cout<<setprecision(3)<<"  pu40;"<<fun_CH_PU40->GetParameter(0)<<" ± "<<fun_CH_PU40->GetParError(0)<<"; offset;"<<fun_CH_PU40->GetParameter(1)<<"  ± "<<fun_CH_PU40->GetParError(1)<<endl;
	cout<<"  pu20;"<<fun_CH_PU20->GetParameter(0)<<" ± "<<fun_CH_PU20->GetParError(0)<<"; offset;"<<fun_CH_PU20->GetParameter(1)<<"  ± "<<fun_CH_PU20->GetParError(1)<<endl;
	cout<<"  8tev;"<<fun_CH_8TEV->GetParameter(0)<<" ± "<<fun_CH_8TEV->GetParError(0)<<"; offset;"<<fun_CH_8TEV->GetParameter(1)<<"  ± "<<fun_CH_8TEV->GetParError(1)<<endl;
	
	cout<<"  neutral slope;  offeset"<<endl;
	cout<<"  pu40 slope;"<<fun_NE_PU40->GetParameter(0)<<" ±  "<<fun_NE_PU40->GetParError(0)<<"; offset;"<<fun_NE_PU40->GetParameter(1)<<" ± "<<fun_NE_PU40->GetParError(1)<<endl;
	cout<<"  pu20 slope;"<<fun_NE_PU20->GetParameter(0)<<" ±  "<<fun_NE_PU20->GetParError(0)<<"; offset;"<<fun_NE_PU20->GetParameter(1)<<" ± "<<fun_NE_PU20->GetParError(1)<<endl;
	cout<<"  8tev slope;"<<fun_NE_8TEV->GetParameter(0)<<" ±  "<<fun_NE_8TEV->GetParError(0)<<"; offset;"<<fun_NE_8TEV->GetParameter(1)<<" ± "<<fun_NE_8TEV->GetParError(1)<<endl;
	
	cout<<"  pu contribution slope;  offeset"<<endl;
	cout<<" pu40 slope;"<<funPU40->GetParameter(0)<<" ± "<<funPU40->GetParError(0)<<"; offset;"<<funPU40->GetParameter(1)<<" ± "<<funPU40->GetParError(1)<<endl;
	cout<<" pu20 slope;"<<funPU20->GetParameter(0)<<" ± "<<funPU20->GetParError(0)<<"; offset;"<<funPU20->GetParameter(1)<<" ±"<<funPU20->GetParError(1)<<endl;
	cout<<" 8tev slope;"<<fun8TEV->GetParameter(0)<<" ± "<<fun8TEV->GetParError(0)<<"; offset;"<<fun8TEV->GetParameter(1)<<" ±"<<fun8TEV->GetParError(1)<<endl;
	
	cout<<"  RATIO NE/PU"<<endl;
	cout << "  pu40;"<<fun_NE_PU40->GetParameter(0)/funPU40->GetParameter(0)<<" ± "<<(fun_NE_PU40->GetParameter(0)/funPU40->GetParameter(0)) * TMath::Sqrt( (funPU40->GetParError(0)/funPU40->GetParameter(0))*(funPU40->GetParError(0)/funPU40->GetParameter(0)) + (fun_NE_PU40->GetParError(0)/fun_NE_PU40->GetParameter(0))*(fun_NE_PU40->GetParError(0)/fun_NE_PU40->GetParameter(0)) ) <<endl;
	cout << "  pu20;"<<fun_NE_PU20->GetParameter(0)/funPU20->GetParameter(0)<<" ± "<<(fun_NE_PU20->GetParameter(0)/funPU20->GetParameter(0)) * TMath::Sqrt( (funPU20->GetParError(0)/funPU20->GetParameter(0))*(funPU20->GetParError(0)/funPU20->GetParameter(0)) + (fun_NE_PU40->GetParError(0)/fun_NE_PU20->GetParameter(0))*(fun_NE_PU20->GetParError(0)/fun_NE_PU20->GetParameter(0)) ) <<endl;
	cout << "  8tev;"<<fun_NE_8TEV->GetParameter(0)/fun8TEV->GetParameter(0)<<" ± "<<(fun_NE_8TEV->GetParameter(0)/fun8TEV->GetParameter(0)) * TMath::Sqrt( (fun8TEV->GetParError(0)/fun8TEV->GetParameter(0))*(fun8TEV->GetParError(0)/fun8TEV->GetParameter(0)) + (fun_NE_8TEV->GetParError(0)/fun_NE_8TEV->GetParameter(0))*(fun_NE_8TEV->GetParError(0)/fun_NE_8TEV->GetParameter(0)) ) <<endl;
	   
	
	
	
	TCanvas *CorrelationPU = new TCanvas("CorrelationPU","CorrelationPU",1200,400);
	CorrelationPU->Divide(2,1);
	TH2F*    hTau_NeIsoVSpuCorrIso_PU20 = (TH2F*)f1->Get("hTau_NeIsoVSpuCorrIso");
	TH2F*    hTau_NeIsoVSpuCorrIso_PU40 = (TH2F*)f2->Get("hTau_NeIsoVSpuCorrIso");
	TH2F*    hTau_NeIsoVSpuCorrIso_8TeV = (TH2F*)f3->Get("hTau_NeIsoVSpuCorrIso");
	CorrelationPU->cd(1);
	cout<<" CORRELATION FACTOR PU20	"<<	hTau_NeIsoVSpuCorrIso_PU20->GetCorrelationFactor()<<endl;
	hTau_NeIsoVSpuCorrIso_PU20->SetTitle("13TeV, PU20, NeIso vs PUIso");
	hTau_NeIsoVSpuCorrIso_PU20->Draw("COLZ");
	hTau_NeIsoVSpuCorrIso_PU20->GetXaxis()->SetTitle("I_{PU}");;
	hTau_NeIsoVSpuCorrIso_PU20->GetYaxis()->SetTitle("I_{neutral}");;
	CorrelationPU->cd(2);
	hTau_NeIsoVSpuCorrIso_PU40->SetTitle("13TeV, PU40, NeIso vs PUIso");
	hTau_NeIsoVSpuCorrIso_PU40->GetXaxis()->SetTitle("I_{PU}");;
	hTau_NeIsoVSpuCorrIso_PU40->GetYaxis()->SetTitle("I_{neutral}");;
	cout<<" CORRELATION FACTOR PU40	"<<	hTau_NeIsoVSpuCorrIso_PU40->GetCorrelationFactor()<<endl;
	hTau_NeIsoVSpuCorrIso_PU40->Draw("COLZ");
	/*CorrelationPU->cd(3);
	hTau_NeIsoVSpuCorrIso_8TeV->GetXaxis()->SetTitle("I_{PU}");;
	hTau_NeIsoVSpuCorrIso_8TeV->GetYaxis()->SetTitle("I_{neutral}");;
	hTau_NeIsoVSpuCorrIso_8TeV->SetTitle("8TeV, NeIso vs PUIso");
	hTau_NeIsoVSpuCorrIso_8TeV->Draw("COLZ");
	cout<<" CORRELATION FACTOR 8TeV	"<<	hTau_NeIsoVSpuCorrIso_8TeV->GetCorrelationFactor()<<endl;/
	
	
	
	
	
	////////////////////NEW ISO/////////////////////////////////////////////
	
/*	
	TCanvas *IsolationComparison = new TCanvas("IsolationComparison","IsolationComparison",1200,500);
	IsolationComparison->Divide(2,1);
	IsolationComparison->cd(1);
	gPad->SetLogy();        
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->SetLineColor(kMagenta);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->SetLineColor(kBlue);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->SetLineColor(kBlack);
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Rebin(2);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Rebin(2);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Rebin(2);
	
	hTau_NewRawIsoCE_PU20->SetMarkerColor(kMagenta);
	hTau_NewRawIsoCE_PU40->SetMarkerColor(kBlue);
	hTau_NewRawIsoCE_PU20->SetMarkerStyle(23);
	hTau_NewRawIsoCE_PU40->SetMarkerStyle(23);
	
	hTau_NewRawIsoEtaCorr_PU20->SetMarkerStyle(23);
	hTau_NewRawIsoEtaCorr_PU20->SetMarkerColor(kMagenta+2);	
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral());
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral());
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral());
	
	hTau_NewRawIsoCE_PU20->Scale(1/hTau_NewRawIsoCE_PU20->Integral());
	hTau_NewRawIsoCE_PU40->Scale(1/hTau_NewRawIsoCE_PU40->Integral());
	
	hTau_NewRawIsoEtaCorr_PU20->Scale(1/hTau_NewRawIsoEtaCorr_PU20->Integral());
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->GetXaxis()->SetTitle("Isolation [GeV]");
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Draw("HISTE");
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Draw("SAMEHISTE");
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Draw("SAMEHISTE");
	hTau_NewRawIsoCE_PU20->Draw("SAME");
	hTau_NewRawIsoCE_PU40->Draw("SAME");    
	hTau_NewRawIsoEtaCorr_PU20->Draw("SAME");  
	
	
	TLegend* legend = new TLegend( 0.3, 0.6, 0.99, 0.9);
	legend->SetTextSize(0.03);
	legend->SetFillColor(0);
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV, "Summer12, 8 TeV");
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20, "Fall13, 13 TeV, PU20, bx25 RawIso3H");
	legend->AddEntry(hTau_NewRawIsoCE_PU20, "Fall13, 13 TeV, PU20, bx25, NewRawIso3H");
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40, "Fall13, 13 TeV, PU40, bx25 RawIso3H");
	legend->AddEntry(hTau_NewRawIsoCE_PU40, "Fall13, 13 TeV, PU40, bx25, NewRawIso3H");
	IsolationComparison->cd(1);
	legend->Draw("same");
	
	
	IsolationComparison->cd(2);
	hTau_NVtxVSRawIso_PU20->ProfileX("prof_iso20", 0,70);
	hTau_NVtxVSRawIso_PU40->ProfileX("prof_iso40", 0,70);
	
	hTau_NVtxVSNewRawIso_PU20->ProfileX("prof_newiso20", 0,70);
	hTau_NVtxVSNewRawIso_PU40->ProfileX("prof_newiso40", 0,70);
	
	hTau_NVtxVSRawIso_8TeV->ProfileX("prof_iso8tev", 0,70);
	prof_iso20->SetLineColor(kMagenta);
	prof_iso40->SetLineColor(kBlue);
	prof_newiso20->SetMarkerColor(kMagenta);
	prof_newiso40->SetMarkerColor(kBlue);
//	prof_iso20->SetMarkerStyle(20);
//	prof_iso40->SetMarkerStyle(20);
	prof_newiso20->SetMarkerStyle(23);
	prof_newiso40->SetMarkerStyle(23);

	prof_iso40->GetXaxis()->SetTitle("NPV");
	prof_iso40->GetYaxis()->SetTitle("<Isolation>");
	prof_iso40->SetTitle("Mean Raw Isolation VS NPV");
	prof_iso40->Draw();
	prof_iso20->Draw("SAME");
	prof_iso8tev->Draw("SAME");
	prof_newiso20->Draw("SAME");
	prof_newiso40->Draw("SAME");
	prof_iso40->SetMinimum(0);
	IsolationComparison->SaveAs("RawIsolationComp.pdf");
 */
	 
	////////////////////NEW ISO/////////////////////////////////////////////        
	
    TH1D *ProjYNeIso20[70]; TH1D *ProjYNeIso40[70];
	float media =0; float media20 =0;
	float pesi =0; float pesi20	=0; 

	
	for(int i=0;i<50;++i){
	
	ProjYNeIso20[i] = hTau_NVtxVSNeIso_PU20->ProjectionY("ProjYNeIso", i, i+1); 
		if( (ProjYNeIso20[i]->GetEntries()) > 100){
		cout<<"PU 20: NVTX="<<i<<" media  "<<ProjYNeIso20[i]->GetMean()<<" RMS  "<<ProjYNeIso20[i]->GetRMS()<<" entries "<<ProjYNeIso20[i]->GetEntries()<<endl;
			media20 += (ProjYNeIso20[i]->GetRMS())/(1/(ProjYNeIso20[i]->GetEntries())*(ProjYNeIso20[i]->GetEntries()));
			pesi20 += 1/(ProjYNeIso20[i]->GetEntries())*(ProjYNeIso20[i]->GetEntries()) ;

		}
	}
	
	
	for(int i=0;i<60;++i){
		
		ProjYNeIso40[i] = hTau_NVtxVSNeIso_PU40->ProjectionY("ProjYNeIso40", i, i+1); 
		if( (ProjYNeIso40[i]->GetEntries()) > 100){
		cout<<" PU 40: NVTX="<<i<<" media  "<<ProjYNeIso40[i]->GetMean()<<" RMS  "<<ProjYNeIso40[i]->GetRMS()<<" entries "<<ProjYNeIso40[i]->GetEntries()<<endl;
			media += (ProjYNeIso40[i]->GetRMS())/(1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries()));
			pesi += 1/(ProjYNeIso40[i]->GetEntries())*(ProjYNeIso40[i]->GetEntries()) ;
		
		}
	}
	
	cout<<" rms medio  pu 40 ="<<media/pesi<<endl;
	cout<<" RMS medio  pu 20 ="<<media20/pesi20<<endl;
	
	TCanvas *palle= new TCanvas("palle","palle",1200,500);
	ProjYNeIso20[20]->SetLineColor(kRed);
	ProjYNeIso20[20]->Draw();
	
	TFile *outFile = new TFile("VtxVsIso_noDM.root","RECREATE");
	hTau_NVtxVSpuCorrPtSum_PU40->Write();
	hTau_NVtxVSNeIso_PU40->Write();
	hTau_neutralIsoPtSum_PU40->Write("NeutralIso");
	outFile->Close();
	
}

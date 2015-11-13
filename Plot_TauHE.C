#include <TH1>
void Plot_TauHE(){

  ////////////////////////////////////////////////////////////////////////////
	TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");
	TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");
	TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");

  gStyle->SetOptStat(0000000);
 
  TH1F* hTau_chargedIsoPtSum_PU20 = (TH1F*)f1->Get("hTau_chargedIsoPtSum_HE");
  TH1F* hTau_neutralIsoPtSum_PU20 = (TH1F*)f1->Get("hTau_neutralIsoPtSum_HE");
  TH1F* hTau_puCorrPtSum_PU20 = (TH1F*)f1->Get("hTau_puCorrPtSum_HE");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20 = (TH1F*)f1->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_HE");
  TH1F* hTau_NewRawIsoHE_PU20 = (TH1F*)f1->Get("hTau_NewRawIsoHE");		

  TH1F* hTau_chargedIsoPtSum_PU40 = (TH1F*)f2->Get("hTau_chargedIsoPtSum_HE");
  TH1F* hTau_neutralIsoPtSum_PU40 = (TH1F*)f2->Get("hTau_neutralIsoPtSum_HE");
  TH1F* hTau_puCorrPtSum_PU40 = (TH1F*)f2->Get("hTau_puCorrPtSum_HE");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40 = (TH1F*)f2->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_HE");
	 TH1F* hTau_NewRawIsoHE_PU40 = (TH1F*)f2->Get("hTau_NewRawIsoHE");		

  TH1F* hTau_chargedIsoPtSum_8TeV = (TH1F*)f3->Get("hTau_chargedIsoPtSum_HE");
  TH1F* hTau_neutralIsoPtSum_8TeV = (TH1F*)f3->Get("hTau_neutralIsoPtSum_HE");
  TH1F* hTau_puCorrPtSum_8TeV = (TH1F*)f3->Get("hTau_puCorrPtSum_HE");
  TH1F* hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV = (TH1F*)f3->Get("hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_HE");
	
 
  TCanvas *IsolationVar = new TCanvas("IsolationVar","Isolation Contribution",1600,800);
  IsolationVar->Divide(2,2);
  
  IsolationVar->cd(1);
  gPad->SetLogy();
  hTau_chargedIsoPtSum_PU20->SetLineColor(kBlue);
  hTau_chargedIsoPtSum_PU40->SetLineColor(kTeal);
  hTau_chargedIsoPtSum_8TeV->SetLineColor(kMagenta);

  hTau_chargedIsoPtSum_PU20->Scale(1/hTau_chargedIsoPtSum_PU20->Integral());
  hTau_chargedIsoPtSum_PU40->Scale(1/hTau_chargedIsoPtSum_PU40->Integral());
  hTau_chargedIsoPtSum_8TeV->Scale(1/hTau_chargedIsoPtSum_8TeV->Integral());

  hTau_chargedIsoPtSum_8TeV->Draw("HISTE");
  hTau_chargedIsoPtSum_PU20->Draw("SAMEHISTE");
  hTau_chargedIsoPtSum_PU40->Draw("SAMEHISTE");

  IsolationVar->cd(2);

  hTau_neutralIsoPtSum_PU20->SetLineColor(kBlue);
  hTau_neutralIsoPtSum_PU40->SetLineColor(kTeal);
  hTau_neutralIsoPtSum_8TeV->SetLineColor(kMagenta);

  hTau_neutralIsoPtSum_PU20->Scale(1/hTau_neutralIsoPtSum_PU20->Integral());
  hTau_neutralIsoPtSum_PU40->Scale(1/hTau_neutralIsoPtSum_PU40->Integral());
  hTau_neutralIsoPtSum_8TeV->Scale(1/hTau_neutralIsoPtSum_8TeV->Integral());

  hTau_neutralIsoPtSum_8TeV->Draw("HISTE"); 
  hTau_neutralIsoPtSum_PU20->Draw("SAMEHISTE");
  hTau_neutralIsoPtSum_PU40->Draw("SAMEHISTE");

  IsolationVar->cd(3);

  hTau_puCorrPtSum_PU20->SetLineColor(kBlue);
  hTau_puCorrPtSum_PU40->SetLineColor(kTeal);
  hTau_puCorrPtSum_8TeV->SetLineColor(kMagenta);

  hTau_puCorrPtSum_PU20->Scale(1/hTau_puCorrPtSum_PU20->Integral());
  hTau_puCorrPtSum_PU40->Scale(1/hTau_puCorrPtSum_PU40->Integral());
  hTau_puCorrPtSum_8TeV->Scale(1/hTau_puCorrPtSum_8TeV->Integral());

  hTau_puCorrPtSum_8TeV->Draw("HISTE");
  hTau_puCorrPtSum_PU20->Draw("SAMEHISTE");
  hTau_puCorrPtSum_PU40->Draw("SAMEHISTE");
 
  
  
  IsolationVar->cd(4);
gPad->SetLogy();
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->SetLineColor(kBlue);
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->SetLineColor(kTeal);
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->SetLineColor(kMagenta);
	
	hTau_NewRawIsoHE_PU20->SetMarkerColor(kBlue);
	hTau_NewRawIsoHE_PU40->SetMarkerColor(kTeal);
	hTau_NewRawIsoHE_PU20->SetMarkerStyle(23);
	hTau_NewRawIsoHE_PU40->SetMarkerStyle(23);

  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral());
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral());
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral());
	
	hTau_NewRawIsoHE_PU20->Scale(1/hTau_NewRawIsoHE_PU20->Integral());
	hTau_NewRawIsoHE_PU40->Scale(1/hTau_NewRawIsoHE_PU40->Integral());

	

  std::cout<<" iso>2 8 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral(4,100)<<endl;
  std::cout<<" iso>2 pu20 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral(4,100)<<endl;
  std::cout<<" iso>2 pu40 tev  "<<hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral(4,100)<<endl;
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Draw("HISTE");
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Draw("SAMEHISTE");
  hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Draw("SAMEHISTE");
	
	hTau_NewRawIsoHE_PU20->Draw("SAME");
	hTau_NewRawIsoHE_PU40->Draw("SAME");
	
 
 
  TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.3);
 legend->SetTextSize(0.035);
 legend->SetFillColor(0);
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV, "Summer12, 8 TeV","f");
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20, "Fall13, 13 TeV, PU20, bx25","f");
 legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40, "Fall13, 13 TeV, PU40, bx25","f");
 IsolationVar->cd(4);
 legend->Draw("same");

 IsolationVar->SaveAs("IsolationVarHE.pdf");
	
	
	
	
	/////////////////////////////////////////////////////////////////
	
	TCanvas* canvas = new TCanvas("canvas", "canvas", 1200, 800);
	canvas->Divide(2,2);
	
	TH2F* hTau_NVtxVSpuCorrPtSum_PU20 = (TH2F*)f1->Get("hTau_NVtxVSpuCorrPtSum_HE");
	TH2F* hTau_NVtxVSpuCorrPtSum_PU40 = (TH2F*)f2->Get("hTau_NVtxVSpuCorrPtSum_HE");
	TH2F* hTau_NVtxVSpuCorrPtSum_8TeV = (TH2F*)f3->Get("hTau_NVtxVSpuCorrPtSum_HE");
	
	TH2F*   hTau_NVtxVSChIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSChIso_HE");
	TH2F*   hTau_NVtxVSChIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSChIso_HE");
	TH2F*   hTau_NVtxVSChIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSChIso_HE");
	
	
	TH2F*    hTau_NVtxVSNeIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNeIso_HE");
	TH2F*    hTau_NVtxVSNeIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNeIso_HE");
	TH2F*    hTau_NVtxVSNeIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSNeIso_HE");
	
	TH2F*    hTau_NVtxVSRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSRawIso_HE");
	TH2F*    hTau_NVtxVSRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSRawIso_HE");
	TH2F*    hTau_NVtxVSRawIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSRawIso_HE");
	
	TH2F*    hTau_NVtxVSNewRawIso_PU20 = (TH2F*)f1->Get("hTau_NVtxVSNewRawIso_HE");
	TH2F*    hTau_NVtxVSNewRawIso_PU40 = (TH2F*)f2->Get("hTau_NVtxVSNewRawIso_HE");
	TH2F*    hTau_NVtxVSNewRawIso_8TeV = (TH2F*)f3->Get("hTau_NVtxVSNewRawIso_HE");
	
	
	
	canvas->cd(1);
	hTau_NVtxVSChIso_PU20->ProfileX("prof_ch20",0,70);
	hTau_NVtxVSChIso_PU40->ProfileX("prof_ch40",0,70);
	hTau_NVtxVSChIso_8TeV->ProfileX("prof_ch8tev",0,70);
	prof_ch20->SetLineColor(kTeal);
	prof_ch40->SetLineColor(kBlue);
	prof_ch40->Draw();
	prof_ch20->Draw("SAME");
	prof_ch8tev->Draw("SAME");
	
	
	TF1  *fun_CH_PU40 = new TF1("fun_CH_PU40"," [0]*x + [1]",0,70) ; 
	TF1  *fun_CH_PU20 = new TF1("fun_CH_PU20"," [0]*x + [1]",0,70) ; 
	TF1  *fun_CH_8TEV = new TF1("fun_CH_8TEV"," [0]*x + [1]",0,70) ; 
	cout<<" ************************************************************ fit ch iso pu40  ************************************************************"<<endl;
	prof_ch40->Fit("fun_CH_PU40","N0");
	cout<<"************************************************************  fit ch iso pu20  ************************************************************"<<endl;
	prof_ch20->Fit("fun_CH_PU20","N0");
	cout<<"************************************************************  fit ch iso 8tev  ************************************************************"<<endl;
	prof_ch8tev->Fit("fun_CH_8TEV","N0");   
	
	fun_CH_8TEV->SetParameter(0,fun_CH_8TEV->GetParameter(0));
	fun_CH_8TEV->SetParameter(1,fun_CH_8TEV->GetParameter(1));
	
	fun_CH_PU40->SetParameter(0,fun_CH_PU40->GetParameter(0));
	fun_CH_PU40->SetParameter(1,fun_CH_PU40->GetParameter(1));
	
	fun_CH_PU20->SetParameter(0,fun_CH_PU20->GetParameter(0));
	fun_CH_PU20->SetParameter(1,fun_CH_PU20->GetParameter(1));
	
	fun_CH_8TEV ->SetLineColor(kBlack); fun_CH_8TEV->Draw("same");
	fun_CH_PU20 ->SetLineColor(kTeal); fun_CH_PU20->Draw("same");
	fun_CH_PU40 ->SetLineColor(kBlue); fun_CH_PU40->Draw("same");
	
	
	
	canvas->cd(2);
	hTau_NVtxVSpuCorrPtSum_PU20->ProfileX("prof1", 0,60);
	hTau_NVtxVSpuCorrPtSum_PU40->ProfileX("prof2", 0,60);
	hTau_NVtxVSpuCorrPtSum_8TeV->ProfileX("prof3", 0,60);
	prof1->SetLineColor(kTeal);  prof2->SetLineColor(kBlue);
	prof2->Draw();
	prof1->Draw("SAME"); 
	prof3->Draw("SAME");   
	prof2->SetMinimum(0);
	
	TF1  *funPU40 = new TF1("funPU40"," [0]*x ",0,60) ; 
	TF1  *funPU20 = new TF1("funPU20"," [0]*x + [1]",0,50) ; 
	TF1  *fun8TEV = new TF1("fun8TEV"," [0]*x + [1]",0,50) ; 
	
	cout<<" ************************************************************ fit PUCorr pu40  ************************************************************"<<endl;
	prof2->Fit("funPU40","N0");
	fitter = TVirtualFitter::GetFitter();
	int nPars = fitter->GetNumberFreeParameters();
	for (int i=0;i<nPars;i++){
		for (int k=0;k<nPars;k++){
			
			cout<<i<<" "<<k<<" "<<(fitter->GetCovarianceMatrixElement(i,k)/TMath::Sqrt( (fitter->GetCovarianceMatrixElement(i,i))* (fitter->GetCovarianceMatrixElement(k,k))))<<endl;
		}}
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
	funPU20 ->SetLineColor(kTeal); funPU20->Draw("same");
	funPU40 ->SetLineColor(kBlue); funPU40->Draw("same");
	
	TLegend* legend = new TLegend( 0.45, 0.15, 0.99, 0.35);
	legend->SetTextSize(0.035);
	legend->SetFillColor(0);
	legend->AddEntry(prof3, "Summer12, 8 TeV","f");
	legend->AddEntry(prof1, "Fall13, 13 TeV, PU20, bx25","f");
	legend->AddEntry(prof2, "Fall13, 13 TeV, PU40, bx25","f");
	canvas->cd(2);
	legend->Draw("same");
	
	canvas->cd(3);
	hTau_NVtxVSNeIso_PU20->ProfileX("prof_ne20", 0,70);
	hTau_NVtxVSNeIso_PU40->ProfileX("prof_ne40", 0,70);
	hTau_NVtxVSNeIso_8TeV->ProfileX("prof_ne8tev", 0,70);
	prof_ne20->SetLineColor(kTeal);
	prof_ne40->SetLineColor(kBlue);
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
	fun_NE_PU20 ->SetLineColor(kTeal); fun_NE_PU20->Draw("same");
	fun_NE_PU40 ->SetLineColor(kBlue); fun_NE_PU40->Draw("same");
	
	canvas->cd(4);
	hTau_NVtxVSRawIso_PU20->ProfileX("prof_iso20", 0,70);
	hTau_NVtxVSRawIso_PU40->ProfileX("prof_iso40", 0,70);
	
	hTau_NVtxVSNewRawIso_PU20->ProfileX("prof_newiso20", 0,70);
	hTau_NVtxVSNewRawIso_PU40->ProfileX("prof_newiso40", 0,70);
	
	hTau_NVtxVSRawIso_8TeV->ProfileX("prof_iso8tev", 0,70);
	prof_iso20->SetLineColor(kTeal);
	prof_iso40->SetLineColor(kBlue);
	
	prof_newiso20->SetLineColor(kMagenta);
	prof_newiso40->SetLineColor(kRed);
	prof_iso40->Draw();
	prof_iso20->Draw("SAME");
	prof_iso8tev->Draw("SAME");
	//prof_newiso20->Draw("SAME");
	//prof_newiso40->Draw("SAME");
	prof_iso40->SetMinimum(0);
	

	////////////////////NEW ISO/////////////////////////////////////////////
	TCanvas *IsolationComparison = new TCanvas("IsolationComparison","IsolationComparison",1200,400);
	IsolationComparison->Divide(2,1);
	IsolationComparison->cd(1);
	gPad->SetLogy();	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->SetLineColor(kBlue);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->SetLineColor(kTeal);
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->SetLineColor(kMagenta);
	
	hTau_NewRawIsoHE_PU20->SetMarkerColor(kBlue);
	hTau_NewRawIsoHE_PU40->SetMarkerColor(kTeal);
	hTau_NewRawIsoHE_PU20->SetMarkerStyle(23);
	hTau_NewRawIsoHE_PU40->SetMarkerStyle(23);
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Integral());
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Integral());
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Scale(1/hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Integral());
	
	hTau_NewRawIsoHE_PU20->Scale(1/hTau_NewRawIsoHE_PU20->Integral());
	hTau_NewRawIsoHE_PU40->Scale(1/hTau_NewRawIsoHE_PU40->Integral());
	
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV->Draw("HISTE");
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20->Draw("SAMEHISTE");
	hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40->Draw("SAMEHISTE");
	hTau_NewRawIsoHE_PU20->Draw("SAME");
	hTau_NewRawIsoHE_PU40->Draw("SAME");	
	
	
	TLegend* legend = new TLegend( 0.4, 0.7, 0.99, 0.9);
	legend->SetTextSize(0.025);
	legend->SetFillColor(0);
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_8TeV, "Summer12, 8 TeV");
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU20, "Fall13, 13 TeV, PU20, bx25 RawIso3H");
	legend->AddEntry(hTau_NewRawIsoHE_PU20, "Fall13, 13 TeV, PU20, bx25, NewRawIso3H");
	legend->AddEntry(hTau_CombinedIsolationDeltaBetaCorrRaw3Hits_PU40, "Fall13, 13 TeV, PU40, bx25 RawIso3H");
	legend->AddEntry(hTau_NewRawIsoHE_PU40, "Fall13, 13 TeV, PU40, bx25, NewRawIso3H");
	IsolationComparison->cd(1);
	legend->Draw("same");
	

	IsolationComparison->cd(2);
	hTau_NVtxVSRawIso_PU20->ProfileX("prof_iso20", 0,70);
	hTau_NVtxVSRawIso_PU40->ProfileX("prof_iso40", 0,70);
	
	hTau_NVtxVSNewRawIso_PU20->ProfileX("prof_newiso20", 0,70);
	hTau_NVtxVSNewRawIso_PU40->ProfileX("prof_newiso40", 0,70);
	
	hTau_NVtxVSRawIso_8TeV->ProfileX("prof_iso8tev", 0,70);
	prof_iso20->SetLineColor(kBlue);
	prof_iso40->SetLineColor(kTeal);
	prof_iso8tev->SetLineColor(kMagenta);
	prof_newiso20->SetMarkerColor(kBlue);
	prof_newiso40->SetMarkerColor(kTeal);
	prof_newiso20->SetMarkerStyle(23);
	prof_newiso40->SetMarkerStyle(23);
	prof_iso40->Draw();
	prof_iso20->Draw("SAME");
	prof_iso8tev->Draw("SAME");
	prof_newiso20->Draw("SAME");
	prof_newiso40->Draw("SAME");
	prof_iso40->SetMinimum(0);
	IsolationComparison->SaveAs("RawIsolation_HighEta.pdf");
	////////////////////NEW ISO/////////////////////////////////////////////	
	
	
	
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
	CorrelationPU->Divide(3,1);
	TH2F*    hTau_NeIsoVSpuCorrIso_PU20 = (TH2F*)f1->Get("hTau_NeIsoVSpuCorrIso_HE");
	TH2F*    hTau_NeIsoVSpuCorrIso_PU40 = (TH2F*)f2->Get("hTau_NeIsoVSpuCorrIso_HE");
	TH2F*    hTau_NeIsoVSpuCorrIso_8TeV = (TH2F*)f3->Get("hTau_NeIsoVSpuCorrIso_HE");
	CorrelationPU->cd(1);
	cout<<" CORRELATION FACTOR PU20	"<<	hTau_NeIsoVSpuCorrIso_PU20->GetCorrelationFactor()<<endl;
	hTau_NeIsoVSpuCorrIso_PU20->Draw("COLZ");
	CorrelationPU->cd(2);
	cout<<" CORRELATION FACTOR PU40	"<<	hTau_NeIsoVSpuCorrIso_PU40->GetCorrelationFactor()<<endl;
	hTau_NeIsoVSpuCorrIso_PU40->Draw("COLZ");
	CorrelationPU->cd(3);
	hTau_NeIsoVSpuCorrIso_8TeV->Draw("COLZ");
	cout<<" CORRELATION FACTOR 8TeV	"<<	hTau_NeIsoVSpuCorrIso_8TeV->GetCorrelationFactor()<<endl;
	

}

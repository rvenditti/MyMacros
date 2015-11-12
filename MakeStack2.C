#include <TH1>
#include <string>
#include <vector>
#include <TString.h>
#include <iostream>

using namespace std;

void MakeStack(string histoName, const bool isBlind, int r){

  std::vector<TString> fileName, TTfileName; 
  std::vector<double> crossSect, TTcrossSect;
  std::vector<double> NEvents, TT_NEvents;
  std::vector<double> color;
  std::vector<string> histoStructure;
  std::vector<double> SF;
 

	                                                                                                                                                                                 
 Double_t templBins[13] = {0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 250, 350};
  //////inserisci qua i nomi dei root file senza .root alla fine. poi filla sezione d'urto e numero di eventi iniziali per ogni file
	
  TTfileName.push_back("tt_hadr");        TTcrossSect.push_back(114.0215);  TT_NEvents.push_back(31223821);   
  TTfileName.push_back("tt_semi");        TTcrossSect.push_back(109.281);   TT_NEvents.push_back(24963676);   
  TTfileName.push_back("tt_lept");        TTcrossSect.push_back(26.1975);   TT_NEvents.push_back(12011428);   
  TTfileName.push_back("Tbar_tW");	      TTcrossSect.push_back(11.1);      TT_NEvents.push_back(493460); 
  TTfileName.push_back("T_tW");	          TTcrossSect.push_back(11.1);      TT_NEvents.push_back(497658);  	
	
//  fileName.push_back("DYJetsToLL");     crossSect.push_back(3503.7);    NEvents.push_back(30459503);   
  
//	fileName.push_back("WJets");          crossSect.push_back(36257.2);   NEvents.push_back(18393090+57709905);   
	fileName.push_back("ZZJetsTo2L2Nu");      crossSect.push_back(2.502);  NEvents.push_back(954911); 
	fileName.push_back("ZZJetsTo2L2Q");       crossSect.push_back(0.716);  NEvents.push_back(1936727);                                                                                                                                                                        
	fileName.push_back("ZZJetsTo4L");         crossSect.push_back(0.181);  NEvents.push_back(4807893);   
	
	fileName.push_back("WWJetsTo2L2Nu");          crossSect.push_back(5.824);  NEvents.push_back(1933235); 
	fileName.push_back("WZJetsTo2L2Q");           crossSect.push_back(2.207);  NEvents.push_back(3215990);                                                                                                                                                                        
	fileName.push_back("WZJetsTo3LNu");           crossSect.push_back(1.058);  NEvents.push_back(2017979);   //di questo ne stanno 2, controlla quale hanno usato

	
   double lumi= 19770;
 
	
	TFile * fileData = TFile::Open("TauPlusX.root");
	TH1F *histoData = (TH1F*)fileData->Get(histoName.c_str());	 
	
	
	TFile * fileDY= TFile::Open("DYJetsToLL.root");
	TH1F *histoDY = (TH1F*)fileDY->Get(histoName.c_str());	
	histoDY->Scale(3503.7*lumi/30459503);
	
	TH1F* histo[6];
	for(int i = 0; i < fileName.size(); i++){//Loop sui file
	 SF.push_back( crossSect[i]*lumi/NEvents[i]);
	// cout<<fileName[i]<<"  "<<SF[i]<<endl;
	  TFile * fileInDib = TFile::Open(fileName[i]+".root");
		histo[i] = (TH1F*)fileInDib->Get(histoName.c_str());
		histo[i]->Scale(SF[i]);
		//cout<<fileName[i]<<"  Entries "<<histo[i]->GetEntries()<<"  Int "<<histo[i]->Integral()<<endl;
	}
	 
	vector<double> SFtt;	 TH1F* histoTT[5];
	for(int i = 0; i < TTfileName.size();  i++){//Loop sui file
		SFtt.push_back( TTcrossSect[i]*lumi/TT_NEvents[i]);
		//cout<<TTfileName[i]<<"  "<<SF[i]<<endl;
		TFile * fileIn = TFile::Open(TTfileName[i]+".root");
		histoTT[i] = (TH1F*)fileIn->Get(histoName.c_str());
		histoTT[i]->Scale(SFtt[i]);
		//cout<<TTfileName[i]<<"  Entries "<<histoTT[i]->GetEntries()<<"  Int "<<histoTT[i]->Integral()<<endl;
	}
	
	
	TFile * fileWJets = TFile::Open("WJets_DataDriven.root");
	TH1F *histoWJets = (TH1F*)fileWJets->Get(histoName.c_str());  
		
	
	TH1F *hDiBosons=(TH1F*)histo[0]->Clone();
	hDiBosons->Add(histo[1]);
	hDiBosons->Add(histo[2]);
	hDiBosons->Add(histo[3]);
	hDiBosons->Add(histo[4]);
	hDiBosons->Add(histo[5]);
	
	
	TH1F *htt=(TH1F*)histoTT[0]->Clone();
	htt->Add(histoTT[1]);
	htt->Add(histoTT[2]);
	htt->Add(histoTT[3]);
	htt->Add(histoTT[4]);
		
	TFile * fileQCD = TFile::Open("QCD.root");
	TH1F *histoQCD = (TH1F*)fileQCD->Get(histoName.c_str());	 
		
	
	
		
	TFile *input = new TFile("input.root","RECREATE");
	histoDY->Write("ZLL");
	histoData->Write("Obs");
	hDiBosons->Write("VV");
	histoWJets->Write("W");
	htt->Write("TT");
	histoQCD->Write("QCD");
	input->Close();
	
	/////////////////////////////////////////Plot////////////////////////////////////////////////
	THStack * hs = new THStack(histoName.c_str(),histoName.c_str());
	TCanvas * cvStack = new TCanvas("","",700,700); 
	
	TH1F *hEWK=(TH1F*)histoWJets->Clone();
	hEWK->Add(hDiBosons);
	
	cout<<" DY  "<<histoDY->Integral()<<endl;
	cout<<" EWK "<<hEWK->Integral()<<endl;
	cout<<" TT "<<htt->Integral()<<endl;
	cout<<" QCD "<<histoQCD->Integral()<<endl;
	cout<<" SumExpected "<<	histoDY->Integral() + histoWJets->Integral() + hDiBosons->Integral() + htt->Integral() + histoQCD->Integral() <<endl;
	cout<<" Obs  "<<histoData->Integral()<<endl;
	
	cout<<" nbins DY "<<histoDY->GetNbinsX()<<endl;
	cout<<" nbins ewk "<<hEWK->GetNbinsX()<<endl;
	cout<<" nbins TT "<<htt->GetNbinsX()<<endl;	
	cout<<" nbins qcd "<<histoQCD->GetNbinsX()<<endl;
	cout<<" nbins Data "<<histoData->GetNbinsX()<<endl;

	
	
//	TLegend *legend=new TLegend(0.6,0.45,0.88,0.85);
	 TLegend* legend = new TLegend(0.52, 0.58, 0.82, 0.89);
	legend->SetFillColor(0);
	legend->SetTextSize(0.04);
	
	histoQCD->SetFillColor(TColor::GetColor(250,202,255));
	hEWK->SetFillColor(TColor::GetColor(222,90,106));
//	hDiBosons->SetFillColor(TColor::GetColor(222,90,100));
	htt->SetFillColor(TColor::GetColor(155,152,204));
	histoDY->SetFillColor(TColor::GetColor(248,206,104));
	
	
	TH1F* refill(TH1F* hin){
		TH1F* houtMC= (TH1F*)hin->Clone(); houtMC->Clear();
		for(int i=0; i<houtMC->GetNbinsX(); ++i){
			houtMC->SetBinContent(i+1, hin->GetBinContent(i+1)/hin->GetBinWidth(i+1));
			houtMC->SetBinError(i+1, 0.);
		}
		return houtMC;
	}

	
	 TH1F* histoQCD1 = (histoQCD);
	 TH1F* hEWK1      = (hEWK);
	 TH1F* htt1       = (htt);
	 TH1F* histoDY1   = (histoDY);
	 TH1F* histoData1         = (histoData);
	
	
	if (isBlind){
	TH1F* histoQCD_Reb = histoQCD1->Rebin(12,"histoQCD_Reb",templBins);
    TH1F* hEWK_Reb = hEWK1->Rebin(12,"hEWK_Reb",templBins);
    TH1F* htt_Reb = htt1->Rebin(12,"htt_Reb",templBins);
    TH1F* histoDY_Reb = histoDY1->Rebin(12,"histoDY_Reb",templBins);
    }
	else {
		
		
		TH1F* histoQCD_Reb = histoQCD1->Rebin(r);
		TH1F* hEWK_Reb = hEWK1->Rebin(r);
		TH1F* htt_Reb = htt1->Rebin(r);
		TH1F* histoDY_Reb = histoDY1->Rebin(r);
	}
	
	hs->Add(histoQCD_Reb);
	hs->Add(hEWK_Reb);
	hs->Add(htt_Reb);
	hs->Add(histoDY_Reb);
	
	float blinding_SM(float mass){ return (100<mass && mass<150); }
	
	if(isBlind==true){
	TH1F* hout = (TH1F*)histoData1->Clone(); hout->Clear();
	for(int i=0; i<hout->GetNbinsX(); ++i){
			hout->SetBinContent(i+1, blinding_SM (histoData->GetBinCenter(i+1)) ? 0. : histoData->GetBinContent(i+1));
			hout->SetBinError (i+1,  blinding_SM (histoData->GetBinCenter(i+1)) ? 0. : histoData->GetBinError(i+1));
	}
	
		TH1F* histoData_Reb = hout->Rebin(12,"histoData_Reb",templBins);
	}
	else{
		TH1F* hout = (TH1F*)histoData1->Clone();
		TH1F* histoData_Reb = hout->Rebin(r);	}
	
	//TH1F* histoData_Reb = hout->Rebin(24,"histoData_Reb",templBins);
	
	histoData_Reb->SetMarkerStyle(20);
	hs->Draw("HIST");
	histoData_Reb->Draw("samepP0E");
	 if ( histoData_Reb->GetMaximum() > hs->GetMaximum()) hs->SetMaximum(histoData_Reb->GetMaximum()*2);
	hs->GetXaxis()->SetTitle("m_{#tau#tau}^{sv}");
	
	legend->AddEntry(histoQCD,"QCD","f");
	legend->AddEntry(hEWK,"EWK","f");
	legend->AddEntry(htt,"t#bar t","f");
	legend->AddEntry(histoDY,"Z #rightarrow ll","f");
	
	legend->AddEntry(histoData_Reb,"Observed","LP");
	
	
	std::string nameForSaving = histoName + ".pdf";
		
	legend->Draw();
	cvStack->Print(nameForSaving.c_str());  
	

	
}	
		
void GetStack(){
	MakeStack("hDitau_sv",true, 1);
	MakeStack("hMass_bb",false, 14);
	MakeStack("hMuonPt",false, 10 );
	MakeStack("hTauPt",false, 10);
	MakeStack("hMuonEta",false, 10);
	MakeStack("hTauEta",false, 10);
	MakeStack("hMass_bbtt", false, 10);
	MakeStack("hMvaMet",false, 10);
}
	


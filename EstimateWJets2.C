#include <TH1>
#include <string>
#include <vector>
#include <TString.h>

using namespace std;

void EstimateWJets(string histoName, string histoNameSSISO, TFile* output){

  std::vector<TString> fileName; 
  std::vector<double> crossSect;
  std::vector<double> NEvents;
  std::vector<double> SF;
                                                                                                                                                
 
  //////inserisci qua i nomi dei root file senza .root alla fine. poi filla sezione d'urto e numero di eventi iniziali per ogni file
  fileName.push_back("tt_hadr");        crossSect.push_back(114.0215);  NEvents.push_back(31223821);   
  fileName.push_back("tt_semi");        crossSect.push_back(109.281);   NEvents.push_back(24963676);   
  fileName.push_back("tt_lept");        crossSect.push_back(26.1975);   NEvents.push_back(12011428);   
	
	fileName.push_back("Tbar_tW");	 crossSect.push_back(11.1); NEvents.push_back(493460); 
	fileName.push_back("T_tW");	     crossSect.push_back(11.1); NEvents.push_back(497658);  
	
  fileName.push_back("DYJetsToLL");     crossSect.push_back(3503.7);    NEvents.push_back(30459503);   
  
   fileName.push_back("ZZJetsTo2L2Nu");          crossSect.push_back(2.502);  NEvents.push_back(954911); 
   fileName.push_back("ZZJetsTo2L2Q");             crossSect.push_back(0.716);   NEvents.push_back(1936727);                                                                                                                                                                        
   fileName.push_back("ZZJetsTo4L");                crossSect.push_back(0.181);    NEvents.push_back(4807893);   
	
	fileName.push_back("WWJetsTo2L2Nu");          crossSect.push_back(5.824);  NEvents.push_back(1933235); 
	fileName.push_back("WZJetsTo2L2Q");             crossSect.push_back(2.207);   NEvents.push_back(3215990);                                                                                                                                                                        
	fileName.push_back("WZJetsTo3LNu");                crossSect.push_back(1.058);    NEvents.push_back(2017979);   //di questo ne stanno 2, controlla quale hanno usato
	
   fileName.push_back("TauPlusX");      


  double lumi= 19770;
  int r = 1;
	
	TFile * fileData = TFile::Open("TauPlusX.root");
	TH1F *histoData_WJetsHighMt= (TH1F*)fileData->Get(histoNameSSISO.c_str());	 
	histoData_WJetsHighMt->Rebin(r); 		
	cout<<" data Mt>70 "<<histoData_WJetsHighMt->Integral()<<endl;
	
	TH1F *hWJets_HighMt=(TH1F*)histoData_WJetsHighMt->Clone();
	TH1F* histo[12];

	for(int i = 0; i < fileName.size()-1; i++){//Loop sui file
	 SF.push_back( crossSect[i]*lumi/NEvents[i]);
		cout<<fileName[i]<<" SF="<<SF[i]<<endl;

		TFile * fileIn = TFile::Open(fileName[i]+".root");
		histo[i] = (TH1F*)fileIn->Get(histoNameSSISO.c_str());
		histo[i]->Scale(SF[i]);
		cout<<fileName[i]<<"  Entries "<<histo[i]->GetEntries()<<"  Int "<<histo[i]->Integral()<<endl;
	}
	
	hWJets_HighMt->Add(histo[0], -1);
	hWJets_HighMt->Add(histo[1], -1);
	hWJets_HighMt->Add(histo[2], -1);
	hWJets_HighMt->Add(histo[3], -1);
	hWJets_HighMt->Add(histo[4], -1);
	hWJets_HighMt->Add(histo[5], -1);
	hWJets_HighMt->Add(histo[6], -1);
	hWJets_HighMt->Add(histo[7], -1);
	hWJets_HighMt->Add(histo[8], -1);
	hWJets_HighMt->Add(histo[9], -1);
	hWJets_HighMt->Add(histo[10], -1);
	hWJets_HighMt->Add(histo[11], -1);

	cout<<"  Wjets "<<hWJets_HighMt->Integral()<<endl;
	
	
	//double crossSectWJets = 36257.2;    double NEventsWJets = (18393090+57709905);   
	//double SFWJ = crossSectWJets*lumi/NEventsWJets;
	
	TFile * fileWJets = TFile::Open("WJets.root");
	TH1F *hWJets_SideBand = (TH1F*)fileWJets->Get(histoNameSSISO.c_str());
	TH1F *hWJets_Signal = (TH1F*)fileWJets->Get(histoName.c_str());
	
	
	
	//double ScaleFactorWJets = hWJets_Signal->Integral()/hWJets_SideBand->Integral();
	//cout<<" scale factor WJ "<<ScaleFactorWJets<<endl;
	
	hWJets_HighMt->Scale(0.224898);
	
	//hWJets_HighMt->Scale(ScaleFactorWJets);
	
	cout<<"  WJets Estimate "<<hWJets_HighMt->Integral()<<endl;
	//ricordati di mettere anche gli errori giusti perchè in alcuni bin escono negativi. 
	output->cd();
	//TFile *WJets_DataDriven = new TFile("WJets_DataDriven.root","RECREATE");
	hWJets_HighMt->SetTitle(histoName.c_str());
	hWJets_HighMt->Write(histoName.c_str());
	//WJets_DataDriven->Close();
	

	
}	
	

void GetWJets(){
	TFile *WJets_DataDriven = new TFile("WJets_DataDriven.root","RECREATE");
	EstimateWJets("hDitau_sv", "hDitau_sv_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hMass_bb","hMass_bb_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hMuonPt", "hMuonPt_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hTauPt", "hTauPt_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hMuonEta", "hMuonEta_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hTauEta", "hTauEta_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hMass_bbtt", "hMass_bb_OSISO_HiMT",WJets_DataDriven);
	EstimateWJets("hMvaMet", "hMvaMet_OSISO_HiMT",WJets_DataDriven);
	WJets_DataDriven->Close();
	}

	


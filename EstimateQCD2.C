#include <TH1>
#include <string>
#include <vector>
#include <TString.h>

using namespace std;

void EstimateQCD2(string histoName, string histoNameSSISO, TFile* output){


  std::vector<TString> fileName; 
  std::vector<double> crossSect;
  std::vector<double> NEvents;
  //std::vector<string> histoName, histoNameSSISO;
  std::vector<double> SF;

	
	

//histoName.push_back("hDiTau_sv");
//	histoNameSSISO.push_back("hDitau_sv_SSISO_LowMt");    
	
 
  //////inserisci qua i nomi dei root file senza .root alla fine. poi filla sezione d'urto e numero di eventi iniziali per ogni file
	 fileName.push_back("WJets");          crossSect.push_back(36257.2);   NEvents.push_back(18393090+57709905);   
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
	
      


  double lumi= 19770;
  int r = 1;
	
	TFile * fileData = TFile::Open("TauPlusX.root");
	TH1F *histoData_SSISO = (TH1F*)fileData->Get(histoNameSSISO.c_str());	 
	histoData_SSISO->Rebin(r); 		
	cout<<" data ss iso "<<histoData_SSISO->Integral()<<endl;
	
	TH1F *hQCD=(TH1F*)histoData_SSISO->Clone();
	TH1F* histo[13];

	for(int i = 0; i < fileName.size(); i++){//Loop sui file
	 SF.push_back( crossSect[i]*lumi/NEvents[i]);
	//	cout<<fileName[i]<<" SF="<<SF[i]<<endl;

		TFile * fileIn = TFile::Open(fileName[i]+".root");
		histo[i] = (TH1F*)fileIn->Get(histoNameSSISO.c_str());
		histo[i]->Scale(SF[i]);
		cout<<fileName[i]<<"  SF="<<SF[i]<<"  Entries "<<histo[i]->GetEntries()<<"  Int "<<histo[i]->Integral()<<endl;
	}
	
	hQCD->Add(histo[0], -1);
	hQCD->Add(histo[1], -1);
	hQCD->Add(histo[2], -1);
	hQCD->Add(histo[3], -1);
	hQCD->Add(histo[4], -1);
	hQCD->Add(histo[5], -1);
	hQCD->Add(histo[6], -1);
	hQCD->Add(histo[7], -1);
	hQCD->Add(histo[8], -1);
	hQCD->Add(histo[9], -1);
	hQCD->Add(histo[10], -1);
	hQCD->Add(histo[11], -1);
	hQCD->Add(histo[12], -1);
	
	std::vector<double> err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11;

	
	for(int k=0; k<hQCD->GetNbinsX(); k++){
		
		double err = 0;
		
		err0.push_back(histo[0]->GetBinError(k));
		err1.push_back(histo[1]->GetBinError(k));
		err2.push_back(histo[2]->GetBinError(k));
		err3.push_back(histo[3]->GetBinError(k));
		err4.push_back(histo[4]->GetBinError(k));
		err5.push_back(histo[5]->GetBinError(k));
		err6.push_back(histo[6]->GetBinError(k));
		err7.push_back(histo[7]->GetBinError(k));
		err8.push_back(histo[8]->GetBinError(k));
		err9.push_back(histo[9]->GetBinError(k));
		err10.push_back(histo[10]->GetBinError(k));
		err11.push_back(histo[11]->GetBinError(k));
		
		
		err = TMath::Sqrt(err0[k]*err0[k] + err1[k]*err1[k] + err2[k]*err2[k] +err3[k]*err3[k] + err4[k]*err4[k]  + err5[k]*err5[k] +  err6[k]*err6[k] + err7[k]*err7[k] + err8[k]*err8[k] +  err9[k]*err9[k] + err10[k]*err10[k] +  err11[k]*err11[k] );						  
		
		if (hQCD->GetBinContent(k) <0) {hQCD->SetBinContent(k,0); hQCD->SetBinError(k,0); }
		else {
			hQCD->SetBinContent(k,hQCD->GetBinContent(k));  
			hQCD->SetBinError(k,  err );	
		}
		cout<<i<<"  binC "<<hQCD->GetBinContent(k)<<" err "<<hQCD->GetBinError(k)<<endl;
		
	}
	
	
	cout<<"  QCD before scaling "<<hQCD->Integral()<<endl;
		
		
	hQCD->Scale(1.06);
	cout<<"  QCD Estimate "<<hQCD->Integral()<<endl;
	//ricordati di mettere anche gli errori giusti perchè in alcuni bin escono negativi. 
	//Copia dalla macro per mu-->tau fake rate
	
	output->cd();

	hQCD->SetTitle(histoName.c_str());
	hQCD->Write(histoName.c_str());
	
	

	
}
		

void GetQCD(){
	TFile *QCD = new TFile("QCD.root","RECREATE");
	EstimateQCD2("hDitau_sv", "hDitau_sv_SSISO_LowMt", QCD);
	EstimateQCD2("hMass_bb", "hMass_bb_SSISO", QCD);
	EstimateQCD2("hMuonPt", "hMuonPt_SSISO", QCD);
    EstimateQCD2("hTauPt", "hTauPt_SSISO", QCD);	
	EstimateQCD2("hMuonEta", "hMuonEta_SSISO", QCD);
	EstimateQCD2("hTauEta", "hTauEta_SSISO", QCD);
	EstimateQCD2("hMass_bbtt", "hMass_bbtt_SSISO",QCD);
	EstimateQCD2("hMvaMet", "hMvaMet_SSISO_LowMT",QCD);
	QCD->Close();
	

}


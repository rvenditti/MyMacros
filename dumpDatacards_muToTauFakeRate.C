
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <assert.h>

TH1* loadHistogram(TFile* inputFile, const std::string& histogramName)
{
  //std::cout << "loading histogram = " << histogramName << " from file = " << inputFile->GetName() << std::endl;
  TH1* histogram = dynamic_cast<TH1*>(inputFile->Get(histogramName.data()));
  //std::cout << " histogram = " << histogram << std::endl;
  if ( !histogram ) {
    std::cerr << "Failed to load histogram = " << histogramName << " from file = " << inputFile->GetName() << " !!" << std::endl;
    delete inputFile;
    assert(0);
  }
  //std::cout << histogramName << ": integral = " << histogram->Integral() << std::endl;
  return histogram;
}

double square(double x)
{
  return (x*x);
}

void dumpDatacards_muToTauFakeRate()
{
  gROOT->SetBatch(true);

  TH1::AddDirectory(false);

	//std::string inputFilePath = "/Users/Rosma/Dropbox/RootFilesFR_04_08_14/RootFilesFR_13_02_2015_pt25_3Hits/AntiMuCutBasedV3/";
//	std::string inputFilePath = "/Users/Rosma/Dropbox/RootFilesFR_04_08_14/RootFilesFR_30_11_2014_pt25_3Hits/";
	std::string inputFilePath = "./";
	//std::string inputFileName = "histForSaving_muToTau_HpsAntiMuLoose3Barrel_3Mar.root";
//	std::string inputFileName = "histForSaving_muToTau_HpsAntiMuLoose3Barrel27Feb_v2.root";
	std::string inputFileName = "histForSaving_muToTau_HpsAntiMuLoose_9Mar.root";
//	std::string inputFileName = "histForSaving_muToTau_HpsAntiMuLoose3Barrel.root";

  std::string inputFileName_full = Form("%s%s", inputFilePath.data(), inputFileName.data());
  TFile* inputFile = new TFile(inputFileName_full.data());
  if ( !inputFile ) {
    std::cerr << "Failed to open input file = " << inputFileName_full << " !!" << std::endl;
    delete inputFile;
    return;
  }

  std::vector<std::string> processes;
 /* processes.push_back("ZTT");
  processes.push_back("ZL");
  processes.push_back("zmumuJets");
  processes.push_back("QCD");
  processes.push_back("W");
  processes.push_back("wjetsDataDriven");
  processes.push_back("TT");
  processes.push_back("VV");
  processes.push_back("data_obs");*/
	
	processes.push_back("ZL_CMS_scale_m_mutau_8TeVUp");
	processes.push_back("ZL_CMS_scale_m_mutau_8TeVDown");
	processes.push_back("ZL_CMS_scale_t_mutau_8TeVUp");
	processes.push_back("ZL_CMS_scale_t_mutau_8TeVDown");
	
  
  std::vector<std::string> categories;
  categories.push_back("pass");
  categories.push_back("fail");
    
  for ( std::vector<std::string>::const_iterator category = categories.begin();
	category != categories.end(); ++category ) {
    for ( std::vector<std::string>::const_iterator process = processes.begin();
	  process != processes.end(); ++process ) {
      //std::cout << "processing category = " << (*category) << ", process = " << (*process) << ":" << std::endl;

      std::string histogramName = Form("%s/%s", category->data(), process->data());
      TH1* histogram = loadHistogram(inputFile, histogramName);

      double sumBinContents = 0.;
      double sumBinError2 = 0.;

      TAxis* xAxis = histogram->GetXaxis();
      int numBins = xAxis->GetNbins();
		double events =  histogram->GetEntries();
      for ( int iBin = 1; iBin <= numBins; ++iBin ) {
	double binCenter = xAxis->GetBinCenter(iBin);
	double binContent = histogram->GetBinContent(iBin);
	double binError = histogram->GetBinError(iBin);
	//std::cout << "  bin #" << iBin << " (x = " << binCenter << "): " << binContent << " +/- " << binError << std::endl;
	sumBinContents += binContent;
	sumBinError2 += (binError*binError);
      }

      double sumBinError = TMath::Sqrt(sumBinError2);
      //std::cout <<(*category) <<"  "<<(*process)<< " sum: " << sumBinContents << " +/- " << sumBinError << " (avWeight = " << (sumBinError2/sumBinContents) << ")  events=" <<events<< std::endl;
	std::cout <<(*category) <<"  "<<(*process)<<"  " << sumBinContents << "  " << sumBinError <<endl;
    }
  }

  delete inputFile;
}



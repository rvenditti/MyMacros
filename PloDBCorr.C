{

       
  gROOT->ProcessLine(".L ./tdrstyle.C");
  setTDRStyle();

  TFile *f1 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU20bx25.root");  
  TFile *f2 = TFile::Open("./histo_file_HToTauTau_13TeV_Fall13dr_PU40bx25.root");  
  TFile *f3 = TFile::Open("./histo_file_HToTauTau_8TeV_HighPt.root");



  gStyle->SetOptStat(000000000);


TCanvas *DBCorrection = new TCanvas("DBCorrection","DBCorrection",500,600);
TH1F* hDB_20 = (TH1F*)f1->Get("hDiff");
TH1F* hDB_40 = (TH1F*)f2->Get("hDiff");
TH1F* hDB_8 = (TH1F*)f3->Get("hDiff");
        
/*hDB_20->SetMarkerStyle(20);
        hDB_40->SetMarkerStyle(20);
        hDB_8->SetMarkerStyle(20);*/
        
hDB_20->SetLineColor(kMagenta);
hDB_40->SetLineColor(kBlue);
hDB_8->SetLineColor(kBlack);
                        
hDB_20->Scale(1/hDB_20->Integral());
hDB_40->Scale(1/hDB_40->Integral());
hDB_8->Scale(1/hDB_8->Integral());
        
cout << " PU20: % tau with (neutral Iso - DB) >0 "<<hDB_20->Integral(50,100)/hDB_20->Integral()<<endl;
cout << " PU40: % tau with (neutral Iso - DB) >0 "<<hDB_40->Integral(50,100)/hDB_40->Integral()<<endl;
cout << " 8TeV: % tau with (neutral Iso - DB) >0 "<<hDB_8->Integral(50,100)/hDB_8->Integral()<<endl;
        
hDB_20->SetTitle("  ");
hDB_20->GetXaxis()->SetTitle("Neutral Iso - DB (Gev)");
        
hDB_20->Draw("HISTE");
hDB_40->Draw("HISTESAMES");
hDB_8->Draw("HISTESAMES");
        
        
TLegend* legend = new TLegend( 0.5, 0.75, 0.99, 0.99);
legend->SetTextSize(0.025);
legend->SetFillColor(0);
legend->AddEntry(hDB_8, "Summer12, 8 TeV (NeIso - k#timesPUIso)");
legend->AddEntry(hDB_20, "Fall13, 13 TeV, PU20, bx25, (NeIso-k #times PuIso - Offset -2 #times RMS)");
legend->AddEntry(hDB_40, "Fall13, 13 TeV, PU40, bx25, (NeIso-k #times PuIso - Offset -2 #times RMS)");
legend->Draw("same");
        
        
//for(int i=0;i<100;i++){ cout<<i<<"  diff "<<hDB_8->GetBinContent(i)<<endl;}
}

#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <TFile.h>  
#include <TString.h>
#include <TH1.h>
#include< vector >   

void MakeRocCurves_new(){

gROOT->ProcessLine(".L ./tdrstyle.C");
setTDRStyle();

std::vector< TString > fileSig(4);
std::vector< TString > fileBkg(4);	
	TH1F* hsig[4];	 
	TH1F* hbkg[4];	

	fileSig[0] = "fEff_OldDeltaBeta.root";
	fileSig[1] = "fEff_ChIso.root";
	fileSig[2] = " fEff_NewDeltaBetak2.root";
	fileSig[3] = "fEff_Rho.root";
	
	fileBkg[0] = "fFakeRate_OldDeltaBeta.root";
	fileBkg[1] = "fFakeRate_ChIso.root";
	fileBkg[2] = "fFakeRate_NewDeltaBetak2.root";
	fileBkg[3] = "fFakeRate_Rho.root";
	
	std::vector< TString > histoSig(3);
	std::vector< TString > histoBkg(3);
	
	
 histoSig[0] ="EffLooseIso3Hits_Pt_Pu40";
 histoSig[1] ="EffLooseIso3Hits_Pt_Pu20";	
histoSig[2] ="EffLooseIso3Hits_Pt_8Tev";	
	
	histoBkg[0] ="FRLooseIso3Hits_Pt_Pu40";
	histoBkg[1] ="FRLooseIso3Hits_Pt_Pu20";	
	histoBkg[2] ="FRLooseIso3Hits_Pt_8Tev";		
	
	
	std::vector<int> numBinsSig,  numBinsBkg;
	int initialBin, increment;
//	std::vector<double> initialBin = 0;
	
    std::vector<double> normalization_signal ;
    
    std::vector<double> normalization_background;
	
	double normalization_signal8Tev ;
    
  double normalization_background8Tev;
	
	
	std::vector<double> x8tev , y8tev;

	double y[4][51]; 	
	double x[4][51];
	double  runningSum_background[4] ;
	double  runningSum_signal[4] ;
	
 std::vector<double> 	runningSum_signal8tev =0;
 std::vector<double> 	runningSum_background8tev =0;
	std::vector<double> 	mean_signal=0;
	std::vector<double> 	mean_background=0;
	
	double Eff[4][51]; 	
	double FR[4][51];
	
	TGraph* graph1 = 0; 
	TGraph* graph_OldDeltaBeta1 = 0;
	TGraph* graph_ChargedIso1 = 0;
	TGraph* graph_Rho1 = 0;
	
	graph1= new TGraph(51);
	graph_ChargedIso1=new TGraph(51);
	graph_NewDeltaBetak21=new TGraph(51);
	graph_Rho1 = new TGraph(51);



		for(int i=0;i<fileSig.size();i++){
			for(int k=0;k<=51;k++){
				x[i][k]=0;
				y[i][k]=0;
				Eff[i][k]=0;
				FR[i][k]=0;
				}
		}
	
	
	assert(fileSig.size() == fileBkg.size())	;
	
	for(int i=0;i<fileSig.size();i++){
		
	TFile* inputFileSig = new TFile( fileSig[i] );
	hsig[i] = (TH1F*)inputFileSig->Get( histoSig[0] ); 

	
	TFile* inputFileBkg = new TFile( fileBkg[i] );
	hbkg[i] = (TH1F*)inputFileBkg ->Get(histoBkg[0]); 
		
 /*   if(i==0){	
	hsig8tev= (TH1F*)inputFileSig->Get("EffLooseIso3Hits_Pt_8Tev"); 	
	hbkg8tev= (TH1F*)inputFileBkg->Get("FRLooseIso3Hits_Pt_8Tev"); 
	normalization_signal8Tev.push_back(hsig8tev->Integral());
	normalization_background8Tev.push_back(hbkg8tev->Integral());	
	
	for ( int iBin = 0; iBin <= 51 ; iBin ++ ) {	
	runningSum_signal8tev += hsig8tev->GetBinContent(iBin);
	runningSum_background8tev += hbkg8tev->GetBinContent(iBin);
	
	x8tev.push_back(runningSum_signal8tev/normalization_signal8Tev);
	y8tev.push_back(runningSum_background8tev/normalization_background8Tev);
	}
		
	}*/
		
		numBinsSig.push_back(hsig[i]->GetNbinsX());
		numBinsBkg.push_back(hbkg[i]->GetNbinsX());
		
		cout<<"NBins x sig: "<<numBinsSig[i]<<" bkg: "<<numBinsBkg[i]<<endl;
		
		assert(numBinsSig[i] == numBinsBkg[i])	;
		
		normalization_signal.push_back(hsig[i]->Integral());
		normalization_background.push_back(hbkg[i]->Integral());
		
		mean_signal.push_back( hsig[i]->GetMean());
		mean_background.push_back( hbkg[i]->GetMean());
		
		if ( mean_signal[i] > mean_background[i] ) { // integrate from "left"                                                                                                                                         
			initialBin = 0; // underflow bin                                                                                                                                                                      
			increment = +1;
			cout<<i<<" mean_signal[i] > mean_background[i]   "<<endl;
		} else { // integrate from "right"                                                                                                                                                                      
			initialBin = hsig[i]->GetNbinsX() ; // overflow bin                                                                                                                                       
			increment = -1;
				cout<<i<<" mean_signal[i] < mean_background[i]   "<<endl;
		}
		

		
		double sumSig=0;
		double sumBkg=0;
		runningSum_signal[i] =0;
		runningSum_background[i] =0;
		
		
		
	//	for ( int iBin = 0; iBin <= 51 ; iBin ++ ) {
		int numBin=numBinsSig[i]+1;
		for ( int iBin = initialBin; ( iBin >= 0 && iBin <= numBin) ; iBin += increment ) {
			 assert(hsig[i]->GetBinCenter(iBin) == hbkg[i]->GetBinCenter(iBin));
			
			if( (hsig[i]->GetBinContent(iBin)! =0) && ( FR[i][iBin]=hbkg[i]->GetBinContent(iBin) != 0)){
			Eff[i][iBin]=hsig[i]->GetBinContent(iBin);
			FR[i][iBin]=hbkg[i]->GetBinContent(iBin);
			//cout <<i<< " bin #"<<iBin<<" content "<<Eff[i][iBin]<<" bkg "<<FR[i][iBin]<<endl;
			}
				
			else{
				Eff[i][iBin]=0.;
				FR[i][iBin]=0.;
			}
			
						
		    runningSum_signal[i] += hsig[i]->GetBinContent(iBin);
			runningSum_background[i]   += hbkg[i]->GetBinContent(iBin);
			
			
	
			//cout <<i<< " bin #"<<iBin<<" content "<<Eff[i][iBin]<<" bkg "<<FR[i][iBin]<<endl;
			
			//std::cout <<i<< " bin #"<<iBin<<" content "<< hsig[i]->GetBinContent(iBin) <<" running sum  "<<runningSum_signal[i]<<endl;
			//std::cout <<i<< " bin #"<<iBin<<" content "<< hbkg[i]->GetBinContent(iBin) <<" running sum  "<<runningSum_background[i]<<endl;
			
		//	std::cout <<i<< " bin #"<<iBin<<" running sum signal "<<runningSum_signal[i] <<" running sum  background "<<runningSum_background[i]<<endl;
			
			if (  (runningSum_signal[i]  >= 1.e-6 || runningSum_background[i] >= 1.e-6) &&
				( (normalization_signal[i]  - runningSum_signal[i]) >= 1.e-6 || (normalization_background[i] - runningSum_background[i])  >= 1.e-6 ) )  {

			
			 sumSig=runningSum_signal[i] /normalization_signal[i] ;
			 x[i][iBin]=sumSig;
			//  std::cout <<i<< " ratio x "<< x[i][iBin] <<endl;
			
			sumBkg =runningSum_background [i] /normalization_background[i] ;
			y[i][iBin]=sumBkg;
			}
			}
							
		}
	
	//std::vector<TGraph>  graph = 0; 
	TGraph* graph = 0; 
	TGraph* graph_OldDeltaBeta = 0;
	TGraph* graph_ChargedIso = 0;
	TGraph* graph_Rho = 0;
	
	graph= new TGraph(51);
	graph_ChargedIso=new TGraph(51);
	graph_NewDeltaBetak2=new TGraph(51);
	graph_Rho = new TGraph(51);
	
	
	
	
	for ( int iBin = 0; iBin <= 51; iBin ++ ) {
		
		graph->SetPoint(iBin, x[0][iBin] ,  y[0][iBin] );	
		graph_ChargedIso->SetPoint(iBin, x[1][iBin] ,  y[1][iBin] );
		graph_NewDeltaBetak2->SetPoint(iBin, x[2][iBin] ,  y[2][iBin] );
		graph_Rho->SetPoint(iBin, x[3][iBin] ,  y[3][iBin] ); 
		
		graph1->SetPoint(iBin, Eff[0][iBin] ,  FR[0][iBin] );	
		
	//	cout<<iBin<<"  sig  "<<	x[0][iBin]<<" bkg "<< y[0][iBin]<<endl;

	}
	
		
	
	TCanvas *IsoRoc = new TCanvas("IsoRoc","IsoRoc",800,700);	
	graph->SetLineColor(0);
	graph_ChargedIso->SetLineColor(0);
	graph_Rho->SetLineColor(0);
	graph_NewDeltaBetak2->SetLineColor(0);
	

	graph_NewDeltaBetak2->Draw("ACP");
	graph->Draw("CP");
	graph_ChargedIso->Draw("CP");
	graph_Rho->Draw("CP");
	
	graph_ChargedIso->SetMarkerColor(kBlue);
	graph_NewDeltaBetak2->SetMarkerColor(kMagenta);
	graph_Rho->SetMarkerColor(kRed);
	
	graph_NewDeltaBetak2->GetXaxis()->SetTitle("Efficiency");
	graph_NewDeltaBetak2->GetYaxis()->SetTitle("1-Fake Rate");
	

	//std::vector< TString > IsoType;
	//IsoType[0]="OldDeltaBeta";
	//IsoType[1]="ChIso";
//	IsoType[2]="NewDeltaBeta";
//	IsoType[3]="Rho";
	
	TCanvas *IsoRoc2 = new TCanvas("IsoRoc2","IsoRoc2",800,700);	
graph1->SetLineColor(0);
	graph_ChargedIso1->SetMarkerColor(kBlue);
	graph1->Draw("ACP");
	graph_ChargedIso1->Draw("CP");
		
	
	TLegend* legend = new TLegend( 0.55, 0.75, 0.99, 0.99);
	legend->SetTextSize(0.02);
	legend->SetFillColor(0);
	legend->AddEntry(graph, "OldDeltaBeta", "p");
	legend->AddEntry(graph_ChargedIso, "Charged Iso" , "p");
	legend->AddEntry(graph_Rho, "Rho Isolation", "p");
	legend->AddEntry(graph_NewDeltaBetak2, "New Delta Beta, k=2", "p");
	IsoRoc->cd();
	legend->Draw("same");
	
	
	
	TFile ROC_curves("ROC_curves.root","recreate"); 
	graph->Write("OldDeltaBeta");
	graph_ChargedIso->Write("ChIso");
	graph_Rho->Write("Rho");
	graph_NewDeltaBetak2->Write("NewDeltaBeta");
	ROC_curves.Close();
	

	}

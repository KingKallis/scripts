#include <TSpectrum.h>
#include <TH1.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TH2.h>
#include <TMath.h>

Calibcheck(){

  c1 = new TCanvas("c1","Checks Clover Calib",10,10,900,600);
//  TH1F *hEClover = new TH1F("hEClover","Gamma Energy Clover",1100,0.,11000.);


  TFile hfile("Checkcalib.root","RECREATE");
  // create histograms
   TH1F *hEClover[48];
   TH1F *hECloverRaw[48];
   char name[256];
   char title[256];
   char nameRaw[256];
   char titleRaw[256];
   for (int n=0;n<48;n++) {
      sprintf(name,"hEClover%d",n);
      sprintf(title,"Gamma Energy hEClover%d",n);
      hEClover[i] = new TH1F(name,title,11000,0,11000);
      sprintf(nameRaw,"hECloverRaw%d",n);
      sprintf(titleRaw,"Gamma Raw Energy hEClover%d",n);
      hECloverRaw[i] = new TH1F(nameRaw,titleRaw,4096,0,4096);
   }

  int m=0;
  // fill histograms
      	for(int i=1; i<13; i++){
	  for(int j=1; j<5; j++){
		char Clover[256];
		char histo[256];
		char histoRaw[256];
		sprintf(Clover,"GammaDetectorType==\"Clover\" && GammaDetectorLabel==%d && GammaDetectorSegm==%d && X1pos>600 && X1pos<630 && X1flag==0 && U1flag==0",i, j);
		m=j+(i-1)*4-1;
		cout << "i = " << i << " j = " << j << " m = " << m << endl;
		sprintf(histo,"GammaEnergy>>hEClover%d",m);
		DATAch->Draw(histo, Clover ,"");
		sprintf(histoRaw,"GammaRawADC>>hECloverRaw%d",m);
		DATAch->Draw(histoRaw, Clover ,"");

		}
	}
  // save histograms		
 hfile.Write();


/*

	for(int i=1; i<13; i++){
	  for(int j=1; j<5; j++){
		char Clover[256];
		//char Cry[256];
		sprintf(Clover,"GammaDetectorType==\"Clover\" && GammaDetectorLabel==%d && GammaDetectorSegm==%d && X1pos>600 && X1pos<630 && X1flag==0 && U1flag==0",i, j);
		//sprintf(Cry,"GammaDetectorSegm==%d",j);
		DATAch->Draw("GammaEnergy>>hEClover", Clover ,"");
              cout << "Clover num = " << i << " Segment num = " << j << endl;
	      c1->Modified(); 
	      c1->Update();
	      c1->WaitPrimitive();
	    }
	}
*/

}

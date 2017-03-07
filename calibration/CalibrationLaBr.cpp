{
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TSpectrum.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGraph.h>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TH2.h>

//*********************************************************
#define Nchannels 2
#define Npeaks    3
//int   chmin =0;
 int   chmin =32;
// int   chmin =48;

double threshold = 0.17;

double sigma = 8.;

double filenum = 1211;
//***********************************************************************

char buffer[256];
sprintf(buffer,"CalibParsPR251_2_Run0%d.dat",filenum);


double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {661.7, 1173.2, 1332.5};


//void Calibration()
//{
  ofstream mOutput;
  mOutput.open(buffer);

  TH2F *unCalibADCs = new TH2F("unCalibADCs","unCalibADCs",4096,0,4096,Nchannels,0,Nchannels);
  TH2F *CalibADCs = new TH2F("CalibADCs","CalibADCs",4096,0,12288,Nchannels,0,Nchannels);


  for(int i=chmin;i<Nchannels+chmin;i++)
    {
      gains[i-chmin] = 0; offsets[i-chmin] = 0;
      TCanvas *c1 = new TCanvas("c1","c1",800,600);
      sprintf(buffer,"CalibFiles/h91ADC_%d.root",i);
      TFile *fin = TFile::Open(buffer);
      TH1F *h = (TH1F*)fin->FindObjectAny("hADC");

      //sprintf(buffer,"hADC2DModule%d",(int)((i-i%32)/32));
      //printf("Channel %d, Module %d\n",i,(int)((i-i%32)/32));
      //TH2F *h2 = (TH2F*)fin->FindObjectAny(buffer);

      //TH1D *h = h2->ProjectionX("_px",i+1,i+1);
      //h->Rebin(4);
      h->Draw();
      h->GetXaxis()->SetRangeUser(300,1000);

      for(int j=0;j<h->GetXaxis()->GetNbins();j++)
	{
	  unCalibADCs->Fill(h->GetXaxis()->GetBinCenter(j),i,h->GetBinContent(j));
	}
	  TSpectrum *sp = new TSpectrum();


///   ***************** TO BE CHECKED
     if(i!=10){
	  sp->Search(h,sigma,"",threshold); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
     }else if(i==10){
	  sp->Search(h,sigma,"",0.14); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
     }
/// ************************************	  
	  if(sp->GetNPeaks()==Npeaks)
	    {
	      float *chan = sp->GetPositionX();
	      for(int n=0;n<Npeaks-1;n++){//Ensure that the peaks are in the right order...
		for(int nn=n+1;nn<Npeaks;nn++){
		  if(chan[nn]<chan[n]){
		    float chan_tmp = chan[n];
		    chan[n]=chan[nn];
		    chan[nn]=chan_tmp;
		  }}}
	      TGraph *g = new TGraph();
	      for(int n=0;n<Npeaks;n++){g->SetPoint(n,chan[n],gamma_E[n]);}
	      TF1 *fit = new TF1("fit","[0]+[1]*x",0,10000);
	      g->Fit(fit,"BR");
	      g->Draw("L* same");
	      offsets[i-chmin] = fit->GetParameter(0);
	      gains[i-chmin] = fit->GetParameter(1);
	    }
      mOutput << i << "\t 2 \t" << offsets[i-chmin] << "\t" << gains[i-chmin] << endl;
      sprintf(buffer,"CalibFiles/FithADC_%d.png",i);
      c1->SaveAs(buffer);

       for(int j=0;j<h->GetXaxis()->GetNbins();j++)
	{
	  CalibADCs->Fill(offsets[i-chmin]+gains[i-chmin]*h->GetXaxis()->GetBinCenter(j),i,h->GetBinContent(j));
	}
    }

    mOutput << "eof" << endl;
  mOutput.close();

      sprintf(buffer,"unCalibADCs_LaBr_%d.root",filenum);
  unCalibADCs->SaveAs(buffer);
      sprintf(buffer,"CalibADCs_LaBr_%d.root",filenum);
  CalibADCs->SaveAs(buffer);

}

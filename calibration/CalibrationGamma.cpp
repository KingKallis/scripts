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
#include <TMath.h>

//**************************************************************
//**************************************************************
#define NADCs     2
#define Nchannels 32
#define Npeaks    3
int   chmin =0;
//int   chmin =32;
// int   chmin =48;

int filenum = 2083;
double threshold = 0.15;
double sigma = 1.;

char buffer[256];
TString rebuffer= "CalibParsPR251Run2083.dat";
//sprintf(buffer,"CalibParsPR251Run0%d.dat",filenum);
//buffer = sprintf("CalibParsPR251Run0%d.dat",filenum);

//**************************************************************
//**************************************************************


double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {661.7, 1173.2, 1332.5};

double ma_funckyton(double *x, double *pars)
{
	double result = 0;

	result += pars[0] * exp(-0.5*pow(x[0]-pars[1],2.)/pars[2]) +pars[3] + pars[4]*x[0];

	return result;
}

void Calibration()
{
  ofstream mOutput;
//  mOutput.open(buffer);
  mOutput.open(rebuffer);

  TH2F *unCalibADCs = new TH2F("unCalibADCs","unCalibADCs",4096,0,4096,Nchannels,0,Nchannels);
  TH2F *CalibADCs = new TH2F("CalibADCs","CalibADCs",4096,0,12288,Nchannels,0,Nchannels);

	double resolutions[32];
  for(int i=chmin;i<Nchannels+chmin;i++)
    {
      gains[i] = 0; offsets[i] = 0;
      TCanvas *c1 = new TCanvas("c1","c1",800,600);

      if (filenum == 1191) filenum = 91;

      sprintf(buffer,"CalibFiles/h%dADC_%d.root",filenum,i);
      TFile *fin = TFile::Open(buffer);
      TH1F *h = (TH1F*)fin->FindObjectAny("hADC");

      //sprintf(buffer,"hADC2DModule%d",(int)((i-i%32)/32));
      //printf("Channel %d, Module %d\n",i,(int)((i-i%32)/32));
      //TH2F *h2 = (TH2F*)fin->FindObjectAny(buffer);

      //TH1D *h = h2->ProjectionX("_px",i+1,i+1);
      //h->Rebin(4);
      h->Draw();
      h->GetXaxis()->SetRangeUser(250,1000);   //changed range minimum from 300

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
	      TGraph *gFitted = new TGraph();
	      for(int n=0;n<Npeaks;n++){g->SetPoint(n,chan[n],gamma_E[n]);}
	      TF1 *fit = new TF1("fit","[0]+[1]*x",0,10000);
	      g->Fit(fit,"BR");
	      g->Draw("L* same");
	      
	      TF1 **fitPeaks = new TF1*[Npeaks];
	      
	      for(int n=0;n<Npeaks;n++)
	      {
	      	char peakBuffer[256];
	      	sprintf(peakBuffer,"fitPeak%d",n);
	      	fitPeaks[n] = new TF1(peakBuffer,ma_funckyton,chan[n]-10,chan[n]+10,5);	
	      	fitPeaks[n]->SetParameter(0,h->GetBinContent(h->FindBin(chan[n])));
	      	fitPeaks[n]->SetParameter(1,chan[n]);
	      	fitPeaks[n]->SetParameter(2,1.0);
	      	fitPeaks[n]->SetParameter(3,0.0);
	      	fitPeaks[n]->SetParameter(4,0.0);
	      	h->Fit(fitPeaks[n],"BRIE");
	      	gFitted->SetPoint(n,fitPeaks[n]->GetParameter(1),gamma_E[n]);
	      }
	      h->Draw();
	      for(int n=0;n<Npeaks;n++)fitPeaks[n]->Draw("same");
	      
	      TF1 *fitFittedlin = new TF1("fitFittedlin","[0]+[1]*x",0,10000);
	      gFitted->Fit(fitFittedlin,"BRQ");
	      TF1 *fitFittedquad = new TF1("fitFittedquad","[0]+[1]*x+[2]*x*x",0,10000);
	      gFitted->Fit(fitFittedquad,"BRQ");
	      offsets[i] = fit->GetParameter(0);
	      gains[i] = fit->GetParameter(1);
	      
	      resolutions[i] = gains[i] * fitPeaks[0]->GetParameter(2) * 2.35;
	    }
      mOutput << i << "\t 2 \t" << offsets[i] << "\t" << gains[i] << endl;
      sprintf(buffer,"CalibFiles/FithADC_%d.png",i);
      c1->SaveAs(buffer);

       for(int j=0;j<h->GetXaxis()->GetNbins();j++)
	{
	  CalibADCs->Fill(offsets[i]+gains[i]*h->GetXaxis()->GetBinCenter(j),i,h->GetBinContent(j));
	}
    }

    for(int i=Nchannels;i<NADCs*32;i++){
    mOutput << i << "\t 2 \t 0.\t 1. \n";
    }
    mOutput << "eof" << endl;
  mOutput.close();

  for (int i=0;i<Nchannels;i++) cout << "Channel: " << i << "; Offset: " << offsets[i] << "\tGain: " << gains[i] << "\tEnergy_ch3850:\t" << gains[i]*3850. + offsets[i] << ";\t" << "FWHM(keV) of the lowest peak: \t" << resolutions[i] << endl;

  
      sprintf(buffer,"unCalibADCs_%d.root",filenum);
  unCalibADCs->SaveAs(buffer);
      sprintf(buffer,"CalibADCs_%d.root",filenum);
  CalibADCs->SaveAs(buffer);
}


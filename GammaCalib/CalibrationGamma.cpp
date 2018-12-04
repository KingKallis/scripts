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
#define NADCs     3
#define Nchannels 80
#define Npeaks    3
int   chmin =72;
int   chmax =72;

//int filenum = 235;
double threshold = 0.14;
double sigma = 3.;

char buffer[256];
TString rebuffer= "CalibPars_PR298_Run508_509_check.dat";
//sprintf(buffer,"CalibParsPR251Run0%d.dat",filenum);
//buffer = sprintf("CalibParsPR251Run0%d.dat",filenum);

//**************************************************************
//**************************************************************


//double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {511, 661.7, 1173.2, 1332.5};
double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {661.7, 1173.2, 1332.5};


double ma_funckyton(double *x, double *pars)
{
	double result = 0;

	result += pars[0] * exp(-0.5*pow(x[0]-pars[1],2.)/pars[2]) +pars[3] + pars[4]*x[0];

	return result;
}

void CalibrationGamma()
{
  ofstream mOutput;
//  mOutput.open(buffer);
  mOutput.open(rebuffer);

/*    for(int i=0;i<32;i++){1 0 3
2 4 7
3 8 11
4 12 15
5 16 19
    mOutput << i << "\t 2 \t 0.\t 1. \n";
    }
*/

//for(int i=0;i<32;i++){
//    mOutput << i << "\t 2 \t 0.\t 1. \n";
//    }

  TH2F *unCalibADCs = new TH2F("unCalibADCs","unCalibADCs",4096,0,4096,Nchannels,0,Nchannels);
  TH2F *CalibADCs = new TH2F("CalibADCs","CalibADCs",4096,0,12288,Nchannels,0,Nchannels);

	double resolutions[Nchannels];

   TCanvas *c1 = new TCanvas("c1","c1",900,700);

  for(int i=chmin;i<chmax+1;i++)
//for(int i=76;i<80;i++)
    {
      gains[i] = 0; offsets[i] = 0; resolutions[i]= 0;   

      sprintf(buffer,"PR298_Calib_508_509/hADC_%d.root",i);
      TFile *fin = TFile::Open(buffer);
      TH1F *h = (TH1F*)fin->FindObjectAny("hADC");

      //sprintf(buffer,"hADC2DModule%d",(int)((i-i%32)/32));
      //printf("Channel %d, Module %d\n",i,(int)((i-i%32)/32));
      //TH2F *h2 = (TH2F*)fin->FindObjectAny(buffer);

      //TH1D *h = h2->ProjectionX("_px",i+1,i+1);
      //h->Rebin(4);
      h->Draw();

     if(i!=69){
      h->GetXaxis()->SetRangeUser(200,600);
     }else if(i==69){
      h->GetXaxis()->SetRangeUser(180,600);
     }

      for(int j=0;j<h->GetXaxis()->GetNbins();j++)
	{
	  unCalibADCs->Fill(h->GetXaxis()->GetBinCenter(j),i,h->GetBinContent(j));
	}
	  TSpectrum *sp = new TSpectrum();


///   ***************** TO BE CHECKED
     if(i!=1){
	  sp->Search(h,sigma,"",threshold); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
     }else if(i==1){
	  sp->Search(h,sigma,"",0.16); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
     }
/// ************************************

         c1->WaitPrimitive();

	  
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
	      
	      resolutions[i] = gains[i] * fitPeaks[2]->GetParameter(2) * 2.35;
	    }
      mOutput << i << "\t 2 \t" << offsets[i] << "\t" << gains[i] << endl;
      sprintf(buffer,"PR298_Calib_508_509/FithADC_%d.png",i);
      c1->SaveAs(buffer);
      c1->WaitPrimitive();
      c1->Clear();

       for(int j=0;j<h->GetXaxis()->GetNbins();j++)
	{
	  CalibADCs->Fill(offsets[i]+gains[i]*h->GetXaxis()->GetBinCenter(j),i,h->GetBinContent(j));
	}
    }


    mOutput << "eof" << endl;
    mOutput.close();

  for (int i=chmin;i<chmax+1;i++) cout << "Channel: " << i << "; Offset: " << offsets[i] << "\tGain: " << gains[i] << "\tEnergy_ch3850:\t" << gains[i]*3850. + offsets[i] << ";\t" << "FWHM(keV) of the lowest peak: \t" << resolutions[i] << endl;

  
      sprintf(buffer,"unCalibADCs.root");
  unCalibADCs->SaveAs(buffer);
      sprintf(buffer,"CalibADCs.root");
  CalibADCs->SaveAs(buffer);

}


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

#define Nchannels 4
#define Npeaks 3
//#define Npeaks 2
int filenum = 2083;


char buffer[256];
sprintf(buffer,"CalibParsPR251_LaBr_Run0%d.dat",filenum);
cout << buffer << endl;

ofstream mOutput(buffer);


double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {661.7, 1173.2, 1332.5};
//double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {1173.2, 1332.5, 4438.9};
//double gains[Nchannels], offsets[Nchannels], gamma_E[Npeaks] = {1173.2, 1332.5};

//**************************************************************
//**************************************************************

int ChNum[Nchannels];
ChNum[0]=32;
ChNum[1]=33;
ChNum[2]=48;
ChNum[3]=49;

float chan[Nchannels][Npeaks];

//  channel 32
chan[0][0]= 306.3;
chan[0][1]= 497.9;
chan[0][2]= 558.8;

//   channel 33
chan[1][0]= 307.3;
chan[1][1]= 505.;
chan[1][2]= 566.3;

//  channel 48
chan[2][0]= 258.2;
chan[2][1]= 386.9;
chan[2][2]= 427.7;

//  channel 49
chan[3][0]= 259.1;
chan[3][1]= 387.3;
chan[3][2]= 428;

for (int i=0;i<Nchannels;i++){
	      TGraph *g = new TGraph();
	      for(int n=0;n<Npeaks;n++){g->SetPoint(n,chan[i][n],gamma_E[n]);}
	      TF1 *fit = new TF1("fit","[0]+[1]*x",0,10000);
	      g->Fit(fit,"BR");
	      g->Draw("L* same");
	      offsets[i] = fit->GetParameter(0);
	      gains[i] = fit->GetParameter(1);	    
      	      mOutput << ChNum[i] << "\t 2 \t" << offsets[i] << "\t" << gains[i] << endl;
}

    mOutput << "eof" << endl;
  mOutput.close();

  for (int i=0;i<Nchannels;i++) cout << "Channel: " << ChNum[i] << "; Offset: " << offsets[i] << "Gain: " << gains[i] << " Energy_ch3850: " << gains[i]*3850. + offsets[i] << ";\n";

  
}

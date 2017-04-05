// ------------------------------------------------------------------------------------
// V. Pesudo - March 2017
// Alternative program to JJ's for aligning TDC's. 
// Instead of looking for derivatives, looks for the highest histogram bin which has 5 histogram bins on its left filled up.
// It's useful for the cases in which you don't have a consistently populated 'white' spectrum,
// so basically peaks shouldn't bother you here.
//
// In order to accelerate the process, compile it using: g++ -o vp_autotrim vp_autotrim.C `root-config --cflags --glibs`
// ------------------------------------------------------------------------------------
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TH2.h>
#include <TROOT.h>
#include <TCanvas.h>
#include <TStopwatch.h>

  int run_no[]={1105,1106,1107,1108,1109,1110,1111,1112,1113,1114,1115,1116,1117,1118,2086,2087,2088,2089,2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,2100,2101,2102,2103,2104,2105,2106,2107,2108,2109,2110,2112,2113,2114,2115,2116,2117,2118,2119,2120,2121,2122,2123,2124,2125,2126,2127};  
  int t0corr=5000;		// Corrected bin number for cable length shift
  int rebin=1;
  
  int nbins=14999;		// Bin size of TDCchan histos
  int xnumbins,xminbin=3000,xmaxbin=6000;	// Plot range for zoomed histo. Rebinning will be considered later, don't bother about that here
  int tmin, j, histI;
  int flag, histImin, histImax;
  char namerun[128], histoname[128], nanana[128];
  

  ofstream outpfile;
  TH1F *h_TDCadd;
  TCanvas *c1;
  
// void vp_autotrim(){
int main(int argc, char *argv[]){


//   int run_no[]={2103,2107,2113,2117,2121,2125,2139,2165,2137,2138,2140,2141,2142,2143,2161,2162,2163,2166,2167,2168,2169};  
//  int run_no[]={1105,1106,1107,1108,1109,1110,1111,1112,1113,1114,1115,1116,1117,1118,2086,2087,2088,2089,2090,2091,2092,2093,2094,2095,2096,2097,2098,2099,2100,2101,2102,2103};  
  
  int nrofruns=sizeof(run_no)/sizeof(run_no[0]);  
  std::cout << "Nruns: " << nrofruns << "\n";



  histImin=0;
  histImax=895;		// 420 for VDC 1 alone; set to 896 for both VDC 1 and 2
//   histImax=100;		// just for quicker tests of the program
  
  int flag =0;    // Flag =1 to plot a particular histo.
  int weirdhist = 500;   // choose channel to plot
  
  if(flag ==1){
    histImin = weirdhist;
    histImax = weirdhist;
    c1 = new TCanvas();
  }
  
  if (rebin>1) {
    xminbin = xminbin/rebin;
    xmaxbin = xmaxbin/rebin;
  }
  xnumbins=xmaxbin-xminbin;  
  
  outpfile.open("CableLengthtmp.dat");
  
//   TStopwatch timer;
//   TStopwatch timerin;
//   TStopwatch timerloop;
//   ofstream timerfile("timer.dat");
//   ofstream timerinfile("timerin.dat");

  for(histI=histImin;histI<=histImax;histI++) {
    
//   if ( histI%100 ==0) timer.Start();
//   timerin.Start();
//   timerloop.Start();
  h_TDCadd = new TH1F("SummedSpectrum","Added TDC channel",nbins,0,nbins);      

  std::cout << "TDC chan #: " << histI << "\n"; 
//*******************************************************
// Loop over each of the run files...
//*******************************************************
      for(int r=0;r<nrofruns;r++) {
//           sprintf(namerun,"~/DATA/ROOT/PR226/autotrim-run0%d.root",run_no[r]);
          sprintf(namerun,"sortedfiles/sorted0%d.root",run_no[r]);
          if(flag==1) std::cout << "run #: "<<run_no[r] << "\n";
	  TFile *runfile = TFile::Open(namerun);
	  //runfile->cd("A_TDCdata");	// Subdirectory created in my f-plane.c code
	  sprintf(histoname,"TDCchan_%d",histI);       
	  h_TDCadd->Add((TH1F*)gROOT->FindObject(histoname));
// 	   TH1F *h1 = (TH1F*)gROOT->FindObject(histoname);
          runfile->Close();
	  delete runfile;
      }
      if (rebin >1) h_TDCadd->Rebin(rebin);
      
//       timerin.Stop(); 
//       timerinfile << timerin.CpuTime() << " secs reading.\n"; 
  
      if(flag ==1) {
	h_TDCadd->Draw();
	c1->Modified();    
	c1->Update();        
      }
//***********************************************************************
// Looking for the first bin with 5 filled bins on its left
//***********************************************************************

      int content =0, bincounter = 0;
      
//       h_TDCadd[histI]->Draw();
      for(int i=xmaxbin;i>xminbin;i--) {
// 	std::cout << i << endl;
	content = h_TDCadd->GetBinContent(i);
	if(content > 0){
	  bincounter ++;
	}else{
	  bincounter = 0;
	}
	if(bincounter > 4){ 
	  tmin = i+4;
	  break;
	}
      }
      
      if (rebin >1) tmin = tmin*rebin;
      if (flag!= 1) {
	  if(tmin!=0) {
		outpfile << tmin-t0corr << "\n";
	  }
    	  else {
	        outpfile << tmin << "\n";
	  }
      }else{
	std::cout << "Check: Edge found at " << tmin << "\n";
      }
//       	std::std::cout << "type anything to continue\n"; std::cin >> k;

      h_TDCadd->Reset("ICES");
      delete h_TDCadd;
  
//       if ( (histI+1)%100 ==0) {
// 	timer.Stop();
// 	timerfile << " Cpu time for histos "<< histI-99 << " to " << histI << " -> " << timer.CpuTime() << " secs.\n"; 
//       }

//       timerloop.Stop(); 
//       timerinfile << timerloop.CpuTime() << " secs in loop.\n"; 
      
	  
      }
  
//       timerloop.Stop();
//       timer.Stop()
//       timerin.Stop();
//       timerinfile.close();
//       timerfile.close();

      outpfile.close();
  
      return 0;
}

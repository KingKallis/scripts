{
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
  // Code to calculate the X1 offsets-----
  // It is set to be run in the folder where the sortedfiles are
  // Put the list of runs in the same folder or change the folders path according to your needs

  bool Mg24_NoCol = false;
  bool Mg24_Col = false;
  bool Mg26_NoCol = false;
  bool Mg26_Col = true;
  bool Sn116_NoCol = false;

 vector<int> runlist;
  if(Mg24_NoCol)
    {
      ifstream input;
      input.open("24Mg_runs_NoCol.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);	
		 if(dummy!=0)  cout << "LIST:run number " << dummy << endl;
		}
    }  
   else if(Mg24_Col)
    {
      ifstream input;
      input.open("24Mg_runs_Col.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		  if(dummy!=0) cout << "LIST:run number " << dummy << endl;
		}
    }
  else if(Mg26_NoCol)
    {
      ifstream input;
      input.open("26Mg_runs_NoCol.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(Mg26_Col)
    {
      ifstream input;
      input.open("26Mg_runs_Col.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
   else if(Sn116_NoCol)
    {
      ifstream input;
      input.open("116Sn_runs_NoCol.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		  if(dummy!=0) cout << "LIST:run number " << dummy << endl;
		}
    }

  cout << "number of runs: " << runlist.size()-1 << endl;

  Int_t nrofruns=(int)runlist.size()-1; 

  Float_t height,position,sigm,intercept,slope;
  Double_t xmin=600,xmax=800;
  TF1 *fit = new TF1("fit","gaus(0) + pol1(3)",xmin,xmax);
  cout << "Height of gaussian"<< endl;
  cin >> height;
  cout << "Position of gaussian"<< endl;
  cin >> position;
  cout << "Sigma of gaussian"<< endl;
  cin >> sigm;
  cout << "Intercep of linebkg"<< endl;
  cin >> intercept;
  cout << "Slope of linebkg"<< endl;
  cin >> slope;

  fit->SetParameters(height,position,sigm,intercept,slope);  


  Double_t a0,a1,a2,a3,a4,norm;
  Double_t width = 5.;
  Double_t par[5];


  Float_t peakposition[nrofruns];
  Float_t sigma[nrofruns];

  if(Mg24_NoCol)
    {
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_24Mg_NoCol.C");
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Cut_pad1X1_24Mg_NoCol.C");
      cout << "----------------> using cuts for 24Mg No Collimator data" << endl;
    }
  else if(Mg24_Col)
    {
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_24Mg_Col.C");
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Cut_pad1X1_24Mg_Col.C");
      cout << "----------------> using cuts for 24Mg Collimator data" << endl;
    }
  else if(Mg26_NoCol)
    {
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_26Mg_NoCol.C");
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Cut_pad1X1_26Mg_NoCol.C");
      cout << "----------------> using cuts for 24Mg No Collimator data" << endl;
    }
  else if(Mg26_Col)
    {
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_26Mg_Col.C");
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Cut_pad1X1_26Mg_Col.C");
      cout << "----------------> using cuts for 24Mg Collimator data" << endl;
    }

for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f){
	     TH1F *hX1pos = new TH1F("hX1pos","X1 Position",300,500.,800.);

             if(Mg24_NoCol)
              {
	        DATA->Draw("X1pos>>hX1pos","Alphas_24Mg_NCol && Cut_pad1X1_24Mg_NoCol","");
                //cout << "24Mg No Collimator cuts" << endl;
              }
	     else if (Mg24_Col)
	      {
	        DATA->Draw("X1pos>>hX1pos","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","");
		//cout << "24Mg Collimator cuts" << endl;
	      }
             else if(Mg26_NoCol)
              {
	        DATA->Draw("X1pos>>hX1pos","Alphas_26Mg_NCol && Cut_pad1X1_26Mg_NoCol","");
                //cout << "26Mg No Collimator cuts" << endl;
              }
	     else if (Mg26_Col)
	      {
	        //DATA->Draw("X1pos>>hX1pos","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col",""); // NOT CORRECTED
                DATA->Draw("X1posCTOF>>hX1pos","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col",""); // CORRECTED
		//cout << "26Mg Collimator cuts" << endl;
	      }


	  int entries = hX1pos->GetEntries();
	  cout << "ENTRIES in histo = " <<entries<<endl;
	  if(entries==0) 
		{cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;
        	 peakposition[i] = peakposition[0];
         	 sigma[i] = 0;
		}else{

	  ///   ***************** TO BE CHECKED
              TSpectrum *sp = new TSpectrum();
	      sp->Search(hX1pos,sigm,"",0.8); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
	      int n_peaks_found = sp->GetNPeaks(); 
//  	      sprintf(buffer,"sorted0%d.root",runlist[i]);
	      std::cout << n_peaks_found << " ---------" << endl;
              Float_t* x = sp->GetPositionX();
	     // Float_t xxx = x[0];
	      cout << x[0] << " *************" << endl;
              xmin=x[0]-10*sigm, xmax=x[0]+10*sigm;
 	      cout << xmin << " " << xmax <<" " <<  x[0] << endl;
              fit->SetParameter(1,x[0]);
              hX1pos->Fit(fit,"R","",xmin,xmax);
                
       
         /// ************************************
 
        //  hX1pos->Fit(fit,"R","");
	  fit->GetParameters(par);

	  //a0=par[0];a1=par[1];a2=par[2];a3=par[3];
          //cout << endl << " par0 " << a0 <<"; par1 " << a1 <<"; par2 " << a2 << "; par3 "<< a3 << "; par4 "<< a4<< endl << endl;

          peakposition[i] = par[1];
          sigma[i] = par[2];
	  }
	  c1->Modified(); c1->Update();
	  c1->WaitPrimitive();
          if(i<(int)runlist.size()-1-1)c1->Clear();
	} 
  }
  for(Int_t i=0;i<nrofruns;i++)	{
     cout << " "<< runlist[i] <<" "<< peakposition[i] <<" "<< sigma[i] << endl;
  }
  for(Int_t i=0;i<nrofruns;i++)	{
     cout << ""<< runlist[i] <<"  Difference compared with run "<< runlist[0] <<"  "<< peakposition[i]-peakposition[0] << endl;
  }
   
  //Creates file with the offsets in the current folder. Then move it to the analyser folder and remove _new to be able to use it
  ofstream outputFile;
  outputFile.open("X1offsetsPR251_new.dat");

  for(Int_t i=0;i<nrofruns;i++)	{
     cout << runlist[i] <<"  "<< float(peakposition[0]-peakposition[i]) << endl;
     outputFile << runlist[i] <<"  "<< float(peakposition[0]-peakposition[i]) << endl;
  }
  outputFile.close();
  cout << "File Offsets Created!\n";

}





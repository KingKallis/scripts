{
  bool CsCo_quadon = true;
  bool CsCo_quadoff = false;
  bool AmBe_quadon = false;
  bool Co56_quadon = false;

   vector<int> runlist;
  if(CsCo_quadon)
    {
      ifstream input;
      input.open("CsCo_calib_runs_quadon.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);	
		 if(dummy!=0)  cout << "LIST:run number " << dummy << endl;
		}
    }  
   else if(CsCo_quadoff)
    {
      ifstream input;
      input.open("CsCo_calib_runs_quadoff.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		  if(dummy!=0) cout << "LIST:run number " << dummy << endl;
		}
    }
  else if(AmBe_quadon)
    {
      ifstream input;
      input.open("AmBe_calib_runs_quadon.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(Co56_quadon)
    {
      ifstream input;
      input.open("Co56_calib_runs_quadon.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
   
  cout << "number of runs: " << runlist.size()-1 << endl;

  Int_t nrofruns=(int)runlist.size()-1; 
 
  Double_t xmin,xmax;
  Double_t par[5];


  Float_t peakposition[nrofruns];
  Float_t sigma[nrofruns];

 TF1 *fit = new TF1("fit","gaus(0) + pol1(3)");
 c1 = new TCanvas("c1","Checks offset energy",10,10,900,600);



 for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f){
	     TH1F *hLaBr1 = new TH1F("hLaBr1","Gamma Energy LaBr1",1500,0.,1500.);
	    // TH1F *hLaBr2 = new TH1F("hLaBr2","Gamma Energy LaBr2",4096,0.,4096.);

	     DATA->Draw("GammaEnergy>>hLaBr1","GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1","");
           //  DATA->Draw("GammaEnergy>>hLaBr2","GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==2","");
            
             int entries = hLaBr1->GetEntries();
	     cout << "ENTRIES in histo = " << entries <<endl;
	     if(entries==0)
		{cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;
        	 peakposition[i] = peakposition[0];
         	 sigma[i] = 0;
		}else{

	       TSpectrum *sp = new TSpectrum();
	       sp->Search(hLaBr1,5,"",0.7); // h histoname; 1. sigma; 0.28 threshold (minimum intensity considered = maximum * threshold)
	       int n_peaks_found = sp->GetNPeaks(); 
         /*      if(i==0)Float_t* x = sp->GetPositionX();
               Float_t* y = sp->GetPositionY();
               //cout << x[0] << "^^^^^^^^^^^^^" << y[0] << endl;
               TLine *line = new TLine(x[0],0,x[0],y[0]);
               line->SetLineColor(1);
	       line->SetLineWidth(2);
	       line->SetLineStyle(2);
               line->Draw();
         */

	        std::cout << n_peaks_found << " ---------" << endl;
                Float_t* x = sp->GetPositionX();
  	        cout << x[0] << " *************" << endl;
		peakposition[i] = x[0];
               // xmin=x[0]-10*5, xmax=x[0]+10*5;
 	    //    cout << xmin << " " << xmax <<" " <<  x[0] << endl;
            //    fit->SetParameter(1,x[0]);
            //    hLaBr1->Fit(fit,"R","",xmin,xmax);
		//fit->GetParameters(par);
		//peakposition[i] = par[1];
            //    sigma[i] = par[2];
	  
	   }
               c1->Modified();	
               c1->Update();        
	       c1->WaitPrimitive();
	       if(i<(int)runlist.size()-1-1)c1->Clear();
	    
     }
    }
  for(Int_t i=0;i<nrofruns;i++)	{
    // cout << " "<< runlist[i] <<" "<< peakposition[i] <<" "<< sigma[i] << endl;
       cout << " "<< runlist[i] <<" "<< peakposition[i] << endl;
  }
 for(Int_t i=0;i<nrofruns;i++)	{
     cout << ""<< runlist[i] <<"  Difference compared with run "<< runlist[0] <<"  "<< peakposition[i]-peakposition[0] << endl;
  }

}

{
  // Code to calculate the TOF offsets-----
  // It is set to be run in the folder where the sortedfiles are
  // Put the list of runs in the same folder or change the folders path according to your needs

  bool Mg24_NoCol = false;
  bool Mg24_Col = false;
  bool Mg26_NoCol = false;
  bool Mg26_Col = false;
  bool Sn116_NoCol = false;
  bool Sm154_Col = true;
  bool Sm154_NoCol = false;


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
   else if(Sm154_Col)
    {
      ifstream input;
      input.open("154Sm_runs_Col.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(Sm154_NoCol)
    {
      ifstream input;
      input.open("154Sm_runs_NoCol.dat");
      
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
    
    
  cout << "number of runs: " << runlist.size()-1 << endl;

  Int_t nrofruns=(int)runlist.size()-1; 

/*  int x1poslow,x1poshi;

  cout << "lower limit for the X1Pos peak"<< endl;
  cin >> x1poslow;
  cout << "higher limit for the X1Pos peak"<< endl;
  cin >> x1poshi;

  TCut CUTX1pos = "X1pos>x1poslow && X1pos<x1poshi";
*/

  TCut CUTX1pos = "X1pos>620 && X1pos<640"; //24Mg----------------> REMEBER TO CHANGE THIS TO SELECT THE PEAK OF INTEREST
 // TCut CUTX1pos = "X1pos>660 && X1pos<720"; //26Mg----------------> REMEBER TO CHANGE THIS TO SELECT THE PEAK OF INTEREST

  Double_t a0,a1,a2,a3,a4,norm;
  Double_t width = 5.;
  Double_t par[5];


  Float_t peakposition[nrofruns];
  Float_t sigma[nrofruns];

  //gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_24Mg_NoCol.C");
  gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_24Mg_Col.C");


for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f){
	     TH1F *hpad1 = new TH1F("hpad1","pad1 spectrum",800,1000.,1800.);
	  //   DATA->Draw("pad1>>hpad1","Alphas_24Mg_NoCol && CUTX1pos","");
             DATA->Draw("pad1>>hpad1","Alphas_24Mg_Col" && CUTX1pos,"");
	  
	  int entries = hpad1->GetEntries();
	  cout << "ENTRIES in histo = " <<entries<<endl;
	  if(entries==0) 
		{cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;
        	 peakposition[i] = peakposition[0];
         	 sigma[i] = 0;
		}else{
	  

	  hpad1->Fit("gaus","R","",1200,1700);  

	  gaus->GetParameters(par);

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
  outputFile.open("PAD1offsetsPR251_new.dat");

  for(Int_t i=0;i<nrofruns;i++)	{
     cout << runlist[i] <<"  "<< float(peakposition[0]-peakposition[i]) << endl;
     outputFile << runlist[i] <<"  "<< float(peakposition[0]-peakposition[i]) << endl;
  }
  outputFile.close();
  cout << "File Offsets Created!\n";

}





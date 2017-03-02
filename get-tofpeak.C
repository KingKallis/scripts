{
  // Code to calculate the TOF offsets-----
  // It is set to be run in the folder where the sortedfiles are
  // Put the list of runs in the same folder or change the folders path according to your needs

  bool Mg24_NoCol = true;
  bool Mg24_Col = false;
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



  //TF1 *fit = new TF1("fit","gaus(0) + pol1(3)",1,800);

  Double_t a0,a1,a2,a3,a4,norm;
  Double_t width = 5.;
  Double_t par[5];


  Float_t peakposition[nrofruns];
  Float_t sigma[nrofruns];



for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f){
  	  TH1F *htof = new TH1F("htof","TOF",250,1600,1850);//350,1600.,2300.
          DATA->Draw("tof>>htof","","");
	  
	  int entries = htof->GetEntries();
	  cout << "ENTRIES in histo = " <<entries<<endl;
	  if(entries==0) 
		{cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;
        	 peakposition[i] = peakposition[0];
         	 sigma[i] = 0;
		}else{
	  
	  htof->Fit("gaus","R","",1600,1850);  

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
  outputFile.open("TOFoffsetsPR251_new.dat");

  for(Int_t i=0;i<nrofruns;i++)	{
     cout << runlist[i] <<"  "<< int(peakposition[0]-peakposition[i]) << endl;
     outputFile << runlist[i] <<"  "<< int(peakposition[0]-peakposition[i]) << endl;
  }
  outputFile.close();
  cout << "File Offsets Created!\n";

}





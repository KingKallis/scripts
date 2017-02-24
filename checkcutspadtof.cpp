{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;
  bool Mg26 = false;
  bool C12 = false;
  bool Sm154 = false;

  char pause;
  c1 = new TCanvas("c1","Checks on Cut PadvsToF",10,10,900,600);
  

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
		}
    }  
  if(Mg24_Col)
    {
      ifstream input;
      input.open("24Mg_runs_Col.dat");
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(Mg26)
    {
      ifstream input;
      input.open("26Mg_runs.dat");
      
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(C12)
    {
      ifstream input;
      input.open("12C_runs.dat");
      
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  else if(Sm154)
    {
      ifstream input;
      input.open("154Sm_runs.dat");
      
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }

  cout << "number of runs: " << runlist.size()-1 << endl;
  
  for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f){
	      // ******* Plot graph to check the cut on padvstof                
              gROOT->ProcessLine(".x ../../Alphas.C");
              // TCutG *cut0=new TCutG();
              // TCutG *cut0   = (TCutG*)gROOT-> Get( "Alphas" );
	      TH2F *pad1vstof_check = new TH2F("pad1vstof_check","Check of the cut in padvstof",350,1600,2300,3000,0,3000);

              DATA->Draw("pad1:tof>>pad1vstof_check","","col");
              cutg->SetLineColor(2);
              cutg->SetLineWidth(2);
              cutg->Draw("same");
	      c1->Modified();
	      c1->Update();
	      c1->WaitPrimitive();

       	    }

  //   cout << "Press any key to continue...";
  //    cin >> pause;		

      }
	  


}

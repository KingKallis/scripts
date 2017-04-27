{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;
  bool Mg26_NoCol = false;
  bool Mg26_Col = false;
  bool C12 = false;
  bool Sm154 = false;
  bool Sn116_NoCol = false;


  bool maketree = false;

  TChain *DATAch = new TChain("DATA");

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
  else if(Mg24_Col)
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
  else if(Sn116_NoCol)
    {
      ifstream input;
      input.open("116Sn_runs_NoCol.dat");
      
      while(!input.eof())
		{
		  int dummy = 0;
		  input >> dummy;
		  runlist.push_back(dummy);
		}
    }
  cout << "number of runs: " << runlist.size()-1 << endl;
 
  //  Include any cuts that you might want to use ---------------------------
  
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
      cout << "----------------> using cuts for 26Mg No Collimator data" << endl;
    }
  else if(Mg26_Col)
    {
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Alphas_26Mg_Col.C");
      gROOT->ProcessLine(".x /home/luna/codes/PR251-analysis/sortedfiles/gates/Cut_pad1X1_26Mg_Col.C");
      cout << "----------------> using cuts for 26Mg Collimator data" << endl;
    }
  

  // ----------------------------------------
  

  for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f)
		{
		  DATAch->Add(buffer);
		  cout << "Total N. events: " << DATAch->GetEntries() << endl;
		}
    }

 
  
 if(Mg24_NoCol)
    {
      DATAch->Draw("Ex>>hEx(1250,3.5,16)","Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol && X1flag==0 && U1flag==0 && Y1>-20 && Y1<20","");
    }
  else if(Mg24_Col)
    {
      DATAch->Draw("Ex>>hEx(1250,3.5,16)","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0 && Y1>-20 && Y1<20","");
    }
  else if(Mg26_NoCol)
    {
      DATAch->Draw("Ex>>hEx(1250,3.5,16)","Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol && X1flag==0 && U1flag==0 && Y1>-20 && Y1<20","");
    }
  else if(Mg26_Col)
    {
      DATAch->Draw("Ex>>hEx(1250,3.5,16)","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && X1flag==0 && U1flag==0 && Y1>-20 && Y1<20","");
    }
  
   cout << "events: " << hEx->GetEntries() << endl;

  if(maketree){
  	 TFile *myfile=new TFile("Chainedtree.root", "RECREATE");
     cout << DATAch->GetEntries() << endl;
     TTree *TF = DATAch->CopyTree("Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0");
     TF->SetName("DATA2");
     myfile = TF->GetCurrentFile();
     myfile->Write();
     myfile->Close();
     
  }

}

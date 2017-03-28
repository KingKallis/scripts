{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;
  bool Mg26 = false;
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
  
//gROOT->ProcessLine(".x pad_tof_alphas0.C"); // USE THIS KIND OF LINE FOR CUTS SAVED AS C FILES ".C"

 //gROOT->ProcessLine(".x CUTpadVStof.C");
//TCutG *cut0=new TCutG();
//TCutG *cut0   = (TCutG*)gROOT-> Get( "CUTpadVStof" );
//gROOT->ProcessLine(".x cut1.C");
//TCutG *cut1=new TCutG();
//TCutG *cut1   = (TCutG*)gROOT-> Get( "cut1" );
// gROOT->ProcessLine(".x Alphas.C");
//TCutG *cut2=new TCutG();
//TCutG *cut2   = (TCutG*)gROOT-> Ge KIND OF LINE FOR CUTS SAVED AS C FILES t( "Alphas" );
//TFile * file2 = new TFile("yourcut.root","OLD"); // USE THIS KIND OF LINE FOR CUTS SAVED AS ROOT FILES ".root"
//gROOT->ProcessLine(".x pad_tof.C"); // USE THIS KIND OF LINE FOR CUTS SAVED AS C FILES ".C"
//TCutG *cut3=new TCutG();
//TCutG *cut3   = (TCutG*)gROOT-> FindObject( "pad_tof" );
//TCutG *cut3   = (TCutG*)gROOT-> Get( "pad_tof" );
//TCutG *cut = new TCutG();
//TFile * file2 = new TFile("pad_tof0.root","OLD"); // USE THIS KIND OF LINE FOR CUTS SAVED AS ROOT FILES ".root"
//TCutG *cut   = (TCutG*)gROOT-> Get( "pad_tof0" );
//file2 -> Close();7

//    TCut CUTcoinc = "abs((18686.5-19.35*X1pos) -GammaEnergy -1368.) < 200";
  // ----------------------------------------
  

  for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256];
      sprintf(buffer,"../sortedfiles/sorted0%d.root",runlist[i]);
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);

      if(f)
		{
		  DATAch->Add(buffer);
		  cout << "Total N. events: " << DATAch->GetEntries() << endl;
		}
    }

  //DATA->SetAlias("ExK600","18686.5-19.35*X1pos");   // true for 24,25 Oct?

  DATA->SetAlias("X1new","X1pos-0.08*(tof-1940)-0.0019*(tof-1940)**2");
  DATA->SetAlias("ExK600","18652.1-19.94*X1new");

//  DATA->Draw("GammaEnergy:ExK600>>h2d(1600,0,16000,1000,0,10000)","GammaDetectorType==\"Addback\" && Y1>-20 && Y1<20 && CUTpadVStof","col");
//  DATA->Draw("GammaEnergy:18686.5-19.35*X1pos>>h2d(1600,0,16000,1000,0,10000)","GammaDetectorType==\"Addback\" && Y1>-20 && Y1<20 && CUTpadVStof","col");
//  DATA->Draw("GammaEnergy>>h1d(1600,0,16000)","GammaDetectorType==\"Addback\"  && CUTpadVStof","");
/*
  DATA->Draw("GammaEnergy:ExK600>>hLaBrvsK600(1600,0,16000,12000,0,12000)", "Alphas && Y1 > -20 && Y1 <20 && GammaTime >2000 && GammaTime<4500 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1  ","col");
  
  DATA->Draw("GammaEnergy:ExK600>>hClovervsK600(1600,0,16000,12000,0,12000)", "Alphas && Y1 > -20 && Y1 <20 && GammaTime >2000 && GammaTime<4500 && GammaDetectorType==\"Addback\"","col");
  
  DATA->Draw("GammaTime>>jj(10000,-10000,10000)","GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && Y1>-10 && Y1<10 && Alphas", "");
*/
//pad_tof_alphas0 && Y1>-15 && Y1<15 && GammaTime>3800 && GammaTime<4400

  if(maketree){
  	 TFile *myfile=new TFile("Chainedtree.root", "RECREATE");
     cout << DATAch->GetEntries() << endl;
     //TTree *TF = DATAch->CopyTree("X1pos<800 && X1pos>0 && padVStof ");
     TTree *TF = DATAch->CopyTree("pad1>600 && Y1>-15 && Y1<15");
     TF->SetName("DATA2");
     myfile = TF->GetCurrentFile();
     myfile->Write();
     myfile->Close();
     
  }

}

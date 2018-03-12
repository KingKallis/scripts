{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;
  bool Mg26 = false;
  bool C12 = false;
  bool Sm154 = false;
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



 c1 = new TCanvas("c1","Checks tof vs X1posCTOF",10,10,900,600);
  for(int i=0;i<(int)runlist.size()-1;i++)
    {
      char buffer[256], histo[256];
      sprintf(buffer,"sorted0%d.root",runlist[i]);
      cout << buffer << endl;
      TFile *f = TFile::Open(buffer);
      sprintf(histo,"histo%d",i);
      cout << histo << endl;

      if(f){
	     
           
            // ******* Plot graph to check X1 position 
            TH2F *htofvsX1posCTOF = new TH2F("htofvsX1posCTOF","Check tof vs X1posCTOF",700,100,800,100,1910,2010);
	   // TH2F *htofvsX1posO = new TH2F("htofvsX1posO","Check tof vs X1posO",700,100,800,100,1910,2010);              
	    
            if(Mg24_NoCol)
              {
		//DATA->Draw("tof:X1posO>>htofvsX1posO","Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","");//NON CORRECTED
	        DATA->Draw("tof:X1posCTOF>>htofvsX1posCTOF","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","colz");//CORRECTED
                //cout << "24Mg No Collimator cuts" << endl;
              }
	     else if (Mg24_Col)
	      {
	      //  DATA->Draw("tof:X1posO>>htofvsX1posO","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","");//NON CORRECTED
	        DATA->Draw("tof:X1posCTOF>>htofvsX1posCTOF","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","colz");//CORRECTED
		//cout << "24Mg Collimator cuts" << endl;
	      }
             else if(Mg26_NoCol)
              {
		//DATA->Draw("tof:X1posO>>htofvsX1posO","Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol","");//NON CORRECTED
	        DATA->Draw("tof:X1posCTOF>>htofvsX1posCTOF","X1flag==0 && U1flag==0 && Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol","colz");//CORRECTED
                //cout << "26Mg No Collimator cuts" << endl;
              }
	     else if (Mg26_Col)
	      {
	      //  DATA->Draw("tof:X1posO>>htofvsX1posO","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col","");//NON CORRECTED
	        DATA->Draw("tof:X1posCTOF>>htofvsX1posCTOF","X1flag==0 && U1flag==0 && Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col","colz");//CORRECTED
		//cout << "26Mg Collimator cuts" << endl;
	      }
	      
              int entries = htofvsX1posCTOF->GetEntries();
	      cout << "ENTRIES in histo = " <<entries<<endl;
	      if(entries==0) cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;

           //   htofvsX1posO->Draw();
           //   htofvsX1posCTOF->Draw("");
	      
              TLine *line1 = new TLine(633,1910,633,2010);
              line1->SetLineColor(2);
	      line1->SetLineWidth(2);
	      line1->SetLineStyle(2);
              line1->Draw();

              TLine *line2 = new TLine(255,1910,255,2010);
              line2->SetLineColor(2);
	      line2->SetLineWidth(2);
	      line2->SetLineStyle(2);
              line2->Draw();

                c1->Modified();	
                c1->Update();        
	        c1->WaitPrimitive();
	    //    if(i<(int)runlist.size()-1-1)c1->Clear();


       //     c2 = new TCanvas("c2","Checks X1pos",10,10,900,600);
            // ******* Plot graph to check X1 position 
            TH1F *hX1posCTOF = new TH1F("hX1posCTOF","Check X1posCTOF",700,100,800);
	    TH1F *hX1posO = new TH1F("hX1posO","Check X1posO",700,100,800);              
	    
            if(Mg24_NoCol)
              {
		DATA->Draw("X1posO>>hX1posO","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","");//NON CORRECTED
	        DATA->Draw("X1posCTOF>>hX1posCTOF","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","");//CORRECTED
                //cout << "24Mg No Collimator cuts" << endl;
              }
	     else if (Mg24_Col)
	      {
	        DATA->Draw("X1posO>>hX1posO","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","");//NON CORRECTED
	        DATA->Draw("X1posCTOF>>hX1posCTOF","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","");//CORRECTED
		//cout << "24Mg Collimator cuts" << endl;
	      }
            else if(Mg26_NoCol)
              {
		DATA->Draw("X1posO>>hX1posO","X1flag==0 && U1flag==0 && Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol","");//NON CORRECTED
	        DATA->Draw("X1posCTOF>>hX1posCTOF","X1flag==0 && U1flag==0 && Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol","");//CORRECTED
                //cout << "26Mg No Collimator cuts" << endl;
              }
	     else if (Mg26_Col)
	      {
	        DATA->Draw("X1posO>>hX1posO","X1flag==0 && U1flag==0 && Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col","");//NON CORRECTED
	        DATA->Draw("X1posCTOF>>hX1posCTOF","X1flag==0 && U1flag==0 && Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col","");//CORRECTED
		//cout << "26Mg Collimator cuts" << endl;
	      }	

      
              int entries = htofvsX1posCTOF->GetEntries();
	      cout << "ENTRIES in histo = " <<entries<<endl;
	      if(entries==0) cout << "------------> Run number " << runlist[i] << " IS EMPTY "<<endl;
              
	      
              
              hX1posCTOF->SetLineColor(2);
              hX1posCTOF->Draw();
              hX1posO->Draw("same");

              c1->Modified();	
              c1->Update();        
	      c1->WaitPrimitive();
	  /*    if(i<(int)runlist.size()-1-1)
                {
		  c1->Clear();
                }*/

       	    }
		

      }



}



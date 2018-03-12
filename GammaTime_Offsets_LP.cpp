///////////////////////////////////////////////////////////////////////////
//		Calculate the Gamma time offsets    			 //
///////////////////////////////////////////////////////////////////////////
#include <TF1.h>

//defining fit function
double Gaus_2sigma( double *x, double*par )
{
  double xx = x[0];
  double height = par[0];
  double mean = par[1];
  double sigma_1 = par[2];
  double sigma_2 = par[3];
  
  //double Pol = par[4] + xx*(par[5] + xx*par[6] );
  
  if( xx < mean ) 
    {
      return  height*exp( -(xx - mean)*(xx - mean)/(2*sigma_1*sigma_1) );
    }
  else
    {
      return  height*exp( -(xx - mean)*(xx - mean)/(2*sigma_2*sigma_2) );
    }
}



int main()
{

   //Parameters

	bool Mg24_NoCol = false;
	bool Mg24_Col = true;

	char *histname = new char[32];
	char *histname = new char[2];
	char *DetectorOption = new char[256];
	Float_t peakposition[32];
	Float_t sigma[32];
	Double_t Clover_par[3];
	Float_t LaBr_peakposition[2];
	Float_t LaBr_sigma[2];
	Double_t LaBr_par[3];
        TCanvas *C = new TCanvas;


  //Read in Cuts for PID selection
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

    //read in file 
   char buffer[256];
    sprintf(buffer,"sorted0%d.root",2227);
     TFile *f = TFile::Open(buffer);



 c1 = new TCanvas("c1","Checks GammaTime",10,10,900,600);
 //defining fit
 TF1 *f_Gaus_2sigma = new TF1("f_Gaus_2sigma", Gaus_2sigma, 4000, 7000, 4 );
 f_Gaus_2sigma->SetParameters(70, 4500, 20, 60);


   //Create gammaTime plot for each clover segment
	for(int i=1;i<9;i++)
	{	
	 for(int j=1;j<5;j++)
	 {
	  sprintf(histname,"Clover_%d_Segm_%d",i,j);
	  TH1F *hGammaTime = new TH1F("hGamTime",histname,400,3000,7000); //Check range		
	  sprintf(DetectorOption,"Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0 && Y1>-20 && Y1<20 && GammaDetectorType==\"Clover\" && GammaDetectorLabel==%d && GammaDetectorSegm==%d",i,j);
	  DATAch->Draw("GammaTime>>hGamTime",DetectorOption,"");
	 //fit
	 hGammaTime->Fit("f_Gaus_2sigma","R","",4000,5200);  
	/*  Gaus_2sigmas->GetParameters(par);
          peakposition[(i-1)*4+j] = Clover_par[1];
          sigma[(i-1)*4+j] = Clover_par[2];
*/
	  c1->Modified(); c1->Update();
	  c1->WaitPrimitive();
 	         cout << "Det num " << (i-1)*4+j << endl; //check

	  hGammaTime->Clear();
          if(j<5)c1->Clear();
	  }
	 if(i<9)c1->Clear();
	 }

/*
	//Check offset values   
	for(Int_t k=1;k<33;i++)	
	  {
	     cout << " "<< k <<" "<< peakposition[k] <<" "<< sigma[k] << endl;
	  }
	  for(Int_t k=1;k<9;i++)	
	  {
	     cout << ""<< k <<"  Difference compared with Gamma detector 1 " <<"  "<< peakposition[k]-peakposition[1] << endl;
	  }




   //Create gammaTime plot for each LaBr Scintillator
     for(int i=1;i<3;i++)
      {	
      sprintf(histname2,"LaBr_%d",i);
      TH1F *hGammaTime = new TH1F("hGamTime",histname2,200,4000,6000); //Check range for peak 
      sprintf(DetectorOption,"Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0 &&Y1>-20 &&Y1<20 &&GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==%d",i);
      DATAch->Draw("GammaTime>>hGamTime",DetectorOption,"");
	//fit
	hGammaTime->Fit("gaus","R","",4500,5500);  
	gaus->GetParameters(LaBr_par);
	LaBr_peakposition[i] = LaBr_par[1];
	LaBr_sigma[i] = LaBr_par[2];
	C->Modified(); C->Update();
	C->WaitPrimitive();
	cout << "NEXT" << endl; //check
        if(i<2)C->Clear();
      }
	  //Check offset values   
	  for(Int_t i=1;i<3;i++)	
	    {
	     cout << " "<< i <<" "<< LaBr_peakposition[i] <<" "<< LaBr_sigma[i] << endl;
	    }
	  for(Int_t i=1;i<3;i++)
	    {
	     cout << ""<< i <<"  Difference compared with LaBr detector 1 " <<"  "<< LaBr_peakposition[i]-LaBr_peakposition[1] << endl;
	    }



   
  //Creates file with the offsets in the current folder. Then move it to the analyser folder and remove _new to be able to use it
	  ofstream outputFile;
	  outputFile.open("GammaTimeOffsetsPR251_new.dat");
	
	  for(Int_t k=1;k<33;i++)
	  {
	    cout << k <<"  "<< int(peakposition[k]-peakposition[1]) << endl;
	    outputFile << k <<"  "<< int(peakposition[k]-peakposition[1]) << endl;
	  }
	  for(Int_t i=1;i<3;i++)
	  {
	    cout << i+100 <<"  "<< int(LaBr_peakposition[i]-LaBr_peakposition[1]) << endl;
	    outputFile << i+100 <<"  "<< int(LaBr_peakposition[i]-LaBr_peakposition[1]) << endl;
	  }
	  for(Int_t i=1;i<3;i++)
	  {
	    cout << i+102 <<"  "<< int(LaBr_peakposition[i]-LaBr_peakposition[1]) << endl;
	    outputFile << i+102 <<"  "<< int(LaBr_peakposition[i]-LaBr_peakposition[1]) << endl;
	  }
	  outputFile << "eof" << endl;
	  outputFile.close();
	  cout << "File Offsets Created!\n";
*/

}




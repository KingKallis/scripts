///////////////////////////////////////////////////////////////////////////
// Macro for extrapolating line shape correction parameters	  	 //
//									 //
//  The run file of interest should be read in to root			 //
//  before implementing this script 					 //
//									 //
///////////////////////////////////////////////////////////////////////////

{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;

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

//=============================================================
// X1Y1 lineshape correction
//=============================================================


  c1 = new TCanvas("c1","Checks lineshape X1Y1",10,10,900,600);
 //ToF vs X1 histogram
  TH2F *hY1vsX1posO = new TH2F("hY1vsX1posO","Y1 vs X1posO",700,100,800,480,-60.,60.);
 
  if(Mg24_NoCol)
    {
      DATA->Draw("Y1:X1posO>> hY1vsX1posO","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col");
    }
  else if(Mg24_Col)
    {
      DATA->Draw("Y1:X1posO>> hY1vsX1posO","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col");
    }

   hY1vsX1posO->GetXaxis()->SetTitle("X1 position (mm)");
   hY1vsX1posO->GetYaxis()->SetTitle("Y1 position");
   c1 -> Update();
   c1 -> Modified();


  TH2F *hPeakofInterest_Y1X1 = new TH2F("hPeakofInterest_Y1X1","Y1 vs X1posO",40,-20,20,480,-60.,60.);

  TCanvas *c2 = new TCanvas("c2","Y1X1 peak of interest",10,10,900,600);

   Double_t X1mean=0;

   cout << "Mean value for X1posO" << endl;
   cin >> X1mean;
   cout << "X1posO = " << X1mean << endl;


  if(Mg24_NoCol)
    {
      DATA->SetAlias("X1posat0",Form("X1posO-%g",X1mean)); //define the X1posO of the peak of interest to 0
      DATA->Draw("Y1:X1posat0>> hPeakofInterest_Y1X1","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col"); 
    }
  else if(Mg24_Col)
    {
      DATA->SetAlias("X1posat0",Form("X1posO-%g",X1mean));  //define the X1posO of the peak of interest to 0
      DATA->Draw("Y1:X1posat0>> hPeakofInterest_Y1X1","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col"); 
    }  

  hPeakofInterest_Y1X1->GetXaxis()->SetTitle("X1-X1mean (mm)");
  hPeakofInterest_Y1X1->GetYaxis()->SetTitle("Y1 position");
  c2 -> Update();
  c2 -> Modified();


   TCanvas *c3 = new TCanvas("c3","Fit Y1X1 correction",10,10,900,600);
  
   float binmin_Y1=0;
   float binmax_Y1=0;
   float bininter_Y1=0, bindiff_Y1=0, bintemp_Y1=0;
   Double_t par_Y1X1[3];
   Double_t a0,a1,a2;
   char key;
 
   cout << "lowest bin for the fitting of Y1X1" << endl;
   cin >> binmin_Y1;
   cout << "highest bin for the fitting for Y1X1" << endl;
   cin >> binmax_Y1;
   cout << "binmin_Y1 = " << binmin_Y1 << " binmax_Y1 = " << binmax_Y1 << endl;
  
   bindiff_Y1 = binmax_Y1-binmin_Y1;

//=============== check to see the sliceX projection used for the fit ========================
/*
   for(int i=0;i<bindiff_Y1-1;i++)
    {
      if(i==0) bintemp_Y1=binmin_Y1;
      bintemp_Y1=bintemp_Y1+1;
      bininter_Y1=bintemp_Y1+1;
      cout << bintemp_Y1 << " " << bininter_Y1 << endl;
      hPeakofInterest_Y1X1->ProjectionX("hPeakofInterest_Y1X1_px",bintemp_Y1,bininter_Y1,"");
      hPeakofInterest_Y1X1_px->Draw();
      c3->Modified();	
      c3->Update();        
      c3->WaitPrimitive();
      c3->Clear();
    }
*/
//=============================================================================================

 //  cout << "binmin_Y1 = " << binmin_Y1 << " binmax_Y1 = " << binmax_Y1 << endl;

   hPeakofInterest_Y1X1->FitSlicesX(0,binmin_Y1,binmax_Y1,0,"Q",0); //see below how the FitSlicesX works
   hPeakofInterest_Y1X1_1->Draw(); //histoname_1 is the histogram of the centroid parameters for each slice 
   hPeakofInterest_Y1X1_1->Fit("pol2");
   pol2->GetParameters(par_Y1X1);
   a0=par_Y1X1[0];a1=par_Y1X1[1];a2=par_Y1X1[2];
   cout << endl << " par0_Y1 " << a0 <<"; par1_Y1 " << a1 <<"; par2_Y1 " << a2 << endl;
   hPeakofInterest_Y1X1_1->GetXaxis()->SetRangeUser(-20., 20.);
   hPeakofInterest_Y1X1_1->GetYaxis()->SetRangeUser(-20., 20.);
   c3 -> Update();
   c3 -> Modified();

 //implement lineshaping correction
   
   DATA->SetAlias("X1_Y1new",Form("X1posO-(%g+(%g*(Y1))+(%g*pow(Y1,2)))",a0,a1,a2));

   TH2F *hY1vsX1new = new TH2F("hY1vsX1new","Y1 vs X1_Y1new",700,100,800,480,-60,60);

   TCanvas *c4 = new TCanvas("c4","Y1 vs X1 corrected matrix",10,10,900,600);

  if(Mg24_NoCol)
    {
      DATA->Draw("Y1:X1_Y1new>> hY1vsX1new","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col"); 
    }
  else if(Mg24_Col)
    {
      DATA->Draw("Y1:X1_Y1new>> hY1vsX1new","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col"); 
    }

   hY1vsX1new->GetXaxis()->SetTitle("Corrected X1 position (mm)");
   hY1vsX1new->GetYaxis()->SetTitle("Y1 position");
   c4 -> Update();
   c4 -> Modified();

   cout << " " << endl;    cout << " " << endl;    cout << " " << endl;
   cout << "----------------FINISHED Y1 vs X1 LINESHAPE CORRECTION----------------" << endl;
   cout << " " << endl;    cout << " " << endl;    cout << " " << endl;

//   cout << "Press key+enter to continue" << endl;
//   cin >> key;   
//   c1->Close(); c2->Close(); c3->Close(); c4->Close();


//=============================================================
// X1tof lineshape correction
//=============================================================

  cout << "****************STARTING TOF vs X1 LINESHAPE CORRECTION****************" << endl;
  cout << " " << endl;    cout << " " << endl;    cout << " " << endl;

  c5 = new TCanvas("c5","Checks lineshape tofX1",10,10,900,600);
 //ToF vs X1 histogram
  TH2F *htofvsX1_Y1new = new TH2F("htofvsX1_Y1new","tof vs X1_Y1new",700,100,800,100,1910,2010);
 
  if(Mg24_NoCol)
    {
      DATA->Draw("tof:X1_Y1new>>htofvsX1_Y1new","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col");
    }
  else if(Mg24_Col)
    {
      DATA->Draw("tof:X1_Y1new>>htofvsX1_Y1new","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col");
    }

   htofvsX1_Y1new->GetXaxis()->SetTitle("X1_Y1new position (mm)");
   htofvsX1_Y1new->GetYaxis()->SetTitle("ToF");
   c5 -> Update();
   c5 -> Modified();


  TH2F *hPeakofInterest = new TH2F("hPeakofInterest","tof vs X1_Y1new",40,-20,20,100,-50,50);
  
  TCanvas *c6 = new TCanvas("c6","tofX1 peak of interest",10,10,900,600);;

   Double_t tofmean=0;

   cout << "Mean value for tof" << endl;
   cin >> tofmean;
   cout << "X1posO = " << X1mean << " tofmean = " << tofmean << endl;


  if(Mg24_NoCol)
    {
      DATA->SetAlias("X1_Y1newat0",Form("X1_Y1new-%g",X1mean)); //define the X1posO of the peak of interest to 0
      DATA->SetAlias("tofat0",Form("tof-%g",tofmean));  //define the tof of the peak of interest to 0
      DATA->Draw("tofat0:X1_Y1newat0>> hPeakofInterest","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col"); 
    }
  else if(Mg24_Col)
    {
      DATA->SetAlias("X1_Y1newat0",Form("X1_Y1new-%g",X1mean)); //define the X1posO of the peak of interest to 0
      DATA->SetAlias("tofat0",Form("tof-%g",tofmean));  //define the tof of the peak of interest to 0
      DATA->Draw("tofat0:X1_Y1newat0>> hPeakofInterest","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col"); 
    }  

  hPeakofInterest->GetXaxis()->SetTitle("X1_Y1new-X1mean (mm)");
  hPeakofInterest->GetYaxis()->SetTitle("ToF-ToFmean");
  c6 -> Update();
  c6 -> Modified();


   TCanvas *c7 = new TCanvas("c7","Fit tofX1 correction",10,10,900,600);
  
   float binmin_tof=0;
   float binmax_tof=0;
   float bininter_tof=0, bindiff_tof=0, bintemp_tof=0;
   Double_t par_tofX1[3];
   Double_t b0,b1,b2;
 
   cout << "lowest bin for the fitting of tofX1" << endl;
   cin >> binmin_tof;
   cout << "highest bin for the fitting for tofX1" << endl;
   cin >> binmax_tof;
   cout << "binmin_tof = " << binmin_tof << " binmax_tof = " << binmax_tof << endl;
  
   bindiff_tof = binmax_tof-binmin_tof;

//=============== check to see the sliceX projection used for the fit ========================
/*
   for(int i=0;i<bindiff_tof-1;i++)
    {
      if(i==0) bintemp_tof=binmin_tof;
      bintemp_tof=bintemp_tof+1;
      bininter_tof=bintemp_tof+1;
      cout << bintemp_tof << " " << bininter_tof << endl;
      hPeakofInterest->ProjectionX("hPeakofInterest_px",bintemp_tof,bininter_tof,"");
      hPeakofInterest_px->Draw();
      c7->Modified();	
      c7->Update();        
      c7->WaitPrimitive();
      c7->Clear();
    }
*/
//=============================================================================================


   hPeakofInterest->FitSlicesX(0,binmin_tof,binmax_tof,0,"Q",0); //see below how the FitSlicesX works
   hPeakofInterest_1->Draw(); //histoname_1 is the histogram of the centroid parameters for each slice 
   hPeakofInterest_1->Fit("pol2");
   pol2->GetParameters(par_tofX1);
   b0=par_tofX1[0];b1=par_tofX1[1];b2=par_tofX1[2];
   cout << endl << " par0_tofX1 " << b0 <<"; par1_tofX1 " << b1 <<"; par2_tofX1 " << b2 << endl;
   hPeakofInterest_1->GetXaxis()->SetRangeUser(-50., 50.);
   hPeakofInterest_1->GetYaxis()->SetRangeUser(-20., 20.);
   c7 -> Update();
   c7 -> Modified();

 //implement lineshaping correction
   
   Double_t X1ref=0;

   cout << "X1 value for the peak that doesn't need correction" << endl;
   cin >> X1ref;

  // DATA->SetAlias("X1new",Form("X1_Y1new-(%g+(%g*(tof-%g)+(%g*pow(tof-%g,2))))",b0,b1,tofmean,b2,tofmean));
   DATA->SetAlias("X1new",Form("X1_Y1new-((%g*(tof-%g)+(%g*pow(tof-%g,2)))*(X1_Y1new-%g)/(%g))",b1,tofmean,b2,tofmean,X1ref,X1mean-X1ref));
  
   
   TH2F *htofvsX1new = new TH2F("htofvsX1new","tof vs X1new",700,100,800,100,1910,2010);
   TCanvas *c8 = new TCanvas("c8","tof vs X1 corrected matrix",10,10,900,600);

  if(Mg24_NoCol)
    {
      DATA->Draw("tof:X1new>> htofvsX1new","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col"); 
    }
  else if(Mg24_Col)
    {
      DATA->Draw("tof:X1new>> htofvsX1new","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col"); 
    }

   htofvsX1new->GetXaxis()->SetTitle("Corrected X1 position (mm)");
   htofvsX1new->GetYaxis()->SetTitle("ToF");
   c8 -> Update();
   c8 -> Modified();


   cout << " " << endl;    cout << " " << endl;    cout << " " << endl;
   cout << "----------------PARAMETERS for the Y1 & TOF CORRECTIONS TO PUT IN THE CONFIG FILE----------------" << endl;
   cout << " " << endl; 

   cout << endl << " Y1 ----> par0  " << -a0 <<"; par1 " << -a1 <<"; par2 " << -a2 << endl;
   cout << endl << " TOF ----> par0 " << -b0 <<"; par1 " << -b1 <<"; par2 " << -b2 << endl;
}

// Project slices along X in case of a 2-D histogram, then fit each slice 
// with function f1 and make a histogram for each fit parameter 
// Only bins along Y between binmin and binmax are considered. 
// if f1=0, a gaussian is assumed 
// 
//  Example: Assume a 2-d histogram h2 
//   Root > h2->FitSlicesX(); produces 4 TH1D histograms 
//          with h2_0 containing parameter 0(Constant) for a Gaus fit 
//                    of each bin in Y projected along X 
//          with h2_1 containing parameter 1(Mean) for a gaus fit 
//          with h2_2 containing parameter 2(RMS)  for a gaus fit 
//          with h2_chi2 containing the chisquare/number of degrees of freedom for a gaus fit 
// 
//   Root > h2->FitSlicesX(0,15,22,10); 
//          same as above, but only for bins 15 to 22 along Y 
//          and only for bins in Y for which the corresponding projection 
//          along X has more than cut bins filled. 
// 
 

# Analysis_scripts
# Analysis_scripts

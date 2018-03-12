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



  c1 = new TCanvas("c1","K600 Ex calibration",10,10,900,600);

  Int_t n = 5;
  Double_t x[n]  = {633.67,534.56,530.31,485.97,361.75};
  Double_t y[n]  = {6.43230,8.35798,8.43731,9.30539,11.72810}; //NNDC data MeV

  Double_t par[3];
  Double_t a0,a1,a2;

  TGraph *Ex_cal = new TGraph(n,x,y);

  Ex_cal->SetTitle("Ex_cal");
  Ex_cal->GetXaxis()->SetTitle("Position (mm)");
  Ex_cal->GetYaxis()->SetTitle("Ex (MeV)");
  Ex_cal->SetMarkerStyle(20);
  Ex_cal->SetMarkerColor(4);
  Ex_cal->Draw("AP");

  Ex_cal->Fit("pol2");
  pol2->GetParameters(par);
  a0=par[0];a1=par[1];a2=par[2];

  cout << endl << " par0  " << a0 <<"; par1 " << a1 <<"; par2 " << a2 << endl;

  TCanvas *c2 = new TCanvas("c2","Ex calibrated spectra",10,10,900,600);
  DATA->SetAlias("Ex_cal",Form("%g+%g*X1posCTOF+%g*X1posCTOF*X1posCTOF",a0,a1,a2));

  TH1F *hEx_cal = new TH1F("hEx_cal","Ex calibrated spectra",8000,4.,16.);

  if(Mg24_NoCol)
    {
      DATA->Draw("Ex_cal>>hEx_cal","Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol && X1flag==0 && U1flag==0","");
    }
  else if(Mg24_Col)
    {
      DATA->Draw("Ex_cal>>hEx_cal","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0","");
    }




}

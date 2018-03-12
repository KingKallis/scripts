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



  c1 = new TCanvas("c1","QBrho calibration",10,10,900,600);

  Int_t n = 5;
 // Double_t x[n]  = {746.558,634.11,487.087,364.114};
 Double_t x[n]  = {633.67,534.56,530.31,485.97,361.75};
 // Double_t y[n]  = {3093.8250656592,3063.2417863046,3022.6684385307,2987.9734250142}; // zero target thickness
//  Double_t y[n]  = {3093.23503895635,3062.6461639164,3022.0651813368,2987.3634400923}; // 700ug/cm2 thickness and considering the downstream value 
    Double_t y[n]  = {3062.646,3035.514,3034.391,3022.065,2987.363}; // 700ug/cm2 thickness and considering the downstream value 

  Double_t par[3];
  Double_t a0,a1,a2;

  TGraph *QBrho_cal = new TGraph(n,x,y);

  QBrho_cal->SetTitle("QBrho_cal");
  QBrho_cal->GetXaxis()->SetTitle("Position (mm)");
  QBrho_cal->GetYaxis()->SetTitle("QBrho (ekGcm)");
  QBrho_cal->SetMarkerStyle(20);
  QBrho_cal->SetMarkerColor(4);
  QBrho_cal->Draw("AP");

  QBrho_cal->Fit("pol2");
  pol2->GetParameters(par);
  a0=par[0];a1=par[1];a2=par[2];

  cout << endl << " par0  " << a0 <<"; par1 " << a1 <<"; par2 " << a2 << endl;

  TCanvas *c2 = new TCanvas("c2","QBrho calibrated spectra",10,10,900,600);
  DATA->SetAlias("QBrho",Form("%g+%g*X1posCTOF+%g*X1posCTOF*X1posCTOF",a0,a1,a2));

  TH1F *hQBrho = new TH1F("hQBrho","QBrho calibrated spectra",1200,2900.,3200.);

  if(Mg24_NoCol)
    {
      DATA->Draw("QBrho>>hQBrho","Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol && X1flag==0 && U1flag==0","");
    }
  else if(Mg24_Col)
    {
      DATA->Draw("QBrho>>hQBrho","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && X1flag==0 && U1flag==0","");
    }




}

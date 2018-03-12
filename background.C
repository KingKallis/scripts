{
  bool Mg24_NoCol = false;
  bool Mg24_Col = true;
  bool Mg26_NoCol = false;
  bool Mg26_Col = false;

 /*if(Mg24_NoCol)
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

*/


  c3 = new TCanvas("c3","Matrix ExY1",10,10,900,600);
  //Y1 vs X1 histogram
  TH2F *hY1vsX1posCTOF = new TH2F("hY1vsEx","Y1 vs Ex",1250,3.5,16,480,-60.,60.);

  if(Mg24_NoCol)
    {
      DATAch->Draw("Y1:Ex>> hY1vsEx","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol","col");
    }
  else if(Mg24_Col)
    {
      DATAch->Draw("Y1:Ex>> hY1vsEx","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col","col");
    }
  else if(Mg26_NoCol)
    {
      DATAch->Draw("Y1:Ex>> hY1vsEx","X1flag==0 && U1flag==0 && Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol","col");
    }
  else if(Mg26_Col)
    {
      DATAch->Draw("Y1:Ex>> hY1vsEx","X1flag==0 && U1flag==0 && Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col","col");
    }


  Double_t par_bkg[4], par_py[2], data_counts=0;
  c4 = new TCanvas("c4","bkg projection",10,10,900,600);

  //bkg from -35 to -25 --> bin 101 to 141
  //good data from -20 to +20 --> bin 161 to 321
  TAxis *yaxis = hY1vsX1posCTOF->GetYaxis();
  Int_t binmin_bkg = yaxis->FindBin(-35);
  Int_t binmax_bkg = yaxis->FindBin(-25);
  Int_t binmin_data = yaxis->FindBin(-20);
  Int_t binmax_data = yaxis->FindBin(20);
  cout << "binmin_bkg " << binmin_bkg << " binmax_bkg " << binmax_bkg << " binmin_data " << binmin_data << " binmax_data " << binmax_data << endl;

  //background estimation
  TH1D *px = hY1vsX1posCTOF->ProjectionX("px", binmin_bkg,binmax_bkg);
  px->Draw();
  px->Fit("pol3","R","",4.8,15);
  pol3->GetParameters(par_bkg);
  
  //calculation of the normalization factor
  TAxis *xaxis = hY1vsX1posCTOF->GetXaxis();
  Int_t binmin_nopeak = xaxis->FindBin(5.2);
  Int_t binmax_nopeak = xaxis->FindBin(5.7);
  cout << "binmin_nopeak " << binmin_nopeak << " binmax_nopeak " << binmax_nopeak << endl;
  
  c7 = new TCanvas("c7","Y1 projection",10,10,900,600);
  TH1D *py = hY1vsX1posCTOF->ProjectionY("py", binmin_nopeak, binmax_nopeak); 
  py->Draw();
//  py->Fit("pol1","R","",-34,30);
//  pol1->GetParameters(par_py);

  Double_t integral_bkg = py->Integral(binmin_bkg,binmax_bkg);
  Double_t integral_data = py->Integral(binmin_data,binmax_data);
  cout << "integral_data " << integral_data << endl;
 

  Double_t norm = integral_data/integral_bkg;
  cout << "normalization factor " << norm << endl;

  cout << endl << " par_bkg[0] " << norm*par_bkg[0] <<";  par_bkg[1] " << norm*par_bkg[1] << "; par_bkg[2] " << norm*par_bkg[2]<< "; par_bkg[3] " << norm*par_bkg[3]<< endl;
//  cout << endl << " par_py[0] " << par_py[0] <<";  par_py[1] " << par_py[1] << endl;


  c5 = new TCanvas("c5","Ex",10,10,900,600);
  TH1F *hEx_withbkg = new TH1F("hEx_withbkg","Ex spectrum with bkg",1250,3.5,16);

  if(Mg24_NoCol)
    {
      DATAch->Draw("Ex>> hEx_withbkg","X1flag==0 && U1flag==0 && Alphas_24Mg_NoCol && Cut_pad1X1_24Mg_NoCol && Y1>-20 && Y1<20","col");
    }
  else if(Mg24_Col)
    {
      DATAch->Draw("Ex>> hEx_withbkg","X1flag==0 && U1flag==0 && Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && Y1>-20 && Y1<20","col");
    }
  else if(Mg26_NoCol)
    {
      DATAch->Draw("Ex>> hEx_withbkg","X1flag==0 && U1flag==0 && Alphas_26Mg_NoCol && Cut_pad1X1_26Mg_NoCol && Y1>-20 && Y1<20","col");
    }
  else if(Mg26_Col)
    {
      DATAch->Draw("Ex>> hEx_withbkg","X1flag==0 && U1flag==0 && Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20","col");
    }

  data_counts=hEx_withbkg->GetEntries();
  cout << "data_counts" << data_counts << endl;

//subtraction of the background
  TF1  *bkg = new TF1("bkg","pol3",4,15.6);
  bkg->SetParameters(pol3->GetParameters());
  bkg->SetLineColor(4);

  TH1F *hbkg = new TH1F("hbkg","scaled bkg",1250,3.5,16);
  hbkg->Add(bkg,norm);
  hbkg->SetLineColor(6);
  hbkg->Draw("same");

 // px->Scale(norm);
 // px->SetLineColor(2);
 // px->Draw("same");  

  c6 = new TCanvas("c6","Ex",10,10,900,600); 

  TH1F *hEx_nobkg =(TH1F*)hEx_withbkg->Clone("hEx_nobkg");
  //hEx_nobkg->Add(px,-1);
  hEx_nobkg->Add(hbkg,-1);
  hEx_nobkg->SetLineColor(2);
  hEx_nobkg->Draw("");

}

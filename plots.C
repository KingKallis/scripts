{
  bool Mg24_Col = false;
  bool Mg26_Col = true;

  if(Mg24_Col)
    {
    
     c1 = new TCanvas("c1","Ex vs Egamma LaBr#1",10,10,900,600);
     TH2F *hExvsEgamma = new TH2F("hExvsEgamma","^{24}Mg(#alpha,#alpha'#gamma): Ex vs Egamma LaBr#1",1250,3.5,16,2000,0,10000);
     
     DATAch->Draw("GammaEnergy:Ex>>hExvsEgamma","Alphas_24Mg_Col && Cut_pad1X1_24Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120","colz");
      
     TLine *line = new TLine(4,4000,10,10000); //ground state decay
     line->SetLineColor(1);
     line->SetLineWidth(2);
     line->SetLineStyle(9);
     line->Draw("same");
     
     TLine *line = new TLine(3.36863,2000,11.36863,10000); //firt excited state decay
     line->SetLineColor(2);
     line->SetLineWidth(2);
     line->SetLineStyle(9);
     line->Draw("same");
     
     hExvsEgamma->SetTitle("^{24}Mg(#alpha,#alpha*#gamma): Ex vs Egamma LaBr#1");
     hExvsEgamma->SetStats(0);
     hExvsEgamma->GetXaxis()->SetTitle("E_{x} - K600 [MeV]");
     hExvsEgamma->GetXaxis()->CenterTitle(true);
     hExvsEgamma->GetYaxis()->SetTitle("E_{#gamma} - BaGeL [keV]");
     hExvsEgamma->GetYaxis()->CenterTitle(true);
     hExvsEgamma->GetXaxis()->SetLabelSize(0.025);  
     hExvsEgamma->GetYaxis()->SetLabelSize(0.025);  
     hExvsEgamma->GetXaxis()->SetTitleOffset(.95);  
     hExvsEgamma->GetYaxis()->SetTitleOffset(1.2); 

    }
  else if(Mg26_Col)
    {
    
     c1 = new TCanvas("c1","Ex vs Egamma LaBr#1",10,10,900,600);
     TH2F *hExvsEgamma = new TH2F("hExvsEgamma","^{26}Mg(#alpha,#alpha'#gamma): Ex vs Egamma LaBr#1",1250,3.5,16,1000,0,10000);
     
      DATAch->Draw("GammaEnergy:Ex>>hExvsEgamma","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120","colz");     

     TLine *line = new TLine(4,4000,10,10000); //ground state decay
     line->SetLineColor(1);
     line->SetLineWidth(2);
     line->SetLineStyle(9);
     line->Draw("same");
     
     TLine *line = new TLine(3.80868,2000,11.80868,10000); //firt excited state decay
     line->SetLineColor(2);
     line->SetLineWidth(2);
     line->SetLineStyle(9);
     line->Draw("same");
     
     TText *gslabel = new TText(7.96,8251,"decay to g.s.");
     gslabel->SetTextColor(1);
     gslabel->SetTextFont(132);
     gslabel->SetTextAngle(38);
     gslabel->SetTextSize(0.03);
     gslabel->Draw();
    
     TText *firstexlabel = new TText(9.54,7945,"decay to 1st excited");
     firstexlabel->SetTextColor(2);
     firstexlabel->SetTextFont(132);
     firstexlabel->SetTextAngle(38);
     firstexlabel->SetTextSize(0.03);
     firstexlabel->Draw();
     
     hExvsEgamma->SetTitle("");
     hExvsEgamma->SetStats(0);
     hExvsEgamma->GetXaxis()->SetTitle("E_{x} - K600 [MeV]");
     hExvsEgamma->GetXaxis()->CenterTitle(true);
     hExvsEgamma->GetXaxis()->SetTitleFont(132);
     hExvsEgamma->GetYaxis()->SetTitle("E_{#gamma} - BaGeL [keV]");
     hExvsEgamma->GetYaxis()->SetTitleFont(132);
     hExvsEgamma->GetYaxis()->CenterTitle(true);
     hExvsEgamma->GetXaxis()->SetLabelSize(0.025);  
     hExvsEgamma->GetYaxis()->SetLabelSize(0.025);  
     hExvsEgamma->GetXaxis()->SetTitleOffset(.95);  
     hExvsEgamma->GetYaxis()->SetTitleOffset(1.2);
     
     c2 = new TCanvas("c2","Ex vs Egamma LaBr#1",10,10,900,600);
     hExvsEgamma->Draw();
     
     TLine *line = new TLine(3.80868,2000,11.80868,10000); //firt excited state decay
     line->SetLineColor(2);
     line->SetLineWidth(2);
     line->SetLineStyle(9);
     line->Draw("same");
     
     TText *firstexlabel = new TText(9.54,7945,"decay to 1st excited");
     firstexlabel->SetTextColor(2);
     firstexlabel->SetTextFont(132);
     firstexlabel->SetTextAngle(38);
     firstexlabel->SetTextSize(0.03);
     firstexlabel->Draw();
     
     c4 = new TCanvas("c4","Ex vs Egamma LaBr#1",10,10,900,600);
     hExvsEgamma->Draw();
     
  //   TText *title = new TText(13,9100,"^{26}Mg(#alpha,#alpha'#gamma)");
  //   title->SetTextColor(1);
  //   title->SetTextFont(22);
  //   title->SetTextAngle(0);
  //   title->SetTextSize(0.05);
  //   title->Draw();
   
     
     TH1F *hEgamma_nogate = new TH1F("hEgamma_nogate","Egamma_nogate LaBr#1",760,2000,9600);
     TH1F *hEgamma_gateK600 = new TH1F("hEgamma_gateK600","Egamma_gateK600 LaBr#1",760,2000,9600);
     TH1F *hEgamma_gategsdecay = new TH1F("hEgamma_gategsdecay","Egamma_gategsdecay LaBr#1",760,2000,9600);
     TH1F *hEgamma_gate1stdecay = new TH1F("hEgamma_gate1stdecay","Egamma_gate1stdecay LaBr#1",760,2000,9600);
 
     TCut gsdecay = "abs(Ex*1000-GammaEnergy) < 150";
     TCut firstexdeacy = "abs(Ex*1000-GammaEnergy-1808.68) < 150";
     
     DATAch->Draw("GammaEnergy>>hEgamma_nogate","GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1","");
     DATAch->Draw("GammaEnergy>>hEgamma_gateK600","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120","");
     DATAch->Draw("GammaEnergy>>hEgamma_gategsdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && gsdecay,"");
     DATAch->Draw("GammaEnergy>>hEgamma_gate1stdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && firstexdeacy,""); 
    
     TH1F *hEx_gated = new TH1F("hEx_gated","hEx_gated K600",1250,3.5,16);
     TH1F *hEx_gategsdecay = new TH1F("hEx_gategsdecay","Ex_gategsdecay K600",1250,3.5,16);
     TH1F *hEx_gate1stdecay = new TH1F("hEx_gate1stdecay","Ex_gate1stdecay K600",1250,3.5,16);
     
     DATAch->Draw("Ex>>hEx_gated","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20","");
     DATAch->Draw("Ex>>hEx_gategsdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && gsdecay,"");
     DATAch->Draw("Ex>>hEx_gate1stdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && firstexdeacy,"");
 
   
     c3 = new TCanvas("c3","Egamma LaBr#1 - First excited decay",10,10,900,600);
     c3->Divide(2,2,0.00001,0.001,0);     
     
     c3->cd(1);     
     hEgamma_nogate->SetLineColor(1);
     hEgamma_nogate->Draw();
     hEgamma_nogate->SetTitle("BaGeL - #gamma spectrum");
     hEgamma_nogate->SetStats(0);

     gPad->SetBottomMargin(0.01);
     hEgamma_nogate->GetXaxis()->SetLabelOffset(999);
     hEgamma_nogate->GetXaxis()->SetLabelSize(0);
     hEgamma_nogate->GetYaxis()->SetTitle("Counts / 10 keV");
     hEgamma_nogate->GetYaxis()->CenterTitle(true);     
     hEgamma_nogate->GetYaxis()->SetLabelSize(0.035); 
     hEgamma_nogate->GetYaxis()->SetTitleSize(0.045);       
     hEgamma_nogate->GetYaxis()->SetTitleOffset(.95);
          
     c3->cd(2);     
     hEx_gated->SetLineColor(1);
     hEx_gated->Draw();
     hEx_gated->SetTitle("K600 - #alpha spectrum");
     hEx_gated->SetStats(0);
     hEx_gated->GetYaxis()->SetTitle("Counts / 10 keV");
     hEx_gated->GetYaxis()->CenterTitle(true);     
     hEx_gated->GetYaxis()->SetLabelSize(0.035); 
     hEx_gated->GetYaxis()->SetTitleSize(0.045);       
     hEx_gated->GetYaxis()->SetTitleOffset(1.2);
     
     gPad->SetBottomMargin(0.01);
     hEx_gated->GetXaxis()->SetLabelOffset(999);
     hEx_gated->GetXaxis()->SetLabelSize(0);
     //gPad->SetTicky(2);     
     
     c3->cd(3);
     hEgamma_gate1stdecay->SetLineColor(2);
     hEgamma_gate1stdecay->Draw();
     hEgamma_gate1stdecay->SetTitle("");
     hEgamma_gate1stdecay->GetXaxis()->SetTitle("E_{#gamma} [keV]");
     hEgamma_gate1stdecay->GetXaxis()->CenterTitle(true);
     hEgamma_gate1stdecay->GetXaxis()->SetTitleFont(132);
     hEgamma_gate1stdecay->GetXaxis()->SetLabelSize(0.025);
     hEgamma_gate1stdecay->GetXaxis()->SetLabelSize(0.035); 
     hEgamma_gate1stdecay->GetXaxis()->SetTitleSize(0.045);
     hEgamma_gate1stdecay->GetXaxis()->SetTitleOffset(.95);
     hEgamma_gate1stdecay->GetYaxis()->SetTitle("Counts / 10 keV");
     hEgamma_gate1stdecay->GetYaxis()->CenterTitle(true);
     hEgamma_gate1stdecay->GetYaxis()->SetLabelSize(0.035); 
     hEgamma_gate1stdecay->GetYaxis()->SetTitleSize(0.045);       
     hEgamma_gate1stdecay->GetYaxis()->SetTitleOffset(.95);     
     hEgamma_gate1stdecay->SetStats(0);
     gPad->SetTopMargin(0.001);  
     
     c3->cd(4);
     hEx_gate1stdecay->SetLineColor(4);
     hEx_gate1stdecay->Draw();
     hEx_gate1stdecay->SetTitle("");
     hEx_gate1stdecay->GetXaxis()->SetTitle("E_{x} [MeV]");
     hEx_gate1stdecay->GetXaxis()->CenterTitle(true);
     hEx_gate1stdecay->GetXaxis()->SetTitleFont(132);
     hEx_gate1stdecay->GetXaxis()->SetLabelSize(0.035); 
     hEx_gate1stdecay->GetXaxis()->SetTitleSize(0.045);
     hEx_gate1stdecay->GetXaxis()->SetTitleOffset(.95);
     hEx_gate1stdecay->GetYaxis()->SetTitle("Counts / 10 keV");
     hEx_gate1stdecay->GetYaxis()->CenterTitle(true);     
     hEx_gate1stdecay->GetYaxis()->SetLabelSize(0.035); 
     hEx_gate1stdecay->GetYaxis()->SetTitleSize(0.045);       
     hEx_gate1stdecay->GetYaxis()->SetTitleOffset(.95);
     hEx_gate1stdecay->SetStats(0);
          
     gPad->SetTopMargin(0);

          
   //  hEgamma_nogate->SetLineColor(1);
   //  hEgamma_gateK600->SetLineColor(4);
   //  hEgamma_gategsdecay->SetLineColor(2);
  //   hEgamma_nogate->Draw("");
    // hEgamma_gateK600->Draw("same");
    // hEgamma_gategsdecay->Draw("same");
    
    // c3 = new TCanvas("c3","Egamma LaBr#1 - First excited decay",10,10,900,600);
     
     


     
     
   /*  
     c5 = new TCanvas("c5","Ex K600 - First excited decay",10,10,900,600);
     TH1F *hEx_gated = new TH1F("hEx_gated","hEx_gated K600",1250,3.5,16);
     TH1F *hEx_gategsdecay = new TH1F("hEx_gategsdecay","Ex_gategsdecay K600",1250,3.5,16);
     TH1F *hEx_gate1stdecay = new TH1F("hEx_gate1stdecay","Ex_gate1stdecay K600",1250,3.5,16);
     
     DATAch->Draw("Ex>>hEx_gated","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20","");
     DATAch->Draw("Ex>>hEx_gategsdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && gsdecay,"");
     DATAch->Draw("Ex>>hEx_gate1stdecay","Alphas_26Mg_Col && Cut_pad1X1_26Mg_Col && Y1>-20 && Y1<20 && GammaDetectorType==\"Scintillator\" && GammaDetectorLabel==1 && GammaTime>5040 && GammaTime<5120" && firstexdeacy,"");
     
   //  hEgamma_nogate->SetLineColor(1);
  //   hEgamma_gateK600->SetLineColor(4);
   //  hEgamma_gategsdecay->SetLineColor(2);
  //   hEgamma_nogate->Draw("");
   //  hEgamma_gateK600->Draw("same");
  //   hEgamma_gategsdecay->Draw("same");
    
    // c5 = new TCanvas("c5","Ex K600 - First excited decay",10,10,900,600);
     
     hEx_gated->SetLineColor(4);
     hEx_gate1stdecay->Scale(1000);
     hEx_gate1stdecay->SetLineColor(2);
     hEx_gated->Draw("");
     hEx_gate1stdecay->Draw("same");
     */
    }


}

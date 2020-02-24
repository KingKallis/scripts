{

  TH1F *htest = (TH1F*)h2->Clone("htest");

  Int_t nbins = h2->GetNbinsX();
  Double_t counts[nbins];

  for(Int_t i=0;i<nbins;i++) {
	counts[i]=h2->GetBinContent(i);
  }


  for(Int_t j = 0; j < nbins; j++) {
	htest->SetBinContent(j,counts[j]-310);
  }
  htest->Scale(0.06);


  h->Draw("col");
  htest->Draw("same");  



}

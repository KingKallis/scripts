{
  //PR170, pt, analysis group 2 & 3
  //Int_t run_no[]={21352,21348,21349,21350,21351,21353,21359,21360,21361,21363,21364,21366,21368,21369,21370,21371,21373,21374,21375,21376,21381,21382,21383,21392,21393,21394,21395};

  //PR170, pt, analysis group 4
  //Int_t run_no[]={21407,21408};

  //PR170, pt, analysis group 5
  //Int_t run_no[]={21441,21442};

  //PR170, pt, analysis group 6
  //Int_t run_no[]={21445,21444,21446,21447,21448,21449,21450,21451,21452,21453,21455,21456,21457,21458,21462,21463,21467,21468,21469,21470,21471};

  //PR170, pt, analysis group 7
  Int_t run_no[]={29174,29173,29172,29177,29178,29179,29180,29181,29182,29183,29184,29185,29201,29202,29210,29211,29212,29213,29214,29215,29216,29217,29219,29220,29221,29223,29224,29235,29242,29243,29244,29245,29246,29247,29248,29249,29250,29251,29252,29253,29254,29257,29258,29259,29260,29276};

  Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);  


  //TF1 *fit = new TF1("fit","gaus(0) + pol1(3)",1,800);
  char name[128];
  Double_t a0,a1,a2,a3,a4,norm;
  Double_t width = 5.;
  Double_t par[5];
  Float_t peakposition[nrofruns];
  Float_t sigma[nrofruns];
  Float_t peakposition2[nrofruns];

  TCut CUTbasicA = "tof>6290 && tof<6390 && pad1>400 && pad1<850 && pad2>200 && pad2<1000";
  TCut CUTlimitsA = "X1flag==0 && X1pos>-100 && U1flag==0 && U1pos>-100 && X2flag==0 && X2pos>-100 && abs(thetaSCAT)<2.2";
  TCut CUTbasic = "tof>6400 && tof<6520 && pad1>360 && pad1<850 && pad2>200 && pad2<1000";     
  TCut CUTlimits = "X1flag==0 && X1pos>-100 && U2flag==0 && U2pos>-100 && X2flag==0 && X2pos>-100";

  for(Int_t i=0;i<nrofruns;i++)	{
	  sprintf(name,"/FAST/run%5d.root",run_no[i]);
          cout << name << endl;
	  TFile *_file0 = TFile::Open(name);     
  	  TH1F *hX1pos = new TH1F("hX1pos","X1 Position",200,100.,200.);
  	  //TH1F *hX1pos = new TH1F("hX1pos","X1 Position",800,0.,800.);

          DATA->Draw("X1posC>>hX1pos",CUTbasic && CUTlimits,"");
          //if(i==0)	DATA->Draw("X1pos>>hX1pos",CUTbasicA && CUTlimitsA,"");
          //else	DATA->Draw("X1pos>>hX1pos",CUTbasicA && CUTlimitsA,"");

/*	  norm = hX1pos->Integral(3000,3300);
	  norm=norm/300.;
          cout << "norm" << norm << endl;
	  fit->SetParameters(1.*norm,592.,1.,norm,0.);
	  fit->SetParLimits(0,0,1e9);                          */

	  //hX1pos->Fit("gaus","R","",130,140);       // 
	  if(i<45)	hX1pos->Fit("gaus","R","",130,139);       // 
	  else  	hX1pos->Fit("gaus","R","",120,130);     // before run 21373

//	  fit->GetParameters(par);
	  gaus->GetParameters(par);
	  //a0=par[0];a1=par[1];a2=par[2];a3=par[3];
          //cout << endl << " par0 " << a0 <<"; par1 " << a1 <<"; par2 " << a2 << "; par3 "<< a3 << "; par4 "<< a4<< endl << endl;
          peakposition[i] = par[1];
          sigma[i] = par[2];
	  c1->Modified(); c1->Update();
	  c1->WaitPrimitive(); 
	  //========================================================================


	  if(i==0)	hX1pos->Fit("gaus","R","",278.,286);       // 
	  else  	hX1pos->Fit("gaus","R","",278.,286);     // before run 21373
	  //else  	hX1pos->Fit("gaus","R","",288,293);       // runs 21373 - 21483
	  //else if(i<6)  hX1pos->Fit("gaus","R","",228,232);     // runs 21407 - 21443
	  //else  	hX1pos->Fit("gaus","R","",320,327.5);       // runs 21444 - 29000
	  //else  	hX1pos->Fit("gaus","R","",208,212);       // runs 29172 -

	  gaus->GetParameters(par);
          peakposition2[i] = par[1];
	  //c1->Modified(); c1->Update();
	  //c1->WaitPrimitive(); 

  }
  for(Int_t i=0;i<nrofruns;i++)	{
     cout << " "<< run_no[i] <<" "<< peakposition[i] <<" "<< sigma[i] << endl;
  }
  for(Int_t i=0;i<nrofruns;i++)	{
     cout << ""<< run_no[i] <<"  Difference compared with run "<<run_no[0] <<"  "<< peakposition[i]-peakposition[0] << "  and peakdif = " << peakposition[i] - peakposition2[i] << endl;
  } 
  for(Int_t i=0;i<nrofruns;i++)	{
     cout << "        case "<< run_no[i] <<": x1offset="<< peakposition[i]-peakposition[0] <<"\; printf(\"run %d: x1 offset= %f \\n\",RunNumber,x1offset); break;   "<< endl;
  }



}





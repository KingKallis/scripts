{

#include <math.h>
#include <stdlib.h>     /* abs */

  char name[128];
  int nrofpeaks=14;   
  int firstpeak=0;   

/*
  for(Int_t i=firstpeak;i<nrofpeaks;i++){
     sprintf(name,"t%i->Delete()",i);
     gROOT->ProcessLine(name); 
     cout<<name<<endl;
  }
  all->Delete();
//  bkgY->Delete();
*/

  Double_t pi=3.14159265359;
  Double_t binsperMeV=100;	// for determiniation of nr of counts in peak
  Double_t low=4.;
  Double_t hi=13.;
  Double_t rangelo[100],rangehi[100],centroid[100],sigma[100];
  Double_t parfit[100], peakcounts[100];

  for(Int_t i=0;i<100;i++){
    parfit[i]=0.0;
  }  

//--------------------------------------------------------------------------------------------------------
// Information for all the states in 24Mg; natural parity states 
 /* rangelo[0]=3.8;     rangehi[0]=4.5 ;   centroid[0]= 4.122889;   sigma[0]= sqrt(.080**2)/2.35;
  rangelo[1]=4;  rangehi[1]=4.5 ;   centroid[1]= 4.23824;   sigma[1]= sqrt(.080**2)/2.35;
  rangelo[2]=5.8;    rangehi[2]=6.2 ;   centroid[2]=  6.01084;   sigma[2]= sqrt(.080**2)/2.35;
  rangelo[3]=6.2;   rangehi[3]=6.8;  centroid[3]=  6.43230;   sigma[3]= sqrt(.080**2)/2.35;
  rangelo[4]=7.2;    rangehi[4]=7.5 ;   centroid[4]= 7.34900;   sigma[4]= sqrt(.080**2)/2.35;
  rangelo[5]=7.4;    rangehi[5]=8 ;   centroid[5]=  7.55504;   sigma[5]= sqrt(.080**2)/2.35;
  rangelo[6]=7.4;    rangehi[6]=8 ;   centroid[6]=  7.61647;   sigma[6]= sqrt(.080**2)/2.35;
  rangelo[7]=7.8;    rangehi[7]=8.4 ;   centroid[7]=   8.1142;   sigma[7]= sqrt(.080**2)/2.35;
  rangelo[8]=8.0;    rangehi[8]=8.7 ;   centroid[8]=  8.35798;   sigma[8]= sqrt(.080**2)/2.35;
  rangelo[9]=7.4;    rangehi[9]=8 ;   centroid[9]=  8.43731;   sigma[9]= sqrt(.080**2)/2.35;
  rangelo[10]=8.1;    rangehi[10]=8.7 ;   centroid[10]=   8.43936;   sigma[10]= sqrt(.080**2)/2.35;
  rangelo[11]=8.3;    rangehi[11]=8.9 ;   centroid[11]=  8.65453;   sigma[11]= sqrt(.080**2)/2.35;
 
  rangelo[12]=8.9;    rangehi[12]=9.1 ;   centroid[12]=   9.00334;   sigma[12]= sqrt(.080**2)/2.35;
  rangelo[13]=9.1;    rangehi[13]=9.25 ;   centroid[13]=   9.14599;   sigma[13]= sqrt(.080**2)/2.35;
  rangelo[14]=9.25;    rangehi[14]=9.45 ;   centroid[14]=  9.30539;   sigma[14]= sqrt(.080**2)/2.35;
  rangelo[15]=9.45;    rangehi[15]=9.65 ;   centroid[15]=   9.53248;   sigma[15]= sqrt(.080**2)/2.35;
  rangelo[16]=10.0;    rangehi[16]=10.1 ;   centroid[16]=   10.05854;   sigma[16]= sqrt(.080**2)/2.35;
  rangelo[17]=10.1;    rangehi[17]=10.25 ;   centroid[17]=   10.161;   sigma[17]= sqrt(.080**2)/2.35;
  rangelo[18]=10.25;    rangehi[18]=10.5 ;   centroid[18]=   10.36051;   sigma[18]= sqrt(.080**2)/2.35;
  rangelo[19]=10.3;    rangehi[19]=10.8 ;   centroid[19]=   10576.02;   sigma[19]= sqrt(.080**2)/2.35;
  rangelo[20]=10.5;    rangehi[20]=10.65 ;   centroid[20]=    10.58131;   sigma[20]= sqrt(.080**2)/2.35;
  rangelo[21]=10.5;    rangehi[21]=10.65 ;   centroid[21]=   10.65958;   sigma[21]= sqrt(.080**2)/2.35;
  rangelo[22]=10.63;    rangehi[22]=10.82 ;   centroid[22]=   10.6797;   sigma[22]= sqrt(.080**2)/2.35;

  rangelo[0]=8.9;     rangehi[0]=9.1 ;      centroid[0]=   9.00334;     sigma[0]= sqrt(.080**2)/2.35;
  rangelo[1]=9.1;     rangehi[1]=9.25 ;     centroid[1]=   9.14599;     sigma[1]= sqrt(.080**2)/2.35;
  rangelo[2]=9.25;    rangehi[2]=9.45 ;     centroid[2]=  9.30539;      sigma[2]= sqrt(.080**2)/2.35;
  rangelo[3]=9.45;    rangehi[3]=9.65 ;     centroid[3]=   9.53248;     sigma[3]= sqrt(.080**2)/2.35;
  rangelo[4]=10.0;    rangehi[4]=10.1 ;     centroid[4]=   10.05854;    sigma[4]= sqrt(.080**2)/2.35;
  rangelo[5]=10.1;    rangehi[5]=10.25 ;    centroid[5]=   10.161;      sigma[5]= sqrt(.080**2)/2.35;
  rangelo[6]=10.25;   rangehi[6]=10.5 ;     centroid[6]=   10.36051;    sigma[6]= sqrt(.080**2)/2.35;
  rangelo[7]=10.3;    rangehi[7]=10.8 ;     centroid[7]=   10576.02;    sigma[7]= sqrt(.080**2)/2.35;
  rangelo[8]=10.55;    rangehi[8]=10.7 ;    centroid[8]=    10.58131;   sigma[8]= sqrt(.080**2)/2.35;
  rangelo[9]=10.60;    rangehi[9]=10.8 ;    centroid[9]=   10.65958;    sigma[9]= sqrt(.080**2)/2.35;
  rangelo[10]=10.65;  rangehi[10]=10.80 ;   centroid[10]=   10.6797;    sigma[10]= sqrt(.080**2)/2.35;
  rangelo[11]=10.66;  rangehi[11]=10.82 ;   centroid[11]=   10.73079;    sigma[11]= sqrt(.080**2)/2.35; 
*/

  rangelo[0]=4.1;    rangehi[0]=4.3 ;     centroid[0]= 4.23824;     sigma[0]= sqrt(.080**2)/2.35;
  rangelo[1]=5.9;    rangehi[1]=6.1 ;     centroid[1]= 6.01084;     sigma[1]= sqrt(.080**2)/2.35;
  rangelo[2]=6.3;    rangehi[2]=6.5;      centroid[2]= 6.43230;     sigma[2]= sqrt(.080**2)/2.35;
  rangelo[3]=7.25;   rangehi[3]=7.45 ;    centroid[3]=  7.34900;    sigma[3]= sqrt(.080**2)/2.35;
  rangelo[4]=7.45;   rangehi[4]=65 ;      centroid[4]= 7.55504;     sigma[4]= sqrt(.080**2)/2.35;
  rangelo[5]=7.5;    rangehi[5]=7.7 ;     centroid[5]= 7.61647;     sigma[5]= sqrt(.080**2)/2.35;
  rangelo[6]=7.55;   rangehi[6]=7.75 ;    centroid[6]= 7.6542;      sigma[6]= sqrt(.080**2)/2.35;
  rangelo[7]=8.25;   rangehi[7]=8.45 ;    centroid[7]= 8.35798;     sigma[7]= sqrt(.080**2)/2.35;
  rangelo[8]=8.33;   rangehi[8]=8.53 ;    centroid[8]= 8.43731;     sigma[8]= sqrt(.080**2)/2.35;
  rangelo[9]=9.5;    rangehi[9]=9.25 ;    centroid[9]= 9.14599;     sigma[9]= sqrt(.080**2)/2.35;
  rangelo[10]=9.20;  rangehi[10]=9.40 ;   centroid[10]= 9.30539;    sigma[10]= sqrt(.080**2)/2.35;
  rangelo[11]=10.57; rangehi[11]=10.77 ;  centroid[11]= 10.6797;    sigma[11]= sqrt(.080**2)/2.35;
  rangelo[12]=11.62; rangehi[12]=11.82 ;  centroid[12]= 11.7281;    sigma[12]= sqrt(.080**2)/2.35;
  rangelo[13]=10.76; rangehi[13]=10.96 ;  centroid[13]=11.8649;     sigma[13]= sqrt(.080**2)/2.35;

//------------------------------------------------------------------------------------------
// Define peaks, plus the polynomial background
//
  for(Int_t i=firstpeak;i<nrofpeaks;i++){
     sprintf(name,"TF1 *t%i = new TF1(\"t%i\",\"gaus\",rangelo[%i],rangehi[%i]);",i,i,i,i);
     gROOT->ProcessLine(name); 
     //cout<<name<<endl;

     sprintf(name,"t%i->SetParameters(10000,centroid[%i],sigma[%i]);",i,i,i);
     gROOT->ProcessLine(name); 
     //cout<<name<<endl;
  }

//background extracted from Y1

  /*  TF1 *bkgY = new TF1("bkgY","([0]+[1]*x+[2]*x*x+[3]*x*x*x)",low,hi);

    bkgY->FixParameter(0,257.642); // norm 3.18
    bkgY->FixParameter(1,-47.7399);
    bkgY->FixParameter(2,3.52365);
    bkgY->FixParameter(3,-0.0864849);
*/

//------------------------------------------------------------------------------------------
// Add all the peaks in one function and fit that function
//


 // TF1 *all = new TF1("all","t3+bkgY",low,hi);
//  TF1 *all = new TF1("all","t0+t1+t2+t3+t4+t5+t6+t7+t8+t9+t10+t11+t12+t13+t14+t15+t16+t17+t18+bkgY",low,hi);
  TF1 *all = new TF1("all","t0+t1+t2+t3+t4+t5+t6+t7+t8+t9+t10+t11+t12+t13",low,hi);
// TF1 *all = new TF1("all","t12+t13+t14+t15+t16+t17+t18+t19+t20+t21+t22",low,hi);
  for(Int_t i=firstpeak;i<nrofpeaks;i++){
 
     sprintf(name,"all->SetParLimits(0+3*%i,0,100000);",i);
     gROOT->ProcessLine(name);  //cout<<name<<endl;
     sprintf(name,"all->SetParLimits(2+3*%i,0.7*sigma[%i],1.3*sigma[%i]);",i,i,i);  // if width not fixed, limit it
     gROOT->ProcessLine(name);  //cout<<name<<endl;
     sprintf(name,"all->SetParLimits(1+3*%i,centroid[%i]-0.08,centroid[%i]+0.08);",i,i,i);  // if position is fixed, limit it
     gROOT->ProcessLine(name);  //cout<<name<<endl;

  }

 // hEx->Fit("all","VRB+","",low,hi);
 // hEx_nobkg->Fit("all","VRB+","",low,hi);
    hEx_cal->Fit("all","VRB+","",low,hi);


//------------------------------------------------------------------------------------------
// get parameters of individual peaks from fit 
//
  all->GetParameters(parfit);
  for(Int_t i=firstpeak;i<nrofpeaks;i++){
     peakcounts[i]=parfit[0+i*3]*fabs(parfit[2+i*3])*sqrt(2*pi)*binsperMeV ; 

     cout << endl << "peak #"<< i+1 << ": position = " << parfit[3*i+1] <<" MeV     FWHM = " << 1000*2.35*parfit[3*i+2] << " kev   peak counts ="<< peakcounts[i]  << "   (NNDC: "<< centroid[i] <<" MeV ;  "<< 1000*2.35*sigma[i] <<" keV ) "
<< endl;
     cout << " --------------> NNDC-peak centroid = "<< (parfit[3*i+1]-centroid[i])*1000 << " keV " << endl;

  }

//------------------------------------------------------------------------------------------
// now plot the individual peaks 
//
  for(Int_t i=firstpeak;i<nrofpeaks;i++){
     sprintf(name,"t%i->SetParameters(parfit[0+3*%i],parfit[1+3*%i],parfit[2+3*%i])",i,i,i,i);
     gROOT->ProcessLine(name); //cout<<name<<endl;
     sprintf(name,"t%i->SetLineColor(%i+40)",i,i);
     gROOT->ProcessLine(name); //cout<<name<<endl;
     sprintf(name,"t%i->SetLineStyle(7)",i);
     gROOT->ProcessLine(name); //cout<<name<<endl;
     sprintf(name,"t%i->Draw(\"same\")",i);
     gROOT->ProcessLine(name); //cout<<name<<endl;
  }


 /* bkgY->SetLineStyle(7);
  bkgY->SetLineColor(4);
  bkgY->Draw("same");
*/

  cout<< " chi sq = "<<  all->GetChisquare() << "  Nr of Degr Of Freedom = "<<  all->GetNDF() <<endl;
  cout<< " reduced chisq = "<<  all->GetChisquare()/all->GetNDF() <<endl;

}



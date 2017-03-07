{
int filenum = 2083;
int minchannel = 0;
int maxchannel = 31;
//int minchannel = 32;
//int maxchannel = 33;
//int minchannel = 48;
//int maxchannel = 49;


char buffer[256];
sprintf(buffer,"../sortedfiles/sorted0%d.root",filenum);

  TFile *fin = TFile::Open(buffer);
  TTree *trin = (TTree*)fin->FindObjectAny("DATA");

  for(int i=minchannel;i<=maxchannel;i++)
//  for(int i=32;i<34;i++)
//  for(int i=48;i<50;i++)
    {
      char buffer[256];
      
      //TFile *fout = new TFile(buffer,"RECREATE");
      sprintf(buffer,"ADCValues[%d]>>hADC(4096,0,4096)",i);
      trin->Draw(buffer,"","");
      TH1F *hADC = gROOT->FindObjectAny("hADC");
      sprintf(buffer,"CalibFiles/h%dADC_%d.root",filenum,i);
      hADC->SaveAs(buffer);
    }
}

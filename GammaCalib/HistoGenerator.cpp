{
int filenum = 509;
//int minchannel = 0;
//int maxchannel = 31;
//int minchannel = 32;
//int maxchannel = 33;
int minchannel = 32;
int maxchannel = 79;

/*
char filename[256];
sprintf(filename,"sorted00%d.root",filenum);

  TFile *fin = TFile::Open(filename);
  TTree *trin = (TTree*)fin->FindObjectAny("DATA");
*/

 // TTree *trin = gROOT->FindObjectAny("DATAch");

  for(int i=minchannel;i<=maxchannel;i++)
//  for(int i=32;i<34;i++)
//  for(int i=48;i<50;i++)
    {
      char ADCbuffer[256];
      
      //TFile *fout = new TFile(buffer,"RECREATE");
      sprintf(ADCbuffer,"ADCValues[%d]>>hADC(4096,0,4096)",i);
      DATAch->Draw(ADCbuffer,"","");

      TH1F *hADC = gROOT->FindObjectAny("hADC");
      sprintf(ADCbuffer,"PR283_Calib/hADC_%d.root",i);
      hADC->SaveAs(ADCbuffer);
    }
}

#include <TString.h>
#include <stdio.h>
#include <stdlib.h>
#include <TCutG.h>


void simulC()
{
   TFile *sim = new TFile("Simul_DCE_C.root","RECREATE"); 
   TTree *t = new TTree("tree","Matrice diretta simulata");
   Long64_t nlines = t->ReadFile("DCE_simulation_irene/Simul_DCE_C.out","xf:tf:yf:phf:phi:tof:lp:xi:ti:yi:zi:ef:dc:d:ec:e:u:v");
   
   printf(" found %lld points\n",nlines);
    
   t->Write();
   sim->Close();
}

void simulSe()
{
   TFile *sim = new TFile("Simul_DCE_Se.root","RECREATE"); 
   TTree *t = new TTree("tree","Matrice diretta simulata");
   Long64_t nlines = t->ReadFile("DCE_simulation_irene/simul.out","xf:tf:yf:phf:phi:tof:lp:xi:ti:yi:zi:ef:dc:d:ec:e:u:v");
   
   printf(" found %lld points\n",nlines);
    
   t->Write();
   sim->Close();
}

void xfocs()
{
  simulSe();
  simulC();
      TFile *simSe = new TFile("Simul_DCE_Se.root"); 
      TFile *simC = new TFile("Simul_DCE_C.root");
	TTree *treeSe = (TTree *)simSe->Get("tree"); 

	TFile *a = new TFile("../numen8_light0068o_red.root"); //all_runs numen8_light0068a_red
	TFile *fondo = new TFile("../background_C_new_rec.root"); //all_runs

	TTree *mxx = (TTree *)a->Get("mx");
	TTree *mxx_fondo = (TTree *)fondo->Get("mx");

	Double_t eresid, det_cor, xfoc2, nrun, si_num, xf_fit, tefoc;

	
	TFile *cut = new TFile("../PID/cuts_DCE.root"); 


   

	TCutG *y12 = (TCutG*)cut->Get("y12");
	TCutG *y34 = (TCutG*)cut->Get("y34");
	TCutG *y56 = (TCutG*)cut->Get("y56");

	TCutG *sig12 = (TCutG*)cut->Get("sig12");
	TCutG *sig34 = (TCutG*)cut->Get("sig34");
	TCutG *sig56 = (TCutG*)cut->Get("sig56");


	TCut yclean = "y12&&y34&&y56"; 
	TCut sigclean = "sig12&&sig34&&sig56"; 

	//gStyle->SetStatOpt(0);
/*	TCanvas *c1 = new TCanvas("c1","Identified events",1000,600);
	c1->Divide(3,2);
	c1->cd(1);
	mxx->SetMarkerStyle(7);
	mxx->SetMarkerColor(1);
	mxx->Draw("xfoc:eresid","si_num==23");
	mxx->SetMarkerStyle(7);
	mxx->SetMarkerColor(2);
	//mxx->Draw("xfoc:eresid",sigclean&&"si_num==23", "same");

	mxx->SetMarkerColor(1);
	c1->cd(2);
	mxx->Draw("xfoc2:eresid","si_num==23");
	mxx->SetMarkerColor(2);
	//mxx->Draw("xfoc2:eresid",sigclean&&"si_num==23", "same");

	mxx->SetMarkerColor(1);
	c1->cd(3);
	mxx->Draw("xfoc3:eresid","si_num==23");
	mxx->SetMarkerColor(2);
	//mxx->Draw("xfoc3:eresid",sigclean&&"si_num==23", "same");

	mxx->SetMarkerColor(1);
	c1->cd(4);
	mxx->Draw("xfoc4:eresid","si_num==23");
	mxx->SetMarkerColor(2);
        //mxx->Draw("xfoc4:eresid",sigclean&&"si_num==23", "same");

	mxx->SetMarkerColor(1);
	c1->cd(5);
	mxx->Draw("xfoc5:eresid","si_num==23");
	mxx->SetMarkerColor(2);
	//mxx->Draw("xfoc5:eresid",sigclean&&"si_num==23", "same");

	mxx->SetMarkerColor(1);
	c1->cd(6);
	mxx->Draw("xfoc6:eresid","si_num==23");
	mxx->SetMarkerColor(2);
	//mxx->Draw("xfoc6:eresid",sigclean&&"si_num==23", "same");
	mxx->SetMarkerColor(1);


	TCanvas *c2 = new TCanvas("c2","Identified events",1500,500);
	c2->Divide(3,1);
	c2->cd(1);
	TH2D *de13 = new TH2D("de13","de1_cor vs de3_cor", 100., 600., 1200., 100., 600., 1400.);
	mxx->Project("de13","de1_cor:de3_cor","");
	de13->Draw("colz");
	de13->GetXaxis()->SetTitle("#DeltaE_{3}^{cor} [ch]");
	de13->GetYaxis()->SetTitle("#DeltaE_{1}^{cor} [ch]");
	de13->GetYaxis()->SetTitleOffset(1.5);

	c2->cd(2);
	TH2D *de25 = new TH2D("de25","de2_cor vs de5_cor", 100., 400., 1100., 100., 500., 1100.);
	mxx->Project("de25","de2_cor:de5_cor","");
	de25->Draw("colz");
	de25->GetXaxis()->SetTitle("#DeltaE_{5}^{cor} [ch]");
	de25->GetYaxis()->SetTitle("#DeltaE_{2}^{cor} [ch]");
	de25->GetYaxis()->SetTitleOffset(1.5);


	c2->cd(3);
	TH2D *de46 = new TH2D("de46","de4_cor vs de6_cor", 100., 600., 1400., 100., 600., 1300.);
	mxx->Project("de46","de4_cor:de6_cor","");
	de46->Draw("colz");
	de46->GetXaxis()->SetTitle("#DeltaE_{6}^{cor} [ch]");
	de46->GetYaxis()->SetTitle("#DeltaE_{4}^{cor} [ch]");
	de46->GetYaxis()->SetTitleOffset(1.5);

	TCanvas *c3 = new TCanvas("c3","tac:xf_fit ",800,800);
	c3->Divide(2,2);
	c3->cd(1);
	mxx->Draw("xf_fit:tac*80/4096","si_num==35&&nrun>186","");
	c3->cd(4);
	mxx->Draw("tefoc:tac*80/4096","si_num==35&&nrun>186","");
	c3->cd(2);
	mxx->Draw("eresid:tac*80/4096","si_num==35&&nrun>186","");
	c3->cd(3);
	mxx->Draw("tac*80/4096","si_num==35&&nrun>186","");

	TCanvas *c4 = new TCanvas("c4","tefoc:xf_fit ",1200,900);
	mxx->SetMarkerStyle(7);
	mxx->SetMarkerColor(1);
	mxx->Draw("tefoc:xf_fit","","");
	mxx->SetMarkerColor(2);
	mxx->Draw("tefoc:xf_fit",""&&sigclean,"same");
	mxx->SetMarkerStyle(3);
	mxx->SetMarkerColor(2);
	//	mxx->Draw("tefoc:xf_fit",!(sigclean),"");


	TCanvas *c5 = new TCanvas("c5","xf_fit ",900,900);
	TH1D *h_x = new TH1D("h_x", "xf_fit (tefoc>1.015&&tefoc<1.045)", 400, -0.6, 0. );
	mxx->Project("h_x", "xf_fit","tefoc>1.015&&tefoc<1.045"&&sigclean&&yclean,"");
	h_x->Draw();
	h_x->GetXaxis()->SetTitle("xf_fit [m]");
	mxx->SetMarkerColor(2);
//	mxx->Draw("tefoc:xf_fit",sigclean&&yclean,"same");





*/
	TCanvas *c6 = new TCanvas("c6","sigmas",1500,500);
	c6->Divide(3,1);
	c6->cd(1);
	TH2D *sig13 = new TH2D("sig13","sig1 vs sig3", 250., 0., 5., 250., 0., 5.);
	mxx->Project("sig13","sig1:sig3","nrun>100");
	sig13->Draw("colz");
	sig13->GetXaxis()->SetTitle("#sigma 3 ");
	sig13->GetYaxis()->SetTitle("#sigma 1");
	sig13->GetYaxis()->SetTitleOffset(1.5);

	c6->cd(2);
	TH2D *sig25 = new TH2D("sig25","sig2 vs sig5", 250., 0., 5., 250., 0., 5.);
	mxx->Project("sig25","sig2:sig5","nrun>100");
	sig25->Draw("colz");
	sig25->GetXaxis()->SetTitle("#sigma 5");
	sig25->GetYaxis()->SetTitle("#sigma 2");
	sig25->GetYaxis()->SetTitleOffset(1.5);


	c6->cd(3);
	TH2D *sig46 = new TH2D("sig46","sig4 vs sig6", 250., 0., 5., 250., 0., 5.);
	mxx->Project("sig46","sig4:sig6","nrun>100");
	sig46->Draw("colz");
	sig46->GetXaxis()->SetTitle("#sigma 6");
	sig46->GetYaxis()->SetTitle("#sigma 4");
	sig46->GetYaxis()->SetTitleOffset(1.5);



	TCanvas *c7 = new TCanvas("c7","sigma thresholds",1500,1000);
	c7->Divide(3,2);
	c7->cd(1);
	mxx->Draw("denom1/de_cd1","","");
	TLine *t1 = new TLine (0.4, 0., 0.4, 7450.);
	t1->Draw();
	t1->SetLineColor(2);
	t1->SetLineWidth(2);


	c7->cd(2);
	mxx->Draw("denom2/de_cd2","","");
	TLine *t2 = new TLine (0.2, 0., 0.2, 8000.);
	t2->Draw();
	t2->SetLineColor(2);
	t2->SetLineWidth(2);



	c7->cd(3);
	mxx->Draw("denom3/de_cd3","","");
	TLine *t3 = new TLine (0.4, 0., 0.4, 5100.);
	t3->Draw();
	t3->SetLineColor(2);
	t3->SetLineWidth(2);



	c7->cd(4);
	mxx->Draw("denom4/de_cd4","","");
	TLine *t4 = new TLine (0.4, 0., 0.4, 10500.);
	t4->Draw();
	t4->SetLineColor(2);
	t4->SetLineWidth(2);



	c7->cd(5);
	mxx->Draw("denom5/de_cd5","","");
	TLine *t5 = new TLine (0.2, 0., 0.2, 8500.);
	t5->Draw();
	t5->SetLineColor(2);
	t5->SetLineWidth(2);



	c7->cd(6);
	mxx->Draw("denom6/de_cd6","","");
	TLine *t6 = new TLine (0.4, 0., 0.4, 11000.);
	t6->Draw();
	t6->SetLineColor(2);
	t6->SetLineWidth(2);

	TCanvas *c8 = new TCanvas("c8","yf_fit:xf_fit with PID for 18Ne",800,600);	
	c8->cd();
	mxx->SetMarkerColor(1);
	mxx->SetMarkerStyle(7);
	mxx->Draw("tefoc:xf_fit","abs(yf_fit)<0.01"&&sigclean&&yclean);

	TCanvas *c9 = new TCanvas("c9","yf_fit:xf_fit with PID for 18Ne",800,600);	
	c8->cd();
	mxx->SetMarkerColor(1);
	mxx->SetMarkerStyle(7);
	mxx->Draw("yf_fit:xf_fit",sigclean&&yclean);

	TH2D *h2_theta_ecc = new TH2D ("h2_theta_ecc", "h2_theta_ecc", 500, -1., 6., 500, 0., 8.);
	TCanvas *c10 = new TCanvas("c10","theta:ecc",600,900);	
	mxx->Project("h2_theta_ecc","theta:ecc","abs(fi<0.026)&&abs(yi)<0.0015"&&sigclean);

	h2_theta_ecc->SetMarkerStyle(20);
	h2_theta_ecc->Draw();

	TLine *t_ground = new TLine (0., 0., 0., 8.);
	t_ground->Draw();
	t_ground->SetLineColor(2);
	t_ground->SetLineWidth(2);

	TLine *t_1Ge = new TLine (0.563, 0., 0.563, 8.);
	t_1Ge->Draw();
	t_1Ge->SetLineColor(2);
	t_1Ge->SetLineWidth(2);

	TLine *t_2Ge = new TLine (1.108, 0., 1.108, 8.);
	t_2Ge->Draw();
	t_2Ge->SetLineColor(2);
	t_2Ge->SetLineWidth(2);

	TLine *t_3Ge = new TLine (1.410, 0., 1.410, 8.);
	t_3Ge->Draw();
	t_3Ge->SetLineColor(2);
	t_3Ge->SetLineWidth(2);

	TLine *t_4Ge = new TLine (1.539, 0., 1.539, 8.);
	t_4Ge->Draw();
	t_4Ge->SetLineColor(2);
	t_4Ge->SetLineWidth(2);


	
	TLine *t_1Ne = new TLine (1.887, 0., 1.887, 8.);
	t_1Ne->Draw();
	t_1Ne->SetLineColor(3);
	t_1Ne->SetLineWidth(2);


	TLine *t_2Ne = new TLine (3.376, 0., 3.376, 8.);
	t_2Ne->Draw();
	t_2Ne->SetLineColor(3);
	t_2Ne->SetLineWidth(2);




	TCanvas *c11 = new TCanvas("c11","ecc",800,600);	
	TH1D *h_ecc = new TH1D ("h_ecc", "h_ecc", 200, -4., 15.);
	c11->cd();
	mxx->Project("h_ecc", "ecc",sigclean&&yclean);
	h_ecc->Draw();
	TCanvas *c12 = new TCanvas("c12","ecc-fondo",800,600);
	c12->SetLogy();	
	TH1D *h_ecc_full_range = new TH1D ("h_ecc_full_range", "h_ecc_full_range", 500, -1., 50.);
	TH1D *h_ecc_fondo = new TH1D ("h_ecc_fondo", "h_ecc_fondo", 500, -1., 50.);

	c12->cd();
	mxx->Project("h_ecc_full_range", "ecc",sigclean&&yclean);
	mxx_fondo->Project("h_ecc_fondo", "ecc",sigclean&&yclean);
	h_ecc_full_range->Draw();
	
	h_ecc_fondo->Scale(12.13);
	h_ecc_full_range->Add(h_ecc_fondo, -1.);
	h_ecc_full_range->Draw();

	h_ecc_fondo->Draw("same");


	TH1D *h_nrun = new TH1D ("h_nrun", "h_nrun", 450, 50., 500.);
	TH1D *h_nrun_sigclean = new TH1D ("h_nrun_sigclean", "h_nrun_sigclean", 450, 50., 500.);
	//TH1D *h_eff_sig = new TH1D ("h_eff_sig", "h_eff_sig", 450, 50, 500);

	TCanvas *c121 = new TCanvas("c11","ecc",800,600);	
	mxx->Project("h_nrun","nrun", "");
	//mxx->Draw("nrun", "");

	//h_nrun->Draw();

	//mxx->SetLineColor(2);
	mxx->Project("h_nrun_sigclean","nrun", sigclean, "");
	//mxx->SetLineColor(3);
	//h_nrun_sigclean->Draw("same");

	h_nrun_sigclean->Divide(h_nrun);
	//mxx->Draw("nrun", !sigclean, "same");
h_nrun_sigclean->Draw();


	cout << "********************************************" << endl;
	cout << "Sigma Efficiency = " << mxx->GetEntries(sigclean)/(float)mxx->GetEntries("") << endl;
	cout << "********************************************" << endl;






/*
	TCanvas *c2 = new TCanvas("c2","tefoc:xf_fit with PID for 18Ne",800,600);	
	c2->cd();
	mxx->Draw("tefoc:xf_fit",idne_18&&yclean,"");

	TCanvas *c3 = new TCanvas("c3","tefoc:tac with PID for 18Ne",800,600);	
	c3->cd();
	mxx->Draw("tefoc:tac",idne_18&&yclean,"");

	TCanvas *c4 = new TCanvas("c4","xf_fit:tac with PID for 18Ne",800,600);	
	c4->cd();
	mxx->Draw("xf_fit:tac",idne_18&&yclean,"");

*/
/*

	TFile *simC = new TFile("Simul_DCE_C.root");
	TTree *tree_sim_C = (TTree *)simC->Get("tree");
	tree_sim_C->SetMarkerStyle(7);
	tree_sim_C->SetMarkerColor(2);
	c5->cd();
	tree_sim_C->Draw("tf:xf","yf>-0.01&&yf<0.01","same");

	c6->cd();
	tree_sim_C->Draw("yf:xf","","same");

	simC->Close();

	TFile *simSe = new TFile("Simul_DCE_Se.root");
	TTree *tree_sim_Se = (TTree *)simSe->Get("tree");
	tree_sim_Se->SetMarkerStyle(7);
	tree_sim_Se->SetMarkerColor(2);
	c5->cd();
	tree_sim_Se->Draw("tf:xf","yf>-0.01&&yf<0.01","same");

	c6->cd();
	tree_sim_Se->Draw("yf:xf","","same");

	simSe->Close();

*/
a->Close();

}

/*

  The QCD, PDF and alpha_s variations are documented in the following slides,

  https://indico.cern.ch/event/459797/contributions/1961581/attachments/1181555/1800214/mcaod-Feb15-2016.pdf
  
  The correspondence with latinos is documented in the mcWeightExplainedOrdered histogram,

  >>> 9 QCD variations
  [bin    1]   <weight id="1001"> muR=1 muF=1 </weight>
  [bin    2]   <weight id="1002"> muR=1 muF=2 </weight>
  [bin    3]   <weight id="1003"> muR=1 muF=0.5 </weight>
  [bin    4]   <weight id="1004"> muR=2 muF=1 </weight>
  [bin    5]   <weight id="1005"> muR=2 muF=2 </weight>
  [bin    6]   <weight id="1006"> muR=2 muF=0.5 </weight>
  [bin    7]   <weight id="1007"> muR=0.5 muF=1 </weight>
  [bin    8]   <weight id="1008"> muR=0.5 muF=2 </weight>
  [bin    9]   <weight id="1009"> muR=0.5 muF=0.5 </weight>

  >>> 100 PDF variations
  [bin   10]   <weight id="2001"> PDF set = 260001 </weight>
  [bin   11]   <weight id="2002"> PDF set = 260002 </weight>
  [bin   12]   <weight id="2003"> PDF set = 260003 </weight>
  ...
  [bin  107]   <weight id="2098"> PDF set = 260098 </weight>
  [bin  108]   <weight id="2099"> PDF set = 260099 </weight>
  [bin  109]   <weight id="2100"> PDF set = 260100 </weight>

  >>> 2 alpha_s variations
  [bin  110]   <weight id="2101"> PDF set = 265000 </weight>
  [bin  111]   <weight id="2102"> PDF set = 266000 </weight>

*/


#include "TFile.h"
#include "TH1D.h"
#include "TString.h"


// Constants
//------------------------------------------------------------------------------
const int _nqcd = 9;
const int _npdf = 100;

const TString _gendir = "/gpfs/csic_users/piedra/work/CMSSW_8_0_5/src/AnalysisCMS/rootfiles/nominal/Control/";
const TString _recdir = "/gpfs/csic_users/piedra/work/CMSSW_8_0_5/src/AnalysisCMS/rootfiles/nominal/Control/";

const bool _savefigures = false;


// Functions
//------------------------------------------------------------------------------
void GetPdfQcdSyst(TString     sample,
		   TString     label,
		   TString     level);

void DrawLatex    (Font_t      tfont,
		   Float_t     x,
		   Float_t     y,
		   Float_t     tsize,
		   Short_t     align,
		   const char* text,
		   Bool_t      setndc = true);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// getPdfQcd
//
//    WWTo2L2Nu 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      2.23%
//    QCD         mu=0.5 / mu=2.0   0.53% / 0.52%
//    alpha_s     265000 / 266000   0.02% / 0.02%
//    PDF                           0.25%
//    PDF+alpha_s                   0.25%
//   
//   
//    WWTo2L2Nu 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.84%
//    QCD         mu=0.5 / mu=2.0   1.53% / 1.37%
//    alpha_s     265000 / 266000   0.01% / 0.00%
//    PDF                           0.27%
//    PDF+alpha_s                   0.27%
//   
//   
//    VBFHToWWTo2L2Nu_M125 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.18%
//    QCD         mu=0.5 / mu=2.0   0.77% / 0.68%
//    alpha_s     265000 / 266000   1.07% / 0.75%
//    PDF                           0.52%
//    PDF+alpha_s                   1.06%
//   
//   
//    VBFHToWWTo2L2Nu_M125 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.79%
//    QCD         mu=0.5 / mu=2.0   0.07% / 0.03%
//    alpha_s     265000 / 266000   0.19% / 0.26%
//    PDF                           0.31%
//    PDF+alpha_s                   0.39%
//   
//   
//    GluGluHToWWTo2L2Nu_M125 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      1.12%
//    QCD         mu=0.5 / mu=2.0   2.81% / 2.34%
//    alpha_s     265000 / 266000   0.13% / 0.05%
//    PDF                           0.58%
//    PDF+alpha_s                   0.58%
//   
//   
//    GluGluHToWWTo2L2Nu_M125 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.55%
//    QCD         mu=0.5 / mu=2.0   2.00% / 1.66%
//    alpha_s     265000 / 266000   0.29% / 0.30%
//    PDF                           0.38%
//    PDF+alpha_s                   0.48%
//   
//   
//    WZTo3LNu 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.15%
//    QCD         mu=0.5 / mu=2.0   1.70% / 1.47%
//    alpha_s     265000 / 266000   0.15% / 0.26%
//    PDF                           0.47%
//    PDF+alpha_s                   0.52%
//   
//   
//    WZTo3LNu 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.14%
//    QCD         mu=0.5 / mu=2.0   2.91% / 2.54%
//    alpha_s     265000 / 266000   0.20% / 0.27%
//    PDF                           0.49%
//    PDF+alpha_s                   0.54%
//   
//   
//    HWminusJ_HToWW_M125 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.12%
//    QCD         mu=0.5 / mu=2.0   6.12% / 4.55%
//    alpha_s     265000 / 266000   0.32% / 0.31%
//    PDF                           0.56%
//    PDF+alpha_s                   0.64%
//   
//   
//    HWminusJ_HToWW_M125 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.12%
//    QCD         mu=0.5 / mu=2.0   1.32% / 1.52%
//    alpha_s     265000 / 266000   0.05% / 0.02%
//    PDF                           0.49%
//    PDF+alpha_s                   0.49%
//   
//   
//    HWplusJ_HToWW_M125 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.12%
//    QCD         mu=0.5 / mu=2.0   2.29% / 3.39%
//    alpha_s     265000 / 266000   0.20% / 0.11%
//    PDF                           0.48%
//    PDF+alpha_s                   0.50%
//   
//   
//    HWplusJ_HToWW_M125 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.12%
//    QCD         mu=0.5 / mu=2.0   4.64% / 3.57%
//    alpha_s     265000 / 266000   0.10% / 0.04%
//    PDF                           0.36%
//    PDF+alpha_s                   0.36%
//   
//   
//    HZJ_HToWW_M125 0jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.06%
//    QCD         mu=0.5 / mu=2.0   1.96% / 3.17%
//    alpha_s     265000 / 266000   0.08% / 0.29%
//    PDF                           1.22%
//    PDF+alpha_s                   1.24%
//   
//   
//    HZJ_HToWW_M125 1jet acceptance uncertainties
//   -----------------------------------------
//    nominal acceptance * eff      0.06%
//    QCD         mu=0.5 / mu=2.0   2.65% / 0.69%
//    alpha_s     265000 / 266000   0.09% / 0.01%
//    PDF                           0.86%
//    PDF+alpha_s                   0.86%
//   
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void getPdfQcd()
{
  gInterpreter->ExecuteMacro("../test/PaperStyle.C");

  if (_savefigures) gSystem->mkdir("figures", kTRUE);

  GetPdfQcdSyst("HWminusJ_HToTauTau_M125", "", "wh3l");
  GetPdfQcdSyst("HWminusJ_HToWW_M125",     "", "wh3l");
  GetPdfQcdSyst("HWplusJ_HToTauTau_M125",  "", "wh3l");
  GetPdfQcdSyst("HWplusJ_HToWW_M125",      "", "wh3l");
  GetPdfQcdSyst("HZJ_HToWW_M125",          "", "wh3l");
  GetPdfQcdSyst("WZZ",                     "", "wh3l");
  GetPdfQcdSyst("ggZH_HToWW_M125",         "", "wh3l");

  GetPdfQcdSyst("HWminusJ_HToTauTau_M125", "", "wh3l_ossf");
  GetPdfQcdSyst("HWminusJ_HToWW_M125",     "", "wh3l_ossf");
  GetPdfQcdSyst("HWplusJ_HToTauTau_M125",  "", "wh3l_ossf");
  GetPdfQcdSyst("HWplusJ_HToWW_M125",      "", "wh3l_ossf");
  GetPdfQcdSyst("HZJ_HToWW_M125",          "", "wh3l_ossf");
  GetPdfQcdSyst("WZZ",                     "", "wh3l_ossf");
  GetPdfQcdSyst("ggZH_HToWW_M125",         "", "wh3l_ossf");

  GetPdfQcdSyst("HWminusJ_HToTauTau_M125", "", "wh3l_sssf");
  GetPdfQcdSyst("HWminusJ_HToWW_M125",     "", "wh3l_sssf");
  GetPdfQcdSyst("HWplusJ_HToTauTau_M125",  "", "wh3l_sssf");
  GetPdfQcdSyst("HWplusJ_HToWW_M125",      "", "wh3l_sssf");
  GetPdfQcdSyst("HZJ_HToWW_M125",          "", "wh3l_sssf");
  GetPdfQcdSyst("WZZ",                     "", "wh3l_sssf");
  GetPdfQcdSyst("ggZH_HToWW_M125",         "", "wh3l_sssf");


  /*
  GetPdfQcdSyst("WWTo2L2Nu", "WW", "0jet");
  GetPdfQcdSyst("WWTo2L2Nu", "WW", "1jet");

  GetPdfQcdSyst("VBFHToWWTo2L2Nu_M125", "qqH", "0jet");
  GetPdfQcdSyst("VBFHToWWTo2L2Nu_M125", "qqH", "1jet");

  GetPdfQcdSyst("GluGluHToWWTo2L2Nu_M125", "ggH", "0jet");
  GetPdfQcdSyst("GluGluHToWWTo2L2Nu_M125", "ggH", "1jet");

  GetPdfQcdSyst("WZTo3LNu", "WZ", "0jet");
  GetPdfQcdSyst("WZTo3LNu", "WZ", "1jet");

  GetPdfQcdSyst("HWminusJ_HToWW_M125", "HW-", "0jet");
  GetPdfQcdSyst("HWminusJ_HToWW_M125", "HW-", "1jet");

  GetPdfQcdSyst("HWplusJ_HToWW_M125", "HW+", "0jet");
  GetPdfQcdSyst("HWplusJ_HToWW_M125", "HW+", "1jet");

  GetPdfQcdSyst("HZJ_HToWW_M125", "HZ", "0jet");
  GetPdfQcdSyst("HZJ_HToWW_M125", "HZ", "1jet");
  */
}


//------------------------------------------------------------------------------
// GetPdfQcdSyst
//------------------------------------------------------------------------------
void GetPdfQcdSyst(TString sample,
		   TString label,
		   TString level)
{
  TFile* file = new TFile(_recdir + sample + ".root", "read");

  TH1F* h_weights_gen = (TH1F*)file->Get("list_vectors_weights_gen");
  TH1F* h_weights_rec = (TH1F*)file->Get("list_vectors_weights_" + level);


  // Produce the QCD uncertainties
  //----------------------------------------------------------------------------
  float qcd_gen_mu05 = h_weights_gen->GetBinContent(9) / h_weights_gen->GetBinContent(1);
  float qcd_gen_mu20 = h_weights_gen->GetBinContent(5) / h_weights_gen->GetBinContent(1);

  float qcd_rec_mu05 = h_weights_rec->GetBinContent(9) / h_weights_rec->GetBinContent(1);
  float qcd_rec_mu20 = h_weights_rec->GetBinContent(5) / h_weights_rec->GetBinContent(1);


  // Produce the PDF uncertainties
  //----------------------------------------------------------------------------
  TH1D* h_pdfratio = new TH1D("h_pdfratio", "", 100, 0.965, 1.035);

  float denominator = h_weights_rec->GetBinContent(1) / h_weights_gen->GetBinContent(1);  // Nominal values

  for (int i=10; i<110; i++)
    {
      float numerator = h_weights_rec->GetBinContent(i) / h_weights_gen->GetBinContent(i);

      float ratio = numerator / denominator;

      h_pdfratio->Fill(ratio);
    }


  // Draw the PDF distribution
  //----------------------------------------------------------------------------
  TCanvas* canvas = new TCanvas(sample + "_" + level, sample + "_" + level);

  h_pdfratio->SetFillColor(kRed+1);
  h_pdfratio->SetFillStyle(  1001);
  h_pdfratio->SetLineColor(kRed+1);

  h_pdfratio->Draw("hist");

  h_pdfratio->SetXTitle("#frac{N_{rec}^{PDF} / N_{gen}^{PDF}}{N_{rec}^{nominal} / N_{gen}^{nominal}}");
  h_pdfratio->SetYTitle("entries / bin");

  h_pdfratio->GetXaxis()->SetTitleOffset(2.0);

  DrawLatex(42, 0.940, 0.945, 0.050, 31, label + " " + level);

  canvas->GetFrame()->DrawClone();

  if (_savefigures)
    {
      canvas->SaveAs("figures/pdfacceptance_" + sample + "_" + level + ".pdf");
      canvas->SaveAs("figures/pdfacceptance_" + sample + "_" + level + ".png");
    }


  // Produce the alpha_s uncertainties
  //----------------------------------------------------------------------------
  float alpha_gen_265000 = h_weights_gen->GetBinContent(110) / h_weights_gen->GetBinContent(1);
  float alpha_gen_266000 = h_weights_gen->GetBinContent(111) / h_weights_gen->GetBinContent(1);

  float alpha_rec_265000 = h_weights_rec->GetBinContent(110) / h_weights_rec->GetBinContent(1);
  float alpha_rec_266000 = h_weights_rec->GetBinContent(111) / h_weights_rec->GetBinContent(1);


  // Prepare the final uncertainties
  //----------------------------------------------------------------------------
  float qcd_mu05 = 1e2 * fabs(1. - qcd_rec_mu05 / qcd_gen_mu05);
  float qcd_mu20 = 1e2 * fabs(1. - qcd_rec_mu20 / qcd_gen_mu20);

  float alpha_265000 = 1e2 * fabs(1. - alpha_rec_265000 / alpha_gen_265000);
  float alpha_266000 = 1e2 * fabs(1. - alpha_rec_266000 / alpha_gen_266000);

  float pdf = 1e2 * h_pdfratio->GetRMS();

  float pdf_alpha = sqrt(pdf*pdf + (alpha_265000*alpha_265000 + alpha_266000*alpha_266000)/2.);


  // Print the final uncertainties
  //----------------------------------------------------------------------------
  printf("\n %s %s acceptance uncertainties\n", sample.Data(), level.Data());
  printf("-----------------------------------------\n");
  printf(" nominal acceptance * eff      %4.2f%%\n", 1e2 * h_weights_rec->GetBinContent(1) / h_weights_gen->GetBinContent(1));
  printf(" QCD         mu=0.5 / mu=2.0   %4.2f%% / %4.2f%%\n", qcd_mu05, qcd_mu20);
  printf(" alpha_s     265000 / 266000   %4.2f%% / %4.2f%%\n", alpha_265000, alpha_266000);
  printf(" PDF                           %4.2f%%\n", pdf);
  printf(" PDF+alpha_s                   %4.2f%%\n", pdf_alpha);
  printf("\n");
}


//------------------------------------------------------------------------------
// DrawLatex 
//------------------------------------------------------------------------------
void DrawLatex(Font_t      tfont,
	       Float_t     x,
	       Float_t     y,
	       Float_t     tsize,
	       Short_t     align,
	       const char* text,
	       Bool_t      setndc)
{
  TLatex* tl = new TLatex(x, y, text);

  tl->SetNDC      (setndc);
  tl->SetTextAlign( align);
  tl->SetTextFont ( tfont);
  tl->SetTextSize ( tsize);

  tl->Draw("same");
}

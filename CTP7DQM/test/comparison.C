#include "drawGridRct.C"

TFile * file0 ;
TFile * fileRef ;

//here the actually interesting code starts
const Double_t min = 0.;
const Double_t max = 2.;

const Int_t nLevels = 50;
Double_t levels[nLevels];



void comparison(TString fileName="~/www/CTP7DQMTESTS/live/CTP7DQM.root", TString fileNameRef="~/www/CTP7DQMTESTS/mc/CTP7DQMMC.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();

 const UInt_t Number = 5;
 Double_t Red[Number]    = { 1.00,  1.0 ,0.00,0   ,0.};
 Double_t Green[Number]  = { 0.00,  1.0 ,1.00,1.  ,0.};
 Double_t Blue[Number]   = { 0.00,  0.0 ,0.  ,1.00,1.00};
 Double_t Length[Number] = { 0.00,  0.45,0.50,0.55,1.00 };
 Int_t nb=100;
 TColor::CreateGradientColorTable(Number,Length,Blue,Green,Red,nb);
 gStyle->SetNumberContours(nb);

 for(int i = 1; i < nLevels; i++) {
  levels[i] = min + (max - min) / (nLevels - 1) * (i);
 }
 levels[0] = 0.;
 //  levels[0] = -1; //Interesting, but this also works as I want!



 file0 = new TFile(fileName,"READONLY");
 fileRef = new TFile(fileNameRef,"READONLY");

 doHisto("RctBitHfPlusTauEtaPhi","Hf Plus Tau Bit");;
 doHisto("RctEmIsoEmEtEtaPhi","EmIso Occupancy (ET in z axis)");;
 doHisto("RctEmIsoEmOccEtaPhi","EmIso Occupancy");;
 doHisto("RctEmNonIsoEmEtEtaPhi","EmNonIso Occupancy (ET in z axis)");;
 doHisto("RctEmNonIsoEmOccEtaPhi","EmNonIso Occupancy");;
 doHisto("RctRegionsEtEtaPhi","Regions Occupancy (ET in z axis)");
 doHisto("RctRegionsOccEtaPhi","Regions Occupancy");;
 doHisto("RctEmIsoEmRank","EmIso Rank",false);;
 doHisto("RctEmNonIsoEmRank","EmNonIso Rank",false);;
 doHisto("RctRegionRank","Regions Rank",false);;
 doHisto("RctRegionRank","Regions Rank Zoomed",false,false,true);;
 doHisto("RctBitMipEtaPhi","Mip Bit");
 doHisto("RctBitOverFlowEtaPhi", "Overflow bit");
 doHisto("RctBitQuietEtaPhi", "Quiet bit");
 doHisto("RctBitTauVetoEtaPhi", "TauVeto bit");
}

//doPUM option used in pumplotter.cc
void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doPUM=false, bool doZoom=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);       histo->SetName("histo");
 TH1F *histoRef=(TH1F*)fileRef->Get("DQMData/L1T/L1TCTP7/"+name);  histoRef->SetName("histoRef");

 if(do2D) {
  histo->Divide(histoRef);

  for (int i=0; i<histo->GetNbinsX(); i++) for (int j=0; j<histo->GetNbinsX(); j++){
   if(histo->GetBinContent(i,j)==0 && histoRef->GetBinContent(i,j)!=0) {histo->SetBinContent(i,j,0.01);}}

  histo->SetContour((sizeof(levels)/sizeof(Double_t)), levels);
  histo->Draw("colz");
  histo->SetXTitle("#eta");
  histo->SetYTitle("#phi");
  histo->GetZaxis()->SetRangeUser(min, max);
  histo->SetTitle(label);
  drawGridRct();

 }
 else if(doZoom){
  histo->Divide(histoRef);
  histo->Draw("hist");
  name=name+"_zoom";
  histo->SetName(name);
  histo->SetXTitle("Rank,E");
  histo->SetTitle(label);
  histo->SetYTitle("Ratio Emulator/CTP7");
  histo->SetLineWidth(2);
  histo->GetXaxis()->SetRangeUser(0,50);
  histo->GetYaxis()->SetRangeUser(0,2);

 }
 else     {
  histo->Divide(histoRef);
  histo->Draw("hist"); 
  histo->SetXTitle("RANK");  
  histo->SetYTitle("Ratio Emulator/CTP7");
  histo->SetLineWidth(2);
  histo->SetTitle(label);
  histo->GetYaxis()->SetRangeUser(0,2);

 }


 C1->SaveAs(name+"_COMPARISON.png");
}

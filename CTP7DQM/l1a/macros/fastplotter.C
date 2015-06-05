#include "drawGridRct.C"

TFile * file0 ;

void fastplotter(TString fileName="L1ADQMMERGED.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();

 //  gStyle->SetPalette(55);

 file0 = new TFile(fileName,"READONLY");

 doHisto("RctRegionsEtEtaPhi","Regions Occupancy (ET in z axis)");;
 doHisto("RctRegionsOccEtaPhi","Regions Occupancy");;
 doHisto("RctEmIsoEmEtEtaPhi","EmIso Occupancy (ET in z axis)");;
 doHisto("RctEmIsoEmOccEtaPhi","EmIso Occupancy");;
 doHisto("RctEmNonIsoEmEtEtaPhi","EmNonIso Occupancy (ET in z axis)");;
 doHisto("RctEmNonIsoEmOccEtaPhi","EmNonIso Occupancy");;
 doHisto("RctRegionBx","Region BX",false,false,true);;
 doHisto("RctEmBx","EmIso BX",false,false,true);;
 doHisto("RctEmIsoEmRank","EmIso Rank",false);;
 doHisto("RctEmNonIsoEmRank","EmNonIso Rank",false);;
 doHisto("RctRegionRank","Regions Rank",false);;
 doHisto("RctRegionRank","Regions Rank Zoomed",false,true);;
}

//doPUM option used in pumplotter.cc
void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doZoom=false,bool doBX=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/RCTL1A/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);
          histo->GetYaxis()->SetTitleOffset(1.4);
          drawGridRct();

 }
 else if(doZoom){
          histo->Draw("hist");
          name=name+"_zoom";
          histo->SetName(name);
          histo->SetXTitle("Rank");
          histo->SetTitle(label);
          histo->GetYaxis()->SetTitleOffset(1.4);
          histo->SetYTitle("Non-Zero Events");
          histo->SetLineWidth(2);
          histo->GetXaxis()->SetRangeUser(0,50);
 }
else if(doBX){
	  histo->Draw("hist");
          histo->SetXTitle("BX");
          histo->SetYTitle("Non-Zero Events");
	  histo->GetYaxis()->SetTitleOffset(1.4);
          histo->SetLineWidth(2);
	  histo->GetXaxis()->SetNdivisions(505);
          histo->SetTitle(label);
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle("RANK");  
          histo->SetYTitle("Non-Zero Events");
          histo->GetYaxis()->SetTitleOffset(1.4);
          histo->SetLineWidth(2);
          histo->SetTitle(label);
 }


 C1->SaveAs(name+".png");
}



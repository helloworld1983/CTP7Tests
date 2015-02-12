TFile * file0 ;
void
set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops,blue, green, red, NCont);
    gStyle->SetNumberContours(NCont);
}
 
void linkplotter(TString fileName="CTP7DQM_link.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();
 set_plot_style();
// see TError.h and set gErrorIgnoreLevel to one of the values:
// gErrorIgnoreLevel = 3000;
//
 file0 = new TFile(fileName,"READONLY");
 
 doHisto("RctLinkMonitor","CTP7 Link Status","CTP7 Link Status", false);;
 doHisto("RctLinkMonitorVsTime","CTP7 Link Health vs Time","Madison Time hhmmss",true, false);;
 doHisto("RctLinkMonitorNot15","CTP7 Link Status Error","CTP7 Link Error Status ", false);;
 doHisto("RctLinkMonitor2D","CTP7 Link Health Per Link","CTP7 Link Number", true,true);;
 doHisto("RctLinkMonitorNot15_2D","CTP7 Link Error Status per Link","CTP7 Link Number", true,false,true);;
}

void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", TString xaxis="X Axis",  bool do2D=true, bool do01=false, bool Ystatus=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/LinkDQM/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle(xaxis);
          if (do01){histo->SetYTitle("No Error                                  Error");}
          else if (Ystatus){histo->SetYTitle("CTP7 Link Status");}
          else{histo->SetYTitle("CTP7 Link Number");}
          histo->SetTitle(label);
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle(xaxis);  
          histo->SetYTitle("Events");
          histo->SetLineWidth(2);
          histo->SetTitle(label);
 }
 C1->SaveAs(name+".png");
}



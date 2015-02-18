TFile * file0 ;
ofstream myfile;
 
void pumplotter(TString fileName="CTP7DQMMERGE.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();
// see TError.h and set gErrorIgnoreLevel to one of the values:
// gErrorIgnoreLevel = 3000;
//
 file0 = new TFile(fileName,"READONLY");
 myfile.open ("pum.log");
 doHistoEvt("RctRegionsNonZeroVsEvt","Non Zero Regions/22 Vs Event","PUM bin",true);;
 doHistoEvt("RctRegionsAvgEtVsEvt","Average Region Rank Vs Event","Average region rank", true);;
 doHistoEvt("RctRegionsAvgEtVsEta","Average Region Rank Vs gctEta","Average region rank", false);;
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs Event","Average region rank", true);;
 doHisto("RctRegionsAverageRegionEt","Average Region Rank",false);;
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs Event","Average region rank", true,40);;
 doHisto("RctRegionsNonZero","Non Zero Regions/22",false,false);;
 doHisto("RctRegionsPumEta0","E_{T} per PUM bin in gcteta=0",false,true);;
 doHisto("RctRegionsPumEta1","E_{T} per PUM bin in gcteta=1",false,true);;
 doHisto("RctRegionsPumEta2","E_{T} per PUM bin in gcteta=2",false,true);;
 doHisto("RctRegionsPumEta3","E_{T} per PUM bin in gcteta=3",false,true);;
 doHisto("RctRegionsPumEta4","E_{T} per PUM bin in gcteta=4",false,true);;
 doHisto("RctRegionsPumEta5","E_{T} per PUM bin in gcteta=5",false,true);;
 doHisto("RctRegionsPumEta6","E_{T} per PUM bin in gcteta=6",false,true);;
 doHisto("RctRegionsPumEta7","E_{T} per PUM bin in gcteta=7",false,true);;
 doHisto("RctRegionsPumEta8","E_{T} per PUM bin in gcteta=8",false,true);;
 doHisto("RctRegionsPumEta9","E_{T} per PUM bin in gcteta=9",false,true);;
 doHisto("RctRegionsPumEta10","E_{T} per PUM bin in gcteta=10",false,true);;
 doHisto("RctRegionsPumEta11","E_{T} per PUM bin in gcteta=11",false,true);;
 doHisto("RctRegionsPumEta12","E_{T} per PUM bin in gcteta=12",false,true);;
 doHisto("RctRegionsPumEta13","E_{T} per PUM bin in gcteta=13",false,true);;
 doHisto("RctRegionsPumEta14","E_{T} per PUM bin in gcteta=14",false,true);;
 doHisto("RctRegionsPumEta15","E_{T} per PUM bin in gcteta=15",false,true);;
 doHisto("RctRegionsPumEta16","E_{T} per PUM bin in gcteta=16",false,true);;
 doHisto("RctRegionsPumEta17","E_{T} per PUM bin in gcteta=17",false,true);;
 doHisto("RctRegionsPumEta18","E_{T} per PUM bin in gcteta=18",false,true);;
 doHisto("RctRegionsPumEta19","E_{T} per PUM bin in gcteta=19",false,true);;
 doHisto("RctRegionsPumEta20","E_{T} per PUM bin in gcteta=20",false,true);;
 doHisto("RctRegionsPumEta21","E_{T} per PUM bin in gcteta=21",false,true);;
 myfile.close();
}

void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doPUM=false, int zoom=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);
          histo->Draw();
 }
 else if(doPUM){
          histo->Draw("colz,text");
          histo->SetXTitle("PUM bin");
          histo->SetYTitle("RANK");
          histo->SetTitle(label);
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle(label);  
          histo->SetYTitle("Events");
          histo->SetLineWidth(2);
          histo->SetTitle(label);
          if(zoom!=-1) {histo->GetXaxis()->SetUserRange(0,zoom); histo->SetName(name+"_zoom");}
              

 }
 C1->SaveAs(name+".png");
if (doPUM) doProfile(name,"Avg "+label);
}

void doProfile(TString name="RctRegionsPumEta10",TString label="Test"){
 TCanvas* C1= new TCanvas("T"+name);
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 histo->Draw("colz,text");
 histo->SetXTitle("PUM bin");
 histo->SetYTitle("Average ET");
 histo->SetTitle(label);
 TProfile *prof=histo->ProfileX();
 prof->Draw();
 for (Int_t i=0;i<22;i++){
   std::cout<<prof->GetBinContent(i)<<",";
   myfile << prof->GetBinContent(i)<<",";
   if(i==21) std::endl;
 }
 C1->SaveAs(name+"Avg"+".png");
}

void doHistoEvt(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", TString yaxis="YAxis",bool doEvt, int zoom=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 histo->Draw("colz,text");
if (doEvt) histo->SetXTitle("EVENT");
else histo->SetXTitle("gctEta");
 histo->SetYTitle(yaxis);
 histo->SetTitle(label);
          if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(0,zoom);  name=name+"_zoom";}
 TProfile *prof=histo->ProfileX();
 prof ->Draw();
//if (doEvt) prof->Rebin(10.);
 C1->SaveAs(name+".png");
}


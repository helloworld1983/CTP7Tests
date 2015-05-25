TFile * file0 ;
ofstream myfile;
 
void timingplotter(TString fileName="CTP7DQMMERGE.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();
// see TError.h and set gErrorIgnoreLevel to one of the values:
// gErrorIgnoreLevel = 3000;
//
 file0 = new TFile(fileName,"READONLY");
 myfile.open ("timing.log");

 doHisto("RctRegionsEtMapVsEvt","Regions vs Event (ET)",false,true,false);;
 doHisto("RctRegionsOccVsEvt","Non Zero Regions vs Event",false,true,false);;

 doHistoEvt("RctRegionsTotEtVsEvt","Tot Region Rank Vs Event","Tot region rank", true);;
 doHistoEvt("RctRegionsNonZeroVsEvt","Non Zero Regions Vs Event","PUM",true,-1,true);;
 doHistoEvt("RctRegionsNonZeroBarrelVsEvt","Non Zero Barrel Regions Vs Event","PUM",true,-1,true);;
 doHistoEvt("RctRegionsNonZeroHFVsEvt","Non Zero HF Regions Vs Event","PUM",true,-1,true);;
 doHistoEvt("RctRegionsAvgEtVsEvt","Average Region Rank Vs Event","Average region rank", true,-1,true);;
 doHistoEvt("RctRegionsAvgEtVsEta","Average Region Rank Vs gctEta","Average region rank", false);;
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs Event","Max region rank", true,-1,true);;
 doHisto("RctRegionsAverageRegionEt","Average Region Rank",false,false);;
 doHisto("RctRegionsTotalRegionEt","Total Region Rank",false,false);;
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs Event","Max region rank", true,170);;
 doHistoEvt("RctRegionsAvgEtVsEvt","Average Region Rank Vs Event","Average region rank", true,170);;
 doHistoEvt("RctRegionsTotEtVsEvt","Tot Region Rank Vs Event","Tot region rank", true,170);;
 doHisto("RctRegionsNormNonZero","Non Zero Regions",false,false,false);;
 doHistoEvt("RctRegionsNormNonZeroVsEvt","Non Zero Regions / 22 Vs Event","PUM",true);;
 doHisto("RctRegionsNonZero","Non Zero Regions",false,false,false);;
//
//Electron plotting
//
 doHistoEvt("RctEmIsoNonZeroVsEvt","Non Zero EM Vs Event","Num non-zero",true);;
 doHistoEvt("RctEmIsoAvgEtVsEta","Average EM Rank Vs gctEta","Average em rank", false);;
 doHistoEvt("RctEmIsoTotEtVsEvt","Tot EM Rank Vs Event","Tot Em rank", true);;
 doHistoEvt("RctEmIsoTotEtVsEvt","Tot Em Rank Vs Event","Tot Em rank", true,170);;
 doHistoEvt("RctEmIsoMaxEtVsEvt","Max Em Rank Vs Event","Max Em rank", true);;
 doHistoEvt("RctEmIsoMaxEtVsEvt","Max Em Rank Vs Event","Max Em rank", true,170);;
 doHistoEvt("RctEmIsoAvgEtVsEvt","Average Em Rank Vs Event","Average em rank", true);;
 doHistoEvt("RctEmIsoAvgEtVsEvt","Average Em Rank Vs Event","Average em rank", true,170);;
 doHisto("RctEmBx","RCT Em Bunch Crossing",false, false);;
 myfile.close();
}

void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool do2DEvent=false, bool doPUM=false, int zoom=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);
          histo->Draw();
 }
 if(do2DEvent) {
          histo->Draw("colz,text");
          histo->SetXTitle("Event");
          histo->SetYTitle("Region Index");
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

          if (histo->GetMaximum()<10) {histo->GetYaxis()->SetRangeUser(0,10);}
          else C1->SetLogy(true); 
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
 for (Int_t i=1;i<23;i++){
   std::cout<<prof->GetBinContent(i)<<",";
   myfile << prof->GetBinContent(i)<<",";
   if(i==22) std::endl;
 }
 //C1->SaveAs(name+"Avg"+".png");
}

void doHistoEvt(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", TString yaxis="YAxis",bool doEvt, int zoom=-1, bool save=false){
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
 if (prof->GetMinimum() <0.1 && prof->GetMaximum()<10) {prof->GetYaxis()->SetRangeUser(0,10);}
//if (doEvt) prof->Rebin(10.);
 C1->SaveAs(name+".png");
 if (save){C1->SaveAs(name+".root");}
}


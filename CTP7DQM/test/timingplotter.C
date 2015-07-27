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

 int firstBX=1000, lastBX=1170; 

 doHistoREGION("RctRegionsEtMapVsEvt","Regions vs BX (ET)",-1);;
 doHistoREGION("RctRegionsOccVsEvt","Non Zero Regions vs BX",-1);;
 doHisto("RctRegionsHFPhiOccETVsEvt","HF Phi regions vs BX",false,true,false);;
 doHisto("RctRegionsHFPhiOccETVsEvt","HF Phi regions vs BX",false,true,false,firstBX,lastBX);;
 doHisto("RctRegionsHFPhiPlusOccETVsEvt","HF Phi regions vs BX",false,true,false,firstBX,lastBX);;
 doHisto("RctRegionsHFPhiMinusOccETVsEvt","HF Phi regions vs BX",false,true,false,firstBX,lastBX);;

 doHistoEvt("RctRegionsTotEtVsEvt","Tot Region Rank Vs BX","Tot region rank", true);;
 doHistoEvt("RctRegionsNonZeroVsEvt","Non Zero Regions Vs BX","PUM",true,-1,-1,true);;
 doHistoEvt("RctRegionsNonZeroVsEvt","ZOOMED - Non Zero Regions Vs BX","PUM",true,firstBX,lastBX,true);;

 doHistoEvt("RctRegionsNonZeroBarrelVsEvt","Non Zero Barrel Regions Vs BX","PUM",true,firstBX,lastBX,true);;
 doHistoEvt("RctRegionsNonZeroHFVsEvt","Non Zero HF Regions Vs BX","PUM",true,-1,-1,true);;
 doHistoEvt("RctRegionsNonZeroBarrelVsEvt","ZOOMED - Non Zero Barrel Regions Vs BX","PUM",true,firstBX,lastBX,true);;
 doHistoEvt("RctRegionsNonZeroHFVsEvt","ZOOMED - Non Zero HF Regions Vs BX","PUM",true,firstBX,lastBX,true);;
 doHistoEvt("RctRegionsAvgEtVsEvt","Average Region Rank Vs BX","Average region rank", true,-1,-1,true);;
 doHistoEvt("RctRegionsAvgEtVsEta","Average Region Rank Vs gctEta","Average region rank", false);;
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs BX","Max region rank", true,-1,-1,true);;
 doHistoEvt("RctRegionsMaxEtHFVsEvt","Max Region Rank in the HF Vs BX","Max region rank", true,-1,-1);;
 doHistoEvt("RctRegionsMaxEtBarrelVsEvt","Max Region Rank Barrel (gctEta=10,11) Vs BX","Max region rank", true,-1,-1);;
 doHistoEvt("RctRegionsMaxEtHFVsEvt","ZOOMED - Max Region Rank in the HF Vs BX","Max region rank", true,firstBX,lastBX);;
 doHistoEvt("RctRegionsMaxEtBarrelVsEvt","ZOOMED - Max Region Rank Barrel (gctEta=10,11) Vs BX","Max region rank", true,firstBX,lastBX);;

 doHisto("RctRegionsAverageRegionEt","Average Region Rank",false,false,false,0,100);;
 doHisto("RctRegionsTotalRegionEt","Total Region Rank",false,false,false,0,100);;
 doHistoEvt("RctRegionsMaxEtVsEvt","ZOOMED - Max Region Rank Vs BX","Max region rank", true,firstBX,lastBX);;
 doHistoEvt("RctRegionsAvgEtVsEvt","ZOOMED - Average Region Rank Vs BX","Average region rank", true,firstBX,lastBX);;
 doHistoEvt("RctRegionsTotEtVsEvt","ZOOMED - Tot Region Rank Vs BX","Tot region rank", true,firstBX,lastBX);;
 doHisto("RctRegionsNormNonZero","Non Zero Regions",false,false,false);;
 doHistoEvt("RctRegionsNormNonZeroVsEvt","Non Zero Regions / 22 Vs BX","PUM",true);;
 doHisto("RctRegionsNonZero","Non Zero Regions",false,false,false);;
//
//Electron plotting
//
 doHistoEvt("RctEmIsoNonZeroVsEvt","Non Zero EM Vs BX","Num non-zero",true);;
 doHistoEvt("RctEmIsoAvgEtVsEta","Average EM Rank Vs gctEta","Average em rank", false);;
 doHistoEvt("RctEmIsoTotEtVsEvt","Tot EM Rank Vs BX","Tot Em rank", true);;
 doHistoEvt("RctEmIsoTotEtVsEvt","ZOOMED - Tot Em Rank Vs BX","Tot Em rank", true,firstBX,lastBX);;
 doHistoEvt("RctEmIsoMaxEtVsEvt","Max Em Rank Vs BX","Max Em rank", true);;
 doHistoEvt("RctEmIsoMaxEtVsEvt","ZOOMED - Max Em Rank Vs BX","Max Em rank", true,firstBX,lastBX);;
 doHistoEvt("RctEmIsoAvgEtVsEvt","Average Em Rank Vs BX","Average em rank", true);;
 doHistoEvt("RctEmIsoAvgEtVsEvt","ZOOMED - Average Em Rank Vs BX","Average em rank", true,firstBX,lastBX);;
 doHisto("RctEmBx","RCT Em Bunch Crossing",false, false);;
 myfile.close();
}

void doHistoREGION(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", int zoom=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
          histo->Draw("colz");
          histo->SetXTitle("BX");
          histo->SetYTitle("Region Index (0-396)");
          histo->SetTitle(label);
          histo->SetLineWidth(2);
 C1->SaveAs(name+".png");
}


void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool do2DBX=false, bool doPUM=false, int zoom=-1, int zoomEnd=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 histo->SetLineWidth(2);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);
 }
 else if(do2DBX) {
          histo->Draw("colz");
          histo->SetXTitle("BX");
          histo->SetYTitle("#phi");
	  if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(zoom,zoomEnd);	name=name+"_zoom";}
          histo->SetTitle(label);
          histo->SetName(name);
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
          histo->SetYTitle("Counts");
          histo->SetLineWidth(2);
          histo->SetTitle(label);
          if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(zoom,zoomEnd); histo->SetName(name+"_zoom");}
              

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
 histo->SetLineWidth(2);
 TProfile *prof=histo->ProfileX();
 prof->Draw();
 for (Int_t i=1;i<23;i++){
   std::cout<<prof->GetBinContent(i)<<",";
   myfile << prof->GetBinContent(i)<<",";
   if(i==22) std::endl;
 }
 //C1->SaveAs(name+"Avg"+".png");
}

void doHistoEvt(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", TString yaxis="YAxis",bool doEvt, int zoom=-1, int zoomEnd=-1, bool save=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 histo->Draw("colz,text");
if (doEvt) histo->SetXTitle("BX");
else histo->SetXTitle("gctEta");
 histo->SetYTitle(yaxis);
 histo->SetTitle(label);
 if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(zoom,zoomEnd);  name=name+"_zoom";}
 TProfile *prof=histo->ProfileX();
 prof ->Draw();
 if (prof->GetMinimum() <0.1 && prof->GetMaximum()<10) {prof->GetYaxis()->SetRangeUser(0,10);}
//if (doEvt) prof->Rebin(10.);
 C1->SaveAs(name+".png");
 if (save){C1->SaveAs(name+".root");}
}


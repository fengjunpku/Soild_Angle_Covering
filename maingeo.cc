#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include "TROOT.h"
#include "TGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TApplication.h"

using namespace std;

const double Theta[2]={20,45};//*deg
const double Size=50;//*mm
const double Distance[2]={150,139};//*mm
const double N = 150;//odd
const double eps = 1e-5;

int main(int argc,char *argv[])
{
  TApplication *theApp = new TApplication("app",&argc,argv);
  TCanvas *c = new TCanvas("c","distribution of angle",800,600);
  TH2D *h = new TH2D("h","distribution of angle",6*Theta[1],0,1.5*Theta[1],240,-60,60);
  gStyle->SetOptStat(0);
  for(int j=0;j<2;j++)
  {
    double theta0=Theta[j]/180.*TMath::Pi();
    TVector3 p0(Size/2.,Size/2.,Distance[j]);
    TVector3 p1(Size/2.,-Size/2.,Distance[j]);
    TVector3 p2(-Size/2.,-Size/2.,Distance[j]);
    TVector3 p3(-Size/2.,Size/2.,Distance[j]);
    p0.RotateY(theta0);
    p1.RotateY(theta0);
    p2.RotateY(theta0);
    p3.RotateY(theta0);
    TVector3 p(p0);
    TVector3 change(1,1,1);
    double flag=1.;
    int nsteps = N*N+N+1;
    for(int i=0;i<nsteps;++i)
    {
      //cout<<" "<<p.X()<<" "<<p.Y()<<" "<<p.Z()<<endl;
      h->Fill(p.Theta()/TMath::Pi()*180.,p.Phi()/TMath::Pi()*180.);
      if((p-p1).Angle(p2-p1)<eps&&change*(p2-p1)<eps) 
        {change = 1./N*(p2-p1);flag=-1.;}
      else if((p-p0).Angle(p3-p0)<eps&&change*(p3-p0)<eps) 
        {change = 1./N*(p3-p0);flag=1.;}
      else
        change=flag/N*(p1-p0);
      p+=change;
    }
    h->Fill(p.Theta()/TMath::Pi()*180.,p.Phi()/TMath::Pi()*180.);
  }
  h->SetXTitle("theta_lab/deg");
  h->SetYTitle("phi_lab/deg");
  c->cd();
  h->Draw("colz");
  theApp->Run();
  return 0;
}

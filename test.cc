void test()
{
	TCanvas *c1 = new TCanvas("c1","Example",200,10,700,500);
	TH1F *hpx = new TH1F("hpx","px",100,-20,20);
	int kUPDATE = 100;
	for(int i=0;i<250000;i++)
	{
		double px = gRandom->Gaus(0,5);
		hpx->Fill(px);
		hpx->Draw();
		c1->Update();
        if(gSystem->ProcessEvents()) break;
    }

}

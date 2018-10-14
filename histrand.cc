// compile with:  g++ -o hist hist.cc `root-config --cflags --glibs` 

# include <cstdlib> 
# include <iostream> 
# include "TRandom.h"  
# include "TH1.h" 
# include "TF1.h"
# include "TCanvas.h"
# include "TRandom3.h"
# include "TApplication.h"
# include "TMath.h" 
# include <cmath>

 
using namespace std;


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / (RAND_MAX+1.0);
    return fMin + f * (fMax - fMin);
}

double myF(double x)
{
  return TMath::Sin(x);
}


double generator(TRandom3& rand)
{
 double x = rand.Uniform(0, TMath::Pi());
 double y = rand.Uniform(0,1); 
 double f = myF(x);
 if(y<f) return x; 	
 return -1;
}

int main()
{    
  TH1* h = new TH1D("h","histogram Hit and Miss",100,0,TMath::Pi());
  TApplication theApp("App",0,0);
  TCanvas *c1 = new TCanvas("c1","transparent pad",200,10,700,500);
  c1->cd();
  TRandom3 rand;	
  double result=0;
  for(int i = 0; i <10000; i++) {
	result = generator(rand);
        if (result < 0) {
	    i--;
        } else {
	   h->Fill(result);
        }
  }
  h->Draw();
  theApp.Run();
  return 0;
}





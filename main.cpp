#include "AraRunlogAccessor.h"

using namespace std;

int main() {
  // AraRunlogAccessor demonstration :

  // Create a pointer on a class member
  AraRunlogAccessor *myRunLog;
  // first argument is a station number, second run number
  myRunLog = new AraRunlogAccessor(1,10171);
  
  // get info from database: 
  cout << "Run quality: " <<  myRunLog->getRunQuality() << endl;
  cout << "User comment: " <<  myRunLog->getUserComment() << endl;
  cout << "RunStartType: " <<  myRunLog->getRunStartType() << endl;

  // check if run quality is "normal", i.e. appropriate for a general analysis 
  if (myRunLog->isRunNormal()){
    
    cout << "Run quality is normal" << endl;

    // analysis code here .. 

    // TFile *Allfile=new TFile(inFileName);
    // TTree *ceventTree = (TTree*)Allfile->Get("eventTree");

    // RawAtriStationEvent *rawAtriEvPtr=0;
    // AraGeomTool *geom = AraGeomTool::Instance();

    // ceventTree->SetBranchAddress("event",&rawAtriEvPtr);

    // Int_t nument=ceventTree->GetEntries();

    //   for(Int_t ievt=0; ievt<nument; ievt++){

    //     ceventTree->GetEntry(ievt);
    //     ...
    //   }

  }
 
}
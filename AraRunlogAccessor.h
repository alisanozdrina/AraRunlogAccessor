//////////////////////////////////////////////////////////////////////////////
/////  AraRunlogAccessor.h       ARA SQlite Datavese Accessor Class      /////
/////                                                                    /////
/////  Description:                                                      /////
/////     A simple class to retrieve information from ara runlog         /////
//////    Database location: runDataBase2018.sqlite                      /////
//////////////////////////////////////////////////////////////////////////////


#ifndef ARARUNLOGACCESSOR_H
#define ARARUNLOGACCESSOR_H

#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <cstring>

using namespace std;

class AraRunlogAccessor 
{       
      int stationNum, runNum;
   
   public:             

      AraRunlogAccessor(int,int); //constructor
      void printDataBaseEntry(); 
      int isRunNormal(); // returns 1 if run quality is Normal, or there is no entry in database
      string getUserComment(); // returns UserComment section 
      string getRunQuality(); // returns RunQuality section 
      string getRunStartType(); // returns RunStartType section 

      // utility functions
      static int callback(void *data, int argc, char **argv, char **azColName);
      void openDataBase();

   private:

      sqlite3 *db;
      char *zErrMsg = 0;
      sqlite3_stmt *stmt;
      int rc;
      char sql[100];
      const char* data = "Callback function called";

};

#endif //ARARUNLOGACCESSOR_H
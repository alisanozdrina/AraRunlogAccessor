#include "AraRunlogAccessor.h"

AraRunlogAccessor::AraRunlogAccessor(int x,int y): stationNum(x), runNum(y) {}

void AraRunlogAccessor::printDataBaseEntry(){

   openDataBase();

   sprintf(sql, "SELECT * FROM ARA0%d WHERE Run = %d", stationNum, runNum);

   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      //fprintf(stdout, "Operation done successfully\n");
   } 
  sqlite3_close(db);


}

int AraRunlogAccessor::isRunNormal(){

   openDataBase();

   sprintf(sql, "SELECT Quality FROM ARA0%d WHERE Run = %d", stationNum, runNum);

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
      fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }
   string quality;

   while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      quality = (char*)sqlite3_column_text(stmt, 0);
      //cout << "quality is " << quality << endl;
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }

   if (rc != SQLITE_DONE) {
    fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }
   sqlite3_finalize(stmt);


   if ( quality == "Normal" || quality == "" ){
      return 1;
   }
   else{
      return 0;
   }

}

int AraRunlogAccessor::callback(void *data, int argc, char **argv, char **azColName){
   int i;

   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

void AraRunlogAccessor::openDataBase(){

   rc = sqlite3_open("runDataBase2018.sqlite", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      //fprintf(stderr, "Opened database successfully\n");
   }

}

string AraRunlogAccessor::getUserComment(){

   openDataBase();

   sprintf(sql, "SELECT UserComments FROM ARA0%d WHERE Run = %d", stationNum, runNum);


   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
      fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }

   string UserComments;

   
   while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      UserComments = (char*)sqlite3_column_text(stmt, 0);

      //cout << "UserComments  is " << UserComments  << endl;
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }


   if (rc != SQLITE_DONE) {
    fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }
   sqlite3_finalize(stmt);

   return UserComments ;

}

string AraRunlogAccessor::getRunQuality(){

   openDataBase();

   sprintf(sql, "SELECT Quality FROM ARA0%d WHERE Run = %d", stationNum, runNum);

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
      fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }

   string Quality;

   
   while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {

      Quality = (char*)sqlite3_column_text(stmt, 0);

      //cout << "Run Quality is " << Quality << endl;

   }


   if (rc != SQLITE_DONE) {
    fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }
   sqlite3_finalize(stmt);

   return Quality ;

}

string AraRunlogAccessor::getRunStartType(){

   openDataBase();

   sprintf(sql, "SELECT RunStartType FROM ARA0%d WHERE Run = %d", stationNum, runNum);

   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
   if (rc != SQLITE_OK) {
      fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }

   string RunStartType;
   
   while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
      RunStartType = (char*)sqlite3_column_text(stmt, 0);

      //cout << "RunStartType is " << RunStartType  << endl;

   }

   if (rc != SQLITE_DONE) {
    fprintf(stderr,"error: ", sqlite3_errmsg(db));
   }
   sqlite3_finalize(stmt);

   return RunStartType;

}

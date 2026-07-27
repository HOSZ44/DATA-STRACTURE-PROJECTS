#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
#include<windows.h>

MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

int choice, id, cnt = 0 , stop;
char query[1000], name[100],state;
char sector_name[100],cell_name[100], village_name[100],umuganda_time[100];
char password[100];

void connection(), selecting_cell(), select_village(), management(), search();
void login(), record_attendance(),view_attendance(), edit(), delete();

int main(){
 printf("\033[1m\n");
 connection();
 while(1){
     printf("\n\033[32mUMUGANDA ATTENDANCE SYSTEM\033[0m\033[1m\n");
     printf("==========================\n");

     login();

     if(choice == 1){
         while(1){
             system("clear");
             printf("\n\033[32mUMUGANDA ATTENDANCE SYSTEM\033[0m\033[1m\n");
             printf("==========================\n");
             printf("\n\nSigned in as ==\033[35m%s\033[0m\033[1m== user\n",sector_name);
             selecting_cell();
             management();     
             
             while (1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                     if(scanf("%d",&choice) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }

                 if(choice == 1){
                     stop = 1;
                     break;
                    }
                 else if(choice == 0){
                     stop = 0;
                     break;
                 }
                 else{
                     printf("\033[31mInvalid choice. please try again.\033[0m\033[1m\n");
                     continue;
                    }
                }
             if(stop == 1){
                 system("clear");
                 continue;
                }
             else{
                 system("clear");
                 break;
                }
            }
        }
     if( choice == 2){
         while(1){
             system("clear");
             printf("\n\033[32mUMUGANDA ATTENDANCE SYSTEM\033[0m\033[1m\n");
             printf("==========================\n");
             printf("\nSigned in as ==\033[35m%s\033[0m\033[1m== user\n",cell_name);
             select_village();
             management();
             while (1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                 if(scanf("%d",&choice) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }

                 if(choice == 1){
                     stop = 1;
                     break;
                    }
                 else if(choice == 0){
                     stop = 0;
                     break;
                 }
                 else{
                     printf("\033[31mInvalid choice. please try again.\033[0m\033[1m\n");
                     continue;
                    }
                }
             if(stop == 1){
                 system("clear");
                 continue;
                }
             else{
                 system("clear");
                 break;
                }
         
            }
        }

     if(choice == 3){
         while(1){
             system("clear");
             printf("\n\033[32mUMUGANDA ATTENDANCE SYSTEM\033[0m\033[1m\n");
             printf("==========================\n");
             printf("\nSigned in as ==\033[35m%s\033[0m\033[1m== user\n",village_name);
             management();
             while (1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                 if(scanf("%d",&choice) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }

                 if(choice == 1){
                     stop = 1;
                     break;
                    }
                 else if(choice == 0){
                     stop = 0;
                     break;
                 }
                 else{
                     printf("\033[31mInvalid choice. please try again.\033[0m\033[1m\n");
                     continue;
                    }
                }
             if(stop == 1){
                 system("clear");
                 continue;
                }
             else{
                 system("clear");
                 break;
                }
            }
        }
    }
}

void connection(){
 conn = mysql_init(NULL);
 if(conn == NULL){
     printf("error: %s\n",mysql_error(conn));
    }
 if(mysql_real_connect(conn,"localhost","donatDB","cuser","umuganda",3306,NULL,0) == NULL){
     printf("Error: %s\n",mysql_error(conn));
     exit(0);
    }
 printf("connected\n");
}

void login(){
     printf("\n+--------+------------------------+\n");
     printf("| \033[33mOption\033[0m\033[1m |\033[33m     Action\033[0m\033[1m             |\n");
     printf("|--------+------------------------|\n");
     printf("|   1.   | Log in as Sector user  |\n");
     printf("|--------+------------------------|\n");
     printf("|   2    | Log in cell user       |\n");
     printf("|--------+------------------------|\n");
     printf("|   3    | Log in as Village user |\n");
     printf("|--------+------------------------|\n");
     printf("|   0    | Exit                   |\n");
     printf("+--------+------------------------+\n");
 
     while (1){
         printf("\nChoose: ");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         else{
            break;
            }
        }
 while(1){
     if(cnt >=3){
         printf("\n\033[31mtoo many attempts, You are not allowed to login.\033[0m\033[1m\n");
         exit(0);
        }
     switch (choice){
         case 0:
             printf("Exiting ...\n");
             Sleep(1000);
             exit(0);
            break;
         case 1:
             printf("\nRemaining %d attemps.\n\n",3-cnt);
             cnt += 1;
             printf("Enter Name of Sector\n: ");
             scanf(" %[^\n]", sector_name);
             printf("Enter The Password\n: ");
             scanf(" %[^\n]", password);

             sprintf(query,"select * from sector_user " 
                " where name='%s'" 
                " and password='%s'",sector_name,password);
             if(mysql_query(conn,query)){
                 printf("failed to verify: %s\n",mysql_error(conn));
                 exit(0);
                }
             result = mysql_store_result(conn);
             if(result == NULL){
                 printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
                 exit(0);
                }
             row = mysql_fetch_row(result);
             if(row != NULL){
                 printf("Logged in successfuly\n");
                 break;
                }
             else{
                 printf("\033[31mIncorect Password or Sector Name, try again.\033[0m\033[1m");
                 mysql_free_result(result);
                 continue;
                }
            break;
         case 2:
             printf("\nRemaining %d attemps.\n\n",3-cnt);
             cnt += 1;
             printf("Enter Name of Cell\n: ");
             scanf(" %[^\n]", cell_name);
             printf("Enter The Password\n: ");
             scanf(" %[^\n]", password);

             sprintf(query,"select * from cell_user " 
                " where name='%s'" 
                " and password='%s'",cell_name,password);
             if(mysql_query(conn,query)){
                 printf("\033[31mfailed to verify:\033[0m\033[1m %s\n",mysql_error(conn));
                 exit(0);
                }
             result = mysql_store_result(conn);
             if(result == NULL){
                 printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
                 exit(0);
                }
             row = mysql_fetch_row(result);
             if(row != NULL){
                 printf("Logged in successfuly\n");
                 break;
                }
             else{
                 printf("\033[31mIncorect Password or cell Name, try again.\033[0m\033[1m");
                 mysql_free_result(result);
                 continue;
                }
            break;
         
         case 3:
             printf("\nRemaining %d attemps.\n\n",3-cnt);
             cnt += 1;
             printf("Enter Name of village\n: ");
             scanf(" %[^\n]", village_name);
             printf("Enter The Password\n: ");
             scanf(" %[^\n]", password);

             sprintf(query,"select * from village_user " 
                " where name='%s'" 
                " and password='%s'",village_name,password);
             if(mysql_query(conn,query)){
                 printf("\033[31mfailed to verify:\033[0m\033[1m %s\n",mysql_error(conn));
                 exit(0);
                }
             result = mysql_store_result(conn);
             if(result == NULL){
                 printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
                 exit(0);
                }
             row = mysql_fetch_row(result);
             if(row != NULL){
                 printf("Logged in successfuly\n");
                 break;
                }
             else{
                 printf("\n\033[31mIncorect Password or cell Name, try again.\033[0m\033[1m\n");
                 mysql_free_result(result);
                 continue;
                }
            break;
         default:
             printf("\n\033[31minvalid choice, Please try again.\033[0m\033[1m\n");
             continue;
            break;
        }
     break;
    }
}

void selecting_cell(){
 while(1){
     printf("==Select The name of cell==\n\n");
     printf("1. Gasura\n");
     printf("2. kayenzi\n");
     printf("3. Kibirizi\n");

     while (1){
         printf("\nChoose: ");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
             }
         else{
             break;
            }
        }
     switch(choice){
         case 1:
             strcpy(cell_name,"Gasura");
             select_village();
            break;
    
         case 2:
             strcpy(cell_name,"Kayenzi");
             select_village();
            break;
         case 3:
             strcpy(cell_name,"Kibirizi");
             select_village();
            break;
         default:
             printf("\033[31mInvalid choice, please try again.\033[0m\033[1m\n");
             continue;
            break;
        }
     break;
    }
}

void select_village(){
 if(strcmp(cell_name,"Gasura") == 0){
     printf("Select the village\n");
     printf("1. Gafuruguto\n");
     printf("2. Gatoki\n");
     printf("3. Nyabihanga\n");

     while (1){
         printf("\nChoose: ");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         switch(choice){
             case 1:
                 strcpy(village_name,"Gafuruguto");

                break;
             case 2:
                 strcpy(village_name,"Gatoki");
                break;
             case 3:
                 strcpy(village_name,"Nyabihanga");
                break;
             default:
                 printf("invalid choice.\n");
                 continue;
                break;
            }
         break;
        }
    }
  if(strcmp(cell_name,"Kayenzi") == 0){
     printf("Select the village\n");
     printf("1. Gacyamo\n");
     printf("2. Gasasa\n");
     printf("3. Gaseke\n");

     while (1){
         printf("\nChoose: ");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         switch(choice){
             case 1:
                 strcpy(village_name,"Gacyamo");
                break;
             case 2:
                 strcpy(village_name,"Gasasa");
                break;
             case 3:
                 strcpy(village_name,"Gaseke");
                break;
             default:
                 printf("invalid choice.\n");
                 continue;
                break;
            }
         break;
        }
    }
  if(strcmp(cell_name,"Kibirizi") == 0){
     printf("Select the village\n");
     printf("1. Bitaba\n");
     printf("2. Gahoromani\n");
     printf("3. Gishanda\n");

     while (1){
         printf("\nChoose: ");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         switch(choice){
             case 1:
                 strcpy(village_name,"Bitaba");
                break;
             case 2:
                 strcpy(village_name,"Gahoromani");
                break;
             case 3:
                 strcpy(village_name,"Gishanda");
                break;
             default:
                 printf("invalid choice.\n");
                 continue;
                break;
            }
         break;
        }
    }
}

void management(){
 int date,month,year;
 while(1){
     printf("\n+--------+-------------------------+\n");
     printf("| \033[33moption\033[0m\033[1m\033[33m |    \033[33m Action\033[0m\033[1m              |\n");
     printf("|--------+-------------------------|\n");
     printf("|   1.   | Record Attendance       |\n");
     printf("|--------+-------------------------|\n");
     printf("|   2.   | View Attendance Records |\n");
     printf("|--------|-------------------------+\n");
     printf("|   3.   | Edit records            |\n");
     printf("|--------|-------------------------|\n");
     printf("|   4.   | Search person           |\n");
     printf("+--------+-------------------------+\n");
     printf("\nChoose: ");

     if(scanf("%d",&choice) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }
                  while(1){
                 printf("\n\nEnter the date: ");
                 if(scanf("%d",&date) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 printf("Enter the month: ");
                 if(scanf("%d",&month) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 printf("Enter the year: ");
                 if(scanf("%d",&year) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 sprintf(umuganda_time,"Le %d/%d/%d",date,month,year);
                 break;
                }

     switch(choice){
         case 1:
             sprintf(query,"alter table citizen add column `%s` varchar(100) default '--'",umuganda_time);
             if(mysql_query(conn,query)){
                 printf("error, %s",mysql_error(conn));
                 exit(0);
                } 

             record_attendance();

            break;
         case 2:
             view_attendance();
            break;
         case 3:
             edit();
            break;

         case 4:
             search();
            break;
         case 5:
             delete();
            break;
         default:
              printf("\033[31mInvalid choice, please.\033[0m\033[1m\n");
              continue;
            break;
        }
     break;
    }
}

void record_attendance(){
 while(1){
      printf("\n\n==ALL \033[35m%s\033[0m\033[1m CITIZEN==\n\n",village_name);
     sprintf(query,"select c.id,c.name from citizen c inner join villages v on c.vill_id=v.vill_id where v.village_name='%s'",village_name);
     if(mysql_query(conn,query)){
         printf("error, %s", mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
         if(result == NULL){
         printf("error, %s",mysql_error(conn));
         exit(0);
        }

     while((row = mysql_fetch_row(result))){
         printf(" %s. %s. \n",row[0],row[1]);
        }

     printf("\n\nEnter the citizen ID: ");

     if(scanf("%d",&id) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }
     printf("P. Present\n");
     printf("A. Absent\n");
     printf("E. Excuse\n");
     scanf(" %c", &state);

     sprintf(query, "select * from citizen c inner join villages v where c.id= %d and v.village_name='%s'",id,village_name);
     if(mysql_query(conn,query)){
         printf("error, %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror,\033[0m\033[1m %s\n", mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     if(row != NULL){
         sprintf(query, "update citizen set `%s`='%c' where id=%d",umuganda_time,state,id);
         if(mysql_query(conn,query)){
             printf("error, %s\n",mysql_error(conn));
             exit(0);
            }
         else{
             printf("attendance recorded.\n");
            }
        }  
     else{
         printf("\n\033[31mCitizen not found.\033[0m\033[1m\n");
         continue;
        }
     while (1){
         printf("\nPress 1 to continue or 0 to stop recording\n");
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         if(choice == 0){
             stop = 0;
            }
         else if(choice == 1){
             stop = 1;
            }
         else{
             printf("I\033[31mnvalid choice, please try again.\033[0m\033[1m\n");
             continue;
            }
         
         break;
        }
     if(stop == 0){
         break;
        }
     else{
        continue;
     }
     
    }
}

void view_attendance(){
 sprintf(query, "select c.id,c.name,c.`%s` from citizen c inner join villages v on c.vill_id=v.vill_id where v.village_name='%s'",umuganda_time,village_name);
 if(mysql_query(conn,query)){
     printf("\033[31mThere is no records that match.\033[0m\033[1m\n");
     exit(0);
    }
 result = mysql_store_result(conn);
 if(result == NULL){
     printf("error: %s\n",mysql_error(conn));
     exit(0);
    }
 printf("\n==All \033[35m%s\033[0m\033[1m citizen==\n\n",village_name);
 while((row = mysql_fetch_row(result)) != NULL){
     char st[100];
     if(strcmp(row[2],"P") == 0 || strcmp(row[2],"p") == 0){
         strcpy(st,"\033[32mPRESENT\033[0m\033[1m");
        }
     else if(strcmp(row[2],"A") == 0 || strcmp(row[2],"a") == 0){
         strcpy(st,"\033[31mABSENT\033[0m\033[1m");
        }
     else if(strcmp(row[2],"E") == 0 || strcmp(row[2],"e") == 0){
         strcpy(st,"\033[33mEXCUSE\033[0m\033[1m");
        }
     else{
         strcpy(st,"---");
        }
     printf(" %s. %s: [%s].\n",row[0],row[1],st);
    }
}

void edit(){
 view_attendance();
 while (1){
     printf("\n\nEnter the citizen ID: ");

     if(scanf("%d",&id) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }
     printf("P. Present\n");
     printf("A. Absent\n");
     printf("E. Excuse\n");
     scanf(" %c", &state);

     sprintf(query, "select * from citizen c inner join villages v on c.vill_id=v.vill_id where c.id= %d and v.village_name='%s'",id, village_name);
     if(mysql_query(conn,query)){
         printf("error, %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror,\033[0m\033[1m %s\n", mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     if(row != NULL){
         sprintf(query, "update citizen set `%s`='%c' where id=%d",umuganda_time,state,id);
         if(mysql_query(conn,query)){
             printf("error, %s\n",mysql_error(conn));
             exit(0);
            }
         else{
             printf("attendance recorded.\n");
            }
        }  
     else{
         printf("\n\033[31mCitizen not found.\033[0m\033[1m\n");
         continue;
        }
     printf("\nPress 1 to continue or 0 to stop recording\n");

     while(1){
         if(scanf("%d",&choice) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         else{
             break;
            }
        }

      if(choice == 0){
         break;
        }
     else if(choice == 1){
         continue;
        }
     else{
         printf("I\033[31mnvalid choice, please try again.\033[0m\033[1m\n");
         continue;
        }
         
     break;
    } 
}

void delete(){
 printf("\nAre you sure you want to \033[31mdelete\033[0m\033[1m The \033[34m%s\033[0m\033[1m Records??\n",village_name);
 while(1){
     printf("\nY. yes.\n");
     printf("N. no.\n");
     scanf(" %c", &state);

     if( state == 'Y' || state == 'y'){
         sprintf(query, "alter table %s drop column `%s`",village_name,umuganda_time);
         if(mysql_query(conn, query)){
             printf("Failed to delete records.\n");
             printf("\033[31mError: %s\033[0m\033[1m\n",mysql_error(conn));
             exit(0);
            }
         printf("\nAll records of %s deleted.\n",umuganda_time);
         break;
        }
     else if (state == 'N' || state == 'n'){
         break;
        }
     else{
         printf("\n\033[31mInvalid choice, Please try again.\033[0m\033[1m\n");
         continue;
     }
 }
 
}

void search(){
 while (1){
     printf("\n1. Search by ID\n");
     printf("2. search by NAME\n");
     printf("choose: ");
     if(scanf("%d", &choice) != 1){
         printf("Invalid Input, Please try again.\n");
         while(getchar() != '\n');
         continue;
        }
     switch(choice){
         case 1:
             printf("Enter the id: ");
             if(scanf("%d", &id) != 1){
                 printf("Invalid Input, Please try again.\n");
                 while(getchar() != '\n');
                 continue;
                }
             sprintf(query, "select c.id,c.name,c.`%s` from citizen c inner join villages v on c.vill_id=v.vill_id where c.id=%d and v.village_name='%s'",umuganda_time,id,village_name);
             if(mysql_query(conn, query)){
                 printf("error: %s\n", mysql_error(conn));
                 exit(0);
                }
             result = mysql_store_result(conn);
             if(result == NULL){
                 printf("error: %s\n",mysql_error(conn));
                 exit(0);
                }
             row = mysql_fetch_row(result);
             if(row != NULL){
                 printf("%s. %s.  %s.\n",row[0],row[1],row[2]);
                 break;
                }
             printf("\ncitizen not found, please try again.\n");
             continue;
            break;
         case 2:
             printf("Enter the NAME: ");
             scanf(" %[^\n]", name);
             sprintf(query, "select c.id,c.name,c.'%s' from citizen c inner join villages v where c.id='%s' and v.village_name='%s'",name,village_name);
             if(mysql_query(conn, query)){
                 printf("error: %s\n", mysql_error(conn));
                 exit(0);
                }
             result = mysql_store_result(conn);
             if(result == NULL){
                 printf("error: %s\n",mysql_error(conn));
                 exit(0);
                }
             row = mysql_fetch_row(result);
             if(row != NULL){
                 printf("%s. %s.  %s.\n",row[0],row[1],row[2]);
                 break;
                }
             else{
                 printf("\nCitizen not found, Please try again.\n");
                 continue;
                }
            break;
             
        }
     break;
    }
 }
 
 
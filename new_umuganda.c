#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql.h>
#include<windows.h>

MYSQL *conn;
MYSQL_RES *result;
MYSQL_ROW row;

int stop, option, id, s_choice, c_choice, v_choice;
char state, query[1000],password[100], lev_name[100], column[100], c_l_name[100], umuganda_time[40];
void select_villages(), select_sectors(), select_cells(), connection()
     ,display_citizen(), validate_user(), login(), record_attendance(), view_attendance()
     ,edit(), search(), management();;

int main(){
 connection();
 while(1){
     printf("\n\033[32mUMUGANDA ATTENDANCE SYSTEM\033[0m\033[1m\n");
     printf("==========================\n\n");
     printf("\n+--------+------------------------+\n");
     printf("| \033[33mOption\033[0m\033[1m |\033[33m     Action\033[0m\033[1m             |\n");
     printf("|--------+------------------------|\n");
     printf("|   1.   | LOG IN AS SECTOR USER  |\n");
     printf("|--------+------------------------|\n");
     printf("|   2    | LOGIN AS CELL USER     |\n");
     printf("|--------+------------------------|\n");
     printf("|   3    | LOGIN AS VILLAGE USER  |\n");
     printf("|--------+------------------------|\n");
     printf("|   0    | EXIT                   |\n");
     printf("+--------+------------------------+\n");
     printf("\nchoose : ");
     if(scanf("%d",&option) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }

     if(option == 1){
         sprintf(lev_name, "sectors");
         sprintf(column, "sec_id");

         select_sectors();
         validate_user();
         select_cells();
         select_villages();
         display_citizen();
         while(1){
             management();
             while(1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                 if(scanf("%d",&stop) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 else{
                     break;
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
     else if (option == 2){
         sprintf(lev_name, "cells");
         sprintf(column, "cell_id");
         
         printf("\nEnter the name of sector: ");
         scanf(" %[^\n]", c_l_name);

         select_cells();
         validate_user();
         select_villages();
         while(1){
             management();
             while(1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                 if(scanf("%d",&stop) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 else{
                     break;
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
     else if (option == 3){
         sprintf(lev_name, "villages");
         sprintf(column, "vill_id");

         printf("\nEnter the name of cell: ");
         scanf(" %[^\n]", c_l_name);
         select_villages();
         validate_user();
         display_citizen();
         while(1){
             management();
             while(1){
                 printf("\n\n1. Continue.\n");
                 printf("0. Logout.\n\n");
                 printf("\nChoose: ");
                 if(scanf("%d",&stop) != 1){
                     printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
                     while(getchar() != '\n');
                     continue;
                    }
                 else{
                     break;
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
     else if(option == 0){
         printf("exiting.....");
         exit(0);
        }
     else{
         printf("Invalid choice, please try again.\n");
         continue;
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

void select_villages(){
 while(1){
     sprintf(query, "select v.vill_id,v.vill_name from villages v inner join cells c on v.cell_id=c.cell_id where c.cell_name='%s'",c_l_name);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     while((row = mysql_fetch_row(result)) != NULL){
         printf("%s. %s \n",row[0],row[1]);
        }

     printf("\nchoose village: ");
     if(scanf("%d",&v_choice) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }
     sprintf(query, "select * from cells where cell_name='%s'",c_l_name);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     c_choice = atoi(row[0]);

     sprintf(query, "select * from villages v inner join cells c on v.cell_id=c.cell_id where v.vill_id=%d and c.cell_id=%d",v_choice,c_choice);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     id = v_choice;
     if(row != NULL){
         break;
        }
     else{
         printf("\ninvalid choice, please try again.\n");
         continue;
     }
     break;
    }
}

void select_cells(){
 while(1){
     sprintf(query, "select c.cell_id,c.cell_name from cells c inner join sectors s on c.sec_id=s.sec_id where s.sec_name='%s'",c_l_name);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     while((row = mysql_fetch_row(result)) != NULL){
         printf("%s. %s \n",row[0],row[1]);
        }

     printf("\nchoose cell: ");
     if(scanf("%d",&c_choice) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }
     
     
     sprintf(query, "select * from sectors where sec_name='%s'",c_l_name);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     s_choice = atoi(row[0]);


     sprintf(query, "select * from cells c inner join sectors s on c.sec_id=s.sec_id where s.sec_id=%d and c.cell_id=%d",s_choice,c_choice);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     id = c_choice;
     if(row != NULL){
         sprintf(c_l_name, "%s",row[1]);
         break;
        }
     else{
         printf("\ninvalid choice, please again.\n");
         continue;
        }
    }
}

void select_sectors(){
 while(1){
     sprintf(query, "select sec_id,sec_name from sectors");
     if(mysql_query(conn,query)){
         printf("\033[31mfailed to verify:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     while((row = mysql_fetch_row(result)) != NULL){
         printf("%s. %s \n",row[0],row[1]);
        }

     printf("\nchoose sector: ");
     if(scanf("%d",&s_choice) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }

     sprintf(query, "select * from sectors where sec_id=%d",s_choice);
     if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     id = s_choice;
     if(row != NULL){ 
         sprintf(c_l_name, "%s",row[1]);
         break;
        }
     else{
         printf("Selected cell is not valid, please try again.\n");
         continue;
        }
    }
}

void display_citizen(){
 sprintf(query, "select cit_id,cit_name from citizen where vill_id=%d",v_choice);
      if(mysql_query(conn,query)){
         printf("\033[31mfailed to verify:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     printf("\nCITZENS\n");
     printf("=======\n");

     while((row = mysql_fetch_row(result)) != NULL){
         printf("%s. %s \n",row[0],row[1]);
        }
}

void validate_user(){
 printf("\nEnter password: ");
 scanf(" %[^\n]", password);

 sprintf(query, "select * from %s where password='%s' and %s=%d",lev_name,password,column,id);
      if(mysql_query(conn,query)){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     result = mysql_store_result(conn);
     if(result == NULL){
         printf("\033[31merror:\033[0m\033[1m %s\n",mysql_error(conn));
         exit(0);
        }
     row = mysql_fetch_row(result);
     if(row != NULL){
         printf("Logg in success.\n\n");
        }
     else{
         printf("Login failed.\n\n");
         exit(0);
        }
}

void login(){
 while(1){
     printf("\n+--------+------------------------+\n");
     printf("| \033[33mOption\033[0m\033[1m |\033[33m     Action\033[0m\033[1m             |\n");
     printf("|--------+------------------------|\n");
     printf("|   1.   | LOG IN AS SECTOR USER  |\n");
     printf("|--------+------------------------|\n");
     printf("|   2    | LOGIN AS CELL USER     |\n");
     printf("|--------+------------------------|\n");
     printf("|   3    | LOGIN AS VILLAGE USER  |\n");
     printf("|--------+------------------------|\n");
     printf("|   0    | EXIT                   |\n");
     printf("+--------+------------------------+\n");
     printf("\nchoose : ");
     if(scanf("%d",&option) != 1){
         printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
         while(getchar() != '\n');
         continue;
        }

     if(option == 1){
         sprintf(lev_name, "sectors");
         sprintf(column, "sec_id");

         select_sectors();
         validate_user();
         select_cells();
         select_villages();
         display_citizen();
        }
     else if (option == 2){
         sprintf(lev_name, "cells");
         sprintf(column, "cell_id");
         
         printf("\nEnter the name of sector: ");
         scanf(" %[^\n]", c_l_name);

         select_cells();
         validate_user();
         select_villages();
         display_citizen();
        }
     else if (option == 3){
         sprintf(lev_name, "villages");
         sprintf(column, "vill_id");

         printf("\nEnter the name of cell: ");
         scanf(" %[^\n]", c_l_name);
         select_villages();
         validate_user();
         display_citizen();
         record_attendance();
        }
     else if(option == 0){
         printf("exiting.....");
         exit(0);
        }
     else{
         printf("Invalid choice, please try again.\n");
         continue;
        }

    }
}

void record_attendance(){
 while(1){
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

     sprintf(query, "select * from citizen ct inner join villages v on ct.vill_id=v.vill_id where ct.cit_id= %d and v.vill_id=%d",id,v_choice);
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
         while(1){
             sprintf(query, "update citizen set `%s`='%c' where cit_id=%d",umuganda_time,state,id);
             if(mysql_query(conn,query)){
                 printf("error, %s\n",mysql_error(conn));
                 sprintf(query,"alter table citizen add column `%s` varchar(100) default '--'",umuganda_time);
                 if(mysql_query(conn,query)){
                     printf("error, %s",mysql_error(conn));
                     exit(0);
                    } 
                 continue;
                }
             else{
                 printf("attendance recorded.\n");
                 break;
                }
            }
        }  
     else{
         printf("\n\033[31mCitizen not found.\033[0m\033[1m\n");
         continue;
        }
     while (1){
         printf("\nPress 1 to continue or 0 to stop recording\n");
         if(scanf("%d",&option) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         if(option == 0){
             stop = 0;
            }
         else if(option == 1){
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
 sprintf(query, "select ct.cit_id,ct.cit_name,ct.`%s` from citizen ct inner join villages v on ct.vill_id=v.vill_id where ct.vill_id=%d",umuganda_time,v_choice);
 if(mysql_query(conn,query)){
     printf("\033[31mThere is no records that match.\033[0m\033[1m\n");
     exit(0);
    }
 result = mysql_store_result(conn);
 if(result == NULL){
     printf("error: %s\n",mysql_error(conn));
     exit(0);
    }
    
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

     sprintf(query, "select * from citizen ct inner join villages v on ct.vill_id=v.vill_id where ct.cit_id= %d and v.vill_id=%d",id,v_choice);
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
         sprintf(query, "update citizen set `%s`='%c' where cit_id=%d",umuganda_time,state,id);
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
         if(scanf("%d",&option) != 1){
             printf("\033[31mInvalid input, please try again.\033[0m\033[1m\n");
             while(getchar() != '\n');
             continue;
            }
         else{
             break;
            }
        }

      if(option == 0){
         break;
        }
     else if(option == 1){
         continue;
        }
     else{
         printf("I\033[31mnvalid choice, please try again.\033[0m\033[1m\n");
         continue;
        }
         
     break;
    } 
}

void search(){
 while (1){
     printf("\n1. Search by ID\n");
     printf("2. search by NAME\n");
     printf("choose: ");
     if(scanf("%d", &option) != 1){
         printf("Invalid Input, Please try again.\n");
         while(getchar() != '\n');
         continue;
        }
     switch(option){
         case 1:
             printf("Enter the id: ");
             if(scanf("%d", &id) != 1){
                 printf("Invalid Input, Please try again.\n");
                 while(getchar() != '\n');
                 continue;
                }
             sprintf(query, "select ct.cit_id,ct.cit_name,ct.`%s` from citizen ct inner join villages v on ct.vill_id=v.vill_id where ct.cit_id=%d and v.vill_id=%d",umuganda_time,id,v_choice);
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
                 printf("\ncitizen not found, please try again.\n");
                 continue;
                }
            break;
         case 2:
              char name[100];
             printf("Enter the NAME: ");
             scanf(" %[^\n]", name);
             sprintf(query, "select ct.cit_id,ct.cit_name,ct.`%s` from citizen ct inner join villages v on ct.vill_id=v.vill_id where ct.cit_name='%s' and v.vill_id=%d",umuganda_time,name,v_choice);
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
 
void management(){
 int date,month,year;
 while(1){
     printf("\n+--------+-------------------------+\n");
     printf("| \033[33moption\033[0m\033[1m\033[33m |    \033[33m Action\033[0m\033[1m              |\n");
     printf("|--------+-------------------------|\n");
     printf("|   1.   | RECORD ATTENDANCE       |\n");
     printf("|--------+-------------------------|\n");
     printf("|   2.   | VIEW ATTENDANCE RECORDS |\n");
     printf("|--------|-------------------------+\n");
     printf("|   3.   | EDIT RECORDS            |\n");
     printf("|--------|-------------------------|\n");
     printf("|   4.   | SEARCH PERSON           |\n");
     printf("+--------+-------------------------+\n");
     printf("\nChoose: ");

     if(scanf("%d",&option) != 1){
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

     switch(option){
         case 1:
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
         default:
              printf("\033[31mInvalid choice, please.\033[0m\033[1m\n");
              continue;
            break;
        }
     break;
    }
}
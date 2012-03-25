#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sqlite3.h>

#include <arpa/inet.h>

unsigned long ip_to_num(char *str)
{
	unsigned long ip_num;
	unsigned char *ip[4];
	char *temp,t[4];
	int i=0;
	ip_num=inet_network(str);
	if(ip_num == -1)
	{
	    perror("inet_netork");
	    return 0;
	}
	return ip_num;
}
void usage(char *str)
{
	printf("\n\tUsage: %s <filename> the file contains output from traceroute or mtr\n",str);
	printf("\n\n###########################################################################\n");
	printf("%s is a IP address to location tracing tool\n",str);
	printf("Copyright(C) Ashok.s.das@gmail.com, Released under GNU GPL V2\n");
	printf("Currently it uses the output of traceroute or mtr\n");
	printf("For converting output of traceroute and mtr 2 shellscripts are provided\n");
	printf("This application uses maxmind\'s 2012 februry city database in CSV format\n");
	printf("The Sqlite3 is used as database for storing and query purpose\n");
	printf("############################################################################\n");
    	exit(0);
}
typedef struct location{
		    char name[30];
		    char region[20];
		    char country[20];
		    float latitude;
		    float longitude;
		}location;
location *get_location(unsigned long n)
{
	int rc,i,ncols;
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200],locid_str[10];
	const char *tail;
	location *locate;
	rc= sqlite3_open("maxmind.db",&db);
	if(rc)
	{
		printf("Can't open database\n");
		sqlite3_close(db);
		exit(1);
	}
	bzero(sql,200);
	sprintf(sql,"select locid from city_block where startip <= %lu and endip >= %lu ;",n,n);
	rc=sqlite3_prepare(db,sql,strlen(sql),&stmt,&tail);
	if(rc != SQLITE_OK)
	{
		printf("sql error1 %s\n",sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	rc = sqlite3_step(stmt);
	ncols = sqlite3_column_count(stmt);
	while(rc== SQLITE_ROW)
	{
		sprintf(locid_str,"%s",sqlite3_column_text(stmt,0));
		//printf("%s\n",locid_str);
		rc=sqlite3_step(stmt);
	}
	
	sprintf(sql,"select city, region, country, latitude, longitude from city_loc where locid = %s ;",locid_str);
	rc=sqlite3_prepare(db,sql,strlen(sql),&stmt,&tail);
	if(rc != SQLITE_OK)
	{
		printf("sql error2 %s\n",sqlite3_errmsg(db));
		printf("%s\n",tail);
		sqlite3_close(db);
		exit(1);
	}
	locate= (location *) malloc(sizeof(location));
	if(!locate)
	{
		printf("Error: allocating memory\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		exit(1);
	}
	rc = sqlite3_step(stmt);
	ncols = sqlite3_column_count(stmt);
	while(rc== SQLITE_ROW)
	{
		strcpy(locate->name,sqlite3_column_text(stmt,0));
		strcpy(locate->region,sqlite3_column_text(stmt,1));
		strcpy(locate->country,sqlite3_column_text(stmt,2));
		locate->latitude=atof(sqlite3_column_text(stmt,3));
		locate->longitude=atof(sqlite3_column_text(stmt,4));
		rc=sqlite3_step(stmt);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return locate;
}
int is_private_ip(char *ipstr)
{
	if(strncmp(ipstr,"10.",3)==0)
		return 1;
	if(strncmp(ipstr,"127.",4)==0)
		return 1;
	if(strncmp(ipstr,"192.168.",8)==0)
		return 1;
	return 0;
}	
int main(int argc, char *argv[])
{
	FILE *fp;
	location *loc;
	char ipstr[16];
	
	if(argc!=2)
	{
	    usage(argv[0]);
	    exit(1);
	}
	fp=fopen(argv[1],"r");
	if(!fp)
	{
		perror("fopen");
		exit(1);
	}
	printf("IP                City            region  country   latitude  longitude\n");
	printf("=======================================================================\n");
	while(!feof(fp))
	{
		bzero(ipstr,16);
		unsigned long loc_id;
		unsigned long n;
		fscanf(fp,"%s",ipstr);
		if(strlen(ipstr)<7) break;
		printf("%-18s",ipstr);
		if(is_private_ip(ipstr)==1)
		{
			printf("%s : Private IP\n",ipstr);
			continue;
		}
		n=ip_to_num(ipstr);
		//printf("%lu :",n);
		loc=get_location(n);
		printf("%-20s %-4s %-8s %f %f\n",loc->name,loc->region,loc->country,loc->latitude,loc->longitude);
		free(loc);
	}
	fclose(fp);
}


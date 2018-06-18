#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
void usage()
{
 fprintf(stderr, "Usage: cstest EXPRESSION\n");
 exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
  bool FLAG, FLAG2, Nflag = false;
  char cwd[100];
  int opt;
  struct stat file_info, temp;
  getcwd( cwd, sizeof(cwd) );
  strcat(cwd, "/");


 while (1) {
 	while ((opt = getopt(argc, argv, "+Ne:f:d:r:w:x:n:z:")) != -1) {
 		switch (opt) {
 		
	 case 'N':
 	 	  Nflag = true;
		  break;
	
	 case 'e':
		strcat(cwd , optarg);			
		if ( stat( cwd, &file_info) == 0) FLAG = 1;
		else FLAG = 0;
		Nflag = Nflag ^ FLAG;			
		if( !Nflag ){
			if( !FLAG )
	  			fprintf(stderr,"File: %s not found\n",optarg);
		  	else
   	 			fprintf(stderr,"File: %s found\n",optarg);
			exit(EXIT_FAILURE);
			}
		Nflag = false;			
		cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';	
		break;
                 

  	 case 'f':
		strcat(cwd , optarg);
		if ( stat( cwd, &file_info) == 0) FLAG = 1;
                else FLAG = 0;
	 	FLAG2 = ( (file_info.st_mode & S_IFMT) == S_IFREG);     
		Nflag = Nflag ^( FLAG & FLAG2);	
		 if( !Nflag ){
                        if( !FLAG )
                                fprintf(stderr,"File: %s not found\n",optarg);
                        else if ( FLAG && !FLAG2)
                                fprintf(stderr,"File: %s is not a regular file\n",optarg);
			else fprintf(stderr, "File: %s is a regular file\n",optarg);
                        exit(EXIT_FAILURE);
                        }

		Nflag = false;                          
                cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';    
	
		break;

	case 'd':
		strcat(cwd , optarg);
                if ( stat( cwd, &file_info) == 0) FLAG = 1;
                else FLAG = 0;
                FLAG2 = ( (file_info.st_mode & S_IFMT) == S_IFDIR);
                Nflag = Nflag ^( FLAG & FLAG2);
                 if( !Nflag ){
                        if( !FLAG )
                                fprintf(stderr,"File: %s not found\n",optarg);
                        else if ( FLAG && !FLAG2)
                                fprintf(stderr,"File: %s is not a directory\n",optarg);
                        else fprintf(stderr, "File: %s is a directory\n",optarg);
                        exit(EXIT_FAILURE);
                        }

                Nflag = false;                          
                cwd[(strlen(cwd) ) - strlen(optarg)] = '\0'; 
		break;	 
	
	case 'r':
		 strcat(cwd , optarg);
                if ( stat( cwd, &file_info) == 0) FLAG = 1;
                else FLAG = 0;
                FLAG2 = ( file_info.st_mode & S_IRUSR);
                Nflag = Nflag ^( FLAG & FLAG2);
                 if( !Nflag ){
                        if( !FLAG )
                                fprintf(stderr,"File: %s not found\n",optarg);
                        else if ( FLAG && !FLAG2)
                                fprintf(stderr,"File: %s does not have read permission\n",optarg);
                        else fprintf(stderr, "File: %s does have read permission\n",optarg);
                        exit(EXIT_FAILURE);
                        }

                Nflag = false;                          
                cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';   

		break;

	case 'w':
		strcat(cwd , optarg);
                if ( stat( cwd, &file_info) == 0) FLAG = 1;
                else FLAG = 0;
                FLAG2 = ( file_info.st_mode & S_IWUSR);
                Nflag = Nflag ^( FLAG & FLAG2);
                 if( !Nflag ){
                        if( !FLAG )
                                fprintf(stderr,"File: %s not found\n",optarg);
                        else if ( FLAG && !FLAG2)
                                fprintf(stderr,"File: %s does not have write permission\n",optarg);
                        else fprintf(stderr, "File: %s does have write permission\n",optarg);
                        exit(EXIT_FAILURE);
                        }

                Nflag = false;                          
                cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';    
		break;

	case 'x':
		strcat(cwd , optarg);
                if ( stat( cwd, &file_info) == 0) FLAG = 1;
                else FLAG = 0;
                FLAG2 = ( file_info.st_mode & S_IXUSR);
                Nflag = Nflag ^( FLAG & FLAG2);
                 if( !Nflag ){
                        if( !FLAG )
                                fprintf(stderr,"File: %s not found\n",optarg);
                        else if ( FLAG && !FLAG2)
                                fprintf(stderr,"File: %s does not have executable permission\n",optarg);
                        else fprintf(stderr, "File: %s does have executable permission\n",optarg);
                        exit(EXIT_FAILURE);
                        }

                Nflag = false;                          
                cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';    
		break;


	case 'n':
		
		strcat(cwd , argv[optind -3]);	
                if ( !Nflag && stat( cwd, &file_info) == -1) {
			fprintf(stderr, "File: %s not found\n", argv[optind -3]);
			exit(EXIT_FAILURE);
			}
  		else if ( Nflag && stat( cwd, &file_info) == -1) {
			Nflag = 0;
	                cwd[(strlen(cwd) ) - strlen(argv[optind - 3])] = '\0';
			break;
                        }
		cwd[(strlen(cwd) ) - strlen(argv[optind - 3])] = '\0';
		
		strcat(cwd, optarg);
		
	
		if ( !Nflag && (stat( cwd, &temp) == -1)){
			fprintf(stderr, "File: %s not found\n", optarg);
			exit(EXIT_FAILURE);
                	}
		else if ( Nflag && stat( cwd, &temp) == -1) {
                        Nflag = 0;
                        cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';
                        break;
                        }
		
		
		if( !Nflag && (file_info.st_mtime <= temp.st_mtime)){
			fprintf(stderr, "%s modification date is not newer than %s\n", argv[optind -3],optarg);
			exit(EXIT_FAILURE);
			}
		else if( Nflag && (file_info.st_mtime >= temp.st_mtime)  ){
		
			fprintf(stderr, "%s modification date is not older than %s\n", argv[optind -3], optarg);
			exit(EXIT_FAILURE);
			}
		
		Nflag = 0;
		cwd[(strlen(cwd) ) - strlen(optarg)] = '\0';
               
		break;	
		
	case 'z':
		if ( atoi(optarg) == 0) break;
		else if( strcmp(optarg,"") == 0); break;
		exit(EXIT_FAILURE);
			
	case ':':
		  fprintf(stderr, "option -%c requires an argument\n", optopt);
		  usage();
		 break;

	 case '?':
		
	 default:
		  fprintf(stderr, "unrecognized option -%c\n", optopt);
		  usage();
 	  	 }
 		}
 	if (optind >= argc)
 		break;

	 
	 ++optind; 
 }
 exit(EXIT_SUCCESS);
}

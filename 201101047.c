#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define ACC_RIGHT 0644
int flag=0;
void  parse(char *line, char **argv)
{
	while (*line != '\0') {     
		while (*line == ' ' || *line == '\t' || *line == '\n')
			*line++ = '\0';     
		*argv++ = line;          
		while (*line != '\0' && *line != ' ' && 
				*line != '\t' && *line != '\n') 
			line++;             
	}
	*argv = '\0';                 
}
void read_string(int file,char str[])
{
	int nread,i=0;
	char temp[5];
	while (nread = read(file,temp,1) > 0)
	{
		if(temp[0]=='\n' || temp[0]==',')
		{
			str[i]=0;
			return;
		}
		str[i]=temp[0];
		i++;
	}
	str[i]=0;
	return;
}
int main()
{
	/*char strr[100];
	while(1)
	{
		scanf("%s",strr);
		if(strcmp(strr,"megatron201101047")!=0)
		{
		//printf("daq\n");
			continue;
		}
		else
		{
			break;
		}
	}*/
	while(1)
	{
		printf("$--->");
		//getchar();
		char **distinct;int gh;
		char **cond1;
		char **cond2;int wr=0;
		distinct = malloc(sizeof(char*)*50000);
		for(gh=0;gh<50000;gh++)
		{
			distinct[gh] = malloc(sizeof(char)*50000);
		}

		char line[1000];
		scanf("%[^\n]",line);
		if(strcmp(line,"exit")==0)
		{
			break;
		}
		if(strcmp(line,"")==0)
		{
	//	getchar();
			printf("Enter a query\n");
			break;
		}

		char c;int i,j;
		char col[1000][1000];
		//char *pc;
		char pc[512];
		char *arg[100];
		/*for(i=0;i<1000;i++)
		{
			strcpy(*argv,"NULL");	
		}*/
		parse(line, arg);
		int length=0;int col_length=0;
		i=0;char table[1000][1000];int tab_length=0;
		while(arg[length]!=NULL)
		{
			length++;

		}
		i=1;int from_valid=0,select_valid=0;
		if(strcmp(arg[0],"select")==0)
		{
			select_valid=1;
		}
		while(1)
		{
			//printf("cc");
			if(strcmp(arg[i],"from")==0)
			{	from_valid=1;
				break;}
			if(strcmp(arg[i],",")!=0)
			{
			strcpy(col[col_length],arg[i]);	
			col_length=col_length+1;}
			if(i>=length-1)
			{
				break;
			}


			i=i+1;
		}
		if(from_valid==0 || select_valid==0)
		{
		
			//getchar();
			printf("Enter a valid query\n");
			break;
		}
		i=0;
		while(1)
		{
			if(strcmp(arg[i],"|")==0)
			{
				wr=1;
			}
			if(i>=length-1)
			{
				break;
			}

			i=i+1;


		}
		int pp=0;
		char tab_name[100];
		i=0;
		while(1)
		{
		
			if(strcmp(arg[i],"where")==0 )
			{
				break;
			}
			if(strcmp(arg[i],"from")==0)
			{
				pp=1;
				i=i+1;
				continue;
			}
			if(pp==1)
			{
		//		printf("hi\n");
				if(strcmp(arg[i],",")!=0)
				{
					strcpy(table[tab_length],arg[i]);	
					tab_length=tab_length+1;
				}
			
			}
			if(i>=length-1)
			{
				break;
			}
			i=i+1;
		}
	
		int set=0;
		if(tab_length==2)
		{
			set=1;
		}
		char condition[100][100];
		int cond_length=0;
		while(1)
		{

			if(strcmp(arg[i],"where")==0 )
			{
				pp=1;
				i=i+1;
				continue;
			}
			if(pp==1)
			{
				//		printf("hi\n");
				if(strcmp(arg[i],",")!=0)
				{
					strcpy(condition[cond_length],arg[i]);	
					cond_length=cond_length+1;
				}
			}
			if(i>=length-1)
			{
				break;
			}
			i=i+1;
		}


	//	printf("wwrr==%d",wr);
		char write_name[100];pp=0;
		while(1)
		{

			if(wr==1)
			{
			//	printf("wwrr==%d",wr);
				//		printf("hi\n");
				if(strcmp(arg[i],",")!=0)
				{
					strcpy(write_name,arg[i]);	
				//	strcpy(condition[cond_length],argv[i]);	
				//	cond_length=cond_length+1;
				}
			}
			if(i>=length-1)
			{
				break;
			}
			i=i+1;
		}
	//	printf("wr=%d,write_name=%s\n",wr,write_name);


		//	printf("len=%d\n",cond_length);
		//////////////////////////////////////////
		char column[10][20][100],tab[10][100],temp[100];
		int no_tables,no_cols[20],type_cols[5][10];
		int schema=open("schema.txt", O_RDONLY);
		read_string(schema,temp);
		no_tables=atoi(temp);
		for (i = 0; i < no_tables; ++i)
		{
			read_string(schema,tab[i]);
			read_string(schema,temp);
			no_cols[i]=atoi(temp);
			for(j=0;j<no_cols[i];j++)
			{
				read_string(schema,column[i][j]);
				read_string(schema,temp);
				if(strcmp(temp,"int")==0)
					type_cols[i][j]=0;
				else
					type_cols[i][j]=1;
				read_string(schema,temp);
				read_string(schema,temp);
				read_string(schema,temp);
			}
		}
		int table_selected[10];
		for(i=0;i<10;i++)
		{
			table_selected[i]=0;
		}
	//	printf("%s\n",table[0]);
		for(i=0;i<no_tables;i++)
		{
			if(strcmp(table[0],tab[i])==0)
			{
				strcat(tab[i],".csv");
				table_selected[i]=1;
				strcpy(tab_name,tab[i]);
			/*	if(i==0)
					strcpy(tab_name1,tab[i]);
				else
					strcpy(tab_name2,tab[i]);
				if(set==1)
				{
					strcat(tab[1],".csv");
					break;
				}*/
			}
		}
		int column_selected[100][100];
		int condition_selected[100][100];
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				column_selected[i][j]=-1;
			//	condition_selected[i][j]=-1;
			}
		}
		int k=0;int dist=0;	
		for(k=0;k<col_length;k++)
		{	
			for(i=0;i<no_tables;i++)
			{
				for(j=0;j<no_cols[i];j++)
				{
					if(strcmp(col[k],column[i][j])==0)
						column_selected[i][j]=j;
					if(strcmp(col[0],"distinct")==0)
						dist=1;
				}
			}
		}
		int cond_1=0;
		int star=0;
		if(strcmp(col[0],"*")==0)
			star=1;
		if(cond_length>1)
		{
			cond_1=1;
			star=0;
		}
		
		if(strcmp(col[0],"*")==0)
		{
			for(k=0;k<cond_length;k++)
			{	
				for(i=0;i<no_tables;i++)
				{
					for(j=0;j<no_cols[i];j++)
					{
						column_selected[i][j]=j;
					}
				}
			}
		}

		for(k=0;k<cond_length;k++)
		{	
			for(i=0;i<no_tables;i++)
			{
				for(j=0;j<no_cols[i];j++)
				{
					if(strcmp(condition[k],column[i][j])==0)
					{	condition_selected[i][j]=j;}
				}
			}
		}
		int first=-1,second=-1;
		//printf("con=%s\n",condition[0]);
		for(i=0;i<no_tables;i++)
		{
			for(j=0;j<no_cols[i];j++)
			{
				if(strcmp(condition[0],column[i][j])==0)
					first=j;
				if(strcmp(condition[2],column[i][j])==0)
					second=j;
			}
		}
	//	printf("%d\n",second);
	//	printf("first=%d,second=%d\n",first,second);

		if(set==1)
		{
			star=0;}
		/*for(i=0;i<no_tables;i++)
		{
			for(j=0;j<no_cols[i];j++)
			{
				if(strcmp(condition[0],column[i][j])==0)
				{	if(i==0)
					{first=j;}
					else
					{
						second=j;
					}
				}
				if(strcmp(condition[2],column[i][j])==0)
				{	if(i==0)
					{first=j;}
					else
					{
						second=j;
					}
				}
			}
		}*/
		
	//	printf("star=%d\n",star);
	//	printf("first=%d,second=%d",first,second);
		int swap=0;
		if(second<first)
		{
			swap=1;
		}
		/*
		   for(i=0;i<no_tables;i++)
		   {
		   k=0;
		   if(table_selected[i]==1)
		   {
				for(j=0;j<no_cols[i];j++)
				{
					//	printf("hi\n");
					if(condition_selected[i][j]!=-1)
					{
						printf("j=%d,%s\n",condition_selected[i][j],column[i][j]);
					}
				}
			}
		}
		*/
		//   printf("%d\n",col_length);
		int file;
		if(wr==1)
		{
		//	printf("open=%d",wr);
			file = open(write_name, O_WRONLY | O_APPEND | O_CREAT , 0644 );
		}
		int  filedes;   int nread;
		if(set==1)
		{
			strcat(table[0],".csv");
			strcat(table[1],".csv");
			strcpy(tab_name,table[0]);
		}
	//	printf("%s",tab_name);
		if ((filedes = open(tab_name, O_RDONLY)) == -1)
		{
			printf("Couldn't open test1.txt \n");
		} 
		else 
		{
	//		printf("file is open!\n");
		}
		int kk;
		int count=0;char copy[10];
		char array[1000][1000];int ct;
		char cc;int m=0;int n=0;int l1=0,l2=0,b1=0,b2=0;
		char ptc[1000];char tuple[1000][1000];int kl=0;

		while (nread = read(filedes, &cc, 1) > 0)
		{
			if( star==0)   
			{
				
			//	printf("star=%d\n",star);
				for(i=0;i<no_tables;i++)
				{
					k=0;
					if(set==1)
					{
						break;
					}
					if(table_selected[i]==1)
					{
						for(j=0;j<no_cols[i];j++)
						{
							if(column_selected[i][j]==count)
							{

								if(dist!=1)
								{
									if(cond_length<=1)
									{	if(set!=1 && cond_1!=1)
										{
										//	printf("\n%d\n",wr);
											if(wr==1)
											{
												write(file,&cc,1);
											}
											else
											{
												printf("%c",cc);
											}
										}
									}
								}
								else
								{
									distinct[m][n]=cc;
									n=n+1;
								}
							}
						}
					}
				}
				if(cond_1==1 || set==1)
				{
					if(cc!='"' && cc!=',')
					{
						ptc[ct]=cc;
						ct=ct+1;}
				}

				if(cc==',')
				{
					ptc[ct]=0;
					strcpy(tuple[kl],ptc);
					kl=kl+1;
					ct=0;
					count=count+1;
				}
				if(cc=='\n')
				{
					ptc[ct]=0;
					strcpy(tuple[kl],ptc);
					kl=kl+1;

					m=m+1;n=0;
					//printf("kl=%d\n",kl);
					ct=0;
					//	count=0;ll=ll+1;bb=0;
					char ps[100],qs[100];
					if(set==1)
					{
						int y;
						for(y=0;y<kl;y++)
						{
							//printf("tip=%s\n",tuple[y]);
							if(y==first)
							{
								//printf("tuple[%d]=%s\n",y,tuple[y]);
								strcpy(ps,tuple[y]);
							}
						}
					}
				//	printf("ps=%s\n",ps);
					char p1[100];char q1[100];int type_p=0,type_q=0;
					if(cond_1==1 && set!=1)
					{
						//printf("hi\n");
						int p,q,y,hg=0;
						for(y=0;y<kl;y++)
						{
							//printf("%d ",column_selected[i][hg]);
							if(y==first)
							{
								//	printf("first=%d",first);
								p=atoi(tuple[y]);int jk;
								strcpy(p1,tuple[y]);
								for(jk=0;jk<no_tables;jk++)
								{
									if(table_selected[jk]==1)
									{
										type_p=type_cols[jk][y];
									}

								}
							//	if(p==0)
							//	{
							//		strcpy(p1,tuple[y]);
							//	}
								//	printf("tuple[y]=%s\n",tuple[y]);
								//	printf("p=%d y=%d\n",p,y);
							}
							if(y==second)
							{
								q=atoi(tuple[y]);
								strcpy(q1,tuple[y]);
								int jk;
								for(jk=0;jk<no_tables;jk++)
								{
									if(table_selected[jk]==1)
									{
										type_q=type_cols[jk][y];
									}

								}
							}

						}
						if(second==-1)
						{
							if(condition[2][0]!='"')
							{
								q=atoi(condition[2]);
							}
							else
							{
								int kkj;char rh[100];int fg=0;
								int fgh=strlen(condition[2]);
								for(kkj=1;kkj<fgh-1;kkj++)
								{
									rh[fg]=condition[2][kkj];
									fg=fg+1;
								}
								strcpy(q1,rh);
							}
						}
						if(second==-1)
						{
							if(condition[2][0]!='"')
							{
								if((p>=q && strcmp(condition[1],">=")==0) ||  (p>q && strcmp(condition[1],">")==0) ||  (p<=q && strcmp(condition[1],"<=")==0) ||  (p==q && strcmp(condition[1],"=")==0) ||  (p<q && strcmp(condition[1],"<")==0))
								{
									int ml=0;hg=0;
									for(ml=0;ml<kl;ml++)
									{
										for(i=0;i<no_tables;i++)
										{
											if(table_selected[i]==1)
											{
												for(hg=0;hg<no_cols[i];hg++)
												{
													if(strcmp(col[0],"*")!=0)
													{
														//printf("%d ",column_selected[i][hg]);
														if(ml==column_selected[i][hg])
														{
															if(wr==1)
															{
																write(file,tuple[ml],strlen(tuple[ml]));
																write(file," ",1);
															}
															else
															{
																printf("%s",tuple[ml]);
																printf(" ");
															}
														}
													}
											/*		else
													{
														//printf("%d ",column_selected[i][hg]);
														if(wr==1)
														{
															write(file,tuple[ml],strlen(tuple[ml]));
															write(file," ",1);
														}
														else
														{
															printf("%s",tuple[ml]);
															printf(" ");
														}

													}*/

												}
											}
										}
										if(strcmp(col[0],"*")==0)
										{
											if(wr==1)
											{
												write(file,tuple[ml],strlen(tuple[ml]));
												write(file," ",1);
											}
											else
											{
												printf("%s",tuple[ml]);printf(" ");}
										}

									}
									if(wr==1)
									{
										write(file,"\n",1);
									}
									else
									{
										printf("\n");
									}
								}

							}
							else
							{
								if((strcmp(p1,q1)>=0 && strcmp(condition[1],">=")==0) ||  (strcmp(p1,q1)>0 && strcmp(condition[1],">")==0) ||  (strcmp(p1,q1)<=0 && strcmp(condition[1],"<=")==0) ||  (strcmp(p1,q1)==0 && strcmp(condition[1],"=")==0) ||  (strcmp(p1,q1)<0 && strcmp(condition[1],"<")==0))
								{
									int ml=0;hg=0;
									for(ml=0;ml<kl;ml++)
									{
										for(i=0;i<no_tables;i++)
										{
											if(table_selected[i]==1)
											{
												for(hg=0;hg<no_cols[i];hg++)
												{
													//printf("%d ",column_selected[i][hg]);
													if(strcmp(col[0],"*")!=0)
													{
														//printf("%d ",column_selected[i][hg]);
														if(ml==column_selected[i][hg])
														{
															if(wr==1)
															{
																write(file,tuple[ml],strlen(tuple[ml]));
																write(file," ",1);
															}
															else
															{
																printf("%s",tuple[ml]);
																printf(" ");
															}
														}
													}
												/*	else
													{
														//printf("%d ",column_selected[i][hg]);
														if(wr==1)
														{
															write(file,tuple[ml],strlen(tuple[ml]));
															write(file," ",1);
														}
														else
														{
															printf("%s",tuple[ml]);
															printf(" ");
														}

													}*/



												}
											}
										}
										if(strcmp(col[0],"*")==0)
										{
											if(wr==1)
											{
												write(file,tuple[ml],strlen(tuple[ml]));
												write(file," ",1);
											}
											else
											{
												printf("%s",tuple[ml]);printf(" ");}
										}

									}
									if(wr==1)
									{
										write(file,"\n",1);
									}
									else
									{
										printf("\n");
									}

								}
							}
						}

						//printf("%s\n",tuple[y]);
						//	printf("p=%s ",tuple[y}
						//				printf("p=%d,q=%d\n",p,q);
						if((type_p==1 && type_q==1) && second!=-1)
						{
							if((p>=q && strcmp(condition[1],">=")==0) ||  (p>q && strcmp(condition[1],">")==0) ||  (p<=q && strcmp(condition[1],"<=")==0) ||  (p==q && strcmp(condition[1],"=")==0) ||  (p<q && strcmp(condition[1],"<")==0))
							{
								int ml=0;hg=0;
								for(ml=0;ml<kl;ml++)
								{
									for(i=0;i<no_tables;i++)
									{
										if(table_selected[i]==1)
										{
											for(hg=0;hg<no_cols[i];hg++)
											{
												if(strcmp(col[0],"*")!=0)
												{
												//printf("%d ",column_selected[i][hg]);
												if(ml==column_selected[i][hg])
												{
													if(wr==1)
													{
														write(file,tuple[ml],strlen(tuple[ml]));
														write(file," ",1);
													}
													else
													{
													printf("%s",tuple[ml]);
													printf(" ");
													}
												}
												}
											/*	else
												{
													//printf("%d ",column_selected[i][hg]);
														if(wr==1)
														{
															write(file,tuple[ml],strlen(tuple[ml]));
															write(file," ",1);
														}
														else
														{
															printf("%s",tuple[ml]);
															printf(" ");
														}
													
												}*/

											}
										}
									}
									if(strcmp(col[0],"*")==0)
									{
									if(wr==1)
									{
										write(file,tuple[ml],strlen(tuple[ml]));
										write(file," ",1);
									}
									else
									{
										printf("%s",tuple[ml]);printf(" ");}
									}


								}
								if(wr==1)
								{
									write(file,"\n",1);
								}
								else
								{
									printf("\n");
								}
							}
						}
		//				printf("p1=%s,q1=%s\n",p1,q1);
						if( (type_p==0 || type_q==0) && second!=-1)
						{
							if((strcmp(p1,q1)>=0 && strcmp(condition[1],">=")==0) ||  (strcmp(p1,q1)>0 && strcmp(condition[1],">")==0) ||  (strcmp(p1,q1)<=0 && strcmp(condition[1],"<=")==0) ||  (strcmp(p1,q1)==0 && strcmp(condition[1],"=")==0) ||  (strcmp(p1,q1)<0 && strcmp(condition[1],"<")==0))
							{
								int ml=0;hg=0;
								for(ml=0;ml<kl;ml++)
								{
									for(i=0;i<no_tables;i++)
									{
										if(table_selected[i]==1)
										{
											for(hg=0;hg<no_cols[i];hg++)
											{
												//printf("%d ",column_selected[i][hg]);
												if(ml==column_selected[i][hg])
												{
													if(strcmp(col[0],"*")!=0)
													{
														//printf("%d ",column_selected[i][hg]);
														if(ml==column_selected[i][hg])
														{
															if(wr==1)
															{
																write(file,tuple[ml],strlen(tuple[ml]));
																write(file," ",1);
															}
															else
															{
																printf("%s",tuple[ml]);
																printf(" ");
															}
														}
													}
										/*			else
													{
														//printf("%d ",column_selected[i][hg]);
														if(wr==1)
														{
															write(file,tuple[ml],strlen(tuple[ml]));
															write(file," ",1);
														}
														else
														{
															printf("%s",tuple[ml]);
															printf(" ");
														}

													}*/


												}

											}
										}
									}
									if(strcmp(col[0],"*")==0)
									{
										if(wr==1)
										{
											write(file,tuple[ml],strlen(tuple[ml]));
											write(file," ",1);
										}
										else
										{
											printf("%s",tuple[ml]);printf(" ");}
									}

								}
								if(wr==1)
								{
									write(file,"\n",1);
								}
								else
								{
									printf("\n");
								}

							}

						}
						//	printf("\n");

				}
			
				if(set==1)
				{

					int  filede;   int n_read;
					if ((filede = open(table[1], O_RDONLY)) == -1)
					{
						printf("Couldn't open test.txt \n");
					} 
					else 
					{
					//	printf("file is open!\n");
					}
					int count2=0;char copy2[10];
					char array2[1000][1000];int ct2;
					char cc2;int m2=0;int n2=0;
					char ptc2[1000];char tuple2[1000][1000];int kl2=0;

					while (n_read = read(filede, &cc2, 1) > 0)
					{
						if(star==0)
						{
							if(cond_1==1 || set==1)
							{
								if(cc2!='"' && cc2!=',')
								{
									ptc2[ct2]=cc2;
									ct2=ct2+1;}
							}

							if(cc2==',')
							{
								ptc2[ct2]=0;
								strcpy(tuple2[kl2],ptc2);
								kl2=kl2+1;
								ct2=0;
								count2=count2+1;
							}
							if(cc2=='\n')
							{
								
								ptc2[ct2]=0;
								strcpy(tuple2[kl2],ptc2);
								kl2=kl2+1;
								ct2=0;
								//	count=0;ll=ll+1;bb=0;
								int p,q,y,hg=0;
							//	printf("second=%d",second);
								for(y=0;y<kl2;y++)
								{
								//	printf("tuple2[%d]=%s\n",y,tuple2[y]);
									if(y==second)
									{
										//		printf("tuple2[%d]=%s sec=%d\n",y,tuple2[y],second);
										strcpy(qs,tuple2[y]);
									}

								}
							//	printf("qs=%s\n",qs);
								if(strcmp(ps,qs)==0)
								{
									int ml=0;hg=0;
							//		printf("kl--->> %d\n",kl);
									for(ml=0;ml<kl;ml++)
									{
										if(wr==1)
										{
											write(file,tuple[ml],strlen(tuple[ml]));
											write(file," ",1);
										}
										else
										{
											printf("%s",tuple[ml]);
											printf(" ");
										}
									}
									int ml2;
									for(ml2=0;ml2<kl2;ml2++)
									{
										if(wr==1)
										{
											write(file,tuple2[ml2],strlen(tuple2[ml2]));
											write(file," ",1);
										}
										else
										{
											printf("%s",tuple2[ml2]);
											printf(" ");
										}

									}
									if(wr==1)
									{
										write(file,"\n",1);
									}
									else
									{
										printf("\n");
									}



								}
								count2=0;int jkl=0;
								for(jkl=0;jkl<kl2;jkl++)
								{
									strcpy(tuple2[jkl],"");
								}
								kl2=0;
								m=m+1;n=0;
						}



					}
				}



			}
			if(wr!=1 && set!=1 && cond_1!=1 && dist!=1)
				printf("\n");
			if(dist!=1 && wr==1 && cond_1!=1 && dist!=1 && set!=1)	
				write(file,"\n",1);
			count=0;int jkl=0;
			for(jkl=0;jkl<kl;jkl++)
			{
				strcpy(tuple[jkl],"");
			}
			kl=0;

		}
	}
	else
	{
		//	printf("hi\n");
		if(wr==1){
			write(file,&cc,1);}
		else
		{
			printf("%c",cc);
		}

	}

}
//	printf("%d\n",l1);
/*	for(i=0;i<l1;i++)
	{
	int p,q,r;
	p=atoi(cond1[i]);
	q=atoi(cond2[i]);
	if(p==0 && q==0)
	{
	if(swap==0)
	{

//	r=strcmp(cond1[i],cond2[i]);
if(p>q)
{	printf("%s\n",distinct[i]);}
}
else
{
//	r=strcmp(cond2[i],cond1[i]);
if(q<p)
{
printf("%s\n",distinct[i]);
}
}
}
}
//int flag=0;
//for(j=0;j<i;j++)
//	{
//		if(strcmp(distinct[i],distinct[j])==0)
//			flag=1;
//	}
//	if(flag!=1){
//		write(file,distinct[i],strlen(distinct[i]));
//		write(file,"\n",1);
//	}

 */	//	printf("%s\n",cond1[i]);}

if(dist==1)
{
	for(i=0;i<m;i++)
	{
		int flag=0;
		for(j=0;j<i;j++)
		{
			if(strcmp(distinct[i],distinct[j])==0)
				flag=1;
		}
		if(flag!=1){
			if(wr==1)
			{
			//		printf("%s\n",distinct[i]);
			write(file,distinct[i],strlen(distinct[i]));
			write(file,"\n",1);}
			else
			{
				printf("%s\n",distinct[i]);
			}
		}
	}
}

getchar();}

return 0;
}

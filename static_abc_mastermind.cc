#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

using namespace std;

int numvec (int length, int *vec1, int *vec2)
//  outputs in how much components two vectors with length components are equal
  {
	int i;
	int numeq=0; 

  for (i=0; i<length; i++)
    {
		if (vec1[i] == vec2[i])
		  numeq++;
		}

	return numeq;
	}

int strategy_check (int p, int questions, int pexit, int* cvec, int **strategy)
//  checks if a given startegy is feasible
	{
	int i,j,l,r,s,t; // count variables
	int iaux; // auxiliary variable
	int optstrat; // optimality of strategy
	int numsec; // number of secrets
  int counter; // count variable

	int *auxvec;

	int **answermat;
	int **pmat;


  numsec = 1;
	for (j=0; j<p; j++)
		numsec *= cvec[j];

  auxvec = (int*) malloc(sizeof(int) * numsec);

  answermat = (int**) malloc(sizeof(int*) * numsec);
  pmat = (int**) malloc(sizeof(int*) * numsec);

  for (s=0; s<numsec; s++)
	  answermat[s] = (int*) malloc(sizeof(int) * questions);

  for (s=0; s<numsec; s++)
	  pmat[s] = (int*) malloc(sizeof(int) * p);

  optstrat = 1;

	counter = 0;
	// creates for each possible secret an anwer vector

	for (s=0; s<numsec; s++)
		{
		for (j=0; j<p; j++)
			auxvec[j] = 0;

		iaux = s;
		j=p-1;
		while (j>=0)
			{
			auxvec[j] = iaux % cvec[j];
			iaux /= cvec[j];
			j--;
			}

		for (j=0; j<p; j++)
			pmat[counter][j] = auxvec[j];

		for (i=0; i<questions; i++)
			answermat[counter][i] = numvec(p, strategy[i], pmat[counter]);

    counter++;
		}

	// checks whether two different possibel secrets have the same answer vector 
	for (s=0; s<numsec; s++)
    {
		for (t=s+1; t<numsec; t++)
      {
			if (numvec(questions,answermat[s],answermat[t]) == questions)
				{
				optstrat = 0;
				if (optstrat == 0 && pexit == 1)
					{
					cout << "Strategy is not feasible." << endl;
					cout << "First possible secret: ";
					for (j=0; j<p; j++)
						cout << pmat[s][j]+1 << " ";
					cout << endl; 

					cout << "Answers: ";
					for (i=0; i<questions; i++)
						cout << answermat[s][i] << " ";
					cout << endl; 
					cout << endl; 
					cout << "Second possible secret: ";

					for (j=0; j<p; j++)
						cout << pmat[t][j]+1 << " "; 
						cout << endl; 

					cout << "Answers: ";
					for (i=0; i<questions; i++)
							cout << answermat[t][i] << " "; 
					cout << endl; 
					cout << endl; 
					exit(1);
					}
				else
				  {
					s = numsec;
					break;
					}
			  }
			}

    }

	if (optstrat == 1)
		cout << "Strategy is feasible." << endl;


  free (auxvec);

  for (s=0; s<numsec; s++)
	   free (answermat[s]);
	free (answermat);

  for (s=0; s<numsec; s++)
	   free (pmat[s]);
	free (pmat);

	return optstrat;
  }

int main (int argc, char **argv)
  {
	int s,t,u,v,w,x,y,z,a,b,d,e,f,g,h,i,j,k,l; // count variables
	int start; // count variable
	int maxvaluea, maxvalueb, maxvaluec, maxvalued, maxvaluee, maxvaluef;
	int maxvalueg, maxvalueh, maxvaluei, maxvaluej, maxvaluek, maxvaluel;
	int maxvaluem, maxvaluen, maxvalueo, maxvaluep; 
	// variables to make sure that the next entry in a column is always
	// at most the largest previous entry plus 1
	int optstrat; // optimaility of strategy
	int p; // number of pegs
	int questions; // number of questions
	int version; // version of the algorithm
	int counter; // count variables
	int *cvec; // color vector 
	int **strategy; // strategy vector
  char* filename; 
  FILE* fname;

	p = 3;
	questions = 3;
  version = 0;

  filename = (char*) malloc(sizeof(char) * 100);

  for (start = 1; start < argc; start++)
		{    
		if (*argv[start] == '-') 
			{    
			char *ep; 
			char *sc = argv[start] + 1; 
			
			while (*sc)
				{
				switch (*sc++)
				  {
					case 'v': 
					  version = strtoul(sc, &ep, 10); 
					  if (ep > sc)
							sc = ep; 
					break;
          }
				}
			}
		else
			strcpy (filename,argv[start]);
		}	

  switch (version)
	  {
		case 0:
			if (fname = fopen (filename,"r"))
				{
				}
			else
				{
				cout << "Error 1" << endl;
				cout << "File ``" << filename << "`` cannot be opened." << endl;
				exit(1);
				}

			fscanf (fname,"%d \n", &p);

			cvec = (int*) malloc(sizeof(int) * p);

			for (j=0; j<p; j++)
				fscanf (fname,"%d \n", &cvec[j]);

			fscanf (fname,"%d \n", &questions);
	  break;
		case 1: // 3 3 4 4
		case 2: 
		case 3: // 3 4 4 4
		case 4: 
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 4;
			cvec[0] = 3;
			if (version == 1 || version == 2)
				cvec[1] = 3;
			else
				cvec[1] = 4;
			cvec[2] = 4;
    break;
		case 5: // 4 4 5 5
		case 6: 
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 5;
			cvec[0] = 4;
			cvec[1] = 4;
			cvec[2] = 5;
    break;
		case 7: // 4 4 6 6
		case 8: 
		case 9: // 4 5 6 6
		case 10: 
		case 11: // 4 5 5 6
		case 12: 
		case 13: 
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 6;
			cvec[0] = 4;

			if (version == 7 || version == 8)
				cvec[1] = 4;
			else
				cvec[1] = 5;

			if (version == 10 || version == 11 || version == 12)
				cvec[2] = 5;
			else
				cvec[2] = 6;
    break;
		case 14: // 4 6 6 7
		case 15: 
		case 16: 
		case 17: // 5 5 6 7
		case 18: 
		case 19: 
		case 20: // 5 6 6 7
		case 21: 
		case 22: 
		case 23: // 5 5 7 7
		case 24: 
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 7;

			if (version == 14 || version == 15 || version == 16)
				cvec[0] = 4;
			else
				cvec[0] = 5;

			if (version == 17 || version == 18 || version == 19 
			    || version == 23 || version == 24)
				cvec[1] = 5;
			else
				cvec[1] = 6;

			if (version == 23 || version == 24)
				cvec[2] = 7;
			else
				cvec[2] = 6;
    break;
		case 25: // 5 5 8 8
		case 26: 
		case 27: // 5 6 7 8
		case 28: 
		case 29: 
		case 30: // 5 6 8 8
		case 31: 
		case 32: // 5 7 7 8
		case 33: 
		case 34:  
		case 35: // 6 6 7 8
		case 36: 
		case 37:  
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 8;

			if (version == 35 || version == 36 || version == 37)
				cvec[0] = 6;
			else
				cvec[0] = 5;

			if (version == 25 || version == 26) 
				cvec[1] = 5;
			else
				if (version == 32 || version == 33 || version == 34) 
					cvec[1] = 7;
				else
					cvec[1] = 6;

			if (version == 25 || version == 26 || version == 30 || version == 31)
				cvec[2] = 8;
			else
				cvec[2] = 7;
    break;
		case 38: // 6 6 8 9
		case 39: 
		case 40: 
		case 41: // 6 7 7 9
		case 42: 
		case 43: 
		case 44: 
		case 45: 
		case 46: // 6 6 9 9
		case 47: 
		case 48: // 6 7 8 9
		case 49: 
		case 50: 
			p=3;
			cvec = (int*) malloc(sizeof(int) * p);
			questions = 9;

			if (version == 38 || version == 39 || version == 40
			    || version == 46 || version == 47) 
				cvec[1] = 6;
			else
				cvec[1] = 7;

			if (version == 41 || version == 42 || version == 43 || version == 44 || version == 45)
				cvec[2] = 7;
			else
			  if (version == 46 || version == 47) 
					cvec[2] = 9;
		    else
					cvec[2] = 8;
    break;
		}

	strategy = (int**) malloc(sizeof(int*) * questions);

	for (i=0; i<questions; i++)
		strategy[i] = (int*) malloc(sizeof(int) * p);

  switch (version)
	  {
		case 0:
			{
			for (i=0; i<questions; i++)
				{
				for (j=0; j<p; j++)
					{
					fscanf (fname,"%d \n", &strategy[i][j]);
					strategy[i][j]--;
					if (strategy[i][j] > cvec[j]-1 || strategy[i][j] < 0) 
						{
						cout << "Error 2" << endl;
						cout << "In (" << i+1 << ", " << j+1 << ") there is the entry " << 
						strategy[i][j] << "." << endl; 
						cout << "At most " <<  cvec[j] << " is allowed" << endl; 
						exit(1);
						}
					}
				}	
			fclose (fname);
			optstrat = strategy_check (p,questions,1,cvec,strategy);
			}
	  break;
		case 1: 
		case 2: 
		case 3: 
		case 4: 
			strategy[0][0] = 0;
			strategy[0][1] = 0;
			strategy[0][2] = 0;
			strategy[1][2] = 1;
			strategy[2][2] = 2;

			if (version == 1 || version == 3)
				strategy[3][2] = 2;
      else
				strategy[3][2] = 3;

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (s+2,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (max(s,t)+2,cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2,cvec[1]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[1][1] = v;

							maxvaluee = min (v+2,cvec[1]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[2][1] = w;

								maxvaluef = min (max(v,w)+2,cvec[1]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[3][1] = x;
									optstrat = strategy_check (p,questions,0,cvec,strategy);
									if (optstrat == 1)
										{
										cout << "Feasible streategy found" << endl;
										exit(1); 
										}
										
									if (optstrat == 1)
										{
										cout << "vec: ";
										cout  << s << " ";
										cout  << t << " ";
										cout  << u << " ";
										cout  << v << " ";
										cout  << w << " ";
										cout  << x << " ";
										cout << endl;
										exit(1); 
										}
									}
								}
							}
						}
					}
			  }		
		break;
		case 5: 
		case 6: 
			strategy[0][0] = 0;
			strategy[0][1] = 0;
			strategy[0][2] = 0;
			strategy[1][2] = 1;
			strategy[2][2] = 2;
			strategy[3][2] = 3;

      if (version == 5)
				strategy[4][2] = 3;
      else
				strategy[4][2] = 4;

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (2+s,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (2+max(s,t),cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2+max(s,max(t,u)),cvec[0]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[4][0] = v;

							maxvaluee = min (2,cvec[1]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[1][1] = w;

								maxvaluef = min (2+max(v,w),cvec[1]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[2][1] = x;

									maxvalueg = min (2+max(v,max(w,x)),cvec[1]);
									for (y=0; y<maxvalueg; y++)
										{
										strategy[3][1] = y;

										maxvalueh = min (2+max(v,max(w,max(x,y))),cvec[1]);
										for (z=0; z<maxvalueh; z++)
											{
											strategy[4][1] = z;
											optstrat = strategy_check (p,questions,0,cvec,strategy);
											if (optstrat == 1)
												{
												cout << "Feasible streategy found" << endl;
												exit(1); 
											  }
											}
										}
									}
								}
							}
						}
					}
			  }		
		break;
		case 7: 
		case 8: 
		case 9: 
		case 10: 
		case 11: 
		case 12: 
		case 13: 
			if (version == 7 || version == 9 || version == 11)
			  {
				strategy[0][0] = 0;
				strategy[0][1] = 0;
				strategy[0][2] = 0;
				strategy[1][2] = 1;
				strategy[2][2] = 2;
				strategy[3][2] = 3;
				strategy[4][2] = 4;
				strategy[5][2] = 4;
        }
			else	
				if (version == 8 || version == 10)
					{
					strategy[0][0] = 0;
					strategy[0][1] = 0;
					strategy[0][2] = 0;
					strategy[1][2] = 1;
					strategy[2][2] = 2;
					strategy[3][2] = 3;
					strategy[4][2] = 4;
					strategy[5][2] = 5;
					}
				else
				  {
					if (version == 12)
					  {
						strategy[0][0] = 0;
						strategy[0][1] = 0;
						strategy[0][2] = 0;
						strategy[1][2] = 1;
						strategy[2][2] = 2;
						strategy[3][2] = 3;
						strategy[4][2] = 3;
						strategy[5][2] = 3;
					  }
					else
					  {
						if (version == 13)
							{
							strategy[0][0] = 0;
							strategy[0][1] = 0;
							strategy[0][2] = 0;
							strategy[1][2] = 1;
							strategy[2][2] = 2;
							strategy[3][2] = 2;
							strategy[4][2] = 3;
							strategy[5][2] = 3;
							}
						}
					}

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (2+s,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (2+max(s,t),cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2+max(s,max(t,u)),cvec[0]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[4][0] = v;

							maxvaluee = min (2+max(s,max(t,max(u,w))),cvec[0]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[5][0] = w;

								maxvaluef = min (2,cvec[1]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[1][1] = x;

									maxvalueg = min (2+x,cvec[1]);
									for (y=0; y<maxvalueg; y++)
										{
										strategy[2][1] = y;

										maxvalueh = min (2+max(x,y),cvec[1]);
										for (z=0; z<maxvalueh; z++)
											{
											strategy[3][1] = z;

											maxvaluei = min (2+max(x,max(y,z)),cvec[1]);
											for (a=0; a<maxvaluei; a++)
												{
												strategy[4][1] = a;

												maxvaluej = min (2+max(x,max(y,max(z,a))),cvec[1]);
												for (b=0; b<maxvaluej; b++)
													{
													strategy[5][1] = b;
													optstrat = strategy_check (p,questions,0,cvec,strategy);
													if (optstrat == 1)
														{
														cout << "Feasible streategy found" << endl;
														exit(1); 
														}
											    }
											  }
											}
										}
									}
								}
							}
						}
					}
				}
		break;
		case 14: 
		case 15: 
		case 16: 
		case 17: 
		case 18: 
		case 19: 
		case 20: 
		case 21: 
		case 22: 
		case 23: 
		case 24: 
			if (version == 14 || version == 17 || version == 20 || version == 23)
			  {
				strategy[0][0] = 0;
				strategy[0][1] = 0;
				strategy[0][2] = 0;
				strategy[1][2] = 1;
				strategy[2][2] = 2;
				strategy[3][2] = 3;
				strategy[4][2] = 4;
				strategy[5][2] = 5;
				strategy[6][2] = 5;
        }
			else	
				if (version == 15 || version == 18 || version == 21)
					{
					strategy[0][0] = 0;
					strategy[0][1] = 0;
					strategy[0][2] = 0;
					strategy[1][2] = 1;
					strategy[2][2] = 2;
					strategy[3][2] = 3;
					strategy[4][2] = 3;
					strategy[5][2] = 4;
					strategy[6][2] = 4;
					}
				else
				  {
					if (version == 16 || version == 19 || version == 22)
					  {
						strategy[0][0] = 0;
						strategy[0][1] = 0;
						strategy[0][2] = 0;
						strategy[1][2] = 1;
						strategy[2][2] = 2;
						strategy[3][2] = 3;
						strategy[4][2] = 4;
						strategy[5][2] = 4;
						strategy[6][2] = 4;
					  }
					else
					  {
						if (version == 24)
							{
							strategy[0][0] = 0;
							strategy[0][1] = 0;
							strategy[0][2] = 0;
							strategy[1][2] = 1;
							strategy[2][2] = 2;
							strategy[3][2] = 3;
							strategy[4][2] = 4;
							strategy[5][2] = 5;
							strategy[6][2] = 6;
						  }
						}
					}

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (2+s,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (2+max(s,t),cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2+max(s,max(t,u)),cvec[0]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[4][0] = v;

							maxvaluee = min (2+max(s,max(t,max(u,v))),cvec[0]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[5][0] = w;

								maxvaluef = min (2+max(s,max(t,max(u,max(v,w)))),cvec[0]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[6][0] = x;

									maxvalueg = min (2,cvec[1]);
									for (y=0; y<maxvalueg; y++)
										{
										strategy[1][1] = y;

										maxvalueh = min (2+y,cvec[1]);
										for (z=0; z<maxvalueh; z++)
											{
											strategy[2][1] = z;

											maxvaluei = min (2+max(y,z),cvec[1]);
											for (a=0; a<maxvaluei; a++)
												{
												strategy[3][1] = a;

												maxvaluej = min (2+max(y,max(z,a)),cvec[1]);
												for (b=0; b<maxvaluej; b++)
													{
													strategy[4][1] = b;

													maxvaluek = min (2+max(y,max(z,max(a,b))),cvec[1]);
													for (d=0; d<maxvaluek; d++)
														{
														strategy[5][1] = d;

														maxvaluel = min (2+max(y,max(z,max(a,max(b,d)))),cvec[1]);
														for (e=0; e<maxvaluel; e++)
															{
															strategy[6][1] = e;
															optstrat = strategy_check (p,questions,0,cvec,strategy);
															if (optstrat == 1)
																{
																cout << "Feasible streategy found" << endl;
																exit(1); 
																}
															}
											      }
													}
											  }
											}
										}
									}
								}
							}
						}
					}
				}
		break;
		case 25: 
		case 26: 
		case 27: 
		case 28: 
		case 29: 
		case 30: 
		case 31: 
		case 32: 
		case 33: 
		case 34: 
		case 35: 
		case 36: 
		case 37: 
			if (version == 25 || version == 27 || version == 30 
			    || version == 32 || version == 35)
			  {
				strategy[0][0] = 0;
				strategy[0][1] = 0;
				strategy[0][2] = 0;
				strategy[1][2] = 1;
				strategy[2][2] = 2;
				strategy[3][2] = 3;
				strategy[4][2] = 4;
				strategy[5][2] = 5;
				strategy[6][2] = 6;
				strategy[7][2] = 6;
        }
			else	
				if (version == 28 || version == 33 || version == 36)
					{
					strategy[0][0] = 0;
					strategy[0][1] = 0;
					strategy[0][2] = 0;
					strategy[1][2] = 1;
					strategy[2][2] = 2;
					strategy[3][2] = 3;
					strategy[4][2] = 4;
					strategy[5][2] = 4;
					strategy[6][2] = 5;
					strategy[7][2] = 5;
					}
				else
				  {
					if (version == 29 || version == 34 || version == 37)
					  {
						strategy[0][0] = 0;
						strategy[0][1] = 0;
						strategy[0][2] = 0;
						strategy[1][2] = 1;
						strategy[2][2] = 2;
						strategy[3][2] = 3;
						strategy[4][2] = 4;
						strategy[5][2] = 5;
						strategy[6][2] = 5;
						strategy[7][2] = 5;
					  }
					else
					  {
						if (version == 26 || version == 31)
							{
							strategy[0][0] = 0;
							strategy[0][1] = 0;
							strategy[0][2] = 0;
							strategy[1][2] = 1;
							strategy[2][2] = 2;
							strategy[3][2] = 3;
							strategy[4][2] = 4;
							strategy[5][2] = 5;
							strategy[6][2] = 6;
							strategy[7][2] = 7;
						  }
						}
					}

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (2+s,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (2+max(s,t),cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2+max(s,max(t,u)),cvec[0]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[4][0] = v;

							maxvaluee = min (2+max(s,max(t,max(u,v))),cvec[0]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[5][0] = w;

								maxvaluef = min (2+max(s,max(t,max(u,max(v,w)))),cvec[0]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[6][0] = x;

									maxvalueg = min (2+max(s,max(t,max(u,max(v,max(w,x))))),cvec[0]);
									for (y=0; y<maxvalueg; y++)
										{
										strategy[7][0] = y;

										maxvalueh = min (2,cvec[1]);
										for (z=0; z<maxvalueh; z++)
											{
											strategy[1][1] = z;

											maxvaluei = min (2+z,cvec[1]);
											for (a=0; a<maxvaluei; a++)
												{
												strategy[2][1] = a;

												maxvaluej = min (2+max(z,a),cvec[1]);
												for (b=0; b<maxvaluej; b++)
													{
													strategy[3][1] = b;

													maxvaluek = min (2+max(z,max(a,b)),cvec[1]);
													for (d=0; d<maxvaluek; d++)
														{
														strategy[4][1] = d;

														maxvaluel = min (2+max(z,max(a,max(b,d))),cvec[1]);
														for (e=0; e<maxvaluel; e++)
															{
															strategy[5][1] = e;

															maxvaluem = min (2+max(z,max(a,max(b,max(d,e)))),cvec[1]);
															for (f=0; f<maxvaluem; f++)
																{
																strategy[6][1] = f;

																maxvaluen = min (2+max(z,max(a,max(b,max(d,max(e,f))))),cvec[1]);
																for (g=0; g<maxvaluen; g++)
																	{
																	strategy[7][1] = g;

																	optstrat = strategy_check (p,questions,0,cvec,strategy);
																	if (optstrat == 1)
																		{
																		cout << "Feasible streategy found" << endl;
																		exit(1); 
																	  }
																	}
																}
															}
														}
												  }
											  }
											}
										}
									}
								}
							}
						}
					}
				}
		break;
		case 41: 
		case 42: 
		case 43: 
		case 44: 
		case 45: 
		case 46: 
		case 47: 
		case 48: 
		case 49: 
		case 50: 
			if (version == 38 || version == 46 || version == 48)
			  {
				strategy[0][0] = 0;
				strategy[0][1] = 0;
				strategy[0][2] = 0;
				strategy[1][2] = 1;
				strategy[2][2] = 2;
				strategy[3][2] = 3;
				strategy[4][2] = 4;
				strategy[5][2] = 5;
				strategy[6][2] = 6;
				strategy[7][2] = 7;
				strategy[8][2] = 7;
        }
			else	
				if (version == 39 || version == 41 || version == 49)
					{
					strategy[0][0] = 0;
					strategy[0][1] = 0;
					strategy[0][2] = 0;
					strategy[1][2] = 1;
					strategy[2][2] = 2;
					strategy[3][2] = 3;
					strategy[4][2] = 4;
					strategy[5][2] = 5;
					strategy[6][2] = 5;
					strategy[7][2] = 6;
					strategy[8][2] = 6;
					}
				else
				  {
					if (version == 40 || version == 42 || version == 50)
					  {
						strategy[0][0] = 0;
						strategy[0][1] = 0;
						strategy[0][2] = 0;
						strategy[1][2] = 1;
						strategy[2][2] = 2;
						strategy[3][2] = 3;
						strategy[4][2] = 4;
						strategy[5][2] = 5;
						strategy[6][2] = 6;
						strategy[7][2] = 6;
						strategy[8][2] = 6;
					  }
					else
					  {
						if (version == 47)
							{
							strategy[0][0] = 0;
							strategy[0][1] = 0;
							strategy[0][2] = 0;
							strategy[1][2] = 1;
							strategy[2][2] = 2;
							strategy[3][2] = 3;
							strategy[4][2] = 4;
							strategy[5][2] = 5;
							strategy[6][2] = 6;
							strategy[7][2] = 7;
							strategy[8][2] = 8;
						  }
						else 
							if (version == 43)
								{
								strategy[0][0] = 0;
								strategy[0][1] = 0;
								strategy[0][2] = 0;
								strategy[1][2] = 1;
								strategy[2][2] = 2;
								strategy[3][2] = 3;
								strategy[4][2] = 3;
								strategy[5][2] = 4;
								strategy[6][2] = 4;
								strategy[7][2] = 5;
								strategy[8][2] = 5;
								}
							else 
								if (version == 44)
									{
									strategy[0][0] = 0;
									strategy[0][1] = 0;
									strategy[0][2] = 0;
									strategy[1][2] = 1;
									strategy[2][2] = 2;
									strategy[3][2] = 3;
									strategy[4][2] = 4;
									strategy[5][2] = 4;
									strategy[6][2] = 5;
									strategy[7][2] = 5;
									strategy[8][2] = 5;
									}
								else 
									if (version == 45)
										{
										strategy[0][0] = 0;
										strategy[0][1] = 0;
										strategy[0][2] = 0;
										strategy[1][2] = 1;
										strategy[2][2] = 2;
										strategy[3][2] = 3;
										strategy[4][2] = 4;
										strategy[5][2] = 5;
										strategy[6][2] = 5;
										strategy[7][2] = 5;
										strategy[8][2] = 5;
										}
						}
					}

			counter=0;

			maxvaluea = min (2,cvec[0]);
			for (s=0; s<maxvaluea; s++)
				{
				strategy[1][0] = s;

				maxvalueb = min (2+s,cvec[0]);
				for (t=0; t<maxvalueb; t++)
					{
					strategy[2][0] = t;

					maxvaluec = min (2+max(s,t),cvec[0]);
					for (u=0; u<maxvaluec; u++)
						{
						strategy[3][0] = u;

						maxvalued = min (2+max(s,max(t,u)),cvec[0]);
						for (v=0; v<maxvalued; v++)
							{
							strategy[4][0] = v;

							maxvaluee = min (2+max(s,max(t,max(u,v))),cvec[0]);
							for (w=0; w<maxvaluee; w++)
								{
								strategy[5][0] = w;

								maxvaluef = min (2+max(s,max(t,max(u,max(v,w)))),cvec[0]);
								for (x=0; x<maxvaluef; x++)
									{
									strategy[6][0] = x;

									maxvalueg = min (2+max(s,max(t,max(u,max(v,max(w,x))))),cvec[0]);
									for (y=0; y<maxvalueg; y++)
										{
										strategy[7][0] = y;

										maxvalueh = min (2+max(s,max(t,max(u,max(v,max(w,max(x,y)))))),cvec[0]);
										for (z=0; z<maxvalueh; z++)
											{
											strategy[8][0] = z;

											maxvaluei = min (2,cvec[1]);
											for (a=0; a<maxvaluei; a++)
												{
												strategy[1][1] = a;

												maxvaluej = min (2+a,cvec[1]);
												for (b=0; b<maxvaluej; b++)
													{
													strategy[2][1] = b;

													maxvaluek = min (2+max(a,b),cvec[1]);
													for (d=0; d<maxvaluek; d++)
														{
														strategy[3][1] = d;

														maxvaluel = min (2+max(a,max(b,d)),cvec[1]);
														for (e=0; e<maxvaluel; e++)
															{
															strategy[4][1] = e;

															maxvaluem = min (2+max(a,max(b,max(d,e))),cvec[1]);
															for (f=0; f<maxvaluem; f++)
																{
																strategy[5][1] = f;

																maxvaluen = min (2+max(a,max(b,max(d,max(e,f)))),cvec[1]);
																for (g=0; g<maxvaluen; g++)
																	{
																	strategy[6][1] = g;

																	maxvalueo = min (2+max(a,max(b,max(d,max(e,max(f,g))))),cvec[1]);
																	for (h=0; h<maxvalueo; h++)
																		{
																		strategy[7][1] = h;

																		maxvaluep = min (2+max(a,max(b,max(d,max(e,max(f,max(g,h)))))),cvec[1]);
																		for (k=0; k<maxvaluep; k++)
																			{
																			strategy[8][1] = k;

																			optstrat = strategy_check (p,questions,0,cvec,strategy);
																			if (optstrat == 1)
																				{
																				cout << "Feasible streategy found" << endl;
																				exit(1); 
																				}
																		  }
																		}
																	}
															  }
															}
														}
												  }
											  }
											}
										}
									}
								}
							}
						}
					}
				}
		break;
		}

	if (version != 0)
		cout << "No feasible strategy found." << endl;

  free (cvec);

	for (i=0; i<questions; i++)
		 free (strategy[i]);
	free (strategy);

	free (filename);

	return 1;
	}


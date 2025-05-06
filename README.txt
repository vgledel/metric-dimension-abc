Source code to the article

"On the Metric Dimension of K_a x K_b x K_c" 
(Authors: Valentin Gledel, Gerold Jäger) 

This directory contains two issues:

1. Strategies of the article:

	 The directory "strategies" contains all explicit strategies
	 mentioned in the paper.
   One strategy is saved in a file with name 
     "strat_a_b_c_q".
	 where 
	 - "a" stands for the number of colors of the first peg, 
	 - "b" stands for the number of colors of the second peg, 
	 - "c" stands for the number of colors of the third peg, 
	 - "q" stands for the number of main questions of the strategy.
   Then q rows follow, where each row contains one question. 
	 The file starts with "3" standing for the number of pegs.
	 (However, it will also work for a general number of pegs.)
	 Then it contains with the values of a,b,c,q.
	 The numbering of the colors begins with "1".

2. Source code:

   The source code consists of one file "static_abc_mastermind.cc".
	 It should be compiled with the compiler "g++" receiving
	 the executable "a.out".

   The program has the following main option:

	 a) "a.out -v0 strategy_file"

	    Checks whether a strategy of the file "strategy_file" is feasible. 
			If the strategy is feasible, then the 
			output is "optstrat=1".
			If the strategy is not feasible, then 
			the output is "optstrat=0".
			If this is the case, the program additionally 
			outputs a group of possible secrets which 
			receive the same combination of answers.
			Also the combination of answers is listed.

	 Exhaustive search:

   b) "a.out -v1" and "a.out -v2"
	    Proves: There is no feasible strategy with a=3, b=3, c=4, q=4.

   c) "a.out -v3" and "a.out -v4"
	    Proves: There is no feasible strategy with a=3, b=4, c=4, q=4.

   d) "a.out -v5" and "a.out -v6"
	    Proves: There is no feasible strategy with a=4, b=4, c=5, q=5.

   e) "a.out -v7" and "a.out -v8"
	    Proves: There is no feasible strategy with a=4, b=4, c=6, q=6.

   f) "a.out -v9" and "a.out -v10"
	    Proves: There is no feasible strategy with a=4, b=5, c=6, q=6.

   g) "a.out -v11" and "a.out -v12" and "a.out -v13"
	    Proves: There is no feasible strategy with a=4, b=5, c=5, q=6.

   h) "a.out -v14" and "a.out -v15" and "a.out -v16"
	    Proves: There is no feasible strategy with a=4, b=6, c=6, q=7.

   i) "a.out -v17" and "a.out -v18" and "a.out -v19"
	    Proves: There is no feasible strategy with a=5, b=5, c=6, q=7.

   j) "a.out -v20" and "a.out -v21" and "a.out -v22"
	    Proves: There is no feasible strategy with a=5, b=6, c=6, q=7.

   k) "a.out -v23" and "a.out -v24" 
	    Proves: There is no feasible strategy with a=5, b=5, c=7, q=7.

   l) "a.out -v25" and "a.out -v26" 
	    Proves: There is no feasible strategy with a=5, b=5, c=8, q=8.

   m) "a.out -v27" and "a.out -v28" and "a.out -v29" 
	    Proves: There is no feasible strategy with a=5, b=6, c=7, q=8.

   n) "a.out -v30" and "a.out -v31" 
	    Proves: There is no feasible strategy with a=5, b=6, c=8, q=8.

   o) "a.out -v32" and "a.out -v33" and "a.out -v34"
	    Proves: There is no feasible strategy with a=5, b=7, c=7, q=8.

   p) "a.out -v35" and "a.out -v36" and "a.out -v37"
	    Proves: There is no feasible strategy with a=6, b=6, c=7, q=8.

   q) "a.out -v38" and "a.out -v38" and "a.out -v39" and "a.out -v40"
	    Proves: There is no feasible strategy with a=6, b=6, c=8, q=9.

   r) "a.out -v41" and "a.out -v42" and "a.out -v43" and "a.out -v44" and "a.out -v45" 
	    Proves: There is no feasible strategy with a=6, b=7, c=7, q=9.

   s) "a.out -v46" and "a.out -v47" 
	    Proves: There is no feasible strategy with a=6, b=6, c=9, q=9.

   t) "a.out -v48" and "a.out -v49" and "a.out -v50"
	    Proves: There is no feasible strategy with a=6, b=7, c=8, q=9.

	 Again, the numbering of the colors starts with "1"i by default,
	 and if the option "-z" is used, it starts with "0".

Information: 
The exhaustive search through all possible triples, but uses two two reductions:
a) It fixes the last column. 
   There are 2 to 5 such possibilities to fix this column.
	 This leads to 2 to 5 separate runs.
b) The colors in the first two columns are ordered in such a way
   that for a new number which is not used in a previous row,
	 the smallest possible one is chosen.

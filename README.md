# Graph-Algorithms

Imagine you're tasked with redesigning the road system of a fictional country. This country consists of N cities, numbered from 0 to N-1. Pairs of cities are connected by bidirectional roads. A path exists between cities A and B if there's a sequence of distinct cities C1, C2, ..., CM, where C1 = A, CM = B, and for each index i < M, there's a road between cities Ci and Ci+1.

The current road network is in a poor state. Some pairs of cities aren't connected by any path, while other pairs have multiple paths, causing complicated traffic routing. Your goal is to reconstruct the road system by building new roads and removing existing ones. However, these actions come with a cost, so you want to minimize the total expense.

You're provided with three matrices:

country[i][j]: A binary matrix where country[i][j] is 1 if a road exists between city i and city j.
build[i][j]: The cost of building a road between city i and city j, represented using English letters (A-Z for 0-25, a-z for 26-51).
destroy[i][j]: The cost of destroying a road between city i and city j, also represented using English letters.
Your objective is to determine and output the minimum cost required to reconstruct the road network such that there's exactly one path between every pair of distinct cities.

You can assume that the inputs will be valid and there's always a way to achieve a single path between every pair of cities. Your task is to compute and print the minimal cost needed for this road network reconstruction.

	 Sample input 1: 000,000,000 ABD,BAC,DCA ABD,BAC,DCA
	Note: 000,000,000 describes the two-dimensional array country. ABD,BAC,DCA describes the two-
	dimensional array build. ABD,BAC,DCA describes the two-dimensional array destroy. The input
	format is: three strings separated by spaces; each string contains N parts separated by commas; each
	part contains N characters.
	Sample output 1: 3
	Comment: There are three cities, totally disconnected.

	 Sample input 2: 011,101,110 ABD,BAC,DCA ABD,BAC,DCA
	Sample output 2: 1
	Comment: Now the three cities form a connected triangle and we need to destroy one road. Optimal
	solution is to destroy the road between the cities 0-1 (cost 1).

	 Sample input 3: (note: all inputs are on the same line. I just couldn't fit them in one line in this pdf.)
	011000,101000,110000,000011,000101,000110
	ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA
	ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA
	Sample output 3: 7
	Comment: We have six cities forming two separate triangles. Destroy one road in each triangle (costs
	1 for each road) and then join the triangles by a new road (costs 5).

	 Sample input 4: 0 A A
	Sample output 4: 0
	Comment: One city is okay just as it is.

	 Sample input 5: 0001,0001,0001,1110 AfOj,fAcC,OcAP,jCPA AWFH,WAxU,FxAV,HUVA
	Sample output 5: 0
	Comment: We have four cities, which are connected in such a way that there is exactly one path
	between each two cities.
	Thus there is nothing to reconstruct.

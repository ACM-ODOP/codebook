#!/usr/bin/env python3

import os
import sys

rootDir = sys.argv[1]

for dirPath, dirNames, fileNames in os.walk(rootDir):
	fileNames = [f for f in fileNames if not f[0] == '.']
	dirNames[:] = [d for d in dirNames if not d[0] == '.' and d != 'pdf']
	if dirPath != rootDir:
		print("\\section{%s}"%dirPath[len(rootDir)+1:].replace('_','\\_'))
	for f in fileNames:
		print("\\subsection{%s}"%os.path.join(dirPath, f)[len(rootDir)+1:].replace('_','\\_'))
		print("\\lstinputlisting{\"%s\"}"%os.path.join(dirPath, f))

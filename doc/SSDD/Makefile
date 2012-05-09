
# run make pdf to explicitly generate the .pdf version

FILE = SSDD

$(FILE).pdf: $(FILE).tex
	pdflatex $(FILE).tex

pdf:
	pdflatex $(FILE).tex; rm -rf $(FILE).out $(FILE).aux $(FILE).log $(FILE).toc $(FILE).dvi

clean:
	rm -rf $(FILE).pdf $(FILE).out $(FILE).aux $(FILE).log $(FILE).toc $(FILE).dvi

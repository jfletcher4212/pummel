# run make pdf to explicitly generate .pdf gtom .tex

FILE = TP_Template

$(FILE).pdf: $(FILE).tex
	pdflatex $(FILE).tex

pdf:
	pdflatex $(FILE).tex; rm -rf $(FILE).out $(FILE).aux $(FILE).log $(FILE).toc $(FILE).dvi

clean:
	rm -rf $(FILE).pdf $(FILE).out $(FILE).aux $(FILE).log $(FILE).toc $(FILE).dvi


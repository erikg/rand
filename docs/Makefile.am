man_MANS = rand.1

EXTRA_DIST=$(man_MANS)

rand.ps: rand.1
	groff -t -e -mandoc rand.1 -Tps > rand.ps

rand.pdf: rand.ps
	ps2pdf rand.ps rand.pdf

clean:
	rm -rf doxygen rand.ps rand.pdf

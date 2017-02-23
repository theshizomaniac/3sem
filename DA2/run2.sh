cat testdataminus.txt testdatacheck.txt testdataplus.txt > testdata.txt
cat testdata.txt testdataminus.txt > testdata2.txt
./DA2 < testdata.txt


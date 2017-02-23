cat save.txt >> testdataminus.txt
cat load.txt >> testdatacheck.txt
cat testdataminus.txt testdatacheck.txt testdataplus.txt > testdata.txt
./DA2 < testdata.txt


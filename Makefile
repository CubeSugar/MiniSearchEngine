Preprocess:
	python3 ./bin/Preprocs_generateRipepageLib.py
	echo 'Build RipepageLib Done!'
	python3 ./bin/Preprocs_generateIndexAndQueryLib.py
	echo 'Build IndexLib & QueryLib Done!'
	echo 'Preprocess Done!'
	
DoWordSegementation:
	echo 'Do Word Segementation Done!'

RemoveDuplication:
	echo 'Remove Duplication Done!'

CalcSimilarity:
	echo 'Calculate Similarity Done!'

Clean:
	rm -rf ./bin/__pycache__






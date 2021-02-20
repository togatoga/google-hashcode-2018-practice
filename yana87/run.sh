g++ -O2 -std=gnu++14 -Wall -Wextra -Wshadow solve.cpp && 
(
	echo "Compiled!!"
	for i in $(ls input); do
		# echo "./a.out < input/$i > output/$i"
		./a.out < input/$i > output/$i
		python ../score.py input/$i output/$i
	done
	rm ./a.out
)
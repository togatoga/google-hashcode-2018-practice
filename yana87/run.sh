g++ -O2 -std=gnu++14 -Wall -Wextra -Wshadow solve.cpp && 
(
	echo "Compiled!!"
	files=$(ls ../input)
	# files=("d_metropolis.in")
	for i in $files; do
		# echo "./a.out < ../input/$i > output/$i"
		./a.out < ../input/$i > output/$i
		echo "python ../score.py ../input/$i output/$i"
		python ../score.py ../input/$i output/$i
	done
	rm ./a.out
)
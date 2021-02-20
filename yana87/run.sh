g++ -O2 -std=gnu++14 -Wall -Wextra -Wshadow solve.cpp && 
(
	echo "Compiled!!"
	for i in $(ls input); do
		echo "./a.out < input/$i > distance/$i"
		./a.out < input/$i > distance/$i
	done
	rm ./a.out
)
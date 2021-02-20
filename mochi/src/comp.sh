while true; do
    ./make_random > input.txt
    ans1=$(./A < input.txt)
    ans2=$(./guchoku < input.txt)
    if [ $ans1 != $ans2 ]; then
        echo "Wrong Answer"
        echo $ans1
        echo $ans2
        exit
    fi
done
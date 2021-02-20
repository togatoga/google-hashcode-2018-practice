input_names=('../../input/a_example.in' '../../input/b_should_be_easy.in' '../../input/c_no_hurry.in' '../../input/d_metropolis.in' '../../input/e_high_bonus.in')
output_names=('../output/a_example.out' '../output/b_should_be_easy.out' '../output/c_no_hurry.out' '../output/d_metropolis.out' '../output/e_high_bonus.out')

# for input_name in "${input_names[@]}"
# do
#   ./A ${input_name} ${output_names}
# done

for((i=0; i<${#input_names[@]}; i++))
do
    python3 ../../score.py ${input_names[i]} ${output_names[i]}
done
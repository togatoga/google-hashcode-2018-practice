original_name='A.cc'
target_names=('B.cc' 'C.cc' 'D.cc' 'E.cc' 'F.cc')

for target_name in "${target_names[@]}"
do
  cp ${original_name} ${target_name}
done
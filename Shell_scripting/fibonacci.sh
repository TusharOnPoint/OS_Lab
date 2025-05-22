read -p "Enter a number: " number
echo -n "Fibonacci numbers up to $number position: "
f1=0
f2=1
for (( i = 0; i < number; i++ )); do
    echo -n "$f1 "
    f3=$(( f1+f2 ))
    f1=$f2
    f2=$f3
done

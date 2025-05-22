read -p "Enter a number: " number
echo "Enter $number numbers: "
sum=0
for (( i = 1; i <= number; i++ )); do
    read num
    sum=$((sum + num))
done
avg=$(echo "scale=2; $sum / $number" | bc)
echo "Average of $number numbers is $avg."

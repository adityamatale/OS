#!/bin/bash



# Main script



# Prompt the user to enter the array elements

echo "Enter the array elements separated by spaces:"

read -a input_array



# Call the sort_array function with the input array

sort_array=($(echo "${input_array[@]}" | tr ' ' '\n' | sort -nr))



# Display the sorted array

echo "Sorted array: ${sort_array[@]}"







# Main script



# Prompt the user to enter the array elements

echo "Enter the array elements separated by spaces:"

read -a input_array



# Call the sort_array function with the input array

sort_array=($(echo "${input_array[@]}" | tr ' ' '\n' | sort -n))



# Display the sorted array

echo "Sorted array (ascending): ${sort_array[@]}"


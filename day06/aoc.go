package main

import (
	"fmt"
	"io/ioutil"
	//"os"
	// "strconv"
	// "strings"
)

func main() {
	input, err := ioutil.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}

	part1(string(input))
	part2(string(input))
}

func part1(input string) {

	length := len(input)

	// Loop over the string with len.
	for i := 0; i < length-4; i++ {
		str := input[i : i+4]
		if stringIsDistinct(str) {

			fmt.Println(i + 4)
			break
		}
	}
}

func part2(input string) {
	length := len(input)

	// Loop over the string with len.
	for i := 0; i < length-14; i++ {
		str := input[i : i+14]
		if stringIsDistinct(str) {

			fmt.Println(i + 14)
			break
		}
	}
}

func stringIsDistinct(str string) bool {
	for i := 0; i < len(str); i++ {
		for j := i + 1; j < len(str); j++ {
			if str[i] == str[j] {
				return false
			}
		}
	}

	return true
}

// func getSolutionPart1(input []int) int {
// 	sum := 0
// 	for _, value := range input {
// 		sum += value
// 	}
// 	return sum
// }

// func getSolutionPart2(input []int) int {
// 	product := 1
// 	for _, value := range input {
// 		product *= value
// 	}
// 	return product
// }

// func main() {
// 	inputBytes, err := ioutil.ReadFile("input.txt")
// 	if err != nil {
// 		panic("couldn't read input")
// 	}

// 	input, err := parseInput(string(inputBytes))
// 	if err != nil {
// 		panic("couldn't parse input")
// 	}

// 	fmt.Println("Go")
// 	part := os.Getenv("part")

// 	if part == "part2" {
// 		fmt.Println(getSolutionPart2(input))
// 	} else {
// 		fmt.Println(getSolutionPart1(input))
// 	}
// }

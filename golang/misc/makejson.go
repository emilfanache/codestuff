// Write a program which prompts the user to first enter a name, and then enter an address.
// Your program should create a map and add the name and address to the map using the keys “name”
// and “address”, respectively. Your program should use Marshal() to create a JSON object from
// the map, and then your program should print the JSON object.

package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"os"
)

func main() {
	var name string = ""
	var address string = ""

	m := make(map[string]string)

	fmt.Printf("Enter name: ")

	scanner := bufio.NewScanner(os.Stdin)
	if scanner.Scan() {
		name = scanner.Text()
	} else {
		fmt.Println("Error when adding the name!")
		return
	}

	fmt.Printf("Enter address: ")

	scanner = bufio.NewScanner(os.Stdin)
	if scanner.Scan() {
		address = scanner.Text()
	} else {
		fmt.Println("Error when adding the address!")
		return
	}

	m["name"] = name
	m["address"] = address

	jsonMarshal, err := json.Marshal(m)

	if err != nil {
		fmt.Println("Error converting map to json!")
	} else {
		fmt.Printf("%s\n", jsonMarshal)
	}
	return
}

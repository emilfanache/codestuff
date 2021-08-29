// Write a program which reads information from a file and represents it in a slice of structs. Assume
// that there is a text file which contains a series of names. Each line of the text file has a
// first name and a last name, in that order, separated by a single space on the line.

// Your program will define a name struct which has two fields, fname for the first name, and lname
// for the last name. Each field will be a string of size 20 (characters).

// Your program should prompt the user for the name of the text file. Your program will successively read
// each line of the text file and create a struct which contains the first and last names found in the
// file. Each struct created will be added to a slice, and after all lines have been read from the file,
// your program will have a slice containing one struct for each line in the file. After reading all
// lines from the file, your program should iterate through your slice of structs and print the first
// and last names found in each struct.

package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Names_t struct {
	fname string
	lname string
}

func main() {

	const NAME_BUFFER_SIZE = 20

	var fileName string
	var nm []Names_t
	fmt.Printf("Enter file name: ")

	scanner := bufio.NewScanner(os.Stdin)
	if scanner.Scan() {
		fileName = scanner.Text()
	} else {
		fmt.Println("Error when adding the file name!")
		return
	}

	fd, err := os.Open(fileName)
	if err != nil {
		fmt.Printf("Unable to open file %s\n", fileName)
		return
	}

	scanner = bufio.NewScanner(fd)
	for scanner.Scan() {
		line := scanner.Text()
		spl := strings.Split(line, " ")
		splitFirstName := spl[0]
		if len(splitFirstName) > NAME_BUFFER_SIZE {
			splitFirstName = splitFirstName[:NAME_BUFFER_SIZE]
		}

		splitLastName := spl[1]
		if len(splitLastName) > NAME_BUFFER_SIZE {
			splitLastName = splitLastName[:NAME_BUFFER_SIZE]
		}

		person := Names_t{
			fname: splitFirstName,
			lname: splitLastName,
		}
		nm = append(nm, person)
	}

	for i := 0; i < len(nm); i++ {
		fmt.Printf("%s %s\n", nm[i].fname, nm[i].lname)
	}
	fd.Close()
	return
}

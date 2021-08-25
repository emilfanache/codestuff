/* Write a program which prompts the user to enter integers and stores the integers in a sorted slice.
 * The program should be written as a loop. Before entering the loop, the program should create an
 * empty integer slice of size (length) 3. During each pass through the loop, the program prompts
 * the user to enter an integer to be added to the slice. The program adds the integer to the slice,
 * sorts the slice, and prints the contents of the slice in sorted order. The slice must grow in size
 * to accommodate any number of integers which the user decides to enter. The program should only quit
 * (exiting the loop) when the user enters the character ‘X’ instead of an integer.
 */

package main

import (
    "fmt"
    "sort"
    "strconv"
)

func main() {
    var inputVal string
    sl := make([]int, 3)

    for {
        fmt.Print("Please insert value: ")
        fmt.Scan(&inputVal)
        if inputVal == "X" {
            fmt.Println("Exiting...")
            break
        }

        integerInput, err := strconv.Atoi(inputVal)
        if err != nil {
            fmt.Println(err)
            continue
        }

        sl = append(sl, integerInput)
        sort.Ints(sl)
        fmt.Printf("%v\n", sl)
    }

}

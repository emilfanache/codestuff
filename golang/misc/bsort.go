// Write a Bubble Sort program in Go. The program
// should prompt the user to type in a sequence of up to 10 integers. The program
// should print the integers out on one line, in sorted order, from least to
// greatest. Use your favorite search tool to find a description of how the bubble
// sort algorithm works.

// As part of this program, you should write a
// function called BubbleSort() which
// takes a slice of integers as an argument and returns nothing. The BubbleSort() function should modify the slice so that the elements are in sorted
// order.

// A recurring operation in the bubble sort algorithm is
// the Swap operation which swaps the position of two adjacent elements in the
// slice. You should write a Swap() function which performs this operation. Your Swap()
// function should take two arguments, a slice of integers and an index value i which
// indicates a position in the slice. The Swap() function should return nothing, but it should swap
// the contents of the slice in position i with the contents in position i+1.

package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

/* Source: wikipedia
procedure bubbleSort(A : list of sortable items)
    n := length(A)
    repeat
        newn := 0
        for i := 1 to n - 1 inclusive do
            if A[i - 1] > A[i] then
                swap(A[i - 1], A[i])
                newn := i
            end if
        end for
        n := newn
    until n ≤ 1
end procedure
*/

func Swap(sl []int, i int) {
    sl[i], sl[i+1] = sl[i+1], sl[i]
}

func BubbleSort(sl []int) {
    length := len(sl)
    for length > 1 {
        newn := 0
        for i := 1; i <= length-1; i++ {
            if sl[i-1] > sl[i] {
                Swap(sl, i-1)
                newn = i
            }
        }
        length = newn
    }
}

func main() {
    var numList string
    const MAX_NUM_INT = 10
    sl := make([]int, 0, MAX_NUM_INT)

    fmt.Print("Please insert list of numbers separated by space: ")

    scanner := bufio.NewScanner(os.Stdin)
    if scanner.Scan() {
        numList = scanner.Text()
    } else {
        fmt.Println("Error fetching list of numbers!")
        return
    }

    splitList := strings.Split(numList, " ")
    numCount := 0
    for i := 0; i < len(splitList); i++ {
        num, err := strconv.Atoi(splitList[i])
        if err != nil {
            fmt.Printf("Unable to convert %v to a number\n", splitList[i])
            continue
        }

        sl = append(sl, num)
        numCount++
        if numCount == MAX_NUM_INT {
            // we've put 10 integers in the list, we don't care if it's more
            break
        }
    }

    BubbleSort(sl)

    fmt.Printf("Sorted: %v\n", sl)
}

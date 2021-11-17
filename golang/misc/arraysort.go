/*
* Write a program to sort an array of integers. The program should
* partition the array into 4 parts, each of which is sorted by a
* different goroutine. Each partition should be of approximately equal
* size. Then the main goroutine should merge the 4 sorted subarrays
* into one large sorted array.

* The program should prompt the user to input a series of integers.
* Each goroutine which sorts ¼ of the array should print the subarray
* that it will sort. When sorting is complete, the main goroutine
* should print the entire sorted list.
*/

package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
    "sync"
    "sort"
)

func sortArray(intArr []int, idx int, wg *sync.WaitGroup) {
    defer wg.Done()
    
    fmt.Printf("Routine %v will sort array: %v\n", idx, intArr)
    sort.Slice(intArr, func(i, j int) bool {
        return intArr[i] < intArr[j]
    })
}

func main() {
    var inputList string
    var wg sync.WaitGroup
    var fourArrays[4][]int

    intSl := make([]int, 0)

    fmt.Print("Please insert several integer values separated by space: ")

    scanner := bufio.NewScanner(os.Stdin)
    if scanner.Scan() {
        inputList = scanner.Text()
    } else {
        fmt.Println("Error fetching the input list of values!")
        return
    }

    splitList := strings.Split(inputList, " ")
    for i := 0; i < len(splitList); i++ {
        vl, err := strconv.Atoi(splitList[i])
        if err != nil {
            fmt.Printf("Unable to convert %v to a int value\n", splitList[i])
            continue
        }

        intSl = append(intSl, vl)
    }

    start := 0
    for idx := 0; idx < 4; idx++ {
        wg.Add(1)

        end := len(intSl) * (idx + 1) / 4
        fourArrays[idx] = make([]int, len(intSl)/4)
        fourArrays[idx] = intSl[start : end]

        go sortArray(fourArrays[idx], idx, &wg)
        if start != end {
            start = end
        }
    }

    wg.Wait()
    
    // merge arrays into one
    final := []int{}

    for idx := 0; idx < 4; idx++ {
        final = append(final, fourArrays[idx]...)
    }

    fmt.Printf("The final array after sorting subarrays: %v \n", final)

    sort.Ints(final)

    fmt.Printf("The final array after full sort: %v \n", final)
}

//Let us assume the following formula for
//displacement s as a function of time t, acceleration a, initial velocity vo,
//and initial displacement so.

//s = ½ a t2 + vot + so

//Write a program which first prompts the user
//to enter values for acceleration, initial velocity, and initial displacement.
//Then the program should prompt the user to enter a value for time and the
//program should compute the displacement after the entered time.

//You will need to define and use a function
//called GenDisplaceFn() which takes three float64
//arguments, acceleration a, initial velocity vo, and initial
//displacement so. GenDisplaceFn()
//should return a function which computes displacement as a function of time,
//assuming the given values acceleration, initial velocity, and initial
//displacement. The function returned by GenDisplaceFn() should take one float64 argument t, representing time, and return one
//float64 argument which is the displacement travelled after time t.

//For example, let’s say that I want to assume
//the following values for acceleration, initial velocity, and initial
//displacement: a = 10, vo = 2, so = 1. I can use the
//following statement to call GenDisplaceFn() to
//generate a function fn which will compute displacement as a function of time.

//fn := GenDisplaceFn(10, 2, 1)

//Then I can use the following statement to
//print the displacement after 3 seconds.

//fmt.Println(fn(3))

//And I can use the following statement to print
//the displacement after 5 seconds.

//fmt.Println(fn(5))


package main

import (
    "bufio"
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

func GenDisplaceFn(acc, vo, disp float64) func(float64) float64{
    fn := func(tm float64) float64 {
            return 0.5 * acc * math.Pow(tm, 2) + (vo * tm) + disp
    }
    return fn
}

func main() {
    var inputList string
    var tm string

    sl := make([]float64, 0, 3)

    fmt.Print("Please insert acceleration, initial velocity and initial displacement separated by space: ")

    scanner := bufio.NewScanner(os.Stdin)
    if scanner.Scan() {
        inputList = scanner.Text()
    } else {
        fmt.Println("Error fetching the input list of values!")
        return
    }
    
    splitList := strings.Split(inputList, " ")
    varCount := 0
    for i := 0; i < len(splitList); i++ {
        fl, err := strconv.ParseFloat(splitList[i], 64)
        if err != nil {
            fmt.Printf("Unable to convert %v to a float64 value\n", splitList[i])
            continue
        }

        sl = append(sl, fl)
        varCount++
        if varCount == 3 {
            break
        }
    }
    
    if varCount != 3 {
        fmt.Println("You need to insert the 3 values separated by spaces")
        return
    }

    fmt.Print("Please insert time: ")

    scanner = bufio.NewScanner(os.Stdin)
    if scanner.Scan() {
        tm = scanner.Text()
    } else {
        fmt.Println("Error fetching the time!")
        return
    }
    t, err := strconv.ParseFloat(tm, 64)
    if err != nil {
        fmt.Printf("Unable to convert time %v to a float64 value\n", tm)
        return
    }   

    fmt.Printf("--- You added ---\n")
    fmt.Printf("acceleration: %v\n", sl[0]) 
    fmt.Printf("initial velocity: %v\n", sl[1]) 
    fmt.Printf("initial displacement: %v\n", sl[2]) 
    fmt.Printf("time: %v\n", t) 
    fmt.Printf("------------\n")
   
    fn := GenDisplaceFn(sl[0], sl[1], sl[2])

    fmt.Printf("Displacement after %v seconds is: ", t)
    fmt.Println(fn(t))
}

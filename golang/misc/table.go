package main

import (
    "fmt"
    "sort"
)

type Person_t struct {
    name string
    age  int
    nick string
}

var PersonTable = []Person_t{
    {"John", 20, "Johnny"},
    {"Marianne", 22, "Mary"},
    {"Samuel", 25, "Sammy"},
    {"Andrew", 18, "Andy"},
}

// https://golangbyexample.com/sort-custom-struct-collection-golang/
// in order to sort we need to implement sort.Interface

type Peer []Person_t

func (p Peer) Len() int {
    return len(PersonTable)
}

func (p Peer) Less(i, j int) bool {
    return (PersonTable[i].age < PersonTable[j].age)
}

func (p Peer) Swap(i, j int) {
    PersonTable[i], PersonTable[j] = PersonTable[j], PersonTable[i]
}

func printTable(header string) {
    fmt.Println(header)
    for i := 0; i < len(PersonTable); i++ {
        fmt.Printf("%s %d %s \n", PersonTable[i].name, PersonTable[i].age, PersonTable[i].nick)
    }
    fmt.Println()
}

func main() {
    printTable("Before sorting:")
    sort.Sort(Peer(PersonTable))
    printTable("After sorting:")
}

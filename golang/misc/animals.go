//Write a program which allows the user to get information about a 
//predefined set of animals. Three animals are predefined, cow, bird, and snake. 
//Each animal can eat, move, and speak. The user can issue a request to find out 
//one of three things about an animal: 1) the food that it eats, 2) its method of 
//locomotion, and 3) the sound it makes when it speaks. The following table contains 
//the three animals and their associated data which should be hard-coded into your program.
//Animal	Food eaten	Locomotion method	Spoken sound
//cow	grass	walk	moo
//bird	worms	fly	peep
//snake	mice	slither	hsss 
//Your program should present the user with a prompt, “>”, to indicate that the user 
//can type a request. Your program accepts one request at a time from the user, prints out
//the answer to the request, and prints out a new prompt. Your program should continue 
//in this loop forever. Every request from the user must be a single line containing 2 strings. 
//The first string is the name of an animal, either “cow”, “bird”, or “snake”. The second string
//is the name of the information requested about the animal, either “eat”, “move”, or “speak”.
//Your program should process each request by printing out the requested data.
//You will need a data structure to hold the information about each animal. 
//Make a type called Animal which is a struct containing three fields:food, locomotion, and noise, 
//all of which are strings. Make three methods called Eat(), Move(), and Speak(). The receiver type 
//of all of your methods should be your Animal type. The Eat() method should print the animal’s food,
//the Move() method should print the animal’s locomotion, and the Speak() method should print the 
//animal’s spoken sound. Your program should call the appropriate method when the user makes a request.



package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

type Animal struct {
    food string
    locomotion string
    noise string
}

var AnimalTable = []Animal{
    {"grass", "walk",    "moo"},
    {"worms", "fly",     "peep"},
    {"mice",  "slither", "hsss"},
}

func (a Animal) getIdFromAnimalString(beast string) (int, bool) {
    allAnimals := [3]string{"cow", "bird", "snake"}

    for i:=0; i < len(allAnimals); i++ {
        if strings.ToLower(beast) == allAnimals[i] {
            return i, true
        }
    }
    
    return -1, false
}

func (a Animal) callAction(action string, beastId int) bool {
    switch (strings.ToLower(action)) {
        case "eat":
            a.Eat(beastId)
            return true
        
        case "move":
            a.Move(beastId)
            return true
        
        case "speak":
            a.Speak(beastId)
            return true
    }

    return false
}


func (a Animal)Eat(beast int) {
    fmt.Printf("%v\n", AnimalTable[beast].food)
}

func (a Animal)Move(beast int) {
    fmt.Printf("%v\n", AnimalTable[beast].locomotion)
}

func (a Animal)Speak(beast int) {
    fmt.Printf("%v\n", AnimalTable[beast].noise)
}

func main() {
    var instruction string
    var a Animal

    fmt.Println("Please insert animal name and action. Press X to exit!")

    for {
        fmt.Printf("> ")

        scanner := bufio.NewScanner(os.Stdin)
        if scanner.Scan() {
            instruction = scanner.Text()
        } else {
            fmt.Println("Error when fetching the initial instruction!")
            return
        }
        
        if instruction == "X" {
            fmt.Println("Exiting")
            return
        }
        
        spl := strings.Split(instruction, " ")            
        if len(spl) != 2 {
            fmt.Println("Your request needs to contain 2 strings!")
            continue
        }
        
        beastId, ok := a.getIdFromAnimalString(spl[0])
        if !ok {
            fmt.Println("The animal string is not correct (it can only be 'cow', 'bird', 'snake')")
            continue
        }
        
        act := a.callAction(spl[1], beastId)
        if !act{
            fmt.Println("The action string is not correct (it can only be 'eat', 'move', 'speak')")
            continue
        }
    }
}

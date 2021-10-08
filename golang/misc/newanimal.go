//Write a program which allows the user to create a set of animals and to
//get information about those animals. Each animal has a name and can be
//either a cow, bird, or snake. With each command, the user can either
//create a new animal of one of the three types, or the user can request
//information about an animal that he/she has already created. Each animal
//has a unique name, defined by the user. Note that the user can define
//animals of a chosen type, but the types of animals are restricted to
//either cow, bird, or snake. The following table contains the three types
//of animals and their associated data.
//Animal    Food eaten  Locomtion method    Spoken sound
//cow   grass   walk    moo
//bird  worms   fly peep
//snake mice    slither hsss
//Your program should present the user with a prompt, “>”, to indicate
//that the user can type a request. Your program should accept one command
//at a time from the user, print out a response, and print out a new prompt
//on a new line. Your program should continue in this loop forever. Every
//command from the user must be either a “newanimal” command or a “query”
//command. Each “newanimal” command must be a single line containing three
//strings. The first string is “newanimal”. The second string is an
//arbitrary string which will be the name of the new animal.
//The third string is the type of the new animal, either “cow”, “bird”, or
//“snake”. Your program should process each newanimal command by creating
//the new animal and printing “Created it!” on the screen.
//Each “query” command must be a single line containing 3 strings.
//The first string is “query”. The second string is the name of the animal.
//The third string is the name of the information requested about the
//animal, either “eat”, “move”, or “speak”. Your program should process
//each query command by printing out the requested data.
//Define an interface type called Animal which describes the methods of an
//animal. Specifically, the Animal interface should contain the methods
//Eat(), Move(), and Speak(), which take no arguments and return no values.
//The Eat() method should print the animal’s food, the Move() method
//should print the animal’s locomotion, and the Speak() method should
//print the animal’s spoken sound. Define three types Cow, Bird, and
//Snake. For each of these three types, define methods Eat(), Move(),
//and Speak() so that the types Cow, Bird, and Snake all satisfy the Animal
//interface. When the user creates an animal, create an object of the
//appropriate type. Your program should call the appropriate method when
//the user issues a query command.


package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

type Animal interface {
    Eat()
    Move()
    Speak()
}

type Cow struct {
    food, locomotion, noise string
}

type Bird struct {
    food, locomotion, noise string
}

type Snake struct {
    food, locomotion, noise string
}

func (c Cow) Eat() {
    fmt.Println(c.food)
}

func (c Cow) Move() {
    fmt.Println(c.locomotion)
}

func (c Cow) Speak() {
    fmt.Println(c.noise)
}

func (b Bird) Eat() {
    fmt.Println(b.food)
}

func (b Bird) Move() {
    fmt.Println(b.locomotion)
}

func (b Bird) Speak() {
    fmt.Println(b.noise)
}

func (s Snake) Eat() {
    fmt.Println(s.food)
}

func (s Snake) Move() {
    fmt.Println(s.locomotion)
}

func (s Snake) Speak() {
    fmt.Println(s.noise)
}


func main() {
    var instruction string
    animap := make(map[string]Animal)
    found := false

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
        if len(spl) != 3 {
            fmt.Println("Your request needs to contain 3 strings!")
            continue
        }

        userAction := strings.ToLower(spl[0])
        animalName := strings.ToLower(spl[1])
        beastTypeOrAct := strings.ToLower(spl[2])

        if userAction != "newanimal" && userAction != "query" {
            fmt.Println("The initial string is not correct (it can only be 'newanimal' or 'query')")
            continue
        }

        if userAction == "newanimal" {
            allAnimals := [3]string{"cow", "bird", "snake"}
            found = false
            for _, beast := range allAnimals {
                if beastTypeOrAct == beast {
                    found = true
                    break
                }
            }

            if !found {
                fmt.Println("The animal string is wrong (it can only be 'cow', 'bird' or 'snake')")
                continue
            }

        } else {
            allActions := [3]string{"eat", "move", "speak"}
            found = false
            for _, act := range allActions {
                if beastTypeOrAct == act {
                    found = true
                    break
                }
            }
            if !found {
                fmt.Println("The animal string is wrong (it can only be 'eat', 'move' or 'speak')")
                continue
            }
        }


        if userAction == "newanimal" {
            switch beastTypeOrAct {
                case "cow":
                    animap[animalName] = Cow{"grass", "walk", "moo"}
                case "bird":
                    animap[animalName] = Bird{"worms", "fly", "peep"}
                case "snake":
                    animap[animalName] = Snake{"mice",  "slither", "hsss"}
            }

            fmt.Println("Created it!")

        } else if userAction == "query" {

            found = false
            for name, animal := range animap {
                if name == animalName {
                    found  = true
                    switch beastTypeOrAct {
                        case "eat":
                            animal.Eat()
                        case "move":
                            animal.Move()
                        case "speak":
                            animal.Speak()
                    }
                    continue
                }
            }

            if !found {
                fmt.Println("I couldn't find the name of the animal")
                continue
            }

        }
    }
}

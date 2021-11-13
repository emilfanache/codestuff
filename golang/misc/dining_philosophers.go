//Implement the dining philosopher’s problem with the following 
//constraints/modifications"

//1. There should be 5 philosophers sharing chopsticks, with one chopstick
//between each adjacent pair of philosophers.
//2. Each philosopher should eat only 3 times (not in an infinite loop as
//we did in lecture)
//3. The philosophers pick up the chopsticks in any order, not 
//lowest-numbered first (which we did in lecture).
//4. In order to eat, a philosopher must get permission from a host which
//executes in its own goroutine.
//5. The host allows no more than 2 philosophers to eat concurrently.
//6. Each philosopher is numbered, 1 through 5.
//7. When a philosopher starts eating (after it has obtained necessary 
//locks) it prints “starting to eat <number>” on a line by itself, where 
//<number> is the number of the philosopher.
//8. When a philosopher finishes eating (before it has released its locks)
//it prints “finishing eating <number>” on a line by itself, where 
//<number> is the number of the philosopher.


package main

import (
    "fmt"
    "sync"
    "time"
    "math/rand"
)

type ChopS struct{ sync.Mutex }

type Philo struct {
    leftCS, rightCS *ChopS
}

func (p Philo) eat(id int, wg *sync.WaitGroup, hostChan chan int) {
    i := 1 
    // send signal (int) to channel, if it has enough room (buffered channel = 2 slots)
    // it will receive the request and process it, otheriwse it will get stuck    
    hostChan <- id
    for i <= 3 {
        p.leftCS.Lock()
        p.rightCS.Lock()
        fmt.Printf("Starting to eat %v\n", id)
        time.Sleep(time.Second)
         fmt.Printf("Finishing eating %v\n", id)
        p.rightCS.Unlock()
        p.leftCS.Unlock()
        i++
    }

    wg.Done()
  
}

func host(hostChan chan int, wg *sync.WaitGroup) {
    for {
        <-hostChan
        time.Sleep(time.Second)
    }
}

func shuffleCSticksOrder() []int {
    a := []int{0, 1, 2, 3, 4}
    rand.Seed(time.Now().UnixNano())
    rand.Shuffle(len(a), func(i, j int) { a[i], a[j] = a[j], a[i]})
    return a
}

func main() {
    fmt.Printf("Initialize\n")
    var wg sync.WaitGroup
    var hostChan = make(chan int, 2)
   
    CSticks := make([]*ChopS, 5)
    for i := 0; i < 5; i++ {
        CSticks[i] = new(ChopS)
    }
    philos := make([]*Philo, 5)
    order := shuffleCSticksOrder()
    fmt.Printf("Chopsticks order: %v\n", order)
    for i := 0; i < 5; i++ {
        philos[i] = &Philo{CSticks[order[i]], CSticks[order[(i+1)%5]]}
    }

    go host(hostChan, &wg)
    for i := 0; i < 5; i++ {
        wg.Add(1)
        go philos[i].eat(i, &wg, hostChan)
    }

    wg.Wait()
    close(hostChan)
    fmt.Printf("All done\n")

}


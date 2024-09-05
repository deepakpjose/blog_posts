package main

import "fmt"
import "sync"

var (
	my      sync.Mutex
    counter int
)

func mythread(arg string, done chan struct{}) {
    var i int

    fmt.Println("Thread name: ", arg)
    for i = 0; i < 1e7; i++ {
		my.Lock()
        counter++
		my.Unlock()
    }
    done <- struct{}{}
    fmt.Println("Finished Thread name: ", arg)
}

func main() {
    var done = make(chan struct{})

    go mythread("thread1", done)
    go mythread("thread2", done)

    <- done
    <- done

    fmt.Println("counter is ", counter)
}

package main

import "fmt"

var (
    counter int
)

func mythread(arg string, done chan struct{}) {
    var i int

    fmt.Println("Thread name: ", arg)
    for i = 0; i < 1e7; i++ {
        counter++
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
